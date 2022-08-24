#ifndef SRC_FRONTEND_CONSOLEVIEW_H_
#define SRC_FRONTEND_CONSOLEVIEW_H_

#include <QMainWindow>
#include <QVector>

#include "../backend/controller.h"
#include "credit.h"
#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ConsoleView;
}
QT_END_NAMESPACE

namespace s21 {
class ConsoleView : public QMainWindow {
  Q_OBJECT

 public:
  explicit ConsoleView(QWidget *parent = nullptr);
  ~ConsoleView();

 private:
  Ui::ConsoleView *ui;
  Controller controller_;
  Graphics *window_;
  Credit *window2_;

 signals:
  void signal(QString);

 private slots:
  void digits_numbers();
  void operations();
  void functions();
  void on_pushButton_dot_clicked();
  void on_pushButton_res_clicked();
  void on_pushButton_ac_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_graph_clicked();
  void on_e_plus_clicked();
  void on_e_minus_clicked();
  void on_pushButton_unar_clicked();
  void on_pushButton_left_clicked();
  void on_pushButton_right_clicked();
  void on_butt_credit_clicked();
};
}  // namespace s21
#endif  // SRC_FRONTEND_CONSOLEVIEW_H_
