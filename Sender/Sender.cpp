#include "Sender.h"
#include "ui_Sender.h"
#include <QtNetwork>

Sender::Sender(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sender)
    , sender(new QUdpSocket(this))
    , receiver(new QUdpSocket(this))
{
    ui->setupUi(this);

    receiver->bind(10000, QUdpSocket::ShareAddress);    // 绑定 UDP 接收端端口
    connect(receiver, &QUdpSocket::readyRead, this, &Sender::onReceive);
}

Sender::~Sender()
{
    delete ui;
}


void Sender::on_btnSend_clicked()
{
    QString text = ui->textEdit->toPlainText();     // 获取要发送的数据

    QString localHostName = QHostInfo::localHostName();     // 获取本地 Host 名称
    QHostInfo info = QHostInfo::fromName(localHostName);    // 获取本地 Host 信息
    foreach (QHostAddress address, info.addresses()) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol) {
            localAddress = address.toString();              // 获取本地 IP 地址
        }
    }

    QString sendData("[Sender] " + localHostName + "(" + localAddress + ")" + ": " + text);
    ui->textEditShow->append(sendData);

    sender->writeDatagram(text.toLocal8Bit(), text.length(), QHostAddress::Broadcast, ui->outPort->value());    // 发送数据
}

void Sender::onReceive()
{
    while(receiver->hasPendingDatagrams()) {
        QByteArray data;    // 创建字节数组
        data.resize(receiver->pendingDatagramSize());   // 重置数组大小
        receiver->readDatagram(data.data(), data.size());   // 保存接收数据
        ui->textEditShow->append("[Receiver] " + QString::fromLocal8Bit(data));
    }
}

void Sender::on_inPort_valueChanged(int arg1)
{
    receiver->close();      // 关闭 Socket
    receiver->bind(arg1, QUdpSocket::ShareAddress); // 重新绑定端口号
}
