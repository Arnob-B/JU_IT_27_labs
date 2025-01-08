/*
7. Create an abstract class “Publication” with data members ‘noOfPages’, ‘price’, ‘publisherName’
etc. with their accessor/modifier functions. Now create two sub-classes “Book” and “Journal”.
Create a class Library that contains a list of Publications. Write a main() function and create
three Books and two Journals, add them to library and print the details of all publications.
*/

import java.util.ArrayList;

abstract class Publication {
  private int id;
  private int noOfPages;
  private float price;
  private String publisherName;

  Publication() {
    this.noOfPages = 0;
    this.price = 0;
    this.publisherName = "";
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }

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
  @Override
  void print() {
    System.out.println("--- Book ---");
    System.out.println("Id : " + getId());
    System.out.println("name : " + getPublisherName());
    System.out.println("price : " + getPrice());
    System.out.println("page count : " + getNoOfPages());
  }
}

class Journal extends Publication {
  @Override
  void print() {
    System.out.println("--- Journal ---");
    System.out.println("Id : " + getId());
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

  int findIndex(int Id) {
    for (int i = 0; i < publications.size(); i++) {
      if (publications.get(i).getId() == Id)
        return i;
    }
    return -1;
  }

  boolean add(Publication pb) {
    if (findIndex(pb.getId()) != -1)
      return false;
    publications.add(pb);
    return true;
  }

  boolean remove(int Id) {
    int id = findIndex(Id);
    if (id == -1)
      return false;
    publications.remove(id);
    return true;
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
    Book b1 = new Book();
    b1.setId(1);
    b1.setNoOfPages(22);
    b1.setPublisherName("JK");
    b1.setPrice(200);
    Library lib = new Library();
    lib.add(b1);
    lib.showAll();
  }
}
