
#include "Base/Tools.h"
#include "Base/Convert.h"

#include "GameEngine/Core.h"

using namespace ge;


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

      resources->AddMusic("music", "../resources/audio/music/music.ogg");

      graphics->AddTexture("image", "../resources/graphics/textures/image.png");

      audio->Add("music", resources->Music("music"));
      audio->Add("piano", "../resources/audio/music/piano.ogg");

      audio->DefaultVolume("piano", 0);

      audio->PlayMusic("music", true);
      audio->PlayMusic("piano", true);

      bool paused = false;

      while (core->IsRunning()) {
         if (core->IsWindowActive()) {
            if (keyboard->Key(27)) core->Quit();

            if (mouse->Clicked(LEFT_BUTTON)) {
               paused = !paused;
               audio->PauseMusic(paused);
            }

            if (mouse->Clicked(RIGHT_BUTTON)) {
               audio->StopMusic();
            }

            if (mouse->WheelMoved()) {
               audio->MusicVolume("music", audio->MusicVolume("music") - (int)mouse->DWheel());
               audio->MusicVolume("piano", audio->MusicVolume("piano") + (int)mouse->DWheel());
            }

            graphics->BeginScene();
            {
               graphics->DrawTexture("image", ge::Rectangle(300, 100, 310, 110));
               graphics->DrawTexture("image", ge::Rectangle(310, 110, 360, 160));
               graphics->DrawTexture("image", ge::Rectangle(360, 160, 620, 320));

               graphics->DrawBox(5, 5, 160, 235);

               graphics->Text(10, 10, "Filename: " + audio->FileName("music"));
               graphics->Text(10, 25, "Master Volume: " + base::AsString(audio->MasterVolume()) + " %");
               graphics->Text(10, 40, "Default Volume: " + base::AsString(audio->DefaultVolume("music")) + " %");

               graphics->Log(10, 65, "Source Playing: " + base::AsString(audio->IsPlaying("music")));

               graphics->Text(10, 90,  "Music Paused: " + base::AsString(audio->IsMusicPaused("music")));
               graphics->Text(10, 105, "Music Looped: " + base::AsString(audio->IsMusicLooped("music")));
               graphics->Text(10, 120, "Music Finished: " + base::AsString(audio->IsMusicFinished("music")));

               graphics->Log(10, 145, "Music Volume: " + base::AsString(audio->MusicVolume("music")) + " %");
               graphics->Log(10, 160, "Music Speed: " + base::AsString(audio->MusicSpeed("music")) + " %");
               graphics->Log(10, 175, "Music Pan: " + base::AsString(audio->MusicPan("music")) + " %");

               graphics->Text(10, 200, "Music Length: " + base::AsString(audio->MusicLength("music")));
               graphics->Text(10, 215, "Music Position: " + base::AsString(audio->MusicPosition("music")));
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

