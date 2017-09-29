#include <QPainter>
#include <QMouseEvent>
#include "qgraphics.h"

QGraphics::QGraphics(QWidget *parent) : QWidget(parent), s_type(Options::Cardinal)
{
    QPalette p;
    p.setBrush(this->backgroundRole(),QBrush(QColor(255,255,255)));
    this->setPalette(p);
    this->setAutoFillBackground(true);

	spline = new CardinalSpline();
    //spline = new BezierSpline();
    setMouseTracking(true);
}

void QGraphics::genSpline(bool fi)
{
	if (options.sline_t != s_type) {
		delete spline; spline = nullptr;
		spline = SplineBuilder::Build(options.sline_t);
		s_type = options.sline_t;
	}
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
	setCursor(Qt::ClosedHandCursor);
	last_pos = event->pos();

	if(options.add_cp_mode == Options::AdjustCtrlPos)
		adj_p_idx = spline->at(last_pos);
    update();
}

void QGraphics::mouseDoubleClickEvent(QMouseEvent * event)
{
	if (options.add_cp_mode == Options::AddCtrlPos) {
		setCursor(Qt::CrossCursor);
		spline->add(event->pos());
	}
	update();
}

void QGraphics::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    if(had_press) {
		if (adj_p_idx != -1 && options.add_cp_mode == Options::AdjustCtrlPos) {
			(*spline)[adj_p_idx] = pos;
			//是否完成绘制，若完成，则更新整个图，否则只更新点
			if (spline->isFinished())
				spline->genSpline();
		}
    }
    last_pos = pos;

    update();
}

void QGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    had_press = false;
	adj_p_idx = -1;
    setCursor(Qt::ArrowCursor);
}

void QGraphics::wheelEvent(QWheelEvent *event)
{
    auto delta = event->angleDelta();
    if(delta.rx() > 0) {

    }
}
