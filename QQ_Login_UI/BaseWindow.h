#include <QWidget>
#include "TitleBar.h"

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

protected:
    void paintEvent(QPaintEvent* event);
    void loadStyleSheet(const QString &sheetName);

private:
    void initTitleBar();

private slots:
    void OnBtnMinClicked();
    void OnBtnRestoreClicked();
    void OnBtnMaxClicked();
    void OnBtnCloseClicked();

protected:
    TitleBar* m_titleBar;
};
