#pragma once
#include "raylib.h"

//draws a wire frame circle by applying the given transformations
//position would contain model coordiantes based on the origin
void draw_wire_frame_circle(Vector2 position,float radius, float angle, float scale=1.0);



void draw_wire_frame_circle(Vector2 position,float radius, float angle, float scale){

    DrawCircleLinesV(position,radius,BLACK);


}