class Room {
  int height, width, breadth;

  public Room(int height, int width, int breadth) {
    this.height = height;
    this.width = width;
    this.breadth = breadth;
  }

  public int volume() {
    return height * breadth * width;
  }
}

class RoomDemo {
  static Room objs[];

  public static void start() {
    int n = 5;
    objs = new Room[n];
    for (int i = 0; i < n; i++) {
      objs[i] = new Room(i + 1, i + 2, i + 3);
    }
    for (int i = 0; i < n; i++) {
      System.out.println("Room " + (i + 1) + " " + objs[i].volume());
    }
  }
}

public class Sol1 {
  public static void main(String[] args) {
    RoomDemo.start();
  }
}
