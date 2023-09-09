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

    if(this->max_num_snapshots > this->num_snapshots + 1) {
        this->capture_snapshot(pop);

        if (this->time_limit > 0.0) {
            this->time_snapshot_factor = std::pow(this->time_limit / this->time_last_snapshot, 1.0 / (this->max_num_snapshots - this->num_snapshots));
            this->time_next_snapshot = this->time_last_snapshot * this->time_snapshot_factor;
        } else {
            this->time_next_snapshot = 0.0;
            this->time_snapshot_factor = 1.0;
        }

        if (this->iterations_limit > 0) {
            this->iteration_snapshot_factor = std::pow(this->iterations_limit / (this->iteration_last_snapshot + 1.0), 1.0 / (this->max_num_snapshots - this->num_snapshots));
            this->iteration_next_snapshot = unsigned(std::round(double(this->iteration_last_snapshot) * this->iteration_snapshot_factor));
        } else {
            this->iteration_next_snapshot = 0;
            this->iteration_snapshot_factor = 1.0;
        }
    } else {
        this->time_next_snapshot = 0.0;
        this->iteration_next_snapshot = 0;
        this->time_snapshot_factor = 1.0;
        this->iteration_snapshot_factor = 1.0;
    }

    while(!this->are_termination_criteria_met()) {
        this->num_iterations++;
        pop = algo.evolve(pop);
        this->update_best_individuals(pop);

        if(this->max_num_snapshots > this->num_snapshots + 1) {
            if (this->iteration_next_snapshot > 0 && 
                this->num_iterations >= this->iteration_next_snapshot) {
                this->capture_snapshot(pop);

                if (this->time_limit > 0.0) {
                    this->time_next_snapshot = this->time_last_snapshot * this->time_snapshot_factor;
                    this->time_snapshot_factor = std::pow(this->time_limit / this->time_last_snapshot, 1.0 / (this->max_num_snapshots - this->num_snapshots));
                } else {
                    this->time_next_snapshot = 0.0;
                    this->time_snapshot_factor = 1.0;
                }

                if (this->iterations_limit > 0) {
                    this->iteration_next_snapshot = unsigned(std::round(double(this->iteration_last_snapshot) * this->iteration_snapshot_factor));
                    this->iteration_snapshot_factor = std::pow(this->iterations_limit / this->iteration_last_snapshot, 1.0 / (this->max_num_snapshots - this->num_snapshots));
                } else {
                    this->iteration_next_snapshot = 0;
                    this->iteration_snapshot_factor = 1.0;
                }
            } else if (this->time_next_snapshot > 0.0 && 
                this->elapsed_time() >= this->time_next_snapshot) {
                this->capture_snapshot(pop);

                if (this->time_limit > 0.0) {
                    this->time_next_snapshot = this->time_last_snapshot * this->time_snapshot_factor;
                    this->time_snapshot_factor = std::pow(this->time_limit / this->time_last_snapshot, 1.0 / (this->max_num_snapshots - this->num_snapshots));
                } else {
                    this->time_next_snapshot = 0.0;
                    this->time_snapshot_factor = 1.0;
                }

                if (this->iterations_limit > 0) {
                    this->iteration_next_snapshot = unsigned(std::round(double(this->iteration_last_snapshot) * this->iteration_snapshot_factor));
                    this->iteration_snapshot_factor = std::pow(this->iterations_limit / this->iteration_last_snapshot, 1.0 / (this->max_num_snapshots - this->num_snapshots));
                } else {
                    this->iteration_next_snapshot = 0;
                    this->iteration_snapshot_factor = 1.0;
                }
            }
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
