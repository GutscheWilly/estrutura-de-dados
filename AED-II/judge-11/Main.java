import java.util.ArrayList;
import java.util.List;

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
    }
}

class Node {
    public Integer value;
    public Node next;

    public Node(Integer value) {
        this.value = value;
        this.next = null;
    }

    public Node(Integer value, Node next) {
        this.value = value;
        this.next = next;
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
}
