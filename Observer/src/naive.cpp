#ifndef NAIVE_CPP
#define NAIVE_CPP

#include <iostream>
#include <string>
#include <vector>

namespace naive {

// Concrete notification and processing services
class UIUpdateService {
public:
    void updateUI(double amount, double balance) {
        std::cout << "[UI] Updated. Transaction: " << amount << ", New Balance: " << balance << std::endl;
    }
};

class EmailService {
public:
    void sendEmail(const std::string& accountNumber, double amount) {
        std::cout << "[Email] Sent receipt for account " << accountNumber << ". Amount: " << amount << std::endl;
    }
};

class LoggerService {
public:
    void logTransaction(const std::string& accountNumber, double amount) {
        std::cout << "[Logger] Logged transaction for account " << accountNumber << ". Amount: " << amount << std::endl;
    }
};

class FraudDetectionService {
public:
    void detectFraud(const std::string& accountNumber, double amount) {
        std::cout << "[Fraud AI] Checked transaction for account " << accountNumber << ". Amount: " << amount << ". Status: Safe." << std::endl;
    }
};

class MobileAppService {
public:
    void pushNotification(double amount) {
        std::cout << "[Mobile App] Push notification sent. Activity: " << amount << std::endl;
    }
};

class AnalyticsService {
public:
    void trackEvent(const std::string& eventType, double amount) {
        std::cout << "[Analytics] Tracked event '" << eventType << "' with amount " << amount << std::endl;
    }
};

// BankAccount class with direct, hardcoded dependencies
class BankAccount {
private:
    double balance;
    std::string accountNumber;
    
    // Direct dependencies on concrete services
    UIUpdateService* uiService;
    EmailService* emailService;
    LoggerService* loggerService;
    FraudDetectionService* fraudService;
    MobileAppService* mobileService;
    AnalyticsService* analyticsService;

public:
    // Constructor implementing initialization with all concrete dependencies passed as parameters
    BankAccount(std::string accNum,
                UIUpdateService* ui,
                EmailService* email,
                LoggerService* logger,
                FraudDetectionService* fraud,
                MobileAppService* mobile,
                AnalyticsService* analytics) 
        : balance(0.0), accountNumber(accNum),
          uiService(ui),
          emailService(email),
          loggerService(logger),
          fraudService(fraud),
          mobileService(mobile),
          analyticsService(analytics) {}

    // Destructor (no ownership of passed service pointers)
    ~BankAccount() = default;

    // deposit method notifying each service directly
    void deposit(double amount) {
        balance += amount;
        
        // Directly invoke methods on each hardcoded concrete service dependency
        uiService->updateUI(amount, balance);
        emailService->sendEmail(accountNumber, amount);
        loggerService->logTransaction(accountNumber, amount);
        fraudService->detectFraud(accountNumber, amount);
        mobileService->pushNotification(amount);
        analyticsService->trackEvent("deposit", amount);
    }

    double getBalance() const { return balance; }
    std::string getAccountNumber() const { return accountNumber; }
};

void naive_test() {
    // Create service variables on the stack
    UIUpdateService ui;
    EmailService email;
    LoggerService logger;
    FraudDetectionService fraud;
    MobileAppService mobile;
    AnalyticsService analytics;

    // Create BankAccount with multiple parameters
    BankAccount account("123456789", &ui, &email, &logger, &fraud, &mobile, &analytics);

    // Call deposit to demonstrate coupling execution
    std::cout << "--- Naive Deposit Test ---" << std::endl;
    account.deposit(500.0);
    account.deposit(200.0);
}

} // namespace naive

#endif