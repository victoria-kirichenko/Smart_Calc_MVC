#ifndef SRC_BACKEND_MODEL_H_
#define SRC_BACKEND_MODEL_H_

#include <math.h>

#include <sstream>
#include <stack>
#include <vector>

using std::stack;
using std::string;

namespace s21 {
class Model {
 public:
  Model();
  ~Model() = default;
  Model&& operator=(Model&& o) = delete;

  double calculate(string& str, double x);
  void valid(const string& str);

  int prior(char sim);
  double GetNumAndLen(string str, std::size_t* len);

  void IfClosedBracket(stack<double>& Num, stack<char>& Sim);
  void IfUnarWhenStackNumIsEmpty(stack<double>& Num, stack<char>& Sim,
                                 const char& ch, const double& x);
  void IfUnarWhenStackNumIsFill(stack<double>& Num, stack<char>& Sim,
                                const char& ch, const double& x,
                                const char& prev);
  void IfSimInputLessOrEgual(stack<double>& Num, stack<char>& Sim,
                             const char& ch);
  void CalculateNumOne(stack<double>* Num, stack<char>* Sim);
  void CalculateNumTwo(stack<double>* Num, stack<char>* Sim);
  double OperationOne(double& a, int sim);
  double OperationTwo(double& a, double& b, int sim);

  double get_data();

  std::pair<std::vector<double>, std::vector<double>> graph(
      string& str, std::vector<double>& data);

 private:
  double data_;

  static double SumOperation(double a, double b);
  static double SubOperation(double a, double b);
  static double MulOperation(double a, double b);
  static double DivOperation(double a, double b);
  static double ModOperation(double a, double b);
  static double SqrtOperation(double a);
  static double AsinOperation(double a);
  static double AcosOperation(double a);
  static double LogOperation(double a);
  static double LnOperation(double a);
};

}  // namespace s21
#endif  // SRC_BACKEND_MODEL_H_
