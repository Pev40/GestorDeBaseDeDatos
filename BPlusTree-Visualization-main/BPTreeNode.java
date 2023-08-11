import java.awt.Color;
import java.awt.Graphics;
import java.util.*;

public class BPTreeNode {
    private boolean leaf;
    private int order;
    private int numValues;

    BPTreeNode parent;
    ArrayList<Integer> values;
    ArrayList<BPTreeNode> childs;
    BPTreeNode next;

    // visualization
    private int x, y;
    private int ident;

    BPTreeNode(int order) {
        this.order = order;
        this.leaf = true;
        this.numValues = 0;

        this.parent = null;
        this.values = new ArrayList<Integer>();
        this.childs = new ArrayList<BPTreeNode>();
    }

    public boolean isLeaf() {
        return this.leaf;
    }

    public void setLeaf(boolean lf) {
        this.leaf = lf;
    }

    public BPTreeNode getParent() {
        return this.parent;
    }

    public void setParent(BPTreeNode node) {
        this.parent = node;
    }

    public void setNext(BPTreeNode node) {
        this.next = node;
    }

    public BPTreeNode getNext() {
        return this.next;
    }

    public void addValue(int val) {
        if (this.numValues == 0) {
            this.values.add(val);
            this.numValues++;
        } else {
            int indx = getValueIndxToInsert(val);
            if (indx > -1) {
                addValueAt(indx, val);
            }
        }
    }

    public void addValueAt(int ind, int val) {
        this.values.add(ind, val);
        this.numValues++;
    }

    public void updateValueAt(int ind, int val) {
        this.values.set(ind, val);
    }

    public int getFirstValue() {
        if (this.numValues > 0) {
            return this.values.get(0);
        }
        return Integer.MIN_VALUE;
    }

    private int getLastValue() {
        if (this.numValues > 0) {
            return this.values.get(this.numValues - 1);
        }
        return Integer.MAX_VALUE;
    }

    public void removeFirstValue() {
        if (!this.leaf) {
            this.values.remove(0);
            this.numValues--;
        }
    }

    private void removeLastValue() {
        if (!this.leaf) {
            this.values.remove(this.numValues - 1);
            this.numValues--;
        }
    }

    public int getValueIndxToInsert(int val) {
        if (this.numValues > 0) {
            for (int i = 0; i < this.numValues; i++) {
                if (this.values.get(i) > val) {
                    return i;
                }
            }
        } else {
            return -1;
        }
        return this.numValues;
    }

    public boolean isValue(int val) {
        if (this.numValues > 0) {
            if (getValueIndex(val) > -1) {
                return true;
            }
        }
        return false;
    }

    public int getValueIndex(int val) {
        return this.values.indexOf(val);
    }

    private int getValueAt(int indx) {
        if (indx < this.numValues && indx > -1) {
            return this.values.get(indx);
        }
        return Integer.MAX_VALUE;
    }

    public boolean overflow() {
        if (this.numValues >= this.order) {
            return true;
        }
        return false;
    }

    public void addChild(BPTreeNode node) {
        if (!this.leaf) {
            if (this.childs.size() == 0) {
                this.childs.add(node);
                node.setParent(this);
            } else {
                if (this.childs.indexOf(node) == -1) {
                    int val = node.getFirstValue();
                    int indx = getChildIndxToInsert(val);
                    if (indx > -1) {
                        addChildAt(indx, node);
                        node.setParent(this);
                    }
                }
            }
        }
    }

    public void addChildAt(int ind, BPTreeNode node) {
        if (!this.leaf) {
            this.childs.add(ind, node);
        }
    }

    public BPTreeNode getChildAt(int indx) {
        if (!this.leaf) {
            if (indx < childs.size()) {
                return this.childs.get(indx);
            }
        }
        return null;
    }

    public int getChildIndxToInsert(int val) {
        int n = this.childs.size();
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (this.childs.get(i).getFirstValue() > val) {
                    return i;
                }
            }
        } else {
            return -1;
        }
        return n; // Extra element
    }

    public int getChildIndx(BPTreeNode child) {
        int n = this.childs.size();
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                if (this.childs.get(i) == child) {
                    return i;
                }
            }
        }
        return -1;
    }

    private void removeChildAt(int indx) {
        this.childs.remove(indx);
    }

    public int getNumValues() {
        return this.numValues;
    }

    public int getNumChilds() {
        return this.childs.size();
    }

    public BPTreeNode split(BPTreeNode node) {
        int med = this.order / 2;
        int Nvalues = this.values.size();

        for (int i = med; i < this.numValues; i++) {
            node.addValue(this.values.get(i));
        }
        for (int i = med; i < Nvalues; i++) {
            this.numValues--;
            this.values.remove(this.numValues);
        }

        if (!this.leaf) {
            med++;
            int n = this.childs.size();
            for (int i = med; i < n; i++) {
                node.addChild(this.childs.get(i));
            }
            int last = n - 1;
            for (int i = med; i < n; i++) {
                this.childs.remove(last);
                last--;
            }
        }

        if (this.leaf) {
            if (this.next != null) {
                node.setNext(this.next);
            }
            setNext(node);
        }

        return node;
    }

    public boolean isEmpty() {
        return (this.numValues == 0);
    }

    public void remove(int value) {
        int indx = getValueIndex(value);
        this.values.remove(indx);
        this.numValues--;
    }

    public void replace(int a, int b) {
        if (!this.leaf) {
            int indxA = getValueIndex(a);
            this.values.set(indxA, b);
        }
    }

    public int bestReeplaceLR(BPTreeNode node) {
        int indx = getChildIndx(node);
        if (indx > 0) {
            BPTreeNode left = this.childs.get(indx - 1);
            if (left.getNumValues() > 1) {
                return -1;
            }
        }
        if (indx < this.childs.size() - 1) {
            BPTreeNode rigth = this.childs.get(indx + 1);
            if (rigth.getNumValues() > 1) {
                return 1;
            }
        }

        return 0;
    }

    public int fromLeft(BPTreeNode node, int del) {
        int indx = this.childs.indexOf(node);
        BPTreeNode left = this.childs.get(indx - 1);

        int value = left.getLastValue();
        node.addValue(value);
        left.remove(value);

        indx = getValueIndex(del);
        if (indx > -1) {
            this.values.set(indx, value);
        }
        return value;
    }

    public int fromRigth(BPTreeNode node, int del) {
        int indx = this.childs.indexOf(node);
        BPTreeNode rigth = this.childs.get(indx + 1);

        int value = rigth.getFirstValue();
        node.addValue(value);
        rigth.remove(value);

        remove(value);
        addValue(rigth.getFirstValue());

        indx = getValueIndex(del);
        if (indx > -1) {
            this.values.set(indx, value);
        }
        return value;
    }

    public int fromRigthParent(BPTreeNode node, int val) {
        int reep = Integer.MIN_VALUE;
        int indx = this.childs.indexOf(node);
        BPTreeNode rigth = this.childs.get(indx + 1);
        reep = rigth.getFirstValue();

        if (node.getNumValues() == 1) {
            if (node.getFirstValue() != val) {
                reep = node.getFirstValue();
            }
            node.removeFirstValue();
        }

        node.addValue(this.values.get(indx));
        node.addChild(rigth.getChildAt(0));

        if (node.getFirstValue() == val) {
            BPTreeNode child2 = node.getChildAt(1);
            node.removeFirstValue();
            node.addValue(child2.getFirstValue());
        }

        int value = rigth.getFirstValue();
        this.values.set(indx, value);

        rigth.removeFirstValue();
        rigth.removeChildAt(0);

        return reep;
    }

    public int fromLeftParent(BPTreeNode node, int val) {
        int reep = Integer.MIN_VALUE;
        int indx = this.childs.indexOf(node);
        BPTreeNode left = this.childs.get(indx - 1);
        reep = left.getFirstValue();

        if (node.getNumValues() == 1) {
            if (node.getFirstValue() != val) {
                reep = node.getFirstValue();
            }
            node.removeFirstValue();
        }

        node.addValue(this.values.get(indx - 1));
        node.addChild(left.getChildAt(left.getNumChilds() - 1));

        if (node.getFirstValue() == val) {
            BPTreeNode child2 = node.getChildAt(1);
            node.removeFirstValue();
            node.addValue(child2.getFirstValue());
        }

        int value = left.getLastValue();
        this.values.set(indx - 1, value);

        left.removeLastValue();
        left.removeChildAt(left.getNumChilds() - 1);

        return reep;
    }

    public void reduceNode(BPTreeNode node, int val) {
        int indx = getChildIndx(node);
        if (indx > 0) {
            BPTreeNode left = this.childs.get(indx - 1);

            this.childs.remove(indx);
            if (this.numValues > 1) {
                remove(val);
                left.setNext(node.getNext());

            } else {
                removeFirstValue();
                left.setNext(node.getNext());
            }

        } else if (indx < this.childs.size() - 1) {
            BPTreeNode rigth = this.childs.get(indx + 1);

            if (this.numValues > 1) {
                int tmp = rigth.getFirstValue();
                rigth.removeFirstValue();
                node.addValue(tmp);

                remove(tmp);
                this.childs.remove(rigth);
                node.setNext(rigth.getNext());
            } else {
                this.childs.remove(indx);
            }
        }
    }

    void jointWithchild(BPTreeNode node, int value) {
        ArrayList<BPTreeNode> tmpnodes = new ArrayList<BPTreeNode>();
        ArrayList<Integer> tmpvalues = new ArrayList<Integer>();

        for (int i = 0; i < this.numValues; i++) {
            int tmp = this.values.get(i);
            if (tmp != value) {
                tmpvalues.add(tmp);
            }
        }

        for (int i = 0; i < this.childs.size(); i++) {
            BPTreeNode tmp = this.childs.get(i);
            for (int j = 0; j < tmp.getNumValues(); j++) {
                int cval = tmp.getValueAt(j);
                if (cval != value) {
                    tmpvalues.add(cval);
                }
            }
            for (int j = 0; j < tmp.getNumChilds(); j++) {
                tmpnodes.add(tmp.getChildAt(j));
            }
        }

        while (node.getNumValues() > 0) {
            node.removeFirstValue();
        }
        while (node.getNumChilds() > 0) {
            node.removeChildAt(0);
        }
        // to node
        for (int i = 0; i < tmpnodes.size(); i++) {
            node.addChild(tmpnodes.get(i));
        }
        for (int i = 0; i < tmpvalues.size(); i++) {
            node.addValue(tmpvalues.get(i));
        }
        // Delete parent data
        this.childs.clear();
        addChild(node);
        this.values.clear();
        this.numValues = 0;
    }

    void collapseWithChilds() {
        int nchild = this.getNumChilds();
        if (nchild < 3) {
            for (int i = 0; i < nchild; i++) {
                BPTreeNode node = this.childs.get(i);
                if (node.isLeaf() == false) {
                    return;
                }
            }
            if (nchild == 1) {
                BPTreeNode left = this.childs.get(0);
                int tmp = left.getFirstValue();
                if (this.values.size() > 0) {
                    if (left.getNumValues() == 1 && tmp != this.values.get(0)) {
                        this.addValue(tmp);
                    }
                } else {
                    this.addValue(tmp);
                }
                this.childs.clear();
                this.setLeaf(true);
            }
        }
    }

    public void setXYVisualization(int x, int y, int ident) {
        this.x = x;
        this.y = y;
        this.ident = ident;
    }

    public int[] getXyVisualization() {
        int[] tmp = new int[2];
        tmp[0] = this.x;
        tmp[1] = this.y;

        return tmp;
    }

    public String[] getValuesVizualization() {
        String[] tmp = new String[this.order];

        for (int i = 0; i < this.values.size(); i++) {
            tmp[i] = this.values.get(i) + "";
        }
        return tmp;
    }

    public void drawGraphicsTree2(Graphics g, int x, int y, int level, int start, int end) {
        if (this.parent == null) {
            setXYVisualization(x, y, -1);
            drawNodeAt(g, this);
        }

        if (this.isLeaf()) {
            return;
        }

        int block = (this.order + 1) * 15;
        block += 2;

        ArrayList<BPTreeNode> tobfs = new ArrayList<BPTreeNode>();
        ArrayList<Integer> lvl = new ArrayList<Integer>();
        for (int i = 0; i < this.childs.size(); i++) {
            tobfs.add(this.childs.get(i));
            lvl.add(1);
        }

        int currentlvl = 1, i = 0, k = 0;
        BPTreeNode lastparent = null;
        do {
            BPTreeNode node;
            int nodeLevel = lvl.get(0);

            if (tobfs.size() > 0) {
                node = tobfs.get(0);

                if (!node.isLeaf()) {
                    for (int j = 0; j < node.childs.size(); j++) {
                        tobfs.add(node.childs.get(j));
                        lvl.add(nodeLevel + 1);
                    }
                }

                tobfs.remove(0);
                lvl.remove(0);
            } else {
                break;
            }

            if (currentlvl < nodeLevel) {
                currentlvl = nodeLevel;
                start = 0;
                y = y + 40;
                i = 0;
            }

            int newX = start + block * i;
            int newY = y + 40;

            node.setXYVisualization(newX, newY, -1);

            int[] tmp = node.getParent().getXyVisualization();
            if(lastparent != node.getParent()) {
                lastparent = node.getParent();
                k = 0;
            }
            g.drawLine(tmp[0] + 15 * k++, y + 20, newX, newY);
            drawNodeAt(g, node);

            i++;

        } while (!tobfs.isEmpty());
    }

    private void drawNodeAt(Graphics g, BPTreeNode node) {
        BPTreeVizNode vnode = new BPTreeVizNode(this.order);
        int[] xy = node.getXyVisualization();
        ArrayList<int[]> cont = vnode.getRectanglesXY(xy[0], xy[1]);
        String[] svalues = node.getValuesVizualization();

        for (int i = 0; i < cont.size(); i++) {
            int[] tmp = cont.get(i);

            g.setColor(Color.LIGHT_GRAY);
            if (node.isLeaf()) {
                g.setColor(new Color(134, 178, 147));
            }
            g.fillRect(tmp[0], tmp[1], tmp[2], tmp[3]); // x, y , w, h

            g.setColor(Color.BLACK);
            if (svalues[i] != null) {
                g.drawString(svalues[i], tmp[4], tmp[5]);
            }
        }

    }

    public int getIdent() {
        return this.ident;
    }

    void printValues() {
        for (int i = 0; i < this.numValues; i++) {
            System.out.print(this.values.get(i) + " ");
        }
        System.out.println("");
    }

    public String toString() {
        String content = "";
        for (int i = 0; i < this.values.size(); i++) {
            content += (values.get(i) + " ");
        }

        return content;
    }
}
