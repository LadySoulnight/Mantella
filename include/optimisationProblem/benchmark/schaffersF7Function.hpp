#pragma once

#include <optimisationProblem/benchmark/benchmarkProblem.hpp>

namespace hop {
  class SchaffersF7Function : public BenchmarkProblem {
    public:
      SchaffersF7Function(const unsigned int& numberOfDimensions);

    protected:
      const arma::Col<double> _delta;

      double getObjectiveValueImplementation(const arma::Col<double>& parameter) const override;
  };
}
