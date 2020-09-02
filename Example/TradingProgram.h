#ifndef KA_TRADING_PROGRAM_H_
#define KA_TRADING_PROGRAM_H_

#include "StrategyEngine/StrategyEngine.h"

class TradingProgram : public StrategyEngineObserver {
public:
    TradingProgram();
    void run();
    virtual void onTradingInstruction(const char *instruction);

private:
    StrategyEngine se;
};

#endif //KA_TRADING_PROGRAM_H_
