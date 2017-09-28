#ifndef QGRAPHICS_H
#define QGRAPHICS_H

#include <QWidget>
#include "spline.h"

class ClipRect {
public:
    ClipRect() {}
    ClipRect(const QRect& r) : crect(r){}

    void offset(const QPoint& pos)
    {
        crect.setTopLeft(crect.topLeft() + pos);
        crect.setWidth(128);
        crect.setHeight(100);
    }

public:
    QRect crect = QRect(60, 100, 128, 100);
};


class QGraphics : public QWidget
{
    Q_OBJECT
public:
    explicit QGraphics(QWidget *parent = 0);

	void genSpline(bool fi = false);
	void repaint();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
public:
	Options options;
private:
    ClipRect clip_rect;
    bool never_move = true;
    bool had_press = false;

    QPoint last_pos;

    SplineABT* spline;
	Options::SplineType s_type;
};

#endif // QGRAPHICS_H
