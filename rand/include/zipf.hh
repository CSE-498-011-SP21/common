/**
 * @author dePaul Miller
 */

#ifndef COMMON_ZIPF_HH
#define COMMON_ZIPF_HH

namespace cse498 {

    namespace rand {

        /**
         * Computes the generalized harmonic number of order theta of n
         * @param theta
         * @param n
         * @return
         */
        double zeta(double theta, int n);

        /**
         * Generates a random zipfian number in [1,n] from the seed, n, zeta(theta, n), and theta
         * This is derived from "Quickly Generating Billion-Record Synthetic Databases" by Jim Gray et. al.
         * @param seed
         * @param n
         * @param zetaN
         * @param theta
         * @return
         */
        int rand_zipf_r(unsigned int *seed, long n, double zetaN, double theta);

        /**
         * Generates a random zipfian number in [1,n] from the n, zeta(theta, n), and theta
         * This is derived from "Quickly Generating Billion-Record Synthetic Databases" by Jim Gray et. al.
         * @param n
         * @param zetaN
         * @param theta
         * @return
         */
        int rand_zipf(long n, double zetaN, double theta);

    }

}

#endif //COMMON_ZIPF_HH
