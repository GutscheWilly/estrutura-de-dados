import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final List<Integer> keys = inputKeys();

        final AVLTree avlTree = new AVLTree(keys);
        avlTree.printHeights();

        final List<Integer> searchKeys = inputKeys();
        handleSearchKeys(searchKeys, avlTree);

        final Integer lastSearchKey = scanner.nextInt();
        System.out.println();
        avlTree.searchKey(lastSearchKey);
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

    private static void addOrRemoveKey(Integer key, AVLTree avlTree) {
        try {
            avlTree.remove(key);
        }
        catch (KeyNotExistsException keyNotExistsException) {
            avlTree.add(key);
        }
    }

    private static void handleSearchKeys(List<Integer> keys, AVLTree avlTree) {
        keys.forEach(key ->
                addOrRemoveKey(key, avlTree)
        );
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
            throw new KeyNotExistsException();
        }

        final int referenceKey = referenceNode.getKey();
        final Node leftNode = referenceNode.getLeftNode();
        final Node rightNode = referenceNode.getRigthNode();

        if (key == referenceKey) {
            if (leftNode == null && rightNode == null) {
                return null;
            }

            if (leftNode != null && rightNode != null) {
                Node auxiliary = referenceNode.getRigthNode();

                while (auxiliary.getLeftNode() != null) {
                    auxiliary = auxiliary.getLeftNode();
                }

                referenceNode.setKey(auxiliary.getKey());
                auxiliary.setKey(key);

                referenceNode.setRightNode(removeNode(key, rightNode));
                referenceNode.setHeight();
                return balanceNode(referenceNode);
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

    public void printHeights() {
        printHeight(firstNode);
    }

    public void printHeight(Node node) {
        final Integer firstNodeHeight = Node.getHeight(node);
        final Integer leftHeight = Node.getHeight(node.getLeftNode()) + 1;
        final Integer rightHeight = Node.getHeight(node.getRigthNode()) + 1;

        System.out.print(firstNodeHeight + ", " + leftHeight + ", " + rightHeight);
    }

    private Node searchNode(int key, Node referenceNode) {
        if (referenceNode == null) {
            return null;
        }

        final int referenceKey = referenceNode.getKey();

        if (key == referenceKey) {
            return referenceNode;
        }

        if (key < referenceKey) {
            return searchNode(key, referenceNode.getLeftNode());
        }
        return searchNode(key, referenceNode.getRigthNode());
    }

    public Node searchNode(Integer key) {
        return searchNode(key, firstNode);
    }

    public void searchKey(Integer key) {
        final Node foundNode = searchNode(key);

        if (foundNode == null) {
            System.out.print("Valor nao encontrado");
            return;
        }
        printHeight(foundNode);
    }
}

class KeyNotExistsException extends RuntimeException {
    public KeyNotExistsException() {
        super("Key not exists!");
    }
}
