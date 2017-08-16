// this file contains code related to the gui of actionPlayaudioFile
void MainWindow::on_volumeControl_slide_valueChanged(int value)
{
   ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->player->setVolume(value);
   ui->volumeControl_spin->setValue(value);
}

void MainWindow::on_volumeControl_spin_valueChanged(int value)
{
   ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->player->setVolume(value);
   ui->volumeControl_slide->setValue(value);
}

void MainWindow::on_selectAudioFileButton_clicked()
{
    ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->askAudioFileName();
    // set the line edit for audio file path to the recently selected value
    ui->selectAudioFileLineEdit->setText(((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->audio_file_name);
}

void MainWindow::on_selectAudioFileLineEdit_editingFinished()
{
    ((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->audio_file_name = ui->selectAudioFileLineEdit->text();
}

/*
void MainWindow::updateMediaLcd(qint64 pos) {
            if (pos > INT_MAX || pos < INT_MIN) {
                // should only happen if the media is longer than
                // 2,147,483,647 ms, or about 596.5 hours
                // that would be almost a month duration media file!
                ui->playbackPassedLcd->display("ERR");
                ui->playbackRemainLcd->display("ERR");
                qWarning("media too long");
                return;
            }

            int ms = (int)pos;  // cast!
            ui->playbackPassedLcd->display(ms);
            ui->playbackRemainLcd->display(
                        (int)((ActionPlayAudioFile *)cue_vector.at(ui->cue_list->currentItem()->row()))->player->duration() - ms);  // cast!

        }
*/
