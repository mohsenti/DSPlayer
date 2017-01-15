//
// Created by mohsen on 1/15/17.
//

#include "MimeType.h"

#ifdef USE_QT

bool Core::MimeType::isAudioFile(QFile &file) {
    if (file.isOpen())
        file.seek(0);
    else {
        if (!file.open(QFile::OpenModeFlag::ReadOnly)) return false;
    }
    char bytes[20];
    file.read(bytes, 20);
    return isAudio(bytes);
}

#endif

bool Core::MimeType::isAudio(const char *first20bytes) {
    //Documented at : https://en.wikipedia.org/wiki/List_of_file_signatures
    if (first20bytes[0] == 0xFF && first20bytes[1] == 0xFB) //MP3 without ID3 tag
        return true;
    if (first20bytes[0] == 'I' && first20bytes[1] == 'D' && first20bytes[2] == '3') //MP3 with ID3 tag
        return true;

    if (first20bytes[8] == 'W' && first20bytes[9] == 'A' && first20bytes[10] == 'V' && first20bytes[11] == 'E') //WAVE
        return true;

    if (first20bytes[0] == 'O' && first20bytes[1] == 'g' && first20bytes[2] == 'g' && first20bytes[3] == 'S') //Ogg
        return true;

    return false;
}
