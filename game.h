#ifndef GAME_H
#define GAME_H

#include <QtGui/QWidget>
#include "ui_game.h"
#include "visual.h"

class game : public QWidget
{
    Q_OBJECT

public:
    game(QWidget *parent = 0);
    ~game();

private:
    Ui::gameClass ui;
    BoardItem* game_board;
    QGraphicsWidget *board_window;
    QGraphicsScene* scene;
};

#endif // GAME_H
