#pragma once

#include "../Solver.hpp"
#include <pagmo/population.hpp>

namespace ZDT {
    /************************************************************************
     * The NSGA2_Solver represents a solver for the ZDT test functions using
     * the Non-Dominated Sorting Genetic Algorithm II.
     ************************************************************************/
    class NSGA2_Solver : public Solver {
        private:
            /*************************
             * Crossover probability.
             *************************/
            double crossoverProbability;

            /************************************
             * Distribution index for crossover.
             ************************************/
            double crossoverDistribution;

            /***************************
             * Mutation probability.
             ***************************/
            double mutationProbability;

            /***********************************
             * Distribution index for mutation.
             ***********************************/
            double mutationDistribution;

            /******************************************************
             * Update the best individuals found so far.
             *
             * @param pop the new solutions.
             *
             * @return true if the best individuals are modified;
             *         false otherwise.
             ******************************************************/
            bool updateIndividuals(const pagmo::population & pop);

        public:
            /******************************************************************
             * Constructs a new solver.
             *
             * @param zdt                   the id of the ZDT test function to
             *                              be solved.
             * @param seed                  the seed for the pseudo-random
             *                              numbers generator.
             * @param timeLimit             the time limit in seconds.
             * @param maxNumSolutions       the maximum number of solutions.
             * @param captureEnabled        the flag indicating whether the
             *                              capturing of solutions for
             *                              evaluation is enabled.
             * @param populationSize        the size of the population.
             * @param crossoverProbability  the crossover probability.
             * @param crossoverDistribution the distribution index for
             *                              crossover.
             * @param mutationProbability   the mutation probability.
             * @param mutationDistribution  the distribution index for 
             *                              mutation.
             ******************************************************************/
            NSGA2_Solver(unsigned zdt,
                         unsigned seed,
                         double timeLimit = 3600.0,
                         unsigned maxNumSolutions = 
                                std::numeric_limits<unsigned>::max(),
                         bool captureEnabled = false,
                         unsigned populationSize = 200,
                         double crossoverProbability = 0.90,
                         double crossoverDistribution = 20.00,
                         double mutationProbability = 0.01,
                         double mutationDistribution = 20.00);

            /***********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function to be solved.
             ***********************************************************/
            NSGA2_Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            NSGA2_Solver();

            /***************************************
             * Returns the crossover probability.
             *
             * @return the crossover probability.
             ***************************************/
            double getCrossoverProbability() const;

            /*************************************************************
             * Sets the crossover probability.
             *
             * @param crossoverProbability the new crossover probability.
             *************************************************************/
            void setCrossoverProbability(double crossoverProbability);

            /************************************************
             * Returns the distribution index for crossover.
             *
             * @return the distribution index for crossover.
             ************************************************/
            double getCrossoverDistribution() const;

            /**************************************************************
             * Sets the distribution index for crossover.
             *
             * @param crossoverDistribution the new distribution index for
             *        crossover.
             **************************************************************/
            void setCrossoverDistribution(double crossoverDistribution);

            /**************************************
             * Returns the mutation probability.
             *
             * @return the mutation probability.
             **************************************/
            double getMutationProbability() const;

            /************************************************************
             * Sets the mutation probability.
             *
             * @param mutationProbability the new crossover probability.
             ************************************************************/
            void setMutationProbability(double mutationProbability);

            /***********************************************
             * Returns the distribution index for mutation.
             *
             * @return the distribution index for mutation.
             ***********************************************/
            double getMutationDistribution() const;

            /*************************************************************
             * Sets the distribution index for mutation.
             *
             * @param mutationDistribution the new distribution index for
             *        mutation.
             *************************************************************/
            void setMutationDistribution(double mutationDistribution);

            /***********************
             * Solves the instance.
             ***********************/
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

