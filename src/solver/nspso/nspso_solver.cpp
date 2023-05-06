#include "solver/nspso/nspso_solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/nspso.hpp>

namespace zdt {

NSPSO_Solver::NSPSO_Solver(unsigned zdt) : Solver::Solver(zdt) {}

NSPSO_Solver::NSPSO_Solver() = default;

void NSPSO_Solver::solve() {
    this->start_time = std::chrono::steady_clock::now();

    pagmo::problem prob{pagmo::zdt(this->zdt, this->m)};

    pagmo::algorithm algo{pagmo::nspso(1,
                                       this->omega,
                                       this->c1,
                                       this->c2,
                                       this->chi,
                                       this->v_coeff,
                                       this->leader_selection_range,
                                       this->diversity_mechanism,
                                       this->memory,
                                       this->seed)};

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

std::ostream & operator <<(std::ostream & os, const NSPSO_Solver & solver) {
    os << static_cast<const Solver &>(solver)
       << "Omega: " << solver.omega << std::endl
       << "C1: " << solver.c1 << std::endl
       << "C2: " << solver.c2 << std::endl
       << "Chi: "  << solver.chi << std::endl
       << "vCoeff: " << solver.v_coeff << std::endl
       << "Leader selection range: " << solver.leader_selection_range
       << std::endl
       << "Diversity mechanism: " << solver.diversity_mechanism << std::endl
       << "Memory: " << solver.memory << std::endl;
    return os;
}

}
