#ifndef CUE_H
#define CUE_H
#include <map>  //  cue_action
#include <functional>  // function maping
#include <QString>  // for popup function
#include <QObject>  // for popup function
#include <QMessageBox>  // for popup function

int popup(const std::map<std::string, std::string> & action_properties) {
    QString text;
    auto search = action_properties.find("text");  // search is an iteratior that could be in the property
    if (search != action_properties.end()) {
        text = QObject::tr(search->second.c_str());
    }
    else {
        text = QObject::tr("default text");
    }

    QMessageBox popup;
    popup.setText(text);
    return popup.exec();
}


// maps action strings to functions
std::map<std::string, std::function<int(std::map<std::string, std::string> &)>> cue_actions =
{
    {"placeHolder", popup},
    {"placeHolder1", popup},
    {"placeHolder2", popup},
    {"placeHolder3", popup},
    {"placeHolder4", popup},
    {"placeHolder5", popup}
};

std::string curr_cue_action = "placeHolder";

struct Cue {
    //for all cues
    QString index = 0;
    QString note = "";
    std::string action = "placeHolder";  // maps to a function that does something
    // change to Qmap?
    std::map<std::string, std::string> action_properties;  // holds the properties for action

    int go() {
        return cue_actions[action](action_properties);
    }

};


#endif // CUE_H
