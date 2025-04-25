interface Shape {
  public void draw();
}

class Circle implements Shape {
  public void draw() {
    System.out.println("drawing a circle");
  }

}

class Rectangle implements Shape {
  public void draw() {
    System.out.println("drawing a rectangle");
  }

}

abstract class ShapeDecorator implements Shape {
  Shape shape;

  public ShapeDecorator(Shape shape) {
    this.shape = shape;
  }

  public void draw() {
    this.shape.draw();
  }
}

class RedShapeDecorator extends ShapeDecorator {
  public RedShapeDecorator(Shape decoratedShape) {
    super(decoratedShape);
  }

  @Override
  public void draw() {
    shape.draw();
    this.setRedBorder();
  }

  public void setRedBorder() {
    System.out.println("added red border");
  }

}

public class DecoratorPatternDemo {
  public static void main(String[] args) {
    System.out.println("Regular Rectangle : ");
    Rectangle shape = new Rectangle();
    shape.draw();
    System.out.println("\nDecorated Rectangle : ");
    RedShapeDecorator decoratedShape = new RedShapeDecorator(shape);
    decoratedShape.draw();
  }

}
