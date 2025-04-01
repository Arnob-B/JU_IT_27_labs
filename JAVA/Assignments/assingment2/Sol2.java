import java.util.Scanner;

class SharedPrinter {
  boolean isOdd = true;
  synchronized void  printOdd(int current){
    try{
      while(!isOdd ){
        wait();
      }
      System.out.print(current + ", ");
      Thread.sleep(500);
      isOdd = false;
      notify();
    }catch(Exception e){
      System.out.println(e);
    }
  }
  synchronized void  printEven(int current){
    try{
        while(isOdd){
          wait();
        }
        System.out.print(current + ", ");
        Thread.sleep(500);
        isOdd = true;
        notify();
    }
    catch(Exception e){
      System.out.println(e);
    }
  }
}
class OddThread extends Thread {
  int limit;
  SharedPrinter printer;

  OddThread( int limit, SharedPrinter printer) {
    this.limit = limit;
    this.printer = printer;
  }

  public void run() {
    for(int i =1;i<=limit;i+=2){
      printer.printOdd(i);
    }
  }
}

class EvenThread extends Thread {
  int limit;
  SharedPrinter printer;

  EvenThread( int limit, SharedPrinter printer) {
    this.limit = limit;
    this.printer = printer;
  }


  public void run() {
    for(int i =2;i<=limit;i+=2){
      printer.printEven(i);
    }
  }
}

public class Sol2 {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter the limit : ");
    int limit = scanner.nextInt();
    SharedPrinter printer = new SharedPrinter();

    EvenThread evenThread = new EvenThread(limit, printer);
    OddThread oddThread = new OddThread(limit, printer);

    oddThread.start();
    evenThread.start();
    try{
      oddThread.join();
      evenThread.join();
      System.out.println();
    }
    catch(Exception e){
      System.out.println(e);
    }
    finally{
      scanner.close();
    }
  }
}
