#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <stdexcept>

namespace pattern {

// Context maps variable names to boolean values
class Context {
public:
    void assign(const std::string& name, bool value) {
        variables_[name] = value;
    }

    bool lookup(const std::string& name) const {
        auto it = variables_.find(name);
        if (it == variables_.end()) {
            throw std::runtime_error("Variable not bound in Context: " + name);
        }
        return it->second;
    }

private:
    std::map<std::string, bool> variables_;
};

// Abstract Expression (Component in Interpreter Pattern)
class BooleanExpression {
public:
    virtual ~BooleanExpression() = default;
    virtual bool interpret(const Context& context) const = 0;
};

// Terminal Expression: Variable
class VariableExpression : public BooleanExpression {
public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    bool interpret(const Context& context) const override {
        return context.lookup(name_);
    }

private:
    std::string name_;
};

// Terminal Expression: Constant
class ConstantExpression : public BooleanExpression {
public:
    explicit ConstantExpression(bool value) : value_(value) {}

    bool interpret(const Context&) const override {
        return value_;
    }

private:
    bool value_;
};

// Non-Terminal Expression: AND Operator
class AndExpression : public BooleanExpression {
public:
    AndExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    bool interpret(const Context& context) const override {
        return left_->interpret(context) && right_->interpret(context);
    }

private:
    std::unique_ptr<BooleanExpression> left_;
    std::unique_ptr<BooleanExpression> right_;
};

// Non-Terminal Expression: OR Operator
class OrExpression : public BooleanExpression {
public:
    OrExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    bool interpret(const Context& context) const override {
        return left_->interpret(context) || right_->interpret(context);
    }

private:
    std::unique_ptr<BooleanExpression> left_;
    std::unique_ptr<BooleanExpression> right_;
};

// Non-Terminal Expression: NOT Operator
class NotExpression : public BooleanExpression {
public:
    explicit NotExpression(std::unique_ptr<BooleanExpression> operand)
        : operand_(std::move(operand)) {}

    bool interpret(const Context& context) const override {
        return !operand_->interpret(context);
    }

private:
    std::unique_ptr<BooleanExpression> operand_;
};

// Non-Terminal Expression: XOR Operator
class XorExpression : public BooleanExpression {
public:
    XorExpression(std::unique_ptr<BooleanExpression> left, std::unique_ptr<BooleanExpression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    bool interpret(const Context& context) const override {
        return left_->interpret(context) ^ right_->interpret(context);
    }

private:
    std::unique_ptr<BooleanExpression> left_;
    std::unique_ptr<BooleanExpression> right_;
};

} // namespace pattern

void runPatternDemo() {
    std::cout << "\n=== RUNNING INTERPRETER PATTERN DEMO (With AST Design Pattern) ===\n";
    pattern::Context context;
    context.assign("A", true);
    context.assign("B", false);
    context.assign("C", true);

    std::cout << "Context setup: A=true, B=false, C=true\n";

    // Build AST for expression: (A AND (NOT B)) OR (C XOR A)
    // std::unique_ptr enforces a strict Abstract Syntax Tree (AST) tree structure,
    // ensuring unique ownership per node (avoiding node sharing as in a DAG/ASG).
    auto notB = std::make_unique<pattern::NotExpression>(
        std::make_unique<pattern::VariableExpression>("B")
    );
    auto aAndNotB = std::make_unique<pattern::AndExpression>(
        std::make_unique<pattern::VariableExpression>("A"),
        std::move(notB)
    );
    auto cXorA = std::make_unique<pattern::XorExpression>(
        std::make_unique<pattern::VariableExpression>("C"),
        std::make_unique<pattern::VariableExpression>("A")
    );
    auto fullExpr = std::make_unique<pattern::OrExpression>(
        std::move(aAndNotB),
        std::move(cXorA)
    );

    std::cout << "AST built for expression: (A AND (NOT B)) OR (C XOR A)\n";
    bool result = fullExpr->interpret(context);
    std::cout << "Result: " << (result ? "true" : "false") << "\n";
    std::cout << "=== INTERPRETER PATTERN DEMO COMPLETED ===\n";
}
