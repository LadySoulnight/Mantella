#pragma once

// C++ Standard Library
#include <memory>

// HOP
#include <hop_bits/optimisationProblem.hpp>

namespace hop {
  template <typename ParameterType, class DistanceFunction>
  class PropertiesAnalysis {
    public:
      explicit PropertiesAnalysis() noexcept
        : plausibility_(0.0) {

      }

      // Copy constructors are not used in this library and deleted to avoid unintended/any usage.
      PropertiesAnalysis(const PropertiesAnalysis&) = delete;
      PropertiesAnalysis& operator=(const PropertiesAnalysis&) = delete;

      void analyse(
          const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem) noexcept;

      double getPlausibility() const noexcept;

    protected:
      double plausibility_;

      virtual void analyseImplementation(
          const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem) noexcept = 0;
  };

  //! Only FORWARD DECLARARTION of FULLY TEMPLATE SPECIALISATION from here on.
  //! Note: Forward declaration is needed to avoid ordering errors within the source file.

  // Nothing to see here, move along ...

  //! Only PARTIAL TEMPLATE SPECIALISATION from here on.
  //!
  //! Only PUBLIC methods from here on
  //! Note: Runtime checks are only performed for public methods.

  template <typename ParameterType, class DistanceFunction>
  void PropertiesAnalysis<ParameterType, DistanceFunction>::analyse(
      const std::shared_ptr<OptimisationProblem<ParameterType>> optimisationProblem) noexcept {
    plausibility_ = 0.0;

    analyseImplementation(optimisationProblem);
  }

  template <typename ParameterType, class DistanceFunction>
  double PropertiesAnalysis<ParameterType, DistanceFunction>::getPlausibility() const noexcept {
    return plausibility_;
  }

  //! ALL METHODS SHOULD BE EITHER PROTECTED OR PRIVATE FROM HERE ON
  //! Note: Runtime checks are only performed for public methods.

  // Nothing to see here, move along ...
}