
#include <Windows.h>

#include "Base/Tools.h"
#include "Base/Convert.h"

#include "GameEngine/Core.h"


int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
{
   Core* core = nullptr;

   base::ScopeGuard guard([&core] () { SecureDelete(core); });

   try {
      core           = Core::Instance();
      auto graphics  = core->Graphics();
      auto input     = core->Input();
      auto audio     = core->Audio();
      auto resources = core->Resources();
      auto keyboard  = input->Keyboard();
      auto mouse     = input->Mouse();

      core->WindowTitle("GameEngine 0.1.0");

      resources->AddBinary("music", "../resources/audio/music/music.ogg");

      audio->Add("music",  resources->Binary("music"));
      audio->Play("music", true);

      while (core->IsRunning()) {
         if (keyboard->Key(27)) break;

         graphics->BeginScene();
         {
            // drawing things goes here
         }
         graphics->EndScene();

         input->Update();
      }
   }
   catch (std::exception& e) {
      std::string err = "Unhandled exception caught in main loop!\n\n";
      err += e.what();
      err += "\n\nProgram will be shut down.";

      ShowError(err.c_str());
      return 5;
   }
   catch (...) {
      ShowError("Unhandled exception caught in main loop!\n\nShutting down program.");
      return 9;
   }

   return 0;
}

