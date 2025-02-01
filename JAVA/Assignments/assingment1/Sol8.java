import java.util.ArrayList;
import java.util.List;

class Account {
  private int accountNumber;
  private String holderName;
  private double balance;

  public Account(int accountNumber, String holderName, double balance) {
    this.accountNumber = accountNumber;
    this.holderName = holderName;
    this.balance = balance;
  }

  public int getAccountNumber() {
    return accountNumber;
  }

  public String getHolderName() {
    return holderName;
  }

  public double getBalance() {
    return balance;
  }

  public void setBalance(double balance) {
    this.balance = balance;
  }

  public String getDetails() {
    return "AccountNumber: " + accountNumber + ", HolderName: " + holderName + ", Balance: " + balance;
  }
}

class SavingsAccount extends Account {
  private double interestRate;

  public SavingsAccount(int accountNumber, String holderName, double balance, double interestRate) {
    super(accountNumber, holderName, balance);
    this.interestRate = interestRate;
  }

  public double calculateYearlyInterest() {
    return getBalance() * interestRate / 100;
  }

  @Override
  public String getDetails() {
    return super.getDetails() + ", InterestRate: " + interestRate;
  }
}

class CurrentAccount extends Account {
  public CurrentAccount(int accountNumber, String holderName, double balance) {
    super(accountNumber, holderName, balance);
  }
}

class Manager {
  private List<Account> accounts;

  public Manager() {
    this.accounts = new ArrayList<>();
  }

  public void addAccount(Account account) {
    accounts.add(account);
  }

  public void printAccounts() {
    for (Account account : accounts) {
      System.out.println(account.getDetails());
    }
  }

  public void calculateSavingsInterest() {
    for (Account account : accounts) {
      if (account instanceof SavingsAccount) {
        SavingsAccount sa = (SavingsAccount) account;
        System.out.println(
            "Yearly Interest for AccountNumber " + sa.getAccountNumber() + ": " + sa.calculateYearlyInterest());
      }
    }
  }
}

class Main {
  public static void main(String[] args) {
    Manager manager = new Manager();

    SavingsAccount sa1 = new SavingsAccount(1, "Alice", 5000, 4);
    SavingsAccount sa2 = new SavingsAccount(2, "Bob", 7000, 3.5);
    CurrentAccount ca1 = new CurrentAccount(3, "Charlie", 10000);
    CurrentAccount ca2 = new CurrentAccount(4, "Diana", 15000);
    CurrentAccount ca3 = new CurrentAccount(5, "Eve", 20000);

    manager.addAccount(sa1);
    manager.addAccount(sa2);
    manager.addAccount(ca1);
    manager.addAccount(ca2);
    manager.addAccount(ca3);

    manager.printAccounts();
    manager.calculateSavingsInterest();
  }
}
