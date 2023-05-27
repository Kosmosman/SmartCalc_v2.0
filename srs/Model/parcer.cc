#include "parcer.h"

namespace s21 {

Parcer& Parcer::operator=(const Parcer& other) {
  expression_ = other.expression_;
  num_stack_ = other.num_stack_;
  op_stack_ = other.op_stack_;
  is_valid_ = other.is_valid_;
  return *this;
};
Parcer& Parcer::operator=(Parcer&& other) noexcept {
  expression_ = std::move(other.expression_);
  num_stack_ = std::move(other.num_stack_);
  op_stack_ = std::move(other.op_stack_);
  is_valid_ = std::move(other.is_valid_);
  return *this;
};

void Parcer::Calculate(const std::string& str, size_t priority) {
  if (str == ")") {
    while (!op_stack_.empty() && op_stack_.top().first != "(")
      ChooseCalculateMode();
    op_stack_.pop();
    if (!op_stack_.empty() && op_stack_.top().second == 4) {
      FunctionMode();
    };
  } else {
    while (!op_stack_.empty() && op_stack_.top().second >= priority)
      ChooseCalculateMode();
  }
};

void Parcer::ChooseCalculateMode() {
  if (num_stack_.size() > 1 && op_stack_.top().second < 4)
    OperationMode();
  else if (num_stack_.size() > 0 && op_stack_.top().second == 4)
    FunctionMode();
};

double Parcer::ReadString() {
  char* ptr{&expression_[0]};
  char* end{&expression_[expression_.size()]};
  Validator();
  if (is_valid_) {
    while (is_valid_ && ptr != end) {
      CheckDigit(&ptr, end);
      CheckFunction(&ptr, end);
      CheckOperator(&ptr, end);
    }
    while (!op_stack_.empty() && !num_stack_.empty()) ChooseCalculateMode();
    if (!op_stack_.empty() || num_stack_.empty()) is_valid_ = false;
  }
  return num_stack_.empty() ? 0 : num_stack_.top();
};

void Parcer::AddToStack(std::string& buffer) {
  if (!buffer.empty()) {
    size_t new_priority = TakePriority(buffer);
    CheckUnary(buffer, new_priority);
    if (buffer != "(" && CheckPow(buffer)) Calculate(buffer, new_priority);
    if (buffer != ")") op_stack_.push({buffer, new_priority});
    buffer.clear();
  }
};

size_t Parcer::TakePriority(const std::string& op) noexcept {
  size_t priority{};
  if (op.find_first_of("()") != (size_t)-1) {
    priority = 0;
  } else if (op.find_first_of("+-") != (size_t)-1) {
    priority = 1;
  } else if (op.find_first_of("*/%") != (size_t)-1) {
    priority = 2;
  } else if (op.find_first_of("^") != (size_t)-1) {
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
  else if (op == "^")
    num_stack_.push(std::pow(first, second));
  else if (op == "%")
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
  bool has_dot{};
  for (auto it : expression_) {
    if (it == '(')
      ++bracer;
    else if (it == ')')
      --bracer;
    else if (prev && std::strchr("+-*/%^", prev) && std::strchr("+-*/%^", it))
      is_valid_ = false;
    else if ((!prev || prev == '(') && std::strchr("*/%^", it))
      is_valid_ = false;
    else if (prev && prev == ')' && std::isdigit(it))
      is_valid_ = false;
    if (bracer < 0) is_valid_ = false;
    if (it == '.' && has_dot) is_valid_ = false;
    if (!std::isdigit(it) && it != '.') has_dot = false;
    if (it == '.') has_dot = true;
    prev = it;
  }
  if (prev && std::strchr("+-*/%^", prev)) is_valid_ = false;
};

void Parcer::CheckDigit(char** ptr, char* end) {
  std::string buffer{};
  while (*ptr != end && (std::isdigit(**ptr) || **ptr == '.'))
    buffer += *((*ptr)++);
  if (!buffer.empty()) {
    num_stack_.push(std::stod(buffer));
    digit_last_ = true;
  }
};
void Parcer::CheckFunction(char** ptr, char* end) {
  std::string buffer{};
  while (*ptr != end && std::isalpha(**ptr)) buffer += *((*ptr)++);
  if (!buffer.empty()) {
    AddToStack(buffer);
    digit_last_ = false;
  }
};

void Parcer::CheckOperator(char** ptr, char* end) {
  std::string buffer{};
  if (*ptr != end && std::ispunct(**ptr) && **ptr != '.') buffer += *((*ptr)++);
  if (!buffer.empty()) {
    AddToStack(buffer);
    digit_last_ = false;
  }
};

bool Parcer::CheckPow(const std::string& buffer) const noexcept {
  return op_stack_.empty() || op_stack_.top().first != "^" || buffer != "^";
};

// Унарный знак мы ставим в двух случаях: в начале выражения и после открывающей
// скобки. Также проверяем, что унарный знак ставится сразу после (. Если
// условия выполняются, то мы отправляем в стак с числами 0 для корректного
// подсчета
void Parcer::CheckUnary(const std::string& buffer,
                        const size_t& priority) noexcept {
  if ((num_stack_.empty() ||
       (!op_stack_.empty() && op_stack_.top().first == "(")) &&
      priority == 1 && !digit_last_) {
    num_stack_.push(0);
  }
};

}  // namespace s21
