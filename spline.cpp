#include "spline.h"


void SplineABT::add(const QPoint &p)
{
	if (finished)
		return;
	points.push_back(p);

	_add(p);
}

void SplineABT::finish()
{
	genSpline();
	finished = true;
}

void CardinalSpline::draw(QPaintDevice* pd, const Options& opt)
{
	SplineABT::draw(pd, opt);

	QPainter pir(pd);
	pir.setRenderHint(QPainter::Antialiasing);
	for (int i = 0; i < size(); ++i)
		pir.drawEllipse((*this)[i], 2, 2);

	pir.drawPath(path);
}

int SplineABT::size()
{
	return points.size();
}

const QPoint &SplineABT::operator[](int index)
{
	Q_ASSERT(index < points.size());
	return points.at(index);
}

void SplineABT::clear()
{
	finished = false;
	points.clear();
	path.swap(QPainterPath());
}

void SplineABT::genSpline()
{
	Path();
}

void CardinalSpline::Path()
{
	float intival[100];
	for (int i = 0; i < opts.interpolation; i++)
		intival[i] = (float)i / opts.interpolation;

	if (!points.isEmpty()) {
		path.swap(QPainterPath());
		path.moveTo(points[0]);
		for (int i = 1; i < size() - 2; i++) {
			for (int j = 0; j < opts.interpolation; j++) {
				path.lineTo(xy(i, intival[j]));
			}
		}
	}
}

void CardinalSpline::_add(const QPoint & p)
{
	if (opts.real_paint) {
		if(points.size() > 2)
			points.erase(points.end() - 2);
		if (points.size() == 1)
			points.push_back(p);
		points.push_back(points.back());
		Path();
	}
}

void CardinalSpline::genSpline()
{
	if (!points.isEmpty() && !finished && !opts.real_paint) {
		points.push_front(points.front());
		points.push_back(points.back());
	}

	SplineABT::genSpline();
}

QPoint CardinalSpline::xy(int i, float u)
{
	float s = (1 - opts.tension) / 2;
	float a = -s * u  *u * u + 2 * s * u * u - s * u;
	float b = (2 - s)*u*u*u + (s - 3)*u*u + 1;
	float c = (s - 2) * u*u*u + (3 - 2 * s)*u*u + s*u;
	float d = s*u*u*u - s*u*u;
	float x = points[i - 1].x() * a + points[i].x() * b + points[i + 1].x() * c + points[i + 2].x()*d;
	float y = points[i - 1].y() * a + points[i].y() * b + points[i + 1].y() * c + points[i + 2].y()*d;

	return QPoint(x, y);
}


BezierSpline::BezierSpline()
{

}

BezierSpline::~BezierSpline()
{
}

void BezierSpline::draw(QPaintDevice *pd, const Options &opt)
{
    SplineABT::draw(pd, opt);

    QPainter pir(pd);
    pir.setRenderHint(QPainter::Antialiasing);
    for (int i = 0; i < size(); ++i)
        pir.drawEllipse((*this)[i], 2, 2);

    pir.drawPath(path);
}

void BezierSpline::Path()
{
	int n = (int)points.size();
	QVector<float> cb(n, 0);
	for(int k = 0; k < n;k++)
		cb[k] = combCoeff(n, k);

    if (!points.isEmpty()) {
        path.swap(QPainterPath());
        path.moveTo(points[0]);
        for (int j = 0; j < opts.interpolation; j++) {
			float u = (float)j / opts.interpolation;
            float x = 0.0, y = 0.0;
            for (int k = 0; k < n; k++) {
                float bezier = cb[k] * std::powf(u, k) * std::powf(1 - u, n - k);
                x += points[k].x() * bezier;
                y += points[k].y() * bezier;
            }
            path.lineTo(x, y);
        }
    }
}

void BezierSpline::_add(const QPoint &p)
{
	if (opts.real_paint)
		Path();
}

float BezierSpline::combCoeff(int n, int k)
{
	if (k == 0) return 1;

	return ((n - k + 1) / (float)k) * combCoeff(n, k - 1);
}


////////////////////
SplineABT* SplineBuilder::Build(Options::SplineType t)
{
	switch (t)
	{
	case Options::Cardinal:
		return new CardinalSpline();
	case Options::Bezier:
		return new BezierSpline();
	}

	return nullptr;
}