import java.io.ObjectInputStream.GetField;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.text.html.HTMLDocument.Iterator;

/**
 * Sol12
 */
class Student {
  String name;
  int roll_no;
  String sub[];

  Student(String name, int roll_no, String sub[]) {
    this.sub = new String[5];
    this.name = name;
    this.roll_no = roll_no;
    for (int i = 0; i < 5 && i < sub.length; i++) {
      this.sub[i] = sub[i];
    }
  }

  public String[] getSub() {
    return sub;
  }

  public String getName() {
    return name;
  }

  public int getRoll_no() {
    return roll_no;
  }

  public void setSub(String[] sub) {
    this.sub = sub;
  }

  public void setRoll_no(int roll_no) {
    this.roll_no = roll_no;
  }

  public void setName(String name) {
    this.name = name;
  }

}

class TabulationSheet {
  HashMap<Integer, Integer> sheet;

  TabulationSheet() {
    sheet = new HashMap<>();
  }

  void addRoll(int roll,int marks) {
    sheet.put(roll,marks);
  }
  int getMarks(int roll){
    if(sheet.containsKey(roll))
      return sheet.get(roll);
    else return -1;
  }
}
class marksSheet{
  Student student;
  ArrayList<Integer> marks;
  marksSheet(Student std){
    student = std;
  }
  void addMarks(){
    //??
  }

}

public class Sol12 {

}
