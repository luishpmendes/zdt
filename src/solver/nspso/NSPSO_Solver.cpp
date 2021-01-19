#include "NSPSO_Solver.hpp"
#include <pagmo/problem.hpp>
#include <pagmo/problems/zdt.hpp>
#include <pagmo/algorithms/nspso.hpp>

namespace ZDT {
    NSPSO_Solver::NSPSO_Solver(unsigned zdt,
                               unsigned seed,
                               double timeLimit,
                               unsigned maxNumSolutions,
                               bool captureEnabled,
                               unsigned populationSize,
                               double omega,
                               double c1,
                               double c2,
                               double chi,
                               double vCoeff,
                               unsigned leaderSelectionRange,
                               std::string diversityMechanism,
                               bool memory)
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions,
                         captureEnabled,
                         populationSize),
          omega(omega),
          c1(c1),
          c2(c2),
          chi(chi),
          vCoeff(vCoeff),
          leaderSelectionRange(leaderSelectionRange),
          diversityMechanism(diversityMechanism),
          memory(memory) {
        this->setOmega(omega);
        this->setC1(c1);
        this->setC2(c2);
        this->setChi(chi);
        this->setVCoeff(vCoeff);
        this->setLeaderSelectionRange(leaderSelectionRange);
        this->setDiversityMechanism(diversityMechanism);
    }

    NSPSO_Solver::NSPSO_Solver(unsigned zdt)
        : NSPSO_Solver::NSPSO_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    NSPSO_Solver::NSPSO_Solver() : Solver::Solver() {}

    bool NSPSO_Solver::updateIndividuals(const pagmo::population & pop) {
        std::vector<std::pair<std::vector<double>, std::vector<double>>>
            individuals(pop.size());

        for(unsigned i = 0; i < pop.size(); i++) {
            individuals[i] = std::make_pair(pop.get_f()[i], pop.get_x()[i]);
        }

        return Solver::updateIndividuals(individuals);
    }

    double NSPSO_Solver::getOmega() const {
        return this->omega;
    }

    void NSPSO_Solver::setOmega(double omega) {
        if(omega < 0.0) {
            this->omega = 0.0;
        } else if(omega > 1.0) {
            this->omega = 1.0;
        } else {
            this->omega = omega;
        }
    }

    double NSPSO_Solver::getC1() const {
        return this->c1;
    }

    void NSPSO_Solver::setC1(double c1) {
        if(c1 <= 0.00) {
            this->c1 = 0.01;
        } else {
            this->c1 = c1;
        }
    }

    double NSPSO_Solver::getC2() const {
        return this->c2;
    }

    void NSPSO_Solver::setC2(double c2) {
        if(c2 <= 0.00) {
            this->c2 = 0.01;
        } else {
            this->c2 = c2;
        }
    }

    double NSPSO_Solver::getChi() const {
        return this->chi;
    }

    void NSPSO_Solver::setChi(double chi) {
        if(chi <= 0.00) {
            this->chi = 0.01;
        } else {
            this->chi = chi;
        }
    }

    double NSPSO_Solver::getVCoeff() const {
        return this->vCoeff;
    }

    void NSPSO_Solver::setVCoeff(double vCoeff) {
        if(vCoeff <= 0.00) {
            this->vCoeff = 0.01;
        } else if(vCoeff > 1.00) {
            this->vCoeff = 1.00;
        } else {
            this->vCoeff = vCoeff;
        }
    }

    unsigned NSPSO_Solver::getLeaderSelectionRange() const {
        return this->leaderSelectionRange;
    }

    void NSPSO_Solver::setLeaderSelectionRange(unsigned leaderSelectionRange) {
        if(leaderSelectionRange <= 0) {
            this->leaderSelectionRange = 1;
        } else if(leaderSelectionRange > 100) {
            this->leaderSelectionRange = 100;
        } else {
            this->leaderSelectionRange = leaderSelectionRange;
        }
    }

    std::string NSPSO_Solver::getDiversityMechanism() const {
        return this->diversityMechanism;
    }

    void NSPSO_Solver::setDiversityMechanism(std::string diversityMechanism) {
        if(diversityMechanism == "crowding distance" 
                || diversityMechanism == "niche count" 
                || diversityMechanism == "max min") {
            this->diversityMechanism = diversityMechanism;
        } else {
            this->diversityMechanism = "crowding distance";
        }
    }

    bool NSPSO_Solver::getMemory() const {
        return this->memory;
    }

    void NSPSO_Solver::setMemory(bool memory) {
        this->memory = memory;
    }

    void NSPSO_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        pagmo::problem prob{pagmo::zdt(this->zdt, param)};

        pagmo::algorithm algo{pagmo::nspso(1, 
                                           this->omega,
                                           this->c1,
                                           this->c2,
                                           this->chi,
                                           this->vCoeff,
                                           this->leaderSelectionRange,
                                           this->diversityMechanism,
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
                           [](const auto & individual) {
                                return individual.first;
                           });
            this->capturedParetos.push_back(pareto);
            this->capturedTimes.push_back(this->getElapsedTime());
            this->capturedIterations.push_back(this->numGenerations);
        }

        this->solvingTime = this->getElapsedTime();
    }

    void NSPSO_Solver::write(std::ostream & os) const {
        Solver::write(os);
        os << "Omega: " << this->omega << std::endl
           << "C1: " << this->c1 << std::endl
           << "C2: " << this->c2 << std::endl
           << "Chi: "  << this->chi << std::endl
           << "vCoeff: " << this->vCoeff << std::endl
           << "Leader selection range: " << this->leaderSelectionRange 
           << std::endl
           << "Diversity mechanism: " << this->diversityMechanism << std::endl
           << "Memory: " << this->memory << std::endl;
    }

    void NSPSO_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void NSPSO_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void NSPSO_Solver::write() const {
        this->write(std::cout);
    }
}

