#pragma once

#include "../Solver.hpp"
#include <pagmo/population.hpp>

namespace ZDT {
    /************************************************************************
     * The MHACO_Solver represents a solver for the ZDT test functions using
     * the Multi-Objective Hypervolume-based Ant Colony Optimizer.
     ************************************************************************/
    class MHACO_Solver : public Solver {
        private:
            /***********************************************************
             * Number of solutions stored in the solution archive 
             * (which is maintained independently from the population).
             ***********************************************************/
            unsigned ker;

            /***********************************************************
             * This parameter is called convergence speed parameter,
             * and it is useful for managing the convergence speed 
             * towards the best found solution 
             * (in terms of non-dominated front and hypervolume value).
             * The smaller the parameter, the faster the convergence 
             * and the higher the chance to get stuck to local minima.
             ***********************************************************/
            double q;

            /***********************************************
             * When the generations reach the threshold, 
             * then q is set to 0.01 automatically, 
             * thus increasing consistently the convergence
             * speed towards the best found value.
             ***********************************************/
            unsigned threshold;

            /*******************************************
             * This parameter regulates the convergence 
             * speed of the standard deviation values.
             *******************************************/
            unsigned nGenMark;

            /*********************************************************
             * If a positive integer is assigned here, 
             * the algorithm will count the runs without improvements
             * (in terms of ideal point), 
             * if this number will exceed the evalStop value, 
             * the algorithm will be stopped and will return the 
             * evolved population until than moment.
             *********************************************************/
            unsigned evalStop;

            /****************************************************************
             * This parameter makes the search for the optimum greedier and 
             * more focused on local improvements (the higher the greedier). 
             * If the value is very high, the search is more focused around
             * the currently found best solutions.
             ****************************************************************/
            double focus;

            /*************************************************
             * Memory parameter. If true, memory is activated 
             * in the algorithm for multiple calls.
             *************************************************/
            bool memory;

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
            /*******************************************************************
             * Constructs a new solver.
             *
             * @param zdt             the id of the ZDT test function to be
             *                        solved.
             * @param seed            the seed for the pseudo-random numbers
             *                        generator.
             * @param timeLimit       the time limit in seconds.
             * @param maxNumSolutions the maximum number of solutions.
             * @param captureEnabled  the flag indicating whether the capturing
             *                        of solutions for evaluation is enabled.
             * @param populationSize  the size of the population.
             * @param ker             number of solutions stored in the 
             *                        solution archive.
             * @param q               the convergence speed parameter.
             * @param threshold       the threshold parameter.
             * @param nGenMark        the nGenMark parameter.
             * @param evalStop        the evalStop parameter.
             * @param focus           the focus parameter.
             * @param memory          the memory paramter.
             *******************************************************************/
            MHACO_Solver(unsigned zdt,
                         unsigned seed,
                         double timeLimit = 3600.0,
                         unsigned maxNumSolutions = 
                                std::numeric_limits<unsigned>::max(),
                         bool captureEnabled = false,
                         unsigned populationSize = 200,
                         unsigned ker = 63,
                         double q = 1.0,
                         unsigned threshold = 1,
                         unsigned nGenMark = 7,
                         unsigned evalStop = 0,
                         double focus = 0.0,
                         bool memory = false);

            /***********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function to be solved.
             ***********************************************************/
            MHACO_Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            MHACO_Solver();

            /******************************************************************
             * Returns the number of solutions stored in the solution archive.
             *
             * @return the number of solutions stored in the solution archive.
             ******************************************************************/
            unsigned getKer() const;

            /****************************************************************
             * Sets the number of solutions stored in the solution archive.
             *
             * @param ker the new number of solutions stored in the solution
             *        archive.
             ****************************************************************/
            void setKer(unsigned ker);

            /*******************************************
             * Returns the convergence speed parameter.
             *
             * @return the convergence speed parameter.
             *******************************************/
            double getQ() const;

            /************************************************
             * Sets the convergence speed parameter.
             *
             * @param q the new convergence speed parameter.
             ************************************************/
            void setQ(double q);

            /**************************************
             * Returns the threshold.
             *
             * @return the threshold.
             **************************************/
            unsigned getThreshold() const;

            /**************************************
             * Sets the threshold.
             *
             * @param threshold the new threshold.
             **************************************/
            void setThreshold(unsigned threshold);

            /*****************************
             * Returns the nGenMark.
             *
             * @return the nGenMark.
             *****************************/
            unsigned getNGenMark() const;

            /************************************
             * Sets the nGenMark.
             *
             * @param nGenMark the new nGenMark.
             ************************************/
            void setNGenMark(unsigned nGenMark);

            /*****************************
             * Returns the evalStop.
             *
             * @return the evalStop.
             *****************************/
            unsigned getEvalStop() const;

            /************************************
             * Sets the evalStop.
             *
             * @param evalStop the new evalStop.
             ************************************/
            void setEvalStop(unsigned evalStop);

            /************************
             * Returns the focus.
             *
             * @return the focus.
             ************************/
            double getFocus() const;

            /******************************
             * Sets the focus.
             *
             * @param focus the new focus.
             ******************************/
            void setFocus(double focus);

            /********************************
             * Returns the memory parameter.
             *
             * @return the memory parameter.
             ********************************/
            bool getMemory() const;

            /******************************************
             * Sets the memory parameter.
             *
             * @param memory the new memory parameter.
             ******************************************/
            void setMemory(bool memory);

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

