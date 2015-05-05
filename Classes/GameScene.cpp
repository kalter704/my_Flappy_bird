#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background_sprite = Sprite::create("background.png");
    background_sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(background_sprite, 0);

    auto edge_body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edge_body->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edge_body->setContactTestBitmask(true);

    auto edge_node = Node::create();
    edge_node->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    edge_node->setPhysicsBody(edge_body);

    this->addChild(edge_node);

    this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);
    //this->schedule(schedule_selector(GameScene::spawnPipe, 0.005 * visibleSize.width));
    
    bird = new Bird(this);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    score = 0;

    __String *temp_score = __String::createWithFormat("%i", score);

    score_lable = Label::createWithTTF(temp_score->getCString(),  "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    score_lable->setColor(Color3B::WHITE);
    score_lable->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));

    this->addChild(score_lable, 1000000);

    this->scheduleUpdate();
    
    return true;
}

void GameScene::spawnPipe(float td) {
    pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK) ||
       (b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK)) 
    {
        auto game_over_scene = GameOverScene::createScene(score);
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, game_over_scene));
    } else {
        if((a->getCollisionBitmask() == BIRD_COLLISION_BITMASK && b->getCollisionBitmask() == POINT_COLLISION_BITMASK) ||
           (b->getCollisionBitmask() == BIRD_COLLISION_BITMASK && a->getCollisionBitmask() == POINT_COLLISION_BITMASK)) 
        {
            ++score;

            __String *temp_score = __String::createWithFormat("%i", score);

            score_lable->setString(temp_score->getCString());
        }
    }
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    bird->fly();
    
    this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);

    return true;
}

void GameScene::stopFlying(float dt) {
    bird->stopFlying();
}

void GameScene::update(float td) {
    bird->fall();
}