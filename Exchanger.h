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
    double* exportMoney = new double[size * repetitions];
    double totalMoney;
    double averageMoney;
    ExchangeType exchangeType;

    // Chakraborti Chakrabarti Exchange Variables
    double lambda;

    double* entropy = new double[steps];
    double* gini = new double[steps];

    void dragulescuYakovenkoStep(double data[]);
    void exchangeDragulescuYakovenko(double data[], int i, int j);

    void chakrabortiChakrabartiStep(double data[]);
    void exchangeChakrabortiChakrabarti(double data[], int i, int j);
public:
    Exchanger(int size, double totalMoney, int steps = 1000, int repetitions = 1);
    void setExchangeType(ExchangeType exchangeType);
    void setToDragulescuYakovenkoExchange();
    void setToChakrabortiChakrabartiExchange(double lambda);
    void execute();

    double *getMoney() const;
    double *getFinalMoney() const;

    void printArray(double data[], int lenght);
};


#endif //ECONOPHYSICS_GENERATOR_H
