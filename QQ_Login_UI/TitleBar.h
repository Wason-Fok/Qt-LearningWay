#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QTimer>

class QLabel;
class QPushButton;

enum ButtonType {
    MIN_CLOSE_BUTTON = 0,         // 最小化和关闭按钮
    MIN_MAX_CLOSE_BUTTON,         // 最小化、最大化和关闭按钮
    ONLY_CLOSE_BUTTON             // 只有关闭按钮
};

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent);

    // 设置标题栏背景色及是否设置标题栏背景色透明
    void setBackgroundColor(int r, int g, int b, bool isTransparent = false);

    // 设置标题栏图标
    void setTitleIcon(const QString &filePath, QSize iconSize = QSize(25, 25));

    // 设置标题栏内容
    void setTitleContent(const QString &titleContent, int titleFontSize = 9);

    // 设置标题栏宽度
    void setTitleWidth(int width);

    // 设置标题栏上按钮类型
    void setButtonType(ButtonType buttontype);

    // 设置标题栏中的标题是否会滚动
    void setTitleRoll();

    // 设置窗口边框宽度
    void setWindowBorderWidth(int borderWidth);

    // 保存/获取 最大化前窗口的位置及大小
    void saveRestoreInfo(const QPoint point, const QSize size);
    void getRestoreInfo(QPoint &point, QSize &size);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    // 按钮触发的信号
    void BtnMinClicked();
    void BtnRestoreClicked();
    void BtnMaxClicked();
    void BtnCloseClicked();

public slots:
    // 按钮触发的槽
    void OnBtnMinClicked();
    void OnBtnRestoreClicked();
    void OnBtnMaxClicked();
    void OnRollTitle();

    void OnBtnCloseClicked();
private:
    // 初始化控件
    void initControl();

    // 绑定信号和槽
    void initConnections();

    // 加载样式文件
    void loadStyleSheet(const QString &sheetName);

private:
    QLabel* m_pTitleIcon;        // 标题栏图标
    QLabel* m_pTitleBar;         // 标题栏
    QPushButton* m_pBtnMin;      // 最小化按钮
    QPushButton* m_pBtnRestore;  // 最大化还原按钮
    QPushButton* m_pBtnMax;      // 最大化按钮
    QPushButton* m_pBtnClose;    // 关闭按钮

    // 标题栏背景色
    int m_colorR;   // 红
    int m_colorG;   // 绿
    int m_colorB;   // 蓝

    // 记录最大化，最小化窗口位置和大小
    QPoint m_restorePos;
    QSize m_restoreSize;

    // 移动窗口判断鼠标按下与否以及鼠标按下时的起始位置
    bool m_isPressed;
    QPoint m_startMovePos;

    QTimer m_titleRollTimer;    // 标题栏滚动效果时钟
    QString m_titleContent;     // 标题栏内容
    ButtonType m_buttonType;    // 按钮类型
    int m_windowBorderWidth;    // 窗口边框宽度
    bool m_isTransparent;       // 标题栏是否透明
    int m_btnHeight;            // 按钮高度
    int m_btnWidth;             // 按钮宽度
    int m_titleHeight;          // 标题栏高度
};

#endif // TITLEBAR_H























