#include "game.h"
#include "visual.h"

game::game(QWidget *parent) :
	QWidget(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene;

    board_window = new QGraphicsWidget(NULL, Qt::Widget);
    game_board = new BoardItem(board_window);


    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout;

    layout->addItem(game_board);
    board_window->setLayout(layout);

    scene->addItem(board_window);
    ui.graphicsView->setScene(scene);
    ui.graphicsView->setRenderHint(QPainter::Antialiasing);

    resize(500, 500);
}


game::~game()
{
    delete board_window;
    delete scene;

}
