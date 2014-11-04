
#include "Base/Tools.h"
#include "Base/Convert.h"

#include "GameEngine/Core.h"
#include "GameEngine/Box.h"

using namespace base;
using namespace ge;


int main ()
{
   try {
      auto core      = Core::Instance();
      auto graphics  = core->Graphics();
      auto input     = core->Input();
      auto audio     = core->Audio();
      auto resources = core->Resources();
      auto keyboard  = input->Keyboard();
      auto mouse     = input->Mouse();

      resources->AddMusic("music", "../resources/audio/music/music.ogg");

      graphics->AddTexture("image", "../resources/graphics/textures/texture.png");

      audio->Add("music", resources->Music("music"));
      audio->Add("piano", "../resources/audio/music/piano.ogg");

      audio->DefaultVolume("piano", 0);

      audio->PlayMusic("music", true);
      audio->PlayMusic("piano", true);

      bool paused = false;

      while (core->Running()) { // GAME LOOP - BEGIN
         if (keyboard->KeyReleased()) core->Quit();

         if (mouse->ButtonPressed(InputMouse::Button_Left)) {
            mouse->Show(paused);
            paused = !paused;
            audio->PauseMusic(paused);
         }

         if (mouse->ButtonPressed(InputMouse::Button_Right)) {
            if (audio->IsPlaying("music")) audio->StopMusic("music");
            else audio->PlayMusic("music", true);
         }

         if (mouse->WheelMoved()) {
            audio->MusicVolume("music", audio->MusicVolume("music") + mouse->DWheel());
            audio->MusicVolume("piano", audio->MusicVolume("piano") - mouse->DWheel());
         }

         graphics->BeginScene(); // DRAWING OPERATIONS - BEGIN
         {
            graphics->DrawTexture("image", Box(300, 100, 310, 110));
            graphics->DrawTexture("image", Box(310, 110, 360, 160));
            graphics->DrawTexture("image", Box(360, 160, 620, 320));

            graphics->FillRectangle(5, 5, 240, 320);
            graphics->DrawRectangle(5, 5, 240, 320);

            graphics->Text(10, 10, "Filename:       " + audio->FileName("music"));
            graphics->Text(10, 30, "Master Volume:  " + AsString(audio->MasterVolume()) + " %");
            graphics->Text(10, 50, "Default Volume: " + AsString(audio->DefaultVolume("music")) + " %");

            graphics->Log(10, 80, "Source Playing: " + AsString(audio->IsPlaying("music")));

            graphics->Text(10, 110, "Music Paused:   " + AsString(audio->IsMusicPaused("music")));
            graphics->Text(10, 130, "Music Looped:   " + AsString(audio->IsMusicLooped("music")));
            graphics->Text(10, 150, "Music Finished: " + AsString(audio->IsMusicFinished("music")));

            graphics->Log(10, 180, "Music Volume: " + AsString(audio->MusicVolume("music")) + " %");
            graphics->Log(10, 200, "Music Speed:  " + AsString(audio->MusicSpeed("music")) + " %");
            graphics->Log(10, 220, "Music Pan:    " + AsString(audio->MusicPan("music")) + " %");

            graphics->Text(10, 250, "Music Length:   " + AsString(audio->MusicLength("music")));
            graphics->Text(10, 270, "Music Position: " + AsString(audio->MusicPosition("music")));
         }
         graphics->EndScene(); // DRAWING OPERATIONS - END

         input->Update();
      } // GAME LOOP - END
   }
   catch (std::exception& e) {
      std::string err = "Unhandled exception caught in main loop!\n\n";
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

