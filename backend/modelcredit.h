#ifndef SRC_BACKEND_MODELCREDIT_H_
#define SRC_BACKEND_MODELCREDIT_H_
#include <math.h>

#include <QList>
#include <QStringList>
#include <sstream>
#include <stack>

namespace s21 {
class CreditCalc {
 public:
  CreditCalc() {}
  ~CreditCalc() = default;
  CreditCalc&& operator=(CreditCalc&& o) = delete;

  QList<QString> CreditCalculate(double credit_sum, double credit_period,
                                 const int& type_period, double interest_rate,
                                 const int& type_payment);
  void AnnuitPayment();
  void DiffPayment(double& first_sum, double& last_sum);
  void RoundingNum(double& num);
  QString ConvertStr(const double& num);

 private:
  struct Data {
    double monthly_payment = 0;
    double overpayment = 0;
    double total_payment = 0;
    double credit_sum = 0;
    double pp = 0;
    double credit_period = 0;
  } data_;
};

}  // namespace s21
#endif  // SRC_BACKEND_MODELCREDIT_H_
