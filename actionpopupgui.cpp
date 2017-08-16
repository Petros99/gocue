void MainWindow::on_actionPopupTitleEntry_editingFinished()
{
   ((ActionPopup *)cue_vector.at(ui->cue_list->currentItem()->row()))->title = ui->actionPopupTitleEntry->text();
}

void MainWindow::on_actionPopupTextEntry_textChanged()
{
    ((ActionPopup *)cue_vector.at(ui->cue_list->currentItem()->row()))->text = ui->actionPopupTextEntry->toPlainText();
}
