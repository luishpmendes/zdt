#include "solver/solver.hpp"
#include "utils/argument_parser.hpp"
#include <cassert>
#include <fstream>

static inline
double multiplicative_epsilon_indicator(
        const std::vector<BRKGA::Sense> & senses,
        const std::vector<std::vector<double>> & reference_front,
        const std::vector<std::vector<double>> & front) {
    double epsilon = 0.0, min_max_ratio = 0.0, max_ratio, ratio;

    for(unsigned i = 0; i < front.size(); i++) {
        for(unsigned j = 0; j < reference_front.size(); j++) {
            max_ratio = 0.0;

            for(unsigned k = 0; k < senses.size(); k++) {
                if(senses[k] == BRKGA::Sense::MINIMIZE) {
                    ratio = reference_front[j][k] / front[i][k];
                } else { // senses[k] == BRKGA::Sense::MAXIMIZE
                    ratio = front[i][k] / reference_front[j][k];
                }

                if(max_ratio < ratio) {
                    max_ratio = ratio;
                }
            }

            if(j == 0) {
                min_max_ratio = max_ratio;
            } else if (min_max_ratio > max_ratio) {
                min_max_ratio = max_ratio;
            }
        }

        if(i == 0) {
            epsilon = min_max_ratio;
        } else if(epsilon < min_max_ratio) {
            epsilon = min_max_ratio;
        }
    }

    return epsilon;
}

int main(int argc, char * argv[]) {
    Argument_Parser arg_parser(argc, argv);

    if(arg_parser.option_exists("--reference-pareto")) {
        std::ifstream ifs;
        std::ofstream ofs;
        unsigned num_objectives = 2, num_solvers;
        std::vector<std::vector<double>> reference_pareto, time_snapshots, multiplicative_epsilon_snapshots;
        std::vector<std::vector<std::vector<double>>> paretos;
        std::vector<std::vector<unsigned>> iteration_snapshots;
        std::vector<std::vector<std::vector<std::vector<double>>>>
            best_solutions_snapshots;
        std::vector<double> multiplicative_epsilons;

        ifs.open(arg_parser.option_value("--reference-pareto"));

        if(ifs.is_open()) {
            for(std::string line; std::getline(ifs, line);) {
                std::istringstream iss(line);
                std::vector<double> value(num_objectives, 0.0);

                for(unsigned j = 0; j < num_objectives; j++) {
                    iss >> value[j];
                }

                reference_pareto.push_back(value);
            }

            ifs.close();
        } else {
            throw std::runtime_error("File " +
                    arg_parser.option_value("--reference-pareto") +
                    " not found.");
        }

        for(num_solvers = 0;
            arg_parser.option_exists("--pareto-" +
                                     std::to_string(num_solvers)) ||
            arg_parser.option_exists("--best-solutions-snapshots-" +
                                     std::to_string(num_solvers)) ||
            arg_parser.option_exists("--multiplicative-epsilon-" +
                                     std::to_string(num_solvers)) ||
            arg_parser.option_exists("--multiplicative-epsilon-snapshots-" +
                                     std::to_string(num_solvers));
            num_solvers++) {}

        paretos.resize(num_solvers);
        iteration_snapshots.resize(num_solvers);
        time_snapshots.resize(num_solvers);
        best_solutions_snapshots.resize(num_solvers);
        multiplicative_epsilons.resize(num_solvers);
        multiplicative_epsilon_snapshots.resize(num_solvers, std::vector<double>());
        multiplicative_epsilon_snapshots.assign(num_solvers, std::vector<double>());

        for(unsigned i = 0; i < num_solvers; i++) {
            if(arg_parser.option_exists("--pareto-" + std::to_string(i))) {
                ifs.open(arg_parser.option_value("--pareto-" +
                                                 std::to_string(i)));

                if(ifs.is_open()) {
                    for(std::string line; std::getline(ifs, line);) {
                        std::istringstream iss(line);
                        std::vector<double> value(num_objectives, 0.0);

                        for(unsigned j = 0; j < num_objectives; j++) {
                            iss >> value[j];
                        }

                        paretos[i].push_back(value);
                    }

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

                        iteration_snapshots[i].push_back(iteration);
                        time_snapshots[i].push_back(time);
                        best_solutions_snapshots[i].emplace_back();

                        ifs.ignore();

                        for(std::string line; std::getline(ifs, line);) {
                            std::istringstream iss(line);
                            std::vector<double> value(num_objectives, 0.0);

                            for(unsigned j = 0; j < num_objectives; j++) {
                                iss >> value[j];
                            }

                            best_solutions_snapshots[i].back().push_back(value);
                        }

                        ifs.close();
                    } else {
                        break;
                    }
                }
            }
        }

        for(unsigned i = 0; i < num_solvers; i++) {
            double multiplicative_epsilon = multiplicative_epsilon_indicator(
                    zdt::Solver::senses, reference_pareto, paretos[i]);

            assert(multiplicative_epsilon >= 0.0);
            assert(multiplicative_epsilon <= 1.0);

            multiplicative_epsilons[i] = multiplicative_epsilon;
        }

        for(unsigned i = 0; i < num_solvers; i++) {
            for(unsigned j = 0;
                j < best_solutions_snapshots[i].size();
                j++) {
                double multiplicative_epsilon
                        = multiplicative_epsilon_indicator(
                                zdt::Solver::senses,
                                reference_pareto,
                                best_solutions_snapshots[i][j]);

                assert(multiplicative_epsilon >= 0.0);
                assert(multiplicative_epsilon >= 0.0);

                multiplicative_epsilon_snapshots[i].push_back(multiplicative_epsilon);
            }
        }

        for(unsigned i = 0; i < num_solvers; i++) {
            ofs.open(arg_parser.option_value("--multiplicative-epsilon-" +
                                             std::to_string(i)));

            if(ofs.is_open()) {
                ofs << multiplicative_epsilons[i] << std::endl;

                if(ofs.eof() || ofs.fail() || ofs.bad()) {
                    throw std::runtime_error("Error writing file " +
                            arg_parser.option_value("--multiplicative-epsilon-" +
                                std::to_string(i)) + ".");
                }

                ofs.close();
            } else {
                throw std::runtime_error("File " +
                        arg_parser.option_value("--multiplicative-epsilon-" +
                            std::to_string(i)) + " not created.");
            }
        }

        for(unsigned i = 0; i < num_solvers; i++) {
            ofs.open(arg_parser.option_value("--multiplicative-epsilon-snapshots-" +
                                             std::to_string(i)));

            if(ofs.is_open()) {
                for(unsigned j = 0;
                    j < best_solutions_snapshots[i].size();
                    j++) {
                    ofs << iteration_snapshots[i][j] << ","
                        << time_snapshots[i][j] << ","
                        << multiplicative_epsilon_snapshots[i][j] << std::endl;

                    if(ofs.eof() || ofs.fail() || ofs.bad()) {
                        throw std::runtime_error("Error writing file " +
                                arg_parser.option_value(
                                    "--multiplicative-epsilon-snapshots-" +
                                    std::to_string(i)) + ".");
                    }
                }

                ofs.close();
            } else {
                throw std::runtime_error("File " +
                        arg_parser.option_value("--multiplicative-epsilon-snapshots-" +
                            std::to_string(i)) + " not created.");
            }
        }
    } else {
        std::cerr << "./multiplicative_epsilon_calculator_exec "
                  << "--reference-pareto <reference_pareto_filename> "
                  << "--pareto-i <pareto_filename> "
                  << "--best-solutions-snapshots-i <best_solutions_snapshots_filename> "
                  << "--multiplicative-epsilon-i <multiplicative_epsilon_filename> "
                  << "--multiplicative-epsilon-snapshots-i <multiplicative_epsilon_snapshots_filename> "
                  << std::endl;
    }

    return 0;
}
