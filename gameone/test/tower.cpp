#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include<QMovie>
#include<QLabel>
Tower::Tower(QPoint pos,int n,MainWindow *game, const QPixmap &sprite):m_pos(pos),m_sprite(sprite),
     m_rotationSprite(0.0)
    , m_chooseEnemy(NULL)
    , m_game(game)
,m_attacking(false)
{
    m_attackrange=200;
    m_fireRate=1000;
    m_damage=10;

    no=n;

    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void Tower::draw(QLabel **towerlabel,QMovie *pic) const{
towerlabel[no]->setGeometry(m_pos.x()-20,m_pos.y()-75,50,84);
towerlabel[no]->setScaledContents(true);
towerlabel[no]->setMovie(pic);
pic->start();
}

void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化


        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackrange, m_chooseEnemy->m_pos, 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内

        foreach (Enemy *enemy, m_game->m_enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackrange, enemy->m_pos, 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}
void Tower::attackEnemy()

{

    // 启动打炮模式



}

void Tower::chooseEnemyForAttack(Enemy *enemy)

{

    // 选择敌人,同时设置对敌人开火

    m_chooseEnemy = enemy;

    // 这里启动timer,开始打炮
m_fireRateTimer->start(m_fireRate);


    // 敌人自己要关联一个攻击者,这个用QList管理攻击者,因为可能有多个

    m_chooseEnemy->getAttacked(this);

}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos+QPoint(0,-80), m_chooseEnemy->m_pos, m_damage, m_chooseEnemy, m_game);
bullet->move();
    m_game->addBullet(bullet);

}

void Tower::targetKilled()

{

    // 目标死亡时,也需要取消关联

    // 取消攻击

    if (m_chooseEnemy)

        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();

    m_rotationSprite = 0.0;

}

void Tower::lostSightOfEnemy()

{

    // 当敌人脱离炮塔攻击范围,要将炮塔攻击的敌人关联取消

    // 同时取消攻击

    m_chooseEnemy->gotLostSight(this);

    if (m_chooseEnemy)

        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();

    m_rotationSprite = 0.0;

}
