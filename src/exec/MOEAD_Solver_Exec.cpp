#include "../utils/ArgumentParser.hpp"
#include "../solver/moead/MOEAD_Solver.hpp"

int main (int argc, char * argv[]) {
    ArgumentParser argParser (argc, argv);

    if(argParser.cmdOptionExists("--zdt")) {
        unsigned zdt = std::stoul(argParser.getCmdOption("--zdt"));
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        double timeLimit = 3600.00;
        unsigned maxNumSolutions = std::numeric_limits<unsigned>::max();
        bool captureEnabled = false;
        unsigned populationSize = 200;
        std::string weightGeneration = "grid";
        std::string decomposition = "tchebycheff";
        unsigned neighbours = 20;
        double cr = 1.0;
        double f = 0.5;
        double etaM = 20.0;
        double realb = 0.9;
        unsigned limit = 2;
        bool preserveDiversity = false;

        if(argParser.cmdOptionExists("--seed")) {
            seed = std::stoul(argParser.getCmdOption("--seed"));
        }

        if(argParser.cmdOptionExists("--time-limit")) {
            timeLimit = std::stod(argParser.getCmdOption("--time-limit"));
        }

        if(argParser.cmdOptionExists("--max-num-solutions")) {
            maxNumSolutions =
                std::stoul(argParser.getCmdOption("--max-num-solutions"));
        }

        captureEnabled = argParser.cmdOptionExists("--capture-enabled");

        if(argParser.cmdOptionExists("--population-size")) {
            populationSize =
                std::stoul(argParser.getCmdOption("--population-size"));
        }

        if(argParser.cmdOptionExists("--weight-generation")) {
            weightGeneration =
                argParser.getCmdOption("--crossover-probability");
        }

        if(argParser.cmdOptionExists("--decomposition")) {
            decomposition = argParser.getCmdOption("--decomposition");
        }

        if(argParser.cmdOptionExists("--neighbours")) {
            neighbours = std::stoul(argParser.getCmdOption("--neighbours"));
        }

        if(argParser.cmdOptionExists("--cr")) {
            cr = std::stod(argParser.getCmdOption("--cr"));
        }

        if(argParser.cmdOptionExists("--f")) {
            f = std::stod(argParser.getCmdOption("--f"));
        }

        if(argParser.cmdOptionExists("--eta-m")) {
            etaM = std::stod(argParser.getCmdOption("--eta-m"));
        }

        if(argParser.cmdOptionExists("--realb")) {
            realb = std::stod(argParser.getCmdOption("--realb"));
        }

        if(argParser.cmdOptionExists("--limit")) {
            limit = std::stoul(argParser.getCmdOption("--limit"));
        }

        preserveDiversity = argParser.cmdOptionExists("--preserve-diversity");

        ZDT::MOEAD_Solver solver(zdt,
                                 seed,
                                 timeLimit,
                                 maxNumSolutions,
                                 captureEnabled,
                                 populationSize,
                                 weightGeneration,
                                 decomposition,
                                 neighbours,
                                 cr,
                                 f,
                                 etaM,
                                 realb,
                                 limit,
                                 preserveDiversity);

        solver.solve();

        if(argParser.cmdOptionExists("--statistics")) {
            solver.write(argParser.getCmdOption("--statistics"));
        }

        if(argParser.cmdOptionExists("--solutions")) {
            std::string solutionsFilename =
                argParser.getCmdOption("--solutions");

            std::ofstream ofs;
            ofs.open(solutionsFilename);

            if(ofs.is_open()) {
                std::vector<std::pair<std::vector<double>, std::vector<double>>>
                    individuals = solver.getIndividuals();

                for(unsigned i = 0; i < individuals.size(); i++) {
                    for(unsigned j = 0; 
                        j < individuals[i].second.size() - 1;
                        j++) {
                        ofs << individuals[i].second[j] << " ";
                    }

                    ofs << individuals[i].second.back() << std::endl;
                }
            } else {
                throw "File not created.";
            }
        }

        if(argParser.cmdOptionExists("--pareto")) {
            std::string paretoFilename = argParser.getCmdOption("--pareto");

            std::ofstream ofs;
            ofs.open(paretoFilename);

            if(ofs.is_open()) {
                std::vector<std::pair<std::vector<double>, std::vector<double>>>
                    individuals = solver.getIndividuals();

                for(unsigned i = 0; i < individuals.size(); i++) {
                    for(unsigned j = 0; 
                        j < individuals[i].first.size() - 1;
                        j++) {
                        ofs << individuals[i].first[j] << " ";
                    }

                    ofs << individuals[i].first.back() << std::endl;
                }
            } else {
                throw "File not created.";
            }
        }

        if(argParser.cmdOptionExists("--captured-paretos")) {
            std::string capturedParetosFilename =
                argParser.getCmdOption("--captured-paretos");
            std::vector<std::vector<std::vector<double>>> capturedParetos =
                solver.getCapturedParetos();
            std::vector<double> capturedTimes = solver.getCapturedTimes();
            std::vector<unsigned> capturedIterations =
                solver.getCapturedIterations();

            for(unsigned i = 0; i < capturedParetos.size(); i++) {
                std::ofstream ofs;
                ofs.open(capturedParetosFilename + std::to_string(i) + ".txt");

                if(ofs.is_open()) {
                    ofs << capturedIterations[i] << " " 
                        << capturedTimes[i] << std::endl;
                    for(unsigned j = 0; j < capturedParetos[i].size(); j++) {
                        for(unsigned k = 0; 
                            k < capturedParetos[i][j].size() - 1;
                            k++) {
                            ofs << capturedParetos[i][j][k] << " ";
                        }

                        ofs << capturedParetos[i][j].back() << std::endl;
                    }
                } else {
                    throw "File not created.";
                }
            }
        }
    } else {
        std::cerr << "./NSGA2_Solver_Exec "
                  << "--zdt <zdt> "
                  << "--seed <seed> "
                  << "--time-limit <timeLimit> "
                  << "--max-num-solutions <maxNumSolutions> "
                  << "--capture-enabled "
                  << "--population-size <populationSize> "
                  << "--weight-generation <weightGeneration> "
                  << "--decomposition <decomposition> "
                  << "--neighbours <neighbours> "
                  << "--cr <cr> "
                  << "--f <f> "
                  << "--eta-m <etaM> "
                  << "--realb <realb> "
                  << "--limit <limit> "
                  << "--preserve-diversity"
                  << "--statistics <statisticsFilename> "
                  << "--solutions <solutionsFilename> "
                  << "--pareto <paretoFilename> "
                  << "--captured-paretos <capturedParetosFilename> "
                  << std::endl;
    }

    return 0;
}

