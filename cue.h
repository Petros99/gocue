#ifndef CUE_H
#define CUE_H
#include <QString>  // for popup function
#include <QDebug>  // uhhhh, for debuging
#include <QMediaPlayer>  // used in ActionPlayAudioFile
#include <QJsonObject>  // read and write functions
#include "ui_mainwindow.h"  // used for show ui functions

class Cue {  // abstract
public:
    QString note;

    virtual int go() = 0;

    virtual int show_ui(Ui::MainWindow * ui) = 0;

    virtual void hide_ui(Ui::MainWindow * ui) = 0;

    static const int cue_type = -1;

    virtual void read(const QJsonObject &json) = 0;  // for loading cues from file

    virtual void write(QJsonObject &json) const = 0; // for writing cues to file
};

class ActionPopup : public Cue {
public:
    //ActionPopup();
    static const int cue_type = 0;
    QString text = "default text";
    QString title = "default title";

    int go() override final;  // TODO, required?

    int show_ui(Ui::MainWindow * ui) override final;

    void hide_ui(Ui::MainWindow * ui) override final;

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

    void hide_ui(Ui::MainWindow * ui) override final;

    void read(const QJsonObject &json);

    void write(QJsonObject &json) const;

    bool muted = true;  // TODO, save


    // -1 means that time is unspecified
    // begin_time is in ms
    int begin_time = -1;

    // stop_time is in ms
    int stop_time = -1;

};

#endif // CUE_H
