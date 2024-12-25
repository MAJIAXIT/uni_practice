#include "btngroup.h"

BtnGroup::BtnGroup(QWidget *parent)
    : QWidget(parent)
    , layout(nullptr)
    , orientation(Qt::Horizontal)
{
    setButtonCount(5);
}

void BtnGroup::setOrientation(Qt::Orientation newOrientation)
{
    if (orientation == newOrientation)
        return;

    orientation = newOrientation;
    updateLayout();
}

Qt::Orientation BtnGroup::getOrientation()
{
    return orientation;
}

int BtnGroup::getButtonsCount()
{
    return buttons.count();
}

void BtnGroup::setButtonCount(int count)
{
    while (buttons.size() > count) {
        delete buttons.takeLast();
    }
    while (buttons.size() < count) {
        QPushButton *button = new QPushButton(QString("Button %1").arg(buttons.size() + 1), this);
        buttons.append(button);
    }

    updateLayout();
}

QPushButton *BtnGroup::getButton(int index) const
{
    if (index >= 0 && index < buttons.size()) {
        return buttons[index];
    }
    return nullptr;
}

void BtnGroup::updateLayout()
{
    if (layout) {
        delete layout;
    }

    if (orientation == Qt::Horizontal) {
        layout = new QHBoxLayout(this);
    } else {
        layout = new QVBoxLayout(this);
    }

    for (QPushButton *button : buttons) {
        layout->addWidget(button);
    }

    setLayout(layout);
}
