#include "controller.h"

namespace s21 {
bool Controller::IsValid(const std::string& str, const std::string& x) {
  return model_(str, x).IsValideExpression();
};

std::string Controller::Result() { return std::to_string(model_.Answer()); }

std::pair<std::vector<double>, std::vector<double>> Controller::CreateDots(
    const std::string& str, std::pair<int, int>& x_borders,
    std::pair<int, int>& y_borders) {
  return model_.CreateDots(str, x_borders, y_borders);
};

};  // namespace s21
