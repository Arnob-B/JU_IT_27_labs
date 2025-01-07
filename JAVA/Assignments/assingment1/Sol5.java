/*
5. Write a class to represent complex numbers with necessary constructors. Write member
functions to add, multiply two complex numbers.
There should be three constructors: (i) to initialize real and imaginary parts to 0; (ii) to initialize
imaginary part to 0 but to initialize the real part to user defined value; (iii) to initialize the real
part and the imaginary part to user defined values.
Also, write a main() function to (i) create two complex numbers 3+2i and 4-2i; (ii) to print the
sum and product of those numbers.
*/


class Complex{
  private float real, imag;
  Complex(){
    this.real = 0;
    this.imag = 0;
  }
  Complex(int real){
    this.real = real;
    this.imag = 0;
  }
  Complex(int real , int imag){
    this.real = real;
    this.imag = imag;
  }
  void add(Complex obj){
    this.real+=obj.real;
    this.imag+=obj.imag;
  }
  void multiply(Complex obj){
    this.real=(this.real * obj.real) - (this.imag * obj.imag);
    this.imag=( this.imag* obj.real )+ (this.real * obj.imag);
  }
  void print(){
    System.out.println("complex number : " + this.real + " + " + this.imag + "j");
  }
}


public class Sol5 {
  public static void main(String[] args) {
    Complex c1,c2, added, multi;
    c1 = new Complex(3,2);
    c1.print();
    c2 = new Complex(4,-2);
    c2.print();
    added = new Complex();
    multi = new Complex();
    added.add(c1);
    added.add(c2);
    System.out.println("addition");
    added.print();
    multi.add(c1);
    multi.multiply(c2);
    System.out.println("multiplication");
    multi.print();
  }
}
