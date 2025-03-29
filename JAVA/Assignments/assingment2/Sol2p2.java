class Prime {
  int currentPrime = 2;
  boolean toPrint = true;

  boolean isPrime(int num) {
    for (int i = 2; i * i <= num; i++) {
      if (num % i == 0) {
        return false;
      }
    }
    return num > 1;
  }

  void generatePrime() {
    try {
      while (true) {
        Thread.sleep(1000);
        while (!toPrint) {
          while (!isPrime(++currentPrime))
            ;
          toPrint = true;
        }
      }
    } catch (Exception err) {
      System.out.println(err);
    }
  }

  void printPrime() {
    try {
      while (true) {
        Thread.sleep(1000);
        while (toPrint) {
          System.out.println("currentPrime -> " + currentPrime);
          toPrint = false;
        }
      }
    } catch (Exception err) {
      System.out.println(err);
    }
  }
}

public class Sol2p2 {

  public static void main(String[] args) {
    Prime p = new Prime();
    Thread t1 = new Thread(() -> {
      p.generatePrime();
    });
    Thread t2 = new Thread(() -> {
      p.printPrime();
    });
    t1.start();
    t2.start();
  }
}
