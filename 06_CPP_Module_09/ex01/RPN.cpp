#include "RPN.hpp"
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN &other) { *this = other; }

RPN &RPN::operator=(const RPN &other) {
  if (this != &other) {
    _stack = other._stack;
  }
  return *this;
}

RPN::~RPN() {}

bool RPN::_isOperator(const std::string &token) {
  return (token == "+" || token == "-" || token == "*" || token == "/");
}

void RPN::_performOp(const std::string &op) {
  if (_stack.size() < 2) {
    throw std::runtime_error("Error");
  }
  int b = _stack.top();
  _stack.pop();
  int a = _stack.top();
  _stack.pop();

  if (op == "+")
    _stack.push(a + b);
  else if (op == "-")
    _stack.push(a - b);
  else if (op == "*")
    _stack.push(a * b);
  else if (op == "/") {
    if (b == 0)
      throw std::runtime_error("Error"); // Div by zero
    _stack.push(a / b);
  }
}

void RPN::calculate(const std::string &expression) {
  std::stringstream ss(expression);
  std::string token;

  while (ss >> token) {
    if (_isOperator(token)) {
      _performOp(token);
    } else {
      // Check if number < 10
      char *end;
      long val = std::strtol(token.c_str(), &end, 10);
      if (*end != '\0' || val >= 10) { // Subject says numbers < 10
        throw std::runtime_error("Error");
      }
      _stack.push(static_cast<int>(val));
    }
  }
  if (_stack.size() != 1) {
    throw std::runtime_error("Error");
  }
  std::cout << _stack.top() << std::endl;
}
