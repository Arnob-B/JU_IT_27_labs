import java.util.Scanner;

class Tollbooth {
  int totalCarPassed;
  int unpaidCars;
  int cash;
  float ticketCost;

  Tollbooth() {
    ticketCost = 0;
    totalCarPassed = 0;
    unpaidCars = 0;
    cash = 0;
  }

  public void setTicketCost(float ticketCost) {
    this.ticketCost = ticketCost;
  }

  void unpaid() {
    totalCarPassed++;
    unpaidCars++;
  }

  void paid() {
    totalCarPassed++;
    cash += ticketCost;
  }

  void showDetails() {
    System.out.println("---TollBooth Record---");
    System.out.println("Cost of ticket :-> " + ticketCost);
    System.out.println("Total cars passed :-> " + totalCarPassed);
    System.out.println("Unpaid cars passed :-> " + unpaidCars);
    System.out.println("Total cash collected  :-> " + cash);
  }
}

public class Sol15 {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    Tollbooth tb = new Tollbooth();
    tb.setTicketCost(50f);
    String c = "y";
    while (c.equals("y")) {
      System.out.println("Press one of the following");
      System.out.println("1. Car passed paying");
      System.out.println("2. Car passed without paying");
      System.out.println("3. show details");
      int choice = scan.nextInt();
      switch (choice) {
        case 1:
          tb.paid();
          break;
        case 2:
          tb.unpaid();
          break;
        case 3:
          tb.showDetails();
          break;
        default:
          System.out.println("plse choose the option wisely");
          break;
      }
      System.out.print("press y to continue : ");
      c = new Scanner(System.in).nextLine();
    }
    scan.close();
  }
}
