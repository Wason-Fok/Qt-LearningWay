#ifndef MYWIN_H
#define MYWIN_H

#include <QWidget>
#include <BaseWindow.h>

namespace Ui {
class MyWin;
}

class QPushButton;

// 登录状态
typedef enum {
    ONLINE = 1,     // 在线
    ACTIVE,         // 活跃
    AWAY,           // 离开
    BUSY,           // 忙碌
    NOT_DISTURB,    // 请勿打扰
    HIDE,           // 隐身
    OFFLINE         // 离线
}LoginState;

class MyWin : public BaseWindow
{
    Q_OBJECT

public:
    explicit MyWin(QWidget *parent = nullptr);
    ~MyWin();

private:
    // 初始化标题栏
    void initMyTitle();

    // 初始化窗口
    void initWindow();

private:
    Ui::MyWin *ui;
    QPushButton* m_keyboardButton;  // 密码框小键盘按钮
};

#endif // MYWIN_H
