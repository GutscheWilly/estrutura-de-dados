import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    public static void main(String[] args) {
        Graph graph = new Graph(8, 8);

        graph.add(0, 1);
        graph.add(0, 3);
        graph.add(1, 4);
        graph.add(1, 5);
        graph.add(4, 6);
        graph.add(6, 0);
        graph.add(5, 2);
        graph.add(2, 7);

        graph.print();

        System.out.println();
        graph.breadthFirstSearch(0);
    }
}

enum Color {
    WHITE,
    GREY,
    BLACK
}

class Node implements Comparable<Node> {
    public Integer value;
    public Node next;
    public Color color;

    public Node(Integer value) {
        this.value = value;
        this.next = null;
        this.color = Color.WHITE;
    }

    public Node(Integer value, Node next) {
        this.value = value;
        this.next = next;
        this.color = Color.WHITE;
    }

    public List<Node> getAllTargets() {
        List<Node> targets = new ArrayList<>();

        for (Node target = next; target != null; target = target.next) {
            targets.add(target);
        }

        return targets;
    }

    @Override
    public int compareTo(Node o) {
        return value - o.value;
    }
}

class Graph {
    public Integer vertices;
    public Integer edges;
    public final List<Node> nodes;

    public Graph(Integer vertices, Integer edges) {
        this.vertices = vertices;
        this.edges = edges;
        this.nodes = new ArrayList<>(vertices);
        initNodes();
    }

    private void initNodes() {
        for (int i = 0; i < vertices; i++) {
            nodes.add(i, new Node(i));
        }
    }

    public void add(Integer source, Integer target) {
        Node reference = nodes.get(source);

        while (reference.next != null && reference.next.value < target) {
            reference = reference.next;
        }

        reference.next = new Node(target, reference.next);
    }

    public void print() {
        nodes.forEach( node -> {
            for (Node reference = node; reference != null; reference = reference.next) {
                System.out.print(reference.value + " -> ");
            }

            System.out.println();
        });
    }

    public void breadthFirstSearch(Integer source) {
        Node start = nodes.get(source);
        start.color = Color.GREY;

        List<Node> queue = new ArrayList<>();
        queue.add(start);

        while (!queue.isEmpty()) {
            Node node = queue.remove(0);

            for (Node target : node.getAllTargets()) {
                Node targetNode = nodes.get(target.value);

                if (targetNode.color == Color.WHITE) {
                    targetNode.color = Color.GREY;
                    queue.add(targetNode);
                }
            }

            node.color = Color.BLACK;
            System.out.print(node.value + " ");
        }
    }
}
