
#pragma once

#include "DLL_DEF.h"


namespace base {

   /// @brief Liefert den Dezimal-Anteil eines float-Wertes.
   /// @param val float-Wert (z.B. 123.45f)
   /// @return Dezimal-Anteil (z.B. 0.45f)
   BASEDLL float Fraction (float val);

   /// @brief Liefert den Dezimal-Anteil eines double-Wertes.
   /// @param val double-Wert (z.B. 123.45)
   /// @return Dezimal-Anteil (z.B. 0.45)
   BASEDLL double Fraction (double val);

}

