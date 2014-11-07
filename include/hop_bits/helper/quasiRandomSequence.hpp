#pragma once

// Armadillo
#include <armadillo>

namespace hop {
   arma::Mat<double> getHaltonSequence(
       const arma::Col<arma::uword>& seed,
       const arma::Col<arma::uword>& base,
       const unsigned int& numberOfColumms);

   arma::Col<double> getVanDerCorputSequence(
       const unsigned int& seed,
       const unsigned int& base,
       const unsigned int& numberOfColumms);
}
