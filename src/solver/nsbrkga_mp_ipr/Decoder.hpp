#pragma once

#include "chromosome.hpp"
#include <pagmo/problem.hpp>

namespace ZDT {
    class Decoder {
        private:
            unsigned zdt;
            pagmo::problem prob;

        public:
            Decoder(unsigned zdt);

            std::vector<double> decode(BRKGA::Chromosome & chromosome, 
                                       bool rewrite);
    };
}

