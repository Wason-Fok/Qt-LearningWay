#include "BaseWindow.h"
#include <QPainter>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>

BaseWindow::BaseWindow(QWidget *parent) :
    QWidget(parent)
{
    // FramelessWindowHint 属性设置窗口去除边框
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    // 设置窗口背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 注意！！！如果是主窗口不要设置WA_DeleteOnClose属性;
    // 关闭窗口时释放资源;
    // setAttribute(Qt::WA_DeleteOnClose);

    // 初始化标题栏;
    initTitleBar();
}

BaseWindow::~BaseWindow()
{

}

void BaseWindow::paintEvent(QPaintEvent *event)
{
    // 设置背景色
    QPainter painter(this);
    QPainterPath pathBack;

    // 设置填充模式为全部填充
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);

    // 消除窗口锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(255, 255, 255)));

    QWidget::paintEvent(event);
}

void BaseWindow::initTitleBar()
{
    m_titleBar = new TitleBar(this);
    m_titleBar->move(0, 0);

    // m_titleBar->setButtonType(MIN_MAX_CLOSE_BUTTON);

    connect(m_titleBar, &TitleBar::BtnMinClicked, this, &BaseWindow::OnBtnMinClicked);
    connect(m_titleBar, &TitleBar::BtnRestoreClicked, this, &BaseWindow::OnBtnRestoreClicked);
    connect(m_titleBar, &TitleBar::BtnMaxClicked, this, &BaseWindow::OnBtnMaxClicked);
    connect(m_titleBar, &TitleBar::BtnCloseClicked, this, &BaseWindow::OnBtnCloseClicked);
}

void BaseWindow::loadStyleSheet(const QString &sheetName)
{
    QFile file(sheetName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (file.isOpen()) {
        QString styleSheet = this->styleSheet();
        styleSheet += file.readAll();
        this->setStyleSheet(styleSheet);
        file.close();
    }
}

// 窗口最小化
void BaseWindow::OnBtnMinClicked()
{
    this->showMinimized();
}

// 窗口复原
void BaseWindow::OnBtnRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::OnBtnMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    // 获取当前桌面可用空间
    QRect desktopRect = QGuiApplication::primaryScreen()->availableGeometry();

    QRect factRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(factRect);
}

void BaseWindow::OnBtnCloseClicked()
{
    this->close();
}




































