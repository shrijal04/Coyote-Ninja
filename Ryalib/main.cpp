#include <iostream>
#include <raylib.h>
#include "Player.hpp"
#include "Wall.hpp"
#include "Enemy.hpp"


using namespace std;

const int screenWidth = 1900;
const int screenHeight = 950;
     // Start with the menu state
int selectedOption = 0; 

enum class GameState {
    MENU,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    YOUWIN,
    DEAD
};

void InfoPrinter(){
    Vector2 mousePosition = GetMousePosition();
    std::string X = std::to_string(mousePosition.x);
    std::string Y = std::to_string(mousePosition.y);
    std::string fps = std::to_string(GetFPS());
    DrawText(X.c_str(), screenWidth -200 , 50, 30, BLACK);
    DrawText(Y.c_str(), screenWidth -200 , 50+60, 30, BLACK);
    DrawText(fps.c_str(), screenWidth -200 , 50+60*2, 30, BLACK);

}




int main() {
    InitWindow(screenWidth, screenHeight, "Base Game");
    SetTargetFPS(60);
    GameState currentState = GameState::MENU;
    // Texture2D bgsprt = LoadTexture("src/background.png");

    while (!WindowShouldClose()) {
        switch (currentState) {
            case GameState::MENU: {
                while (!WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);                    
                    DrawText("Menu", screenWidth / 2 - MeasureText("Menu", 40) / 2, 100, 40, WHITE);
                    (selectedOption == 0) ? DrawText(">Play", screenWidth / 2 - MeasureText("Play", 30) / 2, 200, 30, WHITE) : DrawText(" Play", screenWidth / 2 - MeasureText("Play", 30) / 2, 200, 30, WHITE);
                    (selectedOption == 1) ? DrawText(">Quit", screenWidth / 2 - MeasureText("Quit", 30) / 2, 250, 30, WHITE) : DrawText(" Quit", screenWidth / 2 - MeasureText("Quit", 30) / 2, 250, 30, WHITE);

                    if (IsKeyPressed(KEY_UP)) {
                    selectedOption = (selectedOption - 1) % 2;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        selectedOption = (selectedOption + 1) % 2;
                    }

                    if (IsKeyPressed(KEY_ENTER)) {
                        if (selectedOption == 0) {
                            currentState = GameState::LEVEL1;
                            
                            break;
                        } else if (selectedOption == 1) {
                            CloseWindow();EndDrawing();break;
                        }
                    }
                    EndDrawing();
                }
            }

            
            case GameState::LEVEL1: {
                Enemy enemy(783, 565, 3);
                
                Player player({100, 50}, 300, 100);
                
                Obstacle obstacle[] = {
                    Obstacle(300, 860, 198, 74),
                     Obstacle(700, 750, 198, 74),
                };int on =2;
                
                Wall walls[] = {
                    // Wall(0, screenHeight - 20, screenWidth, 20, BLACK),
                    Wall(0, 0, 0, 0, BLACK),
                    Wall(0, 740, 300, 300, BLACK),//wall1
                    Wall(500, 560, 200, 600, BLACK),//wall2,
                    Wall(700, 830, 200, 600, BLACK),//wall3,
                    Wall(990, 460, 270, 20, BLACK),//wall3,
                    Wall(1505, 650, 200, 800, BLACK),//wall3,
                    Wall(1695, 411, 200, 800, BLACK),//wall3,

                };int wn =7;

                while (!WindowShouldClose()) {
                    // Update and draw level 1
                    InfoPrinter();
                    double deltaTime = GetFrameTime();
                    player.Update(deltaTime);
                    
                    for (int i = 0; i < wn; i++){
                        player.Collision(walls[i], deltaTime);                        
                    }
                    
                    
                    ClearBackground(RAYWHITE);
                    // DrawTexture(bgsprt,0,0,WHITE);
                    
                    enemy.Draw();
                    for (int i = 0; i < on; i++){
                        obstacle[i].Draw();                                            
                    }
                    for (int i = 0; i < wn; i++){
                        walls[i].Draw(); 
                    }
                    for (int i = 0; i < wn; i++){
                        enemy.wallcollider(walls[i]);
                    }
                    enemy.UpdateX();     
                    BeginDrawing();
                    
                    player.Draw();
                    EndDrawing();

                  if ((player.position.x+player.rect.width) >= screenWidth) {
                        currentState = GameState::LEVEL2;   player.~Player();
                        break;
                    }
                    if (IsKeyPressed(KEY_R)) {
                        currentState = GameState::MENU;   player.~Player();
                        break;
                    }
                    if(CheckCollisionRecs(player.rect, enemy.collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                    if((player.position.y-player.rect.height)>780){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }

                    if(CheckCollisionRecs(player.rect, obstacle[0].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;

                    }
                    if(CheckCollisionRecs(player.rect, obstacle[1].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;

                    }

                }
                break;
                
            }
            case GameState::LEVEL2: {
                 Enemy enemy[]={
                    Enemy(715, 686, 3),
                    Enemy(1600,100,3),

                 };int en=2;
                Player player({5, 20}, 300, 100);
                Obstacle obstacle[] = {
                    Obstacle(300, 860, 198, 74),
                     Obstacle(698, 905, 198, 74),
                     Obstacle(1050, 905, 198, 74),
                     Obstacle(1370, 905, 198, 74),
                };int on =4;
                 Wall walls[] = {
                    // Wall(0, screenHeight - 20, screenWidth, 20, BLACK),
                    Wall(0, 0, 0, 0, BLACK),
                    Wall(0, 740, 315, 400, BLACK),//wall1
                    Wall(195,480,150,1200,BLACK),//wall2
                    Wall(500, 200, 200, 1300, BLACK),//wall3,
                    Wall(900, 800, 150, 300, BLACK),//wall4,
                    Wall(1195, 620, 200, 20, BLACK),//wall5,
                    Wall(1565, 465, 200, 800, BLACK),//wall6,
                     Wall(1750, 295, 200, 850, BLACK),//wall7,
                 }; int wn=8;

                while (!WindowShouldClose()) {
                    // Update and draw level 2
                    InfoPrinter();
                    double deltaTime = GetFrameTime();
                    player.Draw();
                    player.Update(deltaTime);
                    for (int i = 0; i < wn; i++){
                        player.Collision(walls[i], deltaTime);                        
                    }
                    
                    
                    ClearBackground(RAYWHITE);
                    // DrawTexture(bgsprt,0,0,WHITE);
                    
                    for(int i=0;i<en;i++)
                    {
                        enemy[i].Draw();
                    }
                    
                    for (int i = 0; i < on; i++){
                        obstacle[i].Draw();                                            
                    }
                    for (int i = 0; i < wn; i++){
                        walls[i].Draw();                                            
                    }
                    for (int i = 0; i < wn; i++){
                        enemy[0].wallcollider(walls[i]);
                        enemy[1].wallcollider(walls[i]);
                    } 
                    enemy[0].UpdateX();
                    enemy[1].UpdateY();
                    


                    BeginDrawing();
                    
                    EndDrawing();

                  
                    if (player.position.x >= screenWidth - 115) {
                        currentState = GameState::LEVEL3;   player.~Player();
                        break;
                    }
                    if (IsKeyPressed(KEY_R)) {
                        currentState = GameState::MENU;   player.~Player();
                        break;
                    }
                    if(CheckCollisionRecs(player.rect, enemy[0].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                     if(CheckCollisionRecs(player.rect, enemy[1].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                    if((player.position.y-player.rect.height)>screenHeight-180){
                        currentState = GameState::DEAD;   player.~Player();
                        break;  
                    }
                    if(CheckCollisionRecs(player.rect, obstacle[0].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[1].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[2].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[3].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                }
             break;
                
                
            }
            case GameState::LEVEL3: {
                    
                    Player player({5, 20}, 300, 100);
                    Enemy enemy[]={
                        Enemy(715, 686, 3),
                        Enemy(0, 180, 3),
                        Enemy(1085, 795, 3),
                        Enemy(1640,100,3),

                    };int en=4;
                    Obstacle obstacle[] = {
                        Obstacle(290, 905, 198, 74),
                        Obstacle(698, 905, 198, 74),
                        Obstacle(1050, 905, 198, 74),
                        Obstacle(1548, 905, 198, 74),
                    };int on =4;
                    Wall walls[] = {
                        // Wall(0, screenHeight - 20, screenWidth, 20, BLACK),
                        Wall(0, 0, 0, 0, BLACK),
                        Wall(0, 800, 295, 300, BLACK),//wall1
                        Wall(195,700,100,100,BLACK),//wall2
                        Wall(555, 465, 130, 130, BLACK),//wall3,
                        Wall(900,300, 150, 1300, BLACK),//wall4,
                        Wall(1260, 190, 100, 100, BLACK),//wall5,
                        Wall(1565, 580, 200, 100, BLACK),//wall6,
                        Wall(1750, 295, 200, 850, BLACK),//wall7,
                    }; int wn=8;
                    while (!WindowShouldClose()) {
                        // Update and draw level 3
                        BeginDrawing();
                        player.Draw(); cout<<player.position.x<<"  "<<player.position.y<<endl;
                        InfoPrinter();
                        double deltaTime = GetFrameTime();
                        player.Update(deltaTime);
                        for (int i = 0; i < wn; i++){
                            player.Collision(walls[i], deltaTime);                        
                        }
                        
                        
                        ClearBackground(RAYWHITE);
                        // DrawTexture(bgsprt,0,0,WHITE);
                        
                        for(int i=0;i<en;i++)
                        {
                            enemy[i].Draw();
                        }
                        
                        for (int i = 0; i < on; i++){
                            obstacle[i].Draw();                                            
                        }
                        for (int i = 0; i < wn; i++){
                            walls[i].Draw();                                            
                        }
                        for (int i = 0; i < wn; i++){
                            enemy[0].wallcollider(walls[i]);
                            enemy[1].wallcollider(walls[i]);
                            enemy[2].wallcollider(walls[i]);
                            enemy[3].wallcollider(walls[i]);
                        } 
                        enemy[0].UpdateX();
                        enemy[1].UpdateX();
                        enemy[2].UpdateX();
                        enemy[3].UpdateY();
                        


                        
                        EndDrawing();

                    
                        if ((player.position.x+player.rect.width+5) >= screenWidth) {
                            currentState = GameState::LEVEL4; 
                            player.position={5, 100};  
                            break;
                        }
                        if (IsKeyPressed(KEY_R)) {
                            currentState = GameState::MENU;   player.~Player();
                            break;
                        }
                            if(CheckCollisionRecs(player.rect, enemy[0].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            break;
                        }
                        
                        
                        if(CheckCollisionRecs(player.rect, enemy[1].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            break;
                        }
                        if(CheckCollisionRecs(player.rect, enemy[2].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            break;
                        }
                        if(CheckCollisionRecs(player.rect, enemy[3].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            break;
                        }
                        if((player.position.y-player.rect.height)>screenHeight-180){
                            currentState = GameState::DEAD;   player.~Player();
                            break;  
                        }
                        if(CheckCollisionRecs(player.rect, obstacle[0].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            cout<<"objectcollided"<<endl;
                            break;}
                        if(CheckCollisionRecs(player.rect, obstacle[1].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            cout<<"objectcollided"<<endl;
                            break;}
                        if(CheckCollisionRecs(player.rect, obstacle[2].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            cout<<"objectcollided"<<endl;
                            break;}
                        if(CheckCollisionRecs(player.rect, obstacle[3].collider)){
                            currentState = GameState::DEAD;   player.~Player();
                            cout<<"objectcollided"<<endl;
                            break;}
                    }
                    break;                    
                }
            case GameState::LEVEL4:{
                int x =1;
                Enemy enemy[]={
                    Enemy(200, 115+x, 3),
                    Enemy(1205, 125+x, 3),
                    // Enemy(1285, 520+x, 3),
                    Enemy(1116,690+x,3),

                 };int en=4;
                
                Player player({025, 740}, 300, 100);
                Obstacle obstacle[] = {
                    Obstacle(205, 608+x, 198, 74),
                     Obstacle(669, 905, 198, 74),
                     Obstacle(780, 195+40, 198, 74),
                     Obstacle(0, 415+x, 198, 74),
                     Obstacle(1050, 295+x, 198, 74),
                     Obstacle(1305, 295+x, 198, 74),
                     Obstacle(1740, 560+x, 198, 74),
                };int on =7;
                Wall walls[] = {
                    // Wall(0, screenHeight - 20, screenWidth, 20, BLACK),
                    Wall(0, 0, 0, 0, BLACK),
                    Wall(0, 895, 650, 100, BLACK),//wall1
                    // Wall(490, 400, 40, 100, BLACK),//wall1
                    Wall(785,700+x,150,50,BLACK),//wall2
                    Wall(0, 680, 550, 40, BLACK),//wall3,
                    Wall(0,480+x,200,212,BLACK),//wall4
                    Wall(785,440+90+x,150,50,BLACK),//wall5
                    Wall(0, 480+x, 550, 50, BLACK),//wall6,
                    Wall(400, 250+30, 640, 50, BLACK),//wall8,
                    Wall(900,210+x, 150, 1300, BLACK),//wall9,
                    Wall(1050, 345+x, 550, 30, BLACK),//wall10,
                    Wall(1295, 230+x, 100, 30, BLACK),//wall11,
                    Wall(1725, 405+x, 190, 40, BLACK),//wall12,
                    Wall(1200, 610+x, 700, 50, BLACK),//wall13,
                    // Wall(1200, 500+x, 80, 120, BLACK),//wall14,
                    Wall(1450, 500+x, 80, 250, BLACK),//wall15,
                    Wall(1050, 895, 900, 100, BLACK),//wall16,
                 }; int wn=15;
                  while (!WindowShouldClose()) {
                    // Update and draw level 4
                    BeginDrawing();
                    InfoPrinter();
                    player.Draw();
                    double deltaTime = GetFrameTime();
                    player.Update(deltaTime);
                    for (int i = 0; i < wn; i++){
                        player.Collision(walls[i], deltaTime);                        
                    }
                     ClearBackground(RAYWHITE);
                    // DrawTexture(bgsprt,0,0,WHITE);

                     for(int i=0;i<en;i++)
                    {
                        enemy[i].Draw();
                    }

                    for (int i = 0; i < on; i++){
                        obstacle[i].Draw();                                            
                    }
                    
                    for (int i = 0; i < wn; i++){
                        walls[i].Draw();                                            
                    }
                     for (int i = 0; i < wn; i++){
                        enemy[0].wallcollider(walls[i]);
                        enemy[1].wallcollider(walls[i]);
                        enemy[2].wallcollider(walls[i]);
                        // enemy[3].wallcollider(walls[i]);
                    } 
                    enemy[0].UpdateY();
                    enemy[1].UpdateY();
                    enemy[2].UpdateX();
                    // enemy[3].UpdateX();
                    
                    EndDrawing();

                  
                    if ((player.position.x+player.rect.width) >= screenWidth&&(player.position.y)>=640) {
                        currentState = GameState::YOUWIN;
                        break;
                    }
                    if (IsKeyPressed(KEY_R)) {
                        currentState = GameState::MENU;   player.~Player();
                        break;
                    }
                      if(CheckCollisionRecs(player.rect, enemy[0].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                    
                    
                     if(CheckCollisionRecs(player.rect, enemy[1].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                    if(CheckCollisionRecs(player.rect, enemy[2].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        break;
                    }
                    // if(CheckCollisionRecs(player.rect, enemy[3].collider)){
                    //     currentState = GameState::DEAD;   player.~Player();
                    //     break;
                    // }
                     if((player.position.y-player.rect.height)>screenHeight-180){
                        currentState = GameState::DEAD;   player.~Player();
                        break;  
                    }
                    if(CheckCollisionRecs(player.rect, obstacle[0].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[1].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[2].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[3].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[4].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[5].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    if(CheckCollisionRecs(player.rect, obstacle[6].collider)){
                        currentState = GameState::DEAD;   player.~Player();
                        cout<<"objectcollided"<<endl;
                        break;}
                    

                  }
                  break;
             }
            case GameState::YOUWIN: {
                while (!WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);                    
                    DrawText("YOU WIN", screenWidth / 2 - MeasureText("YOU WIN", 40) / 2, 100, 40, WHITE);
                    (selectedOption == 0) ? DrawText(">New Game", screenWidth / 2 - MeasureText("New Game", 30) / 2, 200, 30, WHITE) : DrawText(" New Game", screenWidth / 2 - MeasureText("New Game", 30) / 2, 200, 30, WHITE);
                    (selectedOption == 1) ? DrawText(">Quit Game", screenWidth / 2 - MeasureText("Quit Game", 30) / 2, 250, 30, WHITE) : DrawText(" Quit Game", screenWidth / 2 - MeasureText("Quit Game", 30) / 2, 250, 30, WHITE);

                    if (IsKeyPressed(KEY_UP)) {
                    selectedOption = (selectedOption - 1) % 2;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        selectedOption = (selectedOption + 1) % 2;
                    }

                    if (IsKeyPressed(KEY_ENTER)) {
                        if (selectedOption == 0) {
                            currentState = GameState::LEVEL1;
                            
                            break;
                        } else if (selectedOption == 1) {
                            CloseWindow();EndDrawing();break;
                        }
                    }
                    EndDrawing();
                }
                break;
            }
            
            case GameState::DEAD: {
                while (!WindowShouldClose()) {
                    BeginDrawing();
                    ClearBackground(BLACK);                    
                    DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, 100, 40, WHITE);
                    (selectedOption == 0) ? DrawText(">Play", screenWidth / 2 - MeasureText("Play", 30) / 2, 200, 30, WHITE) : DrawText(" Play", screenWidth / 2 - MeasureText("Play", 30) / 2, 200, 30, WHITE);
                    (selectedOption == 1) ? DrawText(">Quit", screenWidth / 2 - MeasureText("Quit", 30) / 2, 250, 30, WHITE) : DrawText(" Quit", screenWidth / 2 - MeasureText("Quit", 30) / 2, 250, 30, WHITE);

                    if (IsKeyPressed(KEY_UP)) {
                    selectedOption = (selectedOption - 1) % 2;
                    }
                    if (IsKeyPressed(KEY_DOWN)) {
                        selectedOption = (selectedOption + 1) % 2;
                    }

                    if (IsKeyPressed(KEY_ENTER)) {
                        if (selectedOption == 0) {
                            currentState = GameState::LEVEL1;
                            
                            break;
                        } else if (selectedOption == 1) {
                            CloseWindow();EndDrawing();break;
                        }
                    }
                    EndDrawing();
                }
                break;
            }
        }
        
    }
    CloseWindow();
    return 0;   
}
