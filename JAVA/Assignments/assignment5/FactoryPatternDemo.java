interface Shape {
  public void draw();
}

class Circle implements Shape{
  public void draw(){
    System.out.println("drawing a circle");
  }

}
class Rectangle implements Shape{
  public void draw(){
    System.out.println("drawing a rectangle");
  }

}
class Square implements Shape{
  public void draw(){
    System.out.println("drawing a square");
  }

}
class ShapeFactory{
  public static Shape getShape(String shapeName){
    switch (shapeName.toLowerCase()) {
      case "circle":
        return new Circle();
      case "rectangle":
        return new Rectangle();
      case "square":
        return new Square();
      default:
        return null;
    }
  }

}
public class FactoryPatternDemo {
  public static void main(String[] args) {
    Shape circle = ShapeFactory.getShape("circle");
    Shape rectangle = ShapeFactory.getShape("rectangle");
    Shape square = ShapeFactory.getShape("square");
    circle.draw();
    rectangle.draw();
    square.draw();
  }
}
