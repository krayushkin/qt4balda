#include "scorepanelitem.h"
#include <QGraphicsLinearLayout>
#include <QPainter>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>




ScorePanelItem::ScorePanelItem(QString player_name, QImage icon, Align align, QGraphicsItem *parent):
    QGraphicsWidget(parent), m_coord(align)
{
    words_layout = new QGraphicsLinearLayout(Qt::Vertical );
    words_layout->setSpacing(0);
    setLayout(words_layout);


}

void ScorePanelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF frame(QPointF(0, 0), geometry().size());
    painter->setOpacity(0.7);
    painter->drawRect(0,0, size().width(), size().height());
}


//leader
void ScorePanelItem::SetLeader(bool is_leader)
{
    m_leader = is_leader;
    update();
}

bool ScorePanelItem::IsLeader()
{
    return m_leader;
}

//player_name
QString ScorePanelItem::PlayerName()
{
    return m_player_name;
}


void ScorePanelItem::Clear()
{
    m_words.clear();
    update();
}



void ScorePanelItem::AddWord(QList<CellItem*> word)
{
    QParallelAnimationGroup *anim_group = new QParallelAnimationGroup(this);
    QList<QPixmap*> pixmaps;
    foreach (CellItem* item, word)
    {
        Pixmap* p_item = new Pixmap(item->snapshot().scaledToHeight(30, Qt::SmoothTransformation), this);
        pixmaps << p_item;
    }


    QMap<Pixmap*, QPointF> coord = m_coord.getNextWordCoord(word);


    CellItem *item;
    foreach(Pixmap* p_item, pixmaps)
    {
        item

        QPropertyAnimation *anim = new QPropertyAnimation(p_item, "pos");
        anim->setDuration(800);
        anim->setStartValue( mapFromItem(item, 0, 0) );
        anim->setEndValue( coord[item] );
        QEasingCurve c(QEasingCurve::InOutBack);
        anim->setEasingCurve(c);
        anim_group->addAnimation(anim);
    }
    anim_group->start();
}


QImage ScorePanelItem::getIcon()
{
    return m_icon;
}

void ScorePanelItem::setIcon(QImage icon)
{
    m_icon = icon;
    update();
}
