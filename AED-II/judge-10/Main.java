import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {

    }
}

class Page {
    List<Integer> keys;
    Page father;
    List<Page> sons;

    public Page(Integer order) {
        keys = new ArrayList<>((order * 2) + 1);
        father = null;
        sons = null;
    }

    public Page(Integer order, List<Integer> keys, Page father) {
        this.keys = new ArrayList<>((order * 2) + 1) { { addAll(keys); } };
        this.father = father;
        sons = null;
    }

    public boolean isLeaf() {
        return sons == null;
    }
}

class BTree {
    Page root;
    Integer order;

    public BTree(Integer order) {
        this.root = new Page(order);
        this.order = order;
    }

    public Page search(Page page, Integer searchedKey) {
        if (page == null) {
            return null;
        }

        List<Integer> keys = page.keys;
        int i = 0;

        for (; i < keys.size(); i++) {
            Integer comparisonKey = keys.get(i);

            if (searchedKey < comparisonKey) {
                break;
            }

            if (searchedKey.equals(comparisonKey)) {
                return page;
            }
        }

        return search(page.sons.get(i), searchedKey);
    }

    public void insert(Page page, Integer keyToInsert) {
        if (page.isLeaf()) {

        }
    }

    private void insertLeaf(Page page, Integer keyToInsert) {
        if (page.sons == null) {

        }
    }
}
