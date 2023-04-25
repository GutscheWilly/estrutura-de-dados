import java.util.*;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        try {
            final int wordsQuantity = scanner.nextInt();
            final int keysQuantity = scanner.nextInt();
            scanner.nextLine();

            final Map<Character, Integer> characterKeys = createCharacterKeys(keysQuantity);
            final List<String> shuffledWords = inputWords(wordsQuantity);

            validateCharacterKeys(shuffledWords, characterKeys);

            final List<String> sortedWords = new HeapSort(shuffledWords, characterKeys).heapSort();

            printWords(sortedWords);
        }
        catch (KeyNotExistsException keyNotExistsException) {
            System.out.print(keyNotExistsException.getMessage());
        }
    }

    private static List<String> inputWords(int quantity) {
        final String shuffledWords = scanner.nextLine();
        final String[] splitShuffledWords = shuffledWords.split(" ");
        return new ArrayList<>(Arrays.asList(splitShuffledWords));
    }

    private static Map<Character, Integer> createCharacterKeys(int quantity) {
        final String allCharacters = scanner.nextLine();
        final Map<Character, Integer> characterKeys = new HashMap<>();

        for (int i = 0; i < quantity; i++) {
            final char character = allCharacters.charAt(i);
            characterKeys.put(character, i);
        }
        return characterKeys;
    }

    private static void printWords(List<String> words) {
        System.out.print(words.get(0));

        for (int i = 1; i < words.size(); i++) {
            System.out.print(" " + words.get(i));
        }
    }

    private static void validateCharacterKeys(List<String> words, Map<Character, Integer> characterKeys) {
        words.forEach( word -> {
                for (char character : word.toCharArray()) {
                    if (!characterKeys.containsKey(character)) {
                        throw new KeyNotExistsException("A palavra " + word + " eh invalida");
                    }
                }
        });
    }
}

class KeyNotExistsException extends RuntimeException {
    public KeyNotExistsException(String message) {
        super(message);
    }
}

class HeapSort {
    private final List<String> wordsList;
    private final Map<Character, Integer> characterKeys;

    public HeapSort(List<String> wordsList, Map<Character, Integer> characterKeys) {
        this.wordsList = wordsList;
        this.characterKeys = characterKeys;
    }

    private boolean validateIndex(int index) {
        final int startIndex = 0;
        final int lastIndex = wordsList.size() - 1;
        return index >= startIndex && index <= lastIndex;
    }

    private void swap(int firstIndex, int secondIndex) {
        final String firstWord = wordsList.get(firstIndex);
        final String secondWord = wordsList.get(secondIndex);

        wordsList.set(firstIndex, secondWord);
        wordsList.set(secondIndex, firstWord);
    }

    private boolean compareWords(int firstWordIndex, int secondWordIndex) {
        final String firstWord = wordsList.get(firstWordIndex);
        final String secondWord = wordsList.get(secondWordIndex);

        final int firstLength = firstWord.length();
        final int secondLength = secondWord.length();

        final int smallerLength = Math.min(firstLength, secondLength);

        for (int i = 0; i < smallerLength; i++) {
            char firstLetter = firstWord.charAt(i);
            char secondLetter = secondWord.charAt(i);

            Integer firsLetterKey = characterKeys.get(firstLetter);
            Integer secondLetterKey = characterKeys.get(secondLetter);

            if (firsLetterKey > secondLetterKey) {
                return true;
            } else if (firsLetterKey < secondLetterKey) {
                return false;
            }
        }

        return firstLength > secondLength;
    }

    private void maxHeapify(int parentIndex) {
        final int leftIndex = (2 * parentIndex) + 1;
        final int rightIndex = 2 * (parentIndex + 1);

        int maxValueIndex = parentIndex;

        if (validateIndex(leftIndex) && compareWords(leftIndex, parentIndex)) {
            maxValueIndex = leftIndex;
        }

        if (validateIndex(rightIndex) && compareWords(rightIndex, maxValueIndex)) {
            maxValueIndex = rightIndex;
        }

        if (parentIndex != maxValueIndex) {
            swap(parentIndex, maxValueIndex);
            maxHeapify(maxValueIndex);
        }
    }

    private int lastParentIndex() {
        final int sizeList = wordsList.size();
        final int middleIndex = sizeList / 2;

        if (sizeList % 2 == 0) {
            return middleIndex;
        }
        return middleIndex - 1;
    }

    private void buildMaxHeap() {
        final int firstParentIndex = 0;
        final int lastParentIndex = lastParentIndex();

        for (int i = lastParentIndex; i >= firstParentIndex; i--) {
            maxHeapify(i);
        }
    }

    private String heapExtractMax() {
        final int maxParentIndex = 0;
        final String maxWord = wordsList.get(maxParentIndex);

        final int lastIndex = wordsList.size() - 1;
        final String lastWord = wordsList.get(lastIndex);

        wordsList.set(maxParentIndex, lastWord);
        wordsList.remove(lastIndex);

        maxHeapify(maxParentIndex);

        return maxWord;
    }

    public List<String> heapSort() {
        buildMaxHeap();

        final List<String> sortedWordsList = new ArrayList<>();
        final int firstIndex = 0;

        for (int extractIndex = wordsList.size() - 1; extractIndex >= 0; extractIndex--) {
            final String extractedWord = heapExtractMax();
            sortedWordsList.add(firstIndex, extractedWord);
        }
        return sortedWordsList;
    }
}
