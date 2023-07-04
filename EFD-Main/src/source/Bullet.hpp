#include "../../include/raylib.h"


class Bullet{
    

    public:
        void setup(int Px, int Py, float rL){
            x = Px;
            y = Py+60;
            
            rightLeft = rL;
            bullet_img.width = bullet_img.width*5;
            bullet_img.height = bullet_img.height*5;

            w = bullet_img.width;
            h = bullet_img.height;
            
        }
        
        
        void draw(){
            
            
            
            DrawTextureRec(bullet_img,Rectangle{0,0,rightLeft*(float)w,(float)h},Vector2{(float) x,(float) y},WHITE);
            x+= speed * rightLeft;
        }
        Rectangle get_Rec(){
            return Rectangle{(float)x,(float)y,(float)w,(float)h};
        }

    private:
        int x;
        int y;
        int w;
        int h;
        float rightLeft;
        int speed = 15;
        Texture2D bullet_img = LoadTexture("./images/bullet/weapon_knife.png");
        

};