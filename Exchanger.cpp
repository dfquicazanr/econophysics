//
// Created by Dany1 on 01/04/2018.
//

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <omp.h>
#include <algorithm>
#include "Exchanger.h"
#include "Analyzer.h"

double get( const double*const src, const size_t index ) { return src[index]; }
int set( double*const dst, const size_t index, const double value ) { dst[index] = value; }

Exchanger::Exchanger(int size, double totalMoney, int steps, int repetitions) :
        size(size), totalMoney(totalMoney), steps(steps), repetitions(repetitions) {
    averageMoney = totalMoney / double(size);
    for (int i = 0; i < size; ++i)
        money[i] = averageMoney;
}

void Exchanger::setExchangeType(ExchangeType exchangeType) {
    Exchanger::exchangeType = exchangeType;
}

void Exchanger::setToDragulescuYakovenkoExchange() {
    exchangeType = ExchangeType::DRAGULESCU_YAKOVENKO;
}

void Exchanger::setToChakrabortiChakrabartiExchange(double lambda){
    exchangeType = ExchangeType::CHAKRABORTI_CHAKRABARTI;
    Exchanger::lambda = lambda;
}

void Exchanger::setToBouchardMezardExchange(double J) {
    exchangeType = ExchangeType::BOUCHARD_MEZARD;
    Exchanger::J = J;
}

void Exchanger::dragulescuYakovenkoStep(double data[]) {
    int i = int((double) rand() / RAND_MAX * size);
    int j = int((double) rand() / RAND_MAX * size);
    double nu = (double) rand() / RAND_MAX;
    double dm = nu * (data[i] + data[j]) / 2.0;
    if (data[i] - dm > 0){
        data[i] -= dm;
        data[j] += dm;
    }
}


void Exchanger::chakrabortiChakrabartiStep(double *data) {
    int i = int((double) rand() / RAND_MAX * size);
    int j = int((double) rand() / RAND_MAX * size);
    double nu = (double) rand() / RAND_MAX;
    double dmi = nu * (1.0 - lambda) * (data[i] + data[j]);
    double dmj = (1.0 - nu) * (1.0 - lambda) * (data[i] + data[j]);
    data[i] = lambda * data[i] + dmi;
    data[j] = lambda * data[j] + dmj;
}

void Exchanger::bouchardMezardStep(double data[]) {
    int i = int((double) rand() / RAND_MAX * size);
    int j = int((double) rand() / RAND_MAX * size);
    double averageWealth = averageMoney;
    /*double averageWealth = 0.0;
    for (int k = 0; k < size; ++k) averageWealth += data[k];
    averageWealth /= double(size);*/
    double nu = (double) rand() / RAND_MAX;
    double dm = J * (averageWealth - data[i]) + nu * data[i];
    if (data[i] - dm > 0 and data[j] + dm > 0){
        data[i] -= dm;
        data[j] += dm;
    }
}

/*
void Exchanger::bouchardMezardStep(double data[]) {
    double averageWealth = 0.0;
    for (int i = 0; i < size; ++i) averageWealth += data[i];
    averageWealth /= double(size);
    int i;
#pragma omp parallel shared(data) private(i)
    {
#pragma omp for schedule(dynamic) nowait
        for (i = 0; i < size; ++i) {
            double nu = (double) rand() / RAND_MAX - 0.5;
            data[i] += J * (averageWealth - data[i]) + nu * data[i];
        }
    }
}
*/

void Exchanger::printArray(double *data, int lenght) {
    for (int i = 0; i < lenght; ++i) {
        cout << data[i] << endl;
    }
}

void Exchanger::execute() {
    int i;
#pragma omp parallel shared(exportMoney) private(i)
    {
#pragma omp for schedule(dynamic) nowait
        for (i = 0; i < repetitions; ++i) {
            double data[size];
            for (size_t k = 0; k < size; ++k)
                set(data, k, get(money, k));

            switch (exchangeType) {
                case DRAGULESCU_YAKOVENKO:
                    for (int j = 0; j < steps; ++j) {
                        dragulescuYakovenkoStep(data);
                    }
                    break;
                case CHAKRABORTI_CHAKRABARTI:
                    for (int j = 0; j < steps; ++j) {
                        chakrabortiChakrabartiStep(data);
                    }
                    break;
                case BOUCHARD_MEZARD:
                    for (int j = 0; j < steps; ++j) {
                        bouchardMezardStep(data);
                    }
                    break;
                default:
                    break;
            }

            sort(data, data + size, greater<double>());

            for (int i1 = 0; i1 < size; ++i1) {
                exportMoney[size * i + i1] += data[i1];
                avMoney[i1] += data[i1];
            }
        }
    }
    for (int i1 = 0; i1 < size; ++i1) {
        avMoney[i1] = avMoney[i1] / double(repetitions);
    }
}

double *Exchanger::getFinalMoney() const {
    return exportMoney;
}

double *Exchanger::getAvMoney() const {
    return avMoney;
}




