#include "raylib.h"
#include <iostream>

#include "GameManager.h";

using namespace std;

typedef enum GameScreen { MENU, STARTOFGAMEPLAY, GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen;
GameManager gameManager;

Music startMusic;
Music mainMusic;
Music endMusic;

Texture2D firstCarTexture;
Texture2D secondCarTexture;

//Variable
int screenWidth = 1280;
int screenHeight = 720;

bool ending = false;
float gameTime = 0;

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
    InitWindow(screenWidth, screenHeight, "Racing Car");
    currentScreen = MENU;
    SetTargetFPS(60);

    InitAudioDevice();
    gameManager.Init();

    startMusic = LoadMusicStream("resources/ForzaHorizon.mp3");
    mainMusic = LoadMusicStream("resources/Odesza.mp3");
    endMusic = LoadMusicStream("resources/Pyre.mp3");

    firstCarTexture = LoadTexture("resources/car_green_3.png");
    secondCarTexture = LoadTexture("resources/car_red_5.png");
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
                currentScreen = STARTOFGAMEPLAY;
            }
        }
        break;
        case STARTOFGAMEPLAY:
        {
            StopMusicStream(startMusic);
            StopMusicStream(endMusic);

            PlayMusicStream(mainMusic);
            UpdateMusicStream(mainMusic);

            gameManager.StartRace();

            if (gameManager.StartRace())
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            PlayMusicStream(mainMusic);
            UpdateMusicStream(mainMusic);

            ending = gameManager.Update(deltaTime);
            gameTime = gameManager.GetTimer();

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

            gameManager.ResetTimer();

            if (IsKeyPressed(KEY_R))
            {
                currentScreen = STARTOFGAMEPLAY;
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
            DrawText("Car Game 2D", (GetScreenWidth() / 2) - (MeasureText("Car Game 2D", 100) / 2), GetScreenHeight() / 3, 100, RED);
            DrawText("Press ENTER to PLAY", (GetScreenWidth() / 2) - (MeasureText("Press ENTER to PLAY", 50) / 2), 400, 50, GRAY);

            DrawTextureEx(firstCarTexture, { 200, 100 }, 45, 2, WHITE);
            DrawTextureEx(secondCarTexture, { 1000, 400 }, -20, 1.5f, WHITE);
        }
        break;
        case STARTOFGAMEPLAY:
        {
            gameManager.Draw();
            gameManager.DrawStartRace();
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

            DrawText("TIME", (GetScreenWidth() / 2) - (MeasureText("TIME", 100) / 2), 300, 100, ORANGE);
            DrawText(TextFormat("%.2fs", gameTime), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%.2fs", gameTime), 75) / 2), 400, 75, BLACK);


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