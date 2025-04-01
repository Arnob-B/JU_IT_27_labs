import java.util.Scanner;

class NumberHandler {
  private int denominator = 1; // Fixed spelling mistake from "denomenator"
  private double result = 0.0; // Changed to double to avoid integer division issues
  int limit = 0;

  NumberHandler(int limit) {
    this.limit = limit;
  }

  synchronized void generateDeno() {
    System.out.print("1 + ");
    try {
      while (true) {
        if (denominator == limit)
          return;
        if (denominator == 1)
          wait();
        denominator++; // Increment first
        System.out.print("1/" + denominator + "!" + ((denominator < (limit)) ? " + " : ""));
        Thread.sleep(1000);
        notify();
        wait();
      }
    } catch (Exception err) {
      System.out.println(err);
    }
  }

  long fact(int a) {
    if (a <= 1)
      return 1;
    return a * fact(a - 1);
  }

  synchronized void adder() {
    try {
      while (true) {
        result = result + (1.0 / fact(denominator));
        notify();
        if (denominator == limit) {
          System.out.println("\nresult = " + result);
          return;
        }
        wait();
      }
    } catch (Exception err) {
      System.out.println(err);
    }
  }
}

public class Sol3 {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter the limit : ");
    int limit = scanner.nextInt();

    NumberHandler n = new NumberHandler(limit);
    Thread t1 = new Thread(n::generateDeno);
    Thread t2 = new Thread(n::adder);

    t1.start();
    t2.start();
    try {
      t1.join();
      t2.join();
    } catch (Exception e) {
      System.out.println(e);
    } finally {
      scanner.close();
    }

  }
}
