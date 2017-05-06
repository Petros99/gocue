#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include "cue.h"
#include <QObject>
#include <vector>

std::vector<Cue> cue_vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    {  // setup cue_list
    ui->cue_list->setColumnCount(3);
    ui->cue_list->setHeaderLabels(QStringList()
                                  << "number"
                                  << "action"
                                  << "note");
    }

    QStringList actions;
    for (auto const & it:cue_actions) {
        actions << it.first.c_str();
    }
    ui->action_select->addItems(actions);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCue(int index, std::string action = "placeHolder", QString note = "")
{
    QTreeWidgetItem * itm = new QTreeWidgetItem(ui->cue_list);
    itm->setText(0, QString::number(index));
    itm->setText(1, tr(action.c_str()));
    itm->setText(2, note);
    ui->cue_list->addTopLevelItem(itm);
    Cue new_cue;
    new_cue.action = action;
    new_cue.index = index;
    new_cue.note = note;
    cue_vector.push_back(new_cue);
}

void MainWindow::on_actionopen_triggered()
{
     QString cueListFileName = QFileDialog::getOpenFileName(this, tr("Open Cue List"), "", tr("CSV files (*.csv)"));
     qDebug(cueListFileName.toLatin1());
}

void MainWindow::on_go_button_clicked()
{
    qDebug("GO pushed");
    Cue test_cue;
    test_cue.go();
}

void MainWindow::on_add_clicked()
{
    MainWindow::addCue(0, curr_cue_action, ui->cue_note->text());
}

void MainWindow::on_remove_clicked()
{
    int selected_row = ui->cue_list->currentIndex().row();
    if (selected_row == -1) selected_row = 0;  // if no row is selected, use first row
    ui->cue_list->takeTopLevelItem(selected_row);
}

void MainWindow::on_action_select_currentIndexChanged(const QString &arg1)
{
    curr_cue_action = ui->action_select->currentText().toStdString();
}

void MainWindow::on_actionsave_triggered()
{
    //TODO
     QString f_name = QFileDialog::getSaveFileName(this,
                                                   QObject::tr("Select Save File"));
                                                   //QDir::homePath);
//                                                   QObject::tr("CSV Files (*.csv)"));
     QFile file(f_name);

    if (!file.open(QIODevice::WriteOnly)) {
        error_message(f_name);
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_8);


   file.flush();
   file.close();
}
