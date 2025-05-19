#include "../include/strategy.hpp"

std::string suggestAction(double price, double sma, double rsi) {
    if (price > sma && rsi < 70 && rsi > 50) return "BUY";
    if (price < sma && rsi > 30 && rsi < 50) return "SELL";
    return "HOLD";
}
