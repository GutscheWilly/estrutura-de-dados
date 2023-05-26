import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final List<Integer> keys = inputKeys();
        RedBlackTree redBlackTree = new RedBlackTree(keys);
        redBlackTree.print();
        System.out.println();
        RedBlackNode.printHeight(redBlackTree.root);
    }

    private static final Scanner scanner = new Scanner(System.in);

    private static List<Integer> inputKeys() {
        final List<Integer> keys = new ArrayList<>();
        int key = scanner.nextInt();

        while (key > -1) {
            keys.add(key);
            key = scanner.nextInt();
        }
        return keys;
    }
}

class RedBlackNode {
    public Integer key;
    public RedBlackNode father, left, right;
    public boolean isRed;
    public Integer height;

    public RedBlackNode(int key, boolean isRed) {
        this.key = key;
        this.isRed = isRed;
        this.father = this.left = this.right = RedBlackTree.nil;
        this.height = 0;
    }

    public RedBlackNode findNode(int key) {
        if (key < this.key && this.left != RedBlackTree.nil) {
            return this.left.findNode(key);
        }

        if (key > this.key && this.right != RedBlackTree.nil) {
            return this.right.findNode(key);
        }
        return this;
    }

    private Integer calculateHeight(RedBlackNode node) {
        if (node == null) {
            return -1;
        }

        if (node.left == RedBlackTree.nil && node.right == RedBlackTree.nil) {
            return 0;
        }

        final int leftHeight = calculateHeight(node.left);
        final int rightHeight = calculateHeight(node.right);

        return Math.max(leftHeight, rightHeight) + 1;
    }

    public void updateHeight() {
        this.height = calculateHeight(this);
    }

    public static void printHeight(RedBlackNode node) {
        final Integer firstNodeHeight = node.height;
        final Integer leftHeight = node.left.height + 1;
        final Integer rightHeight = node.right.height + 1;

        System.out.print(firstNodeHeight + ", " + leftHeight + ", " + rightHeight);
    }
}

class RedBlackTree {
    public RedBlackNode root;
    public static RedBlackNode nil = new RedBlackNode(-1, false);

    public RedBlackTree(List<Integer> keys) {
        this.root = RedBlackTree.nil;
        createTree(keys);
        updateHeights();
    }

    private void createTree(List<Integer> keys) {
        keys.forEach(this::add);
    }

    private void leftRotate(RedBlackNode x) {
        final RedBlackNode y = x.right;
        x.right = y.left;

        if (y.left != RedBlackTree.nil) {
            y.left.father = x;
        }

        y.father = x.father;

        if (x.father == RedBlackTree.nil) {
            this.root = y;
        } else if (x == x.father.left) {
            x.father.left = y;
        } else {
            x.father.right = y;
        }

        y.left = x;
        x.father = y;
    }

    private void rightRotate(RedBlackNode x) {
        final RedBlackNode y = x.left;
        x.left = y.right;

        if (y.right != RedBlackTree.nil)
            y.right.father = x;

        y.father = x.father;

        if (x.father == RedBlackTree.nil) {
            this.root = y;
        } else if (x == x.father.left) {
            x.father.left = y;
        } else {
            x.father.right = y;
        }

        y.right = x;
        x.father = y;
    }

    public void add(int n) {
        if (this.root == RedBlackTree.nil) {
            this.root = new RedBlackNode(n, false);
        } else {
            RedBlackNode a = this.find(n);

            if (n < a.key) {
                a.left = new RedBlackNode(n, true);
                a.left.father = a;
                fixProperties(a.left);
            } else if (n > a.key) {
                a.right = new RedBlackNode(n, true);
                a.right.father = a;
                fixProperties(a.right);
            }
        }
    }

    private void fixProperties(RedBlackNode z) {
        RedBlackNode y;

        while (z.father.isRed) {
            if (z.father == z.father.father.left) {
                y = z.father.father.right;

                if (y.isRed) {
                    z.father.isRed = false;
                    y.isRed = false;
                    z.father.father.isRed = true;
                    z = z.father.father;
                } else {
                    if (z == z.father.right) {
                        z = z.father;
                        this.leftRotate(z);
                    }

                    z.father.isRed = false;
                    z.father.father.isRed = true;
                    this.rightRotate(z.father.father);
                }
            } else {
                y = z.father.father.left;

                if (y.isRed) {
                    y.isRed = z.father.isRed = false;
                    z.father.father.isRed = true;
                    z = z.father.father;
                }	else {
                    if (z == z.father.left) {
                        z = z.father;
                        this.rightRotate(z);
                    }

                    z.father.isRed = false;
                    z.father.father.isRed = true;
                    this.leftRotate(z.father.father);
                }
            }
        }
        this.root.isRed = false;
    }

    public RedBlackNode find(int n) {
        return this.root.findNode(n);
    }

    private void print(RedBlackNode node) {
        if (node != null && node != nil) {
            System.out.print(node.key + "(" + node.isRed + ") ");
            print(node.left);
            print(node.right);
        }
    }

    public void print() {
        print(root);
    }

    private void updateHeights() {
        root.updateHeight();
        root.left.updateHeight();
        root.right.updateHeight();
    }
}
