/*
 * visual.cpp
 *
 *  Created on: 23.08.2009
 *      Author: dmitry
 */


#include "visual.h"


TextWidget::TextWidget(const QString& text, QGraphicsItem* parent) :
	QGraphicsWidget(parent), text(text), color(Qt::black)
{
    setMinimumSize(200, 30);
}

void TextWidget::setText(const QString& s)
{
    text = s;
    update();
}

void TextWidget::addChar(QChar c)
{
    text += c;
    update();
}

void TextWidget::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(QPointF(0, 0), geometry().size());
    painter->setOpacity(0.7);
    painter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    qreal rounded_pix = (frame.width() + frame.height()) / 30;

    painter->setPen(QPen(QBrush(Qt::black), 1));
    painter->drawRoundedRect(frame, rounded_pix, rounded_pix);

    painter->setPen(QPen(color));
    QFont font;
    font.setPixelSize(frame.height() / 3);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(frame, Qt::AlignCenter, text);
}

void TextWidget::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    Q_UNUSED(event);
    emit clicked();
}

QList<CellItem*> BoardItem::getAjacentsCells(CellItem* cell)
{
    QList<CellItem*> list;
    QPoint coord(cell->getPosition());
    QRect rect(0, 0, rows, columns);

    QPoint top = coord + QPoint(0, 1);
    if (rect.contains(top))
        list.append(cells[top.x()][top.y()]);

    QPoint bottom = coord + QPoint(0, -1);
    if (rect.contains(bottom))
        list.append(cells[bottom.x()][bottom.y()]);

    QPoint right = coord + QPoint(1, 0);
    if (rect.contains(right))
        list.append(cells[right.x()][right.y()]);

    QPoint left = coord + QPoint(-1, 0);
    if (rect.contains(left))
        list.append(cells[left.x()][left.y()]);

    return list;
}

void BoardItem::setHelpText()
{
    switch (log.phase)
    {
    case MoveLog::MOVE_PHASE_NOT_STARTED:
        help_test->setText(tr("Move not started"));

        break;

    case MoveLog::MOVE_PHASE_STARTED:
        help_test->setText(tr("Click on cell and enter char"));
        break;

    case MoveLog::MOVE_PHASE_WAIT_FOR_CHAR:
        help_test->setText(tr("Enter letter by pressing a key"));
        break;

    case MoveLog::MOVE_PHASE_ENTER_WORD:
        help_test->setText(tr("Enter word by selecting letters"));
        break;

    case MoveLog::MOVE_PHASE_CLOSE_WORD:
        break;
    }


}


void BoardItem::makeAutoMove()
{

}

bool BoardItem::validateWord(const QString& str)
{

}

BoardItem::BoardItem(QGraphicsItem* parent_item) :
	QGraphicsWidget(parent_item), opacity(1), image(tr("atra_dot.png")),
        rows(5), columns(5), cells(rows, QVector<CellItem*> (columns))
{
    setMinimumSize(200, 200);

    QGraphicsGridLayout *layout = new QGraphicsGridLayout;

    TextWidget* current_word = new TextWidget("", this);
    help_test = new TextWidget("", this);
    connect(current_word, SIGNAL(clicked()), this, SLOT(makeMove()));
    connect(this, SIGNAL(currentWordChanged(const QString &)), current_word, SLOT(setText(const QString &)));
    connect(this, SIGNAL(stateChanged()), this, SLOT( setHelpText()));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            CellItem* it = new CellItem(this, i, j);
            cells[i][j] = it;
            it->installEventFilter(this);
            layout->addItem(it, i, j);
        }
    }
    score = new ScorePanelItem("", QImage(), ScorePanelItem::LEFT, this);
    layout->addItem(current_word, rows, 0, 1, columns);
    layout->addItem(help_test, rows+1, 0, 1, columns);
    layout->addItem(score, rows+2, 0, 1, columns);

    setLayout(layout);

    log.phase = MoveLog::MOVE_PHASE_NOT_STARTED;
    emit stateChanged();

    setCenterWord(tr("balda"));

    qDebug() << "MOVE_PHASE_NOT_STARTED";
}

void BoardItem::markBeforeSelect()
{
    foreach (QVector<CellItem*> row, cells)
    {
        foreach (CellItem* item, row)
        {
            if (item->isEmpty())
                item->setState(STATE_NOT_ALLOWED);
            else
                item->setState(STATE_DEFAULT);
        }
    }
}

void BoardItem::prepareBeforeMove()
{

    foreach (QVector<CellItem*> row, cells)
    {
        foreach (CellItem* item, row)
        {
            item->setState(STATE_NOT_ALLOWED);
        }
    }

    foreach (QVector<CellItem*> row, cells)
    {
        foreach (CellItem* item, row)
        {
            if (!item->isEmpty())
            {
                QList<CellItem*> ajacent_list = getAjacentsCells(item);

                foreach (CellItem* ajacent_item, ajacent_list)
                {
                    if (ajacent_item->isEmpty())
                        ajacent_item->setState(STATE_DEFAULT);
                }
            }
        }
    }
}

void BoardItem::makeMove()
{
    if (log.phase == MoveLog::MOVE_PHASE_NOT_STARTED)
    {
        log.phase = MoveLog::MOVE_PHASE_STARTED;
        emit stateChanged();
        qDebug() << "MOVE_PHASE_STARTED";
        prepareBeforeMove();

    }
    else
        qDebug() << "STARTED ALREADY";
}

void BoardItem::setCenterWord(QString str)
{
    str = str.toUpper();
    if (str.length() <= columns)
    {
        for (int i = 0; i < columns; i++)
            (cells[rows / 2][i])->setChar(str[i]);
    }
}

BoardItem::~BoardItem()
{

}

QString BoardItem::getCurrentWord()
{
    QString str;
    if (!log.cells.isEmpty())
    {
        foreach (CellItem* cell, log.cells)
        {
            str += cell->getChar();
        }
    }
    return str;
}

void BoardItem::reMove()
{
    if (log.phase == MoveLog::MOVE_PHASE_CLOSE_WORD)
    {
        log.added_char->delChar();
        closeMove();
        makeMove();
    }
    else
    {
        qDebug() << "Cannot reMove because state is not MoveLog::MOVE_PHASE_CLOSE_WORD";
    }
}

void BoardItem::closeMove()
{
    if (log.phase == MoveLog::MOVE_PHASE_CLOSE_WORD)
    {
        log.added_char->setMarkedFont(false);

        foreach (QVector<CellItem*> row, cells)
        {
            foreach (CellItem* item, row)
            {
                item->setState(STATE_DEFAULT);
            }
        }
        if (!log.cells.isEmpty()) score->AddWord(log.cells);
        log.cells.clear();
        emit currentWordChanged(getCurrentWord());
        log.phase = MoveLog::MOVE_PHASE_NOT_STARTED;
        emit stateChanged();
        qDebug() << "MOVE_PHASE_NOT_STARTED";

    }
}

bool BoardItem::eventFilter(QObject *obj, QEvent *event)
{
    CellItem * cell = dynamic_cast<CellItem *> (obj);

    if (cell != 0)
    {

        //qDebug() << event->type();

        switch (event->type())
        {

        case QEvent::FocusOut:
            if (log.phase == MoveLog::MOVE_PHASE_WAIT_FOR_CHAR)
            {
                cell->setWaitForChar();
            }
            break;

        case QEvent::KeyPress:
            {
                if (log.phase == MoveLog::MOVE_PHASE_WAIT_FOR_CHAR)
                {
                    QKeyEvent* key_event = static_cast<QKeyEvent*> (event);
                    QChar c = key_event->text()[0];
                    if (c.isLetter())
                    {
                        // Изменяем фазу до вызова cell->setWaitForChar(false), т.к. иначе нам не удасться потерять фокус
                        log.phase = MoveLog::MOVE_PHASE_ENTER_WORD;
                        emit stateChanged();
                        qDebug() << "MOVE_PHASE_ENTER_WORD";
                        cell->setMarkedFont(true);
                        cell->setChar(c);
                        cell->setWaitForChar(false);
                        markBeforeSelect();
                        log.added_char = cell;
                    }
                }
                break;
            }

        case QEvent::GraphicsSceneMouseDoubleClick:
            if (log.phase == MoveLog::MOVE_PHASE_ENTER_WORD)
            {
                log.phase = MoveLog::MOVE_PHASE_CLOSE_WORD;
                emit stateChanged();
                qDebug() << "MOVE_PHASE_CLOSE_WORD";
                if (log.cells.contains(log.added_char)){
                    qDebug() << "Contain";
                    closeMove();
                }

                else{
                    qDebug() << "Not contain";
                    reMove();
                }



            }

            break;

		case QEvent::GraphicsSceneMouseRelease:

            if (log.phase == MoveLog::MOVE_PHASE_STARTED)
            {
                if (cell->getState() == STATE_DEFAULT)
                {
                    cell->setWaitForChar(true);
                    log.phase = MoveLog::MOVE_PHASE_WAIT_FOR_CHAR;
                    emit stateChanged();
                    qDebug() << "MOVE_PHASE_WAIT_FOR_CHAR";
                    foreach (QVector<CellItem*> row, cells)
                    {
                        foreach (CellItem* item, row)
                        {
                            if (item == cell)
                                item->setState(STATE_DEFAULT);
                            else
                                item->setState(STATE_NOT_ALLOWED);
                        }

                    }

                }
            }
            else if (log.phase == MoveLog::MOVE_PHASE_ENTER_WORD)
            {
                if (cell->getState() == STATE_DEFAULT)
                {
                    bool allowed = false;
                    if (!log.cells.isEmpty())
                    {
                        QList<CellItem*> list = getAjacentsCells(log.cells.back());
                        allowed = list.contains(cell);
                    }

                    if (log.cells.isEmpty() || allowed)
                    {
                        cell->setState(STATE_SELECTED);
                        cell->setFocus(false);
                        log.cells.append(cell);
                        emit currentWordChanged( getCurrentWord() );
                    }
                }
                else if (cell->getState() == STATE_SELECTED && log.cells.back()
                    == cell)
                    {
                    cell->setState(STATE_DEFAULT);
                    log.cells.pop_back();
                    emit currentWordChanged( getCurrentWord() );
                }
            }

            break;

		case QEvent::GraphicsSceneHoverEnter:
            {

                if (cell->getState() == STATE_DEFAULT)
                    cell->setFocus();

                break;
            }
		case QEvent::GraphicsSceneHoverLeave:

            if (cell->getState() == STATE_DEFAULT)
                cell->setFocus(false);

            break;

		default:

            //qDebug() << "default";
            break;
        }
    }
    return false;

}

void BoardItem::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(QPointF(0, 0), geometry().size());
    painter->drawPixmap(frame, image, image.rect());
}
