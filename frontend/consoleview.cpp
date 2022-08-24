#include "consoleview.h"

#include <QDebug>
#include <QDir>
#include <QStringList>
#include <iostream>

#include "ui_consoleview.h"

using namespace s21;

ConsoleView::ConsoleView(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::ConsoleView) {
  ui->setupUi(this);
  window_ = new Graphics(this);
  window2_ = new Credit(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_umn, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(this, &ConsoleView::signal, window_, &Graphics::slot);
}

ConsoleView::~ConsoleView() { delete ui; }

void ConsoleView::digits_numbers() {
  QPushButton* button = (QPushButton*)sender();
  QString label = ui->result_show->text();
  label = controller_.ControlNumber(label, button->text());
  ui->result_show->setText(label);
}

void ConsoleView::operations() {
  QPushButton* button = (QPushButton*)sender();
  QString label = ui->result_show->text();
  label = controller_.ControlInputOperations(label, button->text());
  ui->result_show->setText(label);
}

void ConsoleView::functions() {
  QPushButton* button = (QPushButton*)sender();
  QString label = ui->result_show->text();
  char ban[] = ")0123456789.xnsg";
  label =
      controller_.ControlInputTrigonometry(label, ban, button->text() + "(");
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_dot_clicked() {
  QString label = ui->result_show->text();
  label = controller_.ControlDot(label);
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_unar_clicked() {
  QString label = ui->result_show->text();
  label = controller_.ControlUnar(label);
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_left_clicked() {
  QString label = ui->result_show->text();
  char ban[] = ")0123456789.x";
  label = controller_.ControlInputTrigonometry(label, ban, "(");
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_right_clicked() {
  QString label = ui->result_show->text();
  char ban[] = "+-/*^d(.";
  label = controller_.ControlInputTrigonometry(label, ban, ")");
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_x_clicked() {
  QString label = ui->result_show->text();
  char ban[] = ")0123456789.xnsg";
  label = controller_.ControlInputTrigonometry(label, ban, "x");
  ui->result_show->setText(label);
}

void ConsoleView::on_e_plus_clicked() {
  QString label = ui->result_show->text();
  char ban[] = ".x)";
  label = controller_.ControlInputTrigonometry(label, ban, "e+");
  ui->result_show->setText(label);
}

void ConsoleView::on_e_minus_clicked() {
  QString label = ui->result_show->text();
  char ban[] = ".x)";
  label = controller_.ControlInputTrigonometry(label, ban, "e-");
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_delete_clicked() {
  QString label = ui->result_show->text();
  label = controller_.ControlDelete(label);
  ui->result_show->setText(label);
}

void ConsoleView::on_pushButton_ac_clicked() { ui->result_show->setText("0"); }

void ConsoleView::on_pushButton_res_clicked() {
  QString label = ui->result_show->text();
  QString x = ui->x_data->text();
  try {
    double res = controller_.calculate(label, x);
    QString result = QString::number(res, 'g', 15);
    ui->result_show->setText(result);
  } catch (const std::exception& ex) {
    ui->result_show->setText(ex.what());
  }
}

void ConsoleView::on_pushButton_graph_clicked() {
  window_->show();
  emit signal(ui->result_show->text());
}

void ConsoleView::on_butt_credit_clicked() { window2_->show(); }
