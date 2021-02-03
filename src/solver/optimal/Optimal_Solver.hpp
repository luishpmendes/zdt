#pragma once

#include "../Solver.hpp"
#include <pagmo/problem.hpp>

namespace ZDT {
    class Optimal_Solver : public Solver {
        private:
            pagmo::problem prob;

        public:
            /****************************************************************
             * Constructs a new solver.
             *
             * @param zdt             the id of the ZDT test function to be
             *                        solved.
             * @param seed            the seed for the pseudo-random numbers
             *                        generator.
             * @param timeLimit       the time limit in seconds.
             * @param maxNumSolutions the maximum number of solutions.
             ****************************************************************/
            Optimal_Solver(unsigned zdt,
                           unsigned seed,
                           double timeLimit = 3600.0,
                           unsigned maxNumSolutions = 1000);

            /***********************************************************
             * Constructs a new solver.
             *
             * @param zdt the id of the ZDT test function to be solved.
             ***********************************************************/
            Optimal_Solver(unsigned zdt);

            /******************************
             * Constructs an empty solver.
             ******************************/
            Optimal_Solver();

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

