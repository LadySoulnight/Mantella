namespace mant {
  // Calculates a hash value for custom types.
  class Hash {
    public:
      inline std::size_t operator() (
          const arma::Col<double>& key) const noexcept;

      inline std::size_t operator() (
          const arma::Col<unsigned int>& key) const noexcept;
    };

  // Checks whether two keys of a custom type are equal.
  class IsEqual {
    public:
      inline bool operator() (
          const arma::Col<double>& firstKey,
          const arma::Col<double>& secondKey) const noexcept;

      inline bool operator() (
          const arma::Col<unsigned int>& firstKey,
          const arma::Col<unsigned int>& secondKey) const noexcept;
  };

  //
  // Implementation
  //

  inline std::size_t Hash::operator() (
    const arma::Col<double>& key) const noexcept {
    // Start with the hash of the first value ...
    std::size_t hashedKey = std::hash<double>()(key(0));

    // ... and add the hash value of all following values to it.
    // Note: This is adapted from the Boost library (boost::hash_combine).
    for (const double& value : key) {
      hashedKey ^= std::hash<double>()(value) + 0x9e3779b9 + (hashedKey << 6) + (hashedKey >> 2);
    }

    return hashedKey;
  }

  inline std::size_t Hash::operator() (
    const arma::Col<unsigned int>& key) const noexcept {
    // Start with the hash of the first value ...
    std::size_t hashedKey = std::hash<unsigned int>()(key(0));

    // ... and add the hash value of all following values to it.
    // Note: This is adapted from the Boost library (boost::hash_combine).
    for (const unsigned int& value : key) {
      hashedKey ^= std::hash<unsigned int>()(value) + 0x9e3779b9 + (hashedKey << 6) + (hashedKey >> 2);
    }

    return hashedKey;
  }

  inline bool IsEqual::operator() (
    const arma::Col<double>& firstKey,
    const arma::Col<double>& secondKey) const noexcept {
    // Returns true if all values of both column vectors are equal.
    // This will also check if both vectors have the same size.
    return arma::all(firstKey == secondKey);
  }

  inline bool IsEqual::operator() (
    const arma::Col<unsigned int>& firstKey,
    const arma::Col<unsigned int>& secondKey) const noexcept {
    // Returns true if all values of both column vectors are equal.
    // This will also check if both vectors have the same size.
    return arma::all(firstKey == secondKey);
  }
}