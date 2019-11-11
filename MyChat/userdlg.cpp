#include "userdlg.h"
#include "ui_userdlg.h"

UserDlg::UserDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("局域网聊天工具"));
}

UserDlg::~UserDlg()
{
    delete ui;
}


QString UserDlg::getUserName() const
{
    return ui->lineEdit->text();
}

void UserDlg::on_pushButton_clicked()
{
    QDialog::accept();
}

