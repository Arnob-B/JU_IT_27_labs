interface Shape {
  double area();

  void draw();

  void rotate();

  void move(float x, float y);

}

class Circle implements Shape {
  private float radius, x, y;

  Circle(int radius, float x, float y) {
    this.radius = radius;
    this.x = x;
    this.y = y;
  }

  @Override
  public double area() {
    return 3.14 * radius * radius;
  }

  @Override
  public void move(float x, float y) {
    this.x = x;
    this.y = y;

  }

  @Override
  public void draw() {
    System.out
        .println("drawing a circle centererd at (" + this.x + "," + this.y + ") of radius " + this.radius + "units");
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
    this.x = x;
    this.y = y;
  }

  @Override
  public void draw() {
    System.out
        .println("drawing a Rectangle centererd at (" + this.x + "," + this.y + ") of length " + this.length
            + "units and breadth " + this.breadth + "units");
  }

  @Override
  public void rotate() {
  }

}

public class Sol14 {

}
