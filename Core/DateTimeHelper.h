//
// Created by mohsen on 1/16/17.
//

#ifndef DSPLAYER_DATETIMEHELPER_H
#define DSPLAYER_DATETIMEHELPER_H

#include <string>
#include <sstream>

namespace Core {
    std::string formatSecondsToTime(const int &seconds, bool long_format = false);
}

#endif //DSPLAYER_DATETIMEHELPER_H
