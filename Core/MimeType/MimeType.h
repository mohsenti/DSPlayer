//
// Created by mohsen on 1/15/17.
//

#ifndef DSPLAYER_MIMETYPE_H
#define DSPLAYER_MIMETYPE_H

#ifdef USE_QT

#include <QFile>

#endif
namespace Core {
    class MimeType {
    public:
#ifdef USE_QT

        static bool isAudioFile(QFile &file);

#endif

        static bool isAudio(const char *first20bytes);
    };
}


#endif //DSPLAYER_MIMETYPE_H
