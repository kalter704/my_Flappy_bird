#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird {
public:
    Bird() {flappy_bird = NULL;}
    Bird(cocos2d::Layer *layer);

    void fall();
    void fly() { isFalling = false; }
    void stopFlying() { isFalling = true; }


private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite *flappy_bird;

    bool isFalling;
};

#endif // __BIRD_H__
