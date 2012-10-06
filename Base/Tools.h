
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace base {

   /// @brief Hilfsklasse zur Sicherstellung, dass eine bestimmte Funktion
   /// spätestens bei der Zerstörung des Objektes ausgeführt wird.
   ///
   /// Diese Objekte können beispielsweise dort angewendet werden, wo am Ende
   /// eines Vorgangs bestimmte Ressourcen wieder freigegeben werden müssen,
   /// ungeachtet des Ausstiegspunktes und vor allem auch im Fehlerfall. Wo
   /// es kein Objekt gibt, dessen Destruktor für die Abarbeitung genutzt
   /// werden kann, oder wenn der auszuführende Code für einen Destruktor
   /// ungeeignet ist, kann stattdessen ein ScopeGuard-Objekt verwendet werden.
   class ScopeGuard
   {
      std::function<void()> releaser;

   public:
      /// @brief Konstruktor.
      /// @param releaser Funktion, die spätestens bei der Zerstörung des
      /// Objektes ausgeführt werden soll
      ScopeGuard (const std::function<void()>& releaser) : releaser(releaser) { }

      /// @brief Destruktor.
      ///
      /// Führt die angegebene Release-Funktion aus, wenn diese nicht schon
      /// vorher durch Aufruf von Release() abgearbeitet wurde. Wenn die
      /// Methode Clear() verwendet wurde, wird ebenfalls kein zusätzlicher
      /// Code mehr ausgeführt.
      ~ScopeGuard () { Release(); }


      /// @brief Setzt die Release-Funktion.
      void Releaser (const std::function<void()>& val) { releaser = val; }

      /// @brief Führt die Release-Funktion aus, sofern definiert.
      ///
      /// Wenn nach dem Aufruf von Release() keine weitere Funktionszuweisung
      /// über Releaser() mehr erfolgt, wird bei der Zerstörung des Objektes
      /// kein zusätzlicher Code mehr ausgeführt. Gleiches gilt nach Verwendung
      /// der Methode Clear().
      void Release () { if (releaser != nullptr) releaser(); Clear(); }

      /// @brief Entfernt die Release-Funktion. Wird nun Release() aufgerufen
      /// oder das Objekt zerstört, wird kein zusätzlicher Code mehr ausgeführt,
      /// wenn nicht zuvor eine andere Release-Funktion über die Methode
      /// Releaser() angegeben wurde.
      void Clear () { releaser = nullptr; }
   };

}

