//
// Created by mohsen on 2/13/17.
//

#include <zconf.h>
#include "CoreFileSystem.h"
#include "Core.h"

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#endif

string Core::getTmpDirectory() {
    string result;
#ifdef __linux__
    result = Core::getEnvVariable("TEMP");
    if (result.empty()) {
        result = Core::getEnvVariable("TMP");
        if (result.empty()) {
            result = Core::getEnvVariable("TMPDIR");
            if (result.empty()) {
                result = "/tmp/";
            }
        }
    }
    if (result.at(result.length() - 1) != '/')
        result += "/";
#elif _WIN32
    TCHAR lpTempPathBuffer[MAX_PATH];
    DWORD dwRetVal = GetTempPath(MAX_PATH, lpTempPathBuffer); // buffer for path
    result = lpTempPathBuffer;
    if (result.at(result.length() - 1) != '\\')
        result += "\\";
#endif
}

bool Core::fileExists(const string &fileName) {
    return access(fileName.c_str(), F_OK) == 0;
}
