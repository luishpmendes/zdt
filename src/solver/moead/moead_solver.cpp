#include "solver/moead/moead_solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/moead.hpp>

namespace zdt {

MOEAD_Solver::MOEAD_Solver(unsigned zdt) : Solver::Solver(zdt) {}

MOEAD_Solver::MOEAD_Solver() = default;

void MOEAD_Solver::solve() {
    this->start_time = std::chrono::steady_clock::now();

    pagmo::problem prob{pagmo::zdt(this->zdt, this->m)};

    pagmo::algorithm algo{pagmo::moead(1,
                                       this->weight_generation,
                                       this->decomposition,
                                       this->neighbours,
                                       this->cr,
                                       this->f,
                                       this->eta_m,
                                       this->realb,
                                       this->limit,
                                       this->preserve_diversity,
                                       this->seed)};

    if(this->max_num_snapshots > 0) {
        this->time_between_snapshots = this->time_limit /
            this->max_num_snapshots;
        this->iterations_between_snapshots = this->iterations_limit /
            this->max_num_snapshots;
    }

    pagmo::population pop{prob, this->population_size, this->seed};

    this->update_best_individuals(pop);

    if(this->max_num_snapshots > 0) {
        this->capture_snapshot(pop);
    }

    while(!this->are_termination_criteria_met()) {
        this->num_iterations++;
        pop = algo.evolve(pop);
        this->update_best_individuals(pop);

        if(this->max_num_snapshots > 0 &&
           this->num_snapshots < this->max_num_snapshots &&
          (this->elapsed_time() - this->time_last_snapshot >=
           this->time_between_snapshots ||
           this->num_iterations - this->iteration_last_snapshot >=
           this->iterations_between_snapshots)) {
            this->capture_snapshot(pop);
        }
    }

    if(this->max_num_snapshots > 0) {
        this->capture_snapshot(pop);
    }

    this->solving_time = this->elapsed_time();
}

std::ostream & operator <<(std::ostream & os, const MOEAD_Solver & solver) {
    os << static_cast<const Solver &>(solver)
       << "Method used to generate the weights: " << solver.weight_generation
       << std::endl
       << "Decomposition method: " << solver.decomposition << std::endl
       << "Size of the weight’s neighborhood: " << solver.neighbours
       << std::endl
       << "Crossover parameter in the Differential Evolution operator: "
       << solver.cr << std::endl
       << "Parameter for the Differential Evolution operator: " << solver.f
       << std::endl
       << "Chance that the neighbourhood is considered at each generation, "
       << "rather than the whole population: " << solver.realb << std::endl
       << "Maximum number of copies reinserted in the population: "
       << solver.limit << std::endl
       << "Diversity preservation mechanisms activated: "
       << solver.preserve_diversity << std::endl;
    return os;
}

}
