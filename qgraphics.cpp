#include <QPainter>
#include <QMouseEvent>
#include "qgraphics.h"

QGraphics::QGraphics(QWidget *parent) : QWidget(parent)
{
    QPalette p;
    p.setBrush(this->backgroundRole(),QBrush(QColor(255,255,255)));
    this->setPalette(p);
    this->setAutoFillBackground(true);

	spline = new CardinalSpline();
    setMouseTracking(true);
}

void QGraphics::genSpline(bool fi)
{
	if (fi)
		spline->finish();
	else
		spline->genSpline();
}

void QGraphics::repaint()
{
	spline->clear();
}

void QGraphics::paintEvent(QPaintEvent *event)
{
    QPainter pir(this);
    spline->draw(pir.device(), options);

    QWidget::paintEvent(event);
}

void QGraphics::mousePressEvent(QMouseEvent *event)
{
    had_press = true;
    last_pos = event->pos();
    setCursor(Qt::ClosedHandCursor);

	spline->add(last_pos);
    update();
}

void QGraphics::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    if(had_press) {
        clip_rect.offset(pos - last_pos);
        if(never_move) never_move = false;
    }
    last_pos = pos;

    update();
}

void QGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    had_press = false;
    setCursor(Qt::ArrowCursor);
}

void QGraphics::wheelEvent(QWheelEvent *event)
{
    auto delta = event->angleDelta();
    if(delta.rx() > 0) {

    }
}
