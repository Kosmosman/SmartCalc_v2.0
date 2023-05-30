#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <utility>
#include <vector>

#include "../Model/parcer.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  bool IsValid(const std::string& str);
  std::string Result(const std::string& str, const std::string& x);
  std::pair<std::vector<double>, std::vector<double>> CreateDots(
      const std::string& str, std::pair<int, int> x_borders,
      std::pair<int, int> y_borders);

 private:
  Parcer model_;
};
}  // namespace s21

#endif  // CONTROLLER_H
