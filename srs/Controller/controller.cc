#include "controller.h"

namespace s21 {
bool Controller::IsValid(const std::string& str) {
  return model_(str, "0").IsValideExpression();
};

std::string Controller::Result(const std::string& str, const std::string& x) {
  return std::to_string(model_(str, x).Answer());
}

std::pair<std::vector<double>, std::vector<double>> Controller::CreateDots(
    const std::string& str, std::pair<int, int> x_borders,
    std::pair<int, int> y_borders) {
  return model_.CreateDots(str, x_borders, y_borders);
};

};  // namespace s21
