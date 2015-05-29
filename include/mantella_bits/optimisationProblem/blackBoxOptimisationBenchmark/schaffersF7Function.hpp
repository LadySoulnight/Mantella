namespace mant {
  namespace bbob {
    class SchaffersF7Function : public BlackBoxOptimisationBenchmark {
      public:
        inline explicit SchaffersF7Function(
            const unsigned int numberOfDimensions) noexcept;

        inline void setRotationQ(
            const arma::Mat<double>& rotationQ);

        inline std::string toString() const noexcept override;

      protected:
        const arma::Col<double> parameterConditioning_;

        arma::Mat<double> rotationQ_;

        inline double getSoftConstraintsValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

        inline double getObjectiveValueImplementation(
            const arma::Col<double>& parameter) const noexcept override;

#if defined(MANTELLA_USE_PARALLEL)
        friend class cereal::access;

        template <typename Archive>
        void serialize(
            Archive& archive) noexcept {
          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(this)));
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions_));
          archive(cereal::make_nvp("rotationQ", rotationQ_));
        }

        template <typename Archive>
        static void load_and_construct(
            Archive& archive,
            cereal::construct<SchaffersF7Function>& construct) noexcept {
          unsigned int numberOfDimensions;
          archive(cereal::make_nvp("numberOfDimensions", numberOfDimensions));
          construct(numberOfDimensions);

          archive(cereal::make_nvp("BlackBoxOptimisationBenchmark", cereal::base_class<BlackBoxOptimisationBenchmark>(construct.ptr())));
          archive(cereal::make_nvp("rotationQ", construct->rotationQ_));
        }
#endif
    };

    //
    // Implementation
    //

    inline SchaffersF7Function::SchaffersF7Function(
        const unsigned int numberOfDimensions) noexcept
      : BlackBoxOptimisationBenchmark(numberOfDimensions),
        parameterConditioning_(getParameterConditioning(std::sqrt(10.0))) {
      setParameterTranslation(getRandomParameterTranslation());
      setParameterRotation(getRandomRotationMatrix(numberOfDimensions_));
      setRotationQ(getRandomRotationMatrix(numberOfDimensions_));
    }

    inline void SchaffersF7Function::setRotationQ(
        const arma::Mat<double>& rotationQ) {
      verify(rotationQ.n_rows == numberOfDimensions_, "The number of rows must be equal to the number of dimensions");
      verify(isRotationMatrix(rotationQ), "The parameter must be a rotation matrix.");

      rotationQ_ = rotationQ;
    }

    inline double SchaffersF7Function::getSoftConstraintsValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      return 10.0 * getBoundConstraintsValue(parameter);
    }

    inline double SchaffersF7Function::getObjectiveValueImplementation(
        const arma::Col<double>& parameter) const noexcept {
      const arma::Col<double>& s = arma::square(parameterConditioning_ % (rotationQ_ * getAsymmetricParameter(0.5, parameter)));
      const arma::Col<double>& z = arma::pow(s.head(s.n_elem - 1) + s.tail(s.n_elem - 1), 0.25);

      return std::pow(arma::mean(z % (1.0 + arma::square(arma::sin(50.0 * arma::pow(z, 0.4))))), 2.0);
    }

    inline std::string SchaffersF7Function::toString() const noexcept {
      return "bbob_schaffers_f7_function";
    }
  }
}

#if defined(MANTELLA_USE_PARALLEL)
CEREAL_REGISTER_TYPE(mant::bbob::SchaffersF7Function);
#endif