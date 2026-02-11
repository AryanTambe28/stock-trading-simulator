#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

class Stock {
public:
    string symbol;
    double price;

    Stock(string s, double p) {
        symbol = s;
        price = p;
    }
};

class Market {
public:
    map<string, double> stocks;

    void addStock(string symbol, double price) {
        stocks[symbol] = price;
    }

    void displayMarket() {
        cout << "\nMarket Data:\n";
        for (auto s : stocks) {
            cout << s.first << " : " << s.second << endl;
        }
    }
};

class Portfolio {
private:
    map<string, int> holdings;
    double cash;

public:
    Portfolio(double initialCash) {
        cash = initialCash;
    }

    void buyStock(string symbol, int qty, double price) {
        double cost = qty * price;

        if (cash >= cost) {
            holdings[symbol] += qty;
            cash -= cost;
            cout << "Bought " << qty << " shares of " << symbol << endl;
        } else {
            cout << "Not enough balance!\n";
        }
    }

    void sellStock(string symbol, int qty, double price) {
        if (holdings[symbol] >= qty) {
            holdings[symbol] -= qty;
            cash += qty * price;
            cout << "Sold " << qty << " shares of " << symbol << endl;
        } else {
            cout << "Not enough shares!\n";
        }
    }

    void displayPortfolio() {
        cout << "\nPortfolio:\n";
        for (auto h : holdings) {
            cout << h.first << " : " << h.second << endl;
        }
        cout << "Cash Balance: " << cash << endl;
    }

    void saveToFile() {
        ofstream file("portfolio.txt");
        file << cash << endl;
        for (auto h : holdings) {
            file << h.first << " " << h.second << endl;
        }
        file.close();
    }
};

int main() {
    Market market;
    market.addStock("AAPL", 180);
    market.addStock("TSLA", 250);
    market.addStock("TCS", 3900);

    Portfolio portfolio(10000);

    int choice;
    while (true) {
        cout << "\n1. Show Market\n2. Buy\n3. Sell\n4. Portfolio\n5. Exit\n";
        cin >> choice;

        if (choice == 1) {
            market.displayMarket();
        }
        else if (choice == 2) {
            string sym;
            int qty;
            cout << "Enter symbol and quantity: ";
            cin >> sym >> qty;
            portfolio.buyStock(sym, qty, market.stocks[sym]);
        }
        else if (choice == 3) {
            string sym;
            int qty;
            cout << "Enter symbol and quantity: ";
            cin >> sym >> qty;
            portfolio.sellStock(sym, qty, market.stocks[sym]);
        }
        else if (choice == 4) {
            portfolio.displayPortfolio();
        }
        else {
            portfolio.saveToFile();
            break;
        }
    }

    return 0;
}
