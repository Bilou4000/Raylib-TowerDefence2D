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
int waveCount = 0;

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

    startMusic = LoadMusicStream("resources/Albedo.mp3");
    mainMusic = LoadMusicStream("resources/PLvsAA.mp3");
    endMusic = LoadMusicStream("resources/Bastion.mp3");
}

void Update()
{
    float deltaTime = GetFrameTime();

    switch (currentScreen)
    {
        case MENU:
        {
            StopMusicStream(endMusic);

            PlayMusicStream(startMusic);
            UpdateMusicStream(startMusic);

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            PlayMusicStream(mainMusic);
            UpdateMusicStream(mainMusic);

            StopMusicStream(endMusic);

            ending = gameManager.Update(deltaTime);
            waveCount = gameManager.GetWavesCount();

            if (ending)
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            StopMusicStream(mainMusic);

            PlayMusicStream(endMusic);
            UpdateMusicStream(endMusic);

            gameManager.ResetGame();

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
        }
        break;
        case GAMEPLAY:
        {
            gameManager.Draw();
        }
        break;
        case ENDING:
        {
            DrawText("GAME OVER", (GetScreenWidth() / 2) - (MeasureText("GAME OVER", 150) / 2), 100, 150, RED);

            DrawText("WAVE", (GetScreenWidth() / 2) - (MeasureText("WAVE", 100) / 2), 300, 100, ORANGE);
            DrawText(TextFormat("%i", waveCount), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%i", waveCount), 75) / 2), 400, 75, BLACK);

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