#pragma once

#include "../Solver.hpp"

namespace ZDT {
    /**********************************************************************
     * The NSBRKGA_MP_IPR_Solver represents a solver for the ZDT test 
     * functions using the Non-Dominated Sorting Biased Random-Key Genetic 
     * Algorithm with Multiple Parents and Implicit Path Relink.
     **********************************************************************/
    class NSBRKGA_MP_IPR_Solver : public Solver {
        private:
            /************************************************************
             * Percentage of individuals to become the elite set (0, 1].
             ************************************************************/
            double elitePercentage;

            /**********************************************************
             * Percentage of mutants to be inserted in the population.
             **********************************************************/
            double mutantPercentage;

            /**************************************
             * Number of total parents for mating.
             **************************************/
            unsigned numTotalParents;

            /**************************************
             * Number of elite parents for mating.
             **************************************/
            unsigned numEliteParents;

            /**********************************
             * Type of bias that will be used.
             **********************************/
            BRKGA::BiasFunctionType biasType;

            /*******************************************
             * Type of diversity that will be used.
             *******************************************/
            BRKGA::DiversityFunctionType diversityType;

            /**********************************************
             * Number of independent parallel populations.
             **********************************************/
            unsigned numPopulations;

            /*****************************************************
             * Percentage of pairs of chromosomes to be tested to
             * path-relinking.
             *****************************************************/
            double prPercentagePairs;

            /***************************************************
             * Minimum distance between chromosomes selected to
             * path-relinking.
             ***************************************************/
            double prMinDist;

            /********************************************
             * Individual selection to path-relinking.
             ********************************************/
            BRKGA::PathRelinking::Selection prSelection;

            /*****************************************
             * Percentage of the path to be computed.
             *****************************************/
            double prPercentage;

            /***********************************************
             * Interval at which the path relink is applied
             * (0 means no path relinking).
             ***********************************************/
            unsigned prInterval;

            /***********************************************
             * Interval at which the populations are shaken
             * (0 means no shaking).
             ***********************************************/
            unsigned shakeInterval;

            /******************************************************************
             * Interval at which the populations are reset (0 means no reset).
             ******************************************************************/
            unsigned resetInterval;

            /*********************************************************
             * Number of threads to be used during parallel decoding.
             *********************************************************/
            unsigned numThreads;

            /*****************************
             * Last update generation.
             *****************************/
            unsigned lastUpdateGeneration;

            /**********************
             * Last update time.
             **********************/
            double lastUpdateTime;

            /******************************************************
             * Largest number of generations between improvements.
             ******************************************************/
            unsigned largeOffset;

            /**************************
             * Total path relink time.
             **************************/
            double pathRelinkTime;

            /****************************
             * Total path relink calls.
             ****************************/
            unsigned numPathRelinkCalls;

            /***************************
             * Number of homogeneities.
             ***************************/
            unsigned numHomogeneities;

            /*********************************
             * Improvements in the elite set.
             *********************************/
            unsigned numEliteImprovments;

            /********************************
             * Best individual improvements.
             ********************************/
            unsigned numBestImprovements;

            /***********************
             * Total shaking calls.
             ***********************/
            unsigned numShakings;

            /*********************
             * Total reset calls.
             *********************/
            unsigned numResets;

            /*********************************
             * The optimisation senses.
             *********************************/
            std::vector<BRKGA::Sense> senses;

        public:
            /*******************************************************************
             * Constructs a new solver.
             *
             * @param zdt               the id of the ZDT test function to be
             *                          solved.
             * @param seed              the seed for the pseudo-random numbers
             *                          generator.
             * @param timeLimit         the time limit in seconds.
             * @param maxNumSolutions   the maximum number of solutions.
             * @param captureEnabled    the flag indicating whether the
             *                          capturing of solutions for evaluation
             *                          is enabled.
             * @param populationSize    the number of individuals in each
             *                          population.
             * @param elitePercentage   the percentage of individuals to
             *                          become the elite set.
             * @param mutantPercentage  the percentage of mutants to be
             *                          inserted in the population.
             * @param numTotalParents   the number of total parents for mating.
             * @param numEliteParents   the number of elite parents for mating.
             * @param biasType          the type of bias that will be used.
             * @param diversityType     the type of diversity that will be
             *                          used.
             * @param numPopulations    the number of independent parallel
             *                          populations.
             * @param prPercentagePairs the percentage of pairs of chromosomes
             *                          to be tested to path relinking.
             * @param prMinDist         the minimum distance between
             *                          chromosomes selected to path-relinking.
             * @param prSelection       the individual selection to
             *                          path-relinking.
             * @param prPercentage      the percentage of the path to be
             *                          computed.
             * @param prInterval        interval at which the path relink is
             *                          applied.
             * @param shakeInterval     interval at which the populations are
             *                          shaken.
             * @param resetInterval     the interval at which the populations
             *                          are reset.
             * @param numThreads        the number of threads to be used
             *                           during parallel decoding.
             *******************************************************************/
            NSBRKGA_MP_IPR_Solver(unsigned zdt,
                                  unsigned seed,
                                  double timeLimit = 3600.0,
                                  unsigned maxNumSolutions = 
                                        std::numeric_limits<unsigned>::max(),
                                  bool captureEnabled = false,
                                  unsigned populationSize = 200,
                                  double elitePercentage = 0.2,
                                  double mutantPercentage = 0.2,
                                  unsigned numTotalParents = 2,
                                  unsigned numEliteParents = 1,
                                  BRKGA::BiasFunctionType biasType =
                                        BRKGA::BiasFunctionType::LOGINVERSE,
                                  BRKGA::DiversityFunctionType diversityType =
                                        BRKGA::DiversityFunctionType::NONE,
                                  unsigned numPopulations = 1,
                                  double prPercentagePairs = 0.75,
                                  double prMinDist = 0.15,
                                  BRKGA::PathRelinking::Selection prSelection =
                                        BRKGA::PathRelinking::Selection::BESTSOLUTION,
                                  double prPercentage = 0.31,
                                  unsigned prInterval = 0,
                                  unsigned shakeInterval = 0,
                                  unsigned resetInterval = 500,
                                  unsigned numThreads = 1);

            /**********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function to be solved
             **********************************************************/
            NSBRKGA_MP_IPR_Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            NSBRKGA_MP_IPR_Solver();

            /*****************************************************************
             * Returns the percentage of individuals to become the elite set.
             *
             * @return the percentage of individuals to become the elite set.
             *****************************************************************/
            double getElitePercentage() const;

            /**************************************************************
             * Sets the percentage of individuals to become the elite set.
             *
             * @param elitePercentage the new percentage of individuals to
             *                        become the elite set.
             **************************************************************/
            void setElitePercentage(double elitePercentage);

            /**********************************************************
             * Returns the percentage of mutants to be inserted in the
             * population.
             *
             * @return the percentage of mutants to be inserted in the
             *             population.
             **********************************************************/
            double getMutantPercentage() const;

            /*******************************************************************
             * Sets the percentage of mutants to be inserted in the population.
             *
             * @param mutantPercentage the new percentage of mutants to be
             *                         inserted in the population.
             *******************************************************************/
            void setMutantPercentage(double mutantPercentage);

            /**************************************************
             * Returns the number of total parents for mating.
             *
             * @return the number of total parents for mating.
             **************************************************/
            unsigned getNumTotalParents() const;

            /*************************************************************
             * Sets the number of total parents for mating.
             *
             * @param numTotalParents the new number of total parents for
             *                        mating.
             *************************************************************/
            void setNumTotalParents(unsigned numTotalParents);

            /**************************************************
             * Returns the number of elite parents for mating.
             *
             * @return the number of elite parents for mating.
             **************************************************/
            unsigned getNumEliteParents() const;

            /*************************************************************
             * Sets the number of elite parents for mating.
             *
             * @param numEliteParents the new number of elite parents for
             *                        mating.
             *************************************************************/
            void setNumEliteParents(unsigned numEliteParents);

            /**********************************************
             * Returns the type of bias that will be used.
             *
             * @return the type of bias that will be used.
             **********************************************/
            BRKGA::BiasFunctionType getBiasType() const;

            /***********************************************************
             * Sets the type of bias that will be used.
             *
             * @param biasType the new type of bias that will be used.
             ***********************************************************/
            void setBiasType(const BRKGA::BiasFunctionType & biasType);

            /******************************************************
             * Returns the type of diversity that will be used.
             *
             * @return the type of diversity that will be used.
             ******************************************************/
            BRKGA::DiversityFunctionType getDiversityType() const;

            /**************************************************************
             * Sets the type of diversity that will be used.
             *
             * @param diversityType the new type of diversity that will be 
             *                      used.
             **************************************************************/
            void setDiversityType(
                    const BRKGA::DiversityFunctionType & diversityType);

            /**********************************************************
             * Returns the number of independent parallel populations.
             *
             * @return the number of independent parallel populations.
             **********************************************************/
            unsigned getNumPopulations() const;

            /***************************************************************
             * Sets the number of independent parallel populations.
             *
             * @param numPopulations the new number of independent parallel
             *        populations.
             ***************************************************************/
            void setNumPopulations(unsigned numPopulations);

            /*****************************************************************
             * Returns the percentage of pairs of chromosomes to be tested to
             * path-relinking.
             *
             * @return the percentage of pairs of chromosomes to be tested to
             *         path-relinking.
             *****************************************************************/
            double getPrPercentagePairs() const;

            /**************************************************************
             * Sets the percentage of pairs of chromosomes to be tested to
             * path-relinking.
             *
             * @param prPercentagePairs the new percentage of pairs of
             *        chromosomes to be tested to path-relinking.
             **************************************************************/
            void setPrPercentagePairs(double prPercentagePairs);

            /***************************************************************
             * Returns the minimum distance between chromosomes selected to
             * path-relinking.
             *
             * @return the minimum distance between chromosomes selected to
             * path-relinking.
             ***************************************************************/
            double getPrMinDist() const;

            /***************************************************************
             * Sets the minimum distance between chromosomes selected to
             * path-relinking.
             *
             * param prMinDist the new minimum distance between chromosomes
             *                 selected to path-relinking.
             ***************************************************************/
            void setPrMinDist(double prMinDist);

            /*******************************************************
             * Returns the individual selection to path-relinking.
             *
             * @return the individual selection to path-relinking.
             *******************************************************/
            BRKGA::PathRelinking::Selection getPrSelection() const;

            /*****************************************************************
             * Sets the individual selection to path-relinking.
             *
             * @param prSelection the new individual selection to
             *                    path-relinking.
             *****************************************************************/
            void setPrSelection(BRKGA::PathRelinking::Selection prSelection);

            /*****************************************************
             * Returns the percentage of the path to be computed.
             *
             * @return the percentage of the path to be computed.
             *****************************************************/
            double getPrPercentage() const;

            /***********************************************************
             * Sets the percentage of the path to be computed.
             *
             * @param prPercentage the new percentage of the path to be
             *                     computed.
             ***********************************************************/
            void setPrPercentage(double prPercentage);

            /************************************************************
             * Returns the interval at which the path relink is applied.
             *
             * @return the interval at which the path relink is applied.
             ************************************************************/
            unsigned getPrInterval() const;

            /*****************************************************************
             * Sets the interval at which the path relink is applied.
             *
             * @param prInterval the new interval at which the path relink is
             *        applied.
             *****************************************************************/
            void setPrInterval(unsigned prInterval);

            /************************************************************
             * Returns the interval at which the populations are shaken.
             *
             * @return the interval at which the populations are shaken.
             ************************************************************/
            unsigned getShakeInterval() const;

            /*****************************************************************
             * Sets the interval at which the populations are shaken.
             *
             * @param shakeInterval the new interval at which the populations
             *        are shaken.
             *****************************************************************/
            void setShakeInterval(unsigned shakeInterval);

            /***********************************************************
             * Returns the interval at which the populations are reset.
             *
             * @return the interval at which the populations are reset.
             ***********************************************************/
            unsigned getResetInterval() const;

            /*****************************************************************
             * Sets the interval at which the population are reset.
             *
             * @param resetInverval the new interval at which the populations
             *                      are reset.
             *****************************************************************/
            void setResetInterval(unsigned resetInterval);

            /***********************************************************
             * Returns the number of threads to be used during parallel
             * decoding.
             *
             * @return the number of threads to be used during parallel
             *         decoding.
             ***********************************************************/
            unsigned getNumThreads() const;

            /******************************************************************
             * Sets the number of threads to be used during parallel decoding.
             *
             * @param numThreads the new number of threads to be used during
             *                   parallel decoding.
             ******************************************************************/
            void setNumThreads(unsigned numThreads);

            /*****************************************
             * Returns the last update generation.
             *
             * @return the last update generation.
             *****************************************/
            unsigned getLastUpdateGeneration() const;

            /*********************************
             * Returns the last update time.
             *
             * @return the last update time.
             *********************************/
            double getLastUpdateTime() const;

            /******************************************************************
             * Returns the largest number of generations between improvements.
             *
             * @return the largest number of generations between improvements.
             ******************************************************************/
            unsigned getLargeOffset() const;

            /**************************************
             * Returns the total path relink time.
             *
             * @return the total path relink time.
             **************************************/
            double getPathRelinkTime() const;

            /***************************************
             * Returns the total path relink calls.
             *
             * @return the total path relink calls.
             ***************************************/
            unsigned getNumPathRelinkCalls() const;

            /***************************************
             * Returns the number of homogeneities.
             *
             * @return the number of homogeneities.
             ***************************************/
            unsigned getNumHomogeneities() const;

            /*******************************************************
             * Returns the number of improvements in the elite set.
             *
             * @return the number of improvements in the elite set.
             *******************************************************/
            unsigned getNumEliteImprovments() const;

            /******************************************************
             * Returns the number of best individual improvements.
             *
             * @return the number of best individual improvements.
             ******************************************************/
            unsigned getNumBestImprovments() const;

            /**********************
             * Solve the instance.
             **********************/
            void solve();

            /*********************************************************
             * Write the statistics into the specified output stream.
             *
             * @param os the output stream to write into.
             *********************************************************/
            void write(std::ostream & os) const;

            /************************************************
             * Write the statistics into the specified file.
             *
             * @param filename the file to write into.
             ************************************************/
            void write(const char * filename) const;

            /************************************************
             * Write the statistics into the specified file.
             *
             * @param filename the file to write into.
             ************************************************/
            void write(const std::string & filename) const;

            /********************************************************
             * Write the statistics into the standard output stream.
             ********************************************************/
            void write() const;
    };
}

