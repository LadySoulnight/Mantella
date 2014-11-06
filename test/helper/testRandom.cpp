// Catch
#include <catch.hpp>

// C++ Standard Library
#include <cstdlib>
#include <cmath>

// Armadillo
#include <armadillo>

// HOP
#include <hop>

TEST_CASE("Random rotation matrix", "") {
  SECTION("2-dimensional rotation") {
    arma::Col<double>::fixed<10000> angles;
    for(std::size_t n = 0; n < angles.n_elem; ++n) {
      arma::Col<double>::fixed<2> rotatedUnitVector = hop::Random::getRandomRotationMatrix(2) * arma::Col<double>::fixed<2>({-2, 1});
      angles.at(n) = std::atan2(rotatedUnitVector.at(1), rotatedUnitVector.at(0));
    }

    arma::Col<arma::uword> histogram = arma::hist(angles);
    CHECK(0.05 > static_cast<double>(histogram.max() - histogram.min()) / angles.n_elem);
  }

  SECTION("3-dimensional rotation") {
    arma::Col<double>::fixed<10000> rollAngles;
    arma::Col<double>::fixed<10000> pitchAngles;
    arma::Col<double>::fixed<10000> yawAngles;
    for(std::size_t n = 0; n < rollAngles.n_elem; ++n) {
      arma::Col<double>::fixed<3> rotatedUnitVector = hop::Random::getRandomRotationMatrix(3) * arma::Col<double>::fixed<3>({-2, 1, 3});
      rollAngles.at(n) = std::atan2(rotatedUnitVector.at(1), rotatedUnitVector.at(0));
      pitchAngles.at(n) = std::atan2(rotatedUnitVector.at(2), rotatedUnitVector.at(1));
      yawAngles.at(n) = std::atan2(rotatedUnitVector.at(0), rotatedUnitVector.at(2));
    }

    arma::Col<arma::uword> histogram;

    histogram = arma::hist(rollAngles);
    CHECK(0.02 > static_cast<double>(histogram.max() - histogram.min()) / rollAngles.n_elem);

    histogram = arma::hist(pitchAngles);
    CHECK(0.02 > static_cast<double>(histogram.max() - histogram.min()) / pitchAngles.n_elem);

    histogram = arma::hist(yawAngles);
    CHECK(0.02 > static_cast<double>(histogram.max() - histogram.min()) / yawAngles.n_elem);
  }
}

TEST_CASE("Random permutation", "") {
  SECTION("Full permutation") {
    arma::Mat<arma::uword>::fixed<10, 10000> permutations;
    for(std::size_t n = 0; n < permutations.n_cols; ++n) {
      permutations.col(n) = hop::Random::getRandomPermutation(permutations.n_rows);
    }

    arma::Col<arma::uword> centers(permutations.n_rows);
    for(std::size_t n = 0; n < permutations.n_rows; ++n) {
      centers.at(n) = n;
    }

    for(std::size_t n = 0; n < permutations.n_rows; ++n) {
      arma::Row<arma::uword> histogram = arma::hist(permutations.row(n), centers);
      CHECK(0.05 > static_cast<double>(histogram.max() - histogram.min()) / permutations.n_cols);
    }
  }

  SECTION("Partial permutation") {
    arma::Mat<arma::uword>::fixed<10, 20000> permutations;
    for(std::size_t n = 0; n < permutations.n_cols; ++n) {
      permutations.col(n) = hop::Random::getRandomPermutation(permutations.n_rows + 1, permutations.n_rows);
    }

    arma::Col<arma::uword> centers(permutations.n_rows);
    for(std::size_t n = 0; n < permutations.n_rows; ++n) {
      centers.at(n) = n;
    }

    for(std::size_t n = 0; n < permutations.n_rows; ++n) {
      arma::Row<arma::uword> histogram = arma::hist(permutations.row(n), centers);
      CHECK(0.1 > static_cast<double>(histogram.max() - histogram.min()) / permutations.n_cols);
    }
  }
}
