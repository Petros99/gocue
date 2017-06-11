/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionopen;
    QAction *actionnew;
    QAction *actionsave;
    QAction *actionquit;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *go_button;
    QPushButton *pushButton_7;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *cue_list;
    QHBoxLayout *horizontalLayout;
    QComboBox *action_select;
    QLineEdit *cue_note;
    QPushButton *add;
    QPushButton *remove;
    QMenuBar *menuBar;
    QMenu *menugocue;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1265, 621);
        MainWindow->setAcceptDrops(false);
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QStringLiteral("actionopen"));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QStringLiteral("actionnew"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        actionquit = new QAction(MainWindow);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(23, 13, 100, 210));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        go_button = new QPushButton(layoutWidget);
        go_button->setObjectName(QStringLiteral("go_button"));
        go_button->setMinimumSize(QSize(80, 80));
        go_button->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(go_button);

        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(130, 10, 431, 551));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        cue_list = new QTableWidget(layoutWidget1);
        cue_list->setObjectName(QStringLiteral("cue_list"));

        verticalLayout_2->addWidget(cue_list);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        action_select = new QComboBox(layoutWidget1);
        action_select->setObjectName(QStringLiteral("action_select"));
        action_select->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(action_select);

        cue_note = new QLineEdit(layoutWidget1);
        cue_note->setObjectName(QStringLiteral("cue_note"));

        horizontalLayout->addWidget(cue_note);

        add = new QPushButton(layoutWidget1);
        add->setObjectName(QStringLiteral("add"));
        add->setMaximumSize(QSize(60, 50));

        horizontalLayout->addWidget(add);

        remove = new QPushButton(layoutWidget1);
        remove->setObjectName(QStringLiteral("remove"));
        remove->setMaximumSize(QSize(60, 50));

        horizontalLayout->addWidget(remove);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1265, 20));
        menugocue = new QMenu(menuBar);
        menugocue->setObjectName(QStringLiteral("menugocue"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menugocue->menuAction());
        menugocue->addAction(actionnew);
        menugocue->addAction(actionopen);
        menugocue->addAction(actionsave);
        menugocue->addAction(actionquit);

        retranslateUi(MainWindow);
        QObject::connect(actionquit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(cue_note, SIGNAL(returnPressed()), add, SLOT(click()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "gocue", Q_NULLPTR));
        actionopen->setText(QApplication::translate("MainWindow", "open", Q_NULLPTR));
        actionnew->setText(QApplication::translate("MainWindow", "new", Q_NULLPTR));
        actionsave->setText(QApplication::translate("MainWindow", "save", Q_NULLPTR));
        actionquit->setText(QApplication::translate("MainWindow", "quit", Q_NULLPTR));
        go_button->setText(QApplication::translate("MainWindow", "GO", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "back", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "freeze", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "safe", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        cue_note->setText(QString());
        cue_note->setPlaceholderText(QApplication::translate("MainWindow", "enter note", Q_NULLPTR));
        add->setText(QApplication::translate("MainWindow", "add", Q_NULLPTR));
        remove->setText(QApplication::translate("MainWindow", "remove", Q_NULLPTR));
        menugocue->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
