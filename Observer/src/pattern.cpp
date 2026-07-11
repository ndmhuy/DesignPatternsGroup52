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
    std::cout << "[BankAccount] Deposited $" << amount << ". New balance: $" << balance_ << "\n";
    notify("Deposit", amount);
  }
  void withdraw(double amount) {
    if (amount > balance_) {
      std::cout << "[BankAccount] Rejected: Insufficient funds for withdrawal of $" << amount << "\n";
      notify("FailedWithdrawal", amount);
    } else {
      balance_ -= amount;
      std::cout << "[BankAccount] Withdrew $" << amount << ". New balance: $" << balance_ << "\n";
      notify("Withdrawal", amount);
    }
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
    (void)currentBalance;
    if (type == "Deposit") {
      std::cout << "[Email Observer] Alert sent: A deposit of $" << amount << " was made.\n";
    } else if (type == "Withdrawal") {
      std::cout << "[Email Observer] Alert sent: A withdrawal of $" << amount << " was made.\n";
    } else if (type == "FailedWithdrawal") {
      std::cout << "[Email Observer] Security Alert: A withdrawal of $" << amount << " failed due to insufficient funds.\n";
    }
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
    (void)currentBalance;
    if (amount > 10000.0) {
      std::cout << "[Fraud AI] WARNING: Suspicious large activity detected: " << type << " of $" << amount << "\n";
    } else {
      std::cout << "[Fraud AI] Scan complete: " << type << " of $" << amount << " is marked OK.\n";
    }
  }
};

class MobileAppObserver : public AccountObserver {
public:
  void onTransaction(const std::string &type, double amount,
                     double currentBalance) override {
    (void)currentBalance;
    if (type == "Deposit") {
      std::cout << "[Mobile App] Push: Account credited with $" << amount << "\n";
    } else if (type == "Withdrawal") {
      std::cout << "[Mobile App] Push: Account debited with $" << amount << "\n";
    } else if (type == "FailedWithdrawal") {
      std::cout << "[Mobile App] Alert: Withdrawal of $" << amount << " failed (Insufficient Funds).\n";
    }
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

void pressEnterToContinue() {
  std::cout << "[Press Enter to continue...]\n";
  std::cin.get();
}

void runPatternDemo() {
  std::cout << "\n=== RUNNING PATTERN DEMO (With Observer Pattern) ===\n";
  
  std::cout << "Step 1: Initializing BankAccount with $1000.00...\n";
  BankAccount account(1000.0);
  pressEnterToContinue();

  std::cout << "Step 2: Attaching observers...\n";
  std::cout << " - UIObserver (updates screen balance display)\n";
  std::cout << " - EmailObserver (sends transaction notification emails)\n";
  std::cout << " - LoggerObserver (writes to security/audit logs)\n";
  std::cout << " - FraudAIObserver (scans transaction amounts, warns if > $10,000)\n";
  std::cout << " - MobileAppObserver (sends push notification)\n";
  std::cout << " - AnalyticsObserver (records activity metrics)\n";
  
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
  pressEnterToContinue();

  std::cout << "Step 3: Depositing $250.00. Expecting notifications to ALL 6 systems...\n\n";
  account.deposit(250.0);
  std::cout << "\n";
  pressEnterToContinue();

  std::cout << "Step 4: Dynamically detaching Email and Mobile App observers...\n";
  std::cout << " (Customer disabled Email alerts and Mobile pushes in settings)\n";
  account.detach(email);
  account.detach(mobile);
  pressEnterToContinue();

  std::cout << "Step 5: Depositing $12000.00. Expecting notifications to remaining systems...\n";
  std::cout << " (No Email, No Mobile push. Fraud AI alert should trigger for large amount)\n\n";
  account.deposit(12000.0);
  std::cout << "\n";
  pressEnterToContinue();

  std::cout << "Step 6: Customer re-enables Mobile App notifications in settings...\n";
  std::cout << " (Attaching MobileAppObserver back to BankAccount)\n";
  account.attach(mobile);
  pressEnterToContinue();

  std::cout << "Step 7: Withdrawing $500.00. Expecting notifications to UI, Logger, Fraud AI, Analytics, AND Mobile App (Email remains disabled)...\n\n";
  account.withdraw(500.0);
  std::cout << "\n";
  pressEnterToContinue();

  std::cout << "Step 8: Attempting to withdraw $15000.00 (which exceeds current balance of $12750.00)...\n";
  std::cout << " (Expecting Insufficient Funds failure alerts to UI, Logger, Fraud AI, Analytics, and Mobile App)\n\n";
  account.withdraw(15000.0);
  std::cout << "\n";
  pressEnterToContinue();

  std::cout << "=== PATTERN DEMO COMPLETED ===\n";
}