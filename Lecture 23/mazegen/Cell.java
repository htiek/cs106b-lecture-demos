package mazegen;

public class Cell
{
    private final int x;
    private final int y;

    public Cell(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public Cell getOffsetCell(int dx, int dy)
    {
        return new Cell(x + dx, y + dy);
    }

    public int getX()
    {
        return x;
    }

    public int getY()
    {
        return y;
    }

    @Override
    public boolean equals(Object obj)
    {
        if(obj == null)
            return false;
        if(getClass() != obj.getClass())
            return false;
        final Cell other = (Cell) obj;
        if(this.x != other.x)
            return false;
        if(this.y != other.y)
            return false;
        return true;
    }

    @Override
    public int hashCode()
    {
        int hash = 3;
        hash = 17 * hash + this.x;
        hash = 17 * hash + this.y;
        return hash;
    }
}
