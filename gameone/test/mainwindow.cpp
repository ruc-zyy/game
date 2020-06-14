#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include <QPainter>
#include <towerposition.h>
#include <QMouseEvent>
#include <QMovie>
#include <QLabel>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)

{
    ui->setupUi(this);


for(int i=0;i<=20;i++){
    towerlabel[i]=new QLabel(this);
}
for(int i=0;i<=49;i++){
    enemylabel[i]=new QLabel(this);
    epic[i]=new QMovie("E:/gameone/wolf.gif");
}
loadTowerPositions();
addWayPoints();
loadWave();


connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
timer->start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap("E:/gameone/map1.png"));

    for(int i=0;i<m_towerPositionsList.size();i++){
        m_towerPositionsList[i].draw(&painter);

    }

drawHP(&painter);
drawWave(&painter);
drawPlayerGold(&painter);
foreach(Tower *tower,m_towersList){
tower->draw(towerlabel,pic);
}

foreach(Enemy *enemy,m_enemyList){
    enemy->draw(&painter,enemylabel,epic[enemy->no]);
}

foreach(Bullet *bullet,m_bulletList){
    bullet->draw(&painter);
}


if (m_gameEnded || m_gameWin)

{
    if(m_gameEnded) {
       painter.drawPixmap(QPoint(250,250),QPixmap("E:/gameone/test/defeat.png"));
    }
else{

 painter.drawPixmap(QPoint(250,250),QPixmap("E:/gameone/victory.png"));
}

    return;

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


numoftower=numoftower+1;
Tower *tower=new Tower(it->centerPos(),numoftower,this);
            m_towersList.push_back(tower);
m_playerGold-=tower->m_cost;
            update();

            break;

        }



        ++it;

    }

}



bool MainWindow::canBuyTower() const

{

    if(m_playerGold>=60){
        return true;
    }
    else {
        return false;
    }
}

void MainWindow::addWayPoints()

{

    WayPoint *wayPoint1 = new WayPoint(QPoint(120, 330));

    m_wayPointsList.push_back(wayPoint1);



    WayPoint *wayPoint2 = new WayPoint(QPoint(270, 330));

    m_wayPointsList.push_back(wayPoint2);

    wayPoint2->setNextWayPoint(wayPoint1);



    WayPoint *wayPoint3 = new WayPoint(QPoint(270, 640));

    m_wayPointsList.push_back(wayPoint3);

    wayPoint3->setNextWayPoint(wayPoint2);



    WayPoint *wayPoint4 = new WayPoint(QPoint(730, 640));

    m_wayPointsList.push_back(wayPoint4);

    wayPoint4->setNextWayPoint(wayPoint3);



    WayPoint *wayPoint5 = new WayPoint(QPoint(730, 495));

    m_wayPointsList.push_back(wayPoint5);

    wayPoint5->setNextWayPoint(wayPoint4);



    WayPoint *wayPoint6 = new WayPoint(QPoint(433, 495));

    m_wayPointsList.push_back(wayPoint6);

    wayPoint6->setNextWayPoint(wayPoint5);



    WayPoint *wayPoint7 = new WayPoint(QPoint(433, 330));

    m_wayPointsList.push_back(wayPoint7);

    wayPoint7->setNextWayPoint(wayPoint6);


    WayPoint *wayPoint8 = new WayPoint(QPoint(650, 330));

    m_wayPointsList.push_back(wayPoint8);

    wayPoint8->setNextWayPoint(wayPoint7);


    WayPoint *wayPoint9 = new WayPoint(QPoint(650, 185));

    m_wayPointsList.push_back(wayPoint9);

    wayPoint9->setNextWayPoint(wayPoint8);


    WayPoint *wayPoint10 = new WayPoint(QPoint(150, 185));

    m_wayPointsList.push_back(wayPoint10);

    wayPoint10->setNextWayPoint(wayPoint9);
}


bool MainWindow::loadWave()

{

    if (m_waves >= 3)

        return false;

    WayPoint *startWayPoint = m_wayPointsList.back(); // 这里是个逆序的，尾部才是其实节点

    int enemyStartInterval[] = { 100, 2000, 4000, 6000, 8000, 10000 };

    for (int i = 0; i < 5; ++i)

    {
numofwolf++;
        Enemy *enemy = new Enemy(numofwolf,startWayPoint, this);

        m_enemyList.push_back(enemy);

        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));

    }

    return true;

}


void MainWindow::updateMap()

{

    foreach (Enemy *enemy, m_enemyList)

        enemy->move();

    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();

}


void MainWindow::getHpDamage(int damage/* = 1*/)

{



    m_playerHp -= damage;

    if (m_playerHp <= 0)

        doGameOver();

}



void MainWindow::doGameOver()

{

    if (!m_gameEnded)

    {

        m_gameEnded = true;

        // 此处应该切换场景到结束场景

        // 暂时以打印替代,见paintEvent处理

    }

}


void MainWindow::removedEnemy(Enemy *enemy)

{

    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);

    delete enemy;
    enemylabel[enemy->no]=NULL;
    delete enemylabel[enemy->no];
    delete epic[enemy->no];
    if (m_enemyList.empty())

    {

        ++m_waves; // 当前波数加1

        // 继续读取下一波

        if (!loadWave())

        {

            // 当没有下一波时，这里表示游戏胜利

            // 设置游戏胜利标志为true

           m_gameWin=true;

            // 游戏胜利转到游戏胜利场景

            // 这里暂时以打印处理

        }

    }

}
void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}
void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}
QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::awardGold(int num){
    m_playerGold+=num;
    update();
}


void MainWindow::drawWave(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(310, 15, 200, 50), QString("WAVE : %1").arg(m_waves + 1));

}



void MainWindow::drawHP(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(25, 15, 200, 50), QString("HP : %1").arg(m_playerHp));

}



void MainWindow::drawPlayerGold(QPainter *painter)

{

    painter->setPen(QPen(Qt::red,200));

    painter->drawText(QRect(170, 15, 400, 50), QString("GOLD : %1").arg(m_playerGold));

}
