#include "Solver.hpp"

namespace ZDT {
    double Solver::getElapsedTime(
            const std::chrono::steady_clock::time_point & startTime) {
        std::chrono::steady_clock::time_point currentTime =
            std::chrono::steady_clock::now();
        std::chrono::nanoseconds elapsedTime =
            std::chrono::duration_cast<std::chrono::nanoseconds> (
                    currentTime - startTime);
        return (double(elapsedTime.count()))/(double(1e9));
    }

    double Solver::getRemainingTime(
            const std::chrono::steady_clock::time_point & startTime, 
            double timeLimit) {
        return timeLimit - Solver::getElapsedTime(startTime);
    }

    Solver::Solver(unsigned zdt,
                   unsigned seed,
                   double timeLimit, 
                   unsigned maxNumSolutions,
                   bool captureEnabled,
                   unsigned populationSize) 
        : zdt(zdt),
          senses(2, BRKGA::Sense::MINIMIZE),
          seed(seed),
          rng(seed),
          timeLimit(timeLimit),
          maxNumSolutions(maxNumSolutions),
          captureEnabled(captureEnabled),
          populationSize(populationSize) {
        this->setTimeLimit(timeLimit);
        this->rng.discard(1000);
    }

    Solver::Solver(unsigned zdt)
        : Solver::Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    Solver::Solver() {}

    bool Solver::areTerminationCriteriaMet() const {
        return this->getElapsedTime() >= this->timeLimit;
    }

    bool Solver::updateIndividuals(
            const std::vector<
                std::pair<std::vector<double>,
                          std::vector<double>>> & newIndividuals) {
        bool result = false;

        if(newIndividuals.empty()) {
            return result;
        }

        auto nonDominatedNewIndividuals = 
            BRKGA::Population::nonDominatedSort<std::vector<double>>(
                    newIndividuals,
                    this->senses).front();

        for(const auto & newIndividual : nonDominatedNewIndividuals) {
            bool isDominatedOrEqual = false;

            for(auto it  = this->individuals.begin();
                     it != this->individuals.end();) {
                auto individual = *it;

                if((newIndividual.first.front() <= individual.first.front() &&
                    newIndividual.first.back() < individual.first.back()) || 
                   (newIndividual.first.front() < individual.first.front() &&
                    newIndividual.first.back() <= individual.first.back())) {
                    it = this->individuals.erase(it);
                } else {
                    if((individual.first.front() <= newIndividual.first.front()
                     && individual.first.back() < newIndividual.first.back()) || 
                       (individual.first.front() < newIndividual.first.front()
                     && individual.first.back() <= newIndividual.first.back())
                     || std::equal(individual.first.begin(),
                                   individual.first.end(),
                                   newIndividual.first.begin(),
                                   [](const double & a, const double & b) {
                                        return fabs(a - b) < 
                                            std::numeric_limits<double>::epsilon();
                                   })) {
                        isDominatedOrEqual = true;
                        break;
                    }

                    it++;
                }
            }

            if(!isDominatedOrEqual) {
                this->individuals.push_back(newIndividual);
                result = true;
            }
        }

        if(this->individuals.size() > this->maxNumSolutions) {
            BRKGA::Population::crowdingSort<std::vector<double>>(
                    this->individuals);
            this->individuals.resize(this->maxNumSolutions);
            result = true;
        }

        return result;
    }

    unsigned Solver::getZDT() const {
        return this->zdt;
    }

    void Solver::setZDT(unsigned zdt) {
        if (zdt >= 1 && zdt <= 6) {
            this->zdt = zdt;
        }
    }

    unsigned Solver::getSeed() const {
        return this->seed;
    }

    void Solver::setSeed(unsigned seed) {
        this->seed = seed;
    }

    double Solver::getTimeLimit() const {
        return this->timeLimit;
    }

    void Solver::setTimeLimit(double timeLimit) {
        if(timeLimit < 0.0) {
            this->timeLimit = 0.0;
        } else {
            this->timeLimit = timeLimit;
        }
    }

    unsigned Solver::getMaxNumSolutions() const {
        return this->maxNumSolutions;
    }

    void Solver::setMaxNumSolutions(unsigned maxNumSolutions) {
        this->maxNumSolutions = maxNumSolutions;
    }

    bool Solver::isCaptureEnabled() const {
        return this->captureEnabled;
    }

    void Solver::setCaptureEnabled(bool captureEnabled) {
        this->captureEnabled = captureEnabled;
    }

    unsigned Solver::getPopulationSize() const {
        return this->populationSize;
    }

    void Solver::setPopulationSize(unsigned populationSize) {
        this->populationSize = round((double(populationSize)/4.0))*4;
    }

    const std::vector<std::pair<std::vector<double>, std::vector<double>>> &
        Solver::getIndividuals() const {
        return this->individuals;
    }

    std::vector<std::vector<std::vector<double>>> Solver::getCapturedParetos() const {
        return this->capturedParetos;
    }

    std::vector<double> Solver::getCapturedTimes() const {
        return this->capturedTimes;
    }

    std::vector<unsigned> Solver::getCapturedIterations() const {
        return this->capturedIterations;
    }

    double Solver::getSolvingTime() const {
        return this->solvingTime;
    }

    double Solver::getElapsedTime() const {
        return Solver::getElapsedTime(this->startTime);
    }

    double Solver::getRemainingTime() const {
        return Solver::getRemainingTime(this->startTime, this->timeLimit);
    }

    unsigned Solver::getNumGenerations() const {
        return this->numGenerations;
    }

    void Solver::write(std::ostream & os) const {
        os << "Seed: " << this->seed << std::endl
           << "Time limit: " << this->timeLimit << std::endl
           << "Capture Enabled: " << this->captureEnabled << std::endl
           << "Maximum number of solutions: " << this->maxNumSolutions
           << std::endl
           << "Number of generations: " << this->numGenerations << std::endl
           << "Solutions obtained: " << this->individuals.size() << std::endl
           << "Solving time: " << this->solvingTime << std::endl
           << "Captured Paretos: " << this->capturedParetos.size()
           << std::endl
           << "Population size: " << this->populationSize << std::endl;
    }

    void Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if(ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void Solver::write() const {
        this->write(std::cout);
    }
}

