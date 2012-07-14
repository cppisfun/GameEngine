
#include "Precomp.h"

#include "Numeric.h"
#include "Error.h"


namespace base {

   float Fraction (float val)   { return std::abs(val - boost::numeric_cast<float>(boost::numeric_cast<int>(val))); }
   double Fraction (double val) { return std::abs(val - boost::numeric_cast<double>(boost::numeric_cast<int>(val))); }

}

