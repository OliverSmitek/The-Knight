//
// Created by Oliver Šmítek on 09.07.2026.
//

#include "IDsetter.h"

IDsetter::IDsetter() = default;

long long IDsetter::generateID() {
    IDcapasity++;

    return IDcapasity;
}