#ifndef SPLINE_H
#define SPLINE_H

#include <QPoint>
#include <QVector>
#include <QMatrix4x4>
#include <QPainter>

//����������ߵĲ���
struct Options
{
	//��������
	typedef enum
	{
		//Cardinal����
		Cardinal,
		Bezier
	} SplineType;

	SplineType sline_t = Cardinal;
	bool       real_paint = false;

	int        interpolation = 200;
	float      tension = 0;
};

class SplineABT
{
public:
	//��ӵ�
    void add(const QPoint& p);
	//������߻���
    void finish();

	//������������
	virtual void draw(QPaintDevice* pd, const Options& opt) { opts = opt; }
    int size();
    const QPoint& operator[](int index);

	//��λ
	void clear();

	//������������
	virtual void genSpline();

protected:
	SplineABT() {}
	//��ӵ��ִ����������
	virtual void _add(const QPoint& p) = 0;
	//�������߾��巽��
	virtual void Path() = 0;

	QPainterPath path;
	Options      opts;
	QVector<QPoint> points;
    bool finished = false;
};

class CardinalSpline : public SplineABT
{
public:
	CardinalSpline() {}

	virtual void draw(QPaintDevice* pd, const Options& opt);
	virtual void genSpline();
protected:
	virtual void Path();
	virtual void _add(const QPoint& p);
private:
	/**
	* @param i ��i����
	* @param u ��i���㼰i+1����֮���n��������ÿ������Ϊu
	*          \sum_{k=0}^{n}u = length(i, i+1)
	*/
	QPoint xy(int i, float u);
};

class BezierSpline : public SplineABT
{
public:
	BezierSpline();
    virtual ~BezierSpline();

    virtual void draw(QPaintDevice* pd, const Options& opt);
protected:
    virtual void Path();
	virtual void _add(const QPoint& p);
private:
    float combCoeff(int n, int k);
};

class SplineBuilder
{
public:
	~SplineBuilder() {}

	static SplineABT* Build(Options::SplineType t);
private:
	SplineBuilder() {}
};


#endif // SPLINE_H
