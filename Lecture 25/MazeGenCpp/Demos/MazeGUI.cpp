#include "GUI/MiniGUI.h"
#include "grid.h"
#include "vector.h"
#include "priorityqueue.h"
#include "gthread.h"
#include <functional>
using namespace std;

/* Type representing a cell in the maze. */
enum class Cell {
    WALL,
    EMPTY
};

/* Type representing the state of a cell during the depth-first search. */
enum class DFSState {
    UNEXPLORED, // Unexplored empty cell
    ACTIVE,     // Explored cell that is part of the path currently being explored
    VISITED,    // Explored cell that is fully explored
    CURRENT     // Explored cell that is at the end of the path being explored
};

/* Type representing a function that draws the state of the maze. */
using Reporter = function<void(const Grid<Cell>&)>;

Grid<Cell> initialMazeOfSize(int numRows, int numCols);
void dfsFrom(int row, int col, Grid<Cell>& maze, Grid<DFSState>& cellStates, Reporter reporter);

/* An m x n maze is represented as a (2m + 1) x (2n + 1) grid. The cells in the
 * maze are at positions with odd coordinates. All other locations are either
 * walls or passageways connecting the cells. For example, a 3x2 maze might look
 * like this:
 *
 *   WWWWWWW
 *   W W   W
 *   W W W W
 *   W   W W
 *   WWWWWWW
 *
 * The state of the DFS exploration is represented as separate grid whose coordinates
 * map onto the logical grid cells in the maze. For example, a 3x2 maze might look
 * like this:
 *
 *     UUU
 *     UUU
 *
 * Here, U indicates "unexplored."
 *
 * The last parameter to this function is a callback to be invoked at each time step to
 * visualize the state of the maze.
 */
Grid<Cell> makeDFSMaze(int numRows, int numCols, Reporter reporter) {
    auto result = initialMazeOfSize(numRows, numCols);
    Grid<DFSState> dfsState(numRows, numCols, DFSState::UNEXPLORED);

    dfsFrom(0, 0, result, dfsState, reporter);

    return result;
}

/* Creates the initial grid maze. This will consist of a bunch of walls, with empty cells
 * placed in the following pattern:
 *
 *   WWWWWWWWWWWWWWWWWWW
 *   W W W W W W W W W W
 *   WWWWWWWWWWWWWWWWWWW
 *   W W W W W W W W W W
 *   WWWWWWWWWWWWWWWWWWW
 *   W W W W W W W W W W
 *   WWWWWWWWWWWWWWWWWWW
 *   W W W W W W W W W W
 *   WWWWWWWWWWWWWWWWWWW
 *
 * Another way to see this: the open locations occur at all positions whose row and column
 * are odd numbers.
 */
Grid<Cell> initialMazeOfSize(int numRows, int numCols) {
    Grid<Cell> result(2 * numRows + 1, 2 * numCols + 1, Cell::WALL);
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            result[2 * row + 1][2 * col + 1] = Cell::EMPTY;
        }
    }
    return result;
}

/* Runs the DFS maze generation algorithm from the starting location, updating the
 * maze and the DFS state as it goes.
 *
 * At each point, we pick a random ordering of the neighboring cells to visit. We
 * then visit each cell, breaking down the wall between this cell and the neighbor
 * as we go.
 *
 * An important detail here: there are two separate coordinate systems. There's the
 * coordinates into the actual maze itself, where odd pairs represent cells and
 * non-odd pairs represent corridors, and the logical coordinates where (0, 0) is
 * the upper-left corner. The Grid<Cell> uses maze coordinates, and the Grid<State>
 * uses the logical coordinates.
 */
void dfsFrom(int row, int col, Grid<Cell>& maze, Grid<DFSState>& cellStates, Reporter reporter) {
    /* We are now the current cell. */
    cellStates[row][col] = DFSState::CURRENT;
    reporter(maze);

    /* Look at all neighbors in some order. These are technically not GridLocations but
     * rather deltas to add to our current location.
     */
    Vector<GridLocation> deltas = {
        { +1,  0 },
        { -1,  0 },
        {  0, +1 },
        {  0, -1 }
    };
    deltas.shuffle();

    /* Visit all neighbors. */
    for (GridLocation delta: deltas) {
        int nextRow = row + delta.row;
        int nextCol = col + delta.col;

        /* If this cell is in bounds and unvisited, visit it. */
        if (cellStates.inBounds(nextRow, nextCol) &&
            cellStates[nextRow][nextCol] == DFSState::UNEXPLORED) {
            /* Break down the wall between us and the new location. */
            int r0 = 2 * row + 1;
            int c0 = 2 * col + 1;
            int r1 = 2 * nextRow + 1;
            int c1 = 2 * nextCol + 1;
            maze[(r0 + r1) / 2][(c0 + c1) / 2] = Cell::EMPTY;

            /* We are now active but not current, since the new cell will be
             * the current one.
             */
            cellStates[row][col] = DFSState::ACTIVE;
            dfsFrom(nextRow, nextCol, maze, cellStates, reporter);

            /* We're now active again. */
            cellStates[row][col] = DFSState::CURRENT;
            reporter(maze);
        }
    }

    /* Now, we're done. */
    cellStates[row][col] = DFSState::VISITED;
}

/* An edge is represented by its endpoints in logical space. */
struct Edge {
    int r0, c0, r1, c1;
};

Map<GridLocation, GridLocation> initialParentsFor(int numRows, int numCols);
bool areLinked(const Map<GridLocation, GridLocation>& parents, int r0, int c0, int r1, int c1);
void link(Map<GridLocation, GridLocation>& parents, int r0, int c0, int r1, int c1);

PriorityQueue<Edge> randomizedEdgesFor(int numRows, int numCols);

void breakWall(Grid<Cell>& maze, int mazeRow0, int mazeCol0, int mazeRow1, int mazeCol1);


/* Kruskal's algorithm maze generator. See the DFS generator comments for information about
 * the size, shape, and layout of the maze.
 *
 * This implementation uses a simple union-find structure to keep track of which cells are
 * reachable from one another. Do a Google search for "disjoint-set forest" for more
 * information about this.
 */
Grid<Cell> makeKruskalMaze(int numRows, int numCols, Reporter reporter) {
    /* Get a blank maze. */
    auto maze = initialMazeOfSize(numRows, numCols);
    reporter(maze);

    /* Set up union-find structure; each cell is its own parent. */
    Map<GridLocation, GridLocation> parents = initialParentsFor(numRows, numCols);

    /* Permute edges. */
    PriorityQueue<Edge> edges = randomizedEdgesFor(numRows, numCols);

    /* Initially, everything is on its own. */
    int numClusters = numRows * numCols;
    while (numClusters > 1) {
        auto edge = edges.dequeue();

        /* If the endpoints aren't linked, link them. */
        if (!areLinked(parents, edge.r0, edge.c0, edge.r1, edge.c1)) {
            link(parents, edge.r0, edge.c0, edge.r1, edge.c1);
            breakWall(maze, 2 * edge.r0 + 1, 2 * edge.c0 + 1, 2 * edge.r1 + 1, 2 * edge.c1 + 1);
            numClusters--;
            reporter(maze);
        }
    }

    return maze;
}

/* Initially, all cells are their own parents. */
Map<GridLocation, GridLocation> initialParentsFor(int numRows, int numCols) {
    Map<GridLocation, GridLocation> result;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            result[GridLocation{row, col}] = { row, col };
        }
    }
    return result;
}

/* "Find" operation for union/find. */
GridLocation find(const Map<GridLocation, GridLocation>& parents, const GridLocation& loc) {
    GridLocation result = loc;
    while (parents[result] != result) result = parents[result];
    return result;
}

/* Are two cells linked? Check if their representatives are. */
bool areLinked(const Map<GridLocation, GridLocation>& parents, int r0, int c0, int r1, int c1) {
    return find(parents, { r0, c0 }) == find(parents, { r1, c1 });
}

/* Links two cells together by making the first's rep equal the second's. */
void link(Map<GridLocation, GridLocation>& parents, int r0, int c0, int r1, int c1) {
    auto firstRep  = find(parents, { r0, c0 });
    auto secondRep = find(parents, { r1, c1 });

    parents[firstRep] = secondRep;
}

/* Returns all the possible edges in a grid maze. */
Vector<Edge> allEdgesIn(int numRows, int numCols) {
    Vector<Edge> result;

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            /* If we can go horizontally from here, add that edge in. */
            if (col + 1 < numCols) {
                result.add({ row, col, row, col + 1 });
            }
            /* Same for vertical. */
            if (row + 1 < numRows) {
                result.add({ row, col, row + 1, col });
            }
        }
    }

    return result;
}

PriorityQueue<Edge> randomizedEdgesFor(int numRows, int numCols) {
    PriorityQueue<Edge> edges;

    /* Give each edge a random priority. */
    for (auto edge: allEdgesIn(numRows, numCols)) {
        edges.enqueue(edge, randomReal(0, 1));
    }

    return edges;
}

/* Breaks down the wall between the two locations in maze space. */
void breakWall(Grid<Cell>& maze, int mazeRow0, int mazeCol0, int mazeRow1, int mazeCol1) {
    maze[(mazeRow0 + mazeRow1) / 2][(mazeCol0 + mazeCol1) / 2] = Cell::EMPTY;
}

class MazeGUI: public ProblemHandler {
public:
    MazeGUI(GWindow& window);

    void settingUp() override;

protected:
    void repaint() override;

private:
    Grid<Cell> maze;
};

const int kNumRows = 10;
const int kNumCols = 10;
const double kPauseTime = 200;

MazeGUI::MazeGUI(GWindow& window) : ProblemHandler(window) {
    // Nothing to do
}

void MazeGUI::settingUp() {
    auto reporter = [&](const Grid<Cell>& maze) {
        this->maze     = maze;

        GThread::runOnQtGuiThread([&] {
            repaint();
            window().repaint();
        });
        pause(kPauseTime);
    };

    makeKruskalMaze(kNumRows, kNumCols, reporter);
}

struct Geometry {
    double baseX, baseY, scale;
};

const char kBackgroundColor[] = "#c000ff";
const char kEmptyColor[]      = "#ffffff";
const char kWallColor[]       = "#000000";

Geometry geometryFor(GWindow& window, int numRows, int numCols) {
    double workspaceWidth  = window.getCanvasWidth();
    double workspaceHeight = window.getCanvasHeight();
    double aspectRatio     = double(numCols) / numRows;

    double effectiveRatio  = workspaceWidth / workspaceHeight;

    double width, height;

    /* Too wide; width is limiting factor. */
    if (effectiveRatio < aspectRatio) {
        width  = workspaceWidth;
        height = width / aspectRatio;
    } else {
        height = workspaceHeight;
        width  = height * aspectRatio;
    }

    return { (workspaceWidth  - width)  / 2,
             (workspaceHeight - height) / 2,
             width / numCols };
}

void MazeGUI::repaint() {
    auto g = geometryFor(window(), maze.numRows(), maze.numCols());

    clearDisplay(window(), kBackgroundColor);

    for (int row = 0; row < maze.numRows(); row++) {
        for (int col = 0; col < maze.numCols(); col++) {
            window().setColor(maze[row][col] == Cell::EMPTY? kEmptyColor : kWallColor);
            window().fillRect({ col * g.scale + g.baseX,
                                row * g.scale + g.baseY,
                                g.scale, g.scale });
        }
    }
}

GRAPHICS_HANDLER("DFS Maze Generator", GWindow& window) {
    return make_shared<MazeGUI>(window);
}
