#include <hop_bits/optimisationAlgorithm/trajectoryBasedAlgorithm/simulatedAnnealing.hpp>

// C++ Standard Library
#include <cmath>

// HOP
#include <hop_bits/helper/rng.hpp>

namespace hop {
  SimulatedAnnealing::SimulatedAnnealing(
      const std::shared_ptr<OptimisationProblem> optimisationProblem)
    : TrajectoryBasedAlgorithm(optimisationProblem) {
    setMaximalStepSize((optimisationProblem->getUpperBounds() - optimisationProblem->getLowerBounds()) / 10);
  }

  void SimulatedAnnealing::optimiseImplementation() {
    arma::Col<double> candidateSolution;
    do {
      candidateSolution = arma::randu<arma::Col<double>>(optimisationProblem_->getNumberOfDimensions()) % (optimisationProblem_->getUpperBounds() - optimisationProblem_->getLowerBounds()) + optimisationProblem_->getLowerBounds();
    } while(!optimisationProblem_->isSatisfyingConstraints(candidateSolution));

    ++numberOfIterations_;
    arma::Col<double> state = candidateSolution;
    double objectiveValue = optimisationProblem_->getObjectiveValue(candidateSolution) + optimisationProblem_->getSoftConstraintsValue(candidateSolution);

    bestParameter_ = candidateSolution;
    bestObjectiveValue_ = objectiveValue;

    while(!isFinished() && !isTerminated()) {
      ++numberOfIterations_;

      arma::Col<double> candidateSolution;
      do {
        candidateSolution = state + maximalStepSize_ % arma::normalise(arma::randn<arma::Col<double>>(optimisationProblem_->getNumberOfDimensions())) * std::uniform_real_distribution<double>(0, 1)(Rng::generator);
      } while(!optimisationProblem_->isSatisfyingConstraints(candidateSolution));

      double objectiveValue = optimisationProblem_->getObjectiveValue(candidateSolution) + optimisationProblem_->getSoftConstraintsValue(candidateSolution);

      //TODO FIX THIS
//      if (objectiveValue < bestObjectiveValue_ || ) {
//        state = candidateSolution;
//        bestObjectiveValue_ = objectiveValue;
//      } else if (std::exp((objectiveValue - objectiveValue) / (numberOfIterations_ / maximalNumberOfIterations_)) < std::uniform_real_distribution<double>(0, 1)(Random::Rng)) {
//        state = candidateSolution;
//      }

//      if (objectiveValue < bestObjectiveValue_) {
//        bestSolution_ = candidateSolution;
//      }
    }
  }

  void SimulatedAnnealing::setMaximalStepSize(
      const arma::Col<double>& maximalStepSize) {
    maximalStepSize_ = maximalStepSize;
  }

  std::string SimulatedAnnealing::to_string() const {
    return "SimulatedAnnealing";
  }
}