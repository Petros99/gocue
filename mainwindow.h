#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QTreeWidget>
#include <QtGui>
#include <QMessageBox>


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

#endif // MAINWINDOW_H
