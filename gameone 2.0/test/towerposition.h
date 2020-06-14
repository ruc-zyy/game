#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include<QMainWindow>

class TowerPosition
{
public:
TowerPosition();
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap("E:/gameone/pos5.png"));
    void setHasTower();
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;

private:
    QPoint		t_pos;
    bool		t_hasTower;
    QPixmap		t_sprite;
    static const QSize t_fixedSize;
};

#endif // TOWERPOSITION_H
