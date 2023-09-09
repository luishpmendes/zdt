#include "solver/mhaco/mhaco_solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/maco.hpp>

namespace zdt {

MHACO_Solver::MHACO_Solver(unsigned zdt) : Solver::Solver(zdt) {}

MHACO_Solver::MHACO_Solver() = default;

void MHACO_Solver::solve() {
    this->start_time = std::chrono::steady_clock::now();

    pagmo::problem prob{pagmo::zdt(this->zdt, this->m)};

    pagmo::algorithm algo{pagmo::maco(1,
                                      this->ker,
                                      this->q,
                                      this->threshold,
                                      this->n_gen_mark,
                                      this->eval_stop,
                                      this->focus,
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

std::ostream & operator <<(std::ostream & os, const MHACO_Solver & solver) {
    os << static_cast<const Solver &>(solver)
       << "Number of solutions stored in the solution archive: " << solver.ker
       << std::endl
       << "Convergence speed: " << solver.q << std::endl
       << "Threshold: " << solver.threshold << std::endl
       << "nGenMark: " << solver.n_gen_mark << std::endl
       << "EvalStop: " << solver.eval_stop << std::endl
       << "Focus: " << solver.focus << std::endl
       << "Memory: " << solver.memory << std::endl;
    return os;
}

}
