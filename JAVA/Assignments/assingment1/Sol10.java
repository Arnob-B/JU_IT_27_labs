import java.util.ArrayList;
import java.util.Scanner;

class Book {
  private String author;
  private String title;
  private String publisher;
  private float cost;
  private int stock;

  public Book(String author, String title, String publisher, float cost, int stock) {
    this.author = author;
    this.title = title;
    this.publisher = publisher;
    this.cost = cost;
    this.stock = stock;
  }

  public String getAuthor() {
    return author;
  }

  public String getTitle() {
    return title;
  }

  public int getStock() {
    return stock;
  }

  public float getCost() {
    return cost;
  }

  public void displayDetails() {
    System.out.println("----Book----");
    System.out.println("Title: " + title);
    System.out.println("Author: " + author);
    System.out.println("Publisher: " + publisher);
    System.out.println("Cost: " + cost);
    System.out.println("Stock: " + stock);
  }
}

class BookShop {
  ArrayList<Book> books;

  int bookIndex(String author, String title) {
    int ind = -1;
    for (int a = 0; a < books.size(); a++) {
      if (books.get(a).getAuthor().equalsIgnoreCase(author) && books.get(a).getTitle().equalsIgnoreCase(title)) {
        ind = a;
        break;
      }
    }
    return ind;
  }

  BookShop() {
    System.out.println("-----Welcome to BookShop-----");
    // seeding with some books
    this.books = new ArrayList<>();
    books.add(new Book("J.K. Rowling", "Harry Potter", "Bloomsbury", 499.99f, 10));
    books.add(new Book("George Orwell", "1984", "Secker & Warburg", 299.99f, 5));
    books.add(new Book("J.R.R. Tolkien", "The Hobbit", "Allen & Unwin", 399.99f, 7));
  }

  public void search(String author, String title) {
    final int ind = bookIndex(author, title);
    if (ind != -1 && books.get(ind).getStock() > 0) {
      Scanner scan = new Scanner(System.in);
      final Book book = books.get(ind);
      book.displayDetails();
      System.out.print("Enter the required no of copies : ");
      final int copies = scan.nextInt();
      if (book.getStock() >= copies) {
        final float cost = book.getCost() * copies;
        System.out.println("Total cost " + cost);
      } else {
        System.out.println("Dont have that many copies");
      }
      scan.close();
    } else {
      System.out.println("Book is not available");
    }
  }
}

public class Sol10 {
  public static void main(String[] args) {
    BookShop Bs = new BookShop();
    Scanner sc = new Scanner(System.in);
    System.out.print("Name the author : ");
    String author = sc.nextLine();
    System.out.print("Name the Book : ");
    String title = sc.nextLine();
    Bs.search(author, title);
    sc.close();
  }
}
