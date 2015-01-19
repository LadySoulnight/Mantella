#pragma once

// Catch
#include <catch.hpp>

// C++ Standard Library
#include <vector>

// Armadillo
#include <armadillo>

template <typename ParameterType>
void compare(
    const std::vector<arma::Col<ParameterType>>& actual,
    const arma::Mat<ParameterType>& expected);

template <typename ParameterType>
void compare(
    const arma::Mat<ParameterType>& actual,
    const arma::Mat<ParameterType>& expected);

template <typename ParameterType>
void compare(
    const arma::Col<ParameterType>& actual,
    const arma::Col<ParameterType>& expected);

template <typename ParameterType>
void compare(
    const std::vector<arma::Col<ParameterType>>& actual,
    const arma::Mat<ParameterType>& expected) {
  CHECK(actual.size() == expected.n_cols);

  for(std::size_t n = 0; n < expected.n_cols; ++n) {
    compare<ParameterType>(actual.at(n), expected.col(n));
  }
}

template <typename ParameterType>
void compare(
    const arma::Mat<ParameterType>& actual,
    const arma::Mat<ParameterType>& expected) {
  CHECK(actual.n_cols == expected.n_cols);

  for(std::size_t n = 0; n < expected.n_cols; ++n) {
    compare(actual.col(n), expected.col(n));
  }
}

template <typename ParameterType>
void compare(
    const arma::Col<ParameterType>& actual,
    const arma::Col<ParameterType>& expected) {
  CHECK(actual.n_elem == expected.n_elem);

  for (std::size_t k = 0; k < expected.n_elem; ++k) {
    if(std::isfinite(expected.at(k))) {
      CHECK(actual.at(k) == Approx(expected.at(k)));
    } else {
      CHECK(actual.at(k) == expected.at(k));
    }
  }
}