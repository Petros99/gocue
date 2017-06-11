#ifndef CUE_H
#define CUE_H
#include <QString>  // for popup function
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QMediaPlayer>  // used in ActionPlayAudioFile
#include <QFileDialog>  // used in ActionPlayAudioFile's constructor
#include <QJsonObject>

class Cue {
public:
    Cue() {}
    QString note = "";
    virtual int go() {
        QMessageBox box;
        box.setWindowTitle("default cue action");
        box.setText("this cue has the defalt action, that is bad");
        return box.exec();
    }

    virtual void read(const QJsonObject &json) {  // not virtual, but meant to be hidden
        // should read have an access specifier?
        note = json["note"].toString();
    }

    virtual void write(QJsonObject &json) const {
        // TODO also need to write action
        json["note"] = note;
        json["type"] = -1;
        // will cause something bad to happen when saved, this is desired
    }
};

// ActionPopup is blocking, the ok must be pressed before the next cue is selected
class ActionPopup : public Cue {
public:
    ActionPopup() {}
    QString text = "the good text";
    QString title = "Message";

    int go() override final {
        QMessageBox box;
        box.setWindowTitle(title);
        box.setText(text);
        return box.exec();
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
public:
    ActionPlayAudioFile() {
        // https://forum.qt.io/topic/57675/which-file-formats-or-codecs-does-qmediaplayer-support/3
        // the listed extentions might or might not work
    audio_file_name = QFileDialog::getOpenFileName(nullptr,
                       QObject::tr("Select Audio File"),
                       QString(),
                       QObject::tr("Audio files (*.mp3 *.aiff *.au. *avi *midi *.snd *wav)"));
    }
    QString audio_file_name = "sound.wav";
    int volume = 50;

    int go() override final {
        QMediaPlayer * player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(audio_file_name));
        //player->Flag(QMediaPlayer::LowLatency);
        player->setVolume(volume);
        player->play();
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
