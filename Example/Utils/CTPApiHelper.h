#ifndef KA_CTPAPI_HELPER_H_
#define KA_CTPAPI_HELPER_H_

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

#include <ctp/ThostFtdcMdApi.h>

class CTPApiHelper {
public:
    static std::string describe(const CThostFtdcDepthMarketDataField &depth_md, std::string deli = "\n") {
#define DES_FIELD(object, field) \
        ss << deli << #field" <" << object.field << ">"

        std::stringstream ss;
        ss << "\nCThostFtdcDepthMarketDataField:";
        ss << deli << "TradingDay <" << depth_md.TradingDay << ">";
        DES_FIELD(depth_md, InstrumentID);
        DES_FIELD(depth_md, ExchangeID);
        DES_FIELD(depth_md, ExchangeInstID);
        DES_FIELD(depth_md, LastPrice);
        DES_FIELD(depth_md, PreSettlementPrice);
        DES_FIELD(depth_md, PreClosePrice);
        DES_FIELD(depth_md, PreOpenInterest);
        DES_FIELD(depth_md, OpenPrice);
        DES_FIELD(depth_md, HighestPrice);
        DES_FIELD(depth_md, LowestPrice);
        DES_FIELD(depth_md, Volume);
        DES_FIELD(depth_md, Turnover);
        DES_FIELD(depth_md, OpenInterest);
        DES_FIELD(depth_md, ClosePrice);
        DES_FIELD(depth_md, SettlementPrice);
        DES_FIELD(depth_md, UpperLimitPrice);
        DES_FIELD(depth_md, LowerLimitPrice);
        DES_FIELD(depth_md, PreDelta);
        DES_FIELD(depth_md, CurrDelta);
        DES_FIELD(depth_md, UpdateTime);
        DES_FIELD(depth_md, UpdateMillisec);
        DES_FIELD(depth_md, BidPrice1);
        DES_FIELD(depth_md, BidVolume1);
        DES_FIELD(depth_md, AskPrice1);
        DES_FIELD(depth_md, AskVolume1);
        DES_FIELD(depth_md, BidPrice2);
        DES_FIELD(depth_md, BidVolume2);
        DES_FIELD(depth_md, AskPrice2);
        DES_FIELD(depth_md, AskVolume2);
        DES_FIELD(depth_md, BidPrice3);
        DES_FIELD(depth_md, BidVolume3);
        DES_FIELD(depth_md, AskPrice3);
        DES_FIELD(depth_md, AskVolume3);
        DES_FIELD(depth_md, BidPrice4);
        DES_FIELD(depth_md, BidVolume4);
        DES_FIELD(depth_md, AskPrice4);
        DES_FIELD(depth_md, AskVolume4);
        DES_FIELD(depth_md, BidPrice5);
        DES_FIELD(depth_md, BidVolume5);
        DES_FIELD(depth_md, AskPrice5);
        DES_FIELD(depth_md, AskVolume5);
        DES_FIELD(depth_md, AveragePrice);
        DES_FIELD(depth_md, ActionDay);

        return ss.str();
    }

    /*
    #define SetCharArray(array, src) _SetCharArray(array, sizeof(array), src)

    void _SetCharArray(char array[], size_t size, const char *src) {
        strncpy(array, src, size);
    }
    */

    template<class T,
             class = typename std::enable_if<
                       std::is_array<T>::value &&
                       std::is_same<char*, typename std::decay<T>::type>::value>::type
            >
    static void setCharArray(T& array, const char* src) {
        strncpy(array, src, sizeof(array));
    }

    template<class T,
             class = typename std::enable_if<
                       std::is_array<T>::value &&
                       std::is_same<char*, typename std::decay<T>::type>::value>::type
            >
    static std::string readCharArray(const T& array) {

    }
};

#endif //KA_CTPAPI_HELPER_H_

