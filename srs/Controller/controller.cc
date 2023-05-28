#include "controller.h"

namespace s21 {
Controller::Controller(){};

bool Controller::IsValid(const std::string& str) {
  return model_(str).IsValideExpression();
};
std::string Controller::Result(const std::string& str) {
  return std::to_string(model_(str).Answer());
};
};  // namespace s21
