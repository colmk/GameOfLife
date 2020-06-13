#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & (~Qt::WindowMaximizeButtonHint));
    resize(800,800);
    setFixedSize(this->width(),this->height());
    con = new cell(100,100);    //con->paint_map();
    timer.callOnTimeout(this,&MainWindow::timeoutHanle);
    timer.start(250);
    setWindowTitle("Game of Life");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete con;
}

void MainWindow::paintCell()
{
    const auto boardSize = this->size();
    const auto conSize = con->getSize();
    const int indexLimit = con->getIndexLimit();
    const int stepHeight = boardSize.height() / conSize.first;
    const int stepWidth = boardSize.width() / conSize.second;
    QPainter painter(this) ;
    painter.setRenderHints(QPainter::Antialiasing);
    for(int i=0;i< indexLimit;++i)
    {
        int x = i%conSize.first*stepHeight+stepHeight/2-2;
        int y = i/conSize.second*stepWidth+stepWidth/2-2;
        if(con->map[i] & 0x1){
            painter.setPen(Qt::black);
            painter.setBrush(QBrush(Qt::black));
        }else{
            painter.setPen(Qt::white);
            painter.setBrush(QBrush(Qt::white));
        }
        painter.drawEllipse(x, y, 5, 5);

    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QSize size=this->size();
    auto con_size = con->getSize();
    QPainter painter(this);
    painter.setRenderHint(painter.Antialiasing);  //设置反走样
    painter.setPen(Qt::gray);
    int stepHeight = size.height() / con_size.first;
    int stepWidth = size.width() / con_size.second;
    //画网格
    for(int h=stepHeight; h < size.height(); h+=stepHeight)
        painter.drawLine(0,h,size.width(),h);
    for(int w=stepWidth; w < size.width(); w+=stepWidth)
        painter.drawLine(w,0,w,size.height());

    //画cell
    paintCell();
}

void MainWindow::timeoutHanle()
{
    con->updateCells();
    this->repaint();
    //con->paintMap();
}

