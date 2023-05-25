public class Main {
    public static void main(String[] args) {

    }
}

class Node {
    public Integer key;
    public Node father, left, right;
    public boolean isRed;

    public Node(int key, boolean isRed) {
        this.key = key;
        this.isRed = isRed;
        this.father = this.left = this.right = RedBlackTree.nil;
    }

    public Node findNode(int key) {
        if (key < this.key && this.left != RedBlackTree.nil) {
            return this.left.findNode(key);
        }
        if (key > this.key && this.right != RedBlackTree.nil) {
            return this.right.findNode(key);
        }
        return this;
    }
}

class RedBlackTree {
    public Node root;
    public static Node nil = new Node(-1, false);

    public RedBlackTree() {
        this.root = RedBlackTree.nil;
    }

    private void leftRotate(Node x) {
        final Node y = x.right;
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

    private void rightRotate(Node x) {
        final Node y = x.left;
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
            this.root = new Node(n, false);
        } else {
            Node a = this.find(n);

            if (n < a.key) {
                a.left = new Node(n, true);
                a.left.father = a;
                fixProperties(a.left);
            } else if (n > a.key) {
                a.right = new Node(n, true);
                a.right.father = a;
                fixProperties(a.right);
            }
        }
    }

    private void fixProperties(Node z) {
        Node y;

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

    public Node find(int n) {
        return this.root.findNode(n);
    }

    private void print(Node node) {
        if (node != null && node != nil) {
            System.out.print(node.key + "(" + node.isRed + ") ");
            print(node.left);
            print(node.right);
        }
    }

    public void print() {
        print(root);
    }
}
