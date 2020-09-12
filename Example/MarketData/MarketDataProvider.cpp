#include "MarketData/MarketDataProvider.h"

#include <chrono>
#include <iostream>


#include "MarketData/MarketData.h"
#include "UsualHeader.h"


#define LOG_RSP_INFO LOGD("ReqID {} IsLast {} ErrorID {} ErrorMsg {} ", nRequestID, bIsLast, pRspInfo ? pRspInfo->ErrorID : 0, pRspInfo ? pRspInfo->ErrorMsg : "null")

MarketDataProvider::MarketDataProvider() :
    _subsciber(nullptr),
    _work_guard(boost::asio::make_work_guard(_ioctx)),
    _timer(_ioctx) {

};

void MarketDataProvider::run() { 
    std::thread(std::bind(&MarketDataProvider::doRun, this)).detach();    
}

void MarketDataProvider::doRun() { 
    LOGD("");
    //_timer.expires_after(std::chrono::seconds(2));
    //_timer.async_wait(std::bind(&MarketDataProvider::onTimerExpire, this, std::placeholders::_1));
    setupCTPMdApi();
    _ioctx.run();    
}

void MarketDataProvider::onTimerExpire(const boost::system::error_code &error) {
    LOGD("");
    _timer.expires_after(std::chrono::seconds(1));
    _timer.async_wait(std::bind(&MarketDataProvider::onTimerExpire, this, std::placeholders::_1));

    publishMarketData(boost::make_shared<MarketData>());
}

void MarketDataProvider::publishMarketData(const boost::shared_ptr<MarketData> &market_data) {
    LOGD("");
    if (_subsciber) {
        _subsciber->onMarketDataUpdate(market_data); 
    }
}

void MarketDataProvider::setupCTPMdApi() {
    LOGD("");
    _ctp_md_api = CThostFtdcMdApi::CreateFtdcMdApi("./flow_md/");
    _ctp_md_api->RegisterSpi(this);
    const char *front_addr { "tcp://180.168.146.187:10110" };
    _ctp_md_api->RegisterFront(const_cast<char*>(front_addr));
    _ctp_md_api->Init();
}

void MarketDataProvider::OnFrontConnected() {
    LOGD("");
    CThostFtdcReqUserLoginField req = {0};
    int ec = _ctp_md_api->ReqUserLogin(&req, genReqID());
    if (ec != 0) {
        LOGW("ctp md ReqUserLogin return {}", ec);
    }
}

void MarketDataProvider::OnFrontDisconnected(int nReason) {
    LOGD("");
}

void MarketDataProvider::OnHeartBeatWarning(int nTimeLapse) {
    LOGD("");

}

void MarketDataProvider::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                        CThostFtdcRspInfoField *pRspInfo,
                                        int nRequestID, bool bIsLast) {
    //LOGD("ReqID {} IsLast {} ErrorID {} ErrorMsg {} ", nRequestID, bIsLast, pRspInfo ? pRspInfo->ErrorID : 0, pRspInfo ? pRspInfo->ErrorMsg : "nullptr");
    LOG_RSP_INFO;

    const char * instrument_list[]{"IF2009", };
    _ctp_md_api->SubscribeMarketData(const_cast<char**>(instrument_list), 1);
}

///登出请求响应
void MarketDataProvider::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOGD("");

}

///错误应答
void MarketDataProvider::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOG_RSP_INFO;

}

///订阅行情应答
void MarketDataProvider::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOG_RSP_INFO;
    if (pSpecificInstrument) {
        LOGD("InstrumntID {}", pSpecificInstrument->InstrumentID);
    } else {
        LOGD("pSpecificInstrument is null"); 
    }
}

///取消订阅行情应答
void MarketDataProvider::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOGD("");

}

///订阅询价应答
void MarketDataProvider::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOGD("");

}

///取消订阅询价应答
void MarketDataProvider::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    LOGD("");

}

///深度行情通知
void MarketDataProvider::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    LOGD("");
    if (pDepthMarketData) {
        LOGD("describe pDepthMarketData {}", CTPApiHelper::describe(*pDepthMarketData, " "));
    }
}

///询价通知
void MarketDataProvider::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
    LOGD("");

}

MarketDataProvider::~MarketDataProvider() {
    _subsciber = nullptr;
    _ctp_md_api->Release();
    //_ctp_md_api->Join(); //_ctp_md_api usable after release?
    _ctp_md_api = nullptr;
}

