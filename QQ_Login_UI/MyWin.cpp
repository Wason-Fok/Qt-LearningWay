#include "MyWin.h"
#include "ui_MyWin.h"
#include <QLabel>
#include <QMovie>
#include <QLineEdit>
#include <QHBoxLayout>

MyWin::MyWin(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::MyWin)
{
    ui->setupUi(this);
    setWindowTitle(tr("Tencent QQ"));
    initWindow();
    initMyTitle();

    // 调用父类函数加载 Qt 样式表
    loadStyleSheet(":/MyWin/MyWin.css");
}

MyWin::~MyWin()
{
    delete ui;
}

void MyWin::initMyTitle()
{
    // 因为这里有控件层叠了，所以要注意控件 raise( )方法的调用顺序
    // 将标题栏置为顶层
    m_titleBar->raise();
    // 设置标题栏背景色并将标题栏设置为透明
    m_titleBar->setBackgroundColor(0, 0, 0 , true);
    // 标题栏只显示最小化和关闭按钮
    m_titleBar->setButtonType(MIN_CLOSE_BUTTON);
    // 将标题栏宽度匹配到当前窗口
    m_titleBar->setTitleWidth(this->width());
    // 将箭头按钮置为最顶层
    ui->btnArrow->raise();
}

void MyWin::initWindow()
{
    // 背景 GIF 图片
    QLabel* pBack = new QLabel(this);
    QMovie* pMovie = new QMovie();
    pMovie->setFileName(":/MyWin/back.gif");
    pBack->setMovie(pMovie);
    pMovie->start();
    pBack->move(0, 0);

    // 设置输入注释
    ui->accountCmBox->setEditable(true);
    // 添加提示输入文本
    ui->accountCmBox->lineEdit()->setPlaceholderText(tr("ID/Mobile/E-mail"));
    ui->passwdLineEdit->setPlaceholderText(tr("Password"));

    // 密码框中的小键盘按钮
    m_keyboardButton = new QPushButton(this);
    m_keyboardButton->setObjectName("btnKeyboard");
    m_keyboardButton->setFixedSize(QSize(16, 16));
    // 将该按钮的鼠标指针设置为手指
    m_keyboardButton->setCursor(QCursor(Qt::PointingHandCursor));

    // 创建横向布局器
    QHBoxLayout* passwdEditLayout = new QHBoxLayout();
    // 想布局器内添加一个伸缩量
    passwdEditLayout->addStretch();
    // 添加小键盘按钮
    passwdEditLayout->addWidget(m_keyboardButton);
    // 设置布局器内各个控件的间距
    passwdEditLayout->setSpacing(0);
    // 设置部件到布局器的左、上、右和下的页边距
    passwdEditLayout->setContentsMargins(0, 0, 8, 0);

    // 向密码输入文本框内添加一个布局器
    ui->passwdLineEdit->setLayout(passwdEditLayout);
    // 设置边框内文本到左、上、右、下的边距
    ui->passwdLineEdit->setTextMargins(0, 0, m_keyboardButton->width() + 12, 0);

    // 添加用户头像
    ui->userHead->setPixmap(QPixmap(":/MyWin/HeadImage.png"));
    // 设置登录状态按钮图标以及图标大小
    ui->btnLoginState->setIcon(QIcon(":/MyWin/state_online.png"));
    ui->btnLoginState->setIconSize(QSize(13,13));
}





























