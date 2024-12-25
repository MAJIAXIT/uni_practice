#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // Props
    QAction *actionsdfsdf;
    QAction *actionsdfsdf_2;
    QAction *actionsdfsdfs;
    QAction *actionsdfsdf_3;
    QAction *actionfile;
    QAction *actionedit;
    QAction *actionbuild;
    QAction *actiondebug;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_7;
    QToolButton *toolButton_4;
    QToolButton *toolButton_6;
    QToolButton *toolButton_5;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QToolButton *toolButton_9;
    QToolButton *toolButton_10;
    QToolButton *toolButton_8;
    QToolButton *toolButton_11;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFontComboBox *fontComboBox;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_15;
    QToolButton *toolButton_13;
    QToolButton *toolButton_14;
    QToolButton *toolButton_12;
    QSpacerItem *horizontalSpacer_2;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QFontComboBox *fontComboBox_2;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *toolButton_16;
    QToolButton *toolButton_17;
    QToolButton *toolButton_18;
    QToolButton *toolButton_19;
    QToolButton *toolButton_20;
    QSpacerItem *horizontalSpacer_5;
    QTreeWidget *treeWidget_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButton_21;
    QToolButton *toolButton_22;
    QToolButton *toolButton_23;
    QSpacerItem *horizontalSpacer_6;
    QFontComboBox *fontComboBox_3;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *toolButton_24;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *toolButton_25;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_14;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_12;
    QToolButton *toolButton_26;
    QToolButton *toolButton_27;
    QToolButton *toolButton_28;
    QToolButton *toolButton_29;
    QToolButton *toolButton_30;
    QToolButton *toolButton_31;
    QSpacerItem *horizontalSpacer_11;
    QMenuBar *menubar;
    QMenu *menupw_1;
    QMenu *menufile;
    QMenu *menuedit;
    QMenu *menubuild;
    QMenu *menudebug;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
};
#endif // MAINWINDOW_H
