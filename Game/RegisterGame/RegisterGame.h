//
// Created by Oliver Šmítek on 16.07.2026.
//

#ifndef REGISTERGAME_H
#define REGISTERGAME_H



class RegisterGame {
    public:

    static RegisterGame& getInstance(){
        static RegisterGame theInstance;
        return theInstance;
    }

    void performGameRegistration();
};



#endif //REGISTERGAME_H
