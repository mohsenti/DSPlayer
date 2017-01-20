//
// Created by mohsen on 1/16/17.
//

#include "DateTimeHelper.h"

std::string Core::formatSecondsToTime(const int &seconds, bool long_format) {
    int h, m, s;
    s = seconds;
    h = s / 3600;
    s %= 3600;
    m = s / 60;
    s %= 60;
    std::stringstream stream;

    if (long_format) {
        if (h > 9)
            stream << h;
        else if (h > 0)
            stream << "0" << h;
        else stream << "00";
        stream << ":";

        if (m > 9)
            stream << m;
        else if (m > 0)
            stream << "0" << m;
        else stream << "00";
        stream << ":";

        if (s > 9)
            stream << s;
        else if (s > 0)
            stream << "0" << s;
        else stream << "00";
    } else {
        if (h > 0) {
            stream << h;
            stream << ":";
        }

        if (m > 9)
            stream << m;
        else if (m > 0)
            stream << "0" << m;
        else stream << "00";
        stream << ":";

        if (s > 9)
            stream << s;
        else if (s > 0)
            stream << "0" << s;
        else stream << "00";
    }

    return stream.str();
}
