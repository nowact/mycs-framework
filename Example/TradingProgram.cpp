#include "TradingProgram.h"
#include "boost/asio/executor_work_guard.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"

#include <iostream>
#include <functional>

TradingProgram::TradingProgram() :
    _work_guard(boost::asio::make_work_guard(_ioctx)) {
    _mdp.setMarketDataSubscriber(this);
    _se.setObserver(this);
     
}

void TradingProgram::run() {
    _mdp.run();
    _se.run();
    _ioctx.run();
}

void TradingProgram::onMarketDataUpdate(const boost::shared_ptr<MarketData> &market_data) {
    std::cout << "onMarketDataUpdate: " << std::endl;
    _se.feedMarketData(market_data);
}

void TradingProgram::onTradingInstruction(const char *instruction) {
    std::cout << "onTradingInstruction: " << instruction << std::endl;
    //_ioctx.post([](int a){});
    boost::asio::post(_ioctx, std::bind(&TradingProgram::processTradingInstruction, this, instruction));
}

void TradingProgram::processTradingInstruction(const char *instruction) {
    std::cout <<"processTradingInstruction" << std::endl;
}
