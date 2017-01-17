//
// Created by mohsen on 1/17/17.
//

#include <Core/Core.h>
#include "AudioTreeWidgetItem.h"

#include "MediaInfo.h"

using namespace MediaInfoLib;
namespace {
    static MediaInfo MI;
}

QString operator=(String aString) {
    return QString::fromStdWString(aString);
}

String operator=(QString aString) {
    return aString.toStdWString();
}

namespace UI {
    AudioTreeWidgetItem::AudioTreeWidgetItem(const QString &fileName) : QTreeWidgetItem() {
        this->filename = fileName;
        MI.Open(this->filename.toStdWString());

        bool dummy;
        setText(0, QString::fromStdWString(
                MI.Get(MediaInfoLib::Stream_General, 0, __T("Title"), MediaInfoLib::Info_Text,
                       MediaInfoLib::Info_Name)));
        setText(1, Core::formatSecondsToTime(
                QString::fromStdWString(
                        MI.Get(MediaInfoLib::Stream_General, 0, __T("Duration"),
                               MediaInfoLib::Info_Text,
                               MediaInfoLib::Info_Name)).toInt(&dummy) / 1000).c_str());

        setText(2, QString::fromStdWString(MI.Get(MediaInfoLib::Stream_General, 0, __T("Album"),
                                                  MediaInfoLib::Info_Text,
                                                  MediaInfoLib::Info_Name)));

        MI.Close();
    }
}