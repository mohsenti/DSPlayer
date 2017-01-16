//
// Created by mohsen on 1/16/17.
//

#ifndef DSPLAYER_DATETIMEHELPER_H
#define DSPLAYER_DATETIMEHELPER_H

#include <string>
#include <sstream>

namespace Core {
    std::string formatSecondsToTime(const int seconds) {
        int h, m, s;
        s = seconds;
        h = s / 3600;
        s %= 3600;
        m = s / 60;
        s %= 60;
        std::stringstream stream;
        if (h > 0)
            stream << h << ":";
        stream << m << ":" << s;
        return stream.str();
    }
}

#endif //DSPLAYER_DATETIMEHELPER_H
