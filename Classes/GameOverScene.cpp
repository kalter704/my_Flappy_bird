#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int temp_score)
{
    score = temp_score;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
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
    
    auto retry_item = MenuItemImage::create("retry.png", "retry clicked.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this));
    retry_item->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));
    
    auto main_menu_item = MenuItemImage::create("menu button.png", "menu button clicked.png", CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this));
    main_menu_item->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4));  

    auto menu = Menu::create(retry_item, main_menu_item, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    //UserDefault *def = UserDefault::sharedUserDefault();

    //
    //auto high_score = def->getIntegerForKey("HIGHSCORE FLAPPY", 0);

    //if(score > high_score) {
    //    high_score = score;
    //    def->setIntegerForKey("HIGHSCORE FLAPPY", high_score);
    //}

    //def->flush();
    
    __String *temp_score = __String::createWithFormat("%i", score);

    auto  current_score = LabelTTF::create(temp_score->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    current_score->setPosition(Point(visibleSize.width * 0.25 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(current_score);    

    //__String *temp_high_score = __String::createWithFormat("%i", high_score);
    __String *temp_high_score = __String::createWithFormat("%i", score);

    auto high_score_lable = LabelTTF::create(temp_high_score->getCString(), "font/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);  
    high_score_lable->setColor(Color3B::YELLOW);
    high_score_lable->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(high_score_lable);

    return true;
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *pSender) {
    auto main_menu = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, main_menu));
}

void GameOverScene::goToGameScene(cocos2d::Ref *pSender) {
    auto game_scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, game_scene));
}