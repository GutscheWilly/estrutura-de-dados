import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final int size = scanner.nextInt();
        final List<Integer> values = inputValues();
        final Hash hash = createHash(values, size);
        final int valueToBeRemoved = scanner.nextInt();

        hash.remove(valueToBeRemoved);
        hash.print();
    }

    private static final Scanner scanner = new Scanner(System.in);

    private static List<Integer> inputValues() {
        final List<Integer> values = new ArrayList<>();
        int value = scanner.nextInt();

        while (value > -1) {
            values.add(value);
            value = scanner.nextInt();
        }
        return values;
    }

    private static Hash createHash(List<Integer> values, int size) {
        final Hash hash= new Hash(size);
        values.forEach(hash::add);
        return hash;
    }
}

class Hash {
    private final List<Integer> keys;
    private final int size;

    private final int emptyValue;
    private final int removedValue;

    public Hash(int size) {
        this.keys = new ArrayList<>(size);
        this.size = size;
        this.emptyValue = -1;
        this.removedValue = -2;
        initKeys();
    }

    private void initKeys() {
        for (int i = 0; i < this.size; i++) {
            keys.add(emptyValue);
        }
    }

    private int hashFunction(int value) {
        return value % this.size;
    }

    private int hashFunction(int value, int size) {
        return value % size;
    }

    private int doubleHashFunction(int value, int collision) {
        final int h1 = hashFunction(value);
        final int h2 = 1 + hashFunction(value, this.size - 1);
        final int balance = h1 + (collision * h2);
        return hashFunction(balance);
    }

    private boolean isKeyNotEmpty(int key) {
        int value = keys.get(key);
        return value != emptyValue;
    }

    public void add(int value) {
        int key = hashFunction(value);

        for (int collision = 1; isKeyNotEmpty(key); collision++) {
            key = doubleHashFunction(value, collision);
        }
        keys.set(key, value);
    }

    public boolean contains(int value) {
        int key = hashFunction(value);

        for (int collision = 1; isKeyNotEmpty(key); collision++) {
            final int currentValue = keys.get(key);

            if (currentValue == value) {
                return true;
            }

            key = doubleHashFunction(value, collision);
        }
        return false;
    }

    public void remove(int value) {
        if (!contains(value)) {
            System.out.println("Valor nao encontrado");
            return;
        }

        for (int i = 0; i < keys.size(); i++) {
            final int currentValue = keys.get(i);

            if (currentValue == value) {
                keys.set(i, removedValue);
            }
        }
    }

    public void print() {
        for (int key = 0; key < this.size - 1; key++) {
            handlePrint(keys.get(key));
            System.out.print(" ");
        }
        handlePrint(keys.get(this.size - 1));
    }

    private void handlePrint(int value) {
        if (value == emptyValue) {
            System.out.print("\\");
            return;
        }

        if (value == removedValue) {
            System.out.print("D");
            return;
        }

        System.out.print(value);
    }
}
