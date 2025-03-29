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
      binarySearch(mid + 1, e, i);
    } else if (array[mid] < target) {
      binarySearch(s, mid - 1, i);
    } else {
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
    int n = 100;
    OddSeqGenerator oddThread = new OddSeqGenerator(n);
    EvenSeqGenerator evenThread = new EvenSeqGenerator(n);
    oddThread.start();
    evenThread.start();
    try {
      oddThread.join();
      System.out.println("odd sequence generated");
      evenThread.join();
      System.out.println("even sequence generated");
      int sum = oddThread.getSum() + evenThread.getSum();
      System.out.println("final sum " + sum);
    } catch (Exception err) {
      System.out.println(err);
    }
  }
}
