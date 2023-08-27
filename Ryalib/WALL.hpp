#pragma once
#include "raylib.h"

class Wall {
public:
    Rectangle rect;
    Color color;
    
    Wall(float x, float y, float width, float height, Color wallColor): rect{x, y, width, height}, color(wallColor) {}

    void Draw() {
        DrawRectangleRec(rect, color);
    }
~Wall(){};
};