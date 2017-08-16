void MainWindow::on_actionopen_triggered() {
    QString f_name = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                    "",
                                                    tr("JSON (*.json)"));
    QFile in_file(f_name);

    if (!in_file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file.");
    }

    QByteArray in_data = in_file.readAll();  // file to byte array

    QJsonParseError error;  // holds errors
    QJsonDocument json_cues_doc = QJsonDocument::fromJson(in_data, &error);

    QJsonArray json_cues_vector = json_cues_doc.array();
     // byte array to json array

    // reset stuffs
    cue_vector.clear();
    ui->cue_list->clear();
    set_cue_list();

    for (int i = 0; i < json_cues_vector.size(); ++i) {
        QJsonObject current_json_obj = json_cues_vector.at(i).toObject();
        // vector item to json object
        newCue(current_json_obj["type"].toInt(), current_json_obj["note"].toString());
        // json object to a cue, which is added to cue_vector
    }

}

void MainWindow::on_actionsave_triggered()
{
    QString f_name = QFileDialog::getSaveFileName(nullptr, tr("Save File"),
                                "",
                                tr("JSON (*.json)"));
    QFile out_file(f_name);
    if (!out_file.open(QIODevice::WriteOnly)) {
        qWarning("Could not save file!");
        return;
    }


    QJsonArray cues;
    for(int i = 0; i < cue_vector.size(); ++i) {
        QJsonObject json_cue_obj;
        cue_vector.at(i)->write(json_cue_obj);
        // cue_vector to json cue vector
        cues.append(json_cue_obj);
    }

    QJsonDocument json_cues_doc;
    json_cues_doc.setArray(cues);

    // json cue vector to json doc

    QTextStream out (&out_file);
//    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    QString out_text = json_cues_doc.toJson();
    // json doc to text
    out << out_text;
    // text to file
    out_file.close();
}
