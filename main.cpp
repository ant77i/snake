#include <raylib.h>
#include <iostream>
#include <random>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(screenWidth, screenHeight, "Grid Example");

    SetTargetFPS(60); // Set the desired frame rate (60 FPS)

    // Grid settings
    const int cellSize = 50;
    const int COLS = screenWidth / cellSize;
    const int ROWS = screenHeight / cellSize;
    const Color GRIDCOLOR = DARKGRAY;

    // Random setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomCol(0, 15);
    std::uniform_int_distribution<> randomRow(0, 11);

    // Player settings
    int playerX = randomCol(gen);
    int playerY = randomRow(gen);
    const int updateRate = 20;
    Color PLAYERCOLOR = GREEN;

    // Food settings
    int foodX = randomCol(gen);
    int foodY = randomRow(gen);
    Color FOODCOLOR = RED;

    enum directions {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    directions direction = NONE;

    int frameCounter = 0;

    struct Segment {
        int x, y;
    };

    class Snake {
    public:
        Snake(int startX, int startY, int initialLength) {
            for (int i = 0; i < initialLength; ++i) {
                body.push_back({startX - i, startY});
            }
        }

        void move(int newX, int newY) {
            // Update the position of each segment
            for (int i = body.size() - 1; i > 0; --i) {
                body[i] = body[i - 1];
            }
            body[0] = {newX, newY};
        }

        void grow() {
            // Add a new segment at the end of the body
            int lastX = body.back().x;
            int lastY = body.back().y;
            int newX = lastX + (lastX - body[body.size() - 2].x);
            int newY = lastY + (lastY - body[body.size() - 2].y);
            body.push_back({lastX, lastY});
        }

        const std::vector<Segment>& getBody() const {
            return body;
        }

    private:
        std::vector<Segment> body;
    };

    Snake snake(COLS/2, ROWS/2, 3);

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

        // Movement change
        if (frameCounter % updateRate == 0) {
            switch (direction) {
                case UP:
                    if (playerY <= 0) break;
                    playerY--;
                    break;
                case DOWN:
                    if (playerY >= ROWS - 1) break;
                    playerY++;
                    break;
                case LEFT:
                    if (playerX <= 0) break;
                    playerX--;
                    break;
                case RIGHT:
                    if (playerX >= COLS - 1) break;
                    playerX++;
                    break;
                case NONE:
                    direction = NONE;
            };
        };

        snake.move(playerX, playerY);

        // Begin double buffering
        BeginDrawing();

        // Clear the back buffer
        ClearBackground(RAYWHITE);

        // Draw grid lines
        for (int i = 0; i <= ROWS; i++) {
            DrawLine(0, i * cellSize, screenWidth, i * cellSize, GRIDCOLOR);
        };
        for (int i = 0; i <= COLS; i++) {
            DrawLine(i * cellSize, 0, i * cellSize, screenHeight, GRIDCOLOR);
        };

        // Draw player
        const std::vector<Segment>& snakeBody = snake.getBody();
        for (const auto& segment: snakeBody) {
            DrawRectangle(segment.x * cellSize, segment.y * cellSize, cellSize, cellSize, PLAYERCOLOR);
        };

        if (playerX == foodX && playerY == foodY) {
            snake.grow();
            foodX = randomCol(gen);
            foodY = randomRow(gen);
        } else {
            DrawRectangle(foodX * cellSize, foodY * cellSize, cellSize, cellSize, FOODCOLOR);
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
