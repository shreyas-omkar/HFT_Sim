#include <iostream>
#include "../include/angel_api.hpp"
#include "../include/indicators.hpp"
#include "../include/strategy.hpp"

int main() {
    std::string symbol = "RELIANCE";
    auto closePrices = fetchClosePrices(symbol);

    if (closePrices.size() < 15) {
        std::cerr << "Not enough data.\n";
        return 1;
    }

    double sma = calculateSMA(closePrices, 14);
    double rsi = calculateRSI(closePrices, 14);
    double price = closePrices.back();

    std::cout << "Current Price: " << price << "\n";
    std::cout << "SMA(14): " << sma << "\n";
    std::cout << "RSI(14): " << rsi << "\n";
    std::cout << "Suggested Action: " << suggestAction(price, sma, rsi) << "\n";

    return 0;
}
