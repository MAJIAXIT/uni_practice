#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include "btngroup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralwidget;

    BtnGroup *btnGroup;

    QLabel *stateLabel;

    QLayout *mainLayout;
    QGridLayout *mainGrid;

    QSpacerItem *verticalSpacer;

    QPushButton *rotateButton;
    QPushButton *addBtnButton;
    QPushButton *removeBtnButton;

    void setBtnGroupButtonOnClick(int buttonIdx);
    void setupUi();

private slots:
    void rotateButtonOnClick();
    void addBtnButtonOnClick();
    void removeBtnButtonOnClick();
};
#endif // MAINWINDOW_H
