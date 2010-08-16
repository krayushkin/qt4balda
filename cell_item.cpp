/*
 * cell_item.cpp
 *
 *  Created on: 16.11.2009
 *      Author: dima
 */

#include "cell_item.h"

// ********* public functions **********

void CellItem::setChar(QChar c) {
	if (c.isLetter())
	{
		is_empty = false;
		this->c = c.toUpper();
		update();
	}
}

//********************************

CellItem::CellItem(QGraphicsItem* parent_item, int row, int column) :
	QGraphicsWidget(parent_item),
			is_empty(true),
			is_focused(false),
			is_wait_char(false),
                        is_font_marked(false),
			state(STATE_DEFAULT),
			row(row),
			column(column),
			background_color_default("white"),
                        background_color_not_allowed("green"),
                        background_color_selected("khaki"),
                        border_color_focused("blueviolet"),
			border_color_unfocused("black"),
                        border_color_wait_char("deeppink"),
                        font_color_marked("black"),
                        font_color_unmarked("black"),
                        angle(rand() % 4 - 2)

	{
	setAcceptHoverEvents(true);
	setFlags(QGraphicsItem::ItemIsFocusable);
	QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);
	updateGeometry();
}

void CellItem::setMarkedFont(bool value)
{
    is_font_marked = value;
}

bool CellItem::isAdjacentWith(CellItem* other)
{
	return (getPosition() - other->getPosition()).manhattanLength() == 1;
}

QPoint CellItem::getPosition()
{
	return QPoint(row, column);
}

void CellItem::setGeometry ( const QRectF & rect )
{
	QGraphicsWidget::setGeometry(rect);
}

QSizeF CellItem::sizeHint(Qt::SizeHint which,
		const QSizeF & constraint) const {



	switch (which) {
	case Qt::MinimumSize:
	case Qt::PreferredSize:
		// Do not allow a size smaller than the pixmap with two frames around it.
                return QSizeF(30, 30);
	case Qt::MaximumSize:
		return QSizeF(1000, 1000);
	default:
		break;
	}
	return constraint;
}


CellItem::~CellItem() {

}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget) {
	Q_UNUSED(widget);
	Q_UNUSED(option);

	QRectF frame(QPointF(0, 0), geometry().size());
	qreal rounded_pix = (frame.width() + frame.height()) / 30;
        qreal background_opacity = 1;


switch (state) {
	case STATE_DEFAULT:
		painter->setBrush(QBrush(background_color_default, Qt::SolidPattern));
		break;

	case STATE_NOT_ALLOWED:
                painter->setBrush(QBrush(background_color_not_allowed, Qt::SolidPattern));
                background_opacity = 0.5;
		break;

	case STATE_SELECTED:
		painter->setBrush(QBrush(background_color_selected, Qt::SolidPattern));
		break;

	default:
		break;
}

        QPen pen;
        pen.setWidth(1);
        if (is_wait_char) pen.setColor(border_color_wait_char );
	else
        {
                if (is_focused) pen.setColor( border_color_focused );
                        else pen.setColor( border_color_unfocused );
        }
        painter->setPen( pen );

        painter->setOpacity(background_opacity);

        painter->save();
        painter->rotate(angle);
        painter->drawRoundedRect(frame, rounded_pix, rounded_pix);
        painter->restore();

        painter->setOpacity(1);

	if (!is_empty)
	{
		QFont font;
		font.setPixelSize(frame.height() / 2);
                font.setBold(true);

                if (is_font_marked)
                {
                    font.setItalic(true);
                    painter->setPen(font_color_marked);
                }
                else painter->setPen(font_color_unmarked);

		painter->setFont(font);
		painter->drawText(frame, c, QTextOption(Qt::AlignCenter));
	}
}


void CellItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	Q_UNUSED(event);
}


QChar CellItem::getChar() {
	return c;
}

bool CellItem::isEmpty() {
	return is_empty;
}

void CellItem::delChar() {
	is_empty = true;
	update();
}

void CellItem::setWaitForChar(bool x)
{
	is_wait_char = x;
	x ? QGraphicsItem::setFocus() : QGraphicsItem::clearFocus();
	update();
}

void CellItem::setFocus(bool focus) {
	is_focused = focus;
	update();
}


void CellItem::setState(State s)
{
	state = s;
	update();
}

State CellItem::getState()
{
	return state;
}
