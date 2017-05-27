#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include "cue.h"
#include <QObject>
#include <vector>
#include <QString>
#include <QDebug>

int error_message(QString text){
    // opens an error message
    QMessageBox msgBox;
    msgBox.setText("There was an error.");
    msgBox.setInformativeText(text);
    msgBox.setIcon(QMessageBox::Warning);
    return msgBox.exec();
}

std::vector<Cue> cue_vector;
int curr_cue_action_index = 0; // popup
QStringList possible_actions = {"popup"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // action_select dropdown
    ui->action_select->addItems(possible_actions);

    // the qTableWidget cue_list
    ui->cue_list->setColumnCount(2);
    QStringList headers;
    headers << "note" << "action";
    ui->cue_list->setHorizontalHeaderLabels(headers);
    ui->cue_list->setShowGrid(false);
    ui->cue_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cue_list->setSelectionMode(QAbstractItemView::SingleSelection);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertCue(Cue const & cue) {
    int index = ui->cue_list->currentRow();
    // if none selected, insert at end
    if (index == -1) index = cue_vector.size();
    for (int i = cue_vector.size() - 1; i > index; --i) {
        ui->cue_list->setItem(i, 0, ui->cue_list->item(i - 1, 0));
        ui->cue_list->setItem(i, 1, ui->cue_list->item(i - 1, 1));
    }

    ui->cue_list->setRowCount(ui->cue_list->rowCount() + 1);
    QTableWidgetItem * note_itm = new QTableWidgetItem();
    note_itm->setText(cue.note);

    QTableWidgetItem * action_itm = new QTableWidgetItem();
    action_itm->setText(possible_actions.at(curr_cue_action_index));
    ui->cue_list->setItem(index, 0, note_itm);
    ui->cue_list->setItem(index, 1, action_itm);

    cue_vector.insert(cue_vector.begin() + index, cue);
    qDebug() << "the cue_vector contains " << cue_vector.size();
}


void MainWindow::on_actionopen_triggered()
{
    /*
     QString cueListFileName = QFileDialog::getOpenFileName(this, tr("Open Cue List"), "", tr("CSV files (*.csv)"));
     qDebug(cueListFileName.toLatin1());
     */
}

void MainWindow::on_go_button_clicked()
{
    //
}

void MainWindow::on_add_clicked()
{
    // the cue types are listed in possible_actions
    switch (ui->action_select->currentIndex()) {
    case 0:  // the first is popup
    {
        ActionPopup cue;
        cue.note = ui->cue_note->text();
        insertCue(cue);
        break;
    }
    default:  // should never happen
    {
        Cue cue;
        cue.note = ui->cue_note->text();
        insertCue(cue);
        break;
    }
    }
}

void MainWindow::on_remove_clicked()
{
    /*
    int selected_row = ui->cue_list->currentIndex().row();
    if (selected_row == -1) selected_row = 0;  // if no row is selected, use first row
    ui->cue_list->takeTopLevelItem(selected_row);
    */
}

void MainWindow::on_action_select_currentIndexChanged(const QString &arg1)
{
    curr_cue_action_index = ui->action_select->currentIndex();
}

void MainWindow::on_actionsave_triggered()
{
}

void MainWindow::on_cue_note_returnPressed(){
    //
}

