#ifndef SRC_BACKEND_VALIDATOR_H_
#define SRC_BACKEND_VALIDATOR_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <QVector>

using std::string;

namespace s21 {
class Validator {
 public:
  Validator() {}
  ~Validator() = default;
  Validator&& operator=(Validator&& o) = delete;

  QString CheckNumber(const QString& str, const QString& num);
  QString CheckUnar(const QString& str);
  QString CheckInputTrigonometry(const QString& str, const char* ban,
                                 const QString& input);
  QString CheckInputOperations(const QString& str, const QString& input);
  QString CheckDelete(const QString& label);
  void CheckX(const QString& x, int check);
  void CheckInput(const QString& str);
  QString CheckDot(const QString& str);
  void CheckCredit(const double& credit_sum_, const double& credit_period_,
                   const double& interest_rate_);

  string converter(QString& str);
  QString RemovePartOfStr(const QString& str, const QString& del, int a, int b,
                          int c);

 private:
  QVector<QString> lexeme;
};

}  // namespace s21

#endif  // SRC_BACKEND_VALIDATOR_H_
