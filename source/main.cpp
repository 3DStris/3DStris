#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <array>

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

using u32 = uint32_t;
using Color = u32;
using PieceShape = std::vector<bool>;

Color WHITE = C2D_Color32(255, 255, 255, 255);

struct Vector2 {
	float x;
	float y;
};

enum PieceType {I, O, L, J, S, T, Z, None};

namespace Colors {
    Color I = C2D_Color32(65, 175, 222, 255);
    Color O = C2D_Color32(247, 211, 62, 255);
    Color L = C2D_Color32(239, 149, 53, 255);
    Color J = C2D_Color32(25, 131, 191, 255);
    Color S = C2D_Color32(102, 198, 92, 255);
    Color T = C2D_Color32(180, 81, 172, 255);
    Color Z = C2D_Color32(239, 98, 77,  255);
}

std::array<Color, 7> colors{Colors::I, Colors::O, Colors::L, Colors::J, Colors::S, Colors::T, Colors::Z};

class Board {
    private:
        std::vector<PieceType> grid;
    public:
        int width;
        int height;

        Board(int width, int height) : width(width), height(height) {
            grid.resize(width * height, PieceType::None);
        }

        bool inside(int x, int y) {
            return x >= 0 && x < width && y >= 0 && y < height;
        }
        bool inside(Vector2 pos) {
            return inside(pos.x, pos.y);
        }

        void set(int x, int y, PieceType t) {
            if (inside(x, y)) grid[y * width + x] = t;
        }
        void set(Vector2 pos, PieceType t) {
            set(pos.x, pos.y, t);
        }

        PieceType get(int x, int y) {
            return grid[y * width + x];
        }
        PieceType get(Vector2 pos) {
            return get(pos.x, pos.y);
        }
        
        void draw(Vector2 origin, int tileSize) {
            // C2D_DrawRectLines??(origin.x, origin.y, width * tileSize, height * tileSize, WHITE);

            // for (int y = 1; y < height; ++y) {
            //     DrawLine(origin.x, origin.y + y * tileSize, origin.x + width * tileSize, origin.y + y * tileSize, {255, 255, 255, 100});
            // }
            // for (int x = 1; x < width; ++x) {
            //     DrawLine(origin.x + x * tileSize, origin.y, origin.x + x * tileSize, origin.y + height * tileSize, {255, 255, 255, 100});
            // }

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    PieceType p = get(x, y);
                    if (p != PieceType::None) {
                        C2D_DrawRectSolid(origin.x + x * tileSize, origin.y + y * tileSize, 0.0f,
                                          tileSize, tileSize, colors[p]);
                    }
                }
            }
        }

        void clearLines() {
            for (int y = 0; y < height; ++y) {
                bool line = true;
                for (int x = 0; x < width; ++x) {
                    if (get(x, y) == PieceType::None) {
                        line = false;
                        break;
                    }
                }
                if (line) {
                    for (int curY = y; curY >= 1; --curY) {
                        for (int x = 0; x < width; ++x) {
                            set(x, curY, curY == 1 ? PieceType::None : get(x, curY - 1));
                        }
                    }
                }
            }
        }
};

enum Direction {left, right, up, down};

class Piece {
    private:
        float fallTimer;
        PieceShape shape;
        int size;
        // Vector2 as they need one for left and right
        Vector2 dasTimer;
        float arr;
        float arrTimer;
        Board& board;
        float das;
        Color color;
    public:
        Vector2 pos;
        PieceType type;
        bool hasSet;

        Piece(Board& board, PieceShape shape, PieceType type) : board(board) {
            reset(shape, type);
        }

        void reset(PieceShape shape, PieceType type) {
            this->shape = shape;
            this->type = type;
            color = colors[type];
            size = std::sqrt(shape.size());
            pos = {std::floor(board.width / 2) - std::floor(size / 2), 0};
            fallTimer = 0.0f;
            hasSet = false;
            das = 0.138f;
            dasTimer = {0.0f, 0.0f};
            arr = 0.0f;
            arrTimer = arr;
        }

        void draw(Vector2 origin, int tileSize) {
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    if (shape[y * size + x]) {
                        C2D_DrawRectSolid(origin.x + (pos.x + x) * tileSize, origin.y + (pos.y + y) * tileSize, 0.0f,
                                      	  tileSize, tileSize, color);
                    }
                }
            }
        }

        void set() {
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    if (shape[y * size + x]) {
                        board.set(pos.x + x, pos.y + y, type);
                    }
                }
            }
            board.clearLines();
        }

        bool collides(int offX, int offY) {
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    Vector2 offPos = {pos.x + x + offX, pos.y + y + offY};
                    if (shape[y * size + x] && (!board.inside(offPos) || board.get(offPos) != PieceType::None)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool move(Direction dir) {
            float xOff = 0, yOff = 0;
            switch (dir) {
                case Direction::left:  xOff = -1; break;
                case Direction::right: xOff =  1; break;
                case Direction::up:    yOff = -1; break;
                case Direction::down:  yOff =  1; break;
            }
            if (!collides(xOff, yOff)) {
                pos.x += xOff;
                pos.y += yOff;
                return true;
            }
            return false;
        }

        void rotate(bool ccw) {
            PieceShape newShape;
            newShape.resize(size*size, false);
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    if (shape[y * size + x]) {
                        if (ccw) {
                            newShape[(size - x - 1) * size + y] = true;
                        } else {
                            newShape[x * size + size - y - 1] = true;
                        }
                    }
                }
            }
            shape = newShape;
        }

        void update(float dt, u32 kDown, u32 kHeld) {
            fallTimer += dt;
            if (fallTimer > 1.0f) {
                fallTimer = 0.0f;
                move(Direction::down);
            }

            if (kDown & KEY_UP) {
                while (move(Direction::down)) {}
                hasSet = true;
                set();
                return;
            }

            dasTimer.x = kHeld & KEY_LEFT  ? dasTimer.x + dt : 0.0f;
            dasTimer.y = kHeld & KEY_RIGHT ? dasTimer.y + dt : 0.0f;

            bool moved = false;

            if (dasTimer.x > das) {
                if (arr == 0.0f) {
                    while (move(Direction::left)) {}
                } else {
                    arrTimer -= dt;
                    if (arrTimer <= 0.0f) {
                        move(Direction::left);
                        arrTimer = arr;
                    }
                }
                moved = true;
            } else if (kDown & KEY_LEFT) {
                move(Direction::left);
                arrTimer = arr;
                moved = true;
            }

            if (dasTimer.y > das && !moved) {
                if (arr == 0.0f) {
                    while (move(Direction::right)) {}
                } else {
                    arrTimer -= dt;
                    if (arrTimer <= 0.0f) {
                        move(Direction::right);
                        arrTimer = arr;
                    }
                }
            } else if (kDown & KEY_RIGHT) {
                move(Direction::right);
                arrTimer = arr;
            }

            if (kDown & KEY_Y) rotate(true);
            if (kDown & KEY_B) rotate(false);
            
        }
};

namespace Shapes {
    PieceShape I = {
        0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    PieceShape J = {
        1, 0, 0,
        1, 1, 1,
        0, 0, 0
    };

    PieceShape L = {
        0, 0, 1,
        1, 1, 1,
        0, 0, 0
    };

    PieceShape O = {
        1, 1,
        1, 1
    };
    
    PieceShape S = {
        0, 1, 1,
        1, 1, 0,
        0, 0, 0
    };

    PieceShape T = {
        0, 1, 0,
        1, 1, 1,
        0, 0, 0
    };

    PieceShape Z = {
        1, 1, 0,
        0, 1, 1,
        0, 0, 0
    };
};

std::array<PieceShape, 7> shapes{Shapes::I, Shapes::O, Shapes::L, Shapes::J, Shapes::S, Shapes::T, Shapes::Z};

float randf() {
	return static_cast<float>(rand()) / RAND_MAX;
}

int main() {
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	Color colBg = C2D_Color32(34, 34, 34, 255);

	const int tileSize = (SCREEN_HEIGHT - 10)/20;

	std::array<PieceType, 7> pieces{PieceType::I, PieceType::O, PieceType::L, PieceType::J, PieceType::S, PieceType::T, PieceType::Z};

	Board board = Board(10, 20);
    Vector2 origin = {SCREEN_WIDTH / 2 - (board.width / 2) * tileSize, 25};

    for (int x = 3; x < board.width; ++x) {
        board.set(x, 19, PieceType::T);
    }

    Piece piece = Piece(board, shapes[PieceType::I], PieceType::I);
	float dt = 1.0f / 60.0f; // hardcoded because im too lazy to use std::chrono
	while (aptMainLoop()) {
		hidScanInput();

		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) {
			break; // goes back to hb menu
		}

		piece.update(dt, kDown, kHeld);

		if (piece.hasSet) {
            PieceType p = pieces[static_cast<int>(randf() * pieces.size())];
            piece.reset(shapes[p], p);
        }
		
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, colBg);
		C2D_SceneBegin(top);

		board.draw(origin, tileSize);
		piece.draw(origin, tileSize);

		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}