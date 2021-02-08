// https://doi.org/10.1109/CEC.2006.1688406

#include "../utils/ArgumentParser.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

double d(const std::vector<double> & x,
         const std::vector<std::vector<double>> & Sstar) {
    double result = std::numeric_limits<double>::max();

    for(const std::vector<double> & y : Sstar) {
        double curr = 0;

        for(unsigned i = 0; i < x.size() && i < y.size(); i++) {
            curr += (x[i] - y[i]) * (x[i] * y[i]);
        }

        curr = sqrt(curr);

        if(result > curr) {
            result = curr;
        }
    }

    return result;
}

double convergence(const std::vector<std::vector<double>> & S,
                   const std::vector<std::vector<double>> & Sstar) {
    double result = 0.0;

    for(const std::vector<double> & x : S) {
        result += d(x, Sstar);
    }

    result /= S.size();

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
        if(!argParser.cmdOptionExists("--convergence-" + std::to_string(i))) {
            break;
        }

        std::string convergenceFilename =
            argParser.getCmdOption("--convergence-" + std::to_string(i));

        std::ofstream ofs;
        ofs.open(convergenceFilename);

        if(ofs.is_open()) {
            ofs << convergence(paretos[i], optimalPareto) << std::endl;
        } else {
            throw "File not created.";
        }
    }

    for(unsigned i = 0; i < numSolvers; i++) {
        std::string capturedConvergencesFilename =
            argParser.getCmdOption("--captured-convergences-"
                                   + std::to_string(i));

        std::ofstream ofs;
        ofs.open(capturedConvergencesFilename);

        if(ofs.is_open()) {
            for(unsigned j = 0;
                j < capturedParetos[i].size();
                j++) {
                ofs << capturedIterations[i][j] << ","
                    << capturedTimes[i][j] << "," 
                    << convergence(capturedParetos[i][j], optimalPareto)
                    << std::endl;
            }
        } else {
            throw "File not created.";
        }
    }

    return 0;
}

