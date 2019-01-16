#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chym.h"
#include "kvector.h"
#include <string>

#include <QStandardItemModel>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
//  QSplitter *splt = new QSplitter(ui->SplitWidget);
//  splt->addWidget(ui->verticalWidget);
//  splt->addWidget(ui->verticalWidget_2);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_btnGen_clicked()
{
  chym my(ui->spLength->value(), ui->sbRank->value());
  my.sort();

  const int M = ui->spLength->value();
  QStandardItemModel *model = new QStandardItemModel(my.m_nSize,my.m_nLength,this); //2 Rows and 3 Columns

  ui->tableView->setModel(model);

  for (int j = 0; j < my.m_nLength; ++j)
  {
      model->setHorizontalHeaderItem(j, new QStandardItem(QString("X") + QString::number(j)));
  }

  for (int i =0 ; i < my.m_nSize; ++i)
  {
    for (int j = 0; j < my.m_nLength; ++j)
    {
        QStandardItem *Row = new QStandardItem(QString::number(my.get(i,j)) );
        model->setItem(i,j,Row);
    }
  }

  model->setHorizontalHeaderItem(my.m_nLength, new QStandardItem(QString("F")));

// std::vector<int> F = {0,3,1,2,0,1,2,0,0,1,3,3,3,3,3,2};
  std::vector<int> F = {3,0,2,1,3,2,1,3,3,2,0,0,0,0,0,1};
  for (int i =0 ; i < my.m_nSize; ++i)
  {
      QStandardItem *Row = new QStandardItem(QString::number(F[i]) );
      model->setItem(i,my.m_nLength,Row);
  }

  // Fill second table

  QStandardItemModel *model2 = new QStandardItemModel(my.m_nSize, 5,this);

  ui->tableView_2->setModel(model2);

  model2->setHorizontalHeaderItem(0, new QStandardItem(QString("A")));
  model2->setHorizontalHeaderItem(1, new QStandardItem(QString("V")));
  model2->setHorizontalHeaderItem(2, new QStandardItem(QString("^V")));
  model2->setHorizontalHeaderItem(3, new QStandardItem(QString("V\"")));
  model2->setHorizontalHeaderItem(4, new QStandardItem(QString("Lzh*")));

  vZh = std::vector<std::vector<int> >(my.m_nSize,std::vector<int>(my.m_nLength+1));
  std::size_t n = 0;

  int v_ = 0;

  for (int i =0; i < my.m_nLength; ++i)
  {
    vZh[n][i] = my.get(0,i);
  }
 // vZh[n][my.m_nLength] = (F[0] - v_ - 1)%M;
  vZh[n][my.m_nLength] = (F[0] - v_)%M;
  n++;

// Fill firstRow
  QString str = "(";
  for (int i =0; i < my.m_nLength; ++i)
  {
       str += QString::number(my.get(0,i)) + " ";
  }
  QStandardItem *Row = new QStandardItem(str + ")");
  model2->setItem(0,0,Row);

  QStandardItem *Row1 = new QStandardItem(QString::number(F[0]));
  model2->setItem(0,1,Row1);
  QStandardItem *Row2 = new QStandardItem(QString::number(v_) );
  model2->setItem(0,2,Row2);
  QStandardItem *Row3 = new QStandardItem(QString::number(vZh[0][my.m_nLength]) );
  model2->setItem(0,3,Row3);
  QStandardItem *Row4 = new QStandardItem(" + [" + str + ")," + QString::number(vZh[0][my.m_nLength]) + "]");
  model2->setItem(0,4,Row4);


// Calculate

  for (int i = 1; i < my.m_nSize; ++i)
  {
    QString str = "(";
    v_ = calcV(my,  n, i, vZh);
    for (std::size_t k =0; k < my.m_nLength; ++k)
    {
         str += QString::number(my.get(i,k)) + " ";
    }
    QStandardItem *Row = new QStandardItem(str + ")");
    model2->setItem(i,0,Row);

    QStandardItem *Row1 = new QStandardItem(QString::number(F[i]));
    model2->setItem(i,1,Row1);
    QStandardItem *Row2 = new QStandardItem(QString::number(v_) );
    model2->setItem(i,2,Row2);

    if (v_ != F[i])
    {
        // add to Lzh*
        for (std::size_t j =0; j < my.m_nLength  ; ++j)
        {
          vZh[n][j] = my.get(i,j);
        }
        //vZh[n][my.m_nLength] = (F[i] - v_ - 1)%M;
        vZh[n][my.m_nLength] = (F[i] - v_)%M;
        if (vZh[n][my.m_nLength] < 0)
        {
          vZh[n][my.m_nLength] = M + vZh[n][my.m_nLength];
        }
        ++n;

        QStandardItem *Row3 = new QStandardItem(QString::number(vZh[n-1][my.m_nLength]) );
        model2->setItem(i,3,Row3);
        QStandardItem *Row4 = new QStandardItem(" + [" + str + ")," + QString::number(vZh[n-1][my.m_nLength]) + "]");
        model2->setItem(i,4,Row4);
    }
    else
    {
        QStandardItem *Row3 = new QStandardItem(" -- ");
        model2->setItem(i,3,Row3);
        QStandardItem *Row4 = new QStandardItem(" -- ");
        model2->setItem(i,4,Row4);
    }


  }
  vZh.resize(n);
}

void MainWindow::on_btnCalcPlnZh_clicked()
{
  static bool isAlreadyWork = false;

  if (vZh.empty())
    return;
  if (!isAlreadyWork)
  {
      isAlreadyWork = true;
      // Напишем полином жегалкина

      ui->plainTextEdit->appendPlainText("f(x) = ");

      std::size_t nl = vZh[0].size();

      for (std::size_t i = 0; i < vZh.size(); ++i)
      {
          QString str = "";
          if (i != 0)
          {
              str += " + ";
          }
          str += QString::number(vZh[i][nl-1]);

          for (std::size_t j = 0; j < nl-1; ++j)
          {
            str += " * ";
            str += "x" + QString::number(j+1) + "^";
            str += QString::number(vZh[i][j]);
          }


          ui->plainTextEdit->insertPlainText(str);
      }

  }

  QString str = "";
  QStringList strlist = str.split(",");
  std::vector<int> vX(strlist.size());

  for (int i = 0 ; i < strlist.size(); ++i)
  {
    vX[i] = strlist[i].toInt();
  }

  int sum = 0;
  std::size_t nl = vZh[0].size();

  for (std::size_t i = 0; i < vZh.size(); ++i)
  {
      int max = vZh[i][nl-1];
      for (std::size_t j = 0; j < nl-1; ++j)
      {
        int n = vX[j] >= vZh[i][j]+1 ? ui->spLength->value() - 1 : 0;
        max = max > n ? max : n;
      }
      sum += max + 1;
  }
  sum += ui->spLength->value();
  sum -- ;



}

