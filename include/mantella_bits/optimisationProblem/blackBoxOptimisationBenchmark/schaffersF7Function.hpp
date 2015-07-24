namespace mant {
  namespace bbob {
    template <typename T = double>
    class SchaffersF7Function : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "The parameter type T must be a floating point type.");
    
      public:
        explicit SchaffersF7Function(
            const std::size_t numberOfDimensions) noexcept;

        void setRotationQ(
            const arma::Mat<T>& rotationQ);

        std::string toString() const noexcept override;

        // The type is intentionally fixed to ease usage with MPI_DOUBLE.
        std::vector<double> serialise() const noexcept;

        // The type is intentionally fixed to ease usage with MPI_DOUBLE.
        void deserialise(
            std::vector<double> serialisedOptimisationProblem);

      protected:
        const arma::Col<T> parameterConditioning_;

        arma::Mat<T> rotationQ_;

        double getSoftConstraintsValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

        double getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;
    };

    //
    // Implementation
    //

    template <typename T>
    SchaffersF7Function<T>::SchaffersF7Function(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions),
        parameterConditioning_(this->getParameterConditioning(std::sqrt(static_cast<T>(10.0L)))) {
      this->setParameterTranslation(this->getRandomParameterTranslation());
      this->setParameterRotation(getRandomRotationMatrix(this->numberOfDimensions_));
      setRotationQ(getRandomRotationMatrix(this->numberOfDimensions_));
    }

    template <typename T>
    void SchaffersF7Function<T>::setRotationQ(
        const arma::Mat<T>& rotationQ) {
      verify(rotationQ.n_rows == this->numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(isRotationMatrix(rotationQ), "The parameter must be a rotation matrix.");

      rotationQ_ = rotationQ;
    }

    template <typename T>
    double SchaffersF7Function<T>::getSoftConstraintsValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      return 10.0 * this->getBoundConstraintsValue(parameter);
    }

    template <typename T>
    double SchaffersF7Function<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      const arma::Col<T>& s = arma::square(parameterConditioning_ % (rotationQ_ * this->getAsymmetricParameter(static_cast<T>(0.5L), parameter)));
      const arma::Col<T>& z = arma::pow(s.head(s.n_elem - 1) + s.tail(s.n_elem - 1), static_cast<T>(0.25L));

      return std::pow(static_cast<double>(arma::mean(z % (static_cast<T>(1.0L) + arma::square(arma::sin(static_cast<T>(50.0L) * arma::pow(z, static_cast<T>(0.4L))))))), 2.0);
    }

    template <typename T>
    std::string SchaffersF7Function<T>::toString() const noexcept {
      return "bbob_schaffers_f7_function";
    }

#if defined(MANTELLA_USE_MPI)
    template <typename T>
    std::vector<double> SchaffersF7Function<T>::serialise() const noexcept {
      std::vector<double> serialisedOptimisationProblem = BlackBoxOptimisationBenchmark<T>::serialise();
      
      for(std::size_t n = 0; n < rotationQ_.n_elem; ++n) {
        serialisedOptimisationProblem.push_back(static_cast<double>(rotationQ_(n)));
      }
      
      return serialisedOptimisationProblem;
    }

    template <typename T>
    void SchaffersF7Function<T>::deserialise(
        std::vector<double> serialisedOptimisationProblem) {
      rotationQ_.set_size(this->numberOfDimensions_, this->numberOfDimensions_);
      for(std::size_t n = 0; n < rotationQ_.n_elem; ++n) {
        rotationQ_(n) = static_cast<T>(serialisedOptimisationProblem.back());
        serialisedOptimisationProblem.pop_back();
      }
        
      BlackBoxOptimisationBenchmark<T>::deserialise(serialisedOptimisationProblem);
    }
#endif
  }
}