#ifndef BTNGROUP_H
#define BTNGROUP_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "BtnGroup_global.h"

class BTNGROUP_EXPORT BtnGroup : public QWidget
{
    Q_OBJECT

public:
    explicit BtnGroup(QWidget *parent = nullptr);

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation getOrientation();

    void setButtonCount(int count);
    int getButtonsCount();

    void connectButton();

    QPushButton *getButton(int index) const;

private:
    void updateLayout();

    QList<QPushButton *> buttons;
    QLayout *layout;
    Qt::Orientation orientation;
};

#endif // BTNGROUP_H
