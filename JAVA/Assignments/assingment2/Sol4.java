import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.Scanner;

class FileHandler {
  File file;
  int currentNumber = -1;
  long sum = 0;
  boolean toSum = false;

  FileHandler(String location) {
    file = new File(location);
    System.out.println("file found");
  }

  void findNum() {
    try {
      Scanner reader = new Scanner(file);
      while (true) {
        Thread.sleep(100);
        if (!toSum) {
          if (!reader.hasNextLine()) {
            reader.close();
            return;
          }
          String data = reader.nextLine();
          currentNumber = Integer.valueOf(data);
          System.out.println("retrieved -> " + currentNumber);
          toSum = true;
        }
      }
    } catch (Exception ecp) {
      System.out.println(ecp);
    }
  }

  void doSum() {
    try {
      while (true) {
        Thread.sleep(100);
        if (toSum) {
          sum += currentNumber;
          System.out.println("currentSum -> " + sum);
          toSum = false;
        }
      }
    } catch (Exception ecp) {
      System.out.println(ecp);
    }
  }
}

public class Sol4 {
  public static void main(String[] args) {
    FileHandler f = new FileHandler("test.txt");
    Thread t1 = new Thread(() -> {
      f.findNum();
    });
    Thread t2 = new Thread(() -> {
      f.doSum();
    });
    t1.start();
    t2.start();
  }
}
