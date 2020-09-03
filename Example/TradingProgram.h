#ifndef KA_TRADING_PROGRAM_H_
#define KA_TRADING_PROGRAM_H_

#include <boost/asio.hpp>

#include "StrategyEngine/StrategyEngine.h"
#include "MarketData/MarketDataProvider.h"


class TradingProgram : public MarketDataSubscriber, public StrategyEngineObserver {
public:
    TradingProgram();
    void run();
    virtual void onMarketDataUpdate(const boost::shared_ptr<MarketData> &market_data);
    virtual void onTradingInstruction(const char *instruction);


private:
    void processTradingInstruction(const char *instruction);

private:
    MarketDataProvider _mdp;
    StrategyEngine _se;

    boost::asio::io_context _ioctx;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work_guard;
};

#endif //KA_TRADING_PROGRAM_H_
