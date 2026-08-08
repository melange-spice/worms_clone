#pragma once
#include "linked_list.hpp"
#include "phy_obj.hpp"
#include "map.hpp"

// phy_engine is responsible for applying physics on all the phy_obj in the game
class phy_engine : public linked_list<phy_obj *>
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
