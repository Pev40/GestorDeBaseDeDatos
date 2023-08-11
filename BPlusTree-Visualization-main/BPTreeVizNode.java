import java.util.*;

public class BPTreeVizNode {
    private int order;
    private int defaultX = 15;
    private int defaultY = 20;

    private int defaultTextX = 1;
    private int defaultTextY = 12;

    public BPTreeVizNode(int order) {
        this.order = order;
    }

    // x, y, w, h, text x, text y
    private int[] getRectXy(int x, int y) {
        int[] tmp = new int[6];

        tmp[0] = x;
        tmp[1] = y;
        tmp[2] = this.defaultX;
        tmp[3] = this.defaultY;
        tmp[4] = x + this.defaultTextX;
        tmp[5] = y + this.defaultTextY;

        return tmp;
    }

    public ArrayList<int[]> getRectanglesXY(int x, int y) {
        ArrayList<int[]> cont = new ArrayList<int[]>();

        int lastx = x;
        for (int i = 0; i < this.order; i++) {
            int[] tmp = getRectXy(lastx, y);
            cont.add(tmp);

            lastx += this.defaultX + 1;
        }

        return cont;
    }

    public int sizeBox() {
        return this.order * this.defaultTextX;
    }
}
