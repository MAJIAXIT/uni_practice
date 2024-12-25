// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLayoutTypeChanged(const QString &type);
    void addWidget();
    void saveForm();
    void loadForm();

private:
    Ui::MainWindow *ui;
    QWidget *formPreview;
    QLayout *currentLayout;
    QComboBox *layoutTypeCombo;
    QComboBox *widgetTypeCombo;
    QLineEdit *widgetTextEdit;
    
    void setupUI();
    void createNewLayout(const QString &type);
    QWidget* createWidget(const QString &type, const QString &text);
    void clearLayout(QLayout *layout);
    QJsonObject serializeForm();
    void deserializeForm(const QJsonObject &json);
};

#endif // MAINWINDOW_H