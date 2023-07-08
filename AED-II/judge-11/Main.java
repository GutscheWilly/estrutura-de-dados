import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Integer searchingNode = scanner.nextInt();

        Integer vertices = scanner.nextInt();
        Integer edges = scanner.nextInt();

        Graph graph = createGraph(vertices, edges);

        graph.breadthFirstSearch(searchingNode);
        System.out.println();
        graph.depthSearch(searchingNode);
    }

    private static final Scanner scanner = new Scanner(System.in);

    private static Graph createGraph(Integer vertices, Integer edges) {
        Graph graph = new Graph(vertices, edges);

        for (int i = 0; i < edges; i++) {
            Integer source = scanner.nextInt();
            Integer target = scanner.nextInt();
            graph.add(source, target);
        }

        return graph;
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
        setupColorsToWhite();

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

    private void setupColorsToWhite() {
        for (Node node : nodes) {
            node.color = Color.WHITE;
        }
    }

    public void depthSearch(Integer source) {
        setupColorsToWhite();
        checkVisit(nodes.get(source));
    }

    private void checkVisit(Node node) {
        node.color = Color.GREY;
        System.out.print(node.value + " ");

        for (Node target : node.getAllTargets()) {
            Node targetNode = nodes.get(target.value);

            if (targetNode.color == Color.WHITE) {
                checkVisit(targetNode);
            }
        }

        node.color = Color.BLACK;
    }
}
