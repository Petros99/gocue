#ifndef CUE_C
#define CUE_C
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QFileDialog>  // used in ActionPlayAudioFile's constructor
#include "cue.h"

void Cue::read(const QJsonObject &json) {
    note = json["note"].toString();
}

void Cue::write(QJsonObject &json) const {
    json["note"] = note;
    json["type"] = cue_type;
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

void ActionPopup::hide_ui(Ui::MainWindow *ui) {
    ui->actionPopupSettings->hide();
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
}


// ActionPlayAudioFile is not blocking, the next cue can begin while the file is playing
ActionPlayAudioFile::ActionPlayAudioFile() {
    player->setVolume(50); // default volume
}

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
    // if we are before the begin_time, go to the begin time
    if (player->position() < begin_time) player->setPosition((qint64)begin_time);
    player->play();  // not blocking
    return 1;
}
int ActionPlayAudioFile::show_ui(Ui::MainWindow * ui) {
    ui->action_play_audio_file_gui->show();  // shows the ui
    ui->action_play_audio_file_gui->start(this); // give ponter to self to the ui
    return 1;
}

void ActionPlayAudioFile::hide_ui(Ui::MainWindow *ui) {
    ui->action_play_audio_file_gui->hide();
    ui->action_play_audio_file_gui->stop();
}

void ActionPlayAudioFile::read(const QJsonObject &json) {
    Cue::read(json);
    muted = json["muted"].toBool();
    audio_file_name = json["audio_file_name"].toString();
    player->setVolume(json["volume"].toInt());
    begin_time = json["begin_time"].toInt();
    stop_time = json["stop_time"].toInt();
}

void ActionPlayAudioFile::write(QJsonObject &json) const {
    Cue::write(json);
    json["muted"] = muted;
    json["audio_file_name"] = audio_file_name;
    json["volume"] = player->volume();
    json["begin_time"] = begin_time;
    json["stop_time"] = stop_time;
}
// end ActionPlayAudioFile child class functions

#endif // CUE_C
