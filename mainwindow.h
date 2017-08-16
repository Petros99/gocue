#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QTreeWidget>
#include <QtGui>
#include <QMessageBox>

#include <cue.h> // requried here for type cue, also requried by mainwindow.cpp

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

    void on_actionsave_triggered();

    void insertCue(Cue * cue);

    void newCue(int type, QString note);

    void on_action_select_currentIndexChanged();

    void set_cue_list();

    void on_cue_list_itemSelectionChanged();

    void clear_actionSettings();

    void on_actionPopupTitleEntry_editingFinished();

    void on_actionPopupTextEntry_textChanged();

    void on_volumeControl_slide_valueChanged(int value);

    void on_volumeControl_spin_valueChanged(int arg1);

    void on_selectAudioFileButton_clicked();

    void on_selectAudioFileLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
