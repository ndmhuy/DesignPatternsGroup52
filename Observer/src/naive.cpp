#include <iostream>
#include <string>

// Concrete peripheral systems (tightly coupled)
class UI {
public:
    void update(double balance) {
        std::cout << "[UI] Balance display updated to $" << balance << "\n";
    }
};

class EmailSystem {
public:
    void sendEmail(double amount) {
        std::cout << "[Email] Alert sent: A deposit of $" << amount << " was made.\n";
    }
};

class Logger {
public:
    void log(double amount, double balance) {
        std::cout << "[Logger] Transaction logged: Deposit of $" << amount << ", new balance: $" << balance << "\n";
    }
};

class FraudDetector {
public:
    void scan(double amount) {
        std::cout << "[Fraud AI] Scan complete: Deposit of $" << amount << " is marked OK.\n";
    }
};

class MobileApp {
public:
    void pushNotification(double amount) {
        std::cout << "[Mobile App] Push: Account credited with $" << amount << "\n";
    }
};

class Analytics {
public:
    void trackActivity(const std::string& type, double amount) {
        std::cout << "[Analytics] Metric recorded: Event [" << type << "] for $" << amount << "\n";
    }
};

// Tightly-coupled Naive Bank Account
class NaiveBankAccount {
private:
    double balance;
    UI ui;
    EmailSystem email;
    Logger logger;
    FraudDetector fraudDetector;
    MobileApp mobileApp;
    Analytics analytics;

public:
    NaiveBankAccount(double initialBalance = 0.0) : balance(initialBalance) {}

    void deposit(double amount) {
        balance += amount;
        
        // Direct, hardcoded method calls to concrete observer classes
        ui.update(balance);
        email.sendEmail(amount);
        logger.log(amount, balance);
        fraudDetector.scan(amount);
        mobileApp.pushNotification(amount);
        analytics.trackActivity("Deposit", amount);
    }
};
