#include <raylib.h>
#include <iostream>
#include <random>
#include <list>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Grid Example");

    SetTargetFPS(60); // Set the desired frame rate (60 FPS)

    // Grid settings
    const int cellWidth = 50;
    const int cellHeight = 50;
    const int cols = screenWidth / cellWidth;
    const int rows = screenHeight / cellHeight;
    const Color gridColor = DARKGRAY;

    // Random setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomCol(0, 15);
    std::uniform_int_distribution<> randomRow(0, 11);

    // Player settings
    int playerX = randomCol(gen);
    int playerY = randomRow(gen);
    const int updateRate = 20;
    Color squareColor = GREEN;

    // Food settings
    int foodX = randomCol(gen);
    int foodY = randomRow(gen);
    Color foodColor = RED;

    enum directions {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    std::list<directions> playerBody;

    directions direction = NONE;

    int frameCounter = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Player movement
        if (IsKeyDown(KEY_UP) && direction != DOWN) {
            direction = UP;
        } else if (IsKeyDown(KEY_DOWN) && direction != UP) {
            direction = DOWN;
        } else if (IsKeyDown(KEY_LEFT) && direction != RIGHT) {
            direction = LEFT;
        } else if (IsKeyDown(KEY_RIGHT) && direction != LEFT) {
            direction = RIGHT;
        }

        playerBody.front() = direction;

        // Movement change
        if (frameCounter % updateRate == 0) {
            switch (direction) {
                case UP:
                    if (playerY <= 0) break;
                    playerY--;
                    break;
                case DOWN:
                    if (playerY >= rows - 1) break;
                    playerY++;
                    break;
                case LEFT:
                    if (playerX <= 0) break;
                    playerX--;
                    break;
                case RIGHT:
                    if (playerX >= cols - 1) break;
                    playerX++;
                    break;
                case NONE:
                    direction = NONE;
            }
        }

        // Begin double buffering
        BeginDrawing();

        // Clear the back buffer
        ClearBackground(RAYWHITE);

        // Draw grid lines
        for (int i = 0; i <= rows; i++) {
            DrawLine(0, i * cellHeight, screenWidth, i * cellHeight, gridColor);
        }
        for (int i = 0; i <= cols; i++) {
            DrawLine(i * cellWidth, 0, i * cellWidth, screenHeight, gridColor);
        }

        // Draw player
        DrawRectangle(playerX * cellWidth, playerY * cellHeight, cellWidth, cellHeight, squareColor);

        if (playerX == foodX && playerY == foodY) {
            playerBody.push_back(direction);
            foodX = randomCol(gen);
            foodY = randomRow(gen);
        } else {
            DrawRectangle(foodX * cellWidth, foodY * cellHeight, cellWidth, cellHeight, foodColor);
        }

        // End double buffering
        EndDrawing();

        frameCounter++;

        if (frameCounter >= 60) {
            frameCounter = 0;
        }
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
