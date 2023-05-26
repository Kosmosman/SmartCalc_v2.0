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
  Parcer();
  Parcer(const std::string& str) : expression_{str} {};
  ~Parcer();

 private:
  size_t TakePriority(const std::string& op);
  void ChooseCalculateMode(size_t priority);
  void Validator();
  void ReadString();
  void AddToStack(std::string& buffer);
  void OperationMode();
  void FunctionMode();
  void Calculate(const std::string& str, size_t priority);

  std::string expression_{};
  std::stack<double> num_stack_{};
  std::stack<std::pair<std::string, size_t> > op_stack_{};
  bool is_valid_{true};
};
}  // namespace s21

#endif  // CPP_SMARTCALC_V2_SRC_MODEL_PARCER_H_