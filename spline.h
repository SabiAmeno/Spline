#ifndef SPLINE_H
#define SPLINE_H

#include <QPoint>
#include <QVector>
#include <QMatrix4x4>
#include <QPainter>

//存放样条曲线的参数
struct Options
{
	//样条类型
	typedef enum
	{
		//Cardinal样条
		Cardinal,
		Bezier
	} SplineType;

	typedef enum {
		NoOp,
		//添加控制点模式
		AddCtrlPos,
		//调整控制点位置模式
		AdjustCtrlPos
	}OpMode;

	//绘图模式控制
	bool       real_paint = false;
	OpMode     add_cp_mode = AddCtrlPos;
	SplineType sline_t = Cardinal;
	
	//样条参数
	int        interpolation = 1000;
	float      tension = 0;

	//绘图参数
	QColor     endp_color = Qt::black;
	QColor     line_color = Qt::black;
};

class SplineABT
{
public:
	//添加点
    void add(const QPoint& p);
	//完成曲线绘制
    void finish();
	bool isFinished() { return finished; }

	//绘制样条曲线
	virtual void draw(QPaintDevice*, const Options& opt) { opts = opt; }
    int size();
	const QPoint& at(int index);
	int at(const QPoint& p);
	QPoint& operator[](int index);

	//复位
	void clear();

	//生成样条曲线
	virtual void genSpline();

protected:
	SplineABT() {}
	//添加点后执行其它代码
	virtual void _add(const QPoint& p) = 0;
	//生成曲线具体方法
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
	* @param i 第i个点
	* @param u 第i个点及i+1个点之间的n个步长，每个步长为u
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
	QVector<float> computeCoeff(int n);
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
