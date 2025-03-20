/**
 * Sol1
 */
class Utils{
  public static void threadPropertyPrint(Thread t){
    System.out.println(t);
    System.out.println("Name: "+t.getName());
    System.out.println("Id: "+t.getId());
    System.out.println("priority: "+t.getPriority());
    System.out.println("State: "+t.getState());
  }
}
class ChildThread extends Thread{
  public void run(){
    System.out.println("\n\n---[child thread]---");
    System.out.println("inside child thread");
    Utils.threadPropertyPrint(this);
  }
}
public class Sol1 {
  public static void main(String[] args) {
    Thread mainThread = Thread.currentThread();
    System.out.println("---[current thread]---");
    System.out.println("inside main thread");
    Utils.threadPropertyPrint(mainThread);
    Thread childThread = new ChildThread();
    childThread.start();
  }
}
