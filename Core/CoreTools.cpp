//
// Created by mohsen on 2/13/17.
//

#include "CoreTools.h"

string Core::getEnvVariable(const string &envVar) {
    return getenv(envVar.c_str());
}