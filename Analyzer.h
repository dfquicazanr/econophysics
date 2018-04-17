//
// Created by Dany1 on 31/03/2018.
//

#ifndef ECONOPHYSICS_ANALIZER_H
#define ECONOPHYSICS_ANALIZER_H

#include <vector>
#include <string>

using namespace std;

class Analyzer {
private:
    int size;
    vector<double> agents;
    vector<double> normalizedAccumulatedAgents;
    vector<double> data;
    vector<double> normalizedAccumulatedData;
    vector<double> probability;
public:
    Analyzer();

    Analyzer(const vector<double> &data);
    Analyzer(string fileName);

    const vector<double> &getData() const;
    const vector<double> &getAgents() const;

    const vector<double> &getNormalizedAccumulatedAgents() const;
    const vector<double> &getNormalizedAccumulatedData() const;

    void setData(const vector<double> &data);
    void setDataFromFile(string fileName);
    void setAgents();
    void setNormalizedAccumulatedData();
    void setNormalizedAccumulatedAgents();
    void setProbability(double dm);

    double getGini();
    double getEntropy(int m = 10);

    void printProbability(double dm);
};


#endif //ECONOPHYSICS_ANALIZER_H
