#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    flappy_bird = Sprite::create("ball.png");
    flappy_bird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto flappy_body = PhysicsBody::createCircle(flappy_bird->getContentSize().width / 2);
    flappy_body->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappy_body->setContactTestBitmask(true);

    flappy_bird->setPhysicsBody(flappy_body);

    layer->addChild(flappy_bird, 100);
    
    isFalling = true;
}

void Bird::fall() {
    if(isFalling == true) {
        flappy_bird->setPositionX(visibleSize.width / 2 + origin.x);
        flappy_bird->setPositionY(flappy_bird->getPositionY() - BIRD_FALLING_SPEED * visibleSize.height);
    } else {
        flappy_bird->setPositionX(visibleSize.width / 2 + origin.x);
        flappy_bird->setPositionY(flappy_bird->getPositionY() + BIRD_FLYING_SPEED * visibleSize.height);
    }
}
