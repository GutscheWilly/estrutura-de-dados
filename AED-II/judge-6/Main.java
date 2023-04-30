import java.util.*;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        final List<Integer> values = new ArrayList<>(Arrays.asList(0, 0, 0, 0, 0, 13, 0, 0, 1, 0));

        final List<Integer> sortedValues = new CountingSort(values).countingSort();

        System.out.println(sortedValues);
    }
}

class CountingSort {
    private final List<Integer> values;

    public CountingSort(List<Integer> values) {
        this.values = values;
    }

    public List<Integer> countingSort() {
        final List<Integer> auxiliaryList = createAuxiliaryList();
        final Integer[] sortedValues = new Integer[values.size()];

        for (int i = values.size() - 1; i >= 0; i--) {
            final int mainValue = values.get(i);
            final int auxiliaryValue = auxiliaryList.get(mainValue);

            sortedValues[auxiliaryValue - 1] = mainValue;
            decreaseIndexFrequency(auxiliaryList, mainValue);
        }
        return Arrays.asList(sortedValues);
    }

    private List<Integer> createAuxiliaryList() {
        final int size = getMaximumValue();
        final int defaultValue = 0;
        final List<Integer> auxiliaryList = new ArrayList<>();

        for (int i = 0; i < size; i++) {
            auxiliaryList.add(i, defaultValue);
        }

        increaseFrequencyForEachValue(auxiliaryList);
        sumPreviousValues(auxiliaryList);

        return auxiliaryList;
    }

    private Integer getMaximumValue() {
        Integer maximumValue = values.stream()
                .max(Comparator.naturalOrder())
                .orElse(-1);

        return maximumValue + 1;
    }

    private void increaseFrequencyForEachValue(List<Integer> auxiliaryList) {
        values.forEach( value -> {
                final int currentFrequency = auxiliaryList.get(value);
                auxiliaryList.set(value, currentFrequency + 1);
        });
    }

    private void sumPreviousValues(List<Integer> auxiliaryList) {
        for (int i = 1; i < auxiliaryList.size(); i++) {
            final int previousValue = auxiliaryList.get(i - 1);
            final int currentValue = auxiliaryList.get(i);

            final int sumValues = previousValue + currentValue;
            auxiliaryList.set(i, sumValues);
        }
    }

    private void decreaseIndexFrequency(List<Integer> auxiliaryList, int index) {
        final int currentFrequency = auxiliaryList.get(index);
        auxiliaryList.set(index, currentFrequency - 1);
    }
}
