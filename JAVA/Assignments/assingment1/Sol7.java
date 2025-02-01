/*
7. Create an abstract class “Publication” with data members ‘noOfPages’, ‘price’, ‘publisherName’
etc. with their accessor/modifier functions. Now create two sub-classes “Book” and “Journal”.
Create a class Library that contains a list of Publications. Write a main() function and create
three Books and two Journals, add them to library and print the details of all publications.
*/

import java.lang.reflect.Constructor;
import java.util.ArrayList;

abstract class Publication {
  private int noOfPages;
  private float price;
  private String publisherName;

  public void setPublisherName(String publisherName) {
    this.publisherName = publisherName;
  }

  public void setPrice(float price) {
    this.price = price;
  }

  public void setNoOfPages(int noOfPages) {
    this.noOfPages = noOfPages;
  }

  public float getPrice() {
    return price;
  }

  public int getNoOfPages() {
    return noOfPages;
  }

  public String getPublisherName() {
    return publisherName;
  }

  abstract void print();
}

class Book extends Publication {
  String name;

  Book(String name, int noOfPages, float price, String publisherName) {
    this.name = name;
    setNoOfPages(noOfPages);
    setPrice(price);
    setPublisherName(publisherName);
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  void print() {
    System.out.println("--- Book ---");
    System.out.println("name : " + getName());
    System.out.println("price : " + getPrice());
    System.out.println("page count : " + getNoOfPages());
    System.out.println("publisherName : " + getPublisherName());
  }
}

class Journal extends Publication {
  String name;

  Journal(String name, int noOfPages, float price, String publisherName) {
    this.name = name;
    setNoOfPages(noOfPages);
    setPrice(price);
    setPublisherName(publisherName);
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  void print() {
    System.out.println("--- Journal ---");
    System.out.println("name : " + getPublisherName());
    System.out.println("price : " + getPrice());
    System.out.println("page count : " + getNoOfPages());
  }
}

class Library {
  ArrayList<Publication> publications;

  Library() {
    publications = new ArrayList<>();
  }

  void add(Publication pb) {
    publications.add(pb);
  }

  void showAll() {
    System.out.println("Publications in Library...");
    for (Publication publication : publications) {
      publication.print();
    }
  }
}

public class Sol7 {
  public static void main(String[] args) {
    Book b1 = new Book("harry porter", 22, 200, "SK");
    Book b2 = new Book("Murder on the Orient Express", 29, 300, "Mk");
    Book b3 = new Book("Hamlet", 59, 900.77f, "John publications");
    Journal j1 = new Journal("The Lancet", 89, 280.23f, "Das publications");
    Journal j2 = new Journal("Nature Medicine", 19, 300.32f, "Das publications");
    Library lib = new Library();
    lib.add(b1);
    lib.add(b2);
    lib.add(b3);
    lib.add(j1);
    lib.add(j2);
    lib.showAll();
  }
}
