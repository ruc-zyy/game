#ifndef TOWER_H
#define TOWER_H
#include<QPainter>
#include<QLabel>
class Tower
{
public:
    Tower(QPoint pos,const QPixmap &sprite=QPixmap("E:/gameone/tower4.gif"));
QPoint m_pos;
    void draw(QPainter *painter) const;
    QLabel *label;
private:

    int m_attackrange;
    int m_damage;
    int m_firerate;
    QPixmap m_sprite;

};

#endif // TOWER_H
