
#pragma once

#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputGamepad.h"

#include "DLL_DEF.h"

namespace OIS {
   class InputManager;
}


namespace ge {

   /// @brief Input-Basisklasse, verwaltet alle Input-Komponenten zur Behandlung
   /// von Eingabegeräten. Wird über Core::Input() geliefert.
   class GEDLL InputCore
   {
   public:
      /// @brief Auflistung der möglichen Komponentenangaben zur Verwemdung mit
      /// InputCore::Reset() oder InputCore::ShutDown().
      enum What {
         NoInterface       = 0,
         KeyboardInterface = 1,
         MouseInterface    = 2,
         GamepadInterface  = 4,
         AllInterfaces     = 7
      };

   private:
      OIS::InputManager* input;

      std::unique_ptr<InputKeyboard> keyboard;
      std::unique_ptr<InputMouse>    mouse;
      std::unique_ptr<InputGamepad>  gamepad;

      void Init (HWND window);

   public:
      /// @brief Konstruktor. Benötigt ein valides Window-Handle (wird
      /// automatisch bei der Initialisierung über Core übergeben).
      InputCore (HWND window);

      /// @brief Destruktor. Entfernt automatisch alle noch bestehenden
      /// Input-Komponenten und gibt Ressourcen frei, die innerhalb von
      /// InputCore oder einer in InputCore gehaltenen Input-Komponente
      /// erreichbar sind.
      virtual ~InputCore ();

      /// @brief Aktualisiert den Eingabestatus aller vorhandenen und
      /// eingeschalteten Input-Komponenten.
      void Update ();


      /// @brief Setzt eine oder mehrere Input-Komponenten zurück. Dies
      /// beinhaltet die Freigabe der Ressourcen, die in den entsprechenden
      /// Komponenten gehalten werden.
      /// @param what Komponentenangabe aus InputCore::What
      InputCore& Reset (const What& what);

      /// @brief Entfernt eine oder mehrere Input-Komponenten. Dies beinhaltet
      /// die Freigabe der Ressourcen, die in den entsprechenden Komponenten
      /// gehalten werden.
      /// @param what Komponentenangabe aus InputCore::What
      InputCore& ShutDown (const What& what);


      /// @brief Liefert den Pointer zur Komponente für Taststur-Eingaben.
      InputKeyboard* Keyboard () { if (keyboard == nullptr) Reset(KeyboardInterface); return keyboard.get(); }

      /// @brief Liefert den Pointer zur Komponente für Maus-Eingaben.
      InputMouse* Mouse () { if (mouse == nullptr) Reset(MouseInterface); return mouse.get(); }

      /// @brief Liefert den Pointer zur Komponente für Gamepad-Eingaben.
      InputGamepad* Gamepad () { if (gamepad == nullptr) Reset(GamepadInterface); return gamepad.get(); }
   };

}

