#include "Scoreboard.h"
#include "MenuScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* Scoreboard::createScene()
{
    return Scoreboard::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scoreboard::init()
{
    //inicio
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    UserDefault* def = UserDefault::getInstance();

    std::string z;

    auto first = def->getIntegerForKey("FIRST", 0);
    if (first < 100) z = "0";
    if (first < 10) z += "0";
    z += std::to_string(first);

    score1 = Label::createWithTTF(z, "fonts/q_modular.ttf", 30.0f);

    auto second = def->getIntegerForKey("SECOND", 0);
    if (second < 100) z = "0";
    if (second < 10) z += "0";
    z += std::to_string(second);

    score2 = Label::createWithTTF(z, "fonts/q_modular.ttf", 30.0f);

    auto third = def->getIntegerForKey("THIRD", 0);
    if (third < 100) z = "0";
    if (third < 10) z += "0";
    z += std::to_string(third);

    score3 = Label::createWithTTF(z, "fonts/q_modular.ttf", 30.0f);

    //background mode

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
        mainIcon = Sprite::create("ScoreBlack.png");
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
        mainIcon = Sprite::create("ScoreWhite.png");
    }

    //sound

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }

    def->flush();

    this->addChild(_bgColor, -10);

    score1->setColor(Color3B::WHITE);
    score2->setColor(Color3B::WHITE);
    score3->setColor(Color3B::WHITE);

    score1->setAlignment(TextHAlignment::LEFT);
    score2->setAlignment(TextHAlignment::LEFT);
    score3->setAlignment(TextHAlignment::LEFT);

    //interfaz


    imgFirst = Sprite::create("1stPlace.png");
    imgSecond = Sprite::create("2ndPlace.png");
    imgThird = Sprite::create("3rdPlace.png");

    regreso = MenuItemImage::create("Return.png","ReturnSelected.png", CC_CALLBACK_1(Scoreboard::changeSceneToMenu, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    float h = imgFirst->getContentSize().height;

    mainIcon->setPosition(Vec2(x, (y + h + 10 + h / 2) / 2 + y));

    imgFirst->setPosition(Vec2(x, y + h + 10));
    score1->setPosition(Vec2(20+x, y + h + 12));

    imgSecond->setPosition(Vec2(x, y));
    score2->setPosition(Vec2(20+x, y+2));

    imgThird->setPosition(Vec2(x, y - h - 10));
    score3->setPosition(Vec2(20+x, y - h - 8));

    regreso->setPosition(Vec2(x,(y - h - 10 - h / 2) / 2));

    auto menu = Menu::create(regreso, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(mainIcon, 0);
    this->addChild(imgFirst, 0);
    this->addChild(imgSecond, 0);
    this->addChild(imgThird, 0);
    this->addChild(score1, 1);
    this->addChild(score2, 1);
    this->addChild(score3, 1);
    this->addChild(menu, 1);

    ////////////////////////////
    return true;
}

void Scoreboard::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void Scoreboard::changeSceneToMenu(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}