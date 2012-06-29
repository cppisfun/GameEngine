
#include "Precomp.h"

#include "Core.h"


int WINAPI WinMain (HINSTANCE instance, HINSTANCE, LPSTR, int)
{
   MSG msg    = { 0 };
   Core* core = nullptr;

   try {
      core           = Core::Instance(instance);
      auto graphics  = core->Graphics();
      auto input     = core->Input();
      auto audio     = core->Audio();
      auto resources = core->Resources();
      auto keyboard  = input->Keyboard();

      resources->AddBinary("music", "../resources/audio/music/Killer Tofu.ogg");

      audio->Add("music",     resources->Binary("music"));
      audio->Add("bell",      "../resources/audio/sound/bell.wav");
      audio->Add("explosion", "../resources/audio/sound/explosion.wav");

      audio->Play("music", true);

      while (msg.message != WM_QUIT) {
         if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
         else if (GetAsyncKeyState(VK_ESCAPE)) {
            PostQuitMessage(0);
         }
         else {
            input->Update();

            if (keyboard->KeyPressed())       audio->Play("bell");
            else if (keyboard->KeyReleased()) audio->Play("explosion");

            graphics->Begin();
            // do your thing
            graphics->End();
         }
      }
   }
   catch (std::exception& e) {
      std::string err = "Unhandeled exception caught in main loop!\n\n";
      err += e.what();
      err += "\n\nShutting down program.";

      ShowError(err.c_str());
   }

   SecureDelete(core);
   return static_cast<int>(msg.wParam);
}

