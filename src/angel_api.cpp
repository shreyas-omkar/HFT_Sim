#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>

using json = nlohmann::json;

// Replace these with your actual keys
const std::string API_KEY = "gKyQKPXM ";
const std::string SECRET_KEY = "c5ea77cb-146d-432e-9be8-71a84e108bec ";

std::string generateJwtToken() {
    json body = {
        {"api_key", API_KEY},
        {"secret_key", SECRET_KEY}
    };

    auto response = cpr::Post(
        cpr::Url{"https://apiconnect.angelbroking.com/rest/auth/angelbroking/jwt/v1/generateTokens"},
        cpr::Header{
            {"Content-Type", "application/json"},
            {"Accept", "application/json"}
        },
        cpr::Body{body.dump()}
    );

    if (response.status_code != 200) {
        std::cerr << "Auth failed: " << response.status_code << "\n" << response.text << "\n";
        return "";
    }

    json res = json::parse(response.text);
    return res["data"]["jwtToken"];
}

std::vector<double> fetchClosePrices(const std::string& symbolToken, const std::string& jwtToken) {
    std::string body = R"({
        "exchange": "NSE",
        "symboltoken": ")" + symbolToken + R"(",
        "interval": "FIVE_MINUTE",
        "fromdate": "2025-05-12 09:15",
        "todate": "2025-05-13 15:30"
    })";

    auto response = cpr::Post(
        cpr::Url{"https://apiconnect.angelbroking.com/rest/secure/angelbroking/historical/v1/getCandleData"},
        cpr::Header{
            {"Authorization", "Bearer " + jwtToken},
            {"Content-Type", "application/json"},
            {"Accept", "application/json"},
            {"X-PrivateKey", API_KEY},  // Use the API key here
            {"X-SourceID", "WEB"},
            {"X-ClientLocalIP", "127.0.0.1"},
            {"X-ClientPublicIP", "127.0.0.1"},
            {"X-MACAddress", "00:11:22:33:44:55"}
        },
        cpr::Body{body}
    );

    if (response.status_code != 200) {
        std::cerr << "Failed to fetch data: " << response.status_code << "\n" << response.text << std::endl;
        return {};
    }

    json jsonData = json::parse(response.text);
    std::vector<double> prices;

    for (const auto& candle : jsonData["data"]) {
        prices.push_back(std::stod(candle[5].get<std::string>()));  // Close price
    }

    return prices;
}

int main() {
    std::string jwt = generateJwtToken();
    if (jwt.empty()) return 1;

    std::vector<double> prices = fetchClosePrices("3045", jwt); // Example token for RELIANCE
    for (double price : prices) {
        std::cout << price << "\n";
    }

    return 0;
}
