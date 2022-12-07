#include "MenuScene.h"
#include "EndGame.h"
#include "GameScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* EndGame::createScene()
{
    return EndGame::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool EndGame::init()
{
    //inicio
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //background mode

    UserDefault* def = UserDefault::getInstance();

    auto lastScore = def->getIntegerForKey("LastScore", 0);
    std::string z;
    if (lastScore < 100) z = "0";
    if (lastScore < 10) z += "0";
    z += std::to_string(lastScore);

    score = Label::createWithTTF(z, "fonts/q_modular.ttf", 70.0f);

    auto first = def->getIntegerForKey("FIRST", 0);
    auto second = def->getIntegerForKey("SECOND", 0);
    auto third = def->getIntegerForKey("THIRD", 0);
    if (lastScore >= first) {
        def->setIntegerForKey("THIRD", second);
        def->setIntegerForKey("SECOND", first);
        def->setIntegerForKey("FIRST", lastScore);

        //estrellita
        cocos2d::Sprite* stars = Sprite::create("three-stars.png");
        stars->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - stars->getContentSize().height/2 - 30));
        this->addChild(stars, -1);

        auto soundMode = def->getIntegerForKey("Sound", 0);
        if (soundMode == 0) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("trumpets.mp3");
    }
    else {
        if (lastScore >= second) {
            def->setIntegerForKey("THIRD", second);
            def->setIntegerForKey("SECOND", lastScore);
        }
        else {
            if (lastScore > third) {
                def->setIntegerForKey("THIRD", lastScore);
            }
        }
    }

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
        score->setColor(Color3B::BLACK);
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
        score->setColor(Color3B::WHITE);
    }

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }

    def->flush();

    score->setAlignment(TextHAlignment::CENTER);

    this->addChild(_bgColor, -10);

    //animacion

    //interfaz

    reiniciar = MenuItemImage::create("Reiniciar.png","ReturnSelected.png", CC_CALLBACK_1(EndGame::changeSceneToGame, this));
    home = MenuItemImage::create("Home.png", "InfoSelected.png", CC_CALLBACK_1(EndGame::changeSceneToMenu, this));


    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;

    reiniciar->setPosition(Vec2(x, y));

    score->setPosition(Vec2(x, y + reiniciar->getContentSize().height + 50));

    home->setPosition(Vec2(x,y- reiniciar->getContentSize().height - 30));


    auto menu = Menu::create(reiniciar, home, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);
    this->addChild(score, 0);

    ////////////////////////////
    return true;
}

void EndGame::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void EndGame::changeSceneToGame(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void EndGame::changeSceneToMenu(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioBegin.mp3", true);
    }
    def->flush();
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}