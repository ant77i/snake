#include <raylib.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Grid Example");

    SetTargetFPS(60); // Set the desired frame rate (60 FPS)

    // Grid settings
    const Color gridColor = DARKGRAY;
    const int cellWidth = 50;
    const int cellHeight = 50;
    const int rows = screenHeight / cellHeight;
    const int cols = screenWidth / cellWidth;

    // Player settings
    int playerY = 4;
    int playerX = 7;
    const int updateRate = 20;
    Color squareColor = GREEN;

    enum directions {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    directions direction = NONE;

    int frameCounter = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Player movement
        if (IsKeyDown(KEY_UP)) {
            direction = UP;
        } else if (IsKeyDown(KEY_DOWN)) {
            direction = DOWN;
        } else if (IsKeyDown(KEY_LEFT)) {
            direction = LEFT;
        } else if (IsKeyDown(KEY_RIGHT)) {
            direction = RIGHT;
        }

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

        // Draw colored square
        DrawRectangle(playerX * cellWidth, playerY * cellHeight, cellWidth, cellHeight, squareColor);

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
