//
// Created by Dany1 on 31/03/2018.
//

#include "Analyzer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <omp.h>

using namespace std;

Analyzer::Analyzer() {}

Analyzer::Analyzer(const vector<double> &data) : data(data) {
    sort(Analyzer::data.begin(), Analyzer::data.end());
    size = data.size();
    setNormalizedAccumulatedData();
    setAgents();
    setNormalizedAccumulatedAgents();
}

Analyzer::Analyzer(string fileName) {
    setDataFromFile(move(fileName));
    size = data.size();
    setNormalizedAccumulatedData();
    setAgents();
    setNormalizedAccumulatedAgents();
}

const vector<double> &Analyzer::getData() const {
    return data;
}

const vector<double> &Analyzer::getAgents() const {
    return agents;
}

const vector<double> &Analyzer::getNormalizedAccumulatedAgents() const {
    return normalizedAccumulatedAgents;
}

const vector<double> &Analyzer::getNormalizedAccumulatedData() const {
    return normalizedAccumulatedData;
}

void Analyzer::setData(const vector<double> &data) {
    Analyzer::data = data;
    size = data.size();
    setNormalizedAccumulatedData();
    setAgents();
    setNormalizedAccumulatedAgents();
}

void Analyzer::setDataFromFile(string fileName) {
    vector<double> numbers;

    ifstream inputFile(fileName);        // Input file stream object

    // Check if exists and then open the file.
    if (inputFile.good()) {
        // Push items into a vector
        double current_number = 0;
        while (inputFile >> current_number){
            numbers.push_back(current_number);
        }

        // Close the file.
        inputFile.close();
        sort(numbers.begin(), numbers.end());

        Analyzer::data = numbers;

    }else {
        cout << "Error!";
        _exit(0);
    }
}

void Analyzer::setAgents() {

    vector<double> agents(size);
    Analyzer::agents.swap(agents);

    for (int i = 0; i < size; ++i) {
        Analyzer::agents[i] = 1;
    }
}

void Analyzer::setNormalizedAccumulatedData() {
    double total = 0.0;

    for (auto& n : data)
        total += n;

    vector<double> normalizedAccumulatedData(size);
    Analyzer::normalizedAccumulatedData.swap(normalizedAccumulatedData);

    Analyzer::normalizedAccumulatedData[0] = data[0] / total;
    for (int i = 1; i < size; ++i) {
        Analyzer::normalizedAccumulatedData[i] = Analyzer::normalizedAccumulatedData[i - 1] + data[i] / total;
    }
}

void Analyzer::setNormalizedAccumulatedAgents() {
    double doubleSize = double(size);

    vector<double> normalizedAccumulatedAgents(size);
    Analyzer::normalizedAccumulatedAgents.swap(normalizedAccumulatedAgents);

    Analyzer::normalizedAccumulatedAgents[0] = agents[0] / doubleSize;
    for (int i = 1; i < size; ++i) {
        Analyzer::normalizedAccumulatedAgents[i] = Analyzer::normalizedAccumulatedAgents[i - 1] + agents[i] / doubleSize;
    }

}

double Analyzer::getGini() {
    double aux = 0.0;
    for (int i = 0; i < size - 1; ++i) {
        aux += (normalizedAccumulatedAgents[i + 1] - normalizedAccumulatedAgents[i]) * (normalizedAccumulatedData[i + 1] + normalizedAccumulatedData[i]);
    }

    return abs(1.0 - aux);
}

double Analyzer::getEntropy(int m) {
    double entropy = 0.0;

    double max = data.back() * 1.000001;
    vector<int> count(m);
    double dm = max / double(m);
    for (int i = 0; i < m; ++i) {
        double dmin = dm * i;
        double dmax = dm * (i + 1); // Not counting the last one
        for (int j = 0; j < size; ++j) {
            if (data[j] > dmin and data[j] <= dmax){
                count[i] += 1;
            }
        }
    }

    vector<double> probability(m);
    for (int k = 0; k < m; ++k) {
        probability[k] = count[k] / double(size);
    }

    for (int l = 0; l < m; ++l) {
        if (probability[l] != 0.0) {
            entropy -= probability[l] * log2(probability[l]);
        }
    }

    return entropy;
}

void Analyzer::setProbability(double dm) {
    double max = data.back();
    int N = int(max / dm) + 1;
    vector<int> count(N);
    vector<double> probability(N);
    int i;
#pragma omp parallel shared(count) private(i)
    {
#pragma omp for schedule(dynamic) nowait
        for (i = 0; i < N; ++i) {
            double dmin = dm * i;
            double dmax = dm * (i + 1);
            for (int j = 0; j < size; ++j) {
                if (data[j] > dmin and data[j] <= dmax) {
                    count[i] += 1;
                }
            }
        }
    }
    for (int k = 0; k < count.size(); ++k) {
        probability[k] = count[k] / double(size);
    }

    Analyzer::probability.swap(probability);
}

void Analyzer::printProbability(double dm) {

    for (int i = 0; i < probability.size(); ++i)
        cout << dm * (i + 0.5) << "\t" << probability[i] << endl;
}








