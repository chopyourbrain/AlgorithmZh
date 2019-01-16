#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_btnGen_clicked();

  void on_btnCalcPlnZh_clicked();

private:
  Ui::MainWindow *ui;
  std::vector<std::vector<int> > vZh;
};

#endif // MAINWINDOW_H
