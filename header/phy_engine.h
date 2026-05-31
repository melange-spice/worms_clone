#pragma once
#include "LinkedList.h"
#include "phy_obj.h"
#include <cmath>
#include "map.h"
#include "raylib.h"
#include <vector>

// phy_engine is responsible for applying physics on all the phy_obj in the game
class phy_engine : public LinkedList<phy_obj *>
{
private:
    int total_obj;

    Vector2 apply_gravity(phy_obj *obj);
    bool check_map_collision(phy_obj *obj, Vector2 potential_position, Vector2 &response, map *mapp);
    float angle_step(float radius, int mapp_width);

    void do_collision(phy_obj *obj, Vector2 &response);
    void delete_dead_object(Node<phy_obj *> *node);

    // apply shock wave to all the phy objects
    void apply_shockwave(Vector2 explosion_pos, int radius);

public:
    void insertAtTail(phy_obj *value);
    void apply_physics(map *mapp);
    void draw();
    void draw_debug();
    int get_num_objects();

    void explosion(map *mapp, Vector2 position, int radius);

    phy_engine();
    ~phy_engine();
};

void phy_engine::apply_shockwave(Vector2 explosion_pos, int radius)
{
    static int clamp_factor = 100;

    Node<phy_obj *> *tmp = head;
    Vector2 blast_veloctity{};

    while (tmp != nullptr)
    {
        phy_obj *obj = tmp->data;

        // vector from the explosion position to the phy_obj position
        blast_veloctity.x = obj->position.x - explosion_pos.x;
        blast_veloctity.y = obj->position.y - explosion_pos.y;

        // distance between explosion and phy_obj or equivalently
        // the magnitude of the vector obtained above
        float distance = sqrtf(blast_veloctity.x * blast_veloctity.x + blast_veloctity.y * blast_veloctity.y);

        if (distance < 0.1f)
            distance = 0.1f;

        if (distance - obj->radius <= radius)
        {
            // normalization * factor dependent upon distance and radius * constant multiplication factor
            blast_veloctity.x = (blast_veloctity.x / distance) * (radius * 30 / distance);
            blast_veloctity.y = (blast_veloctity.y / distance) * (radius * 30 / distance);

            // clamping
            if (blast_veloctity.x > clamp_factor)
            {
                blast_veloctity.x = clamp_factor;
            }
            else if (blast_veloctity.x < -clamp_factor)
            {
                blast_veloctity.x = -clamp_factor;
            }

            if (blast_veloctity.y > clamp_factor)
            {
                blast_veloctity.y = clamp_factor;
            }
            else if (blast_veloctity.y < -clamp_factor)
            {
                blast_veloctity.y = -clamp_factor;
            }

            obj->velocity = blast_veloctity;
        }

        tmp = tmp->next;
    }
}

// create an explosion with the given radius and position
//  radius in pixel values not in map coordinates
void phy_engine::explosion(map *mapp, Vector2 position, int radius)
{
    // midpoint circle in the map
    mapp->make_circle(position, radius);

    apply_shockwave(position,radius);

    //an explosion of radius 10 should have about 3 debris objects
    for (int i = 1; i < radius / 3.3333; i++)
    {
        debris *created_debris = nullptr;
        created_debris = new debris({position.x, position.y}, 6);
        insertAtTail(created_debris);
    }
}

// deletes a single physics object implementation as well as the node from the dll
void phy_engine::delete_dead_object(Node<phy_obj *> *node)
{
    total_obj--;
    delete node->data; // first delete the phy obj
    delete_node(node); // now delete the node from the linked list
}

// draw the phy_obj circle of all the objects
void phy_engine::draw_debug()
{
    Node<phy_obj *> *tmp = head;

    while (tmp != nullptr)
    {
        // current phy object
        phy_obj *obj = tmp->data;
        obj->draw_debug();

        // next phy_object in the linked list
        tmp = tmp->next;
    }
}

int phy_engine::get_num_objects()
{
    return total_obj;
}

// draws all the phy objects
void phy_engine::draw()
{
    Node<phy_obj *> *tmp = head;

    while (tmp != nullptr)
    {
        // current phy object
        phy_obj *obj = tmp->data;
        obj->draw();

        // next phy_object in the linked list
        tmp = tmp->next;
    }
}

// loop through the linked list applying physics to each object in each iteration
void phy_engine::apply_physics(map *mapp)
{
    Node<phy_obj *> *tmp = head;

    while (tmp != nullptr)
    {
        // current phy object
        phy_obj *obj = tmp->data;

        Vector2 potential_position = apply_gravity(obj);

        Vector2 response{0, 0};
        bool collided = check_map_collision(obj, potential_position, response, mapp);

        // velocity magnitude
        float velocity_mag = sqrtf((obj->velocity.x * obj->velocity.x) + (obj->velocity.y * obj->velocity.y));

        // collision has occured with the map
        if (collided == true)
        {
            // calculate response
            do_collision(obj, response);
        }
        else
        {
            // no collision just apply the potential position
            obj->position.x = potential_position.x;
            obj->position.y = potential_position.y;
        }

        // TODO: is this doing anything how is is_stable gonna make phy_obj stop collision calculations?
        if (velocity_mag < 0.1f)
        {
            obj->is_stable = true;
        }
        
        Node<phy_obj *> *to_delete = tmp;
        tmp = tmp->next; // go to next node before deleting this node

        // delete the previous object if flagged
        if (obj->is_dead == true)
        {
            //TODO: determination of dead actions
            if (obj->radius == 10){
                explosion(mapp,obj->position,50);
            }
                

                delete_dead_object(to_delete);
        }
    }
}

// calculates the reflection vector given the normal vector (response) and obj
// should only be called if collision has actually occured
// refer to docs and the maths of vector reflection https://www.sunshine2k.de/articles/coding/vectorreflection/vectorreflection.html
void phy_engine::do_collision(phy_obj *obj, Vector2 &response)
{
    // invert the response vector
    // this essentially gives us the normal vector
    response.x *= -1;
    response.y *= -1;

    obj->is_stable = true; // TODO: this stable thingy

    // calculate normal collision plane
    float response_angle = atan2f(response.y, response.x);
    float normal_angle = response_angle + (PI / 2.0); //+ or minus does not matter

    // normalize the response vector
    float response_mag = sqrtf((response.x * response.x) + (response.y * response.y));
    response.x = response.x / response_mag;
    response.y = response.y / response_mag;

    // invert the velocity vector for reflection calculations
    obj->velocity.x *= -1;
    obj->velocity.y *= -1;

    // projection of velocity to n i.e v_parallel calculation
    // magnitude of v_parallel
    float dot = (obj->velocity.x * response.x) + (obj->velocity.y * response.y);
    // actual v_parallel calculation
    Vector2 v_parallel{response.x * dot, response.y * dot};

    // v_perpendicular calculation
    //  v - v_parallel
    Vector2 v_perpendicular;
    v_perpendicular.x = obj->velocity.x - v_parallel.x;
    v_perpendicular.y = obj->velocity.y - v_parallel.y;

    // invert the v_perpendicular
    v_perpendicular.x *= -1;
    v_perpendicular.y *= -1;

    // final velocity reflection calculation
    Vector2 v_reflection;
    v_reflection.x = v_parallel.x + v_perpendicular.x;
    v_reflection.y = v_parallel.y + v_perpendicular.y;

    // friction
    v_reflection.x *= obj->friction;
    v_reflection.y *= obj->friction;

    if (obj->bounce_before_death > 1)
        obj->bounce_before_death--;
    else if (obj->bounce_before_death == 1) // flag for deletion
    {
        obj->bounce_before_death--;
        obj->is_dead = true;
    }

    // Final velocity update
    obj->velocity.x = v_reflection.x;
    obj->velocity.y = v_reflection.y;
}

// given the radius of the phy object and width of a single map tile
// calculate the angle step required that makes it so that every map tile fits in phy object
float phy_engine::angle_step(float radius, int mapp_width)
{

    // refer to angle step derivation in the documentation
    // essentially implementing the formula
    //\theta=\arcsin(\dfrac{w\sqrt{(2r+w)(2r-w)}}{2r^2})

    // TODO: check reaction with phy_obj radius = 6
    // radius<=5 problems start from this function
    float numerator = float(mapp_width) * sqrtf((2 * radius + mapp_width) * (2 * radius - mapp_width));
    float denominator = 2.0 * radius * radius;
    float lim = asinf(numerator / denominator);

    // making the theta smaller for more precise detection for phyobjects
    lim /= 2;

    return lim;
}

// given a phy_obj check if it has collided with the map
// if the collision has occured it returns true and the response vector which is passed by ref
bool phy_engine::check_map_collision(phy_obj *obj, Vector2 potential_position, Vector2 &response, map *mapp)
{
    // velocity angle i.e the direction of the object
    float v_angle = atan2f(obj->velocity.y, obj->velocity.x);

    // making a semi-circle that covers only the half where the object is facing
    //  semi-circle start and end angles
    float sc_start_angle = v_angle + (PI / 2.0);
    float sc_end_angle = v_angle - (PI / 2.0);

    // make sure passed response vector is null
    response.x = 0;
    response.y = 0;

    bool collision_occured = false;
    float lim = angle_step(obj->radius, mapp->tile_width); // TODO: angle_step should be a constructor call

    // for every point on the semi-circle separated by the lim angle
    // check for collision on the point via mapp_grid
    for (; sc_start_angle >= sc_end_angle; sc_start_angle -= lim)
    {
        // first calculate the coordinates of the collision_point from pov of (0,0)
        Vector2 collision_point{obj->radius * cosf(sc_start_angle), obj->radius * sinf(sc_start_angle)};

        // translation necessary cause currently collision_point are centered about (0,0)
        collision_point.x += potential_position.x;
        collision_point.y += potential_position.y;

        // now we can directly check with the map via map_grid
        // check if collision with between the collision_point and the map has occurred

        // conversion from pixel co-ordinates to map_co-ordinates
        int map_x = collision_point.x / 10;
        int map_y = collision_point.y / 10;

        bool clamp = false;
        // TODO: map out of bounds check !!!
        // clamp x
        if (map_x < 0)
        {
            map_x = 0;
            clamp = true;
        }
        else if (map_x >= 100)
        {
            map_x = 99;
            clamp = true;
        }

        // clamp y
        if (map_y < 0)
        {
            map_y = 0;
            clamp = true;
        }
        else if (map_y >= 60)
        {
            map_y = 59;
            clamp = true;
        }

        // TODO: does clamp condition even make sense
        //  if there is something other than 'S' in the map then yes collision has occured
        if (mapp->map_grid[map_y][map_x] != 'S' && clamp == false)
        {
            // translate again before addition to center around (0,0)
            // hence response vector would be centered about (0,0)
            response.x += collision_point.x - potential_position.x;
            response.y += collision_point.y - potential_position.y;

            collision_occured = true;
        }
        else if (clamp == true)
        {
            // translate again before addition to center around (0,0)
            response.x += collision_point.x - potential_position.x;
            response.y += collision_point.y - potential_position.y;

            collision_occured = true;
        }
    }

    return collision_occured; // response is returned via by ref parameter passed in
}

// apply gravity to a single phy object
// does not directly modifies the position instead
// return the potential position after applying the calculations
Vector2 phy_engine::apply_gravity(phy_obj *obj)
{
    // gravity downard
    obj->acceleration.y += 10.0f;

    // velocity due to gravity
    obj->velocity.x += obj->acceleration.x * GetFrameTime();
    obj->velocity.y += obj->acceleration.y * GetFrameTime();

    // don't directly modify objects position instead use a temp variable for calculations instead
    Vector2 potential_position{obj->position.x, obj->position.y};
    potential_position.x += obj->velocity.x * GetFrameTime();
    potential_position.y += obj->velocity.y * GetFrameTime();

    // reset gravity so it becomes constant
    obj->acceleration = {0, 0};
    obj->is_stable = false; // object is moving hence not stable

    return potential_position;
}

void phy_engine::insertAtTail(phy_obj *value)
{
    LinkedList<phy_obj *>::insertAtTail(value);
    total_obj++;
}

phy_engine::phy_engine() : total_obj{0}
{
}

// go through all the nodes and delete the actual objects
// before deleting the linked list pointers
phy_engine::~phy_engine()
{
    Node<phy_obj *> *tmp = head;

    while (tmp != nullptr)
    {
        phy_obj *obj = tmp->data;
        delete obj; // dynamic data of every node of linked list

        total_obj--;
        tmp = tmp->next;
    }
}
