import java.util.Scanner;

class OddSeqGenerator extends Thread {
  int boundary = 0;
  int sum = 0;

  OddSeqGenerator(int n) {
    this.boundary = n;
  }

  void generateSeq() {
    for (int i = 1; i <= boundary; i += 2)
      sum += i;
  }

  int getSum() {
    return this.sum;
  }

  public void run() {
    generateSeq();
  }
}

class EvenSeqGenerator extends Thread {
  int boundary = 0;
  int sum = 0;

  EvenSeqGenerator(int n) {
    this.boundary = n;
  }

  void generateSeq() {
    for (int i = 2; i <= boundary; i += 2)
      sum += i;
  }

  int getSum() {
    return this.sum;
  }

  public void run() {
    generateSeq();
  }
}

/**
 * Sol5
 */
public class Sol5 {

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter the limit : ");
    int n = scanner.nextInt();
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
    } finally {
      scanner.close();
    }
  }
}
