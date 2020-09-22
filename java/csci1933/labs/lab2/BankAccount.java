import java.util.Scanner;
public class BankAccount {
    String name;
    String password;
    double balance;

    private BankAccount(String initName, String initPass, double initBalance) {
        this.name = initName;
        this.password = initPass;
        this.balance = initBalance;
    }

    private BankAccount() {}


    public void withdraw(String password, double amount) {
        if (password.equals(password) && balance >= amount) {
            balance = balance - amount;
        }
    }


    public void deposit(String enteredPassword, double amount) {
        if (password.equals(enteredPassword)) {
            balance = balance + amount;
        }
    }


    public double getBalance(String enteredPassword) {
        if (password.equals(enteredPassword)) 
            return balance;

        else return -1;
    }


    public boolean setPassword(String oldPassword, String newPassword) {
        if (password.equals(oldPassword)) {
            password = newPassword;
            return true;
        }

        else return false;
    }

    public void transfer(BankAccount other, String enteredPassword, double amount) {
        if (other.password.equals(enteredPassword)) {
            withdraw(this.password, amount);

            other.deposit(enteredPassword, amount);
        }

        else System.out.println("either amount more than in bank account or password wrong");
    }


    public static void main(String[] args) {
        BankAccount myAccount = new BankAccount();

        myAccount.password = "dog";
        myAccount.deposit("dog", 200);
//        System.out.println("My account's balance is: " + myAccount.balance);
        System.out.println();



        BankAccount otherAccount = new BankAccount("Fletcher", "cat", 0);
//
//        Scanner s = new Scanner(System.in);
//
//        System.out.print("To view balance, enter password: ");
//        String pass = s.nextLine();
//
//        System.out.println(myAccount.getBalance(pass));
        


        System.out.println("current balance: " + myAccount.getBalance("dog"));
        System.out.println("other account balance: " + otherAccount.getBalance("cat"));
        System.out.println();

        Scanner t = new Scanner(System.in);

        System.out.print("how much money do you wish to transfer: ");
        double amt = Double.valueOf(t.nextLine());

        System.out.println();

        System.out.print("Password: ");
        String passwd = t.nextLine();

        myAccount.transfer(otherAccount, passwd, amt);

        System.out.println("new balance: " + myAccount.getBalance("dog"));
        System.out.println("other account balance: " + otherAccount.getBalance("cat"));


    }
}
