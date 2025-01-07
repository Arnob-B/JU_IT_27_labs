
/**
 * Sol3
 */

class Stack {
  private int data[];
  private int top;

  Stack(int n) {
    data = new int[n];
    top = -1;
  }

  public boolean push(int val) {
    if (top != data.length) {
      data[++top] = val;
      return true;
    }
    return false;
  }

  public int pop() {
    if (top != 0) {
      return data[top--];
    }
    return -1;
  }

  public void print() { // what do you mean by that
    System.out.print("contents of the stack : ");
    for (int i = 0; i < top; i++) {
      System.out.print(data[i] + ",");
    }
    System.out.println();
  }
}

public class Sol3 {
  public static void main(String[] args) {
    Stack s = new Stack(30);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(15);
    s.push(9);
    s.print();
    s.pop();
    s.pop();
    s.pop();
    s.print();
  }
}
