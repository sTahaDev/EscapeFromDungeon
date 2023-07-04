#include "../../include/raylib.h"

#include <iostream>

using namespace std;

class Player{
    
    public:
        int health;
        
        Texture2D player_img[4] = { LoadTexture("./images/knight/knight_m_idle_anim_f0.png"),
                                    LoadTexture("./images/knight/knight_m_idle_anim_f1.png"),
                                    LoadTexture("./images/knight/knight_m_idle_anim_f2.png"),
                                    LoadTexture("./images/knight/knight_m_idle_anim_f3.png")};

        Texture2D player_run_img[4] = { LoadTexture("./images/knight/knight_m_run_anim_f0.png"),
                                        LoadTexture("./images/knight/knight_m_run_anim_f1.png"),
                                        LoadTexture("./images/knight/knight_m_run_anim_f2.png"),
                                        LoadTexture("./images/knight/knight_m_run_anim_f3.png")};

        
       
        
        void setup(){
            dash_voice = LoadSound("./voices/dash_normalized.wav");
            
            for (size_t i = 0; i < 4; i++)
            {
                player_img[i].width = 16*zoom_count;
                player_img[i].height = 28*zoom_count;
            }
            for (size_t i = 0; i < 4; i++)
            {
                player_run_img[i].width = 16*zoom_count;
                player_run_img[i].height = 28*zoom_count;
            }
            health = max_health;
        }
        void draw(){
            
            if(!isRun){
                DrawTextureRec(player_img[frame],Rectangle{0,0, rightLeft * (float)player_img[0].width,(float)player_img[0].height},playerPos,WHITE);
                
            }else{
                DrawTextureRec(player_run_img[frame],Rectangle{0,0, rightLeft * (float)player_run_img[0].width,(float)player_run_img[0].height},playerPos,WHITE);

            }
            
            
        }
        void unLoad_voice(){
            UnloadSound(dash_voice);
        }
        void update(){
            //Animation
            running_time += GetFrameTime();
            if(running_time >= update_time){
                frame++;
                running_time = 0.f;
                if (frame >= max_frame){
                    frame = 0;
                }
            }
            
            
            //Key Handle
            if (IsKeyDown(KEY_D)) {
                playerPos.x += speed;
                rightLeft = 1.f;
            }
            if (IsKeyDown(KEY_A)){
                playerPos.x -= speed;
                rightLeft = -1.f;
            }
            if (IsKeyDown(KEY_W)){
                playerPos.y -= speed;
            }
            if (IsKeyDown(KEY_S)){
                playerPos.y += speed;
            }
            
            if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S)){
                isRun = true;
            }else{
                isRun = false;
            }

            //Dash Mecanics
            time += GetFrameTime();

            if(IsKeyPressed(KEY_L)){
                
                if(time > 0.7){
                    PlaySound(dash_voice);
                    speed += dash_speed;
                    time = 0;
                }

            }
            if(speed > max_speed){
                speed -= 3;
            }

           
            
        }

        int get_player_x(){
            return playerPos.x;
        }

        int get_player_y(){
            return playerPos.y;
        }

        float get_rightlef(){
            return rightLeft;
        }

        int get_health(){
            return health;
        }

        void set_healt(int damage){
            health -=damage;
        }

        Rectangle get_rec(){
            return Rectangle{playerPos.x,playerPos.y,(float)player_run_img[0].width,(float)player_run_img[0].height};
        }

    private:
        int zoom_count = 4;
        
        Vector2 playerPos = {100,100};
        int speed = 5;
        const int max_speed = 5;
        
        
        int frame = 0;
        float running_time;
        const int max_frame = 4;
        const float update_time = 1.0f/5.0f;
        bool isRun = false;
        float rightLeft = 1.f;
        
        const int max_health = 100;
        const int dash_speed = 35;
        float time = 0;

        Sound dash_voice;


};