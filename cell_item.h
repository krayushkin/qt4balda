/*
 * cell_item.h
 *
 *  Created on: 16.11.2009
 *      Author: dima
 */

#ifndef CELL_ITEM_H_
#define CELL_ITEM_H_

#include <QtGui>


	enum State
	{
		STATE_DEFAULT,
		STATE_NOT_ALLOWED,
		STATE_SELECTED
	};

class CellItem: public QGraphicsWidget
{
	Q_OBJECT
public:

	CellItem(QGraphicsItem* parent_item, int row, int column);
	~CellItem();

	QPoint getPosition();
	bool isAdjacentWith(CellItem* other);


	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,	QWidget *widget);



	public slots:
		void setChar(QChar c);
		void delChar();

		void setFocus(bool focus = true);
		void setState(State s);

		void setWaitForChar(bool x = true);

		QChar getChar();
		bool isEmpty();
		State getState();

private:


		void mousePressEvent ( QGraphicsSceneMouseEvent * event );


	QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
	void setGeometry ( const QRectF & rect );

	bool	is_empty,
			is_focused,
			is_wait_char;

	State state;

	int row, column;

	// Visual settings
	QColor	background_color_default,
			background_color_not_allowed,
			background_color_selected,
			border_color_focused,
			border_color_unfocused,
			border_color_wait_char;


	qreal opacity;
	QChar c;
};

#endif /* CELL_ITEM_H_ */
