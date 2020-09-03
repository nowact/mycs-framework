#ifndef KA_STRATEGY_ENGINE_H_
#define KA_STRATEGY_ENGINE_H_

#include <boost/asio.hpp>

class MarketData;

class StrategyEngineObserver {
public:
    virtual void onTradingInstruction(const char *instruction) = 0;

};

class StrategyEngine {
public:
    StrategyEngine();
    void setObserver(StrategyEngineObserver *obs);
    void feedMarketData(const boost::shared_ptr<MarketData> &market_data);
    void run();

private:
    void processMarketData(const boost::shared_ptr<MarketData> &market_data);
    void issueTradingInstruction();
    void doRun();

private:
    StrategyEngineObserver *observer; //not owned
    boost::asio::io_context _ioctx;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work_guard;
};

#endif //KA_STRATEGY_ENGINE_H_

