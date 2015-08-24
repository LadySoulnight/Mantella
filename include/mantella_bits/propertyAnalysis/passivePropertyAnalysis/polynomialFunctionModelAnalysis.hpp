#pragma once

// C++ standard library
#include <unordered_map>
#include <memory>
#include <string>

// Armadillo
#include <armadillo>

// Mantella
#include <mantella_bits/propertyAnalysis/passivePropertyAnalysis.hpp>
#include <mantella_bits/regressionFunction.hpp>

namespace mant {
  class PolynomialFunctionModelAnalysis : public PassivePropertyAnalysis {
    public:
      const std::shared_ptr<RegressionFunction> regressionFunction_;
    
      explicit PolynomialFunctionModelAnalysis(
          const std::unordered_map<arma::Col<double>, double, Hash, IsEqual>& samples,
          const std::shared_ptr<RegressionFunction> regressionFunction);

      arma::Col<double> getCoefficients() const;
      arma::Col<double> getResiduals() const;

      std::string toString() const override;

    protected:
      arma::Col<double> coefficients_;
      arma::Col<double> residuals_;

      void analyseImplementation() override;
  };
}