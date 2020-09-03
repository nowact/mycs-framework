#include "MarketData/MarketDataProvider.h"

#include <chrono>
#include <iostream>

#include "MarketData/MarketData.h"

MarketDataProvider::MarketDataProvider() :
    _subsciber(nullptr),
    _work_guard(boost::asio::make_work_guard(_ioctx)),
    _timer(_ioctx) {

};

void MarketDataProvider::run() { 
    std::thread(std::bind(&MarketDataProvider::doRun, this)).detach();    
}

void MarketDataProvider::doRun() { 
    std::cout << "MarketDataProvider::doRun()" <<std::endl;
    _timer.expires_after(std::chrono::seconds(2));
    _timer.async_wait(std::bind(&MarketDataProvider::onTimerExpire, this, std::placeholders::_1));
    _ioctx.run();    
}

void MarketDataProvider::onTimerExpire(const boost::system::error_code &error) {
    std::cout << "MarketDataProvider::onTimerExpire()" <<std::endl;
    _timer.expires_after(std::chrono::seconds(1));
    _timer.async_wait(std::bind(&MarketDataProvider::onTimerExpire, this, std::placeholders::_1));

    publishMarketData(boost::make_shared<MarketData>());
}

void MarketDataProvider::publishMarketData(const boost::shared_ptr<MarketData> &market_data) {
    if (_subsciber) {
        _subsciber->onMarketDataUpdate(market_data); 
    }
}
