#ifndef CUE_H
#define CUE_H
#include <QString>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QMediaPlayer>  // used in ActionPlayAudioFile
#include <QJsonObject>  // read and write functions
#include "ui_mainwindow.h"  // used for show ui functions

class Cue {
    // the base class for all cues
public:  // no reason for any to be private or protected
    QString note = "note";

    virtual int go();  // this base class version should never be called

    virtual int show_ui(Ui::MainWindow * ui);

    static const int cue_type;

    virtual void read(const QJsonObject &json);  // for loading cues from file

    virtual void write(QJsonObject &json) const; // for writing cues to file
};

class ActionPopup : public Cue {
public:
    //ActionPopup();
    static const int cue_type = 0;
    QString text = "default text";
    QString title = "default title";

    int go() override final;

    int show_ui(Ui::MainWindow * ui) override final;

    void read(const QJsonObject &json);

    void write(QJsonObject &json) const;
};

class ActionPlayAudioFile : public Cue {
    // plays audio file from disk
public:
    ActionPlayAudioFile();
    static const int cue_type = 1;
    // player is now a memeber
    QMediaPlayer * player = new QMediaPlayer;
    QString audio_file_name = "sound.wav";

    QString askAudioFileName();

    int go() override final;

    int show_ui(Ui::MainWindow * ui) override final;

    void read(const QJsonObject &json);

    void write(QJsonObject &json) const;

};

#endif // CUE_H
