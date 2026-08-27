#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

namespace naive {

class Context {
public:
    void assign(const std::string& name, bool value) {
        variables_[name] = value;
    }

    bool lookup(const std::string& name) const {
        auto it = variables_.find(name);
        if (it == variables_.end()) {
            throw std::runtime_error("Variable not found in context: " + name);
        }
        return it->second;
    }

private:
    std::map<std::string, bool> variables_;
};

class NaiveLogicEvaluator {
public:
    // Evaluates flat left-to-right expressions (e.g. "A AND B OR C") without AST / operator precedence support
    static bool evaluate(const std::string& expression, const Context& context) {
        std::vector<std::string> tokens = tokenize(expression);
        if (tokens.empty()) return false;

        bool result = parseOperand(tokens[0], context);

        for (size_t i = 1; i + 1 < tokens.size(); i += 2) {
            const std::string& op = tokens[i];
            bool rhs = parseOperand(tokens[i + 1], context);

            if (op == "AND") {
                result = result && rhs;
            } else if (op == "OR") {
                result = result || rhs;
            } else if (op == "XOR") {
                result = result ^ rhs;
            } else {
                throw std::invalid_argument("Unsupported operator in naive evaluator: " + op);
            }
        }
        return result;
    }

private:
    static bool parseOperand(const std::string& token, const Context& context) {
        if (token == "true" || token == "1") return true;
        if (token == "false" || token == "0") return false;
        return context.lookup(token);
    }

    static std::vector<std::string> tokenize(const std::string& expression) {
        std::stringstream ss(expression);
        std::string token;
        std::vector<std::string> tokens;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

} // namespace naive

void runNaiveDemo() {
    std::cout << "\n=== RUNNING INTERPRETER NAIVE DEMO (Without Pattern) ===\n";
    naive::Context ctx;
    ctx.assign("A", true);
    ctx.assign("B", false);
    ctx.assign("C", true);

    std::cout << "Context: A=true, B=false, C=true\n";
    std::string expr1 = "A AND B";
    std::cout << "Evaluating '" << expr1 << "': " 
              << (naive::NaiveLogicEvaluator::evaluate(expr1, ctx) ? "true" : "false") << "\n";

    std::string expr2 = "A OR B AND C"; // Naive parses left-to-right: (A OR B) AND C
    std::cout << "Evaluating '" << expr2 << "' (Naive left-to-right evaluation): " 
              << (naive::NaiveLogicEvaluator::evaluate(expr2, ctx) ? "true" : "false") << "\n";
    std::cout << "Notice: Naive evaluator lacks true grammar structure, AST nodes, and flexible operator hierarchy.\n";
    std::cout << "=== INTERPRETER NAIVE DEMO COMPLETED ===\n";
}
