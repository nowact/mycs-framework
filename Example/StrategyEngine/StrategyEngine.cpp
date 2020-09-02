#include "StrategyEngine.h"

//#include <>
#include "Utils/Utils.h"


StrategyEngine::StrategyEngine() : observer(nullptr) {

}

void StrategyEngine::setObserver(StrategyEngineObserver *obs) {
    observer = obs;
}

void StrategyEngine::issueTradingInstruction() {
    if (observer) {
        observer->onTradingInstruction("buy 600001 500"); 
    }
} 


