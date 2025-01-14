interface fruit {
  void hasAPeel();
}

interface vegetable {
  void hasARoot();
}

class Tomato implements fruit, vegetable {
  @Override
  public void hasAPeel() {
    System.out.println("yes it can be peeled");
  }

  @Override
  public void hasARoot() {
    System.out.println("no it does not have roots");
  }
}

public class Sol16 {
  public static void main(String[] args) {
    Tomato tom = new Tomato();
    tom.hasAPeel();
    tom.hasARoot();
  }

}
