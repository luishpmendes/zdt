#include "../utils/ArgumentParser.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

int main(int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);
    std::vector<std::vector<unsigned>> capturedIterations;
    std::vector<std::vector<double>> capturedTimes, capturedMetrics;
    std::vector<std::pair<double, unsigned>> metric;
    double mean = 0.0, std = 0.0;

    for(unsigned i = 0; ; i++) {
        if(!argParser.cmdOptionExists("--captured-metrics-"
                                      + std::to_string(i))) {
            break;
        }
        capturedIterations.emplace_back();
        capturedTimes.emplace_back();
        capturedMetrics.emplace_back();
        std::string capturedMetricsFilename =
            argParser.getCmdOption("--captured-metrics-" + std::to_string(i));
        std::ifstream ifs;
        ifs.open(capturedMetricsFilename);

        if(ifs.is_open()) {
            for(std::string line; std::getline(ifs, line);) {
                std::istringstream iss(line);
                std::string element;
                std::getline(iss, element, ',');
                capturedIterations.back().push_back(stoul(element));
                std::getline(iss, element, ',');
                capturedTimes.back().push_back(stod(element));
                std::getline(iss, element, ',');
                capturedMetrics.back().push_back(stod(element));
            }
        } else {
            throw "File not found.";
        }
    }

    for(unsigned i = 0; i < capturedMetrics.size(); i++) {
        metric.push_back(std::make_pair(i, capturedMetrics[i].back()));
        mean += capturedMetrics[i].back();
    }

    mean /= (double) capturedMetrics.size();

    for(unsigned i = 0; i < capturedMetrics.size(); i++) {
        std += (capturedMetrics[i].back() - mean) 
             * (capturedMetrics[i].back() - mean);
    }

    std = sqrt(std / ((double) capturedMetrics.size()));

    std::nth_element(metric.begin(),
                     metric.begin() + metric.size()/2,
                     metric.end());

    unsigned medianIndex = metric[metric.size() / 2].second;

    if(argParser.cmdOptionExists("--median-captured-metrics")) {
        std::string medianCapturedMetricsFilename =
            argParser.getCmdOption("--median-captured-metrics");

        std::ofstream ofs;
        ofs.open(medianCapturedMetricsFilename);

        if(ofs.is_open()) {
            for(unsigned i = 0; i < capturedMetrics[medianIndex].size(); i++) {
                ofs << capturedIterations[medianIndex][i] << ","
                    << capturedTimes[medianIndex][i] << ","
                    << capturedMetrics[medianIndex][i] << std::endl;
            }
        } else {
            throw "File not created.";
        }
    }

    if(argParser.cmdOptionExists("--mean-std-metric")) {
        std::string meanStdMetricFilename =
            argParser.getCmdOption("--mean-std-metric");

        std::ofstream ofs;
        ofs.open(meanStdMetricFilename);

        if(ofs.is_open()) {
            ofs << mean << "," << std << std::endl;
        } else {
            throw "File not created.";
        }
    }

    return 0;
}

