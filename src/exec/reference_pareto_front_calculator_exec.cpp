#include "solver/solver.hpp"
#include "utils/argument_parser.hpp"
#include <sstream>
#include <fstream>

int main(int argc, char * argv[]) {
    Argument_Parser arg_parser(argc, argv);
    std::ifstream ifs;
    unsigned num_objectives = 2, num_solvers;
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
            reference_pareto,
            pareto,
            best_solutions_snapshot;

    for(num_solvers = 0;
        arg_parser.option_exists("--pareto-" +
                                    std::to_string(num_solvers)) ||
        arg_parser.option_exists("--best-solutions-snapshots-" +
                                    std::to_string(num_solvers));
        num_solvers++) {}

    for(unsigned i = 0; i < num_solvers; i++) {
        if(arg_parser.option_exists("--pareto-" + std::to_string(i))) {
            ifs.open(arg_parser.option_value("--pareto-" + std::to_string(i)));

            if(ifs.is_open()) {
                pareto.clear();

                for(std::string line; std::getline(ifs, line);) {
                    std::istringstream iss(line);
                    std::vector<double> value(num_objectives, 0.0);

                    for(unsigned j = 0; j < num_objectives; j++) {
                        iss >> value[j];
                    }

                    pareto.push_back(std::make_pair(value, std::vector<double>()));
                }

                zdt::Solver::update_best_individuals(reference_pareto,
                                                     pareto,
                                                     zdt::Solver::senses);

                ifs.close();
            } else {
                throw std::runtime_error("File " +
                                         arg_parser.option_value("--pareto-" +
                                         std::to_string(i)) + " not found.");
            }
        }
    }

    for(unsigned i = 0; i < num_solvers; i++) {
        if(arg_parser.option_exists("--best-solutions-snapshots-" +
                                    std::to_string(i))) {
            std::string best_solutions_snapshots_filename =
                arg_parser.option_value("--best-solutions-snapshots-" +
                                        std::to_string(i));

            for(unsigned j = 0; ; j++) {
                ifs.open(best_solutions_snapshots_filename +
                         std::to_string(j) + ".txt");

                if(ifs.is_open()) {
                    unsigned iteration;
                    double time;

                    ifs >> iteration >> time;

                    best_solutions_snapshot.clear();

                    ifs.ignore();

                    for(std::string line; std::getline(ifs, line);) {
                        std::istringstream iss(line);
                        std::vector<double> value(num_objectives, 0.0);

                        for(unsigned j = 0; j < num_objectives; j++) {
                            iss >> value[j];
                        }

                        best_solutions_snapshot.push_back(
                            std::make_pair(value, std::vector<double>()));
                    }

                    zdt::Solver::update_best_individuals(
                        reference_pareto,
                        best_solutions_snapshot,
                        zdt::Solver::senses);

                    ifs.close();
                } else {
                    break;
                }
            }
        }
    }

    if(arg_parser.option_exists("--reference-pareto")) {
        std::ofstream ofs;
        ofs.open(arg_parser.option_value("--reference-pareto"));

        if(ofs.is_open()) {
            for(const std::pair<std::vector<double>, std::vector<double>> & solution : reference_pareto) {
                for(unsigned i = 0; i < solution.first.size() - 1; i++) {
                    ofs << solution.first[i] << " ";
                }

                ofs << solution.first.back() << std::endl;

                if(ofs.eof() || ofs.fail() || ofs.bad()) {
                    throw std::runtime_error(
                        "Error writing file " +
                        arg_parser.option_value("--reference-pareto") + ".");
                }
            }

            ofs.close();
        } else {
            throw std::runtime_error(
                "File " + arg_parser.option_value("--reference-pareto") +
                " not created.");
        }
    }

    return 0;
}
