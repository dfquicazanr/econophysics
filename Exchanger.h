//
// Created by Dany1 on 01/04/2018.
//

#ifndef ECONOPHYSICS_GENERATOR_H
#define ECONOPHYSICS_GENERATOR_H

#include <string>

using namespace std;

enum ExchangeType {
    DRAGULESCU_YAKOVENKO,
    CHAKRABORTI_CHAKRABARTI,
    BOUCHARD_MEZARD
};

class Exchanger {
private:
    int size;
    int steps;
    int repetitions;
    double* money = new double[size];
    double* avMoney = new double[size];
    double* exportMoney = new double[size * repetitions];
    double totalMoney;
    double averageMoney;
    ExchangeType exchangeType;

    // Chakraborti-Chakrabarti Exchange Variables
    double lambda;

    // Bouchard-Mezard Exchange Variables
    double J;

    double* entropy = new double[steps];
    double* gini = new double[steps];

    void dragulescuYakovenkoStep(double data[]);

    void chakrabortiChakrabartiStep(double data[]);
    void bouchardMezardStep(double data[]);
public:
    Exchanger(int size, double totalMoney, int steps = 1000, int repetitions = 1);
    void setExchangeType(ExchangeType exchangeType);
    void setToDragulescuYakovenkoExchange();
    void setToChakrabortiChakrabartiExchange(double lambda);
    void setToBouchardMezardExchange(double J);
    void execute();

    double *getFinalMoney() const;
    double *getAvMoney() const;

    void printArray(double data[], int lenght);
};


#endif //ECONOPHYSICS_GENERATOR_H
