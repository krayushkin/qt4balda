#include "scorepanelitem.h"
#include <QGraphicsLinearLayout>
#include <QPainter>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

ScorePanelItem::ScorePanelItem(QString player_name, QImage icon, QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);



    setLayout(layout);
}

void ScorePanelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF frame(QPointF(0, 0), geometry().size());
    painter->setOpacity(0.7);


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
    foreach(CellItem* item, word)
    {
        QGraphicsPixmapItem* p_item = new QGraphicsPixmapItem(item->snapshot() ,this);
        p_item->setPos(item->scenePos());
        QPropertyAnimation *anim = new QPropertyAnimation;
        anim->setPropertyName("pos");
        anim->setTargetObject((QObject*)p_item);
        anim->setDuration(1000);
        anim->setStartValue(item->scenePos());
        anim->setEndValue(QPointF(0, 0));
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
