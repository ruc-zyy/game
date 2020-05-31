#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <towerposition.h>
#include <tower.h>
#include <QPainter>
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
    QLabel *w=new QLabel(this);
protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QList<TowerPosition> m_towerPositionsList;
    void loadTowerPositions();
    QList<Tower> m_towersList;
};

#endif // MAINWINDOW_H
