#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::genSpline()
{
	int inter = ui->slider_2->value();
	double smooth = ui->slider_1->value();
	ui->u_cv->options.interpolation = inter;
	ui->u_cv->options.tension = smooth;
	ui->u_cv->genSpline(true);
	ui->u_cv->update();
}

void MainWindow::repaintSpline()
{
	ui->u_cv->repaint();
	ui->u_cv->update();
}

void MainWindow::interpolateChanged(int v)
{
	ui->u_cv->options.interpolation = v;
	ui->u_cv->genSpline();
	ui->u_cv->update();

	ui->int_plo->setText(QString::number(v));
}

void MainWindow::smoothChanged(double v)
{
	ui->u_cv->options.tension = v;
	ui->u_cv->genSpline();
	ui->u_cv->update();

	ui->slide_dg->setText(QString::number(v));
}

void MainWindow::realTimeRender(int s)
{
	ui->u_cv->options.real_paint = bool(s);
	ui->u_cv->genSpline();
	ui->u_cv->update();
}

void MainWindow::splineTypeChanged(int index)
{
	ui->u_cv->options.sline_t = (SplineType)index;
	ui->u_cv->genSpline();
	ui->u_cv->update();
}

void MainWindow::init()
{
	ui->slider_1->setValue(0);
	ui->slider_2->setValue(20);
	connect(ui->gen_line, &QPushButton::clicked, this, &MainWindow::genSpline);
	connect(ui->repaint_btn, &QPushButton::clicked, this, &MainWindow::repaintSpline);
	connect(ui->slider_1, SIGNAL(valueChanged(double)), this, SLOT(smoothChanged(double)));
	connect(ui->slider_2, &QSlider::valueChanged, this, &MainWindow::interpolateChanged);
	connect(ui->real_time, &QCheckBox::stateChanged, this, &MainWindow::realTimeRender);
	connect(ui->samp_box, SIGNAL(currentIndexChanged(int)), this, SLOT(splineTypeChanged(int)));
}
