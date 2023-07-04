#include "Map.h"
#include "../../include/raylib.h"
#include <iostream>

void Map::settings(){
    map_image.width=1200;
    map_image.height = 720;
}

void Map::draw(){
    DrawTexture(map_image,0,-16,WHITE);
    
}