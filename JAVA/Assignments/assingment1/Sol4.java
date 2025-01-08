import java.util.ArrayList;

class BankAccount {
  private int accountNumber;
  private String ownerName;
  private float balance;

  BankAccount(int accno, String owner, float bal) {
    this.accountNumber = accno;
    this.ownerName = owner;
    this.balance = bal;
  }

  float Balance() {
    return balance;
  }

  boolean sub(float val) {
    if (balance < val)
      return false;
    balance -= val;
    return true;
  }

  void add(float val) {
    balance += val;
  }
  boolean checkAccNo(int accno){ return accno == this.accountNumber;}
  void show(){
    System.out.println("-- Account --");
    System.out.println("AccountNo : "+ this.accountNumber);
    System.out.println("name : "+ ownerName);
    System.out.println("balance : "+ balance);
  }
}

class AccountManager {
  ArrayList<BankAccount> accounts;
  AccountManager(){
    this.accounts = new ArrayList<>();
  }
  boolean createAccount(int accno, String owner,float bal){
    if(findAccInd(accno) != -1) return false;
    BankAccount temp = new BankAccount(accno, owner, bal);
    this.accounts.add(temp);
    return true;
  }
  int findAccInd(int accno){
    int ind = -1;
    for (int i = 0; i < this.accounts.size(); i++) {
      if(accounts.get(i).checkAccNo(accno)){
        ind = i;break;
      }
    }
    return ind;
  }
  boolean RemoveAccount(int accno){
    int ind = findAccInd(accno);
    if(ind == -1) return false;
    this.accounts.remove(ind);
    return true;
  }
  boolean deposit(int accno , float bal){
    int ind = findAccInd(accno);
    if(ind == -1 ) return false;
    accounts.get(ind).add(bal);
    return true;
  }
  boolean withdraw(int accno , float bal){
    int ind = findAccInd(accno);
    if(ind == -1 ) return false;
    if(accounts.get(ind).Balance() < bal) return false;
    accounts.get(ind).add(bal);
    return true;
  }
  void showAll(){
    System.out.println("---- All accounts in the bank ----");
    for (BankAccount bankAccount : accounts) {
      bankAccount.show();
    }
  }
}
class Bank{
  public static void main(String[] args) {
      AccountManager accMan = new AccountManager();
      accMan.createAccount(1, "Joy", 2000);
      accMan.createAccount(2, "Roy", 3000);
      accMan.createAccount(3, "Ravi", 5000);
      accMan.createAccount(4, "Ram", 4000);
      accMan.createAccount(5,"Robin", 1000);
      accMan.showAll();
  }
}

public class Sol4 {
  public static void main(String[] args) {
    Bank.main(args);
  }
}
