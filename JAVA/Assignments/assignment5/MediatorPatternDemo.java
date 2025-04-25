class Chatroom {
  public void showMessages(String message, User user) {
    System.out.println(user.getName() + " : " + message);

  }
}

class User {
  String name;
  protected Chatroom chatroomMediator;

  public User() {
    chatroomMediator = new Chatroom();
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public void sendMessage(String message) {
    chatroomMediator.showMessages(message, this);
  }
}

public class MediatorPatternDemo {
  public static void main(String[] args) {
    User john = new User();
    john.setName("John");
    User mark = new User();
    mark.setName("Mark");

    john.sendMessage("hello Mark !");
    mark.sendMessage("hi John !");
  }

}
