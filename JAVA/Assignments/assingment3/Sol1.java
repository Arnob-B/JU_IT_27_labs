class GenericSorter <T extends Comparable<T>>{
  T array[];
  GenericSorter(T [] array){
    this.array = array;
  }

  public void sort() {
    int n = array.length;

    // Bubble Sort
    for (int i = 0; i < n - 1; i++) {

      for (int j = 0; j < n - i - 1; j++) {
        if (array[j].compareTo(array[j + 1])> 0) {
          // array[j] > array[j + 1]
          T temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;

        }
      }

    }
  }
}
public class Sol1 {

  public static void main(String[] args) {
    // Integer
    Integer[] intArray = {5, 2, 8, 1, 3};
    GenericSorter<Integer> intSorter = new GenericSorter<>(intArray);
    intSorter.sort();
    for (Integer i : intArray) {
      System.out.print(i + " ");
    }
    System.out.println();

    // String
    String[] strArray = {"Banana", "Apple", "Mango", "Cherry"};
    GenericSorter<String> stringSorter = new GenericSorter<String>(strArray);
    stringSorter.sort();
    for (String s : strArray) {
      System.out.print(s + " ");
    }
  }
}
