#include "raylib.h"
#include <iostream>

#include "GameManager.h";

using namespace std;

typedef enum GameScreen { MENU, GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen;
GameManager gameManager;

Music startMusic;
Music mainMusic;
Music endMusic;

//Variable
int screenWidth = 1280;
int screenHeight = 850; //720

bool ending = false;

//Function
void Load();
void Update();
void Draw();
void Unload();


int main() {

    Load();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    Unload();
    return 0;
}


void Load()
{
    InitWindow(screenWidth, screenHeight, "Tower Defence 2D");
    currentScreen = MENU;
    SetTargetFPS(60);

    InitAudioDevice();
    gameManager.Init();

    startMusic = LoadMusicStream("resources/ForzaHorizon.mp3");
    mainMusic = LoadMusicStream("resources/Odesza.mp3");
    endMusic = LoadMusicStream("resources/Pyre.mp3");
}

void Update()
{
    float deltaTime = GetFrameTime();

    switch (currentScreen)
    {
        case MENU:
        {
            StopMusicStream(endMusic);

            //PlayMusicStream(startMusic);
            //UpdateMusicStream(startMusic);

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            //PlayMusicStream(mainMusic);
            //UpdateMusicStream(mainMusic);

            ending = gameManager.Update(deltaTime);

            if (ending)
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            StopMusicStream(mainMusic);

            //PlayMusicStream(endMusic);
            //UpdateMusicStream(endMusic);

            if (IsKeyPressed(KEY_R))
            {
                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                currentScreen = MENU;
            }
        }
        break;
        default: break;
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground({ LIGHTGRAY });

    switch (currentScreen)
    {
        case MENU:
        {
            DrawText("Tower Defence 2D", (GetScreenWidth() / 2) - (MeasureText("Tower Defence 2D", 100) / 2), GetScreenHeight() / 3, 100, RED);
            DrawText("Press ENTER to PLAY", (GetScreenWidth() / 2) - (MeasureText("Press ENTER to PLAY", 50) / 2), 400, 50, GRAY);

            //DrawTextureEx(firstCarTexture, { 200, 100 }, 45, 2, WHITE);
            //DrawTextureEx(secondCarTexture, { 1000, 400 }, -20, 1.5f, WHITE);
        }
        break;
        case GAMEPLAY:
        {
            gameManager.Draw();
        }
        break;
        case ENDING:
        {
            DrawText("Race Finished !", (GetScreenWidth() / 2) - (MeasureText("Race Finished !", 150) / 2), 100, 150, RED);

            DrawText("Press R to PLAY AGAIN", (GetScreenWidth() / 2) - (MeasureText("Press R to PLAY AGAIN", 40) / 2), 530, 40, GRAY);
            DrawText("Or Press M to go back to MENU", (GetScreenWidth() / 2) - (MeasureText("Or Press M to go back to MENU", 40) / 2), 620, 40, GRAY);
        }
        break;
        default: break;
    }

    EndDrawing();
}

void Unload()
{
    CloseAudioDevice();
    CloseWindow();
}