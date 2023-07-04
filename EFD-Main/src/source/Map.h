#include "../../include/raylib.h"

class Map{

    public:
        void draw();
        void settings();
        
    private:
        Texture2D map_image = LoadTexture("./map/map.png");
        
        
};