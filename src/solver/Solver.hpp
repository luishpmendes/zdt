#pragma once

#define NSBRKGA_MULTIPLE_INCLUSIONS

#include "nsbrkga_mp_ipr.hpp"
#include <chrono>
#include <random>
#include <vector>

namespace ZDT {
    /*****************************************************************
     * The Solver abstract class represents a solver for the ZDT test
     * functions.
     *****************************************************************/
    class Solver {
        public:
            /*****************************************************************
             * Returns the elapsed time in seconds.
             *
             * @param startTime the start time
             *
             * @return the elapsed time in seconds.
             *****************************************************************/
            static double getElapsedTime(
                    const std::chrono::steady_clock::time_point & startTime);

            /***************************************
             * Returns the elapsed time in seconds.
             *
             * @return the elapsed time.
             ***************************************/
            static double getRemainingTime(
                    const std::chrono::steady_clock::time_point & startTime,
                    double timeLimit);

        protected:
            /***********************************************
             * The id of the ZDT test function been solved.
             ***********************************************/
            unsigned zdt;

            /***************************
             * The optimisation senses.
             ***************************/
            std::vector<BRKGA::Sense> senses;

            /****************************************************
             * The seed for the pseudo-random numbers generator.
             ****************************************************/
            unsigned seed;

            /**************************************
             * The pseudo-random number generator.
             **************************************/
            std::mt19937 rng;

            /*****************************
             * The time limit in seconds.
             *****************************/
            double timeLimit;

            /******************************************************
             * The maximum number of solutions (0 means no limit).
             ******************************************************/
            unsigned maxNumSolutions;

            /*********************************************************
             * Flag indicating whether the capturing of solutions for
             * evaluation is enabled.
             *********************************************************/
            bool captureEnabled;

            /**************************
             * Size of the population.
             **************************/
            unsigned populationSize;

            /****************************************************************
             * The individuals found.
             ****************************************************************/
            std::vector<std::pair<std::vector<double>, std::vector<double>>>
                individuals;

            /*******************************
             * The solving time in seconds.
             *******************************/
            double solvingTime;

            /************************************************************
             * Solutions' costs captured for evaluation.
             ************************************************************/
            std::vector<std::vector<std::vector<double>>> capturedParetos;

            /********************************************************
             * The time in seconds when the solutions were captured.
             ********************************************************/
            std::vector<double> capturedTimes;

            /***************************************************
             * The iteration when the solutions where captured.
             ***************************************************/
            std::vector<unsigned> capturedIterations;

            /************************************************
             * The start time.
             ************************************************/
            std::chrono::steady_clock::time_point startTime;

            /*****************************
             * The number of generations.
             *****************************/
            unsigned numGenerations;

            /***********************************************************
             * Verifies whether the termination criteria have been met.
             *
             * @return true if the termination criteria have been met;
             * false otherwise.
             ***********************************************************/
            bool areTerminationCriteriaMet() const;

            /**************************************************************
             * Update the best individuals found so far.
             *
             * @param newIndividuals the new individuals found.
             *
             * @return true if the best individual are modified;
             *         false otherwise.
             **************************************************************/
            bool updateIndividuals(
                    const std::vector<
                        std::pair<std::vector<double>,
                                  std::vector<double>>> & newIndividuals);

        public:
            /*******************************************************************
             * Constructs a new solver.
             *
             * @param zdt             the id of the ZDT test function to be 
             *                        solved.
             * @param seed            the seed for the pseudo-random numbers
             *                        generator.
             * @param timeLimit       the time limit in seconds.
             * @param maxNumSolutions the maximum number of solutions
             * @param captureEnabled  the flag indicating whether the capturing
             *                        of solutions for evaluation is enabled.
             * @param populationSize  the size of the population.
             *******************************************************************/
            Solver(unsigned zdt,
                   unsigned seed,
                   double timeLimit = 10.0,
                   unsigned maxNumSolutions =
                        std::numeric_limits<unsigned>::max(),
                   bool captureEnabled = false,
                   unsigned populationSize = 100);

            /**********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function been solved.
             **********************************************************/
            Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            Solver();

            /*******************************************************
             * Returns the id of the ZDT test function to be solved.
             *
             * @return the id of the ZDT test function to be solved.
             *******************************************************/
            unsigned getZDT() const;

            /***************************************************************
             * Sets the id of the ZDT test function to be solved.
             *
             * @param zdt the id of the new ZDT test function to be solved.
             ***************************************************************/
            void setZDT(unsigned zdt);

            /************************************************************
             * Returns the seed for the pseudo-random numbers generator.
             *
             * @return the seed for the pseudo-random numbers generator.
             ************************************************************/
            unsigned getSeed() const;

            /*********************************************************
             * Sets the seed for the pseudo-random numbers generator.
             *
             * @param seed the new seed for the pseudo-random numbers
             *        generator.
             *********************************************************/
            void setSeed(unsigned seed);

            /*************************************
             * Returns the time limit in seconds.
             *
             * @return the time limit in seconds.
             *************************************/
            double getTimeLimit() const;

            /**************************************************
             * Sets the time limit in seconds.
             *
             * @param timeLimit the new time limit in seconds.
             **************************************************/
            void setTimeLimit(double timeLimit);

            /*******************************************
             * Returns the maximum number of solutions.
             *
             * @return the maximum number of solutions.
             *******************************************/
            unsigned getMaxNumSolutions() const;

            /**************************************************************
             * Sets the maximum number of solutions.
             *
             * @param maxNumSolutions the new maximum number of solutions.
             **************************************************************/
            void setMaxNumSolutions(unsigned maxNumSolutions);

            /*****************************************************************
             * Returns the flag indicating whether the capturing of solutions
             * for evaluation is enabled.
             *
             * @return true if the capturing of solutions for evaluation is
             * enabled, false otherwise.
             *****************************************************************/
            bool isCaptureEnabled() const;

            /******************************************************************
             * Sets the flag indicating whether the capturing of solutions for
             * evaluation is enabled.
             *
             * @param captureEnabled the new flag indicating whether the
             *        capturing of solutions for evaluation is enabled.
             ******************************************************************/
            void setCaptureEnabled(bool captureEnabled);

            /**************************************
             * Returns the size of the population.
             *
             * @return the size of the population.
             **************************************/
            unsigned getPopulationSize() const;

            /********************************************************
             * Sets the size of the population.
             *
             * @param populationSize the new size of the population.
             ********************************************************/
            void setPopulationSize(unsigned populationSize);

            /********************************************************************
             * Returns the individuals found.
             *
             * @return the individuals found.
             ********************************************************************/
            const std::vector<std::pair<std::vector<double>,
                                        std::vector<double>>> & getIndividuals()
                                            const;

            /***********************************************************************
             * Returns the solutions' costs captured for evaluation.
             *
             * @return the solutions' costs captured for evaluation.
             ***********************************************************************/
            std::vector<std::vector<std::vector<double>>> getCapturedParetos() const;

            /****************************************************************
             * Returns the time in seconds when the solutions were captured.
             *
             * @return the time in seconds when the solutions were captured.
             ****************************************************************/
            std::vector<double> getCapturedTimes() const;

            /***********************************************************
             * Returns the iteration when the solutions where captured.
             *
             * @return the iteration when the solutions where captured.
             ***********************************************************/
            std::vector<unsigned> getCapturedIterations() const;

            /***************************************
             * Returns the solving time in seconds.
             *
             * @return the solving time in seconds.
             ***************************************/
            double getSolvingTime() const;

            /***************************************
             * Returns the elapsed time in seconds.
             *
             * @return the elapsed time.
             ***************************************/
            double getElapsedTime() const;

            /*****************************************
             * Returns the remaining time in seconds.
             *
             * @return the remaining time in seconds.
             *****************************************/
            double getRemainingTime() const;

            /*************************************
             * Returns the number of generations.
             *************************************/
            unsigned getNumGenerations() const;

            /*************************
             * Solves the instance.
             *************************/
            virtual void solve() = 0;

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

