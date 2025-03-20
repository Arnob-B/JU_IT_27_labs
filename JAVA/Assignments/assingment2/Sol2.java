class PrintNumber{
  int num =0;
  int turn; // 0 -> even, 1 -> odd
  PrintNumber(){
    this.num =0;
    this.turn = 0;
  }
  void switchTurn(){
    //System.out.println(this.turn);
    if(this.turn == 1) this.turn = 0;
    else this.turn = 1;
    //System.out.println("switching -> "+turn);
  }
  void increment(){
    this.num++;
  }
  void print(){
    System.out.println(this.num);
  }
}
class EvenThread extends Thread{
  PrintNumber num;
  EvenThread(PrintNumber num){
    this.num = num;
    this.start();
  }
  public void run(){
    while(true){
      try{
      sleep(1000);
      if(num.turn == 0)
      {
        num.print();
        num.increment();
        num.switchTurn();
      }
      }catch(Exception e){
        System.out.println(e);
      }
    }
  }
}
class OddThread extends Thread{
  PrintNumber num;
  OddThread(PrintNumber num){
    this.num = num;
    this.start();
  }
  public void run(){
    while(true){
      try{
      sleep(1000);
      if(num.turn == 1)
      {
        num.print();
        num.increment();
        num.switchTurn();
      }
      }catch(Exception e){
        System.out.println(e);
      }
    }
  }
}
public class Sol2 {
  public static void main(String[] args) {
    PrintNumber num = new PrintNumber();
    Thread even = new EvenThread(num);
    Thread odd = new OddThread(num);
  }
}
