#include "parcer.h"

namespace s21 {

void Parcer::Calculate(const std::string& str, size_t priority) {
  if (str == ")") {
    while (op_stack_.top().first != "(" && !op_stack_.empty())
      ChooseCalculateMode(priority);
    op_stack_.pop();
  } else if (str != "(") {
    while (op_stack_.top().second >= priority && !op_stack_.empty())
      ChooseCalculateMode(priority);
  }
};

void Parcer::ChooseCalculateMode(size_t priority) {
  if (num_stack_.size() > 1 && op_stack_.top().second < 4)
    OperationMode();
  else if (num_stack_.size() > 0 && op_stack_.top().second == 4)
    FunctionMode();
};

void Parcer::ReadString() {
  std::string buffer{};
  bool number_mode{};
  Validator();
  if (is_valid_) {
    for (auto it : expression_) {
      if (!number_mode && (std::isdigit(it) || it == '.')) {
        number_mode = true;
        AddToStack(buffer);
      } else if (number_mode && std::isalpha(it)) {
        number_mode = false;
        AddToStack(buffer);
      } else {
        number_mode = true;
        AddToStack(buffer);
        buffer += it;
        AddToStack(buffer);
      }
      buffer += it;
      if (!is_valid_) break;
    }
  }
};

void Parcer::AddToStack(std::string& buffer) {
  if (!buffer.empty()) {
    if (std::isdigit(buffer[0]) || buffer[0] == '.') {
      num_stack_.push(std::stod(buffer));
    } else {
      size_t new_priority = TakePriority(buffer);
      Calculate(buffer, new_priority);
      if (buffer != ")") op_stack_.push({buffer, new_priority});
    }
    buffer.clear();
  }
};

size_t Parcer::TakePriority(const std::string& op) {
  size_t priority{};
  if (op.find_first_of("()") != -1) {
    priority = 0;
  } else if (op.find_first_of("+-") != -1) {
    priority = 1;
  } else if (op.find_first_of("*/m") != -1) {
    priority = 2;
  } else if (op.find_first_of("^") != -1) {
    priority = 3;
  } else {
    priority = 4;
  }
  return priority;
};

void Parcer::OperationMode() {
  double second = num_stack_.top();
  num_stack_.pop();
  double first = num_stack_.top();
  num_stack_.pop();
  std::string op = op_stack_.top().first;
  op_stack_.pop();
  if (op == "+")
    num_stack_.push(first + second);
  else if (op == "-")
    num_stack_.push(first - second);
  else if (op == "*")
    num_stack_.push(first * second);
  else if (op == "/")
    num_stack_.push(first / second);
  else if (op == "mod")
    num_stack_.push(std::fmod(first, second));
  else
    is_valid_ = false;
};

void Parcer::FunctionMode() {
  double first = num_stack_.top();
  num_stack_.pop();
  std::string op = op_stack_.top().first;
  op_stack_.pop();
  if (op == "sin")
    num_stack_.push(std::sin(first));
  else if (op == "cos")
    num_stack_.push(std::cos(first));
  else if (op == "tan")
    num_stack_.push(std::tan(first));
  else if (op == "asin")
    num_stack_.push(std::asin(first));
  else if (op == "acos")
    num_stack_.push(std::acos(first));
  else if (op == "atan")
    num_stack_.push(std::atan(first));
  else if (op == "sqrt")
    num_stack_.push(std::sqrt(first));
  else if (op == "ln")
    num_stack_.push(std::log(first));
  else if (op == "log")
    num_stack_.push(std::log10(first));
  else
    is_valid_ = false;
};

void Parcer::Validator() {
  int bracer{};
  char prev{};
  for (auto it : expression_) {
    if (it == '(')
      ++bracer;
    else if (it == ')')
      --bracer;
    else if (prev && prev == '.' && it == '.')
      is_valid_ = false;
    else if (prev && std::strchr("+-*/%^", prev) && std::strchr("+-*/%^", it))
      is_valid_ = false;
    else if ((!prev || prev == '(') && std::strchr("*/%^", it))
      is_valid_ = false;
    else if (prev && prev == ')' && std::isdigit(it))
      is_valid_ = false;
    if (bracer < 0) is_valid_ = false;
  }
};

}  // namespace s21