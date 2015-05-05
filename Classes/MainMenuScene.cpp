#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    auto background_sprite = Sprite::create("background.png");
    background_sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(background_sprite, 0);

    auto title_sprite = Sprite::create("title.png");
    title_sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height - title_sprite->getContentSize().height));

    this->addChild(title_sprite, 1);    

    auto play_item = MenuItemImage::create("play button.png", "play button clicked.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
    play_item->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    auto main_menu = Menu::create(play_item, NULL);
    main_menu->setPosition(Point::ZERO);

    this->addChild(main_menu);

    return true;
}

void MainMenuScene::goToGameScene(cocos2d::Ref *pSender) {
    auto game_scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(DISPLAY_TIME_SPLASH_SCENE, game_scene));
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
