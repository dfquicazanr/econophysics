#include <iostream>
#include <fstream>
#include "Analyzer.h"
#include "Exchanger.h"

using namespace std;

char *p;

void executeSecondExercise(char* argv[]){
    Analyzer analyzer(argv[2]);
    /*cout << "Gini: \t\t" << analyzer.getGini() << endl;
    cout << "Entropy10: \t" << analyzer.getEntropy(10) << endl;
    cout << "Entropy20: \t" << analyzer.getEntropy(20) << endl;*/
    analyzer.setProbability(0.1);
    analyzer.printProbability(0.1);
}

void executeThirdExercise(char* argv[]) {
    int size = 1000, totalMoney = 1000, steps = 100000, repetitions = 10000;
    Exchanger exchanger(size, totalMoney, steps, repetitions);
    switch (strtol(argv[2], &p, 10)){
        case 1:
            exchanger.setToDragulescuYakovenkoExchange();
            break;
        case 2:
            switch (strtol(argv[3], &p, 10)){
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
        case 3:
            switch (strtol(argv[3], &p, 10)){
                case 1:
                    exchanger.setToBouchardMezardExchange(0.0);
                    break;
                case 2:
                    exchanger.setToBouchardMezardExchange(0.3);
                    break;
                case 3:
                    exchanger.setToBouchardMezardExchange(0.7);
                    break;
                default:
                    exchanger.setToBouchardMezardExchange(0.0);
                    break;
            }
            break;
        default:
            exchanger.setToDragulescuYakovenkoExchange();
            break;
    }
    exchanger.execute();
    exchanger.printArray(exchanger.getFinalMoney(), size * repetitions);
    //exchanger.printArray(exchanger.getAvMoney(), size);
}

int main(int argc, char* argv[]) {
    switch (strtol(argv[1], &p, 10)) {
        case 1:
            executeSecondExercise(argv);
            break;
        case 2:
            executeThirdExercise(argv);
            break;
        default:
            cout << "Enter all the parameters";
            break;
    }
}

