class DuplicateFinder<T> {

  public void printDuplicates(T[] array) {
    boolean[] visited = new boolean[array.length];

    for (int i = 0; i < array.length; i++) {
      if (visited[i])
        continue;

      boolean isDuplicate = false;

      for (int j = i + 1; j < array.length; j++) {
        if (array[i].equals(array[j])) {
          visited[j] = true;
          isDuplicate = true;
        }
      }

      if (isDuplicate) {
        System.out.println("Duplicate: " + array[i]);
      }
    }
  }

}

public class Sol3 {

  public static void main(String[] args) {
    DuplicateFinder<Integer> intFinder = new DuplicateFinder<>();
    Integer[] intArray = { 1, 2, 3, 2, 4, 1, 5 };
    System.out.println("Integer Duplicates:");
    intFinder.printDuplicates(intArray);

    DuplicateFinder<String> strFinder = new DuplicateFinder<>();
    String[] strArray = { "apple", "banana", "apple", "cherry", "banana", "date" };
    System.out.println("\nString Duplicates:");
    strFinder.printDuplicates(strArray);
  }
}
