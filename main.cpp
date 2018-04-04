#include <iostream>
#include "Analyzer.h"
#include "Exchanger.h"

using namespace std;

char *p;

void executeSecondExercise(char* argv[]){
    Analyzer analyzer(argv[1]);
    cout << "Gini: \t\t" << analyzer.getGini() << endl;
    cout << "Entropy10: \t" << analyzer.getEntropy(10) << endl;
    cout << "Entropy20: \t" << analyzer.getEntropy(20) << endl;
}

void executeThirdExercise(char* argv[]) {
    Exchanger exchanger(1000, 1000, 100000, 10000);
    switch (strtol(argv[1], &p, 10)){
        case 1:
            exchanger.setExchangeType(ExchangeType::DRAGULESCU_YAKOVENKO);
            break;
        case 2:
            switch (strtol(argv[2], &p, 10)){
                case 1:
                    exchanger.setToChakrabortiChakrabartiExchange(0.0);
                    break;
                case 2:
                    exchanger.setToChakrabortiChakrabartiExchange(0.2);
                    break;
                case 3:
                    exchanger.setToChakrabortiChakrabartiExchange(0.5);
                    break;
                default:
                    exchanger.setToChakrabortiChakrabartiExchange(0.0);
                    break;
            }
            break;
        default:
            exchanger.setExchangeType(ExchangeType::DRAGULESCU_YAKOVENKO);
            break;
    }
    exchanger.execute();
    exchanger.printArray(exchanger.getFinalMoney(), 1000 * 10000);
}

int main(int argc, char* argv[]) {
    executeThirdExercise(argv);
}

