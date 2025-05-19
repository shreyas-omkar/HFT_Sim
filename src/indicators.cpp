#include "../include/indicators.hpp"

double calculateSMA(const std::vector<double>& prices, int period) {
    if (prices.size() < period) return -1;
    double sum = 0;
    for (int i = prices.size() - period; i < prices.size(); ++i)
        sum += prices[i];
    return sum / period;
}

double calculateRSI(const std::vector<double>& prices, int period) {
    if (prices.size() < period + 1) return -1;
    double gain = 0, loss = 0;

    for (size_t i = prices.size() - period; i < prices.size(); ++i) {
        double diff = prices[i] - prices[i - 1];
        if (diff > 0) gain += diff;
        else loss -= diff;
    }

    if (loss == 0) return 100;
    double rs = gain / loss;
    return 100 - (100 / (1 + rs));
}
