class Employee {
  private String name;
  private int id;
  private String address;
  private double salary;

  public Employee(String name, int id, String address, double salary) {
    this.name = name;
    this.id = id;
    this.address = address;
    this.salary = salary;
  }

  public double getSalary() {
    return salary;
  }

  public String toString() {
    return "ID: " + id + ", Name: " + name + ", Address: " + address + ", Salary: " + salary;
  }
}

class Dept {
  private String name;
  private String location;
  private Employee[] employees;
  private int count;

  public Dept(String name, String location, int capacity) {
    this.name = name;
    this.location = location;
    this.employees = new Employee[capacity];
    this.count = 0;
  }

  public void add(Employee employee) {
    if (count < employees.length) {
      employees[count++] = employee;
    }
  }

  public void remove(int id) {
    for (int i = 0; i < count; i++) {
      if (employees[i].toString().contains("ID: " + id + ",")) {
        employees[i] = employees[--count];
        employees[count] = null;
        break;
      }
    }
  }

  public double calculateYearlyExpenditure() {
    double total = 0;
    for (int i = 0; i < count; i++) {
      total += employees[i].getSalary();
    }
    return total * 12;
  }

  public void printEmployees() {
    for (int i = 0; i < count; i++) {
      System.out.println(employees[i]);
    }
  }
}

public class Sol6 {
  public static void main(String[] args) {
    Dept itDept = new Dept("Information Technology", "Building A", 10);

    Employee emp1 = new Employee("Alice", 1, "123 Street", 5000);
    Employee emp2 = new Employee("Bob", 2, "456 Avenue", 6000);
    Employee emp3 = new Employee("Charlie", 3, "789 Boulevard", 7000);
    Employee emp4 = new Employee("Diana", 4, "101 Road", 5500);
    Employee emp5 = new Employee("Eve", 5, "202 Lane", 5200);

    itDept.add(emp1);
    itDept.add(emp2);
    itDept.add(emp3);
    itDept.add(emp4);
    itDept.add(emp5);

    itDept.printEmployees();

    System.out.println("Yearly Expenditure: " + itDept.calculateYearlyExpenditure());
  }
}
