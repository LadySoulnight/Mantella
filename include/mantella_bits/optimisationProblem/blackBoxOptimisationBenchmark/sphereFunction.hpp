namespace mant {
  namespace bbob {
    template <typename T = double>
    class SphereFunction : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "The parameter type T must be a floating point type.");
    
      public:
        explicit SphereFunction(
            const std::size_t numberOfDimensions) noexcept;

        std::string toString() const noexcept override;

        // The type is intentionally fixed to ease usage with MPI_DOUBLE.
        std::vector<double> serialise() const noexcept;

        // The type is intentionally fixed to ease usage with MPI_DOUBLE.
        void deserialise(
            std::vector<double> serialisedOptimisationProblem);

      protected:
        double getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;
    };

    //
    // Implementation
    //

    template <typename T>
    SphereFunction<T>::SphereFunction(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions) {
      this->setParameterTranslation(this->getRandomParameterTranslation());
    }

    template <typename T>
    double SphereFunction<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      return std::pow(static_cast<double>(arma::norm(parameter)), 2.0);
    }

    template <typename T>
    std::string SphereFunction<T>::toString() const noexcept {
      return "bbob_sphere_function";
    }
    
#if defined(MANTELLA_USE_MPI)
    template <typename T>
    std::vector<double> SphereFunction<T>::serialise() const noexcept {
      return BlackBoxOptimisationBenchmark<T>::serialise();
    }

    template <typename T>
    void SphereFunction<T>::deserialise(
        std::vector<double> serialisedOptimisationProblem) {
      BlackBoxOptimisationBenchmark<T>::deserialise(serialisedOptimisationProblem);
    }
#endif
  }
}