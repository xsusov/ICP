#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    GameObject();
    virtual void draw() = 0;    // pure virtual method for drawing various game object (used by viewer)
};

#endif // GAMEOBJECT_H
