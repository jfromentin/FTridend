#ifndef TRIDEND_SCHROEDER_ALGEBRA_HPP
#define TRIDEND_SCHROEDER_ALGEBRA_HPP

#include "schroeder_forest.hpp"
#include "quasi_shuffle.hpp"

class TridendSchroederAlgebra{
private:
public:
  SchroederTree atomic_product(Array<SchroederForest>& left, Array<SchroederForest>& right, QuasiShuffle &sigma);
  
};

#endif
