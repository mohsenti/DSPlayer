//
// Created by mohsen on 1/19/17.
//

#ifndef DSPLAYER_CORETYPES_H
#define DSPLAYER_CORETYPES_H

namespace Core {
    typedef struct {
        int currentItemIndex;
        int volume;
        int seekBarPosition;
        int playerState;
        int playlistItemsCount;
        bool repeat;
        bool shuffle;
    } ApplicationState;
}
#endif //DSPLAYER_CORETYPES_H
