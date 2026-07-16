//
// Created by Oliver Šmítek on 09.07.2026.
//

#ifndef IDSETTER_H
#define IDSETTER_H



class IDsetter {

    public:

  long long IDcapasity = 0;

    IDsetter();

    static IDsetter& getInstance(){
        static IDsetter theInstance;
        return theInstance;
    }

    long long generateID();

};



#endif //IDSETTER_H
