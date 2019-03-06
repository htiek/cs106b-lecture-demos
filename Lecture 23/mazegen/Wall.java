package mazegen;

public enum Wall implements Barrier
{
    NORTH(1, 0, -1), EAST(2, 1, 0), WEST(4, -1, 0), SOUTH(8, 0, 1);
    private int val, dx, dy;

    private Wall(int val, int dx, int dy)
    {
        this.val = val;
        this.dx = dx;
        this.dy = dy;
    }

    public int getVal()
    {
        return val;
    }

    public int getDx()
    {
        return dx;
    }

    public void setDx(int dx)
    {
        this.dx = dx;
    }

    public int getDy()
    {
        return dy;
    }

    public void setDy(int dy)
    {
        this.dy = dy;
    }

    public Wall opposite()
    {
        switch(this)
        {
            case NORTH:
                return SOUTH;
            case SOUTH:
                return NORTH;
            case EAST:
                return WEST;
            case WEST:
                return EAST;
            default:
                throw new RuntimeException();
        }
    }

}
