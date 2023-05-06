#include "solver/nsbrkga/nsbrkga_solver.hpp"
#include <cassert>

int main() {
    zdt::NSBRKGA_Solver solver;
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        individuals;

    for(unsigned zdt = 1; zdt <= 6; zdt++) {
        solver = zdt::NSBRKGA_Solver(zdt);

        solver.set_seed(2351389233);
        solver.time_limit = 5.0;
        solver.iterations_limit = 1000;
        solver.max_num_solutions = 64;
        solver.population_size = 32;
        solver.max_num_snapshots = 16;

        assert((solver.seed = 2351389233));
        assert(fabs(solver.time_limit - 5.0) <
                std::numeric_limits<double>::epsilon());
        assert(solver.iterations_limit == 1000);
        assert(solver.max_num_solutions == 64);
        assert(solver.population_size == 32);
        assert(solver.max_num_snapshots == 16);
        assert(fabs(solver.min_elites_percentage - 0.10) <
                std::numeric_limits<double>::epsilon());
        assert(fabs(solver.max_elites_percentage - 0.50) <
                std::numeric_limits<double>::epsilon());
        assert(fabs(solver.mutation_probability - 0.01) <
                std::numeric_limits<double>::epsilon());
        assert(fabs(solver.mutation_distribution - 50.0) <
                std::numeric_limits<double>::epsilon());
        assert(solver.num_total_parents == 3);
        assert(solver.num_elite_parents == 2);
        assert(solver.bias_type == BRKGA::BiasFunctionType::LOGINVERSE);
        assert(solver.diversity_type ==
                BRKGA::DiversityFunctionType::AVERAGE_DISTANCE_TO_CENTROID);
        assert(solver.num_populations == 1);
        assert((solver.pr_number_pairs = 100));
        assert(fabs(solver.pr_min_dist - 0.15) <
                std::numeric_limits<double>::epsilon());
        assert(solver.pr_selection ==
                BRKGA::PathRelinking::Selection::BESTSOLUTION);
        assert(fabs(solver.pr_percentage - 0.30) <
                std::numeric_limits<double>::epsilon());
        assert(solver.pr_interval == 200);
        assert(solver.shake_interval == 200);
        assert(solver.shake_intensity == 10);
        assert(solver.reset_interval == 500);
        assert(fabs(solver.reset_intensity - 0.5) <
                std::numeric_limits<double>::epsilon());
        assert(solver.num_threads == 1);

        solver.solve();

        assert(solver.solving_time > 0);

        assert(solver.num_iterations > 0);
        assert(solver.num_iterations <= solver.iterations_limit);

        assert(solver.best_individuals.size() > 0);
        assert(solver.best_individuals.size() <= solver.max_num_solutions);

        assert(solver.num_snapshots > 0);
        assert(solver.num_snapshots <= solver.max_num_snapshots + 1);

        assert(solver.best_solutions_snapshots.size() == solver.num_snapshots);
        assert(solver.num_non_dominated_snapshots.size() == solver.num_snapshots);
        assert(solver.num_fronts_snapshots.size() == solver.num_snapshots);
        assert(solver.populations_snapshots.size() == solver.num_snapshots);

        for(const auto & s1 : solver.best_individuals) {
            assert(s1.first.size() == 2);

            // for(const auto & v : s1.first) {
                // assert(v >= 0.0); // what is the correct lower bound?
                // assert(v <= 1.0); // what is the correct upper bound?
            // }

            if (zdt != 5) {
                assert(s1.second.size() == solver.m);
            } else {
                assert(s1.second.size() == 30 + (solver.m - 1) * 5);
            }

            if (zdt != 4) {
                for(const auto & x : s1.second) {
                    assert(x >= 0.0);
                    assert(x <= 1.0);
                }
            } else {
                assert(s1.second.front() >= 0.0);
                assert(s1.second.front() <= 1.0);

                for(const auto & x : s1.second) {
                    assert(x >= -5.0);
                    assert(x <= +5.0);
                }
            }

            for(const auto & s2 : solver.best_individuals) {
                bool dominates = zdt::Solver::dominates(s1.first, s2.first),
                     is_dominated = zdt::Solver::dominates(s2.first, s1.first);
                assert(!dominates);
                assert(!is_dominated);
            }
        }

        for(const auto & snapshot : solver.best_solutions_snapshots) {
            assert(std::get<0>(snapshot) >= 0);
            assert(std::get<0>(snapshot) <= solver.num_iterations);
            assert(std::get<1>(snapshot) >= 0.0);
            assert(std::get<1>(snapshot) <= solver.solving_time);
            assert(std::get<2>(snapshot).size() > 0);
            assert(std::get<2>(snapshot).size() <= solver.max_num_solutions);

            for(const auto & s : std::get<2>(snapshot)) {
                assert(s.size() == 2);

                // for(const auto & v : s) {
                    // assert(v >= 0.0); // what is the correct lower bound?
                    // assert(v <= 1.0); // what is the correct upper bound?
                // }
            }
        }

        for(const auto & snapshot : solver.num_fronts_snapshots) {
            assert(std::get<0>(snapshot) >= 0);
            assert(std::get<0>(snapshot) <= solver.num_iterations);
            assert(std::get<1>(snapshot) >= 0.0);
            assert(std::get<1>(snapshot) <= solver.solving_time);
            assert(std::get<2>(snapshot).size() > 0);
            assert(std::get<2>(snapshot).size() <= solver.max_num_solutions);

            for(const unsigned & num_fronts : std::get<2>(snapshot)) {
                assert(num_fronts > 0);
                assert(num_fronts < solver.population_size);
            }
        }

        for(const auto & snapshot : solver.populations_snapshots) {
            assert(std::get<0>(snapshot) >= 0);
            assert(std::get<0>(snapshot) <= solver.num_iterations);
            assert(std::get<1>(snapshot) >= 0.0);
            assert(std::get<1>(snapshot) <= solver.solving_time);
            assert(std::get<2>(snapshot).size() > 0);
            assert(std::get<2>(snapshot).size() <= solver.max_num_solutions);

            for(const auto & population : std::get<2>(snapshot)) {
                assert(population.size() == solver.population_size);

                for(const auto & s : population) {
                    assert(s.size() == 2);

                    // for(const auto & v : s) {
                        // assert(v >= 0.0); // what is the correct lower bound?
                        // assert(v <= 1.0); // what is the correct upper bound?
                    // }
                }
            }
        }

        std::cout << solver << std::endl;

        std::cout << "Num non dominated snapshots: ";
        for(unsigned i = 0;
            i < solver.num_non_dominated_snapshots.size() - 1;
            i++) {
            std::cout << std::get<2>(solver.num_non_dominated_snapshots[i]).front()
                    << " ";
        }
        std::cout << std::get<2>(solver.num_non_dominated_snapshots.back()).front()
                << std::endl;

        std::cout << "Num fronts snapshots: ";
        for(unsigned i = 0; i < solver.num_fronts_snapshots.size() - 1; i++) {
            std::cout << std::get<2>(solver.num_fronts_snapshots[i]).front()
                    << " ";
        }
        std::cout << std::get<2>(solver.num_fronts_snapshots.back()).front()
                << std::endl << std::endl;
    }

    return 0;
}
