#include "NSBRKGA_MP_IPR_Solver.hpp"
#include "Decoder.hpp"

namespace ZDT {
    NSBRKGA_MP_IPR_Solver::NSBRKGA_MP_IPR_Solver(
            unsigned zdt,
            unsigned seed,
            double timeLimit,
            unsigned maxNumSolutions,
            bool captureEnabled,
            unsigned populationSize,
            double elitePercentage,
            double mutantPercentage,
            unsigned numTotalParents,
            unsigned numEliteParents,
            BRKGA::BiasFunctionType biasType,
            BRKGA::DiversityFunctionType diversityType,
            unsigned numPopulations,
            double prPercentagePairs,
            double prMinDist,
            BRKGA::PathRelinking::Selection prSelection,
            double prPercentage,
            unsigned prInterval,
            unsigned shakeInterval,
            unsigned resetInterval,
            unsigned numThreads) 
        : Solver::Solver(zdt,
                         seed,
                         timeLimit,
                         maxNumSolutions,
                         captureEnabled,
                         populationSize),
          biasType(biasType),
          diversityType(diversityType),
          prSelection(prSelection),
          prInterval(prInterval),
          shakeInterval(shakeInterval),
          resetInterval(resetInterval) {
        this->setElitePercentage(elitePercentage);
        this->setMutantPercentage(mutantPercentage);
        this->setNumTotalParents(numTotalParents);
        this->setNumEliteParents(numEliteParents);
        this->setNumPopulations(numPopulations);
        this->setPrPercentagePairs(prPercentagePairs);
        this->setPrMinDist(prMinDist);
        this->setPrPercentage(prPercentage);
        this->setNumThreads(numThreads);
    }

    NSBRKGA_MP_IPR_Solver::NSBRKGA_MP_IPR_Solver(unsigned zdt) 
        : NSBRKGA_MP_IPR_Solver::NSBRKGA_MP_IPR_Solver(
                zdt,
                std::chrono::system_clock::now().time_since_epoch().count()) {}

    NSBRKGA_MP_IPR_Solver::NSBRKGA_MP_IPR_Solver() : Solver::Solver() {}

    double NSBRKGA_MP_IPR_Solver::getElitePercentage() const {
        return this->elitePercentage;
    }

    void NSBRKGA_MP_IPR_Solver::setElitePercentage(double elitePercentage) {
        if(elitePercentage < std::numeric_limits<double>::epsilon()) {
            this->elitePercentage = 0.01;
        } else if(elitePercentage > 1.00) {
            this->elitePercentage = 1.00;
        } else {
            this->elitePercentage = elitePercentage;
        }
    }

    double NSBRKGA_MP_IPR_Solver::getMutantPercentage() const {
        return this->mutantPercentage;
    }

    void NSBRKGA_MP_IPR_Solver::setMutantPercentage(double mutantPercentage) {
        if(mutantPercentage < 0.00) {
            this->mutantPercentage = 0.00;
        } else if(mutantPercentage > 1.00) {
            this->mutantPercentage = 1.00;
        } else {
            this->mutantPercentage = mutantPercentage;
        }
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumTotalParents() const {
        return this->numTotalParents;
    }

    void NSBRKGA_MP_IPR_Solver::setNumTotalParents(unsigned numTotalParents) {
        if(numTotalParents < 2) {
            this->numTotalParents = 2;
        } else if(numTotalParents > this->populationSize) {
            this->numTotalParents = this->populationSize;
        } else {
            this->numTotalParents = numTotalParents;
        }
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumEliteParents() const {
        return this->numEliteParents;
    }

    void NSBRKGA_MP_IPR_Solver::setNumEliteParents(unsigned numEliteParents) {
        if(numEliteParents < 1) {
            this->numEliteParents = 1;
        } else if(numEliteParents > this->numTotalParents) {
            this->numEliteParents = this->numTotalParents;
        } else {
            this->numEliteParents = numEliteParents;
        }
    }

    BRKGA::BiasFunctionType NSBRKGA_MP_IPR_Solver::getBiasType() const {
        return this->biasType;
    }

    void NSBRKGA_MP_IPR_Solver::setBiasType(
            const BRKGA::BiasFunctionType & biasType) {
        this->biasType = biasType;
    }

    BRKGA::DiversityFunctionType NSBRKGA_MP_IPR_Solver::getDiversityType() 
        const {
        return this->diversityType;
    }

    void NSBRKGA_MP_IPR_Solver::setDiversityType(
            const BRKGA::DiversityFunctionType & diversityType) {
        this->diversityType = diversityType;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumPopulations() const {
        return this->numPopulations;
    }

    void NSBRKGA_MP_IPR_Solver::setNumPopulations(unsigned numPopulations) {
        if(numPopulations < 1) {
            this->numPopulations = 1;
        } else {
            this->numPopulations = numPopulations;
        }
    }

    double NSBRKGA_MP_IPR_Solver::getPrPercentagePairs() const {
        return this->prPercentagePairs;
    }

    void NSBRKGA_MP_IPR_Solver::setPrPercentagePairs(double prPercentagePairs) {
        if(prPercentagePairs < 0.00) {
            this->prPercentagePairs = 0.00;
        } else if(prPercentagePairs > 1.00) {
            this->prPercentagePairs = 1.00;
        } else {
            this->prPercentagePairs = prPercentagePairs;
        }
    }

    double NSBRKGA_MP_IPR_Solver::getPrMinDist() const {
        return this->prMinDist;
    }

    void NSBRKGA_MP_IPR_Solver::setPrMinDist(double prMinDist) {
        if(prMinDist < 0.0) {
            this->prMinDist = 0.0;
        } else {
            this->prMinDist = prMinDist;
        }
    }

    BRKGA::PathRelinking::Selection NSBRKGA_MP_IPR_Solver::getPrSelection() const {
        return this->prSelection;
    }

    void NSBRKGA_MP_IPR_Solver::setPrSelection(
            BRKGA::PathRelinking::Selection prSelection) {
        this->prSelection = prSelection;
    }

    double NSBRKGA_MP_IPR_Solver::getPrPercentage() const {
        return this->prPercentage;
    }

    void NSBRKGA_MP_IPR_Solver::setPrPercentage(double prPercentage) {
        if(prPercentage < std::numeric_limits<double>::epsilon()) {
            this->prPercentage = 0.01;
        } else if(prPercentage > 1.00) {
            this->prPercentage = 1.00;
        } else {
            this->prPercentage = prPercentage;
        }
    }

    unsigned NSBRKGA_MP_IPR_Solver::getPrInterval() const {
        return this->prInterval;
    }

    void NSBRKGA_MP_IPR_Solver::setPrInterval(unsigned prInterval) {
        this->prInterval = prInterval;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getShakeInterval() const {
        return this->shakeInterval;
    }

    void NSBRKGA_MP_IPR_Solver::setShakeInterval(unsigned shakeInterval) {
        this->shakeInterval = shakeInterval;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getResetInterval() const {
        return this->resetInterval;
    }

    void NSBRKGA_MP_IPR_Solver::setResetInterval(unsigned resetInterval) {
        this->resetInterval = resetInterval;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumThreads() const {
        return this->numThreads;
    }

    void NSBRKGA_MP_IPR_Solver::setNumThreads(unsigned numThreads) {
        if(numThreads < 1) {
            this->numThreads = 1;
        } else {
            this->numThreads = numThreads;
        }
    }

    unsigned NSBRKGA_MP_IPR_Solver::getLastUpdateGeneration() const {
        return this->lastUpdateGeneration;
    }

    double NSBRKGA_MP_IPR_Solver::getLastUpdateTime() const {
        return this->lastUpdateTime;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getLargeOffset() const {
        return this->largeOffset;
    }

    double NSBRKGA_MP_IPR_Solver::getPathRelinkTime() const {
        return this->pathRelinkTime;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumPathRelinkCalls() const {
        return this->numPathRelinkCalls;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumHomogeneities() const {
        return this->numHomogeneities;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumEliteImprovments() const {
        return this->numEliteImprovments;
    }

    unsigned NSBRKGA_MP_IPR_Solver::getNumBestImprovments() const {
        return this->numBestImprovements;
    }

    void NSBRKGA_MP_IPR_Solver::solve() {
        this->startTime = std::chrono::steady_clock::now();

        Decoder decoder(zdt);

        this->senses = std::vector<BRKGA::Sense>(2, BRKGA::Sense::MINIMIZE);

        BRKGA::BrkgaParams params;
        params.num_incumbent_solutions = this->maxNumSolutions;
        params.population_size = this->populationSize;
        params.elite_percentage = this->elitePercentage;
        params.mutants_percentage = this->mutantPercentage;
        params.total_parents = this->numTotalParents;
        params.num_elite_parents = this->numEliteParents;
        params.bias_type = this->biasType;
        params.diversity_type = this->diversityType;
        params.num_independent_populations = this->numPopulations;
        params.pr_number_pairs = this->prPercentagePairs *
            (this->maxNumSolutions * this->elitePercentage) *
            (this->maxNumSolutions * this->elitePercentage);
        params.pr_minimum_distance = this->prMinDist;
        params.pr_type = BRKGA::PathRelinking::Type::PERMUTATION;
        params.pr_selection = this->prSelection;
        params.alpha_block_size = 0.1;
        params.pr_percentage = this->prPercentage;

        unsigned chromosomeSize = 10;
        if(this->zdt == 1 || this->zdt == 2 || this->zdt == 3) {
            chromosomeSize = 30;
        } else if(this->zdt == 5) {
            chromosomeSize = 80;
        }

        BRKGA::NSBRKGA_MP_IPR algorithm(decoder,
                                        this->senses,
                                        this->seed,
                                        chromosomeSize,
                                        params,
                                        this->numThreads);

        std::vector<std::vector<double>> pareto;

        algorithm.initialize();

        std::vector<std::pair<std::vector<double>, std::vector<double>>>
            newIndividuals = algorithm.getIncumbentSolutions();

        this->updateIndividuals(newIndividuals);

        std::shared_ptr<BRKGA::DistanceFunctionBase> dist_func(
                new BRKGA::HammingDistance());

        this->numGenerations = 0;
        this->lastUpdateGeneration = 0;
        this->largeOffset = 0;

        this->pathRelinkTime = 0.0;
        this->numPathRelinkCalls = 0;
        this->numHomogeneities = 0;
        this->numBestImprovements = 0;
        this->numEliteImprovments = 0;
        this->numShakings = 0;
        this->numResets = 0;

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

        std::uniform_int_distribution<int> distribution(1, chromosomeSize);

        while(!this->areTerminationCriteriaMet()) {
            this->numGenerations++;

            if(algorithm.evolve()) {
                this->lastUpdateTime = this->getElapsedTime();

                auto updateOffset = this->numGenerations -
                                    this->lastUpdateGeneration;
                this->lastUpdateGeneration = this->numGenerations;

                if(this->largeOffset < updateOffset) {
                    this->largeOffset = updateOffset;
                }

                newIndividuals = algorithm.getIncumbentSolutions();

                if(this->updateIndividuals(newIndividuals) && this->captureEnabled) {
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

            unsigned generationsWithoutImprovement = this->numGenerations -
                this->lastUpdateGeneration;

            if(this->largeOffset < generationsWithoutImprovement) {
                this->largeOffset = generationsWithoutImprovement;
            }

            if(this->prInterval > 0 && generationsWithoutImprovement > 0 &&
                    (generationsWithoutImprovement % this->prInterval == 0)) {
                this->numPathRelinkCalls++;
                const auto prStartTime = std::chrono::steady_clock::now();
                auto result = algorithm.pathRelink(
                        params.pr_type, 
                        params.pr_selection,
                        dist_func, 
                        params.pr_number_pairs, 
                        params.pr_minimum_distance, 
                        1, 
                        this->timeLimit - this->getElapsedTime(), 
                        params.pr_percentage);

                const auto prTime = Solver::getElapsedTime(prStartTime);
                this->pathRelinkTime += prTime;

                switch(result) {
                    case BRKGA::PathRelinking::PathRelinkingResult::TOO_HOMOGENEOUS: {
                        this->numHomogeneities++;
                        break;
                    }
                    case BRKGA::PathRelinking::PathRelinkingResult::ELITE_IMPROVEMENT: {
                        this->numEliteImprovments++;
                    }
                    case BRKGA::PathRelinking::PathRelinkingResult::BEST_IMPROVEMENT: {
                        this->numBestImprovements++;
                        this->lastUpdateTime = this->getElapsedTime();

                        auto updateOffset = this->numGenerations -
                                            this->lastUpdateGeneration;
                        this->lastUpdateGeneration = this->numGenerations;

                        if(this->largeOffset < updateOffset) {
                            this->largeOffset = updateOffset;
                        }

                        newIndividuals = algorithm.getIncumbentSolutions();

                        if(this->updateIndividuals(newIndividuals) &&
                                this->captureEnabled) {
                            std::vector<std::vector<double>> pareto(
                                    this->individuals.size());
                            std::transform(this->individuals.begin(),
                                           this->individuals.end(),
                                           pareto.begin(),
                                           [](const auto & individual) {
                                                return individual.first;
                                           });
                            this->capturedParetos.push_back(pareto);
                            this->capturedTimes.push_back(
                                    this->getElapsedTime());
                            this->capturedIterations.push_back(
                                    this->numGenerations);
                        }

                        break;
                    }

                    default: {
                        break;
                    }
                }
            }

            if(this->shakeInterval > 0 
                    && generationsWithoutImprovement > 0 
                    && (generationsWithoutImprovement % this->shakeInterval 
                        == 0)) {
                this->numShakings++;
                unsigned intensity = distribution(this->rng);
                algorithm.shake(intensity, BRKGA::ShakingType::SWAP);
            }

            if(this->resetInterval > 0 
                    && generationsWithoutImprovement > 0 
                    && (generationsWithoutImprovement % this->resetInterval) 
                        == 0) {
                this->numResets++;
                algorithm.reset();
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

    void NSBRKGA_MP_IPR_Solver::write(std::ostream & os) const {
        Solver::write(os);
        os << "Percentage of individuals to become the elite set: " 
           << this->elitePercentage << std::endl
           << "Percentage of mutants to be inserted in the population: " 
           << this->mutantPercentage << std::endl
           << "Number of total parents for mating: " << this->numTotalParents 
           << std::endl
           << "Number of elite parents for mating: " << this->numEliteParents 
           << std::endl
           << "Type of bias that will be used: " << this->biasType << std::endl
           << "Type of diversity that will be used: " << this->diversityType 
           << std::endl
           << "Number of independent parallel populations: "
           << this->numPopulations << std::endl
           << "Percentage of pairs of chromosomes to be tested to path-relinking: " 
           << this->prPercentagePairs << std::endl
           << "Minimum distance between chromosomes selected to path-relinking: " 
           << this->prMinDist << std::endl
           << "Individual selection to path-relinking: " << this->prSelection 
           << std::endl
           << "Percentage of the path to be computed: " << this->prPercentage 
           << std::endl
           << "Interval at which the path relink is applied: "
           << this->prInterval << std::endl
           << "Interval at which the populations are shaken: "
           << this->shakeInterval << std::endl
           << "Interval at which the populations are reset: " 
           << this->resetInterval << std::endl
           << "Number of threads to be used during parallel decoding: " 
           << this->numThreads << std::endl
           << "The number of generations evolved: " << this->numGenerations 
           << std::endl
           << "Last update generation: " << this->lastUpdateGeneration 
           << std::endl
           << "Last update time: " << this->lastUpdateTime << std::endl
           << "Largest number of generations between improvements: " 
           << this->largeOffset << std::endl
           << "Total path relink time: " << this->pathRelinkTime << std::endl
           << "Total path relink calls: " << this->numPathRelinkCalls 
           << std::endl
           << "Number of homogeneities: " << this->numHomogeneities 
           << std::endl
           << "Improvements in the elite set: " << this->numEliteImprovments 
           << std::endl
           << "Best individual improvements: " << this->numBestImprovements 
           << std::endl
           << "Total shakings calls: " << this->numShakings << std::endl
           << "Total resets calls: " << this->numResets << std::endl;
    }

    void NSBRKGA_MP_IPR_Solver::write(const char * filename) const {
        std::ofstream ofs;
        ofs.open(filename);

        if (ofs.is_open()) {
            this->write(ofs);
            ofs.close();
        } else {
            throw "File not created.";
        }
    }

    void NSBRKGA_MP_IPR_Solver::write(const std::string & filename) const {
        this->write(filename.c_str());
    }

    void NSBRKGA_MP_IPR_Solver::write() const {
        this->write(std::cout);
    }
}

