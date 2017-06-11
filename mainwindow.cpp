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

QVector<Cue *> cue_vector;
int current_row = 0;
int curr_cue_action_index = 0; // popup
QStringList possible_actions = {"popup", "sound"};

void MainWindow::set_cue_list() {
     // the qTableWidget cue_list
    ui->cue_list->setColumnCount(2);
    QStringList headers;
    headers << "note" << "action";
    ui->cue_list->setHorizontalHeaderLabels(headers);
    ui->cue_list->setShowGrid(false);
    ui->cue_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cue_list->setSelectionMode(QAbstractItemView::SingleSelection);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // action_select dropdown
    ui->action_select->addItems(possible_actions);

    set_cue_list();

   }


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertCue(Cue * cue) {
    int index = ui->cue_list->currentRow();
    // if none selected, insert at end
    if (index == -1) index = cue_vector.size();

    ui->cue_list->insertRow(index);
    QTableWidgetItem * note_itm = new QTableWidgetItem();
    note_itm->setText(cue->note);

    QTableWidgetItem * action_itm = new QTableWidgetItem();
    action_itm->setText(possible_actions.at(curr_cue_action_index));
    ui->cue_list->setItem(index, 0, note_itm);
    ui->cue_list->setItem(index, 1, action_itm);

    cue_vector.insert(cue_vector.begin() + index, cue);
    qDebug() << "the cue_vector contains " << cue_vector.size();
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
        // should not use the default constructor when opening from file
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
        qWarning("Something bad happened in newCue(default).");
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

}

void MainWindow::on_actionopen_triggered() {
    QString f_name = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                    "",
                                                    tr("JSON (*.json)"));
    QFile in_file(f_name);

    if (!in_file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file.");
    }

    QByteArray in_data = in_file.readAll();


    QJsonParseError error;
    QJsonDocument json_cues_doc = QJsonDocument::fromJson(in_data, &error);

    qDebug() << error.errorString();
    qDebug() << in_data.at(error.offset);
    qDebug() << json_cues_doc.isNull();

    QJsonArray json_cues_vector = json_cues_doc.array();

    cue_vector.clear();
    ui->cue_list->clear();
    set_cue_list();

    for (int i = 0; i < json_cues_vector.size(); ++i) {
        QJsonObject current_json_obj = json_cues_vector.at(i).toObject();
        qDebug() << "adding " << current_json_obj["note"].toString();
        newCue(current_json_obj["type"].toInt(), current_json_obj["note"].toString());
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
        cues.append(json_cue_obj);
    }

    QJsonDocument json_cues_doc;
    json_cues_doc.setArray(cues);

    QDataStream out (&out_file);
//    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    qDebug() << json_cues_doc.toJson();

    // outputing char by char removes extranious chars present when
//    out << out_text;
    // is used
    QString out_text = json_cues_doc.toJson();
 //   for (int i = 0; i < out_text.size(); ++i) {
//        out << out_text.at(i);

    out << out_text;
//    }
    out_file.close();
}

void MainWindow::on_cue_note_returnPressed(){
}


void MainWindow::on_action_select_currentIndexChanged()
{
    curr_cue_action_index = ui->action_select->currentIndex();
}
