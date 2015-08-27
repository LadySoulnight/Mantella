#include <mantella_bits/surrogateModel.hpp>

namespace mant {
  SurrogateModel::SurrogateModel(
      const std::unordered_map<arma::Col<double>, double, Hash, IsEqual>& samples) 
    : OptimisationProblem(samples.cbegin()->first.n_elem),
      samples_(samples) {
      
  }
  
  void SurrogateModel::model() {
    modelImplementation();
  }
}