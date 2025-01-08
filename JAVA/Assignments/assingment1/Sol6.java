import java.util.ArrayList;

/**
 * Sol6
 */
class Employee {
  int id;
  float sal;
  String name, address;

  Employee(int id, float sal, String name, String address) {
    this.id = id;
    this.sal = sal;
    this.name = name;
    this.address = address;
  }

}

class Dept {
  ArrayList<Employee> employees;
  private String name;
  private int count;

  Dept(String name) {
    this.employees = new ArrayList<>();
    this.count = 0;
    this.name = name;
  }

  int findIndex(int eId) {
    for (int i = 0; i < employees.size(); i++) {
      if (employees.get(i).id == eId)
        return i;
    }
    return -1;
  }

  boolean add(Employee emp) {
    if (findIndex(emp.id) != -1)
      return false;
    employees.add(emp);
    return true;
  }

  boolean remove(int empId) {
    int ind = findIndex(empId);
    if (ind == -1)
      return false;
    employees.remove(ind);
    return true;
  }

}

public class Sol6 {
  public static void main(String[] args) {
    Dept dept = new Dept("Information Technology");
    dept.add(new Employee(1, 200, "Tp", "new zealand"));
    dept.add(new Employee(2, 300, "Pp", "London"));
    dept.add(new Employee(3, 400, "Bp", "Italy"));
    dept.add(new Employee(4, 500, "Cp", "Zimbawe"));
    dept.add(new Employee(5, 400, "Np", "Morroco"));
    float sum = 0;
    for (Employee emp : dept.employees) {
      sum += emp.sal;
    }
    System.out.println("yearly expenditure is " + sum * 12);
  }
}
