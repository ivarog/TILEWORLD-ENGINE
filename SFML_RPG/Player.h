#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    //variables
    bool attacking;

    //Initializer functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, std::map<std::string, sf::Texture>& textures);
    virtual ~Player();

    //Functions
    void updateAttack();
    void updateAnimation(const float& dt); 
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

