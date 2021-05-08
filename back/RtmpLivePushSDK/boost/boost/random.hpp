/* boost random.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/random for documentation.
 *
 * $Id: random.hpp 71018 2011-04-05 21:27:52Z steven_watanabe $
 *
 * Revision history
 *  2000-02-18  portability fixes (thanks to Beman Dawes)
 *  2000-02-21  shuffle_output, inversive_congruential_schrage,
 *              generator_iterator, uniform_smallint
 *  2000-02-23  generic modulus arithmetic helper, removed *_schrage classes,
 *              implemented Streamable and EqualityComparable concepts for 
 *              generators, added Bernoulli distribution and Box-Muller
 *              transform
 *  2000-03-01  cauchy, lognormal, triangle distributions; fixed 
 *              uniform_smallint; renamed gaussian to normal distribution
 *  2000-03-05  implemented iterator syntax for distribution functions
 *  2000-04-21  removed some optimizations for better BCC/MSVC compatibility
 *  2000-05-10  adapted to BCC and MSVC
 *  2000-06-13  incorporated review results
 *  2000-07-06  moved basic templates from namespace detail to random
 *  2000-09-23  warning removals and int64 fixes (Ed Brey)
 *  2000-09-24  added lagged_fibonacci generator (Matthias Troyer)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_HPP
#define BOOST_RANDOM_HPP

// generators
#include "additive_combine.hpp"
#include "discard_block.hpp"
#include "independent_bits.hpp"
#include "inversive_congruential.hpp"
#include "lagged_fibonacci.hpp"
#include "linear_congruential.hpp"
#include "linear_feedback_shift.hpp"
#include "mersenne_twister.hpp"
#include "ranlux.hpp"
#include "shuffle_order.hpp"
#include "shuffle_output.hpp"
#include "subtract_with_carry.hpp"
#include "taus88.hpp"
#include "xor_combine.hpp"

// misc
#include "generate_canonical.hpp"
#include "seed_seq.hpp"
#include "random_number_generator.hpp"
#include "variate_generator.hpp"

// distributions
#include "bernoulli_distribution.hpp"
#include "binomial_distribution.hpp"
#include "cauchy_distribution.hpp"
#include "chi_squared_distribution.hpp"
#include "discrete_distribution.hpp"
#include "exponential_distribution.hpp"
#include "extreme_value_distribution.hpp"
#include "fisher_f_distribution.hpp"
#include "gamma_distribution.hpp"
#include "geometric_distribution.hpp"
#include "lognormal_distribution.hpp"
#include "negative_binomial_distribution.hpp"
#include "normal_distribution.hpp"
#include "piecewise_constant_distribution.hpp"
#include "piecewise_linear_distribution.hpp"
#include "poisson_distribution.hpp"
#include "student_t_distribution.hpp"
#include "triangle_distribution.hpp"
#include "uniform_01.hpp"
#include "uniform_int.hpp"
#include "uniform_int_distribution.hpp"
#include "uniform_on_sphere.hpp"
#include "uniform_real.hpp"
#include "uniform_real_distribution.hpp"
#include "uniform_smallint.hpp"
#include "weibull_distribution.hpp"

#endif // BOOST_RANDOM_HPP
