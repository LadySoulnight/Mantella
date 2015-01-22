// Catch
#include <catch.hpp>

// C++ Standard Library
#include <cstdlib>
#include <string>

// Armadillo
#include <armadillo>

// Mantella
#include <mantella>

extern std::string testDirectory;

TEST_CASE("BBOB2015-StepEllipsoidalFunction", "") {
  for (const auto& numberOfDimensions : {2, 40}) {
    mant::bbob2015::StepEllipsoidalFunction stepEllipsoidalFunction(numberOfDimensions);

    arma::Mat<double> parameters;
    parameters.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/parameters,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> translation;
    translation.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/translation,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationR;
    rotationR.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/rotationR,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Mat<double> rotationQ;
    rotationQ.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/rotationQ,dim" + std::to_string(numberOfDimensions) +".mat");

    arma::Col<double> expected;
    expected.load(testDirectory + "/data/optimisationProblem/blackBoxOptimisationBenchmark2015/expectedStepEllipsoidalFunction,dim" + std::to_string(numberOfDimensions) +".mat");

    stepEllipsoidalFunction.setObjectiveValueTranslation(0);
    stepEllipsoidalFunction.setTranslation(translation);
    stepEllipsoidalFunction.setRotationR(rotationR);
    stepEllipsoidalFunction.setRotationQ(rotationQ);

    for (std::size_t n = 0; n < parameters.n_cols; ++n) {
      CHECK(stepEllipsoidalFunction.getObjectiveValue(parameters.col(n)) == Approx(expected.at(n)));
    }
  }
}
