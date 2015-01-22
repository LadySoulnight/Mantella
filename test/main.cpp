// Catch
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

// C++ Standard Library
#include <string>
#include <stdexcept>
#include <iostream>

// Mantella
#include <mantella>

std::string testDirectory;

int main(const int argc, const char* argv[]) {
  try {
    if (argc != 2) {
      throw std::invalid_argument("The location of the test directory must be added to the command line.");
    }

    testDirectory = argv[1];

    if (!mant::file_exists(testDirectory)) {
      throw std::invalid_argument("The speficied test directory (" + testDirectory + ") does not exists.");
    }

    mant::Rng::setSeed(1234567890);

    return Catch::Session().run();
  } catch(const std::exception& exception) {
    std::cout << exception.what();
  }
}
