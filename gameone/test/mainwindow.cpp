#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <towerposition.h>
#include <QMouseEvent>
#include <QMovie>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap("E:/gameone/map2.png"));
    loadTowerPositions();
    for(int i=0;i<m_towerPositionsList.size();i++){
        m_towerPositionsList[i].draw(&painter);
    }


foreach(Tower tower,m_towersList){
tower.draw(&painter);

}



}

void MainWindow::loadTowerPositions(){
    QPoint pos[] =	{

        QPoint(320, 90),
        QPoint(470, 90),
        QPoint(550, 90),
        QPoint(160, 250),
        QPoint(320, 250),
        QPoint(480, 250),
        QPoint(700, 250),
        QPoint(170, 390),

        QPoint(550, 390),
        QPoint(320, 480),
        QPoint(400, 550),
        QPoint(620, 550),
        QPoint(170, 620),

                    };
    int len	= sizeof(pos) / sizeof(pos[0]);
    for (int i = 0; i < len; ++i) m_towerPositionsList.push_back(pos[i]);

}

void MainWindow::mousePressEvent(QMouseEvent *event)

{

    QPoint pressPos=event->pos();

    auto it = m_towerPositionsList.begin();

    while (it != m_towerPositionsList.end())

    {

        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())

        {

            it->setHasTower();



            m_towersList.push_back(it->centerPos());

            update();

            break;

        }



        ++it;

    }

}



bool MainWindow::canBuyTower() const

{

    return true;

}
