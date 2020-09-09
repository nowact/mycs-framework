#include "StrategyEngine.h"

#include <iostream>

#include "Utils/Utils.h"
#include "UsualHeader.h"


StrategyEngine::StrategyEngine() :
    observer(nullptr),
    _work_guard(boost::asio::make_work_guard(_ioctx)) {

}

void StrategyEngine::setObserver(StrategyEngineObserver *obs) {
    observer = obs;
}

void StrategyEngine::feedMarketData(const boost::shared_ptr<MarketData> &market_data) {
    LOGD("");
    boost::asio::post(_ioctx, std::bind(&StrategyEngine::processMarketData, this, market_data));
}

void StrategyEngine::processMarketData(const boost::shared_ptr<MarketData> &market_data) {
    LOGD("");
    issueTradingInstruction();
}

void StrategyEngine::issueTradingInstruction() {
    LOGD("");
    if (observer) {
        observer->onTradingInstruction("buy 600001 500"); 
    }
} 

void StrategyEngine::run() { 
    std::thread(std::bind(&StrategyEngine::doRun, this)).detach();    
}

void StrategyEngine::doRun() { 
    LOGD("");
    _ioctx.run();    
}


