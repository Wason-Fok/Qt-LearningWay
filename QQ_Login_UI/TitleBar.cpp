#include "TitleBar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    m_colorR(50),
    m_colorG(50),
    m_colorB(50),
    m_isPressed(false),
    m_buttonType(MIN_MAX_CLOSE_BUTTON),
    m_windowBorderWidth(0),
    m_isTransparent(false),
    m_btnHeight(30),
    m_btnWidth(30),
    m_titleHeight(30)
{
    // 初始化
    initControl();

    // 绑定按钮信号
    initConnections();

    // 加载本地样式
    this->loadStyleSheet(":/MyWin/Title.css");
}

// 设置标题栏背景色,在 paintEvent 事件中进行绘制标题栏背景色
// 在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void TitleBar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    m_isTransparent = isTransparent;

    this->update();
}

// 设置标题栏图标
void TitleBar::setTitleIcon(const QString &filePath, QSize iconSize)
{
    QPixmap titleIcon(filePath);
    // 设置标题栏图标，并设置到指定大小
    m_pTitleIcon->setPixmap(titleIcon.scaled(iconSize));
}

// 设置标题栏内容
void TitleBar::setTitleContent(const QString &titleContent, int titleFontSize)
{
    // 设置标题栏字体大小
    QFont font = m_pTitleBar->font();
    font.setPointSize(titleFontSize);
    m_pTitleBar->setFont(font);

    // 设置标题栏内容
    m_pTitleBar->setText(titleContent);
    m_titleContent = titleContent;
}

// 设置标题栏为固定宽度
void TitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

// 设置标题栏上的按钮类型
void TitleBar::setButtonType(ButtonType buttontype)
{
    m_buttonType = buttontype;

    switch(buttontype) {

    // 显示最小化和关闭按钮
    case MIN_CLOSE_BUTTON:
        m_pBtnRestore->setVisible(false);       // 设置按钮不可见
        m_pBtnMax->setVisible(false);
        break;

    // 显示最小化、最大化、关闭按钮
    case MIN_MAX_CLOSE_BUTTON:
        m_pBtnRestore->setVisible(false);
        break;

    // 只显示关闭按钮
    case ONLY_CLOSE_BUTTON:
        m_pBtnMin->setVisible(false);
        m_pBtnRestore->setVisible(false);
        m_pBtnMax->setVisible(false);
        break;
    }
}

// 设置标题栏中的标题是否会自动滚动，跑马灯的效果
void TitleBar::setTitleRoll()
{
    connect(&m_titleRollTimer, &QTimer::timeout, this, &TitleBar::OnRollTitle);
    // 设置定时器为 200ms
    m_titleRollTimer.start(200);
}

// 设置窗口边框宽度
void TitleBar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

// 保存窗口最大化前窗口的位置以及大小
void TitleBar::saveRestoreInfo(const QPoint point, const QSize size)
{
    m_restorePos = point;
    m_restoreSize = size;
}

// 获取窗口最大化前的窗口位置及大小
void TitleBar::getRestoreInfo(QPoint &point, QSize &size)
{
    point = m_restorePos;
    size = m_restoreSize;
}

// 绘制标题栏背景色
void TitleBar::paintEvent(QPaintEvent *event)
{
    // 判断是否设置标题透明
    if (!m_isTransparent) {
        // 绘画标题栏背景
        QPainter painter(this);
        QPainterPath pathBack;

        // 设置填充模式为全部填充
        pathBack.setFillRule(Qt::WindingFill);

        // 设置矩形圆角
        pathBack.addRoundedRect(QRect(0 , 0, this->width(), this->height()), 3, 3);

        // 开启 painter 防锯齿效果
        painter.setRenderHint(QPainter::Antialiasing, true);

        // 绘画指定路径
        painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    }

    // 当窗口最大化或者还原后，窗口宽度变了，标题栏的宽度应当一起改变
    // 这里减去 m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框
    // 如果窗口有边框则需要设置 m_windowBorderWidth 的值，否则 m_windowBorderWidth 默认为 0
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth)) {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }

    // 将 event 状态返回给 QWidget
    QWidget::paintEvent(event);
}

// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 只有存在最大化、还原按钮时双击才有效
    if (m_buttonType == MIN_MAX_CLOSE_BUTTON) {

        // 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态
        // 或者通过单独设置变量来表示当前窗口状态
        if (m_pBtnMax->isVisible()) {
            OnBtnMaxClicked();
        } else {
            OnBtnRestoreClicked();
        }
    }

    // 将双击事件返回给 QWidget
    QWidget::mouseDoubleClickEvent(event);
}

// 鼠标按下事件
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    // 如果按钮包含最大化、还原按钮，并且最大化按钮可见时才允许拖动
    if (m_buttonType == MIN_MAX_CLOSE_BUTTON) {
        // 窗口最大化时禁止拖动窗口
        if (m_pBtnMax->isVisible()) {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
    } else {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    // 鼠标按下事件返回给 QWidget
    QWidget::mousePressEvent(event);
}

// 鼠标移动事件
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed) {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }

    // 鼠标移动事件返回给 QWidget
    QWidget::mouseMoveEvent(event);
}

// 鼠标释放事件
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;

    // 鼠标释放事件返回给 QWidget
    QWidget::mouseReleaseEvent(event);
}

// 最小化按钮
void TitleBar::OnBtnMinClicked()
{
    emit BtnMinClicked();
}

// 窗口复原按钮
void TitleBar::OnBtnRestoreClicked()
{
    m_pBtnRestore->setVisible(false);
    m_pBtnMax->setVisible(true);
    emit BtnRestoreClicked();
}

// 最大化按钮
void TitleBar::OnBtnMaxClicked()
{
    m_pBtnMax->setVisible(false);
    m_pBtnRestore->setVisible(true);
    emit BtnMaxClicked();
}

// 关闭按钮
void TitleBar::OnBtnCloseClicked()
{
    emit BtnCloseClicked();
}

// 该方法主要是让标题栏中的标题显示为滚动的效果
void TitleBar::OnRollTitle()
{
    static int nPos = 0;
    QString titleContent = m_titleContent;

    // 当截取的位置比字符串长时，从头开始;
    if (nPos > titleContent.length()) {
        nPos = 0;
    }
    m_pTitleBar->setText(titleContent.mid(nPos));
    nPos++;
}

void TitleBar::initControl()
{

    m_pTitleIcon = new QLabel(this);
    m_pTitleBar = new QLabel(this);

    m_pBtnMin = new QPushButton(this);
    m_pBtnRestore = new QPushButton(this);
    m_pBtnMax = new QPushButton(this);
    m_pBtnClose = new QPushButton(this);

    // 设置按钮大小
    m_pBtnMin->setFixedSize(QSize(m_btnWidth, m_btnHeight));
    m_pBtnRestore->setFixedSize(QSize(m_btnWidth, m_btnHeight));
    m_pBtnMax->setFixedSize(QSize(m_btnWidth, m_btnHeight));
    m_pBtnClose->setFixedSize(QSize(m_btnWidth, m_btnHeight));

    // 设置对象名称
    m_pTitleBar->setObjectName("TitleContent");
    m_pBtnMin->setObjectName("btnMin");
    m_pBtnRestore->setObjectName("btnRestore");
    m_pBtnMax->setObjectName("btnMax");
    m_pBtnClose->setObjectName("btnClose");

    // 设置按钮 ToolTip 提示信息
    m_pBtnMin->setToolTip(tr("Minimize"));
    m_pBtnRestore->setToolTip(tr("Restore"));
    m_pBtnMax->setToolTip(tr("Maximize"));
    m_pBtnClose->setToolTip(tr("Close"));

    // 创建横向布局并添加标题栏和标题栏图标
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(m_pTitleIcon);
    hLayout->addWidget(m_pTitleBar);

    // 向横向布局添加按钮
    hLayout->addWidget(m_pBtnMin);
    hLayout->addWidget(m_pBtnRestore);
    hLayout->addWidget(m_pBtnMax);
    hLayout->addWidget(m_pBtnClose);

    // 设置部件到布局器的左、上、右和下的页边距
    hLayout->setContentsMargins(5, 0, 0, 0);
    // 设置布局器内的控件之间间隔
    hLayout->setSpacing(0);

    // 控制标题栏：横向可以放大和缩小，纵向大小不变
    m_pTitleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 设置标题栏固定高度
    this->setFixedHeight(m_titleHeight);

}

void TitleBar::initConnections()
{
    // 绑定按钮信号
    connect(m_pBtnMin, &QPushButton::clicked, this, &TitleBar::OnBtnMinClicked);
    connect(m_pBtnRestore, &QPushButton::clicked, this, &TitleBar::OnBtnRestoreClicked);
    connect(m_pBtnMax, &QPushButton::clicked, this, &TitleBar::OnBtnMaxClicked);
    connect(m_pBtnClose, &QPushButton::clicked, this, &TitleBar::OnBtnCloseClicked);
}

// 加载本地样式文件
// 可以将样式直接写在文件中，程序运行时直接加载进来
void TitleBar::loadStyleSheet(const QString &sheetName)
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



























