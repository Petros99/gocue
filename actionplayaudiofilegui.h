#ifndef ACTIONPLAYAUDIOFILEGUI_H
#define ACTIONPLAYAUDIOFILEGUI_H

#include <QTimer>
#include <QWidget>
#include <QMediaPlayer>

//#include "cue.h"
// because forward declarations...
class ActionPlayAudioFile;

namespace Ui {
class ActionPlayAudioFileGui;
}

class ActionPlayAudioFileGui : public QWidget
{
    Q_OBJECT

public:
    explicit ActionPlayAudioFileGui(QWidget *parent = 0);
    ~ActionPlayAudioFileGui();

    void start(ActionPlayAudioFile * cue);

    void stop();

private slots:
    void on_mute_button_clicked();

    void setMediaInfo(QMediaPlayer::MediaStatus status);

    void on_file_path_line_editingFinished();

    void on_pick_file_button_clicked();

    void on_play_button_clicked();

    void on_pause_button_clicked();

    void set_position(qint64 poss);

    void loadMedia(qint64 dur);

    void set_time_passed(qint64 poss);

    void on_scrub_slider_sliderMoved(int position);

    void on_begin_spin_editingFinished();

    void on_end_spin_editingFinished();

    void setDisabledMediaInteraction(bool disabled);

    void on_unmute_button_clicked();

    void update_volume(int vol);

    void setPlayButtons(qreal rate);

private:
    ActionPlayAudioFile * target_cue;
    Ui::ActionPlayAudioFileGui *ui;
};

#endif // ACTIONPLAYAUDIOFILEGUI_H
