#include <iostream>
#include <list>
#include <cstdlib>
#include "../include/raylib.h"
#include "./source/Map.h"
#include "./source/Player.hpp"
#include "./source/Demon.hpp"
#include "./source/Bullet.hpp"

using namespace std;

int main(void)
{
  
    const int screenWidth = 1200;
    const int screenHeight = 704;
    
    InitWindow(screenWidth, screenHeight, "Escape From Dungeon");
    InitAudioDevice();

    bool collision = false;

    float time_1;
    float time_2;

    int current_level = 0;
    int demon_number = 3;

    //Voices
    
   

    SetTargetFPS(60);               

    //---------------------Define------------------

    //Map
    Map map;
    map.settings();

    //Player
    Player player;
    player.setup();

    //Demon
    list<Demon> demon_list;
    for (int i = 0; i < demon_number; i++)
    {
        demon_list.push_back(Demon());
        demon_list.back().setup(rand()%screenWidth,rand()%screenHeight);
    }
    

    //Bullet
    list<Bullet> bullet_list;

    //Game Settings
    bool game_over = false;
    
    
    
    if(!game_over){
        while (!WindowShouldClose() && game_over == false)    
        {
            // Update
            //----------------------------------------------------------------------------------
            player.update();

            //Demon Update
            for(auto dem = demon_list.begin();dem != demon_list.end();dem++){
                dem->update(player.get_player_x(),player.get_player_y());
                if(dem->health == 0){
                    dem = demon_list.erase(dem);
                }
            }

            //Bullet Colission
            for (auto bull = bullet_list.begin(); bull != bullet_list.end(); ++bull) {
                

                for(auto dem = demon_list.begin();dem != demon_list.end();dem++){
                    collision = CheckCollisionRecs((*bull).get_Rec(),dem->get_Rec());
                    if(collision){
                        bull = bullet_list.erase(bull);
                        dem->health -= 10;
                    }
                }
                
            }

            //Player Demon Collision
            time_1 += GetFrameTime();
            
            for(auto dem = demon_list.begin();dem != demon_list.end();dem++){
                collision = CheckCollisionRecs(player.get_rec(),dem->get_Rec());
                if(collision){
                    if(time_1 > 1.f){
                        player.health-=5;
                        time_1 = 0;
                        
                    }
                }
        
            }
            

            //Bullet Updating
            time_2 += GetFrameTime();
            if(IsKeyPressed(KEY_K)){
                if (time_2 > 0.f){
                    bullet_list.push_back(Bullet());
                    bullet_list.back().setup(player.get_player_x(),player.get_player_y(),player.get_rightlef());
                    time_2 = 0.f;
                }
                
            }
            //Level Updating
            if(demon_list.size()<1){
                current_level += 1;
                player.health += 20;
                if(current_level > 1){
                    demon_number += 1;
                }else{
                    demon_number += 2;
                }
                for (int i = 0; i < demon_number; i++)
                {
                    demon_list.push_back(Demon());
                    demon_list.back().setup(rand()%screenWidth,rand()%screenHeight);
                }
            }

            if(player.health < 0){
                game_over = true;
            }
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

                ClearBackground(RAYWHITE);
                //Drawing Map
                map.draw();

                //Drawing Player
                player.draw();

                //Drawing Demon
                for(auto dem = demon_list.begin();dem != demon_list.end();dem++){
                    dem->draw(player.get_player_x(),player.get_player_y());
                }

                //Bullet Drawing
                for (auto bull = bullet_list.begin(); bull != bullet_list.end(); ++bull) {
                    (*bull).draw();
                }

                //Draw FPS
                DrawText(TextFormat("FPS: %d ",GetFPS()),50,620,20,WHITE);
                //Draw Player Hp
                DrawText(TextFormat("Player HP: %d ",player.health),1000,620,20,WHITE);
                //Drawing Level
                DrawText(TextFormat("Level: %d ",current_level),600,620,20,WHITE);

                
            
            EndDrawing();
            //----------------------------------------------------------------------------------
        }
    }
    if(game_over == true){
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here
            //----------------------------------------------------------------------------------

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

                ClearBackground(RAYWHITE);

                DrawText("GAME OVER !", 330, 250, 70, LIGHTGRAY);
                DrawText(TextFormat("Your Score: %d",current_level), 330, 350, 70, LIGHTGRAY);

            EndDrawing();
            //----------------------------------------------------------------------------------
        }
    }
    

    // De-Initialization
    player.unLoad_voice();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}