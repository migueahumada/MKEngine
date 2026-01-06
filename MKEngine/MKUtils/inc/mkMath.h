#include "PrerequisitesUtils.h"
#include <type_traits>

template<typename Real>
class mkVector3_T {

public:
  mkVector3_T() = default;
  ~mkVector3_T() = default;

  NODISCARD inline mkVector3_T operator+(const mkVector3_T& other) const
  {
    return {x + other.x,
            y + other.y, 
            z + other.z);
  }

  NODISCARD inline mkVector3_T operator-(const mkVector3_T& other) const
  {
    return {x - other.x, 
            y - other.y, 
            z - other.z};
  }

  NODISCARD inline mkVector3_T operator*(Real scalar) const
  {
    return {scalar * x,
            scalar * y,
            scalar * z};
  }

  NODISCARD const Real getMagnitude()
  {
    Real inside = x*x + y*y + z*z;

    return sqrt(inside);
  }

  Real x {0};
  Real y {0};
  Real z {0};



};