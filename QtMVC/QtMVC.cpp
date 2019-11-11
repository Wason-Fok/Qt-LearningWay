#include "QtMVC.h"
#include "ui_QtMVC.h"
#include <QStandardItemModel>
#include <SpinBoxDelegate.h>
#include <QtCharts>
#include <QGridLayout>
#include <QSortFilterProxyModel>
#include <QDataWidgetMapper>
#include <QRegExp>

QtMVC::QtMVC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtMVC)
{
    ui->setupUi(this);

    Init();
    BarChart();
}

QtMVC::~QtMVC()
{
    delete ui;
}

void QtMVC::Init()
{
    // 绑定信号槽
    connect(ui->btnFilter, &QPushButton::clicked, this, &QtMVC::OnBtnFilterClicked);
    connect(ui->btnPrevious, &QPushButton::clicked, this, &QtMVC::OnBtnPreviousClicked);
    connect(ui->btnNext, &QPushButton::clicked, this, &QtMVC::OnBtnNextClicked);



    filterModel = new QSortFilterProxyModel(this);  // 创建过滤代理数据模型
    mapper = new QDataWidgetMapper(this);           // 创建窗口映射器

    // 创建标准数据模型
    model = new QStandardItemModel(3, 2, this);

    model->setItem(0, 0, new QStandardItem(tr("小明")));
    model->setItem(0, 1, new QStandardItem("90"));
    model->setItem(1, 0, new QStandardItem(tr("小刚")));
    model->setItem(1, 1, new QStandardItem("75"));
    model->setItem(2, 0, new QStandardItem(tr("小红")));
    model->setItem(2, 1, new QStandardItem("80"));

    model->setHorizontalHeaderItem(0, new QStandardItem(tr("名称")));   // 设置第 0 列标题
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("分数")));   // 设置第 1 列标题

    // 为视图设置自定义的委托类
    SpinBoxDelegate *delegate = new SpinBoxDelegate(this);
    ui->tableView->setItemDelegate(delegate);

    // 为过滤代理模型以及窗口映射器绑定模型
    filterModel->setSourceModel(model);
    mapper->setModel(model);

    // 窗口映射器映射数据
    mapper->addMapping(ui->lineEditName, 0);
    mapper->addMapping(ui->lineEditScore, 1);
    mapper->toFirst();

    ui->tableView->setModel(filterModel);     // 为视图设置模型
}

// 创建柱状图表
void QtMVC::BarChart()
{
    // 创建学生分数集合
    QBarSet *set = new QBarSet(tr("分数"));
    int count = ui->tableView->model()->rowCount();     // 获取条目数量
    for(int i = 0; i < count; i++) {    // 获取分数
        int score = ui->tableView->model()->index(i, 1).data().toInt();
        *set << score;      // 保存分数
    }

    // 将以上的分数集合数量进行分类，每一个分数从而代表一个学生的分数
    // 如果存在多个集合，那么将根据每个集合的第一个索引值分为一类、第二个索引值分为一类、以此类推
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // 创建图表对象，并添加成员类别
    QChart *chart = new QChart();
    chart->addSeries(series);       // 像图标添加类别
    chart->setTitle(tr("学生分数"));    // 设置图表标题
    chart->setAnimationOptions(QChart::SeriesAnimations);   // 设置图表打开动画

    // 创建默认图标坐标轴
    chart->createDefaultAxes();

    // 创建分类图表轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QStringList studentName;    // 学生姓名列表
    for(int i = 0; i < count; i++) {
        QString name = ui->tableView->model()->index(i, 0).data().toString();   // 获取姓名
        studentName << name;
    }
    axisX->append(studentName);     // 将姓名列表添加到坐标轴中
    chart->addAxis(axisX, Qt::AlignBottom);     // 在视图底部添加分类图表轴
    series->attachAxis(axisX);      // 将分类图标轴绑定到类别



    // 显示图标图例对象，并将其以下部对齐
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 创建图表视图，并设置渲染模式为抗锯齿
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 将视图添加到布局管理器中
    ui->gridLayout->addWidget(chartView, 0, 1);

    chartView->show();

}

void QtMVC::OnBtnFilterClicked()
{
    QRegExp rx(ui->lineEditFilter->text());
    filterModel->setFilterRegExp(rx);
}

void QtMVC::OnBtnPreviousClicked()
{
    mapper->toPrevious();
}

void QtMVC::OnBtnNextClicked()
{
    mapper->toNext();
}


