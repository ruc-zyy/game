#include "tower.h"
#include<QMovie>
#include<QLabel>
Tower::Tower(QPoint pos, const QPixmap &sprite):m_pos(pos),m_sprite(sprite){
    m_attackrange=100;
    m_firerate=1000;
    m_damage=10;
    label=new QLabel;
}
void Tower::draw(QPainter *painter) const{
painter->drawPixmap(this->m_pos.x()-20,this->m_pos.y()-75,this->m_sprite);
}
