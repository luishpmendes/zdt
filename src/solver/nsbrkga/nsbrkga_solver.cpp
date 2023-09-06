#include "solver/nsbrkga/nsbrkga_solver.hpp"

namespace zdt {

NSBRKGA_Solver::NSBRKGA_Solver(unsigned zdt) : Solver::Solver(zdt) {}

NSBRKGA_Solver::NSBRKGA_Solver() = default;

void NSBRKGA_Solver::capture_snapshot(
        const NSBRKGA::NSBRKGA<Decoder> & algorithm) {
    double time_snapshot = this->elapsed_time();

    this->best_solutions_snapshots.emplace_back(std::make_tuple(
                this->num_iterations,
                time_snapshot,
                std::vector<std::vector<double>>(
                    this->best_individuals.size())));
    for(std::size_t i = 0; i < this->best_individuals.size(); i++) {
        std::get<2>(this->best_solutions_snapshots.back())[i] =
            this->best_individuals[i].first;
    }

    this->num_non_dominated.resize(this->num_populations);
    this->num_fronts.resize(this->num_populations);
    this->num_elites.resize(this->num_populations);

    for(unsigned i = 0; i < this->num_populations; i++) {
        this->num_non_dominated[i] =
            algorithm.getCurrentPopulation(i).num_non_dominated;
        this->num_fronts[i] = algorithm.getCurrentPopulation(i).num_fronts;
        this->num_elites[i] = algorithm.getCurrentPopulation(i).num_elites;
    }

    this->num_non_dominated_snapshots.push_back(std::make_tuple(
                this->num_iterations,
                time_snapshot,
                this->num_non_dominated));

    this->num_fronts_snapshots.push_back(std::make_tuple(this->num_iterations,
                                                         time_snapshot,
                                                         this->num_fronts));

    this->populations_snapshots.emplace_back(std::make_tuple(
                this->num_iterations,
                time_snapshot,
                std::vector<std::vector<std::vector<double>>>()));
    for(unsigned i = 0; i < this->num_populations; i++) {
        std::get<2>(this->populations_snapshots.back()).emplace_back();
        for(unsigned j = 0; j < this->population_size; j++) {
            std::get<2>(this->populations_snapshots.back()).back().push_back(
                    algorithm.getCurrentPopulation(i).getFitness(j));
        }
    }

    this->num_elites_snapshots.push_back(std::make_tuple(this->num_iterations,
                                                         time_snapshot,
                                                         this->num_elites));

    this->time_last_snapshot = time_snapshot;
    this->iteration_last_snapshot = this->num_iterations;
    this->num_snapshots++;
}

void NSBRKGA_Solver::solve() {
    this->start_time = std::chrono::steady_clock::now();

    Decoder decoder(this->zdt, this->m);

    NSBRKGA::NsbrkgaParams params;
    params.num_incumbent_solutions = this->max_num_solutions;
    params.population_size = this->population_size;
    params.min_elites_percentage = this->min_elites_percentage;
    params.max_elites_percentage = this->max_elites_percentage;
    params.mutation_probability = this->mutation_probability;
    params.mutation_distribution = this->mutation_distribution;
    params.total_parents = this->num_total_parents;
    params.num_elite_parents = this->num_elite_parents;
    params.bias_type = this->bias_type;
    params.diversity_type = this->diversity_type;
    params.num_independent_populations = this->num_populations;
    params.pr_type = NSBRKGA::PathRelinking::Type::BINARY_SEARCH;

    unsigned chromosome_size = this->m;
    
    if(this->zdt == 5) {
        chromosome_size = 30 + (m - 1) * 5;
    }

    NSBRKGA::NSBRKGA algorithm(decoder,
                               this->senses,
                               this->seed,
                               chromosome_size,
                               params,
                               this->num_threads);

    algorithm.initialize();

    this->update_best_individuals(algorithm.getIncumbentSolutions());

    std::shared_ptr<NSBRKGA::DistanceFunctionBase> dist_func(
            new NSBRKGA::EuclideanDistance());

    if(this->max_num_snapshots > 0) {
        if (this->time_limit > 0.0) {
            this->time_between_snapshots = this->time_limit / 
                    (std::pow(2.0, this->max_num_snapshots) - 1.0);
        } else {
            this->time_between_snapshots = 0.0;
        }

        if (this->iterations_limit > 0) {
            this->iterations_between_snapshots = this->iterations_limit / 
                    (std::pow(2, this->max_num_snapshots) - 1);
        } else {
            this->iterations_between_snapshots = 0;
        }

        this->capture_snapshot(algorithm);
    }

    while(!this->are_termination_criteria_met()) {
        this->num_iterations++;

        if(algorithm.evolve()) {
            this->last_update_time = this->elapsed_time();

            auto update_offset = this->num_iterations -
                                 this->last_update_generation;
            this->last_update_generation = this->num_iterations;

            if(this->large_offset < update_offset) {
                this->large_offset = update_offset;
            }

            this->update_best_individuals(algorithm.getIncumbentSolutions());
        }

        if(this->max_num_snapshots > 0 &&
            this->num_snapshots < this->max_num_snapshots) {
            if ((this->time_between_snapshots > 0.0 &&
                this->elapsed_time() - this->time_last_snapshot
                    >= this->time_between_snapshots) ||
                (this->iterations_between_snapshots > 0 &&
                       this->num_iterations - this->iteration_last_snapshot
                           >= this->iterations_between_snapshots)) {
                this->capture_snapshot(algorithm);
                this->time_between_snapshots *= 2.0;
                this->iterations_between_snapshots *= 2;
            }
        }

        unsigned generations_without_improvement = this->num_iterations -
            this->last_update_generation;

        if(this->large_offset < generations_without_improvement) {
            this->large_offset = generations_without_improvement;
        }

        if (this->exchange_interval > 0 && this->num_iterations > 0 &&
                (this->num_iterations % this->exchange_interval == 0)) {
            algorithm.exchangeElite(this->num_exchange_individuals);
        }

        if(this->pr_interval > 0 && this->num_iterations > 0 &&
                (this->num_iterations % this->pr_interval == 0)) {
            this->num_path_relink_calls++;
            const auto pr_start_time = std::chrono::steady_clock::now();
            auto result = algorithm.pathRelink(
                    params.pr_type,
                    dist_func,
                    this->time_limit - this->elapsed_time());

            const auto pr_time = Solver::elapsed_time(pr_start_time);
            this->path_relink_time += pr_time;

            switch(result) {
                case NSBRKGA::PathRelinking::PathRelinkingResult::ELITE_IMPROVEMENT: {
                    this->num_elite_improvments++;
                }
                case NSBRKGA::PathRelinking::PathRelinkingResult::BEST_IMPROVEMENT: {
                    this->num_best_improvements++;
                    this->last_update_time = this->elapsed_time();

                    auto update_offset = this->num_iterations -
                                         this->last_update_generation;
                    this->last_update_generation = this->num_iterations;

                    if(this->large_offset < update_offset) {
                        this->large_offset = update_offset;
                    }

                    this->update_best_individuals(
                            algorithm.getIncumbentSolutions());
                    break;
                }

                default: {
                    break;
                }
            }
        }

        if(this->shake_interval > 0 && generations_without_improvement > 0 &&
                (generations_without_improvement % this->shake_interval == 0)) {
            this->num_shakings++;
            algorithm.shake(this->shake_intensity);
        }

        if(this->reset_interval > 0 && generations_without_improvement > 0 &&
                (generations_without_improvement % this->reset_interval) == 0) {
            this->num_resets++;
            algorithm.reset(this->reset_intensity);
        }
    }

    if(this->max_num_snapshots > 0) {
        this->capture_snapshot(algorithm);
    }

    this->solving_time = this->elapsed_time();
}

std::ostream & operator <<(std::ostream & os, const NSBRKGA_Solver & solver) {
    os << static_cast<const Solver &>(solver)
       << "Minimum percentage of individuals to become the elite set: "
       << solver.min_elites_percentage << std::endl
       << "Maximum percentage of individuals to become the elite set: "
       << solver.max_elites_percentage << std::endl
       << "Mutation probability: " << solver.mutation_probability << std::endl
       << "Mutation distribution: " << solver.mutation_distribution << std::endl
       << "Number of total parents for mating: " << solver.num_total_parents
       << std::endl
       << "Number of elite parents for mating: " << solver.num_elite_parents
       << std::endl
       << "Type of bias that will be used: "
       << EnumIO<NSBRKGA::BiasFunctionType>::enum_names().at(
               static_cast<int>(solver.bias_type)) << std::endl
       << "Type of diversity that will be used: "
       << EnumIO<NSBRKGA::DiversityFunctionType>::enum_names().at(
               static_cast<int>(solver.diversity_type)) << std::endl
       << "Number of independent parallel populations: "
       << solver.num_populations << std::endl
       << "Interval at which the elite solutions are exchanged between populations: "
       << solver.exchange_interval << std::endl
       << "Number of elite individuals to be exchanged between populations: "
       << solver.num_exchange_individuals << std::endl
       << "Interval at which the path relink is applied: "
       << solver.pr_interval << std::endl
       << "Interval at which the populations are shaken: "
       << solver.shake_interval << std::endl
       << "The intensity of the shaking: "
       << solver.shake_intensity << std::endl
       << "Interval at which the populations are reset: "
       << solver.reset_interval << std::endl
       << "The intensity of the reset: "
       << solver.reset_intensity << std::endl
       << "Number of threads to be used during parallel decoding: "
       << solver.num_threads << std::endl
       << "Last update generation: " << solver.last_update_generation
       << std::endl
       << "Last update time: " << solver.last_update_time << std::endl
       << "Largest number of generations between improvements: "
       << solver.large_offset << std::endl
       << "Total path relink time: " << solver.path_relink_time << std::endl
       << "Total path relink calls: " << solver.num_path_relink_calls
       << std::endl
       << "Improvements in the elite set: " << solver.num_elite_improvments
       << std::endl
       << "Best individual improvements: " << solver.num_best_improvements
       << std::endl
       << "Total shakings calls: " << solver.num_shakings << std::endl
       << "Total resets calls: " << solver.num_resets << std::endl;
    return os;
}

}
