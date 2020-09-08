#include <iostream>

#include "TradingProgram.h"
#include "UsualHeader.h"

int main(int argc, char *argv[]) {


    Logger::init();

    LOGI("program start");

    TradingProgram tp;
    tp.run();    

    LOGI("program finish");

    return 0;
}

