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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
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
    QFrame *actionPopupSettings;
    QLineEdit *actionPopupTitleEntry;
    QTextEdit *actionPopupTextEntry;
    QFrame *actionPlayAudioFileSettings;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *volumeControlLabel;
    QGridLayout *gridLayout;
    QSpinBox *volumeControl_spin;
    QSlider *volumeControl_slide;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *selectAudioFileButton;
    QLineEdit *selectAudioFileLineEdit;
    QLCDNumber *playbackPassedLcd;
    QLCDNumber *playbackRemainLcd;
    QFrame *actionNoneSettings;
    QVBoxLayout *verticalLayout_3;
    QLabel *no_selected_cue_label;
    QMenuBar *menuBar;
    QMenu *menugocue;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(944, 621);
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

        actionPopupSettings = new QFrame(centralWidget);
        actionPopupSettings->setObjectName(QStringLiteral("actionPopupSettings"));
        actionPopupSettings->setGeometry(QRect(570, 10, 331, 521));
        actionPopupSettings->setAutoFillBackground(false);
        actionPopupSettings->setFrameShape(QFrame::StyledPanel);
        actionPopupSettings->setFrameShadow(QFrame::Sunken);
        actionPopupTitleEntry = new QLineEdit(actionPopupSettings);
        actionPopupTitleEntry->setObjectName(QStringLiteral("actionPopupTitleEntry"));
        actionPopupTitleEntry->setGeometry(QRect(1, 1, 330, 26));
        actionPopupTextEntry = new QTextEdit(actionPopupSettings);
        actionPopupTextEntry->setObjectName(QStringLiteral("actionPopupTextEntry"));
        actionPopupTextEntry->setGeometry(QRect(1, 27, 330, 70));
        actionPlayAudioFileSettings = new QFrame(centralWidget);
        actionPlayAudioFileSettings->setObjectName(QStringLiteral("actionPlayAudioFileSettings"));
        actionPlayAudioFileSettings->setGeometry(QRect(570, 10, 331, 521));
        actionPlayAudioFileSettings->setFrameShape(QFrame::StyledPanel);
        actionPlayAudioFileSettings->setFrameShadow(QFrame::Sunken);
        layoutWidget2 = new QWidget(actionPlayAudioFileSettings);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 331, 61));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, -1, -1, -1);
        volumeControlLabel = new QLabel(layoutWidget2);
        volumeControlLabel->setObjectName(QStringLiteral("volumeControlLabel"));
        QFont font;
        font.setBold(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        font.setKerning(true);
        volumeControlLabel->setFont(font);
        volumeControlLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(volumeControlLabel);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        volumeControl_spin = new QSpinBox(layoutWidget2);
        volumeControl_spin->setObjectName(QStringLiteral("volumeControl_spin"));
        volumeControl_spin->setMaximum(100);

        gridLayout->addWidget(volumeControl_spin, 0, 0, 1, 1);

        volumeControl_slide = new QSlider(layoutWidget2);
        volumeControl_slide->setObjectName(QStringLiteral("volumeControl_slide"));
        volumeControl_slide->setAutoFillBackground(false);
        volumeControl_slide->setMaximum(100);
        volumeControl_slide->setValue(100);
        volumeControl_slide->setOrientation(Qt::Horizontal);
        volumeControl_slide->setInvertedAppearance(false);
        volumeControl_slide->setInvertedControls(false);
        volumeControl_slide->setTickPosition(QSlider::NoTicks);
        volumeControl_slide->setTickInterval(0);

        gridLayout->addWidget(volumeControl_slide, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        selectAudioFileButton = new QPushButton(layoutWidget2);
        selectAudioFileButton->setObjectName(QStringLiteral("selectAudioFileButton"));

        horizontalLayout_3->addWidget(selectAudioFileButton);

        selectAudioFileLineEdit = new QLineEdit(layoutWidget2);
        selectAudioFileLineEdit->setObjectName(QStringLiteral("selectAudioFileLineEdit"));

        horizontalLayout_3->addWidget(selectAudioFileLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_3);

        playbackPassedLcd = new QLCDNumber(actionPlayAudioFileSettings);
        playbackPassedLcd->setObjectName(QStringLiteral("playbackPassedLcd"));
        playbackPassedLcd->setGeometry(QRect(10, 90, 64, 23));
        playbackRemainLcd = new QLCDNumber(actionPlayAudioFileSettings);
        playbackRemainLcd->setObjectName(QStringLiteral("playbackRemainLcd"));
        playbackRemainLcd->setGeometry(QRect(250, 100, 64, 23));
        actionNoneSettings = new QFrame(centralWidget);
        actionNoneSettings->setObjectName(QStringLiteral("actionNoneSettings"));
        actionNoneSettings->setGeometry(QRect(570, 10, 331, 521));
        actionNoneSettings->setFrameShape(QFrame::StyledPanel);
        actionNoneSettings->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(actionNoneSettings);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        no_selected_cue_label = new QLabel(actionNoneSettings);
        no_selected_cue_label->setObjectName(QStringLiteral("no_selected_cue_label"));
        no_selected_cue_label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(no_selected_cue_label);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        actionNoneSettings->raise();
        actionPopupSettings->raise();
        actionPlayAudioFileSettings->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 944, 20));
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
        actionPopupTitleEntry->setText(QString());
        actionPopupTitleEntry->setPlaceholderText(QApplication::translate("MainWindow", "popup title", Q_NULLPTR));
        actionPopupTextEntry->setPlaceholderText(QApplication::translate("MainWindow", "popup text", Q_NULLPTR));
        volumeControlLabel->setText(QApplication::translate("MainWindow", "volume", Q_NULLPTR));
        selectAudioFileButton->setText(QApplication::translate("MainWindow", "select file", Q_NULLPTR));
        no_selected_cue_label->setText(QApplication::translate("MainWindow", "please select a cue", Q_NULLPTR));
        menugocue->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
