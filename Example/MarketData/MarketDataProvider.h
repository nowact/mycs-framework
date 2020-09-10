#ifndef KA_MARKET_DATA_PROVIDER_H_
#define KA_MARKET_DATA_PROVIDER_H_

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

#include <ctp/ThostFtdcMdApi.h>

class MarketData;

class MarketDataSubscriber {
public:
    virtual void onMarketDataUpdate(const boost::shared_ptr<MarketData> &mark_data) = 0;
};

class MarketDataProvider : public CThostFtdcMdSpi {
public:
    MarketDataProvider();
    ~MarketDataProvider();

    void setMarketDataSubscriber(MarketDataSubscriber *subsciber) {
        _subsciber = subsciber;
    }

    void run();

private:
    void setupCTPMdApi();
    //CThostFtdcMdSpi 
    virtual void OnFrontConnected() override;
    virtual void OnFrontDisconnected(int nReason) override;

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) override;

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                CThostFtdcRspInfoField *pRspInfo,
                                int nRequestID, bool bIsLast) override;
    ///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) override;


private:
    void doRun();
    void onTimerExpire(const boost::system::error_code &error);
    void publishMarketData(const boost::shared_ptr<MarketData> &market_data);
    //Generate Request ID
    int genReqID() {
        return ++_md_req_id; 
    }


private:
    MarketDataSubscriber *_subsciber{nullptr};
    boost::asio::io_context _ioctx;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _work_guard;
    boost::asio::steady_timer _timer;

    CThostFtdcMdApi *_ctp_md_api{nullptr};
    int _md_req_id{0};
};

#endif //KA_MARKET_DATA_PROVIDER_H_

