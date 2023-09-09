#include "solver/moead/moead_solver.hpp"

int main() {
    zdt::MOEAD_Solver solver;

    for(unsigned zdt = 1; zdt <= 6; zdt++) {
        solver = zdt::MOEAD_Solver(zdt);

        solver.set_seed(2351389233);
        solver.time_limit = 5.0;
        solver.iterations_limit = 100;
        solver.max_num_solutions = 64;
        solver.population_size = 36;
        solver.max_num_snapshots = 16;  

        assert((solver.seed = 2351389233));
        assert(fabs(solver.time_limit - 5.0) <
                std::numeric_limits<double>::epsilon());
        assert(solver.iterations_limit == 100);
        assert(solver.max_num_solutions == 64);
        assert(solver.population_size == 36);
        assert(solver.max_num_snapshots == 16);
        assert(solver.weight_generation == "random");
        assert(solver.decomposition == "tchebycheff");
        assert(solver.neighbours == 20);
        assert(fabs(solver.cr - 1.0) < std::numeric_limits<double>::epsilon());
        assert(fabs(solver.f - 0.5) < std::numeric_limits<double>::epsilon());
        assert(fabs(solver.eta_m - 20.0) < std::numeric_limits<double>::epsilon());
        assert(fabs(solver.realb - 0.9) < std::numeric_limits<double>::epsilon());
        assert(solver.limit == 2);
        assert(solver.preserve_diversity);

        solver.solve();

        assert(solver.solving_time > 0);

        assert(solver.num_iterations > 0);
        assert(solver.num_iterations <= solver.iterations_limit);

        assert(solver.best_individuals.size() > 0);
        assert(solver.best_individuals.size() <= solver.max_num_solutions);

        assert(solver.num_snapshots == solver.max_num_snapshots);

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
            std::cout << "(" 
                    << std::get<0>(solver.num_non_dominated_snapshots[i])
                    << ", "
                    << std::get<1>(solver.num_non_dominated_snapshots[i])
                    << ", "
                    << std::accumulate(
                std::get<2>(solver.num_non_dominated_snapshots[i]).begin(),
                std::get<2>(solver.num_non_dominated_snapshots[i]).end(),
                0) / std::get<2>(solver.num_non_dominated_snapshots[i]).size()
                    << "), ";
        }
        std::cout << "("
                << std::get<0>(solver.num_non_dominated_snapshots.back())
                << ", "
                << std::get<1>(solver.num_non_dominated_snapshots.back())
                << ", "
                << std::accumulate(
            std::get<2>(solver.num_non_dominated_snapshots.back()).begin(),
            std::get<2>(solver.num_non_dominated_snapshots.back()).end(),
            0) / std::get<2>(solver.num_non_dominated_snapshots.back()).size()
                << ")" << std::endl;

        std::cout << "Num fronts snapshots: ";
        for(unsigned i = 0; i < solver.num_fronts_snapshots.size() - 1; i++) {
            std::cout << "("
                    << std::get<0>(solver.num_fronts_snapshots[i])
                    << ", "
                    << std::get<1>(solver.num_fronts_snapshots[i])
                    << ", "
                    << std::accumulate(
                std::get<2>(solver.num_fronts_snapshots[i]).begin(),
                std::get<2>(solver.num_fronts_snapshots[i]).end(),
                0) / std::get<2>(solver.num_fronts_snapshots[i]).size()
                    << "), ";
        }
        std::cout << "("
                << std::get<0>(solver.num_fronts_snapshots.back())
                << ", "
                << std::get<1>(solver.num_fronts_snapshots.back())
                << ", "
                << std::accumulate(
            std::get<2>(solver.num_fronts_snapshots.back()).begin(),
            std::get<2>(solver.num_fronts_snapshots.back()).end(),
            0) / std::get<2>(solver.num_fronts_snapshots.back()).size()
                << ")" << std::endl;
    }

    std::cout << std::endl << "MOEAD Solver Test PASSED" << std::endl;

    return 0;
}
