#include "controller.h"

using namespace s21;

double Controller::calculate(QString& str, const QString& x) {
  valid_.CheckInput(str);
  valid_.CheckX(x, 0);
  string label = valid_.converter(str);
  model_.calculate(label, x.toDouble());
  return model_.get_data();
}

std::pair<QVector<double>, QVector<double>> Controller::graph(
    QString& str, std::vector<double>& data) {
  valid_.CheckInput(str);
  string label = valid_.converter(str);
  std::pair<std::vector<double>, std::vector<double>> vect =
      model_.graph(label, data);
  std::pair<QVector<double>, QVector<double>> res;
  res.first = QVector<double>(vect.first.begin(), vect.first.end());
  res.second = QVector<double>(vect.second.begin(), vect.second.end());
  return res;
}

QList<QString> Controller::credit(double credit_sum, double credit_period,
                                  const int& type_period, double interest_rate,
                                  const int& type_payment) {
  return credit_.CreditCalculate(credit_sum, credit_period, type_period,
                                 interest_rate, type_payment);
}

QString Controller::ControlNumber(const QString& str, const QString& num) {
  return valid_.CheckNumber(str, num);
}

QString Controller::ControlUnar(const QString& str) {
  return valid_.CheckUnar(str);
}

QString Controller::ControlInputTrigonometry(const QString& str,
                                             const char* ban,
                                             const QString& input) {
  return valid_.CheckInputTrigonometry(str, ban, input);
}

QString Controller::ControlInputOperations(const QString& str,
                                           const QString& input) {
  return valid_.CheckInputOperations(str, input);
}

QString Controller::ControlDelete(const QString& label) {
  return valid_.CheckDelete(label);
}

QString Controller::ControlDot(const QString& str) {
  return valid_.CheckDot(str);
}

void Controller::ControlX(const QString& x, bool check) {
  valid_.CheckX(x, check);
}

void Controller::ControlCredit(const double& credit_sum_,
                               const double& credit_period_,
                               const double& interest_rate_) {
  valid_.CheckCredit(credit_sum_, credit_period_, interest_rate_);
}
