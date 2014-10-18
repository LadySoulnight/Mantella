#include <cstdlib>
#include <memory>
#include <string>
#include <array>
#include <ostream>

#include <armadillo>

#include <boost/filesystem.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>

#include <hop>

int main(const int argc, const char* argv[]) {
  
  if (argc < 8) {
    // TODO Add exception
  }

  std::shared_ptr<hop::OptimisationProblem> optimisationProblem;
  if(hop::endsWith(argv[1], ".serialised")) {
    std::ifstream input(argv[1]); {
      cereal::JSONInputArchive archive(input);
      archive(optimisationProblem);
    } input.close();
  } else {
    unsigned int optimisationProblemIndex = std::stoi(argv[1]);
    unsigned int numberOfDimensions = 2;

    std::array<std::shared_ptr<hop::OptimisationProblem>, 24> optimisationProblems({
      std::shared_ptr<hop::OptimisationProblem>(new hop::SphereFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::EllipsoidalFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::RastriginFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::BuecheRastriginFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::LinearSlope(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::AttractiveSectorFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::StepEllipsoidalFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::RosenbrockFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::RosenbrockFunctionRotated(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::EllipsoidalFunctionRotated(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::DiscusFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::BentCigarFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::SharpRidgeFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::DifferentPowersFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::RastriginFunctionRotated(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::WeierstrassFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::SchaffersF7Function(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::SchaffersF7FunctionIllConditioned(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::CompositeGriewankRosenbrockFunctionF8F2(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::SchwefelFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::GallaghersGaussian101mePeaksFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::GallaghersGaussian21hiPeaksFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::KatsuuraFunction(numberOfDimensions)),
      std::shared_ptr<hop::OptimisationProblem>(new hop::LunacekBiRastriginFunction(numberOfDimensions)),
    });

    optimisationProblem = optimisationProblems.at(optimisationProblemIndex);
  }

  double xAxisLowerBound = std::stod(argv[2]);
  double xAxisUpperBound = std::stod(argv[3]);
  unsigned int xAxisSize = std::stoi(argv[4]);

  arma::Col<double> xAxis = arma::linspace(xAxisLowerBound, xAxisUpperBound, xAxisSize);

  double yAxisLowerBound = std::stod(argv[5]);
  double yAxisUpperBound = std::stod(argv[6]);
  unsigned int yAxisSize = std::stoi(argv[7]);

  arma::Col<double> yAxis = arma::linspace(yAxisLowerBound, yAxisUpperBound, yAxisSize);


  boost::filesystem::path filepath = boost::filesystem::path(
    "./fitnessFunctionGrid_" +
    hop::to_string(optimisationProblem) +
    "_x" +
    std::to_string(xAxisLowerBound) +
    "," +
    std::to_string(xAxisUpperBound) +
    "," +
    std::to_string(xAxisSize) +
    "_y" +
    std::to_string(yAxisLowerBound) +
    "," +
    std::to_string(yAxisUpperBound) +
    "," +
    std::to_string(yAxisSize) +
    ".serialised");

  if(boost::filesystem::exists(filepath)) {
    // TODO Add exception
  }

  std::ofstream output(filepath.string()); {
    cereal::JSONOutputArchive archive(output);
    archive(optimisationProblem);
  } output.close();

  for (auto x : xAxis) {
    for (auto y : yAxis) {
      std::cout << "f(" << x << ", " << y << ") = " << optimisationProblem->getObjectiveValue({x, y}) << std::endl;
    }
  }

  return EXIT_SUCCESS;
}