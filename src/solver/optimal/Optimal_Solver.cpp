#include "Optimal_Solver.hpp"
#include <pagmo/problems/zdt.hpp>

namespace ZDT {
    Optimal_Solver::Optimal_Solver(unsigned zdt,
                                   unsigned seed,
                                   double timeLimit,
                                   unsigned maxNumSolutions)
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions) {
        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        this->prob = pagmo::zdt(this->zdt, param);

        this->rng.discard(1000);
    }

    Optimal_Solver::Optimal_Solver(unsigned zdt)
        : Optimal_Solver::Optimal_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    Optimal_Solver::Optimal_Solver() : Solver::Solver() {}

    void Optimal_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        std::vector<double> x, f;

        if(this->zdt == 1 || this->zdt == 2 || this->zdt == 3) {
            x = std::vector<double>(30, 0.0);
        } else if (this->zdt == 4 || this->zdt == 6) {
            x = std::vector<double>(10, 0.0);
        }

        double delta = 1.0/((double) (this->maxNumSolutions - 1.0));

        std::vector<std::pair<std::vector<double>, std::vector<double>>> 
            individuals;

        for(unsigned i = 0; i < this->maxNumSolutions; i++) {
            f = this->prob.fitness(x);

            individuals.push_back(std::make_pair(f, x));

            x[0] += delta;
        }

        this->updateIndividuals(individuals);

        this->solvingTime = this->getElapsedTime();
    }

    void Optimal_Solver::write(std::ostream & os) const {
        Solver::write(os);
    }

    void Optimal_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void Optimal_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void Optimal_Solver::write() const {
        this->write(std::cout);
    }
}

