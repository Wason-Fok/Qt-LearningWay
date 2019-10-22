#ifndef SENDER_H
#define SENDER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Sender; }
QT_END_NAMESPACE

class QUdpSocket;

class Sender : public QMainWindow
{
    Q_OBJECT

public:
    Sender(QWidget *parent = nullptr);
    ~Sender();

private slots:
    void on_btnSend_clicked();              // 发送按钮槽函数
    void onReceive();                       // UDP Socket 接收数据槽函数
    void on_inPort_valueChanged(int arg1);  // 更改输入端口槽函数

private:
    Ui::Sender *ui;
    QUdpSocket* sender;     // 发送端 UDP Socket
    QUdpSocket* receiver;   // 接收端 UDP Socket
    QString localAddress;   // 本地 IP 地址
};
#endif // SENDER_H
