#pragma once
#include "phy_obj.h"
#include "raylib.h"
#include "wire_frame.h"


class dummy : public phy_obj
{
    // // each dummy object is made up of 10 points
    // static const int num_points = 10;

    // Vector2 wireframe_points[num_points];
    Vector2 angle_point; // terminal point of the angle

    // void transform_wireframe(Vector2 new_position);
    void rotate_wireframe(float rot_angle);
    void rotate_angle(float rot_angle);

public:
    dummy(Vector2 position, float radius, float angle);

    //void set_position(Vector2 new_position);
    void draw() ;
};

// // set a new center for the phy object directly
// void dummy::set_position(Vector2 new_position)
// {
//     transform_wireframe(new_position);
//     this->position = new_position;
// }

// rotate the wireframe points by the given rotation
void dummy::rotate_wireframe(float rot_angle)
{
    // // Given the center and the radius compute 10 wireframe points on the circle
    // float partition_angle = 2.0 * PI / (float(num_points));
    // for (int i = 0; i < num_points; i++)
    // {
    //     // essentially implementing the formula (2pi/n)*i+theta = partition_angle*i+theta where theta is the rotation angle
    //     int x = radius * cosf(partition_angle * i + rot_angle);
    //     int y = radius * sinf(partition_angle * i + rot_angle);

    //     // now compute the coordinate transformation
    //     x += position.x;
    //     y += position.y;

    //     wireframe_points[i].x = x;
    //     wireframe_points[i].y = y;
    // }

    rotate_angle(rot_angle);

    this->angle = rot_angle;
}

// rotates the terminal point of the angle plus the points of the angle head
void dummy::rotate_angle(float rot_angle)
{
    // workout the terminal point of the angle for the current rotation
    int x = radius * cosf(rot_angle);
    int y = radius * sinf(rot_angle);

    // translate according to the current pos
    x += position.x;
    y += position.y;

    angle_point.x = x;
    angle_point.y = y;
}

// // update all the wireframe points along with the angle terminal point
// void dummy::transform_wireframe(Vector2 new_position)
// {

//     // how much difference in x,y direction from the previous pos and the new pos
//     int diff_x = new_position.x - position.x;
//     int diff_y = new_position.y - position.y;

//     for (int i = 0; i < num_points; i++)
//     {
//         wireframe_points[i].x += diff_x;
//         wireframe_points[i].y += diff_y;
//     }

//     angle_point.x += diff_x;
//     angle_point.y += diff_y;
// }

dummy::dummy(Vector2 position, float radius, float angle) : phy_obj(position, radius, angle)
{
    // initialize the angle terminal point
    // essentially equal to wire_frame_point[0]
    angle_point = {position.x + radius, position.y};

    rotate_wireframe(angle);
}

void dummy::draw() 
{
    float angle = atan2f(velocity.y,velocity.x);
    rotate_angle(angle);
    

    // draw the circle
    DrawCircleLinesV(position, radius, BLACK);
    // draw_wire_frame_circle(position,radius,1);

    // // draw the wireframe points on the circle
    // for (int i = 0; i < num_points; i++)
    // {
    //     DrawLineV(position, wireframe_points[i], GREEN);
    // }

    
    // DrawLineEx(position,acceleration,3,BLUE);
    // std::cout<<"Acceleration: "<<acceleration.x<<", "<<acceleration.y<<std::endl;

    // DrawLineEx(position,velocity,3,PURPLE);
    // std::cout<<"velocity: "<<velocity.x<<", "<<velocity.y<<std::endl;

    //std::cout<<"arctan "<<atan2f(-0.6,-0.8);

    

    // if (acceleration.y>600)
    // {
    //     system("pause");
    // }
    
    // draw the arrow
    DrawLineV(position, angle_point, RED);
}
