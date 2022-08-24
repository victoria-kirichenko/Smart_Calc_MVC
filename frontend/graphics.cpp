#include "graphics.h"

#include "ui_graphics.h"

using namespace s21;

Graphics::Graphics(QWidget* parent) : QDialog(parent), ui(new Ui::Graphics) {
  ui->setupUi(this);
}

Graphics::~Graphics() { delete ui; }

void Graphics::on_pushButton_draw_clicked() {
  try {
    data_.clear();
    dots_.first.clear();
    dots_.second.clear();
    controller_.ControlX(ui->d_y->text(), 1);
    controller_.ControlX(ui->e_y->text(), 1);
    controller_.ControlX(ui->x_max->text(), 1);
    controller_.ControlX(ui->x_min->text(), 0);
    controller_.ControlX(ui->butt_step->text(), 1);
    data_.push_back(ui->d_y->text().toDouble());
    data_.push_back(ui->e_y->text().toDouble());
    data_.push_back(ui->x_max->text().toDouble());
    data_.push_back(ui->x_min->text().toDouble());
    data_.push_back(ui->butt_step->text().toDouble());
    dots_ = controller_.graph(label_, data_);
  } catch (const std::exception& ex) {
    return;
  }

  ui->widget->clearGraphs();
  double d_y = ui->d_y->text().toDouble();
  double e_y = ui->e_y->text().toDouble();

  ui->widget->xAxis->setRange(-1 * d_y, d_y);
  ui->widget->yAxis->setRange(-1 * e_y, e_y);

  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(dots_.first, dots_.second);
  ui->widget->graph(0)->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCross, 4.0));
  ui->widget->replot();

  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

void Graphics::slot(QString text) {
  label_.clear();
  label_ = text;
  ui->func->setText(text);
}
