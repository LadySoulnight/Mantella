namespace mant {
  namespace bbob {
    template <typename T = double>
    class BuecheRastriginFunction : public BlackBoxOptimisationBenchmark<T> {
      static_assert(std::is_floating_point<T>::value, "T must be a floating point type.");
    
      public:
        explicit BuecheRastriginFunction(
            const std::size_t numberOfDimensions) noexcept;

        std::string toString() const noexcept override;

      protected:
        const arma::Col<T> parameterConditioning_;

        T getSoftConstraintsValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

        T getObjectiveValueImplementation(
            const arma::Col<T>& parameter) const noexcept override;

#if defined(MANTELLA_USE_PARALLEL)
        friend class cereal::access;
        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<BuecheRastriginFunction>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(construct.ptr())));
        }
#endif
    };

    //
    // Implementation
    //

    template <typename T>
    BuecheRastriginFunction<T>::BuecheRastriginFunction(
        const std::size_t numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark<T>(numberOfDimensions),
        parameterConditioning_(this->getParameterConditioning(std::sqrt(static_cast<T>(10.0L)))) {
      arma::Col<T> parameterTranslation = this->getRandomParameterTranslation();
      for (std::size_t n = 0; n < parameterTranslation.n_elem; n += 2) {
        parameterTranslation(n) = std::abs(parameterTranslation(n));
      }
      this->setParameterTranslation(parameterTranslation);
    }

    template <typename T>
    T BuecheRastriginFunction<T>::getSoftConstraintsValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      return static_cast<T>(100.0L) * this->getBoundConstraintsValue(parameter);
    }

    template <typename T>
    T BuecheRastriginFunction<T>::getObjectiveValueImplementation(
        const arma::Col<T>& parameter) const noexcept {
      arma::Col<T> z = parameterConditioning_ % this->getOscillatedParameter(parameter);
      for (std::size_t n = 0; n < z.n_elem; n += 2) {
        if (z(n) > static_cast<T>(0.0L)) {
          z(n) *= static_cast<T>(10.0L);
        }
      }

      return static_cast<T>(10.0L) * (static_cast<T>(this->numberOfDimensions_) - arma::accu(arma::cos(static_cast<T>(2.0L) * arma::datum::pi * z))) + std::pow(arma::norm(z), static_cast<T>(2.0L));
    }

    template <typename T>
    std::string BuecheRastriginFunction<T>::toString() const noexcept {
      return "bbob_bueche_rastrigin_function";
    }
  }
}
