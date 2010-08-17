#include "scorepanelitem.h"
#include <QGraphicsLinearLayout>
#include <QPainter>

ScorePanelItem::ScorePanelItem(QString player_name, QImage icon, QGraphicsWidget *parent) :
    QGraphicsWidget(parent)
{

}

void ScorePanelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF frame(QPointF(0, 0), geometry().size());
    painter->setOpacity(0.7);
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);

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

void ScorePanelItem::AddWord(QString word)
{
    m_words.append(word);
    update();
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
