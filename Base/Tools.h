
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace base {

   /// @brief Hilfsklasse zur Sicherstellung, dass eine bestimmte Funktion
   /// sp�testens bei der Zerst�rung des Objektes ausgef�hrt wird.
   ///
   /// Diese Objekte k�nnen beispielsweise dort angewendet werden, wo am Ende
   /// eines Vorgangs bestimmte Ressourcen wieder freigegeben werden m�ssen,
   /// ungeachtet des Ausstiegspunktes und vor allem auch im Fehlerfall. Wo
   /// es kein Objekt gibt, dessen Destruktor f�r die Abarbeitung genutzt
   /// werden kann, oder wenn der auszuf�hrende Code f�r einen Destruktor
   /// ungeeignet ist, kann stattdessen ein ScopeGuard-Objekt verwendet werden.
   class ScopeGuard
   {
      std::function<void()> releaser;

   public:
      /// @brief Konstruktor.
      /// @param releaser Funktion, die sp�testens bei der Zerst�rung des
      /// Objektes ausgef�hrt werden soll
      ScopeGuard (const std::function<void()>& releaser) : releaser(releaser) { }

      /// @brief Destruktor.
      ///
      /// F�hrt die angegebene Release-Funktion aus, wenn diese nicht schon
      /// vorher durch Aufruf von Release() abgearbeitet wurde. Wenn die
      /// Methode Clear() verwendet wurde, wird ebenfalls kein zus�tzlicher
      /// Code mehr ausgef�hrt.
      ~ScopeGuard () { Release(); }


      /// @brief Setzt die Release-Funktion.
      void Releaser (const std::function<void()>& val) { releaser = val; }

      /// @brief F�hrt die Release-Funktion aus, sofern definiert.
      ///
      /// Wenn nach dem Aufruf von Release() keine weitere Funktionszuweisung
      /// �ber Releaser() mehr erfolgt, wird bei der Zerst�rung des Objektes
      /// kein zus�tzlicher Code mehr ausgef�hrt. Gleiches gilt nach Verwendung
      /// der Methode Clear().
      void Release () { if (releaser != nullptr) releaser(); Clear(); }

      /// @brief Entfernt die Release-Funktion. Wird nun Release() aufgerufen
      /// oder das Objekt zerst�rt, wird kein zus�tzlicher Code mehr ausgef�hrt,
      /// wenn nicht zuvor eine andere Release-Funktion �ber die Methode
      /// Releaser() angegeben wurde.
      void Clear () { releaser = nullptr; }
   };

}

