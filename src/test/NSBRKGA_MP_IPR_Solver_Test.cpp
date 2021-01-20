#include "../solver/nsbrkga_mp_ipr/NSBRKGA_MP_IPR_Solver.hpp"
#include <cassert>

int main() {
    ZDT::NSBRKGA_MP_IPR_Solver solver;
    std::vector<std::pair<std::vector<double>, std::vector<double>>>
        individuals;

    for(unsigned zdt = 1; zdt <= 6; zdt++) {
        if(zdt == 5) {
            continue;
        }

        solver = ZDT::NSBRKGA_MP_IPR_Solver(zdt);

        solver.setTimeLimit(5.0);
        solver.setPopulationSize(200);
        solver.setElitePercentage(0.2);
        solver.setMutantPercentage(0.2);
        solver.setNumTotalParents(2);
        solver.setNumEliteParents(1);

        assert(fabs(solver.getTimeLimit() - 5.0) <
                std::numeric_limits<double>::epsilon());
        assert(solver.getPopulationSize() == 200);
        assert(fabs(solver.getElitePercentage() - 0.2) <
                std::numeric_limits<double>::epsilon());
        assert(fabs(solver.getMutantPercentage() - 0.2) <
                std::numeric_limits<double>::epsilon());
        assert(solver.getNumTotalParents() == 2);
        assert(solver.getNumEliteParents() == 1);
        assert(solver.getBiasType() == BRKGA::BiasFunctionType::LOGINVERSE);
        assert(solver.getDiversityType() ==
                BRKGA::DiversityFunctionType::NONE);

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
            for(unsigned i = 0; i < individual.second.size(); i++) {
                assert(individual.second[i] >= 0.0);
                assert(individual.second[i] <= 1.0);
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

    std::cout << "NSBRGKA MP IPR Solver Test PASSED" << std::endl;

    return 0;
}

