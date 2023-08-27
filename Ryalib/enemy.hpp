#pragma once
#include "raylib.h"
#include "WALL.hpp"


class Enemy {
public:
    Texture2D sprite1=LoadTexture("src/enemyani/enemy1.png");
    Texture2D sprite2=LoadTexture("src/enemyani/enemy2.png");
    Texture2D sprite3=LoadTexture("src/enemyani/enemy2.png");
    // Texture2D sprite=LoadTexture("src/a/niti.png");
    Enemy(int posX, int posY, int speed);
    
    
    float x;
    float y;
    float speed;
    int direction; // -1 for left, 1 for right
    Rectangle collider;

    void wallcollider(const Wall & wall ){
        
        if (CheckCollisionRecs(collider, wall.rect)){
            direction *=-1;
        }
        
    }

    void UpdateX()  {
        if (x <= 0 || x + collider.width >= GetScreenWidth()) {
            direction *= -1;
        }
    x += speed * direction;        
    // Change direction when reaching screen edges
    // Update the collider's position
    collider.x = x;
    collider.y = y;
    }
    void UpdateY()  {
            if (y <=0 || y + collider.height >= GetScreenHeight()) {
        direction *= -1;
    }
    y += speed * (direction);        
    // Change dir(ection when reaching screen edges
    // Update the collider's position
    collider.x = x;
    collider.y = y;
    }
    float timer = 0.0f;
    int frame= 0;
    
    void Draw() {
        
        timer += GetFrameTime();
        if(timer>0.2){
            timer  =  0.0f;
            frame  += 1;
        }
        frame = frame% 3;
        switch (frame)
        {
            case 0:{
                DrawTexture(sprite1,collider.x,collider.y , WHITE);        
                
                break;
            
            }
            case 1:{
                DrawTexture(sprite2,collider.x,collider.y , WHITE);        
                
                break;
            
            }
            case 2:{
                DrawTexture(sprite3,collider.x,collider.y , WHITE);        
                
                break;
            }
        
        }
        
    }
};


Enemy::Enemy(int posX, int posY, int speed)
    : x(posX), y(posY), speed(speed), direction(1) {
    collider = {x, y, 50, 50}; // Adjust the size as needed
}



// Obstacle.h
class Obstacle {
    Texture2D sprite= LoadTexture("src/obs.png"); 
public:
    Obstacle(int posX, int posY, int width, int height);
    Rectangle GetCollider() const;
    void Draw();
    int x;
    int y;
    int width;
    int height;
    Rectangle collider;
};
Obstacle::Obstacle(int posX, int posY, int width, int height)
    : x(posX), y(posY), width(width), height(height) {
    collider = {static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};
}

Rectangle Obstacle::GetCollider() const {
    return collider;
}

void Obstacle::Draw() {
    // DrawRectangle(static_cast<int>(x), static_cast<int>(y), width, height, RED);
    DrawTexture(sprite,collider.x,collider.y , WHITE);
    
}





