import java.util.*;
import java.util.stream.Collectors;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        final int wordsQuantity = scanner.nextInt();
        scanner.nextLine();

        final Map<Character, Integer> characterPriorityKeys = inputCharacterPriorityKeys();

        final List<String> words = inputWords();
        printWordsInitial(words);

        final int maxLength = maxLength(words);
        matchWordsLength(words, maxLength);
        System.out.println(maxLength);

        final List<String> sortedWords = new RadixSort(words, characterPriorityKeys, maxLength).radixSort();
        printSortedWords(sortedWords);
    }

    private static Map<Character, Integer> inputCharacterPriorityKeys() {
        final String priorityKeys = scanner.nextLine();
        final Map<Character, Integer> characterPriorityKeys = new HashMap<>() { { put(' ', 0); } };

        int priority = 1;

        for (Character key : priorityKeys.toCharArray()) {
            characterPriorityKeys.put(key, priority);
            priority++;
        }
        return characterPriorityKeys;
    }

    private static List<String> inputWords() {
        final String words = scanner.nextLine();
        final String lowerCaseWords = words.toLowerCase();
        final String[] splitWords = lowerCaseWords.split(" ");
        return Arrays.asList(splitWords);
    }

    private static void matchWordsLength(List<String> words, int maxLength) {
        for (int i = 0; i < words.size(); i++) {
            final String word = words.get(i);
            final int wordLength = word.length();

            if (wordLength < maxLength) {
                final int gapLength = maxLength - wordLength;
                final String spaces = " ".repeat(gapLength);

                words.set(i, word.concat(spaces));
            }
        }
    }

    private static int maxLength(List<String> words) {
        return words.stream()
                .map(String::length)
                .max(Comparator.naturalOrder())
                .get();
    }

    private static void printWordsInitial(List<String> words) {
        words.forEach( word -> {
            System.out.println(word.concat("."));
        });
    }

    private static void printSortedWords(List<String> words) {
        System.out.print(words.get(0));

        for (int i = 1; i < words.size(); i++) {
            System.out.print("\n" + words.get(i));
        }
    }
}

class RadixSort {
    private List<String> words;
    private final Map<Character, Integer> characterPriorityKeys;
    private final Integer maxWordLength;

    public RadixSort(List<String> words, Map<Character, Integer> characterPriorityKeys, Integer maxWordLength) {
        this.words = words;
        this.characterPriorityKeys = characterPriorityKeys;
        this.maxWordLength = maxWordLength;
    }

    public List<String> radixSort() {
        for (int i = maxWordLength - 1; i >= 0; i--) {
            List<Integer> columnValues = convertCharacterColumnToValues(i);
            countingSort(columnValues);
        }
        return words;
    }

    private List<Integer> convertCharacterColumnToValues(int columnIndex) {
        return words.stream()
                .map(word -> word.charAt(columnIndex))
                .map(characterPriorityKeys::get)
                .collect(Collectors.toList());
    }

    private void countingSort(List<Integer> values) {
        final List<Integer> auxiliaryList = createAuxiliaryList(values);
        printAuxiliaryList(auxiliaryList);

        final String[] sortedWords = new String[values.size()];

        for (int i = values.size() - 1; i >= 0; i--) {
            final int mainValue = values.get(i);
            final int auxiliaryValue = auxiliaryList.get(mainValue);

            final String currentWord = words.get(i);
            sortedWords[auxiliaryValue - 1] = currentWord;

            decreaseIndexFrequency(auxiliaryList, mainValue);
        }

        words = Arrays.asList(sortedWords);
    }

    private List<Integer> createAuxiliaryList(List<Integer> values) {
        final int size = 27;
        final int defaultValue = 0;
        final List<Integer> auxiliaryList = new ArrayList<>();

        for (int i = 0; i < size; i++) {
            auxiliaryList.add(i, defaultValue);
        }

        increaseFrequencyForEachValue(values, auxiliaryList);
        sumPreviousValues(auxiliaryList);

        return auxiliaryList;
    }

    private void printAuxiliaryList(List<Integer> auxiliaryList) {
        System.out.print(auxiliaryList.get(0));

        for (int i = 1; i < auxiliaryList.size(); i++) {
            System.out.print(" " + auxiliaryList.get(i));
        }
        System.out.println();
    }

    private void increaseFrequencyForEachValue(List<Integer> values, List<Integer> auxiliaryList) {
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
