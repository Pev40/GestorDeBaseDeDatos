import java.awt.Graphics;

public class BPTree {
    private int order;
    private BPTreeNode root;

    BPTree(int order) {
        this.order = order;
        this.root = new BPTreeNode(this.order);
    }

    public void insert(int val) {
        BPTreeNode node = this.root;

        while (!node.isLeaf()) {
            int ind = node.getValueIndxToInsert(val);
            node = node.getChildAt(ind);
        }
        node.addValue(val);

        while (node.overflow()) {
            BPTreeNode parent;
            if (node.getParent() == null) {
                parent = new BPTreeNode(this.order);
            } else {
                parent = node.getParent();
            }
            BPTreeNode nodeRigth = new BPTreeNode(this.order);

            nodeRigth.setLeaf(node.isLeaf());
            nodeRigth = node.split(nodeRigth);

            parent.setLeaf(false);
            parent.addValue(nodeRigth.getFirstValue());
            nodeRigth.removeFirstValue();
            parent.addChild(node);
            parent.addChild(nodeRigth);

            if (parent.getParent() == null) {
                this.root = parent;
            }

            if (parent.overflow()) {
                node = parent;
            } else {
                break;
            }
        }
    }

    public boolean search(int value) {
        BPTreeNode node = searchNode(value);
        return node.isValue(value);
    }

    private BPTreeNode searchNode(int value) {
        BPTreeNode node = this.root;

        while (!node.isLeaf()) {
            int indx = node.getValueIndxToInsert(value);
            if (indx != -1) {
                node = node.getChildAt(indx);
            } else {
                return null;
            }
        }

        return node;
    }

    public void delete(int value) {
        BPTreeNode node = searchNode(value);
        if (node.isValue(value)) {
            node.remove(value);
            BPTreeNode parent = node.getParent();
            int first = Integer.MIN_VALUE;

            while (parent != null) {

                if (!node.isLeaf() && (node.isEmpty() || node.getNumChilds() < 2)) {
                    int pnode = parent.bestReeplaceLR(node);
                    if (pnode == -1) {
                        int tmp = parent.fromLeftParent(node, value);
                        first = (first == Integer.MIN_VALUE) ? tmp : first;
                    } else if (pnode == 1) {
                        int tmp = parent.fromRigthParent(node, value);
                        first = (first == Integer.MIN_VALUE) ? tmp : first;
                    } else if (pnode == 0) {
                        parent.jointWithchild(node, value);
                    }

                }

                if (node.isEmpty()) {
                    if (node.isLeaf()) {
                        int reep = parent.bestReeplaceLR(node);
                        if (reep == -1) {
                            int tmp = parent.fromLeft(node, value);
                            first = (first == Integer.MIN_VALUE) ? tmp : first;
                        } else if (reep == 1) {
                            int tmp = parent.fromRigth(node, value);
                            first = (first == Integer.MIN_VALUE) ? tmp : first;
                        } else if (reep == 0) {
                            parent.reduceNode(node, value);
                            parent.collapseWithChilds();
                        }
                    }
                } else { // node.values > 0
                    if (node.isLeaf()) {
                        int tmp = node.getFirstValue();
                        first = (first == Integer.MIN_VALUE) ? tmp : first;
                    }
                    if (parent.isValue(value)) { // out
                        parent.replace(value, first);
                    }
                }
                node = parent;
                parent = node.getParent();
            }

            if (node.getNumValues() == 0 && parent == null) {
                this.root = node;
                node.setParent(null);
            }

        } else {
            System.out.println("Not found!");
        }
    }

    public void print() {
        printTree(this.root, "");
        System.out.println();
    }

    private void printTree(BPTreeNode node, String tab) {
        System.out.print(tab);
        node.printValues();
        int i = 0;
        BPTreeNode child = node.getChildAt(i);

        while (child != null) {
            i++;
            printTree(child, tab + "|");
            child = node.getChildAt(i);
        }
    }

    public void iterator() {
        System.out.print("Linked : ");
        BPTreeNode node = this.root;
        while (!node.isLeaf()) {
            node = node.getChildAt(0);
        }
        rangeList(node, null);
    }

    private void rangeList(BPTreeNode start, BPTreeNode end) {
        while (start != end) {
            System.out.print(start.toString() + " ");
            start = start.getNext();
        }
        System.out.println();
    }

    public void rangeSearch(int start, int end) {
        BPTreeNode a = searchNode(start);
        if (a == null) {
            System.out.println("Not found " + start);
        }
        BPTreeNode b = searchNode(end);
        if (b == null) {
            System.out.println("Not found " + end);
        }
        if (start < end) {
            rangeList(a, b);
        } else {
            rangeList(b, a);
        }
    }

    public void visualizationTree(Graphics g, int width) {
        //this.root.drawGraphicsTree(g, 10, 20, 0, 0, width);
        this.root.drawGraphicsTree2(g, 10, 20, 0, 0, width);
    }

    public String visualizationList() {
        String tmp = "";

        BPTreeNode node = this.root;
        while (!node.isLeaf()) {
            node = node.getChildAt(0);
        }

        while (node != null) {
            tmp += node.toString() + " ";
            node = node.getNext();
        }

        return tmp;
    }
}
