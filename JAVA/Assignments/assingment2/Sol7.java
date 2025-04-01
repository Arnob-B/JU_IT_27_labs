import java.util.Scanner;

class Result {
  int arr[];
  int curIndex = -1;

  Result(int n) {
    arr = new int[n];
  }

  synchronized void push(int num) {
    curIndex++;
    arr[curIndex] = num;
  }

  void Print() {
    if (curIndex == -1) {
      System.out.println("element not found");
    } else {
      System.out.println("element found at index ");
      for (int i = 0; i <= curIndex; i++) {
        System.out.print(arr[i] + ((i != curIndex) ? ", " : ""));
      }
      System.out.println();
    }
  }
}

class BinaryThread extends Thread {
  int start, end, target;
  int array[];
  Result result;

  BinaryThread(int s, int e, int arr[], int target, Result result) {
    this.start = s;
    this.end = e;
    this.array = arr;
    this.target = target;
    this.result = result;
  }

  void binarySearch(int s, int e, int i) {
    if (s > e) {
      return;
    }
    int mid = (s + e) / 2;
    if (array[mid] > target) {
      binarySearch(s, mid - 1, i);
    } else if (array[mid] < target) {
      binarySearch(mid + 1, e, i);
    } else {
      System.out.println("found element by thread " + this.getId() + " at index " + mid);
      this.result.push(mid);
      return;
    }
  }

  public void run() {
    binarySearch(start, end, 0);
  }
}

/**
 * Sol5
 */
public class Sol7 {

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int n = 1;
    while (n % 10 != 0) {
      System.out.print("Enter the limit (multiple of 10) : ");
      n = scanner.nextInt();
    }
    int arr[] = new int[n];
    System.out.print("enter the array of " + n + " elements : ");
    for (int i = 0; i < n; i++) {
      arr[i] = scanner.nextInt();
    }
    System.out.print("enter the target : ");

    int target = scanner.nextInt();

    int noOfThreads = n / 10;
    Result result = new Result(n);
    BinaryThread threadPool[] = new BinaryThread[noOfThreads];

    for (int i = 0; i < noOfThreads; i++) {
      threadPool[i] = new BinaryThread(i * 10, (i + 1) * 10 - 1, arr, target, result);
      threadPool[i].start();
    }

    try {
      for (int i = 0; i < noOfThreads; i++) {
        threadPool[i].join();
      }
      result.Print();
    } catch (Exception err) {
      System.out.println(err);
    } finally {
      scanner.close();
    }
  }
}
