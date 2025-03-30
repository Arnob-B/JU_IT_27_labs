import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import org.w3c.dom.events.Event;

class SharedPrinter {
  int current;
  SharedPrinter(){
    this.current = 1;
  }
  synchronized void  printOdd(){
    try{
        Thread.sleep(500);
        if(current%2 == 0){
          wait();
        }
        System.out.print(current + ", ");
        current++;
        notify();
    }catch(Exception e){
      System.out.println(e);
    }
  }
  synchronized void  printEven(){
    try{
        Thread.sleep(500);
        if(current%2 != 0){
          wait();
        }
        System.out.print(current + ", ");
        current++;
        notify();
    }
    catch(Exception e){
      System.out.println(e);
    }
  }
  synchronized int getCurrentValue(){
    return current;
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
    while(printer.getCurrentValue() <= limit){
      printer.printOdd();
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
    while(printer.getCurrentValue() <= limit){
      printer.printEven();
    }
  }
}

public class Sol2 {
  public static void main(String[] args) {
    int limit = 8;
    SharedPrinter printer = new SharedPrinter();

    EvenThread evenThread = new EvenThread(limit, printer);
    OddThread oddThread = new OddThread(limit, printer);

    oddThread.start();
    evenThread.start();
    try{
      oddThread.join();
      evenThread.join();
    }
    catch(Exception e){
      System.out.println(e);
    }
  }
}
