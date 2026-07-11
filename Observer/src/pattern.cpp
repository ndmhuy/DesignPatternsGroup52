#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

class AccountObserver {
public:
  virtual ~AccountObserver() = default;
  virtual void onTransaction(const std::string &type, double amount,
                             double currentBalance) = 0;
};

class BankAccount {
public:
  BankAccount(double initialBalance = 0.0) : balance_(initialBalance) {}

  void attach(std::shared_ptr<AccountObserver> observer) {
    observers_.push_back(observer);
  }
  void detach(std::shared_ptr<AccountObserver> observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end());
  }
  void notify(const std::string &type, double amount) {
    for (auto observer : observers_) {
      observer->onTransaction(type, amount, balance_);
    }
  }
  void deposit(double amount) {
    balance_ += amount;
    notify("Deposit", amount);
  }

  double getBalance() const { return balance_; }

private:
  double balance_;
  std::vector<std::shared_ptr<AccountObserver>> observers_;
};

class UIObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)type; (void)amount;
    std::cout << "[UI Observer] Balance display updated to $" << currentBalance << "\n";
  }
};

class EmailObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)type; (void)currentBalance;
    std::cout << "[Email Observer] Alert sent: A deposit of $" << amount << " was made.\n";
  }
};

class LoggerObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    std::cout << "[Logger Observer] Transaction logged: " << type 
              << " of $" << amount << ", new balance: $" << currentBalance << "\n";
  }
};

class FraudAIObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)type; (void)currentBalance;
    if (amount > 10000.0) {
      std::cout << "[Fraud AI] WARNING: Suspicious large deposit detected: $" << amount << "\n";
    } else {
      std::cout << "[Fraud AI] Scan complete: Deposit of $" << amount << " is marked OK.\n";
    }
  }
};

class MobileAppObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)type; (void)currentBalance;
    std::cout << "[Mobile App] Push: Account credited with $" << amount << "\n";
  }
};

class AnalyticsObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)currentBalance;
    std::cout << "[Analytics] Metric recorded: Event [" << type << "] for $" << amount << "\n";
  }
};

void runPatternDemo() {
  std::cout << "\n=== RUNNING PATTERN DEMO (With Observer Pattern) ===\n";
  BankAccount account(1000.0);

  auto ui = std::make_shared<UIObserver>();
  auto email = std::make_shared<EmailObserver>();
  auto logger = std::make_shared<LoggerObserver>();
  auto fraud = std::make_shared<FraudAIObserver>();
  auto mobile = std::make_shared<MobileAppObserver>();
  auto analytics = std::make_shared<AnalyticsObserver>();

  account.attach(ui);
  account.attach(email);
  account.attach(logger);
  account.attach(fraud);
  account.attach(mobile);
  account.attach(analytics);

  // First deposit: notifies all observers
  account.deposit(250.0);

  std::cout << "\n--- Dynamically detaching Email and Mobile App ---\n";
  account.detach(email);
  account.detach(mobile);

  // Second deposit: notifies remaining observers
  account.deposit(12000.0);
}