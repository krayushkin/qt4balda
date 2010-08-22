#ifndef SCOREPANELITEM_H
#define SCOREPANELITEM_H

#include <QGraphicsWidget>
#include "cell_item.h"

class Pixmap : public QGraphicsWidget
{
    Q_OBJECT

    QPixmap m_pix;

public:
    Pixmap(const QPixmap &pix, QGraphicsItem* parent)
        : QGraphicsWidget(parent), m_pix(pix)
    {
        setPreferredSize(m_pix.size());
        setMinimumSize(m_pix.size());
        setMaximumSize(m_pix.size());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->drawPixmap(QPointF(0, 0), m_pix);
    }
};


class ScorePanelItem : public QGraphicsWidget
{
    Q_OBJECT

    Q_PROPERTY(bool leader READ IsLeader WRITE SetLeader)
    Q_PROPERTY(QString player_name READ PlayerName)
    Q_PROPERTY(QImage icon READ getIcon WRITE setIcon)
    bool m_leader;
    QList<QString> m_words;
    QString m_player_name;
    QImage m_icon;
    QGraphicsLinearLayout *words_layout;

    // draw words in ScorePanel

public:
    enum Align
    {
        LEFT = 0,
        RIGHT
    };
private:


    class Draw_coordinates
    {
        int start_x, start_y, x, y;
        Align align;
    public:

        QMap<CellItem*, QPointF> getNextWordCoord(QList<Pixmap*> items)
        {
            QMap<Pixmap*, QPointF> coord;
            foreach (Pixmap* item, items)
            {
                coord[item] = QPointF(0, 0);
            }
            return coord;
        }


        Draw_coordinates(Align a) : align(a)
        {

        }
    };
    Draw_coordinates m_coord;
    // draw end





    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const
    {
        switch(which)
        {
        case Qt::PreferredSize:
        case Qt::MinimumSize:
            return QSizeF(100, 100);

        case Qt::MaximumSize:
            return QSizeF(1000, 1000);
        default:
            break;
        }
        return constraint;
    }
public:

    ScorePanelItem(QString player_name, QImage icon, Align align, QGraphicsItem *parent = 0);
    //leader
    void SetLeader(bool is_leader);
    bool IsLeader();

    //player_name
    QString PlayerName();

    //icon
    QImage getIcon();
    void setIcon(QImage icon);

signals:

public slots:
    void Clear();
    void AddWord(QList<CellItem*> word);
};

#endif // SCOREPANELITEM_H
