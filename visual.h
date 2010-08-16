/*
 * visual.h
 *
 *  Created on: 23.08.2009
 *      Author: dmitry
 */

#ifndef VISUAL_H_
#define VISUAL_H_

#include <vector>
#include <list>
#include <QtGui>

#include "cell_item.h"

struct MoveLog
{
	enum MovePhase
	{
		MOVE_PHASE_NOT_STARTED,
		MOVE_PHASE_STARTED,
		MOVE_PHASE_WAIT_FOR_CHAR,
		MOVE_PHASE_ENTER_WORD,
		MOVE_PHASE_CLOSE_WORD
	};

        // Current phase
	MovePhase phase;

        // The list of items in the order they are added
	QList<CellItem*> cells;

        // Added char
	CellItem* added_char;
};

class TextWidget : public QGraphicsWidget
{
	Q_OBJECT
public:
	TextWidget(const QString& text, QGraphicsItem* parent);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,	QWidget *widget);
        void mousePressEvent (QGraphicsSceneMouseEvent * event );

	public slots:
	void addChar(QChar c);
	void setText(const QString& s);

	signals:
	void clicked();

private:
	QString text;
	QColor color;
};




class BoardItem: public QGraphicsWidget
{
	Q_OBJECT
public:

	BoardItem(QGraphicsItem* parent_item);
	~BoardItem();
	QList<CellItem*> getAjacentsCells(CellItem* cell);
	QString getCurrentWord();
        bool validateWord(const QString& str);

	public slots:

	void prepareBeforeMove();
	void markBeforeSelect();
	void makeMove();
        void makeAutoMove();
        void reMove();
        void closeMove();
	void setCenterWord(QString str);

        void setHelpText();

	signals:
        void tryComplete();
	void currentWordChanged(const QString& str);
        void stateChanged();

private:
	bool eventFilter(QObject *obj, QEvent *event);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,	QWidget *widget);


	// Visual settings
	qreal opacity;
	QPixmap image;
        TextWidget* help_test;
	int rows, columns;

	// Cells
	QVector< QVector<CellItem *> > cells;

	MoveLog log;

};


#endif /* VISUAL_H_ */
