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
    private Integer balance;

    public Node(Integer key) {
        this.key = key;
        this.leftNode = null;
        this.rigthNode = null;
        this.balance = 0;
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

    public Integer getBalance() {
        return balance;
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

    public void setBalance(Integer balance) {
        this.balance = balance;
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
        final Height height = new Height();

        keys.forEach( key -> {
            final Node newNode = addNode(key, firstNode, height);
            setFirstNode(newNode);
        });
    }

    private Node addNode(Integer key, Node referenceNode, Height height) {
        if (referenceNode == null) {
            height.setIncreaseHeight(true);
            return new Node(key);
        }

        final Integer referenceKey = referenceNode.getKey();

        if (key <= referenceKey) {
            referenceNode.setLeftNode(addNode(key, referenceNode.getLeftNode(), height));

            if (height.getIncreaseHeight()) {
                switch (referenceNode.getBalance()) {
                    case 1 -> {
                        referenceNode.setBalance(0);
                        height.setIncreaseHeight(false);
                    }
                    case 0 -> {
                        referenceNode.setBalance(-1);
                        height.setIncreaseHeight(true);
                    }
                    case -1 -> {
                        final Integer leftBalance = referenceNode.getLeftNode().getBalance();
                        if (leftBalance == -1) {
                            referenceNode = rightRotate(referenceNode);
                            final Node rightNode = referenceNode.getRigthNode();
                            rightNode.setBalance(0);
                        } else {
                            referenceNode.setLeftNode(leftRotate(referenceNode.getLeftNode()));
                            referenceNode = rightRotate(referenceNode);

                            final Integer referenceBalance = referenceNode.getBalance();

                            if (referenceBalance == 0) {
                                referenceNode.getLeftNode().setBalance(0);
                                referenceNode.getRigthNode().setBalance(0);
                            } else if (referenceBalance == -1) {
                                referenceNode.getLeftNode().setBalance(0);
                                referenceNode.getRigthNode().setBalance(1);
                            } else {
                                referenceNode.getLeftNode().setBalance(-1);
                                referenceNode.getRigthNode().setBalance(0);
                            }
                        }
                        referenceNode.setBalance(0);
                        height.setIncreaseHeight(false);
                    }
                }
            }
        } else {
            referenceNode.setRightNode(addNode(key, referenceNode.getRigthNode(), height));

            if (height.getIncreaseHeight()) {
                switch (referenceNode.getBalance()) {
                    case -1 -> {
                        referenceNode.setBalance(0);
                        height.setIncreaseHeight(false);
                    }
                    case 0 -> {
                        referenceNode.setBalance(1);
                        height.setIncreaseHeight(true);
                    }
                    case 1 -> {
                        final Integer rightBalance = referenceNode.getRigthNode().getBalance();
                        if (rightBalance == 1) {
                            referenceNode = leftRotate(referenceNode);
                            final Node leftNode = referenceNode.getLeftNode();
                            leftNode.setBalance(0);
                        } else {
                            referenceNode.setRightNode(rightRotate(referenceNode.getRigthNode()));
                            referenceNode = leftRotate(referenceNode);

                            final Integer referenceBalance = referenceNode.getBalance();

                            if (referenceBalance == 0) {
                                referenceNode.getLeftNode().setBalance(0);
                                referenceNode.getRigthNode().setBalance(0);
                            } else if (referenceBalance == 1) {
                                referenceNode.getRigthNode().setBalance(0);
                                referenceNode.getLeftNode().setBalance(-1);
                            } else {
                                referenceNode.getRigthNode().setBalance(1);
                                referenceNode.getLeftNode().setBalance(0);
                            }

                            referenceNode.setBalance(0);
                            height.setIncreaseHeight(false);
                        }
                    }
                }
            }
        }

        return referenceNode;
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

class Height {
    private Boolean increaseHeight;

    public Height() {
        this.increaseHeight = false;
    }

    public Boolean getIncreaseHeight() {
        return increaseHeight;
    }

    public void setIncreaseHeight(Boolean increaseHeight) {
        this.increaseHeight = increaseHeight;
    }
}
