import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final List<Integer> keys = inputKeys();

        final AVLTree avlTree = new AVLTree(keys);
        avlTree.printHeights();
        System.out.println();

        final RedBlackTree redBlackTree = new RedBlackTree(keys);
        RedBlackNode.printHeight(redBlackTree.root);
        System.out.println();

        System.out.println(redBlackTree.blackHeight());

        System.out.print(redBlackTree.colorChanges + ", " + redBlackTree.rotations + ", " + avlTree.rotations);
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
    public Boolean isRed;
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
    public Integer rotations;
    public Integer colorChanges;

    public RedBlackTree(List<Integer> keys) {
        this.root = RedBlackTree.nil;
        rotations = 0;
        colorChanges = 0;
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

        rotations++;
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

        rotations++;
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
                    colorChanges += 3;
                    z = z.father.father;
                } else {
                    if (z == z.father.right) {
                        z = z.father;
                        this.leftRotate(z);
                    }

                    z.father.isRed = false;
                    z.father.father.isRed = true;
                    colorChanges += 2;
                    this.rightRotate(z.father.father);
                }
            } else {
                y = z.father.father.left;

                if (y.isRed) {
                    y.isRed = z.father.isRed = false;
                    z.father.father.isRed = true;
                    colorChanges += 3;
                    z = z.father.father;
                }	else {
                    if (z == z.father.left) {
                        z = z.father;
                        this.rightRotate(z);
                    }

                    z.father.isRed = false;
                    z.father.father.isRed = true;
                    colorChanges += 2;
                    this.leftRotate(z.father.father);
                }
            }
        }
        this.root.isRed = false;
    }

    public RedBlackNode find(int n) {
        return this.root.findNode(n);
    }

    private void updateHeights() {
        root.updateHeight();
        root.left.updateHeight();
        root.right.updateHeight();
    }

    public Integer blackHeight() {
        RedBlackNode node = root;
        int blackHeight = 0;

        while (node != nil) {
            if (!node.isRed) {
                blackHeight++;
            }
            node = node.left;
        }
        return blackHeight;
    }
}

class Node {
    private Integer key;
    private Node leftNode;
    private Node rigthNode;
    private Integer height;

    public Node(Integer key) {
        this.key = key;
        this.leftNode = null;
        this.rigthNode = null;
        this.height = 0;
    }

    public Integer getKey() {
        return key;
    }

    public Node getLeftNode() {
        return leftNode;
    }

    public Node getRigthNode() {
        return rigthNode;
    }

    public static Integer getHeight(Node node) {
        if (node == null) {
            return -1;
        }
        return node.height;
    }

    public static Integer getBalance(Node node) {
        if (node == null) {
            return 0;
        }
        return getHeight(node.getLeftNode()) - getHeight(node.getRigthNode());
    }

    public void setKey(Integer key) {
        this.key = key;
    }

    public void setLeftNode(Node node) {
        leftNode = node;
    }

    public void setRightNode(Node node) {
        rigthNode = node;
    }

    public void setHeight() {
        final Integer leftHeight = getHeight(leftNode);
        final Integer rightHeight = getHeight(rigthNode);

        if (leftHeight >= rightHeight) {
            this.height = leftHeight + 1;
            return;
        }
        this.height = rightHeight + 1;
    }
}

class AVLTree {
    private Node firstNode;
    public Integer rotations;

    public AVLTree(List<Integer> keys) {
        rotations = 0;
        createAVLTree(keys);
    }

    private void setFirstNode(Node node) {
        this.firstNode = node;
    }

    private void createAVLTree(List<Integer> keys) {
        keys.forEach( this::add );
    }

    private Node addNode(Integer key, Node referenceNode) {
        if (referenceNode == null) {
            return new Node(key);
        }

        if (key < referenceNode.getKey()) {
            referenceNode.setLeftNode(addNode(key, referenceNode.getLeftNode()));
        } else if (key > referenceNode.getKey()) {
            referenceNode.setRightNode(addNode(key, referenceNode.getRigthNode()));
        }

        referenceNode.setHeight();
        return balanceNode(referenceNode);
    }

    public void add(Integer key) {
        final Node firstNodeAdded = addNode(key, firstNode);
        setFirstNode(firstNodeAdded);
    }

    private Node leftRotate(Node node) {
        final Node auxiliaryNode = node.getRigthNode();
        final Node auxiliaryLeft = auxiliaryNode.getLeftNode();

        node.setRightNode(auxiliaryLeft);
        auxiliaryNode.setLeftNode(node);

        node.setHeight();
        auxiliaryNode.setHeight();

        return auxiliaryNode;
    }

    private Node rightRotate(Node node) {
        final Node auxiliaryNode = node.getLeftNode();
        final Node auxiliaryRight = auxiliaryNode.getRigthNode();

        node.setLeftNode(auxiliaryRight);
        auxiliaryNode.setRightNode(node);

        node.setHeight();
        auxiliaryNode.setHeight();

        return auxiliaryNode;
    }

    private Node doubleLeftRotate(Node node) {
        node.setRightNode(rightRotate(node.getRigthNode()));
        return leftRotate(node);
    }

    private Node doubleRightRotate(Node node) {
        node.setLeftNode(leftRotate(node.getLeftNode()));
        return rightRotate(node);
    }

    private Node balanceNode(Node node) {
        final int nodeBalance = Node.getBalance(node);
        final int leftBalance = Node.getBalance(node.getLeftNode());
        final int rightBalance = Node.getBalance(node.getRigthNode());

        if (nodeBalance < -1 && rightBalance <= 0) {
            rotations++;
            return leftRotate(node);
        }

        if (nodeBalance > 1 && leftBalance >= 0) {
            rotations++;
            return rightRotate(node);
        }

        if (nodeBalance > 1) {
            rotations++;
            return doubleRightRotate(node);
        }

        if (nodeBalance < -1) {
            rotations++;
            return doubleLeftRotate(node);
        }

        return node;
    }

    public void printHeights() {
        printHeight(firstNode);
    }

    public void printHeight(Node node) {
        final Integer firstNodeHeight = Node.getHeight(node);
        final Integer leftHeight = Node.getHeight(node.getLeftNode()) + 1;
        final Integer rightHeight = Node.getHeight(node.getRigthNode()) + 1;

        System.out.print(firstNodeHeight + ", " + leftHeight + ", " + rightHeight);
    }
}
