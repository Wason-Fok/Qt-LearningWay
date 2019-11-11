#ifndef USERDLG_H
#define USERDLG_H

#include <QDialog>

namespace Ui {
class UserDlg;
}

class UserDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UserDlg(QWidget *parent = 0);
    ~UserDlg();
    QString getUserName() const;

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserDlg *ui;
};

#endif // USERDLG_H
