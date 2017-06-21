#ifndef CUE_H
#define CUE_H
#include <QString>  // for popup function
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QMediaPlayer>  // used in ActionPlayAudioFile
#include <QFileDialog>  // used in ActionPlayAudioFile's constructor
#include <QJsonObject>  // read and write functions

class Cue {
    // the base class for all cues
public:  // no reason for any to be private or protected
    Cue() {}
    QString note = "";
    virtual int go() {  // this base class version should never be called
        QMessageBox box;
        box.setWindowTitle("default cue action");
        box.setText("this cue has the defalt action, that is bad");
        return box.exec();  // will stop program until popup is dismissed
    }

    virtual void read(const QJsonObject &json) {  // for loading cues from file
        note = json["note"].toString();
    }

    virtual void write(QJsonObject &json) const {  // for writing cues to file
        json["note"] = note;
        json["type"] = -1;
        // -1 value will cause something bad to happen when saved, this is desired
        // the base class cue should not be saved
    }
};

class ActionPopup : public Cue {
public:
    ActionPopup() {}
    QString text = "the good text";
    QString title = "Message";

    int go() override final {
        QMessageBox box;
        box.setWindowTitle(title);
        box.setText(text);
        return box.exec();  // will stop execution until dismissed
    }

    void read(const QJsonObject &json) {
        Cue::read(json);  // call the base class's read function
        text = json["text"].toString();
        title = json["title"].toString();
    }

    void write(QJsonObject &json) const {
        Cue::write(json);
        json["text"] = text;
        json["title"] = title;
        json["type"] = 0;
    }
};

// ActionPlayAudioFile is not blocking, the next cue can begin while the file is playing
class ActionPlayAudioFile : public Cue {
    // plays audio file from disk
public:
    ActionPlayAudioFile() {
        // https://forum.qt.io/topic/57675/which-file-formats-or-codecs-does-qmediaplayer-support/3
        // the listed extentions might or might not work
        // QFileDialog::getOpenFileName opens a window for the user to select a file
    audio_file_name = QFileDialog::getOpenFileName(nullptr,
                       QObject::tr("Select Audio File"),
                       QString(),
                       QObject::tr("Audio files (*.mp3 *.aiff *.au. *avi *midi *.snd *wav)"));
    }
    QString audio_file_name = "sound.wav";

    int volume = 50;  // no code yet exists to change this value

    int go() override final {
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(audio_file_name));
        //player->Flag = QMediaPlayer::LowLatency;
        player->setVolume(volume);
        player->play();  // not blocking
        return 1;
    }

    void read(const QJsonObject &json) {
        Cue::read(json);
        audio_file_name = json["audio_file_name"].toString();
        volume = json["volume"].toInt();
    }

    void write(QJsonObject &json) const {
        Cue::write(json);
        json["audio_file_name"] = audio_file_name;
        json["volume"] = volume;
        json["type"] = 1;
    }

};

#endif // CUE_H
