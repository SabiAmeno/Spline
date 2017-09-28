#ifndef SPLINE_H
#define SPLINE_H

#include <QPoint>
#include <QVector>
#include <QMatrix4x4>
#include <QPainter>

//��������
typedef enum
{
	//Cardinal����
	Cardinal
} SplineType;

//����������ߵĲ���
struct Options
{
	SplineType sline_t = Cardinal;
	bool       real_paint = false;

	int        interpolation = 20;
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
	void genSpline();

protected:
	SplineABT() {}
	//�������߾��巽��
	virtual void Path() = 0;

	QPainterPath path;
	Options      opts;
	QVector<QPoint> points;
private:
    bool finished = false;
};

class CardinalSpline : public SplineABT
{
public:
	CardinalSpline() {}

	virtual void draw(QPaintDevice* pd, const Options& opt);
protected:
	virtual void Path();

private:
	/**
	* @param i ��i����
	* @param u ��i���㼰i+1����֮���n��������ÿ������Ϊu
	*          \sum_{k=0}^{n}u = length(i, i+1)
	*/
	QPoint xy(int i, float u);
};

#endif // SPLINE_H
