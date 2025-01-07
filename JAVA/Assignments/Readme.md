# JAVA Assignments

## Assignment 1
1. Create a class “Room” which will hold the “height”, “width” and “breadth” of the room in three
fields. This class also has a method “volume()” to calculate the volume of this room. Create
another class “RoomDemo” which will use the earlier class, create instances of rooms, and
display the volume of room. [sol](./assingment1/Sol1.java)

2. Write a program to implement a class “student” with the following members.
Name of the student.
Marks of the student obtained in three subjects.
Function to assign initial values.
Function to compute total average.
Function to display the student’s name and the total marks.
Write an appropriate main() function to demonstrate the functioning of the above.[sol](./assingment1/Sol2.java)

3. Implement a class for stack of integers using an array. Please note that the operations defined for
a stack data structure are as follows: “push”, “pop”, “print”. There should be a constructor to
create an array of integers; the size of the array is provided by the user.
Write a main() function to (i) create a stack to hold maximum of 30 integers; (ii) push the
numbers 10, 20, 30, 15, 9 to the stack; (iii) print the stack; (iii) pop thrice and (iv) print the stack
again.[sol](./assingment1/Sol3.java)

4. Write a class “BankAccount” with the following instance variables:
AccountNumber (an integer), balance a floating-point number), and “ownerName” (a String).
Write proper constructor for this class. Also write methods balance, add (to deposit an amount),
and subtract (to withdraw an amount) and implement them. Now create another class
“AccountManager” that contains an array of BankAccount. Write methods create (to create an
account), delete(to terminate an account), deposit (to deposit an amount to an account) and
withdraw (to withdraw an amount from an account). Also write a class “Bank”, add main()
function that creates an AccountManager and add 5 accounts. Now print the details of all
accounts in this Bank.[sol](./assingment1/sol4.java)

5. Write a class to represent complex numbers with necessary constructors. Write member
functions to add, multiply two complex numbers.
There should be three constructors: (i) to initialize real and imaginary parts to 0; (ii) to initialize
imaginary part to 0 but to initialize the real part to user defined value; (iii) to initialize the real
part and the imaginary part to user defined values.
Also, write a main() function to (i) create two complex numbers 3+2i and 4-2i; (ii) to print the
sum and product of those numbers.

6. Write a Java class “Employee” containing information name, id, address, salary etc. Write
necessary constructor and read/write methods.
Create a class “Dept” that has a name, location etc. The “Dept” contains a number of
“Employee”. Write methods “add” and “remove” to add and remove an employee to/from this
department.
Write a main() function and create “Information Technology” department. Add five employees
and print yearly expenditure for this department.

7. Create an abstract class “Publication” with data members ‘noOfPages’, ‘price’, ‘publisherName’
etc. with their accessor/modifier functions. Now create two sub-classes “Book” and “Journal”.
Create a class Library that contains a list of Publications. Write a main() function and create
three Books and two Journals, add them to library and print the details of all publications.

8. Write a class for “Account” containing data members ‘accountNumber’, ‘holderName’,
‘balance’ and add constructors and necessary accessor/modifier functions for these data
members. Now create two class “SavingsAccount” and “CurrentAccount” extending from this
class. SavingsAccount will have a member variable ‘interestRate’ and member function
‘calculateYearlyInterest’. Write another class “Manager” that contains a list Account. Also write
a main() function to create an instance of Manager class. Add two SavingsAccount and three
CurrentAccount to Manager. Calculate interest of each SavingsAccount. Print the details of all
accounts.

9. Implement a class for a “Person”. Person has data members ‘age’, ’weight’, ‘height’,
‘dateOfBirth’, ‘address’ with proper reader/write methods etc. Now create two subclasses
“Employee” and “Student”. Employee will have additional data member ‘salary’,
‘dateOfJoining’, ‘experience’ etc. Student has data members ‘roll’, ‘listOfSubjects’, their marks
and methods ‘calculateGrade’. Again create two sub-classes “Technician” and “Professor” from
Employee. Professor has data members ‘courses’, ‘listOfAdvisee’ and their add/remove
methods. Write a main() function to demonstrate the creation of objects of different classes and
their method calls.

10. A bookshop maintains the inventory of books that are being sold at the shop. The list includes
details such as author, title, publisher, cost and stock position. Whenever a customer wants a
book, the sales person inputs the title and author and the system searches the list and displays
whether it is available or not. If it is not, an appropriate message is displayed. If it is, then the
system displays the book details and details and requests for the number of copies required. If the
required copies are available, the total cost of the requested copies is displayed, otherwise the
message “requires copies not in stock” is displayed. Design a system using a class called “Book”
with suitable member methods and constructors.

11. Implement a class for “Date”. Write member functions for (i) getting the previous day, (iv)
getting the next day, (iii) printing a day
There should be four constructors: (i) day, month and year are initialized to 01, 01, 1970; (ii) day
is initialized to user specified value but month and year are initialized to 01, 1970; (iii) day,
month are initialized to user specified value but year is initialized to 1970; (iv) day, month and
year are initialized to user defined values.
Also, write a main() function to (i) create a date object; (ii) print the next and the previous day.

12. Implement a class for a “Student”. Information about a student includes name, roll no and an array
of five subject names. The class should have suitable constructor and get/set methods.
Implement a class “TabulationSheet”. A tabulation sheet contains roll numbers and marks of each
student for a particular subject. This class should have a method for adding the marks and roll no
of a student.
Implement a class “MarkSheet”. A mark sheet contains marks of all subjects for a particular
student. This class should have a method to add name of a student and marks in each subject.
Write a main() function to create three “Student” objects, Five “Tabulationsheet” objects for Five
subjects and three “Marksheet” object for three students. Print the mark sheets.

13. Create a base class “Automobile”. An Automobile contains data members ‘make’, ‘type’,
‘maxSpeed’, ‘price’, ‘mileage’, ‘registrationNumber’ etc. with their reader/writer methods. Now
create two sub-classes “Track” and “Car”. Track has data members ‘capacity’, ‘hoodType’,
‘noOfWheels’ etc. Car has data members ‘noOfDoors’, ‘seatingCapacity’ and their reader/writer
methods. Create a main() function to demonstrate this.

14. Implement the classes for the following inheritance hierarchies.
Create an interface “Shape” that contains methods ‘area’, ‘draw’, ‘rotate’, ‘move’ etc. Now create
two classes “Circle” and “Rectangle” that implement this ‘Shape’ interface and implement the
methods ‘area’, ‘move’, etc. Write a main() function to create two “Circle” and three “Rectangle”,
then move them. Print the details of circles and rectangles before after moving them.

15. Imagine a toll booth and a bridge. Cars passing by the booth are expected to pay an amount of Rs.
50/- as toll tax. Mostly they do but sometimes a car goes by without paying. The toll booth keeps
track of the number of the cars that have passed without paying, total number of cars passed by,
and the total amount of money collected. Execute this with a class called “Tollbooth” and print
out the result as follows:
The total number of cars passed by without paying.
Total number of cars passed by.
Total cash collected.

16. Write two interfaces “Fruit” and “Vegetable” containing methods ‘hasAPeel’ and ‘hasARoot’.
Now write a class “Tomato” implementing Fruit and Vegetable. Instantiate an object of Tomato.
Print the details of this object.

17. A bookshop maintains the inventory of books that are being sold at the shop. The list includes
details such as author, title, publisher, cost and stock position. Whenever a customer wants a
book, the sales person inputs the title and author and the system searches the list and displays
whether it is available or not. If it is not, an appropriate message is displayed. If it is, then the
system displays the book details and details and requests for the number of copies required. If the
required copies are available, the total cost of the requested copies is displayed, otherwise the
message “requires copies not in stock” is displayed. Design a system using a class called “Book”
with suitable member methods and constructors

