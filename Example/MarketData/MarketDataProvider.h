#ifndef KA_MARKET_DATA_PROVIDER_H_
#define KA_MARKET_DATA_PROVIDER_H_

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

class MarketData;

class MarketDataSubscriber {
public:
    virtual void onMarketDataUpdate(const boost::shared_ptr<MarketData> &mark_data) = 0;
};

class MarketDataProvider {
public:
    MarketDataProvider();

    void setMarketDataSubscriber(MarketDataSubscriber *subsciber) {
        _subsciber = subsciber;
    }

    void run();

private:
    void doRun();
    void onTimerExpire(const boost::system::error_code &error);
    void publishMarketData(const boost::shared_ptr<MarketData> &market_data);

private:
    MarketDataSubscriber *_subsciber;
    boost::asio::io_context _ioctx;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work_guard;
    boost::asio::steady_timer _timer;
};

#endif //KA_MARKET_DATA_PROVIDER_H_

