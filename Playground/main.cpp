
#include <Windows.h>

#include "Base/Tools.h"

#include "GameEngine/Core.h"


int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
{
   Core* core = nullptr;

   Base::ScopeGuard guard([&core] () { SecureDelete(core); });

   try {
      core           = Core::Instance();
      auto graphics  = core->Graphics();
      auto input     = core->Input();
      auto audio     = core->Audio();
      auto resources = core->Resources();
      auto keyboard  = input->Keyboard();

      core->WindowTitle("GameEngine 0.1.0");

      resources->AddBinary("music", "../resources/audio/music/music.ogg");

      audio->Add("music",  resources->Binary("music"));
      audio->Play("music", true);

      while (core->IsRunning() && !keyboard->KeyReleased(27)) {   // TODO
         graphics->BeginScene();
         {
            graphics->Text(10, 10, "Hello World!");
         }
         graphics->EndScene();
      }
   }
   catch (std::exception& e) {
      std::string err = "Unhandeled exception caught in main loop!\n\n";
      err += e.what();
      err += "\n\nShutting down program.";

      ShowError(err.c_str());
      return 5;
   }
   catch (...) {
      ShowError("Unhandled exception caught in main loop!\n\nShutting down program.");
      return 9;
   }

   return 0;
}

