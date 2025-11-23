//
// Created by Oliver Šmítek on 03.11.2025.
//

#ifndef INPUT_H
#define INPUT_H

#include "SprightManager.h"


class Input {

  public:

    std::string faceHeading;
    bool oneFunctionPreTime = false;

    void inputD(SprightManager& sManager);
    void inputA(SprightManager& sManager);


};



#endif //INPUT_H
