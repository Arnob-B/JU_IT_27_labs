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
        System.out.print(arr[i] + ", ");
      }
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
public class Sol6 {

  public static void main(String[] args) {
    int n = 20;
    int arr[] = { 1, 2, 3, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    int target = 20;

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
    }
  }
}
