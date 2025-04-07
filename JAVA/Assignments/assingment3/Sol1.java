class GenericSorter {

    public static <T extends Comparable<T>> void sortArray(T[] array) {
        int n = array.length;
        boolean swapped;

        // Bubble Sort
        for (int i = 0; i < n - 1; i++) {
            swapped = false;

            for (int j = 0; j < n - i - 1; j++) {
                if (array[j].compareTo(array[j + 1]) > 0) {
                    // Swap array[j] and array[j+1]
                    T temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;

                    swapped = true;
                }
            }

            // If no elements were swapped, the array is already sorted
            if (!swapped) break;
        }
    }
}
public class Sol1 {

  public static void main(String[] args) {
    // Integer
    Integer[] intArray = {5, 2, 8, 1, 3};
    GenericSorter.sortArray(intArray);
    for (Integer i : intArray) {
      System.out.print(i + " ");
    }
    System.out.println();

    // String
    String[] strArray = {"Banana", "Apple", "Mango", "Cherry"};
    GenericSorter.sortArray(strArray);
    for (String s : strArray) {
      System.out.print(s + " ");
    }
  }
}
