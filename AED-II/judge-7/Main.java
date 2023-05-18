import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final List<Integer> keys = inputKeys();

        final AVLTree avlTree = new AVLTree(keys);

        avlTree.printHeights();
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static List<Integer> inputKeys() {
        final List<Integer> keys = new ArrayList<>();
        int key = scanner.nextInt();

        while (key > -1) {
            keys.add(key);
            key = scanner.nextInt();
        }
        return keys;
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

    public AVLTree(List<Integer> keys) {
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
            return leftRotate(node);
        }

        if (nodeBalance > 1 && leftBalance >= 0) {
            return rightRotate(node);
        }

        if (nodeBalance > 1) {
            return doubleRightRotate(node);
        }

        if (nodeBalance < -1) {
            return doubleLeftRotate(node);
        }

        return node;
    }

    private Node removeNode(Integer key, Node referenceNode) {
        if (referenceNode == null) {
            return null;
        }

        final int referenceKey = referenceNode.getKey();
        final Node leftNode = referenceNode.getLeftNode();
        final Node rightNode = referenceNode.getRigthNode();

        if (key == referenceKey) {
            if (leftNode == null && rightNode == null) {
                return null;
            }

            if (leftNode != null && rightNode != null) {
                Node auxiliary = referenceNode.getLeftNode();

                while (auxiliary.getRigthNode() != null) {
                    auxiliary = auxiliary.getRigthNode();
                }

                referenceNode.setKey(auxiliary.getKey());
                auxiliary.setKey(key);

                referenceNode.setLeftNode(removeNode(key, leftNode));
                return referenceNode;
            }

            return leftNode != null ? leftNode : rightNode;
        }

        if (key < referenceKey) {
            referenceNode.setLeftNode(removeNode(key, leftNode));
        } else {
            referenceNode.setRightNode(removeNode(key, rightNode));
        }

        referenceNode.setHeight();
        return balanceNode(referenceNode);
    }

    public void remove(Integer key) {
        final Node fistNodeRemoved = removeNode(key, firstNode);
        setFirstNode(fistNodeRemoved);
    }

    private void printNode(Node node) {
        if (node != null) {
            System.out.print(node.getKey() + "(" + Node.getHeight(node) + ") ");
            printNode(node.getLeftNode());
            printNode(node.getRigthNode());
        }
    }

    public void printTree() {
        printNode(firstNode);
        System.out.println();
    }

    public void printHeights() {
        final Integer firstNodeHeight = Node.getHeight(firstNode);
        final Integer leftHeight = Node.getHeight(firstNode.getLeftNode()) + 1;
        final Integer rightHeight = Node.getHeight(firstNode.getRigthNode()) + 1;

        System.out.print(firstNodeHeight + ", " + leftHeight + ", " + rightHeight);
    }
}
