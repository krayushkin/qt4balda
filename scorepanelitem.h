#ifndef SCOREPANELITEM_H
#define SCOREPANELITEM_H

#include <QGraphicsWidget>
#include "cell_item.h"

class Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Pixmap(const QPixmap &pix, QGraphicsItem* parent)
        : QObject(), QGraphicsPixmapItem(pix, parent)
    {
       // setCacheMode(DeviceCoordinateCache);
    }
    virtual ~Pixmap()
    {

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

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    ScorePanelItem(QString player_name, QImage icon, QGraphicsWidget *parent = 0);

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
