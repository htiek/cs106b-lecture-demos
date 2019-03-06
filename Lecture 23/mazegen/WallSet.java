/******************************************************************************
 * File: WallSet.java
 * Author: Leonid Shamis (leonid.shamis@gmail.com)
 *
 */

package mazegen;

public class WallSet implements Barrier
{
    private int val;

    private WallSet(int val)
    {
        this.val = val;
    }

    public int getVal()
    {
        return val;
    }

    public static WallSet All()
    {
        return WallSet.join(Wall.NORTH,
                            Wall.EAST,
                            Wall.WEST,
                            Wall.SOUTH);
    }

    public static WallSet join(Barrier... walls)
    {
        int all = 0;
        for(Barrier b : walls)
            all |= b.getVal();
        return new WallSet(all);
    }

    public boolean contains(Wall w)
    {
        return (val & w.getVal()) != 0;
    }

    public void remove(Wall w)
    {
        val &= ~w.getVal();
    }

}
