#include "NSGA2_Solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/nsga2.hpp>

namespace ZDT {
    NSGA2_Solver::NSGA2_Solver(unsigned zdt,
                               unsigned seed,
                               double timeLimit,
                               unsigned maxNumSolutions,
                               bool captureEnabled,
                               unsigned populationSize,
                               double crossoverProbability,
                               double crossoverDistribution,
                               double mutationProbability,
                               double mutationDistribution)
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions,
                         captureEnabled,
                         populationSize),
          crossoverProbability(crossoverProbability),
          crossoverDistribution(crossoverDistribution),
          mutationProbability(mutationProbability),
          mutationDistribution(mutationDistribution) {
        this->setCrossoverProbability(crossoverProbability);
        this->setCrossoverDistribution(crossoverDistribution);
        this->setMutationProbability(mutationProbability);
        this->setMutationDistribution(mutationDistribution);

        this->rng.discard(1000);
    }

    NSGA2_Solver::NSGA2_Solver(unsigned zdt)
        : NSGA2_Solver::NSGA2_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    NSGA2_Solver::NSGA2_Solver() : Solver::Solver() {}

    bool NSGA2_Solver::updateIndividuals(const pagmo::population & pop) {
        std::vector<std::pair<std::vector<double>, std::vector<double>>>
            newIndividuals(pop.size());

        for(unsigned i = 0; i < pop.size(); i++) {
            newIndividuals[i] = std::make_pair(pop.get_f()[i], pop.get_x()[i]);
        }

        return Solver::updateIndividuals(newIndividuals);
    }

    double NSGA2_Solver::getCrossoverProbability() const {
        return this->crossoverProbability;
    }

    void NSGA2_Solver::setCrossoverProbability(double crossoverProbability) {
        if(crossoverProbability < 0.00) {
            this->crossoverProbability = 0.00;
        } else if(crossoverProbability >= 1.00) {
            this->crossoverProbability = 0.99;
        } else {
            this->crossoverProbability = crossoverProbability;
        }
    }

    double NSGA2_Solver::getCrossoverDistribution() const {
        return this->crossoverDistribution;
    }

    void NSGA2_Solver::setCrossoverDistribution(double crossoverDistribution) {
        if(crossoverDistribution < 1.00) {
            this->crossoverDistribution = 1.00;
        } else if(crossoverDistribution >= 100.00) {
            this->crossoverDistribution = 99.99;
        } else {
            this->crossoverDistribution = crossoverDistribution;
        }
    }

    double NSGA2_Solver::getMutationProbability() const {
        return this->mutationProbability;
    }

    void NSGA2_Solver::setMutationProbability(double mutationProbability) {
        if(mutationProbability < 0.00) {
            this->mutationProbability = 0.00;
        } else if(mutationProbability > 1.00) {
            this->mutationProbability = 1.00;
        } else {
            this->mutationProbability = mutationProbability;
        }
    }

    double NSGA2_Solver::getMutationDistribution() const {
        return this->mutationDistribution;
    }

    void NSGA2_Solver::setMutationDistribution(double mutationDistribution) {
        if(mutationDistribution < 1.00) {
            this->mutationDistribution = 1.00;
        } else if(mutationDistribution >= 100.00) {
            this->mutationDistribution = 99.99;
        } else {
            this->mutationDistribution = mutationDistribution;
        }
    }

    void NSGA2_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        pagmo::problem prob{pagmo::zdt(this->zdt, param)};

        pagmo::algorithm algo{pagmo::nsga2(1, 
                                           this->crossoverProbability,
                                           this->crossoverDistribution,
                                           this->mutationProbability,
                                           this->mutationDistribution,
                                           this->seed)};

        std::vector<std::vector<double>> pareto;

        pagmo::population pop{prob, this->populationSize, this->seed};

        this->updateIndividuals(pop);

        this->numGenerations = 0;

        if(this->captureEnabled) {
            pareto.resize(this->individuals.size());
            std::transform(this->individuals.begin(),
                           this->individuals.end(),
                           pareto.begin(),
                           [](const auto & individual) {
                                return individual.first;
                           });
            this->capturedParetos.push_back(pareto);
            this->capturedTimes.push_back(this->getElapsedTime());
            this->capturedIterations.push_back(this->numGenerations);
        }

        while(!this->areTerminationCriteriaMet()) {
            this->numGenerations++;
            pop = algo.evolve(pop);

            if(this->updateIndividuals(pop) && this->captureEnabled) {
                pareto.resize(this->individuals.size());
                std::transform(this->individuals.begin(),
                               this->individuals.end(),
                               pareto.begin(),
                               [](const auto & individual) {
                                    return individual.first;
                               });
                this->capturedParetos.push_back(pareto);
                this->capturedTimes.push_back(this->getElapsedTime());
                this->capturedIterations.push_back(this->numGenerations);
            }
        }

        if(this->captureEnabled) {
            pareto.resize(this->individuals.size());
            std::transform(this->individuals.begin(),
                           this->individuals.end(),
                           pareto.begin(),
                           [](const auto & individual){
                                return individual.first;
                           });
            this->capturedParetos.push_back(pareto);
            this->capturedTimes.push_back(this->getElapsedTime());
            this->capturedIterations.push_back(this->numGenerations);
        }

        this->solvingTime = this->getElapsedTime();
    }

    void NSGA2_Solver::write(std::ostream & os) const {
        Solver::write(os);
        os << "Crossover probability: " << this->crossoverProbability 
           << std::endl
           << "Distribution index for crossover: " 
           << this->crossoverDistribution << std::endl
           << "Mutation probability: " << this->mutationProbability 
           << std::endl
           << "Distribution index for mutation: " 
           << this->mutationDistribution << std::endl;
    }

    void NSGA2_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void NSGA2_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void NSGA2_Solver::write() const {
        this->write(std::cout);
    }
}

