#include "actionplayaudiofilegui.h"
#include "ui_actionplayaudiofilegui.h"

#include "cue.h"
#include <QFileDialog>  // for file picker
#include <QAudio>  // for audio conversions

ActionPlayAudioFileGui::ActionPlayAudioFileGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionPlayAudioFileGui)
{
    qDebug() << "APAFG constructor";
    ui->setupUi(this);
    setDisabledMediaInteraction(true);

}

ActionPlayAudioFileGui::~ActionPlayAudioFileGui()
{
    qDebug() << "APAFG destructor";
    delete ui;
}

void ActionPlayAudioFileGui::start(ActionPlayAudioFile * cue) {
    qDebug() << "start";
    // this function is called when the target_cue is known

    target_cue = cue; // we now know of target_cue

    // volume stuff
    // intial volume settings
    ui->volume_slider->setValue(target_cue->player->volume());
    ui->volume_spin->setValue(target_cue->player->volume());

    // volume connections
    connect(target_cue->player, SIGNAL(volumeChanged(int)), this, SLOT(updateVolume(int)));
    connect(ui->volume_slider, SIGNAL(valueChanged(int)), this, SLOT(update_volume(int)));
    connect(ui->volume_spin, SIGNAL(valueChanged(int)), this, SLOT(update_volume(int)));

    // intial mute settings
    ui->mute_button->setDisabled(target_cue->muted);
    ui->unmute_button->setEnabled(target_cue->muted);


    // disable mute button if muted
    connect(target_cue->player, SIGNAL(mutedChanged(bool)), ui->mute_button, SLOT(setEnabled(bool)));
    // disable unmute button if not muted
    connect(target_cue->player, SIGNAL(mutedChanged(bool)), ui->unmute_button, SLOT(setDisabled(bool)));

    ui->pause_button->setDisabled(true);
    // when playing, play button should be disabled, and pause button enabled

    connect(target_cue->player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(setPlayButtons(QMediaPlayer::State)));

    // update the gui (scrub_slider, lcds, etc) every 25 ms, or 40 times a sec.
    target_cue->player->setNotifyInterval(25);

    target_cue->player->setPosition(ui->scrub_slider->value()); // probably bad
    connect(  // when the player's position changes, update the scrub_slider
                target_cue->player, SIGNAL(positionChanged(qint64)),
                  this, SLOT(set_position(qint64)));

    loadMedia(target_cue->player->duration());  // must be called at least once
    connect(  // when the media's durration changes (on (re)load),
              // set up gui for the media
                target_cue->player, SIGNAL(durationChanged(qint64)),
                this, SLOT(loadMedia(qint64)));
}

void ActionPlayAudioFileGui::update_volume(int vol) {
    qDebug() << "update volume";
   ui->volume_slider->setValue(vol);  // TODO, needs to be tested
   ui->volume_spin->setValue(vol);

   // convert audio scales
   // qthelp://org.qt-project.qtmultimedia.590/qtmultimedia/qaudio.html
   qreal linearVolume = QAudio::convertVolume(vol / qreal(100.0),
                                              QAudio::LogarithmicVolumeScale,
                                              QAudio::LinearVolumeScale);
   target_cue->player->setVolume(qRound(linearVolume * 100));
}

void ActionPlayAudioFileGui::setPlayButtons(QMediaPlayer::State state) {
    qDebug() << "set play buttons";
    // if playing, enable the pause button and disable the play button
    if (state == QMediaPlayer::PlayingState) {
        ui->pause_button->setEnabled(true);
        ui->play_button->setDisabled(true);
    }
    else {
        ui->pause_button->setDisabled(true);
        ui->play_button->setEnabled(true);
    }
}

void ActionPlayAudioFileGui::setDisabledMediaInteraction(bool disabled) {
    qDebug() << "set disabled media interaction";
    // disables/enables the media interatction widgests
    ui->play_button->setDisabled(disabled);
    ui->pause_button->setDisabled(disabled);
    ui->end_spin->setDisabled(disabled);
    ui->begin_spin->setDisabled(disabled);
    ui->passed_lcd->setDisabled(disabled);
    ui->passed_lcd->display("");
    ui->remain_lcd->setDisabled(disabled);
    ui->remain_lcd->display("");
    ui->length_lcd->setDisabled(disabled);
    ui->length_lcd->display("");
    ui->scrub_slider->setDisabled(disabled);
}

void ActionPlayAudioFileGui::stop() {
    qDebug() << "stop";
    // called when unselected

    // disconnect everything connected to all signals in player
    disconnect(target_cue->player, 0, 0, 0);

    setDisabledMediaInteraction(true);

    // clear the interface
    ui->file_path_line->clear();
    ui->end_spin->setValue(0);
    ui->begin_spin->setValue(0);
    ui->scrub_slider->setValue(0);
    ui->length_lcd->display(0);
    ui->remain_lcd->display(0);
    ui->passed_lcd->display(0);
}

void ActionPlayAudioFileGui::loadMedia(qint64 dur) {
    qDebug() << "load media";
    (void)(dur);  // dur is unused,
                 // but required for connecting this func. to durrationChanged
    this->setMediaInfo(target_cue->player->mediaStatus());
}

void ActionPlayAudioFileGui::on_mute_button_clicked() {
    qDebug() << "on mute button clicked";
    target_cue->player->setMuted(true);
    target_cue->muted = false;
}

void ActionPlayAudioFileGui::on_file_path_line_editingFinished() {
    qDebug() << "on file path line editing finished";
   target_cue->player->setMedia(QUrl::fromLocalFile(ui->file_path_line->text()));
}

void ActionPlayAudioFileGui::on_pick_file_button_clicked() {
    qDebug() << "on pick file button clicked";
   QString new_file = QFileDialog::getOpenFileName(this, tr("Selct Your File"),"", tr("Audio (*.mp3 *.wav *.ogg *.wma *.aiff *.m4a *.wmv)"));
   // TODO: the avalable file types should be dependent on OS, or gstreamer should be integrated
   target_cue->player->setMedia(QUrl::fromLocalFile(new_file));
   connect(target_cue->player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), \
           this, SLOT(setMediaInfo(QMediaPlayer::MediaStatus)));
   ui->file_path_line->setText(new_file);
}

void ActionPlayAudioFileGui::on_play_button_clicked()
{
   target_cue->player->play();
}

void ActionPlayAudioFileGui::on_pause_button_clicked()
{
    target_cue->player->pause();
}

void ActionPlayAudioFileGui::set_position(qint64 poss) {
    if (!(poss >= 0 && poss < INT32_MAX)) return;  // TODO there should be error handeling here;

    // target_cue->player->duration() *will* be cast-able to an int,
    // this is checked by setMediaInfo before connection
    double remain_time = (double)target_cue->player->duration()/1000 - (double)poss/1000;

    // changes the position of the scrub_slider if it is not being scrubed by the user
    if (!(ui->scrub_slider->isSliderDown())) {
        ui->scrub_slider->setValue(poss);
    }

    // sets the remain_lcd's display (in seconds)
    ui->remain_lcd->display(QString::number(remain_time));
}

void ActionPlayAudioFileGui::set_time_passed(qint64 poss) {
    // sets gui elements that do not require knowlaede of the media durration

    double dposs = (double)poss / 1000;
    ui->passed_lcd->display(QString::number(dposs));
}

void ActionPlayAudioFileGui::setMediaInfo(QMediaPlayer::MediaStatus status){
    qDebug() << "set media info";
    // tell user the media status
    if (status == QMediaPlayer::InvalidMedia) {
        ui->status_label->setText("Invalid Media");
    }
    else if (status == QMediaPlayer::LoadingMedia) {
        ui->status_label->setText("Loading Media");
    }
    else if (status == QMediaPlayer::NoMedia) {
        ui->status_label->setText("No Media");
    }
    else if (status == QMediaPlayer::UnknownMediaStatus) {
        ui->status_label->setText("Unknown Media Status");
    }
    else if (target_cue->player->duration() < 1) {
        ui->status_label->setText("Negative Duration");
    }
    else if (target_cue->player->duration() > INT32_MAX) {
        ui->status_label->setText("Duration Overflow");
    }
    else if (status == QMediaPlayer::BufferedMedia) {
        ui->status_label->setText("Media Buffered");
    }
    else if (status == QMediaPlayer::BufferingMedia) {
        ui->status_label->setText("Media Buffering");
    }
    else if (status == QMediaPlayer::AccessDeniedError) {
        ui->status_label->setText("Access Denied");
    }
    else if (status == QMediaPlayer::EndOfMedia) {
        ui->status_label->setText("Done Playing");
    }
    else {
        ui->status_label->setText(target_cue->player->errorString());
    }
    // TODO, finish this list




    if (  // only allow play and pause if media is valid
            status == QMediaPlayer::InvalidMedia ||
            status == QMediaPlayer::LoadingMedia ||
            status == QMediaPlayer::NoMedia ||
            status == QMediaPlayer::UnknownMediaStatus ||

           // negative duration is not good, -1 prob means value unknown, see:
           // https://github.com/qtproject/qt-mobility/blob/master/src/multimedia/qmediaplayer.cpp line 437
          target_cue->player->duration() < 1 ||

           // treat a very long file (ms > INT32_MAX) the same as one whose durration is unknown
          target_cue->player->duration() > INT32_MAX
          )
    {
        setDisabledMediaInteraction(true);  // do not allow the user use media file
        ui->status_label->setText(QString().number(status));
        // TODO, tell the user what is broken
    }

   else { // valid media

    setDisabledMediaInteraction(false);

    connect(target_cue->player, SIGNAL(positionChanged(qint64)), this, SLOT(set_time_passed(qint64)));
   ui->file_path_line->setText(target_cue->player->currentMedia().canonicalUrl().toDisplayString(QUrl::PreferLocalFile));

    ui->end_spin->setMaximum((double)target_cue->player->duration()/1000);  // set the max to duration of media

    // if the target cue does not specify a stop time, set the stop time to the end of the media
    if (target_cue->stop_time == -1) ui->end_spin->setValue((double)target_cue->player->duration()/1000);
    else ui->end_spin->setValue((double)target_cue->stop_time);

    ui->begin_spin->setEnabled(true);
    ui->begin_spin->setMaximum((double)target_cue->player->duration()/1000);


    // if the target cue does not specify a start time, set the stop time to the end of the media
    if (target_cue->begin_time == -1) ui->begin_spin->setValue(0);
    else ui->begin_spin->setValue((double)target_cue->begin_time/1000);


    ui->length_lcd->setEnabled(true);
    ui->length_lcd->display((double)target_cue->player->duration()/1000);
    ui->length_lcd->show();

    ui->scrub_slider->setEnabled(true);
    ui->scrub_slider->setMaximum((int)target_cue->player->duration());
    ui->scrub_slider->show();

   // can only connect to slider and remain lcd if the durration is known
   connect(target_cue->player, SIGNAL(positionChanged(qint64)), this, SLOT(set_position(qint64)));
   }

}

void ActionPlayAudioFileGui::on_scrub_slider_sliderMoved(int position)
{
    // qint64 is bigger than int, there should be no issues with the cast
    target_cue->player->setPosition((qint64)position);
}

void ActionPlayAudioFileGui::on_begin_spin_editingFinished()
{
    target_cue->begin_time = (int)ui->begin_spin->value()*1000;
}

void ActionPlayAudioFileGui::on_end_spin_editingFinished()
{
   target_cue->stop_time = (int)ui->end_spin->value()*1000;
}

void ActionPlayAudioFileGui::on_unmute_button_clicked()
{
   target_cue->player->setMuted(false);
   target_cue->muted = false;
}
