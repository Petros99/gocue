#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include "cue.h"
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
    ui->cue_list->removeRow(index);  // TODO crashes the program
    if (cue_vector.size() == index) ui->cue_list->selectRow(index -1);
}

void MainWindow::on_actionopen_triggered() {
    QString f_name = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                    "",
                                                    tr("JSON (*.json)"));
    QFile in_file(f_name);

    if (!in_file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file.");
    }

    QByteArray in_data = in_file.readAll();  // file to byte array

    QJsonParseError error;  // holds errors
    QJsonDocument json_cues_doc = QJsonDocument::fromJson(in_data, &error);

    QJsonArray json_cues_vector = json_cues_doc.array();
     // byte array to json array

    // reset stuffs
    cue_vector.clear();
    ui->cue_list->clear();
    set_cue_list();

    for (int i = 0; i < json_cues_vector.size(); ++i) {
        QJsonObject current_json_obj = json_cues_vector.at(i).toObject();
        // vector item to json object
        newCue(current_json_obj["type"].toInt(), current_json_obj["note"].toString());
        // json object to a cue, which is added to cue_vector
    }

}


void MainWindow::on_actionsave_triggered()
{
    QString f_name = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                                "",
                                tr("JSON (*.json)"));
    QFile out_file(f_name);
    if (!out_file.open(QIODevice::WriteOnly)) {
        qWarning("Could not save file!");
        return;
    }


    QJsonArray cues;
    for(int i = 0; i < cue_vector.size(); ++i) {
        QJsonObject json_cue_obj;
        cue_vector.at(i)->write(json_cue_obj);
        // cue_vector to json cue vector
        cues.append(json_cue_obj);
    }

    QJsonDocument json_cues_doc;
    json_cues_doc.setArray(cues);

    // json cue vector to json doc

    QTextStream out (&out_file);
//    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    QString out_text = json_cues_doc.toJson();
    // json doc to text
    out << out_text;
    // text to file
    out_file.close();
}

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

void MainWindow::on_volumeControl_slide_valueChanged(int value)
{
   ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->volume = value;
   ui->volumeControl_spin->setValue(value);
}

void MainWindow::on_volumeControl_spin_valueChanged(int value)
{
   ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->volume = value;
   ui->volumeControl_slide->setValue(value);
}

void MainWindow::on_actionPopupTitleEntry_editingFinished()
{
   ((ActionPopup *)cue_vector.at(ui->cue_list->currentItem()->row()))->title = ui->actionPopupTitleEntry->text();
}

void MainWindow::on_actionPopupTextEntry_textChanged()
{
    ((ActionPopup *)cue_vector.at(ui->cue_list->currentItem()->row()))->text = ui->actionPopupTextEntry->toPlainText();
}
