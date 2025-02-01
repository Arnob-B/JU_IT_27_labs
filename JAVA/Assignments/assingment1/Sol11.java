class Date {
  int day, month, year;
  int monthArray[];

  Date() {
    this.day = 1;
    this.month = 1;
    this.year = 1970;
    this.monthArray = new int[] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  }

  Date(int day) {
    this();
    this.day = day;
  }

  Date(int day, int month) {
    this();
    this.day = day;
    this.month = month;
  }

  Date(int day, int month, int year) {
    this();
    this.day = day;
    this.month = month;
    this.year = year;
  }

  boolean checkLeap(int yr) {
    return (yr % 4 == 0 && yr % 100 != 0) || (yr % 400 == 0);
  }

  Date prevDay() {
    int newDay = this.day, newMonth = this.month, newYear = this.year;

    if (this.day == 1) { // If first day of the month
      if (this.month == 1) { // If January, move to December
        newMonth = 12;
        newDay = 31;
        newYear--;
      } else {
        newMonth--;
        newDay = (newMonth == 2 && checkLeap(newYear)) ? 29 : monthArray[newMonth - 1];
      }
    } else {
      newDay--;
    }

    return new Date(newDay, newMonth, newYear);
  }

  Date nextDay() {
    int newDay = this.day, newMonth = this.month, newYear = this.year;
    int daysInMonth = (month == 2 && checkLeap(year)) ? 29 : monthArray[month - 1];

    if (this.day == daysInMonth) { // Last day of the month
      if (this.month == 12) { // If December, move to January next year
        newMonth = 1;
        newDay = 1;
        newYear++;
      } else {
        newDay = 1;
        newMonth++;
      }
    } else {
      newDay++;
    }

    return new Date(newDay, newMonth, newYear);
  }

  void print() {
    System.out.println("--- Date ---");
    System.out.println(this.day + "/" + this.month + "/" + this.year);
  }
}

public class Sol11 {
  public static void main(String argv[]) {
    Date d = new Date(31, 12, 1997);
    d.print();
    d.prevDay().print();
    d.nextDay().print();
  }
}
