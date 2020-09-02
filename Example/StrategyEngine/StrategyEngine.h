#ifndef KA_STRATEGY_ENGINE_H_
#define KA_STRATEGY_ENGINE_H_

class StrategyEngineObserver {
public:
    virtual void onTradingInstruction(const char *instruction) = 0;

};

class StrategyEngine {
public:
    StrategyEngine();
    void setObserver(StrategyEngineObserver *obs);
    void feedMarketData();

private:
    void issueTradingInstruction();

private:
    StrategyEngineObserver *observer; //not owned
};

#endif //KA_STRATEGY_ENGINE_H_

