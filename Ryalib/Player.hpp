#pragma once
#include "raylib.h"
#include "wall.hpp"
#include <iostream>
#include "enemy.hpp"

class Player {
public:
    enum states{
        idleleft,idleright,
        runleft,runright,
        jumpright,jumpleft

    };
    states state,prestate;
    float timer = 0.0f;
    int frame= 0;
    //animation
    Texture2D idleleft1 = LoadTexture("src/playerani/idlerleft1.png");
    Texture2D idleleft2 = LoadTexture("src/playerani/idlerleft2.png");
    Texture2D idleleft3 = LoadTexture("src/playerani/idlerleft3.png");
    Texture2D idleleft4 = LoadTexture("src/playerani/idlerleft4.png");
    Texture2D idleleft5 = LoadTexture("src/playerani/idlerleft5.png");
    Texture2D idleright1 = LoadTexture("src/playerani/idleright1.png");
    Texture2D idleright2 = LoadTexture("src/playerani/idleright2.png");
    Texture2D idleright3 = LoadTexture("src/playerani/idleright3.png");
    Texture2D idleright4 = LoadTexture("src/playerani/idleright4.png");
    Texture2D idleright5 = LoadTexture("src/playerani/idleright5.png");
    
    Texture2D runright1 =LoadTexture("src/playerani/runright1.png");
    Texture2D runright2 =LoadTexture("src/playerani/runright2.png");
    Texture2D runright3 =LoadTexture("src/playerani/runright3.png");
    Texture2D runright4 =LoadTexture("src/playerani/runright4.png");
    Texture2D runleft1 =LoadTexture("src/playerani/runleft1.png");
    Texture2D runleft2 =LoadTexture("src/playerani/runleft2.png");
    Texture2D runleft3 =LoadTexture("src/playerani/runleft3.png");
    Texture2D runleft4 =LoadTexture("src/playerani/runleft4.png");
    Texture2D jumpright1 = LoadTexture("src/playerani/jumpright.png");
    Texture2D jumpleft1 = LoadTexture("src/playerani/jumpleft.png");





    Rectangle rect;
    Vector2 position;
    Vector2 previousPosition;
    Texture2D spriteLeft, spriteRight;
    bool facingRight = true;
    float speed;
    float gravity;
    float jumpForce;
    bool isColliding;
    bool isJumping,isOnGround;
    float verticalVelocity;
    float deltaTime = GetFrameTime();
    Player(Vector2 startPos, float playerSpeed=300, float playerJumpForce=100)
        : position(startPos), speed(playerSpeed), gravity(3000.0f), jumpForce(playerJumpForce),
          isColliding(false), isJumping(false), verticalVelocity(10.0f) {
        rect.width = 100;
        rect.height = 120;
        spriteLeft = LoadTexture("src/player2right.png");
        spriteRight = LoadTexture("src/player2left.png");
        
    }
   



    void Update(double deltaTime) {

        // Move the player based on input
        if (IsKeyDown(KEY_RIGHT)){
            position.x += speed * deltaTime;
            facingRight = true;state=runright;prestate=state;}
        if(IsKeyReleased(KEY_RIGHT)){state = idleright;}

        if (IsKeyDown(KEY_LEFT)){
            position.x -= speed * deltaTime;
            facingRight  = false ; state=runleft;prestate=state;}
        if(IsKeyReleased(KEY_LEFT)){state = idleleft;frame = 0; }

        if (IsKeyPressed(KEY_UP) && !isJumping) {
            verticalVelocity = -jumpForce * 015;
            isJumping = true;}
        if(isJumping&&facingRight&&(!isOnGround)){state=jumpright; }
        if(isJumping&&!facingRight&&(!isOnGround)){state= jumpleft;}
        if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
            state = (facingRight) ? idleright : idleleft;
        }
        // Apply gravity
        verticalVelocity += gravity * deltaTime;
        position.y += verticalVelocity * deltaTime;

    
    }
    void Collision(Wall& wall, double deltaTime) {
    previousPosition = position;
    Rectangle nextRect = rect;
    nextRect.x = static_cast<int>(position.x);
    nextRect.y = static_cast<int>(position.y);

    isOnGround = CheckCollisionRecs(nextRect, wall.rect);

    if (isOnGround) {
        isJumping = false; // Reset jump state when on the ground
    }

    if (CheckCollisionRecs(nextRect, wall.rect)) {
        // Calculate the overlap between the player and the wall
        float xOverlap = std::min(nextRect.x + nextRect.width, wall.rect.x + wall.rect.width) -
                        std::max(nextRect.x, wall.rect.x);
        float yOverlap = std::min(nextRect.y + nextRect.height, wall.rect.y + wall.rect.height) -
                        std::max(nextRect.y, wall.rect.y);

        // Resolve the collision based on the smaller overlap
        if (xOverlap < yOverlap) {
            if (position.x < wall.rect.x) {
                position.x = wall.rect.x - rect.width;
            } else {
                position.x = wall.rect.x + wall.rect.width;
            }
        } else {
            if (position.y < wall.rect.y + 5) {
                position.y = wall.rect.y - rect.height;
                verticalVelocity = 0.0f;
            } else {
                position.y = wall.rect.y + wall.rect.height;
                verticalVelocity = 0.0f;
            }
        }
    }

    // Only allow jumping if the player is on the ground
    if (IsKeyPressed(KEY_UP) && !isJumping && isOnGround) {
        verticalVelocity = -jumpForce * 8;
        isJumping = true;
    }

    // Limit player's position to stay within the screen bounds
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + rect.width > GetScreenWidth()) position.x = GetScreenWidth() - rect.width;
    if (position.y + rect.height > GetScreenHeight()) position.y = GetScreenHeight() - rect.height;

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
}

    

    void Draw() {
    // DrawRectangleRec(rect, BLUE);
    // (facingRight== true)?(DrawTexture(spriteLeft,position.x,position.y , WHITE)):(DrawTexture(spriteRight,position.x,position.y , WHITE));
        if((Player::state)== idleright){
            timer += GetFrameTime();
            if(timer>0.2){
                timer  =  0.0f;
                frame  += 1;
            }
            frame = frame% 5;
            switch (frame)
            {
                case 0:{DrawTexture(idleright1,Player::rect.x,Player::rect.y , WHITE);break;}            
                case 1:{DrawTexture(idleright2,Player::rect.x,Player::rect.y , WHITE);break;}            
                case 2:{DrawTexture(idleright3,Player::rect.x,Player::rect.y , WHITE);break;}            
                case 3:{DrawTexture(idleright4,Player::rect.x,Player::rect.y , WHITE);break;}            
                case 4:{DrawTexture(idleright5,Player::rect.x,Player::rect.y , WHITE);break;}        
            }
        }
        if((Player::state)== idleleft){
            timer += GetFrameTime();
            if(timer>0.2){
                timer  =  0.0f;
                frame  += 1;
            }
            frame = frame% 5;
            switch (frame)
            {
                case 0:{DrawTexture(idleleft1,Player::position.x,Player::position.y , WHITE);break;}            
                case 1:{DrawTexture(idleleft2,Player::position.x,Player::position.y , WHITE);break;}            
                case 2:{DrawTexture(idleleft3,Player::position.x,Player::position.y , WHITE);break;}            
                case 3:{DrawTexture(idleleft4,Player::position.x,Player::position.y , WHITE);break;}            
                case 4:{DrawTexture(idleleft5,Player::position.x,Player::position.y , WHITE);break;}        
            }
        }
        if((Player::state)== runright){
            timer += GetFrameTime();
            if(timer>0.2){
                timer  =  0.0f;
                frame  += 1;
            }
            frame = frame% 4;
            switch (frame)
            {
                case 0:{DrawTexture(runright1,Player::position.x,Player::position.y , WHITE);break;}            
                case 1:{DrawTexture(runright2,Player::position.x,Player::position.y , WHITE);break;}            
                case 2:{DrawTexture(runright3,Player::position.x,Player::position.y , WHITE);break;}            
                case 3:{DrawTexture(runright4,Player::position.x,Player::position.y , WHITE);break;}        
            }
        }
        if((Player::state)== runleft){
            timer += GetFrameTime();
            if(timer>0.2){
                timer  =  0.0f;
                frame  += 1;
            }
            frame = frame% 4;
            switch (frame)
            {
                case 0:{DrawTexture(runleft1,Player::position.x,Player::position.y , WHITE);break;}            
                case 1:{DrawTexture(runleft2,Player::position.x,Player::position.y , WHITE);break;}            
                case 2:{DrawTexture(runleft3,Player::position.x,Player::position.y , WHITE);break;}            
                case 3:{DrawTexture(runleft4,Player::position.x,Player::position.y , WHITE);break;}        
            }
        }
        if((Player::state)== jumpleft){
            DrawTexture(jumpleft1,Player::position.x,Player::position.y , WHITE);
        }
        if((Player::state)== jumpright){
            DrawTexture(jumpright1,Player::position.x,Player::position.y , WHITE);
        }
    }
~Player(){std::cout<<"player destroyed"<<std::endl;}
};
