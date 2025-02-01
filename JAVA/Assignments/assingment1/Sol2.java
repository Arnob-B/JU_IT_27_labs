class Student {
  private String name;
  private int marks[];

  public Student() {
    this.marks = new int[3];
  }

  public void setName(String name) {
    this.name = name;
  }

  public void setMarks(int m1, int m2, int m3) {
    this.marks[0] = m1;
    this.marks[1] = m2;
    this.marks[2] = m3;
  }

  public float avg() {
    int sum = 0;
    for (int i = 0; i < marks.length; i++) {
      sum += marks[i];
    }
    return sum / marks.length;
  }

  public void display() {
    System.out.println("... Student profile ...");
    System.out.println("name : -> " + name);
    for (int i = 0; i < 3; i++) {
      System.out.println("marks of sub" + (i + 1) + " : -> " + marks[i]);
    }
    System.out.println("avg is " + avg());
  }
}

public class Sol2 {
  public static void main(String[] args) {
    Student s = new Student();
    s.setName("Joy");
    s.setMarks(22, 92, 89);
    s.display();
  }
}
