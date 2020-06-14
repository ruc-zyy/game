#ifndef TOWER_H
#define TOWER_H
#include <QTimer>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include<QPainter>
#include<QLabel>
class QPainter;
class Enemy;
class MainWindow;
class QTimer;

class Tower:public QObject
{
Q_OBJECT
public:
    Tower(QPoint pos,int n,MainWindow *game,const QPixmap &sprite=QPixmap("E:/gameone/tower4.gif"));

    void draw(QLabel **towerlabel,QMovie *pic) const;
   QPoint m_pos;
   int no;
   int m_cost=60;
   void checkEnemyInRange();
   void targetKilled();
   void attackEnemy();
   void chooseEnemyForAttack(Enemy *enemy);
   void removeBullet();
   void damageEnemy();
   void lostSightOfEnemy();

private slots:
   void shootWeapon();

private:
bool m_attacking;
    int m_attackrange;
    int m_damage;
    int m_fireRate;
    QPixmap m_sprite;
    qreal			m_rotationSprite;

    Enemy *			m_chooseEnemy;
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer=new QTimer(this);

};

#endif // TOWER_H
