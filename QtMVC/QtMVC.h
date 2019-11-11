#ifndef QTMVC_H
#define QTMVC_H

#include <QMainWindow>

class QStandardItemModel;
class QDataWidgetMapper;
class QSortFilterProxyModel;

QT_BEGIN_NAMESPACE
namespace Ui { class QtMVC; }
QT_END_NAMESPACE

class QtMVC : public QMainWindow
{
    Q_OBJECT

public:
    QtMVC(QWidget *parent = nullptr);
    ~QtMVC();

    void Init();
    void BarChart();

private slots:
    void OnBtnFilterClicked();
    void OnBtnPreviousClicked();
    void OnBtnNextClicked();

private:
    Ui::QtMVC *ui;

    QStandardItemModel *model;  // 数据模型
    QDataWidgetMapper *mapper;  // 窗口映射器
    QSortFilterProxyModel *filterModel;     // 过滤器代理模型
};
#endif // QTMVC_H
