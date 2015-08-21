#include <mantella_bits/surrogateModel/quadraticFunctionModel.hpp>

namespace mant {
  QuadraticFunctionModel::QuadraticFunctionModel(
      const arma::Mat<double>& quadraticCoefficients,
      const arma::Col<double>& linearCoefficients,
      const double errorTerm) 
    : SurrogateModel(true, true),
      quadraticCoefficients_(quadraticCoefficients),
      linearCoefficients_(linearCoefficients),
      errorTerm_(errorTerm),
      hessian_(quadraticCoefficients_ + quadraticCoefficients_.t()) {
    
  }

  void QuadraticFunctionModel::modelImplementation() {
    // Nothing to do here
  }
      
  arma::Col<double> QuadraticFunctionModel::getJacobian(
      const arma::Col<double>& parameter) const {
    return arma::dot(hessian_, parameter);
  }

  arma::Mat<double> QuadraticFunctionModel::getHessian(
      const arma::Col<double>& parameter) const {
    return hessian_;
  }
  
  double QuadraticFunctionModel::getObjectiveValueImplementation(
      const arma::Col<double>& parameter) const {
    return arma::dot(parameter.t() * quadraticCoefficients_, parameter) + arma::dot(parameter, linearCoefficients_) + errorTerm_;
  }
  
  std::string QuadraticFunctionModel::toString() const {
    return "quadratic_function_model";
  }
}