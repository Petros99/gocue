#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QObject>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QJsonArray>

QVector<Cue *> cue_vector;  // holds pointers to every cue in order
int current_row = 0;  // for cue_list gui element
int curr_cue_action_index = 0; // popup action is index 0
QStringList possible_actions = {"popup", "sound"};

void MainWindow::set_cue_list() {  // "reset" the cue_list element
    ui->cue_list->setColumnCount(2);
    QStringList headers;
    headers << "note" << "action";
    ui->cue_list->setHorizontalHeaderLabels(headers);
    ui->cue_list->setShowGrid(false);
    ui->cue_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cue_list->setSelectionMode(QAbstractItemView::SingleSelection);

}

void MainWindow::clear_actionSettings() {  // hide settings for all cue groups and no cue
    ui->actionPlayAudioFileSettings->hide();
    ui->actionPopupSettings->hide();
    ui->actionNoneSettings->hide();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->action_select->addItems(possible_actions); // action_select dropdown
    set_cue_list();
    clear_actionSettings();
    ui->actionNoneSettings->show();
   }

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::insertCue(Cue * cue) {
    QTableWidgetItem * note_itm = new QTableWidgetItem();
    note_itm->setText(cue->note);  // add the text to the note item

    QTableWidgetItem * action_itm = new QTableWidgetItem();
    action_itm->setText(possible_actions.at(curr_cue_action_index));  // add the text which describes the action

    int index = ui->cue_list->currentRow();
    if (index == -1) {  // index is at end
        index = cue_vector.size();  // set to end
     }
    else {  // index is not at end
        ++index;  // set to act on next item
     }

    ui->cue_list->insertRow(index);  // insert new row into the gui element
    ui->cue_list->setItem(index, 0, note_itm);  // put in the note item into cue_list
    ui->cue_list->setItem(index, 1, action_itm);  // put the action item into the cue_list
    cue_vector.insert(cue_vector.begin() + index, cue);  // add the cue to the vector

}

void MainWindow::on_go_button_clicked()
{
    // ensures current_row is never -1
    if (ui->cue_list->currentRow() != -1) current_row = ui->cue_list->currentRow();
    cue_vector.at(current_row)->go();
    ui->cue_list->selectRow(current_row + 1);  // go to next row
}

void MainWindow::newCue(int type, QString note) {
     // the cue types are listed in possible_actions
    switch (type) {
    case 0:
    {
        ActionPopup * cue = new ActionPopup;
        cue->note = note;
        insertCue(cue);
        break;

    }
    case 1:
    {
        ActionPlayAudioFile * cue = new ActionPlayAudioFile;
        cue->note = note;
        insertCue(cue);
        break;
    }
    default:  // should never happen
    {
        Cue * cue = new Cue;
        cue->note = note;
        insertCue(cue);
        qWarning("Something bad happened in newCue (default).");
        break;
    }
    }
    if (ui->cue_list->rowCount() == 1) {
        qDebug() << "one row";
        ui->cue_list->selectRow(0);
        clear_actionSettings();
        cue_vector.at(0)->show_ui(ui);
    }
}

void MainWindow::on_add_clicked()
{
    newCue(ui->action_select->currentIndex(), ui->cue_note->text());
}

void MainWindow::on_remove_clicked()
{
    int index = ui->cue_list->currentRow();
    if (cue_vector.isEmpty()) return;  // do nothing if no cues
    if (index == -1) return;  // do nothing if no cue selected
    if (cue_vector.size() == 1) {  // the last cue
        ui->cue_list->removeRow(0);
        ui->cue_list->clearContents();
        cue_vector.remove(index);
        clear_actionSettings();
        return;
    }
    if (index > 0) {
        // select cue above
        ui->cue_list->selectRow(index - 1);
    }

    else {
        // select cue below
        ui->cue_list->selectRow(index + 1);
    }
    cue_vector.remove(index);
    ui->cue_list->removeRow(index);
    if (cue_vector.size() == index) ui->cue_list->selectRow(index -1);
}

#include "saveandopen.cpp"
#include "actionplayaudiofilegui.cpp"
#include "actionpopupgui.cpp"

void MainWindow::on_action_select_currentIndexChanged()
{
    curr_cue_action_index = ui->action_select->currentIndex();
}

void MainWindow::on_cue_list_itemSelectionChanged()
{
    clear_actionSettings();
    if (ui->cue_list->rowCount() == 1) return;  // if this is the last item
    cue_vector.at(ui->cue_list->currentItem()->row())->show_ui(MainWindow::ui);
}
