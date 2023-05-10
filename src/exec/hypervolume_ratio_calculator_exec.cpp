#include "utils/argument_parser.hpp"
#include <pagmo/utils/hypervolume.hpp>
#include <fstream>

int main(int argc, char * argv[]) {
    Argument_Parser arg_parser(argc, argv);

    if(arg_parser.option_exists("--reference-pareto")) {
        std::ifstream ifs;
        std::ofstream ofs;
        unsigned num_objectives = 2, num_solvers;
        double reference_hypervolume;
        std::vector<std::vector<double>> reference_pareto, time_snapshots;
        std::vector<std::vector<std::vector<double>>> paretos;
        std::vector<std::vector<unsigned>> iteration_snapshots;
        std::vector<std::vector<std::vector<std::vector<double>>>>
            best_solutions_snapshots;
        std::vector<double> reference_point(
            num_objectives, std::numeric_limits<double>::lowest());
        pagmo::hypervolume hv;

        std::string reference_pareto_filename = arg_parser.option_value("--reference-pareto");
        ifs.open(reference_pareto_filename);

        if(ifs.is_open()) {
            for(std::string line; std::getline(ifs, line);) {
                std::istringstream iss(line);
                std::vector<double> value(num_objectives, 0.0);

                for(unsigned j = 0; j < num_objectives; j++) {
                    iss >> value[j];

                    if(reference_point[j] < value[j]) {
                        reference_point[j] = value[j];
                    }
                }

                reference_pareto.push_back(value);
            }

            ifs.close();
        } else {
            throw std::runtime_error(
                "File " + reference_pareto_filename + " not found.");
        }

        for(num_solvers = 0;
            arg_parser.option_exists("--pareto-" +
                                        std::to_string(num_solvers)) ||
            arg_parser.option_exists("--best-solutions-snapshots-" +
                                        std::to_string(num_solvers)) ||
            arg_parser.option_exists("--hypervolume-ratio-" +
                                        std::to_string(num_solvers)) ||
            arg_parser.option_exists("--hypervolume-ratio-snapshots-" +
                                        std::to_string(num_solvers));
            num_solvers++) {}
        
        paretos.resize(num_solvers);
        iteration_snapshots.resize(num_solvers);
        time_snapshots.resize(num_solvers);
        best_solutions_snapshots.resize(num_solvers);

        for(unsigned i = 0; i < num_solvers; i++) {
            if(arg_parser.option_exists("--pareto-" + std::to_string(i))) {
                std::string pareto_filename =
                    arg_parser.option_value("--pareto-" + std::to_string(i));
                ifs.open(pareto_filename);

                if(ifs.is_open()) {
                    for(std::string line; std::getline(ifs, line);) {
                        std::istringstream iss(line);
                        std::vector<double> value(num_objectives, 0.0);

                        for(unsigned j = 0; j < num_objectives; j++) {
                            iss >> value[j];

                            if(reference_point[j] < value[j]) {
                                reference_point[j] = value[j];
                            }
                        }

                        paretos[i].push_back(value);
                    }

                    ifs.close();
                } else {
                    throw std::runtime_error(
                        "File " + pareto_filename + " not found.");
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

                                if(reference_point[j] < value[j]) {
                                    reference_point[j] = value[j];
                                }
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
            if(arg_parser.option_exists("--populations-snapshots-" +
                                        std::to_string(i))) {
                std::string populations_snapshots_filename =
                    arg_parser.option_value("--populations-snapshots-" +
                                            std::to_string(i));

                for(unsigned j = 0; ; j++) {
                    ifs.open(populations_snapshots_filename +
                                std::to_string(j) + ".txt");

                    if(ifs.is_open()) {
                        unsigned iteration;
                        double time;

                        ifs >> iteration >> time;

                        ifs.ignore();

                        for(std::string line; std::getline(ifs, line);) {
                            std::istringstream iss(line);
                            std::vector<double> value(num_objectives, 0.0);

                            for(unsigned j = 0; j < num_objectives; j++) {
                                iss >> value[j];

                                if(reference_point[j] < value[j]) {
                                    reference_point[j] = value[j];
                                }
                            }
                        }

                        ifs.close();
                    } else {
                        break;
                    }
                }
            }
        }

        hv = pagmo::hypervolume(reference_pareto);
        reference_hypervolume = hv.compute(reference_point);

        for(unsigned i = 0; i < num_solvers; i++) {
            std::string hypervolume_ratio_filename =
                arg_parser.option_value("--hypervolume-ratio-" +
                                        std::to_string(i));
            ofs.open(hypervolume_ratio_filename);
            
            if(ofs.is_open()) {
                hv = pagmo::hypervolume(paretos[i]);

                double hypervolume = hv.compute(reference_point);
                assert(hypervolume >= 0.0);
                assert(hypervolume <= reference_hypervolume);
                
                double hypervolume_ratio = hypervolume / reference_hypervolume;
                assert(hypervolume_ratio >= 0.0);
                assert(hypervolume_ratio <= 1.0);

                ofs << hypervolume_ratio << std::endl;

                if(ofs.eof() || ofs.fail() || ofs.bad()) {
                    throw std::runtime_error(
                        "Error writing file " +
                        hypervolume_ratio_filename + ".");
                }

                ofs.close();
            } else {
                throw std::runtime_error(
                    "File " + arg_parser.option_value("--hypervolume-ratio-" +
                    std::to_string(i)) + " not created.");
            }
        }

        for(unsigned i = 0; i < num_solvers; i++) {
            std::string hypervolume_ratio_snapshots_filename =
                arg_parser.option_value("--hypervolume-ratio-snapshots-" +
                                        std::to_string(i));
            ofs.open(hypervolume_ratio_snapshots_filename);

            if(ofs.is_open()) {
                for(unsigned j = 0;
                    j < best_solutions_snapshots[i].size();
                    j++) {
                    hv = pagmo::hypervolume(best_solutions_snapshots[i][j]);

                    double hypervolume = hv.compute(reference_point);
                    assert(hypervolume >= 0.0);
                    assert(hypervolume <= reference_hypervolume);

                    double hypervolume_ratio = hypervolume /
                        reference_hypervolume;
                    assert(hypervolume_ratio >= 0.0);
                    assert(hypervolume_ratio <= 1.0);

                    ofs << iteration_snapshots[i][j] << ","
                        << time_snapshots[i][j] << ","
                        << hypervolume_ratio << std::endl;
                    
                    if(ofs.eof() || ofs.fail() || ofs.bad()) {
                        throw std::runtime_error(
                            "Error writing file " +
                            hypervolume_ratio_snapshots_filename + ".");
                    }
                }

                ofs.close();
            } else {
                throw std::runtime_error(
                    "File " + arg_parser.option_value(
                        "--hypervolume-ratio-snapshots-" + std::to_string(i)) +
                        " not created.");
            }
        }
    } else {
        std::cerr << "./hypervolume_ratio_calculator_exec "
                  << "--reference-pareto <reference_pareto_filename> "
                  << "--pareto-i <pareto_filename> "
                  << "--best-solutions-snapshots-i <best_solutions_snapshots_filename> "
                  << "--populations-snapshots-i <populations_snapshots_filename> "
                  << "--hypervolume-ratio-i <hypervolume_filename> "
                  << "--hypervolume-ratio-snapshots-i <hypervolume_snapshots_filename> "
                  << std::endl;
    }

    return 0;
}
