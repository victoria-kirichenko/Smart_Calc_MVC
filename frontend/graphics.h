#ifndef SRC_FRONTEND_GRAPHICS_H_
#define SRC_FRONTEND_GRAPHICS_H_

#include "../backend/controller.h"

using std::string;

#include <QDialog>

namespace Ui {
class Graphics;
}

namespace s21 {
class Graphics : public QDialog {
  Q_OBJECT

 public:
  explicit Graphics(QWidget *parent = nullptr);
  ~Graphics();

 private slots:

  void on_pushButton_draw_clicked();

 private:
  Ui::Graphics *ui;
  QString label_;
  Controller controller_;
  std::pair<QVector<double>, QVector<double>> dots_;
  std::vector<double> data_;

 public slots:
  void slot(QString text);
};

}  // namespace s21
#endif  // SRC_FRONTEND_GRAPHICS_H_
