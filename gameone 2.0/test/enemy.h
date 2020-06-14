#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QLabel>
#include <QMovie>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class Enemy:public QObject
{Q_OBJECT
public:
    Enemy(int num,WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite=QPixmap("E:/gameone/wolf.gif"));
    void draw(QPainter *painter,QLabel **enemylabel,QMovie *pic);
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    int no;
    QPoint			m_pos;
public slots:
    void doActivate();
private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    double			m_walkingSpeed;
    qreal			m_rotationSprite;


    WayPoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

#endif // ENEMY_H
