// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h" 
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Main widget and layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    
    // Control panel
    QWidget *controlPanel = new QWidget;
    QVBoxLayout *controlLayout = new QVBoxLayout(controlPanel);
    
    // Layout type selection
    QLabel *layoutLabel = new QLabel("Layout Type:");
    layoutTypeCombo = new QComboBox;
    layoutTypeCombo->addItems({"VBox", "HBox", "Grid"});

    // Widget type selection
    QLabel *widgetLabel = new QLabel("Widget Type:");
    widgetTypeCombo = new QComboBox;
    widgetTypeCombo->addItems({"QPushButton", "QLabel", "QLineEdit"});
    
    // Widget text input
    QLabel *textLabel = new QLabel("Widget Text:");
    widgetTextEdit = new QLineEdit;
    
    // Control buttons
    QPushButton *addButton = new QPushButton("Add Widget");
    QPushButton *saveButton = new QPushButton("Save Form");
    QPushButton *loadButton = new QPushButton("Load Form");
    
    // Add controls to panel
    controlLayout->addWidget(layoutLabel);
    controlLayout->addWidget(layoutTypeCombo);
    controlLayout->addWidget(widgetLabel);
    controlLayout->addWidget(widgetTypeCombo);
    controlLayout->addWidget(textLabel);
    controlLayout->addWidget(widgetTextEdit);
    controlLayout->addWidget(addButton);
    controlLayout->addWidget(saveButton);
    controlLayout->addWidget(loadButton);
    controlLayout->addStretch();
    
    // Form preview
    formPreview = new QWidget;
    formPreview->setMinimumSize(400, 400);
    formPreview->setStyleSheet("background-color: #404040; border: 1px solid gray;");
    
    // Add panels to main layout
    mainLayout->addWidget(controlPanel);
    mainLayout->addWidget(formPreview);
    
    // Connect signals
    connect(layoutTypeCombo, &QComboBox::currentTextChanged, this, &MainWindow::onLayoutTypeChanged);
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addWidget);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveForm);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadForm);
    
    // Initialize with default layout
    onLayoutTypeChanged(layoutTypeCombo->currentText());
}

void MainWindow::onLayoutTypeChanged(const QString &type)
{
    createNewLayout(type);
}

void MainWindow::createNewLayout(const QString &type)
{
    if (currentLayout) {
        clearLayout(currentLayout);
        delete currentLayout;
    }
    
    if (type == "VBox") {
        currentLayout = new QVBoxLayout(formPreview);
    } else if (type == "HBox") {
        currentLayout = new QHBoxLayout(formPreview);
    } else if (type == "Grid") {
        currentLayout = new QGridLayout(formPreview);
    }
}

QWidget* MainWindow::createWidget(const QString &type, const QString &text)
{
    QWidget *widget = nullptr;
    
    if (type == "QPushButton") {
        widget = new QPushButton(text);
    } else if (type == "QLabel") {
        widget = new QLabel(text);
    } else if (type == "QLineEdit") {
        widget = new QLineEdit;
        static_cast<QLineEdit*>(widget)->setText(text);
    }
    
    return widget;
}

void MainWindow::addWidget()
{
    QString type = widgetTypeCombo->currentText();
    QString text = widgetTextEdit->text();
    
    QWidget *widget = createWidget(type, text);
    if (widget) {
        if (QGridLayout *gridLayout = qobject_cast<QGridLayout*>(currentLayout)) {
            int row = gridLayout->rowCount();
            gridLayout->addWidget(widget, row, 0);
        } else {
            currentLayout->addWidget(widget);
        }
    }
}

void MainWindow::saveForm()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Form", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Could not save file");
        return;
    }
    
    QJsonObject json = serializeForm();
    QJsonDocument doc(json);
    file.write(doc.toJson());
}

void MainWindow::loadForm()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Form", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    deserializeForm(doc.object());
}

QJsonObject MainWindow::serializeForm()
{
    QJsonObject json;
    json["layoutType"] = layoutTypeCombo->currentText();
    
    QJsonArray widgets;
    for (int i = 0; i < currentLayout->count(); ++i) {
        QWidget *widget = currentLayout->itemAt(i)->widget();
        if (!widget) continue;
        
        QJsonObject widgetJson;
        QString type;
        QString text;
        
        if (QPushButton *btn = qobject_cast<QPushButton*>(widget)) {
            type = "QPushButton";
            text = btn->text();
        } else if (QLabel *label = qobject_cast<QLabel*>(widget)) {
            type = "QLabel";
            text = label->text();
        } else if (QLineEdit *lineEdit = qobject_cast<QLineEdit*>(widget)) {
            type = "QLineEdit";
            text = lineEdit->text();
        }
        
        widgetJson["type"] = type;
        widgetJson["text"] = text;
        widgets.append(widgetJson);
    }
    
    json["widgets"] = widgets;
    return json;
}

void MainWindow::deserializeForm(const QJsonObject &json)
{
    QString layoutType = json["layoutType"].toString();
    layoutTypeCombo->setCurrentText(layoutType);
    createNewLayout(layoutType);
    
    QJsonArray widgets = json["widgets"].toArray();
    for (const QJsonValue &value : widgets) {
        QJsonObject widgetJson = value.toObject();
        QString type = widgetJson["type"].toString();
        QString text = widgetJson["text"].toString();
        
        QWidget *widget = createWidget(type, text);
        if (widget) {
            if (QGridLayout *gridLayout = qobject_cast<QGridLayout*>(currentLayout)) {
                int row = gridLayout->rowCount();
                gridLayout->addWidget(widget, row, 0);
            } else {
                currentLayout->addWidget(widget);
            }
        }
    }
}

void MainWindow::clearLayout(QLayout *layout)
{
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        if (QLayout *childLayout = item->layout()) {
            clearLayout(childLayout);
            childLayout->deleteLater();
        }
        delete item;
    }
}