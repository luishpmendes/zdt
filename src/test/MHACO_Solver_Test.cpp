#include "../solver/mhaco/MHACO_Solver.hpp"

int main() {
    ZDT::MHACO_Solver solver;
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        individuals;

    for(unsigned zdt = 1; zdt <= 6; zdt++) {
        if(zdt == 5) {
            continue;
        }

        solver = ZDT::MHACO_Solver(zdt);

        solver.setTimeLimit(5.0);
        solver.setPopulationSize(200);

        assert(fabs(solver.getTimeLimit() - 5.00) <
                std::numeric_limits<double>::epsilon());
        assert(solver.getPopulationSize() == 200);
        assert(solver.getKer() == 63);
        assert(fabs(solver.getQ() - 1.0) <
                std::numeric_limits<double>::epsilon());
        assert(solver.getThreshold() == 1);
        assert(solver.getNGenMark() == 7);
        assert(solver.getEvalStop() == 0);
        assert(fabs(solver.getFocus() - 0.0) <
                std::numeric_limits<double>::epsilon());
        assert(!solver.getMemory());

        solver.solve();

        assert(solver.getSolvingTime() >= 0.0);
        assert(solver.getNumGenerations() > 0);

        individuals = solver.getIndividuals();

        assert(individuals.size() > 0);
        assert(individuals.size() <= solver.getMaxNumSolutions());

        for(const std::pair<std::vector<double>, std::vector<double>> &
                individual : individuals) {
            assert(individual.first.size() == 2);
            if(zdt == 1 || zdt == 2 || zdt == 3 || zdt == 4) {
                assert(individual.first.front() >= 0.0);
                assert(individual.first.front() <= 1.0);
            }
            if(zdt == 1 || zdt == 2 || zdt == 3) {
                assert(individual.second.size() == 30);
            } else if(zdt == 4 || zdt == 6) {
                assert(individual.second.size() == 10);
            }
            if(zdt == 1 || zdt == 2 || zdt == 3 || zdt == 6) {
                for(unsigned i = 0; i < individual.second.size(); i++) {
                    assert(individual.second[i] >= 0.0);
                    assert(individual.second[i] <= 1.0);
                }
            } else if(zdt == 4) {
                assert(individual.second.front() >= 0.0);
                assert(individual.second.front() <= 1.0);
                for(unsigned i = 1; i < individual.second.size(); i++) {
                    assert(individual.second[i] >= -5.0);
                    assert(individual.second[i] <= +5.0);
                }
            }
        }
        for(const std::pair<std::vector<double>, std::vector<double>> &
                individual1 : individuals) {
            for(const std::pair<std::vector<double>, std::vector<double>> &
                    individual2 : individuals) {
                assert(!(individual1.first.front() < individual2.first.front() 
                      && individual1.first.back() < individual2.first.back()));
            }
        }
    }

    return 0;
}

