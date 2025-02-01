import java.util.*;

class Person {
  private int age;
  private double weight;
  private double height;
  private String dateOfBirth;
  private String address;

  public Person(int age, double weight, double height, String dateOfBirth, String address) {
    this.age = age;
    this.weight = weight;
    this.height = height;
    this.dateOfBirth = dateOfBirth;
    this.address = address;
  }

  public int getAge() {
    return age;
  }

  public void setAge(int age) {
    this.age = age;
  }

  public double getWeight() {
    return weight;
  }

  public void setWeight(double weight) {
    this.weight = weight;
  }

  public double getHeight() {
    return height;
  }

  public void setHeight(double height) {
    this.height = height;
  }

  public String getDateOfBirth() {
    return dateOfBirth;
  }

  public void setDateOfBirth(String dateOfBirth) {
    this.dateOfBirth = dateOfBirth;
  }

  public String getAddress() {
    return address;
  }

  public void setAddress(String address) {
    this.address = address;
  }
}

class Employee extends Person {
  private double salary;
  private String dateOfJoining;
  private int experience;

  public Employee(int age, double weight, double height, String dateOfBirth, String address, double salary,
      String dateOfJoining, int experience) {
    super(age, weight, height, dateOfBirth, address);
    this.salary = salary;
    this.dateOfJoining = dateOfJoining;
    this.experience = experience;
  }

  public double getSalary() {
    return salary;
  }

  public void setSalary(double salary) {
    this.salary = salary;
  }

  public String getDateOfJoining() {
    return dateOfJoining;
  }

  public void setDateOfJoining(String dateOfJoining) {
    this.dateOfJoining = dateOfJoining;
  }

  public int getExperience() {
    return experience;
  }

  public void setExperience(int experience) {
    this.experience = experience;
  }
}

class Student extends Person {
  private int roll;
  private Map<String, Integer> listOfSubjects;

  public Student(int age, double weight, double height, String dateOfBirth, String address, int roll) {
    super(age, weight, height, dateOfBirth, address);
    this.roll = roll;
    this.listOfSubjects = new HashMap<>();
  }

  public int getRoll() {
    return roll;
  }

  public void setRoll(int roll) {
    this.roll = roll;
  }

  public void addSubject(String subject, int marks) {
    listOfSubjects.put(subject, marks);
  }

  public void removeSubject(String subject) {
    listOfSubjects.remove(subject);
  }

  public String calculateGrade() {
    int totalMarks = 0;
    for (int marks : listOfSubjects.values()) {
      totalMarks += marks;
    }
    double average = totalMarks / (double) listOfSubjects.size();

    if (average >= 90)
      return "A";
    else if (average >= 75)
      return "B";
    else if (average >= 50)
      return "C";
    else
      return "F";
  }
}

class Technician extends Employee {
  public Technician(int age, double weight, double height, String dateOfBirth, String address, double salary,
      String dateOfJoining, int experience) {
    super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
  }
}

class Professor extends Employee {
  private List<String> courses;
  private List<String> listOfAdvisee;

  public Professor(int age, double weight, double height, String dateOfBirth, String address, double salary,
      String dateOfJoining, int experience) {
    super(age, weight, height, dateOfBirth, address, salary, dateOfJoining, experience);
    this.courses = new ArrayList<>();
    this.listOfAdvisee = new ArrayList<>();
  }

  public void addCourse(String course) {
    courses.add(course);
  }

  public void removeCourse(String course) {
    courses.remove(course);
  }

  public void addAdvisee(String advisee) {
    listOfAdvisee.add(advisee);
  }

  public void removeAdvisee(String advisee) {
    listOfAdvisee.remove(advisee);
  }
}

public class Sol9 {
  public static void main(String[] args) {
    Person person = new Person(30, 70.5, 175.0, "1995-12-15", "123 Main St");
    Employee employee = new Employee(35, 80.0, 180.0, "1990-05-20", "456 Oak St", 60000.0, "2015-06-01", 8);
    Student student = new Student(20, 60.0, 165.0, "2003-08-25", "789 Pine St", 101);
    Technician technician = new Technician(28, 75.0, 170.0, "1995-03-10", "321 Elm St", 45000.0, "2020-01-10", 3);
    Professor professor = new Professor(45, 85.0, 178.0, "1978-11-30", "654 Maple St", 80000.0, "2000-09-15", 23);

    student.addSubject("Math", 95);
    student.addSubject("Science", 88);
    student.addSubject("History", 72);
    System.out.println("Student Grade: " + student.calculateGrade());

    professor.addCourse("Physics");
    professor.addCourse("Quantum Mechanics");
    professor.addAdvisee("John Doe");
    professor.addAdvisee("Jane Smith");
  }
}
