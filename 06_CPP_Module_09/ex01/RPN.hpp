#ifndef RPN_HPP
#define RPN_HPP

#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>


class RPN {
private:
  std::stack<int> _stack;
  bool _isOperator(const std::string &token);
  void _performOp(const std::string &op);

public:
  RPN();
  RPN(const RPN &other);
  RPN &operator=(const RPN &other);
  ~RPN();

  void calculate(const std::string &expression);
};

#endif
