#include "MHACO_Solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/maco.hpp>

namespace ZDT {
    MHACO_Solver::MHACO_Solver(unsigned zdt,
                               unsigned seed,
                               double timeLimit,
                               unsigned maxNumSolutions,
                               bool captureEnabled,
                               unsigned populationSize,
                               unsigned ker,
                               double q,
                               unsigned threshold,
                               unsigned nGenMark,
                               unsigned evalStop,
                               double focus,
                               bool memory)
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions,
                         captureEnabled,
                         populationSize),
          ker(ker),
          q(q),
          threshold(threshold),
          nGenMark(nGenMark),
          evalStop(evalStop),
          focus(focus),
          memory(memory) {
        this->setThreshold(threshold);
        this->setFocus(focus);

        this->rng.discard(1000);
    }

    MHACO_Solver::MHACO_Solver(unsigned zdt)
        : MHACO_Solver::MHACO_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    MHACO_Solver::MHACO_Solver() : Solver::Solver() {}

    bool MHACO_Solver::updateIndividuals(const pagmo::population & pop) {
        std::vector<std::pair<std::vector<double>, std::vector<double>>>
            newIndividuals(pop.size());

        for(unsigned i = 0; i < pop.size(); i++) {
            newIndividuals[i] = std::make_pair(pop.get_f()[i], pop.get_x()[i]);
        }

        return Solver::updateIndividuals(newIndividuals);
    }

    unsigned MHACO_Solver::getKer() const {
        return this->ker;
    }

    void MHACO_Solver::setKer(unsigned ker) {
        this->ker = ker;
    }

    double MHACO_Solver::getQ() const {
        return this->q;
    }

    void MHACO_Solver::setQ(double q) {
        this->q = q;
    }

    unsigned MHACO_Solver::getThreshold() const {
        return this->threshold;
    }

    void MHACO_Solver::setThreshold(unsigned threshold) {
        if(threshold < 1) {
            this->threshold = 1;
        } else if(this->memory && threshold > 1) {
            this->threshold = 1;
        } else {
            this->threshold = threshold;
        }
    }

    unsigned MHACO_Solver::getNGenMark() const {
        return this->nGenMark;
    }

    void MHACO_Solver::setNGenMark(unsigned nGenMark) {
        this->nGenMark = nGenMark;
    }

    unsigned MHACO_Solver::getEvalStop() const {
        return this->evalStop;
    }

    void MHACO_Solver::setEvalStop(unsigned evalStop) {
        this->evalStop = evalStop;
    }

    double MHACO_Solver::getFocus() const {
        return this->focus;
    }

    void MHACO_Solver::setFocus(double focus) {
        if(focus < 0.0) {
            this->focus = 0.0;
        } else {
            this->focus = focus;
        }
    }

    bool MHACO_Solver::getMemory() const {
        return this->memory;
    }

    void MHACO_Solver::setMemory(bool memory) {
        this->memory = memory;
    }

    void MHACO_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        pagmo::problem prob{pagmo::zdt(this->zdt, param)};

        pagmo::algorithm algo{pagmo::maco(1, 
                                          this->ker,
                                          this->q,
                                          this->threshold,
                                          this->nGenMark,
                                          this->evalStop,
                                          this->focus,
                                          this->memory,
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

    void MHACO_Solver::write(std::ostream & os) const {
        Solver::write(os);
        os << "Number of solutions stored in the solution archive: "
           << this->ker << std::endl
           << "Convergence speed: " << this->q << std::endl
           << "Threshold: " << this->threshold << std::endl
           << "nGenMark: " << this->nGenMark << std::endl
           << "EvalStop: " << this->evalStop << std::endl
           << "Focus: " << this->focus << std::endl
           << "Memory: " << this->memory << std::endl;
    }

    void MHACO_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void MHACO_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void MHACO_Solver::write() const {
        this->write(std::cout);
    }
}

