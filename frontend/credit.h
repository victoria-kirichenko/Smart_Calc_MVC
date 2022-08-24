#ifndef SRC_FRONTEND_CREDIT_H_
#define SRC_FRONTEND_CREDIT_H_

#include <QDialog>

#include "../backend/controller.h"
#include "../backend/validator.h"

namespace Ui {
class Credit;
}

namespace s21 {
class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_butt_calculate_clicked();

  void on_interest_rate_textChanged(const QString &arg1);

  void on_credit_period_textChanged(const QString &arg1);

 private:
  Ui::Credit *ui;
  CreditCalc credit_;
  Controller controller_;
  int type_payment_;
  int type_period_;
  double credit_sum_ = 0.01;
  double credit_period_ = 1;
  double interest_rate_ = 0.01;
};
}  // namespace s21
#endif  // SRC_FRONTEND_CREDIT_H_
