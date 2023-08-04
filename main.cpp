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

    // Colored square position
    int coloredRow = 4;
    int coloredCol = 7;
    Color squareColor = RED;

    int cooldown = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (cooldown > 0) {
            cooldown--;
            continue;;
        }

        // Player movement
        if (IsKeyDown(KEY_UP)) {
            if (coloredRow > 0) {
                coloredRow--;
                cooldown = 10000;
            }
        } else if (IsKeyDown(KEY_DOWN)) {
            if (coloredRow < rows - 1) {
                coloredRow++;
                cooldown = 10000;
            }
        } else if (IsKeyDown(KEY_LEFT)) {
            if (coloredCol > 0) {
                coloredCol--;
                cooldown = 10000;
            }
        } else if (IsKeyDown(KEY_RIGHT)) {
            if (coloredCol < cols - 1) {
                coloredCol++;
                cooldown = 10000;
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
        DrawRectangle(coloredCol * cellWidth, coloredRow * cellHeight, cellWidth, cellHeight, squareColor);

        // End double buffering
        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
