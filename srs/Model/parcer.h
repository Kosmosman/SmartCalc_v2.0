#ifndef CPP_SMARTCALC_V2_SRC_MODEL_PARCER_H_
#define CPP_SMARTCALC_V2_SRC_MODEL_PARCER_H_

#include <cmath>
#include <cstring>
#include <stack>
#include <string>
#include <utility>

namespace s21 {
class Parcer {
 public:
  Parcer(){};
  explicit Parcer(const std::string& str) : expression_{str} { ReadString(); };
  Parcer(const Parcer& other)
      : expression_{other.expression_},
        num_stack_{other.num_stack_},
        op_stack_{other.op_stack_},
        is_valid_{other.is_valid_} {};
  Parcer(Parcer&& other)
      : expression_{std::move(other.expression_)},
        num_stack_{std::move(other.num_stack_)},
        op_stack_{std::move(other.op_stack_)},
        is_valid_{std::move(other.is_valid_)} {};
  ~Parcer(){};

  Parcer& operator=(const Parcer& other);
  Parcer& operator=(Parcer&& other) noexcept;
  Parcer& operator()(const std::string& str);

  double Answer() const noexcept { return is_valid_ ? num_stack_.top() : 0; };
  bool IsValideExpression() const noexcept { return is_valid_; };

 private:
  size_t TakePriority(const std::string& op) noexcept;
  void ChooseCalculateMode();
  void Validator();
  double ReadString();
  void AddToStack(std::string& buffer);
  void OperationMode();
  void FunctionMode();
  void Calculate(const std::string& str, size_t priority);
  void CheckDigit(char** ptr, char* end);
  void CheckFunction(char** ptr, char* end);
  bool CheckCorrectFunction(const std::string& str);
  void CheckOperator(char** ptr, char* end);
  bool CheckCorrectOperator(const std::string& str);
  bool CheckPow(const std::string& buffer) const noexcept;
  void CheckUnary(const size_t& priority) noexcept;
  void Clear();

  std::string expression_{};
  std::stack<double> num_stack_{};
  std::stack<std::pair<std::string, size_t> > op_stack_{};
  bool is_valid_{true};
  bool digit_last_{};
};
}  // namespace s21

#endif  // CPP_SMARTCALC_V2_SRC_MODEL_PARCER_H_
