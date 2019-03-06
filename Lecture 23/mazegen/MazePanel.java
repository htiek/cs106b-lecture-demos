package mazegen;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

import javax.swing.JPanel;

public class MazePanel extends JPanel
{
    private final DfsMazeGenerator gen;
    private float xLength;
    private float yLength;
    private boolean drawActive;

    public MazePanel(DfsMazeGenerator gen, boolean drawActive,
                     int screenWidth, int screenHeight)
    {
        setPreferredSize(new Dimension(screenWidth, screenHeight));
        setSize(screenWidth, screenHeight);

        this.gen = gen;
        this.drawActive = drawActive;

        recomputeSize();
    }

    @Override
    public void paintComponent(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        super.paintComponent(g2d);
        colorBackground(g2d);
        fillSeenCells(g2d);
        if(drawActive)
            fillActiveCells(g2d);
        drawWalls(g2d);
    }

    public void recomputeSize() {
        xLength = this.getWidth() * 1.0f / gen.getWidth();
        yLength = this.getHeight() * 1.0f / gen.getHeight();
    }

    private void colorBackground(Graphics2D g2d)
    {
        g2d.setColor(Color.GRAY);
        g2d.fillRect(0, 0, this.getWidth(), this.getHeight());
    }

    private void fillSeenCells(Graphics2D g2d)
    {
        g2d.setColor(new Color(125, 125, 255));

        for(Cell c : gen.getSeen())
        {
            float x0 = c.getX() * xLength;
            float y0 = c.getY() * yLength;

            fillRect(g2d, x0, y0, xLength, yLength);
        }
    }

    private void fillActiveCells(Graphics2D g2d)
    {
        for(Cell c : gen.getHistory())
        {
            float x0 = c.getX() * xLength;
            float y0 = c.getY() * yLength;

            g2d.setColor(Color.BLUE);
            fillRect(g2d, x0, y0, xLength, yLength);

            g2d.setColor(Color.BLACK);
            fillOval(g2d, x0 + xLength / 4, y0 + yLength / 4, xLength / 2, yLength / 2);
        }

        if(!gen.getHistory().isEmpty())
        {
            g2d.setColor(Color.WHITE);
            Cell current = gen.getCurrent();
            float x0 = current.getX() * xLength + 0.1f * xLength;
            float y0 = current.getY() * yLength + 0.1f * yLength;

            fillOval(g2d, x0, y0, 0.8f * xLength, 0.8f * yLength);
        }
    }

    private void drawWalls(Graphics2D g2d)
    {
        g2d.setColor(Color.BLACK);
        g2d.setStroke(new BasicStroke(2));
        for(int y = 0; y < gen.getHeight(); y++)
            for(int x = 0; x < gen.getWidth(); x++)
            {
                Cell c = new Cell(x, y);
                drawCellWalls(g2d, c, gen.getWalls(c));
            }
    }

    private void drawCellWalls(Graphics2D g2d, Cell c, WallSet ws)
    {
        float x0 = c.getX() * xLength;
        float y0 = c.getY() * yLength;

        for(Wall w : Wall.values())
            if(ws.contains(w) && (w == Wall.SOUTH || w == Wall.EAST))
            {
                int dx = (w.getDx() + 1) / 2;
                int dy = (w.getDy() + 1) / 2;
                float x = x0 + dx * xLength;
                float y = y0 + dy * yLength;
                float d2x = xLength * Math.abs(w.getDy());
                float d2y = yLength * Math.abs(w.getDx());
                drawLine(g2d, x, y, x + d2x, y + d2y);
            }
    }

    private void drawLine(Graphics2D g2d,
                          float x0, float y0,
                          float x1, float y1)
    {
        g2d.drawLine(Math.round(x0),
                     Math.round(y0),
                     Math.round(x1),
                     Math.round(y1));
    }

    private void fillRect(Graphics2D g2d,
                          float x0, float y0,
                          float w, float h)
    {
        g2d.fillRect(Math.round(x0),
                     Math.round(y0),
                     Math.round(w),
                     Math.round(h));
    }

    private void fillOval(Graphics2D g2d,
                          float x0, float y0,
                          float w, float h)
    {
        g2d.fillOval(Math.round(x0),
                     Math.round(y0),
                     Math.round(w),
                     Math.round(h));
    }

}
