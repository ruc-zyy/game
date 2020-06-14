#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
static const int Health_Bar_Width = 20;
const QSize Enemy::ms_fixedSize(50, 50);
Enemy::Enemy(int num,WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite)

    : QObject(0)

    , m_pos(startWayPoint->pos())

    , m_sprite(sprite)

{

    m_maxHp = 40;

    m_currentHp = 40;

    m_active = false;

    m_walkingSpeed = 3.0;

    m_destinationWayPoint = startWayPoint->nextWayPoint();

    m_rotationSprite = 0.0;

    m_game = game;
    no=num;

}

void Enemy::draw(QPainter *painter,QLabel **enemylabel,QMovie *pic)

{
    if (!m_active)
        return;


    // 血条的长度

    // 其实就是2个方框,红色方框表示总生命,固定大小不变

    // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响

    static const int Health_Bar_Width = 20;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 5, -ms_fixedSize.height() / 3)+QPoint(12,-15);

    // 绘制血条

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::red);

    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));

    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);

    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 2));

    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上

    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);

    painter->translate(m_pos);

    painter->rotate(m_rotationSprite);

    // 绘制敌人

    enemylabel[no]->setGeometry(m_pos.x()-25,m_pos.y()-25,50,50);
    enemylabel[no]->setScaledContents(true);
    enemylabel[no]->setMovie(pic);
    pic->start();

    painter->restore();

}


void Enemy::move()

{

    if (!m_active)
        return;



    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;


}


void Enemy::doActivate()

{

    m_active = true;

}
void Enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void Enemy::getDamage(int damage)
{

    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
m_game->awardGold(30);
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void Enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}



