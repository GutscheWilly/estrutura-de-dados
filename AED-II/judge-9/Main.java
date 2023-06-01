import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Hash hash = new Hash(7);
        hash.add(3);
        hash.add(4);
        hash.add(9);
        hash.add(8);
        hash.add(1);
        hash.add(2);
        hash.print();
    }
}

class Hash {
    private final List<Integer> keys;
    private final int size;
    private final int emptyValue;

    public Hash(int size) {
        this.keys = new ArrayList<>(size);
        this.size = size;
        this.emptyValue = -1;
        initKeys();
    }

    private void initKeys() {
        for (int i = 0; i < size; i++) {
            keys.add(emptyValue);
        }
    }

    private int hashFunction(int value) {
        return value % size;
    }

    private boolean isKeyNotEmpty(int key) {
        int value = keys.get(key);
        return value != emptyValue;
    }

    public void add(int value) {
        int key = hashFunction(value);

        while (isKeyNotEmpty(key)) {
            key = hashFunction(key + 1);
        }

        keys.set(key, value);
    }

    public boolean contains(int value) {
        int key = hashFunction(value);

        while (isKeyNotEmpty(key)) {
            int currentValue = keys.get(key);

            if (currentValue == value) {
                return true;
            }

            key = hashFunction(key + 1);
        }
        return false;
    }

    public void print() {
        for (int key = 0; key < size; key++) {
            System.out.println(key + " = " + keys.get(key));
        }
    }
}
