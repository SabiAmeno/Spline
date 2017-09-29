#ifndef PIXELFUN_H
#define PIXELFUN_H

#include <QMainWindow>

namespace Ui {
class mainwindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void genSpline();
	void repaintSpline();
	void interpolateChanged(int v);
	void smoothChanged(double v);
	void realTimeRender(int);
	void splineTypeChanged(int);
	void addCtrlPoint(int);
private:
    void init();
private:
    Ui::mainwindow *ui;
};

#endif // PIXELFUN_H
