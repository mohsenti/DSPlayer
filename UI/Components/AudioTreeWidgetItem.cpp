//
// Created by mohsen on 1/17/17.
//

#include <Core/Core.h>
#include "AudioTreeWidgetItem.h"

#include "MediaInfo.h"

using namespace MediaInfoLib;

namespace {
    Core::Ref<MediaInfo> MI(nullptr);
}

namespace UI {
    AudioTreeWidgetItem::AudioTreeWidgetItem(const QString &fileName) : QTreeWidgetItem() {
        this->filename = fileName;
        if (!MI.IsValid()) {
            MI.resetObject(new MediaInfo());
        }
        MI->Open(this->filename.toStdWString());

        bool dummy;
        setText(1, QString::fromStdWString(
                MI->Get(MediaInfoLib::Stream_General, 0, __T("Title"), MediaInfoLib::Info_Text,
                        MediaInfoLib::Info_Name)));
        this->duration = QString::fromStdWString(
                MI->Get(MediaInfoLib::Stream_General, 0, __T("Duration"),
                        MediaInfoLib::Info_Text,
                        MediaInfoLib::Info_Name)).toInt(&dummy);
        setText(2, Core::formatSecondsToTime(this->duration / 1000).c_str());

        setText(3, QString::fromStdWString(MI->Get(MediaInfoLib::Stream_General, 0, __T("Album"),
                                                   MediaInfoLib::Info_Text,
                                                   MediaInfoLib::Info_Name)));

        MI->Close();

        setFlags(flags() ^ Qt::ItemIsDropEnabled);
    }

    void AudioTreeWidgetItem::setIcon(const QIcon &icon) {
        QTreeWidgetItem::setIcon(0, icon);
    }

    QMediaContent AudioTreeWidgetItem::getMediaContent() const {
        return QMediaContent(QUrl::fromLocalFile(filename));
    }

    int AudioTreeWidgetItem::getDuration() {
        return duration;
    }

    QString AudioTreeWidgetItem::getFileName() {
        return filename;
    }
}