#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../Model/parcer.h"

namespace s21 {
class Controller {
 public:
  Controller();
  bool IsValid(const std::string& str);
  std::string Result(const std::string& str);

 private:
  Parcer model_;
};
}  // namespace s21

#endif  // CONTROLLER_H
