#include "decoder.hpp"
#include <pagmo/problems/zdt.hpp>
#include <cmath>

namespace zdt {

Decoder::Decoder(unsigned zdt, unsigned m) : zdt(zdt), m(m) {
    this->prob = pagmo::zdt(this->zdt, this->m);
}

std::vector<double> Decoder::decode(NSBRKGA::Chromosome & chromosome, 
                                    bool /* not used */) {
    pagmo::vector_double dv(chromosome);

    if(this->zdt == 4) {
        for(unsigned i = 1; i < chromosome.size(); i++) {
            dv[i] = 10 * (chromosome[i] - 0.5);
        }
    }

    return this->prob.fitness(dv);
}

}
