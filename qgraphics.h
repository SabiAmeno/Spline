#ifndef QGRAPHICS_H
#define QGRAPHICS_H

#include <QWidget>
#include "spline.h"

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
	void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
public:
	Options options;
private:
    bool had_press = false;

    QPoint last_pos;

    SplineABT* spline;
	Options::SplineType s_type;
	int adj_p_idx = -1;
};

#endif // QGRAPHICS_H
