#include "credit.h"

#include "ui_credit.h"

using namespace s21;

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->max_rate->setVisible(false);
  ui->max_period->setVisible(false);
}

Credit::~Credit() { delete ui; }

void Credit::on_butt_calculate_clicked() {
  try {
    controller_.ControlX(ui->credit_sum->text(), 2);
    controller_.ControlX(ui->credit_period->text(), 2);
    controller_.ControlX(ui->interest_rate->text(), 2);
    type_period_ = ui->combo_credit_period->currentIndex();
    type_payment_ = ui->type_payment->currentIndex();
    credit_sum_ = ui->credit_sum->text().toDouble();
    credit_period_ = ui->credit_period->text().toDouble();
    interest_rate_ = ui->interest_rate->text().toDouble();
    controller_.ControlCredit(credit_sum_, credit_period_, interest_rate_);
    QList<QString> res =
        controller_.credit(credit_sum_, credit_period_, type_period_,
                           interest_rate_, type_payment_);
    ui->monthly_payment->setText(res[0]);
    ui->butt_overpayment->setText(res[1]);
    ui->total_payment->setText(res[2]);
  } catch (const std::exception &ex) {
    ui->monthly_payment->setText("Invalid Input!");
    ui->butt_overpayment->setText("Invalid Input!");
    ui->total_payment->setText("Invalid Input!");
  }
}

void Credit::on_interest_rate_textChanged(const QString &arg1) {
  if (arg1.toDouble() > 999 || arg1.toDouble() < 0.01) {
    ui->max_rate->setVisible(true);
  } else {
    ui->max_rate->setVisible(false);
  }
}

void Credit::on_credit_period_textChanged(const QString &arg1) {
  if (arg1.toDouble() > 50 || arg1.toDouble() < 1) {
    ui->max_period->setVisible(true);
  } else {
    ui->max_period->setVisible(false);
  }
}
