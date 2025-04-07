/**
 * Deadlock
 */
class Deadlocker extends Thread {
  Thread dependecy;

  void setDependency(Thread dependecy) {
    this.dependecy = dependecy;
  }

  public void run() {
    System.out.println("wating for other thread in Deadlocker class");
    try {
      this.dependecy.join();
      System.out.println("other thread is dead");
    } catch (Exception e) {
      System.out.println(e);
    }
  }

}

public class Deadlock {
  public static void main(String[] args) {
    Deadlocker d1 = new Deadlocker();
    Deadlocker d2 = new Deadlocker();
    d1.setDependency(d2);
    d2.setDependency(d1);
    d1.start();
    d2.start();
  }
}
