class FrequencyCounter<T> {

  T[] array;

  FrequencyCounter(T[] array) {
    this.array = array;

  }

  public void findFrequencies() {
    boolean[] visited = new boolean[array.length];

    for (int i = 0; i < array.length; i++) {
      if (visited[i])
        continue;

      int count = 1;

      for (int j = i + 1; j < array.length; j++) {
        if (array[i].equals(array[j])) {
          count++;
          visited[j] = true;
        }
      }

      System.out.println(array[i] + " -> " + count);
    }
  }
}

public class Sol2 {

  public static void main(String[] args) {
    // Integer
    Integer[] intArray = { 1, 2, 2, 3, 1, 4, 2 };
    FrequencyCounter<Integer> fc1 = new FrequencyCounter<Integer>(intArray);
    System.out.println("Integer Array Frequencies:");
    fc1.findFrequencies();

    // String
    String[] strArray = { "apple", "banana", "apple", "cherry", "banana", "apple" };
    FrequencyCounter<String> fc2 = new FrequencyCounter<String>(strArray);
    System.out.println("\nString Array Frequencies:");
    fc2.findFrequencies();
  }
}
