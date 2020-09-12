#include "Utils/CTPApiHelper.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(set_char_array_test) {

    typedef char CharArray10TestType[10];
    CharArray10TestType ca{0};

    CTPApiHelper::setCharArray(ca, "1234");
    BOOST_TEST(strcmp(ca, "1234") == 0);

    CTPApiHelper::setCharArray(ca, "12345678909999");
    BOOST_TEST(strncmp(ca, "1234567890", 10) == 0);
    BOOST_TEST(strncmp(ca, "12345678909", 11) != 0);

    //should compile with error
    //typedef int IntArray12TestType[12];
    //IntArray12TestType ia{0};
    //CTPApiHelper::setCharArray(ia, "1234");

    //char *p = ca;
    //CTPApiHelper::setCharArray(p, "1234567890");
    //BOOST_TEST(strncmp(p, "1234567890", 10) == 0);
    
}

BOOST_AUTO_TEST_CASE(describe_depth_market_data_filed_test) {
  CThostFtdcDepthMarketDataField dmd{0};

  CTPApiHelper::setCharArray(dmd.TradingDay, "20200911");
  CTPApiHelper::setCharArray(dmd.InstrumentID, "IF2009");


#define DELI "\n"
  std::string result{
    DELI"CThostFtdcDepthMarketDataField:" 
    DELI"TradingDay <20200911>"
    DELI"InstrumentID <IF2009>"
  };

  BOOST_TEST(CTPApiHelper::describe(dmd).find(result) == 0);
}

