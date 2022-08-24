#include "modelcredit.h"

using namespace s21;

QList<QString> CreditCalc::CreditCalculate(double credit_sum,
                                           double credit_period,
                                           const int& type_period,
                                           double interest_rate,
                                           const int& type_payment) {
  QList<QString> res;
  double first_sum = 0, last_sum = 0;
  data_.pp = interest_rate / (100 * 12);
  data_.credit_sum = credit_sum;
  data_.credit_period = (type_period == 0) ? credit_period * 12 : credit_period;

  if (type_payment == 0) {
    AnnuitPayment();
    res.push_back(ConvertStr(data_.monthly_payment));
  } else {
    DiffPayment(first_sum, last_sum);
    res.push_back(ConvertStr(first_sum));
    res[0].append("...");
    res[0].append(ConvertStr(last_sum));
  }

  RoundingNum(data_.overpayment);
  RoundingNum(data_.total_payment);
  res.push_back(ConvertStr(data_.overpayment));
  res.push_back(ConvertStr(data_.total_payment));
  data_.overpayment = 0;
  data_.total_payment = 0;
  return res;
}

void CreditCalc::AnnuitPayment() {
  data_.monthly_payment =
      data_.credit_sum *
      (data_.pp / (1 - pow((1 + data_.pp), -data_.credit_period)));
  RoundingNum(data_.monthly_payment);
  data_.overpayment =
      (data_.monthly_payment * data_.credit_period) - data_.credit_sum;
  data_.total_payment = data_.credit_sum + data_.overpayment;
}

void CreditCalc::DiffPayment(double& first_sum, double& last_sum) {
  double ostatok = 0, main_payment = 0, proc = 0;
  for (int i = 0; i < data_.credit_period; ++i) {
    main_payment = data_.credit_sum / data_.credit_period;
    ostatok = data_.credit_sum - (main_payment * i);
    proc = ostatok * data_.pp;
    data_.monthly_payment = main_payment + proc;
    data_.overpayment += proc;
    if (i == 0) {
      first_sum = data_.monthly_payment;
    }
    data_.total_payment = data_.credit_sum + data_.overpayment;
  }
  last_sum = data_.monthly_payment;
  RoundingNum(last_sum);
  RoundingNum(first_sum);
}

void CreditCalc::RoundingNum(double& num) { num = round(num * 100) / 100; }

QString CreditCalc::ConvertStr(const double& num) {
  QString str = QString::number(num, 'g', 15);
  return str;
}
