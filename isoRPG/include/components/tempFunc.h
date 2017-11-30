//
// Created by Bjornar on 20.11.2017.
//

#ifndef ISORPG_TEMPFUNC_H
#define ISORPG_TEMPFUNC_H


#include <iostream>
#include <ostream>


bool printTempBool()
{
    std::cout << "Hello from temp" << std::endl;
    return true;
}

void printTempVoid(anax::Entity entity)
{
    std::cout << "Hello from temp" << std::endl;
}

#endif //ISORPG_TEMPFUNC_H
