#include "MOEAD_Solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/moead.hpp>

namespace ZDT {
    MOEAD_Solver::MOEAD_Solver(unsigned zdt,
                               unsigned seed,
                               double timeLimit,
                               unsigned maxNumSolutions,
                               bool captureEnabled,
                               unsigned populationSize,
                               std::string weightGeneration,
                               std::string decomposition,
                               unsigned neighbours,
                               double cr,
                               double f,
                               double etaM,
                               double realb,
                               unsigned limit,
                               bool preserveDiversity)
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions,
                         captureEnabled,
                         populationSize),
          weightGeneration(weightGeneration),
          decomposition(decomposition),
          neighbours(neighbours),
          cr(cr),
          f(f),
          etaM(etaM),
          realb(realb),
          limit(limit),
          preserveDiversity(preserveDiversity) {
        this->setWeightGeneration(weightGeneration);
        this->setDecomposition(decomposition);
        this->setNeighbours(neighbours);
        this->setCR(cr);
        this->setF(f);
        this->setEtaM(etaM);
        this->setRealb(realb);

        this->rng.discard(1000);
    }

    MOEAD_Solver::MOEAD_Solver(unsigned zdt)
        : MOEAD_Solver::MOEAD_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    MOEAD_Solver::MOEAD_Solver() : Solver::Solver() {}

    bool MOEAD_Solver::updateIndividuals(const pagmo::population & pop) {
        std::vector<std::pair<std::vector<double>, std::vector<double>>>
            newIndividuals(pop.size());

        for(unsigned i = 0; i < pop.size(); i++) {
            newIndividuals[i] = std::make_pair(pop.get_f()[i], pop.get_x()[i]);
        }

        return Solver::updateIndividuals(newIndividuals);
    }

    std::string MOEAD_Solver::getWeightGeneration() const {
        return this->weightGeneration;
    }

    void MOEAD_Solver::setWeightGeneration(
            const std::string & weightGeneration) {
        if(weightGeneration == "grid" 
                || weightGeneration == "low discrepancy" 
                || weightGeneration == "random") {
            this->weightGeneration = weightGeneration;
        } else {
            this->weightGeneration = "grid";
        }
    }

    std::string MOEAD_Solver::getDecomposition() const {
        return this->decomposition;
    }

    void MOEAD_Solver::setDecomposition(const std::string & decomposition) {
        if(decomposition == "weighted" 
                || decomposition == "tchebycheff" 
                || decomposition == "bi") {
            this->decomposition = decomposition;
        } else {
            this->decomposition = "tchebycheff";
        }
    }

    unsigned MOEAD_Solver::getNeighbours() const {
        return this->neighbours;
    }

    void MOEAD_Solver::setNeighbours(unsigned neighbours) {
        if(neighbours < 2) {
            this->neighbours = 2;
        } else {
            this->neighbours = neighbours;
        }
    }

    double MOEAD_Solver::getCR() const {
        return this->cr;
    }

    void MOEAD_Solver::setCR(double cr) {
        if(cr < 0.0) {
            this->cr = 0.0;
        } else if(cr > 1.0) {
            this->cr = 1.0;
        } else {
            this->cr = cr;
        }
    }

    double MOEAD_Solver::getF() const {
        return this->f;
    }

    void MOEAD_Solver::setF(double f) {
        if(f < 0.0) {
            this->f = 0.0;
        } else if(f > 1.0) {
            this->f = 1.0;
        } else {
            this->f = f;
        }
    }

    double MOEAD_Solver::getEtaM() const {
        return this->etaM;
    }

    void MOEAD_Solver::setEtaM(double etaM) {
        if(etaM < 0.0) {
            this->etaM = 0.0;
        } else {
            this->etaM = etaM;
        }
    }

    double MOEAD_Solver::getRealb() const {
        return this->realb;
    }

    void MOEAD_Solver::setRealb(double realb) {
        if(realb < 0.0) {
            this->realb = 0.0;
        } else if(realb > 1.0) {
            this->realb = 1.0;
        } else {
            this->realb = realb;
        }
    }

    unsigned MOEAD_Solver::getLimit() const {
        return this->limit;
    }

    void MOEAD_Solver::setLimit(unsigned limit) {
        this->limit = limit;
    }

    bool MOEAD_Solver::getPreserveDiversity() const {
        return this->preserveDiversity;
    }

    void MOEAD_Solver::setPreserveDiversity(bool preserveDiversity) {
        this->preserveDiversity = preserveDiversity;
    }

    void MOEAD_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        pagmo::problem prob{pagmo::zdt(this->zdt, param)};

        pagmo::algorithm algo{pagmo::moead(1, 
                                           this->weightGeneration,
                                           this->decomposition,
                                           this->neighbours,
                                           this->cr,
                                           this->f,
                                           this->etaM,
                                           this->realb,
                                           this->limit,
                                           this->preserveDiversity,
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

    void MOEAD_Solver::write(std::ostream & os) const {
        Solver::write(os);
        os << "Method used to generate the weights: " << this->weightGeneration 
           << std::endl
           << "Decomposition method: " << this->decomposition << std::endl
           << "Size of the weight’s neighborhood: " << this->neighbours 
           << std::endl
           << "Crossover parameter in the Differential Evolution operator: " 
           << this->cr << std::endl
           << "Parameter for the Differential Evolution operator: " << this->f
           << std::endl
           << "Chance that the neighbourhood is considered at each generation,"
           << "rather than the whole population: " << this->realb << std::endl
           << "Maximum number of copies reinserted in the population: "
           << this->limit << std::endl
           << "Diversity preservation mechanisms activated: "
           << this->preserveDiversity << std::endl;
    }

    void MOEAD_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void MOEAD_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void MOEAD_Solver::write() const {
        this->write(std::cout);
    }
}

