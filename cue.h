#ifndef CUE_H
#define CUE_H
#include <map>  //  cue_action
#include <functional>  // function maping
#include <QString>  // for popup function
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function

class Cue {
public:
    Cue() = default;
    QString note = "";
    virtual int go() {
        QMessageBox box;
        box.setWindowTitle("default cue action");
        box.setText("this cue has the defalt action, that is bad");
        return box.exec();
    }
};

class ActionPopup : public Cue {
public:
    QString text = "";
    QString title = "Message";
    int go() override final {
        QMessageBox box;
        box.setWindowTitle(title);
        box.setText(text);
        return box.exec();
    }
};

#endif // CUE_H
