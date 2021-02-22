#include "../utils/ArgumentParser.hpp"
#include "../solver/mhaco/MHACO_Solver.hpp"

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
        unsigned ker = 63;
        double q = 1.0;
        unsigned threshold = 1;
        unsigned nGenMark = 7;
        unsigned evalStop = 0;
        double focus = 0.0;
        bool memory = false;

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

        if(argParser.cmdOptionExists("--ker")) {
            ker = std::stoul(argParser.getCmdOption("--ker"));
        }

        if(argParser.cmdOptionExists("--q")) {
            q = std::stod(argParser.getCmdOption("--q"));
        }

        if(argParser.cmdOptionExists("--threshold")) {
            threshold = std::stoul(argParser.getCmdOption("--threshold"));
        }

        if(argParser.cmdOptionExists("--n-gen-mark")) {
            nGenMark = std::stoul(argParser.getCmdOption("--n-gen-mark"));
        }

        if(argParser.cmdOptionExists("--eval-stop")) {
            evalStop = std::stoul(argParser.getCmdOption("--eval-stop"));
        }

        if(argParser.cmdOptionExists("--focus")) {
            focus = std::stod(argParser.getCmdOption("--focus"));
        }

        memory = argParser.cmdOptionExists("--memory");

        ZDT::MHACO_Solver solver(zdt,
                                 seed,
                                 timeLimit,
                                 maxNumSolutions,
                                 captureEnabled,
                                 populationSize,
                                 ker,
                                 q,
                                 threshold,
                                 nGenMark,
                                 evalStop,
                                 focus,
                                 memory);

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
        std::cerr << "./MHACO_Solver_Exec "
                  << "--zdt <zdt> "
                  << "--seed <seed> "
                  << "--time-limit <timeLimit> "
                  << "--max-num-solutions <maxNumSolutions> "
                  << "--capture-enabled "
                  << "--population-size <populationSize> "
                  << "--ker <ker> "
                  << "--q <q> "
                  << "--threshold <threshold> "
                  << "--n-gen-mark <nGenMark> "
                  << "--eval-stop <evalStop> "
                  << "--focus <focus> "
                  << "--memory <memory> "
                  << "--statistics <statisticsFilename> "
                  << "--solutions <solutionsFilename> "
                  << "--pareto <paretoFilename> "
                  << "--captured-paretos <capturedParetosFilename> "
                  << std::endl;
    }

    return 0;
}

