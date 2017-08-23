//
// Created by mohsen on 2/13/17.
//

#ifndef DSPLAYER_COREFILESYSTEM_H
#define DSPLAYER_COREFILESYSTEM_H

#include <string>

using namespace std;

namespace Core {
    string getTmpDirectory();

    string getHomeDirectory();

    void createDirectory(string path);

    bool fileExists(const string &fileName);
}
#endif //DSPLAYER_COREFILESYSTEM_H
