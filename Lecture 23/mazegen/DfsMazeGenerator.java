package mazegen;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.Stack;

public class DfsMazeGenerator
{
    private final Random rand = new Random();

    private int width;
    private int height;
    private boolean backwardIsStep;
    private WallSet[][] grid;
    private Stack<Cell> history = new Stack<Cell>();

    private HashSet<Cell> seen = new HashSet<Cell>();

    protected DfsMazeGenerator(int width, int height, boolean backwardIsStep)
    {
        this.width = width;
        this.height = height;
        this.backwardIsStep = backwardIsStep;

        grid = new WallSet[height][width];
        for(WallSet[] row : grid)
            for(int i = 0; i < row.length; i++)
                row[i] = WallSet.All();
        Cell start = new Cell(0, 0);
        history.push(start);
        seen.add(start);
    }

    public int getWidth()
    {
        return width;
    }

    public int getHeight()
    {
        return height;
    }

    public Stack<Cell> getHistory()
    {
        return history;
    }

    public Set<Cell> getSeen()
    {
        return seen;
    }

    public Cell getCurrent()
    {
        return history.peek();
    }

    public WallSet getWalls(Cell c)
    {
        return grid[c.getY()][c.getX()];
    }

    protected void destroyWall(Cell c, Wall w)
    {
        grid[c.getY()][c.getX()].remove(w);
        grid[c.getY() + w.getDy()][c.getX() + w.getDx()].remove(w.opposite());
    }

    public void SimulateForward()
    {
            if(history.isEmpty())
                return;

            Cell current = history.peek();
            List<Wall> destructables = new ArrayList<Wall>();

            for(Wall w : Wall.values())
                if((current.getX() + w.getDx() >= 0)
                   && (current.getX() + w.getDx() < width)
                   && (current.getY() + w.getDy() >= 0)
                   && (current.getY() + w.getDy() < height)
                   && (!seen.contains(current.getOffsetCell(w.getDx(), w.getDy()))))
                    destructables.add(w);

            if(destructables.size() == 0)
            {
                history.pop();
                if(!backwardIsStep)
                    SimulateForward();
            }
            else
            {
                int r = rand.nextInt(destructables.size());
                Wall w = destructables.get(r);
                destroyWall(current, w);

                Cell newCell = current.getOffsetCell(w.getDx(), w.getDy());
                history.push(newCell);
                seen.add(newCell);
            }
    }

    public boolean SimulationDone()
    {
        return history.isEmpty();
    }

}
