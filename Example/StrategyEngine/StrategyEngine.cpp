#include "StrategyEngine.h"

#include <iostream>

#include "Utils/Utils.h"


StrategyEngine::StrategyEngine() :
    observer(nullptr),
    _work_guard(boost::asio::make_work_guard(_ioctx)) {

}

void StrategyEngine::setObserver(StrategyEngineObserver *obs) {
    observer = obs;
}

void StrategyEngine::feedMarketData(const boost::shared_ptr<MarketData> &market_data) {
    std::cout << "StrategyEngine::feedMarketData()" <<std::endl;
    boost::asio::post(_ioctx, std::bind(&StrategyEngine::processMarketData, this, market_data));
}

void StrategyEngine::processMarketData(const boost::shared_ptr<MarketData> &market_data) {
    std::cout << "StrategyEngine::processMarketData()" <<std::endl;
}

void StrategyEngine::issueTradingInstruction() {
    if (observer) {
        observer->onTradingInstruction("buy 600001 500"); 
    }
} 

void StrategyEngine::run() { 
    std::thread(std::bind(&StrategyEngine::doRun, this)).detach();    
}

void StrategyEngine::doRun() { 
    std::cout << "StrategyEngine::doRun()" <<std::endl;
    _ioctx.run();    
}


