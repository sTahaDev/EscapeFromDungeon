#include "../../include/raylib.h"


class Demon{
    
    public:
        int health=50;
        Texture2D demon_run_image[4] = {LoadTexture("./images/big-demon/big_demon_run_anim_f0.png"),
                                        LoadTexture("./images/big-demon/big_demon_run_anim_f1.png"),
                                        LoadTexture("./images/big-demon/big_demon_run_anim_f2.png"),
                                        LoadTexture("./images/big-demon/big_demon_run_anim_f3.png")};

        void setup(int x,int y){
            demon_pos.x = x;
            demon_pos.y = y;
            health = max_health;
            for (int i = 0; i < 4; i++)
            {
                demon_run_image[i].width = demon_run_image[i].width * zoom_count;
                demon_run_image[i].height = demon_run_image[i].height * zoom_count;
            }
            
        }
        void update(int playerX,int playerY){
            //Animation
            running_time += GetFrameTime();
            if(running_time >= update_time){
                frame++;
                running_time = 0.f;
                if (frame >= max_frame){
                    frame = 0;
                }
            }

            //Moving Demon
            int distanceX = playerX-demon_pos.x;
            int distanceY = playerY-demon_pos.y;
            if(distanceX > 20){
                demon_pos.x += speed;
                rightLeft = 1.f;

            }else if(distanceX < 20){
                demon_pos.x -= speed;
                rightLeft = -1.f;
            }

            if(distanceY > 20){
                demon_pos.y += speed;
            }else if(distanceY < 20){
                demon_pos.y -= speed;
            }
            
        }

        void draw(int playerX, int playerY){
            int distance = playerY-demon_pos.y;
            DrawTextureRec(demon_run_image[frame],Rectangle{0,0, rightLeft * (float)demon_run_image[0].width,(float)demon_run_image[0].height},demon_pos,WHITE);
            DrawText(TextFormat("HP: %d",health),demon_pos.x+20,demon_pos.y-20,20,WHITE);
            
        }

        int get_demon_x(){
            return demon_pos.x;
        }

        int get_demon_y(){
            return demon_pos.y;
        }
        Rectangle get_Rec(){
            return Rectangle{(float)get_demon_x(),(float)get_demon_y(),(float)demon_run_image[0].width,(float)demon_run_image[0].height};
        }
    private:
        int zoom_count = 3;
        int frame = 0;
        float rightLeft = 1.0f;
        Vector2 demon_pos = {100,100};
        float running_time;
        const int max_frame = 4;
        const float update_time = 1.0f/9.0f;
        int speed = 2;
        int const max_health = 50;
        

        
        
        
};