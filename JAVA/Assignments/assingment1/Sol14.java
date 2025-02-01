import javax.security.sasl.RealmCallback;

interface Shape {
  double area();

  void draw();

  void rotate();

  void move(float x, float y);

}

class Circle implements Shape {
  private float radius, x, y;
  private final float PIE = 3.14f;

  Circle(float radius, float x, float y) {
    this.radius = radius;
    this.x = x;
    this.y = y;
  }

  @Override
  public double area() {
    return PIE * radius * radius;
  }

  @Override
  public void move(float x, float y) {
    System.out.println("----Moving a Circle----");
    System.out.print("from (" + x + "," + y + ") ");
    this.x = x;
    this.y = y;
    System.out.println("to (" + x + "," + y + ") ");
  }

  @Override
  public void draw() {
    System.out.println("----- Drawing a Circle ----");
    System.out
        .println("centererd at (" + this.x + "," + this.y + ") of radius " + this.radius + "units");
  }

  @Override
  public void rotate() {
    System.out.println("rotation has no effect in a circle...");
  }

}

class Rectangle implements Shape {
  private float x, y, length, breadth;

  Rectangle(float len, float breadth, float x, float y) {
    this.length = len;
    this.breadth = breadth;
    this.x = x;
    this.y = y;
  }

  @Override
  public double area() {
    return length * breadth;
  }

  @Override
  public void move(float x, float y) {
    System.out.println("----Moving a Rectangle----");
    System.out.print("from (" + x + "," + y + ") ");
    this.x = x;
    this.y = y;
    System.out.println("to (" + x + "," + y + ") ");
  }

  @Override
  public void draw() {
    System.out.println("----- Drawing a Rectangle ----");
    System.out
        .println("centererd at (" + this.x + "," + this.y + ") of length " + this.length
            + "units and breadth " + this.breadth + "units");
  }

  @Override
  public void rotate() {
    System.out.println("Rectangle is rotating");
  }

}

public class Sol14 {
  public static void main(String[] args) {
    Shape rect = new Rectangle(12, 13, 0, 0);
    Shape circ = new Circle(19.4f, 5, 9);
    rect.draw();
    System.out.println("Area of Rectangle " + rect.area());
    rect.move(2.5f, 2.55f);
    rect.rotate();

    circ.draw();
    System.out.println("Area of Rectangle " + circ.area());
    circ.move(2.5f, 2.55f);
    circ.rotate();
  }
}
