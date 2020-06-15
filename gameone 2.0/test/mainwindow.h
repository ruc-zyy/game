#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "bullet.h"
#include "enemy.h"
#include <QMainWindow>
#include <towerposition.h>
#include <tower.h>
#include <QPainter>
#include <QMovie>
#include <waypoint.h>
#include <QTimer>
class Enemy;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    bool canBuyTower() const;
    void drawtower();
    void addBullet(Bullet *bullet);
    void getHpDamage(int damege=1);
    void removedBullet(Bullet *bullet);
    void doGameOver();
    void awardGold(int num);
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    int m_playerGold=270;

    QLabel *towerlabel[21]={new QLabel(this)};
    QList<QLabel *> t;
    QMovie *pic=new QMovie("E:/gameone 2.0/tower4.gif");
    int numoftower=0;

    QList<WayPoint *> m_wayPointsList;	// 在paintEvent中需要进行绘制，那个类似的foreach(xxx) xxx.draw(xxx)
    void addWayPoints();			// 在构造函数中调用

QList<Enemy *> m_enemyList;
void removedEnemy(Enemy *enemy);
bool loadWave();
QTimer *timer = new QTimer(this);

QLabel *enemylabel[50]={new QLabel(this)};
QList<QLabel *> e;
QMovie *epic[50]={new QMovie("E:/gameone 2.0/wolf.gif")};
QList<QMovie *> ep;
int numofwolf=0;
QList<Enemy *> enemyList() const;

QList<Bullet *>			m_bulletList;

protected:
    void paintEvent(QPaintEvent *);
protected slots:
 void updateMap();
private:
    Ui::MainWindow *ui;
    QList<TowerPosition> m_towerPositionsList;
    void loadTowerPositions();
    QList<Tower *> m_towersList;
    int m_waves=0;
    int m_playerHp=3;
    bool m_gameEnded=false;
    bool m_gameWin=false;
QPixmap vic;
};

#endif // MAINWINDOW_H
