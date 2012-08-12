
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

      std::vector<std::string> log;

      while (core->IsRunning()) {
         if (core->IsWindowActive()) {
            if (keyboard->Key(27)) core->Quit();

            if (mouse->Clicked(LEFT_BUTTON)) {
               log.push_back("CLICKED");
            }

            if (mouse->DoubleClicked(LEFT_BUTTON)) {
               log.push_back("DOUBLE CLICKED");
               core->MaximizeWindow();
            }

            if (mouse->TripleClicked(LEFT_BUTTON)) {
               log.push_back("TRIPLE CLICKED");
               core->MinimizeWindow();
            }

            graphics->BeginScene();
            {
               for (size_t i = 0; i < log.size(); ++i) {
                  graphics->Text(10, i * 10, log[i]);
               }
            }
            graphics->EndScene();

            input->Update();
         }
         else {
            core->DoNothing();
         }
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

