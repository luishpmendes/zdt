#pragma once

#include "chromosome.hpp"
#include <pagmo/problem.hpp>

namespace zdt {

class Decoder {
    public:

    unsigned zdt;

    unsigned m;

    pagmo::problem prob;

    Decoder(unsigned zdt, unsigned m);

    std::vector<double> decode(NSBRKGA::Chromosome & chromosome, bool rewrite);
};

}
