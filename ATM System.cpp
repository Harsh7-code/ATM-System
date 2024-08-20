#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

class Account {
public:
    Account() : accountNumber(""), pin(""), balance(0) {}

    Account(string accNum, string pin) : accountNumber(accNum), pin(pin), balance(0) {}

    string getAccountNumber() const { return accountNumber; }
    string getPin() const { return pin; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back("Deposited: ₹" + to_string(amount));
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                transactionHistory.push_back("Withdrew: ₹" + to_string(amount));
                return true;
            } else {
                cout << "Insufficient balance." << endl;
                return false;
            }
        } else {
            cout << "Withdrawal amount must be positive." << endl;
            return false;
        }
    }

    void showTransactionHistory() const {
        if (transactionHistory.empty()) {
            cout << "No transactions to show." << endl;
            return;
        }
        cout << "Transaction History:" << endl;
        for (const string& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }

    void closeAccount() {
        transactionHistory.clear();
    }

private:
    string accountNumber;
    string pin;
    double balance;
    vector<string> transactionHistory;
};

map<string, Account> accounts;

void showMenu() {
    cout << "********** MENU **********" << endl;
    cout << "1. Check balance" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Show Transaction History" << endl;
    cout << "5. Close Account" << endl;
    cout << "6. Exit" << endl;
    cout << "**************************" << endl;
}

bool authenticate(const string& accountNumber, const string& pin) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second.getPin() == pin;
    }
    return false;
}

void createAccount() {
    string accNum, pin;
    cout << "Enter new account number: ";
    cin >> accNum;
    cout << "Enter new PIN: ";
    cin >> pin;

    if (accounts.find(accNum) != accounts.end()) {
        cout << "Account already exists." << endl;
    } else {
        accounts[accNum] = Account(accNum, pin);
        cout << "Account created successfully." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "********** ATM SYSTEM **********" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Access Account" << endl;
        cout << "3. Exit" << endl;
        cout << "********************************" << endl;
        cout << "Please choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                createAccount();
                break;
            }
            case 2: {
                string accountNumber, pin;
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter PIN: ";
                cin >> pin;

                if (!authenticate(accountNumber, pin)) {
                    cout << "Authentication failed." << endl;
                    break;
                }

                Account& currentAccount = accounts[accountNumber];
                int option;
                do {
                    showMenu();
                    cout << "Please choose option: ";
                    cin >> option;

                    switch (option) {
                        case 1:
                            cout << "Balance is: ₹" << fixed << setprecision(2) << currentAccount.getBalance() << endl;
                            break;
                        case 2: {
                            double depositAmount;
                            cout << "Deposit amount: ";
                            cin >> depositAmount;
                            currentAccount.deposit(depositAmount);
                            break;
                        }
                        case 3: {
                            double withdrawAmount;
                            cout << "Withdraw amount: ";
                            cin >> withdrawAmount;
                            currentAccount.withdraw(withdrawAmount);
                            break;
                        }
                        case 4:
                            currentAccount.showTransactionHistory();
                            break;
                        case 5:
                            currentAccount.closeAccount();
                            accounts.erase(accountNumber);
                            cout << "Account closed successfully." << endl;
                            break;
                        case 6:
                            cout << "Exiting. Thank you for using the ATM." << endl;
                            break;
                        default:
                            cout << "Invalid option. Please try again." << endl;
                            break;
                    }

                    cout << endl;
                } while (option != 6);

                break;
            }
            case 3:
                cout << "Exiting system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
