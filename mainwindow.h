#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintDevice>
#include <QPainter>
#include <QTimer>

#include "cell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    cell *con;
    typedef struct{
        int boardSizeX;
        int boardSizeY;
    }config;
    config conf;
    void paintCell();
    QTimer timer;

protected:
    void paintEvent(QPaintEvent *);
private slots:
    void timeoutHanle();
};
#endif // MAINWINDOW_H
