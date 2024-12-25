#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    this->resize(400, 300);

    centralwidget = new QWidget(this);
    mainGrid = new QGridLayout(centralwidget);
    mainLayout = new QVBoxLayout();

    verticalSpacer = new QSpacerItem(20,
                                     40,
                                     QSizePolicy::Policy::Minimum,
                                     QSizePolicy::Policy::Expanding);

    btnGroup = new BtnGroup(centralwidget);
    btnGroup->setButtonCount(6);
    btnGroup->setOrientation(Qt::Vertical);

    stateLabel = new QLabel(centralwidget);
    stateLabel->setText("No buttons clicked");

    rotateButton = new QPushButton(centralwidget);
    rotateButton->setText("Rotate");
    connect(rotateButton, &QPushButton::clicked, this, &MainWindow::rotateButtonOnClick);

    addBtnButton = new QPushButton(centralwidget);
    addBtnButton->setText("Add button");
    connect(addBtnButton, &QPushButton::clicked, this, &MainWindow::addBtnButtonOnClick);

    removeBtnButton = new QPushButton(centralwidget);
    removeBtnButton->setText("Remove button");
    connect(removeBtnButton, &QPushButton::clicked, this, &MainWindow::removeBtnButtonOnClick);

    int btnsCnt = btnGroup->getButtonsCount();
    for (int i = 0; i < btnsCnt; i++) {
        setBtnGroupButtonOnClick(i);
    }

    mainLayout->addWidget(btnGroup);
    mainLayout->addItem(verticalSpacer);
    mainLayout->addWidget(stateLabel);
    mainLayout->addWidget(rotateButton);
    mainLayout->addWidget(addBtnButton);
    mainLayout->addWidget(removeBtnButton);

    mainGrid->addLayout(mainLayout, 0, 0);

    this->setCentralWidget(centralwidget);
}

void MainWindow::setBtnGroupButtonOnClick(int buttonIdx)
{
    auto btn = btnGroup->getButton(buttonIdx);
    connect(btn, &QPushButton::clicked, this, [this, buttonIdx]() {
        stateLabel->setText(QString("Button %1 clicked!").arg(buttonIdx + 1));
    });
}

void MainWindow::rotateButtonOnClick()
{
    if (btnGroup->getOrientation() == Qt::Horizontal) {
        btnGroup->setOrientation(Qt::Vertical);
    } else {
        btnGroup->setOrientation(Qt::Horizontal);
    }
}

void MainWindow::addBtnButtonOnClick()
{
    int btnCount = btnGroup->getButtonsCount();
    if (btnCount < 10) {
        btnCount++;
        btnGroup->setButtonCount(btnCount);
        setBtnGroupButtonOnClick(btnCount - 1);
        stateLabel->setText(QString("Button added. Buttons count: %1").arg(btnCount));
    } else {
        stateLabel->setText(QString("There are too many buttons already"));
    }
}

void MainWindow::removeBtnButtonOnClick()
{
    int btnCount = btnGroup->getButtonsCount();
    if (btnCount > 5) {
        btnCount--;
        btnGroup->setButtonCount(btnCount);
        stateLabel->setText(QString("Button removed. Buttons count: %1").arg(btnCount));
    } else {
        stateLabel->setText(QString("There are too few buttons already"));
    }
}

MainWindow::~MainWindow() {}
