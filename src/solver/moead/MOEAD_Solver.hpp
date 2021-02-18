#pragma once

#include "../Solver.hpp"
#include <pagmo/population.hpp>

namespace ZDT {
    /************************************************************************
     * The MOEAD_Solver represents a solver for the ZDT test functions using
     * the Multi-objective Evolutionary Algorithm by Decomposition.
     ************************************************************************/
    class MOEAD_Solver : public Solver {
        private:
            /******************************************************
             * Method used to generate the weights, one of “grid”,
             * “low discrepancy” or “random”.
             ******************************************************/
            std::string weightGeneration;

            /******************************************************************
             * Decomposition method: one of “weighted”, “tchebycheff” or “bi”.
             ******************************************************************/
            std::string decomposition;

            /*************************************
             * Size of the weight’s neighborhood.
             *************************************/
            unsigned neighbours;

            /**************************************************************
             * Crossover parameter in the Differential Evolution operator.
             **************************************************************/
            double cr;

            /*****************************************************
             * Parameter for the Differential Evolution operator.
             *****************************************************/
            double f;

            /******************************************************
             * Distribution index used by the polynomial mutation.
             ******************************************************/
            double etaM;

            /****************************************************
             * Chance that the neighbourhood is considered at
             * each generation, rather than the whole population
             * (only if preserve_diversity is true).
             ****************************************************/
            double realb;

            /********************************************************
             * Maximum number of copies reinserted in the population
             * (only if m_preserve_diversity is true).
             ********************************************************/
            unsigned limit;

            /****************************************************************
             * When true activates the two diversity preservation mechanisms
             * described in Li, Hui, and Qingfu Zhang paper.
             ****************************************************************/
            bool preserveDiversity;

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
             * @param zdt               the id of the ZDT test function to be
             *                          solved.
             * @param seed              the seed for the pseudo-random numbers
             *                          generator.
             * @param timeLimit         the time limit in seconds.
             * @param maxNumSolutions   the maximum number of solutions.
             * @param captureEnabled    the flag indicating whether the
             *                          capturing of solutions for evaluation
             *                          is enabled.
             * @param populationSize    the size of the population.
             * @param weightGeneration  the method used to generate the
             *                          weights.
             * @param decomposition     the decomposition method..
             * @param neighbours        the size of the weight’s neighborhood.
             * @param cr                the crossover parameter in the
             *                          Differential Evolution operator.
             * @param f                 the parameter for the Differential
             *                          Evolution operator.
             * @param etaM              the distribution index used by the
             *                          polynomial mutation.
             * @param realb             the chance that the neighbourhood is
             *                          considered at each generation, rather
             *                          than the whole population.
             * @param limit             the maximum number of copies reinserted
             *                          in the population.
             * @param preserveDiversity when true activates the two diversity
             *                          preservation mechanisms described in 
             *                          Li, Hui, and Qingfu Zhang paper.
             ******************************************************************/
            MOEAD_Solver(unsigned zdt,
                         unsigned seed,
                         double timeLimit = 3600.0,
                         unsigned maxNumSolutions = 
                                std::numeric_limits<unsigned>::max(),
                         bool captureEnabled = false,
                         unsigned populationSize = 200,
                         std::string weightGeneration = "grid",
                         std::string decomposition = "tchebycheff",
                         unsigned neighbours = 20,
                         double cr = 1.0,
                         double f = 0.5,
                         double etaM = 20.0,
                         double realb = 0.9,
                         unsigned limit = 2,
                         bool preserveDiversity = true);

            /***********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function to be solved.
             ***********************************************************/
            MOEAD_Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            MOEAD_Solver();

            /***************************************************
             * Returns the method used to generate the weights.
             *
             * @return the method used to generate the weights.
             ***************************************************/
            std::string getWeightGeneration() const;

            /***************************************************************
             * Sets the method used to generate the weights.
             *
             * @param weightGeneration the new method used to generate the
             *        weights.
             ***************************************************************/
            void setWeightGeneration(const std::string & weightGeneration);

            /*************************************
             * Returns the decomposition method.
             *
             * @return the decomposition method.
             *************************************/
            std::string getDecomposition() const;

            /*********************************************************
             * Sets the decomposition method.
             *
             * @param decomposition the new decomposition method.
             *********************************************************/
            void setDecomposition(const std::string & decomposition);

            /*************************************************
             * Returns the size of the weight’s neighborhood.
             *
             * @return the size of the weight’s neighborhood.
             *************************************************/
            unsigned getNeighbours() const;

            /***************************************************************
             * Sets the size of the weight’s neighborhood.
             *
             * @param neighbours the new size of the weight’s neighborhood.
             ***************************************************************/
            void setNeighbours(unsigned neighbours);

            /****************************************************************
             * Returns the crossover parameter in the Differential Evolution
             * operator.
             *
             * @return the crossover parameter in the Differential Evolution
             *         operator.
             ****************************************************************/
            double getCR() const;

            /*************************************************************
             * Sets the crossover parameter in the Differential Evolution
             * operator.
             *
             * @param cr the new crossover parameter in the Differential
             *        Evolution operator.
             *************************************************************/
            void setCR(double cr);

            /*****************************************************************
             * Returns the parameter for the Differential Evolution operator.
             *
             * @return the parameter for the Differential Evolution operator.
             *****************************************************************/
            double getF() const;

            /**************************************************************
             * Sets the parameter for the Differential Evolution operator.
             *
             * @param f the new parameter for the Differential Evolution
             *        operator.
             **************************************************************/
            void setF(double f);

            /******************************************************************
             * Returns the distribution index used by the polynomial mutation.
             *
             * @return the distribution index used by the polynomial mutation.
             ******************************************************************/
            double getEtaM() const;

            /****************************************************************
             * Sets the distribution index used by the polynomial mutation.
             *
             * @param etaM the new distribution index used by the polynomial
             *             mutation.
             ****************************************************************/
            void setEtaM(double etaM);

            /******************************************************************
             * Returns the chance that the neighbourhood is considered at each
             * generation, rather than the whole population.
             *
             * @return the chance that the neighbourhood is considered at each
             *         generation, rather than the whole population.
             ******************************************************************/
            double getRealb() const;

            /*******************************************************************
             * Sets the chance that the neighbourhood is considered at each
             * generation, rather than the whole population.
             *
             * @param realb the new chance that the neighbourhood is considered
             *        at each generation, rather than the whole population.
             *******************************************************************/
            void setRealb(double realb);

            /*********************************************************
             * Returns the maximum number of copies reinserted in the
             * population.
             *
             * @return the maximum number of copies reinserted in the
             *         population.
             *********************************************************/
            unsigned getLimit() const;

            /******************************************************************
             * Sets the maximum number of copies reinserted in the population.
             *
             * @param limit the new maximum number of copies reinserted in the
             *        population.
             ******************************************************************/
            void setLimit(unsigned limit);

            /*************************************************************
             * Returns true if the preservation mechanisms are activated;
             * false otherwise.
             *
             * @return true if the preservation mechanisms are activated;
             *         false otherwise.
             *************************************************************/
            bool getPreserveDiversity() const;

            void setPreserveDiversity(bool preserveDiversity);

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

