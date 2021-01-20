#include "Decoder.hpp"
#include <pagmo/problems/zdt.hpp>
#include <cmath>

namespace ZDT {
    Decoder::Decoder(unsigned zdt) : zdt(zdt) {
        unsigned param = 30;

        if(this->zdt == 4 || this->zdt == 6) {
            param = 10;
        }

        this->prob = pagmo::zdt(this->zdt, param);
    }

    std::vector<double> Decoder::decode(BRKGA::Chromosome & chromosome, 
                                        bool /* not used */) {
        pagmo::vector_double dv(chromosome);

        if(this->zdt == 4) {
            for(unsigned i = 1; i < chromosome.size(); i++) {
                dv[i] = 5 * (chromosome[i] - 0.5);
            }
        }

        return this->prob.fitness(dv);
    }
}

