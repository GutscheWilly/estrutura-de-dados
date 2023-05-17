import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Integer> keys = Arrays.asList(15, 27, 49, 10, 8, 67, 59, 9, 13, 20, 14);
        AVLTree avlTree = new AVLTree(keys);
        avlTree.printTree();
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

    private static Integer getHeight(Node node) {
        if (node == null) {
            return -1;
        }
        return node.height;
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

    public static Integer getBalance(Node node) {
        if (node == null) {
            return 0;
        }
        return getHeight(node.getLeftNode()) - getHeight(node.getRigthNode());
    }
}

class AVLTree {
    private Node firstNode;

    public AVLTree(List<Integer> keys) {
        createAVLTree(keys);
    }

    private void setFirstNode(Node node) {
        firstNode = node;
    }

    private void createAVLTree(List<Integer> keys) {
        keys.forEach( key -> {
            final Node firstNodeAdded = addNode(key, firstNode);
            setFirstNode(firstNodeAdded);
        });
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

    private Node leftRotate(Node node) {
        final Node auxiliaryNode = node.getRigthNode();

        node.setRightNode(auxiliaryNode.getLeftNode());
        auxiliaryNode.setLeftNode(node);

        return auxiliaryNode;
    }

    private Node rightRotate(Node node) {
        final Node auxiliaryNode = node.getLeftNode();

        node.setLeftNode(auxiliaryNode.getRigthNode());
        auxiliaryNode.setRightNode(node);

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
        final Integer nodeBalance = Node.getBalance(node);
        final Integer leftBalance = Node.getBalance(node.getLeftNode());
        final Integer rightBalance = Node.getBalance(node.getRigthNode());

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

    private void printNode(Node node) {
        if (node != null) {
            printNode(node.getLeftNode());
            System.out.print(node.getKey() + " ");
            printNode(node.getRigthNode());
        }
    }

    public void printTree() {
        printNode(firstNode);
    }
}
