#ifndef CUE_C
#define CUE_C
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QFileDialog>  // used in ActionPlayAudioFile's constructor
#include "cue.h"

int Cue::go() {  // this base class version should never be called
    QMessageBox box;
    box.setWindowTitle("default cue action");
    box.setText("this cue has the defalt action, that is bad");
    return box.exec();  // will stop program until popup is dismissed
}

int Cue::show_ui(Ui::MainWindow * ui) {
    qDebug() << "THIS FUNCTION SHOULD NOT HAVE BEEN CALLED!!!";
    return 1;
}

//static const int Cue::cue_type = -1;

void Cue::read(const QJsonObject &json) {  // for loading cues from file
    note = json["note"].toString();
}

void Cue::write(QJsonObject &json) const {  // for writing cues to file
    json["note"] = note;
    json["type"] = -1;
    // -1 value will cause something bad to happen when saved, this is desired
    // the base class cue should not be saved
}


int ActionPopup::go() {
    QMessageBox box;
    box.setWindowTitle(title);
    box.setText(text);
    return box.exec();  // will stop execution until dismissed
}

int ActionPopup::show_ui(Ui::MainWindow * ui) {
    ui->actionPopupTextEntry->setText(text);
    ui->actionPopupTitleEntry->setText(title);
    ui->actionPopupSettings->show();
    return 1;
}

void ActionPopup::read(const QJsonObject &json) {
    Cue::read(json);  // call the base class's read function
    text = json["text"].toString();
    title = json["title"].toString();
}

void ActionPopup::write(QJsonObject &json) const {
    Cue::write(json);
    json["text"] = text;
    json["title"] = title;
    json["type"] = cue_type;
}
// end ActionPopup child class funtions

// begin ActionPlayAudioFile child class functions
// ActionPlayAudioFile is not blocking, the next cue can begin while the file is playing
ActionPlayAudioFile::ActionPlayAudioFile() {
    player->setVolume(50); // default volume
}
//static const ActionPlayAudioFile::cue_type;
// player is a memeber
//ActionPlayAudioFile::player = new QMediaPlayer;
//QString ActionPlayAudioFile::audio_file_name = "sound.wav";
//something evil
QString ActionPlayAudioFile::askAudioFileName() {
    audio_file_name = QFileDialog::getOpenFileName(nullptr,  // parent
                QObject::tr("Select Audio File"),  // caption
                QString(),  // directory
                QObject::tr("Audio files (*.mp3 *.aiff *.au. *avi *midi *.snd *wav)"));  // filter
            return audio_file_name;

}

int ActionPlayAudioFile::go() {
    player->setMedia(QUrl::fromLocalFile(audio_file_name));
    //player->Flag = QMediaPlayer::LowLatency;
    player->play();  // not blocking
    return 1;
}
int ActionPlayAudioFile::show_ui(Ui::MainWindow * ui) {
    ui->volumeControl_slide->setValue(player->volume());
    ui->volumeControl_spin->setValue(player->volume());
    ui->selectAudioFileLineEdit->setText(audio_file_name);
    //ui->updateMediaLcd(10);
    //QObject::connect(player, &QMediaPlayer::positionChanged, ui->updateMediaLcd);
    ui->actionPlayAudioFileSettings->show();
    return 1;
}

void ActionPlayAudioFile::read(const QJsonObject &json) {
    Cue::read(json);
    audio_file_name = json["audio_file_name"].toString();
    player->setVolume(json["volume"].toInt());
}

void ActionPlayAudioFile::write(QJsonObject &json) const {
    Cue::write(json);
    json["audio_file_name"] = audio_file_name;
    json["volume"] = player->volume();
    json["type"] = cue_type;
}
// end ActionPlayAudioFile child class functions

#endif // CUE_C
