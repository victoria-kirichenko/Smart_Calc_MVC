#ifndef SRC_BACKEND_CONTROLLER_H_
#define SRC_BACKEND_CONTROLLER_H_
#include "model.h"
#include "modelcredit.h"
#include "validator.h"

namespace s21 {
class Controller {
 private:
  Model model_;
  Validator valid_;
  CreditCalc credit_;

 public:
  Controller() {}
  ~Controller() = default;
  Controller&& operator=(Controller&& o) = delete;

  double calculate(QString& str, const QString& x);
  std::pair<QVector<double>, QVector<double>> graph(QString& str,
                                                    std::vector<double>& data);
  QList<QString> credit(double credit_sum, double credit_period,
                        const int& type_period, double interest_rate,
                        const int& type_payment);

  QString ControlNumber(const QString& str, const QString& num);
  QString ControlUnar(const QString& str);
  QString ControlInputTrigonometry(const QString& str, const char* ban,
                                   const QString& input);
  QString ControlInputOperations(const QString& str, const QString& input);
  QString ControlDelete(const QString& label);
  QString ControlDot(const QString& str);
  void ControlX(const QString& x, bool check);
  void ControlCredit(const double& credit_sum_, const double& credit_period_,
                     const double& interest_rate_);
};
}  // namespace s21
#endif  // SRC_BACKEND_CONTROLLER_H_
