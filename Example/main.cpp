#include <iostream>

#include "TradingProgram.h"

int main(int argc, char *argv[]) {

    std::cout << "program start" << std::endl;

    TradingProgram tp;
    tp.run();    

    std::cout << "program finish" << std::endl;

    return 0;
}

