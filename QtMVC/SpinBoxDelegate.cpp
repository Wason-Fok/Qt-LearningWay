#include "SpinBoxDelegate.h"
#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(QObject* parent)
    :QItemDelegate(parent)
{

}

// 创建编辑器
QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 如果当前选择项索引值位于第 1 列，那么创建 Spinbox
    if(index.column() == 1) {
        QSpinBox *spinBox = new QSpinBox(parent);
        spinBox->setMinimum(0);
        spinBox->setMaximum(100);
        return spinBox;
    }

    return QItemDelegate::createEditor(parent, option, index);
}

// 设置编辑器数据
void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // 如果当前选择项索引值位于第 1 列，那么设置编辑器数据
    if(index.column() == 1) {
        int value = index.model()->data(index, Qt::DisplayRole).toInt();    // 根据当前索引值获取模型数据
        QSpinBox *spinBox = dynamic_cast<QSpinBox*>(editor);     // 将 QWidget 类型转为 QSpinBox 类型
        spinBox->setValue(value);
    }

    QItemDelegate::setEditorData(editor, index);
}

// 设置模型数据
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // 如果当前选择项索引值位于第 1 列，那么设置模型数据
    if(index.column() == 1) {
        QSpinBox *spinBox = dynamic_cast<QSpinBox*>(editor);
        model->setData(index, spinBox->value(), Qt::DisplayRole);   // 设置模型数据
    }

    QItemDelegate::setModelData(editor, model, index);
}

// 更新编辑器几何布局
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}





