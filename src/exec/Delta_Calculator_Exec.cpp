// https://doi.org/10.1109/CEC.2006.1688406

#include "../utils/ArgumentParser.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

double d(const std::vector<double> & x,
         const std::vector<std::vector<double>> & S) {
    double result = std::numeric_limits<double>::max();

    for(const std::vector<double> & y : S) {
        if(!std::equal(x.begin(),
                       x.end(),
                       y.begin(),
                       [](const double & a, const double & b) {
                            return fabs(a - b) <
                                std::numeric_limits<double>::epsilon();
                       })) {
            double curr = 0;

            for(unsigned i = 0; i < x.size() && i < y.size(); i++) {
                curr += (x[i] - y[i]) * (x[i] * y[i]);
            }

            curr = sqrt(curr);

            if(result > curr) {
                result = curr;
            }
        }
    }

    return result;
}

double delta(const std::vector<std::vector<double>> & Sstar,
             const std::vector<std::vector<double>> & S) {
    double result = 0.0;
    unsigned m = Sstar.front().size();
    std::vector<std::vector<double>> e(m, Sstar.front());
    double sumDeiS = 0.0,
           dSum = 0.0,
           dBar = 0.0;

    for(unsigned i = 0; i < m; i++) {
        std::vector<double> e = Sstar.front();

        for(const std::vector<double> & x : Sstar) {
            if(e[i] > x[i]) {
                e = x;
            }
        }

        sumDeiS += d(e, S);
    }

    for(const std::vector<double> & x : Sstar) {
        dSum += d(x, S);
    }

    dBar = dSum / ((double) Sstar.size());

    result = sumDeiS;

    for(const std::vector<double> & x : Sstar) {
        result += abs(d(x, S) - dBar);
    }

    result /= sumDeiS + dSum;

    return result;
}

int main(int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    unsigned numObjectives = 2;
    std::vector<std::vector<double>> optimalPareto;
    std::vector<std::vector<std::vector<double>>> paretos;
    std::vector<std::vector<unsigned>> capturedIterations;
    std::vector<std::vector<double>> capturedTimes;
    std::vector<std::vector<std::vector<std::vector<double>>>> capturedParetos;
    unsigned numSolvers;

    for(numSolvers = 0;
        argParser.cmdOptionExists("--pareto-" + std::to_string(numSolvers));
        numSolvers++) {}

    paretos.resize(numSolvers);
    capturedIterations.resize(numSolvers);
    capturedTimes.resize(numSolvers);
    capturedParetos.resize(numSolvers);

    if(argParser.cmdOptionExists("--optimal-pareto")) {
        std::string optimalParetoFilename =
            argParser.getCmdOption("--optimal-pareto");
        std::ifstream ifs;
        ifs.open(optimalParetoFilename);

        if(ifs.is_open()) {
            for(std::string line; std::getline(ifs, line);) {
                std::istringstream iss(line);
                std::vector<double> solution(numObjectives, 0.0);

                for(unsigned j = 0; j < numObjectives; j++) {
                    if(!(iss >> solution[j])) {
                        throw "Error reading file.";
                    }
                }

                optimalPareto.push_back(solution);
            }
        }
    }

    for(unsigned i = 0; i < numSolvers; i++) {
        if(!argParser.cmdOptionExists("--pareto-" + std::to_string(i))) {
            break;
        }

        std::string paretoFilename = argParser.getCmdOption(
                "--pareto-" + std::to_string(i));
        std::ifstream ifs;
        ifs.open(paretoFilename);

        if(ifs.is_open()) {
            for(std::string line; std::getline(ifs, line);) {
                std::istringstream iss(line);
                std::vector<double> costs(numObjectives, 0.0);

                for(unsigned j = 0; j < numObjectives; j++) {
                    if(!(iss >> costs[j])) {
                        throw "Error reading file.";
                    }
                }

                paretos[i].push_back(costs);
            }
        } else {
            throw "File not found.";
        }
    }

    for(unsigned i = 0; i < numSolvers; i++) {
        if(!argParser.cmdOptionExists(
                    "--captured-paretos-" + std::to_string(i))) {
            break;
        }

        std::string capturedParetosFilename = argParser.getCmdOption(
                "--captured-paretos-" + std::to_string(i));

        for(unsigned j = 0; ; j++) {
            std::ifstream ifs;
            ifs.open(capturedParetosFilename + std::to_string(j) + ".txt");

            if(ifs.is_open()) {
                unsigned capturedIteration;
                double capturedTime;

                ifs >> capturedIteration >> capturedTime;

                capturedIterations[i].push_back(capturedIteration);
                capturedTimes[i].push_back(capturedTime);
                capturedParetos[i].emplace_back();

                ifs.ignore();

                for(std::string line; std::getline(ifs, line);) {
                    std::istringstream iss(line);
                    std::vector<double> costs(numObjectives, 0.0);

                    for(unsigned j = 0; j < numObjectives; j++) {
                        if(!(iss >> costs[j])) {
                            throw "Error reading file.";
                        }
                    }

                    capturedParetos[i].back().push_back(costs);
                }
            } else {
                break;
            }
        }
    }

    for(unsigned i = 0; i < numSolvers; i++) {
        if(!argParser.cmdOptionExists("--delta-" + std::to_string(i))) {
            break;
        }

        std::string deltaFilename =
            argParser.getCmdOption("--delta-" + std::to_string(i));

        std::ofstream ofs;
        ofs.open(deltaFilename);

        if(ofs.is_open()) {
            ofs << delta(optimalPareto, paretos[i]) << std::endl;
        } else {
            throw "File not created.";
        }
    }

    for(unsigned i = 0; i < numSolvers; i++) {
        std::string capturedDeltasFilename =
            argParser.getCmdOption("--captured-deltas-" + std::to_string(i));

        std::ofstream ofs;
        ofs.open(capturedDeltasFilename);

        if(ofs.is_open()) {
            for(unsigned j = 0;
                j < capturedParetos[i].size();
                j++) {
                ofs << capturedIterations[i][j] << ","
                    << capturedTimes[i][j] << "," 
                    << delta(optimalPareto, capturedParetos[i][j]) << std::endl;
            }
        } else {
            throw "File not created.";
        }
    }

    return 0;
}

