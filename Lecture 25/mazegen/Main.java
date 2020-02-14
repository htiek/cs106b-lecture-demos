package mazegen;

import java.awt.*;
import java.awt.event.*;
import java.util.TimerTask;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.concurrent.Semaphore;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.WindowConstants;
import javax.swing.SwingUtilities;

public class Main
{
    public static void main(String[] args)
    {
        if (args.length != 3) {
             System.err.println("Usage: mazegen.Main width height delay");
             return;
        }

        boolean backwardIsStep = true;
        boolean drawActive = true;
        long millisecond_period = Long.parseLong(args[2]);

        final DfsMazeGenerator gen = new DfsMazeGenerator(Integer.parseInt(args[0]), Integer.parseInt(args[1]), backwardIsStep);

        final JFrame frame = new JFrame();
        final MazePanel panel = new MazePanel(gen, drawActive, 600, 600);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.add(panel);
        frame.pack();
        frame.addComponentListener(new ComponentListener() {
            public void componentResized(ComponentEvent e) {
                panel.recomputeSize();
            }
            public void componentHidden(ComponentEvent e) {}
            public void componentMoved(ComponentEvent e) {}
            public void componentShown(ComponentEvent e) {}
        });
        frame.setVisible(true);

        final Semaphore lock = new Semaphore(0);

        while (!gen.SimulationDone()) {
            gen.SimulateForward();
            panel.repaint();

	    SwingUtilities.invokeLater(new Runnable() {
                 public void run() {
                        lock.release();
                 }
            });

	    lock.acquireUninterruptibly();

            try {
                 Thread.sleep(millisecond_period);
            } catch (InterruptedException iex) {
                 System.exit(-1);
            }
         }
    }

}
