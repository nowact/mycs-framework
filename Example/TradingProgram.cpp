#include "TradingProgram.h"

#include <iostream>

TradingProgram::TradingProgram() {
    se.setObserver(this);
     
}

void TradingProgram::run() {

}

void TradingProgram::onTradingInstruction(const char *instruction) {
    std::cout << "onTradingInstruction: " << instruction << std::endl;
}
