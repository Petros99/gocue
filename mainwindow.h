#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QTreeWidget>
#include <QtGui>
#include <QMessageBox>
#include "cue.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

void addCue(int index, std::string action, QString note);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionopen_triggered();
    void on_go_button_clicked();

    void on_add_clicked();

    void on_remove_clicked();

    void on_action_select_currentIndexChanged(const QString &arg1);

    void on_cue_list_editingFinished();

    void on_pushButton_4_clicked();

    void on_cue_note_returnPressed();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;
};

int error_message(QString text){
    // opens an error message
    QMessageBox msgBox;
    msgBox.setText("There was an error.");
    msgBox.setInformativeText(text);
    msgBox.setIcon(QMessageBox::Warning);
    return msgBox.exec();
}

std::vector<Cue> cue_vector;

#endif // MAINWINDOW_H
