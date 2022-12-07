#include "MenuScene.h"
#include "SettingsScene.h"
#include "Scoreboard.h"
#include "GameScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>


USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //inicio
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("AudioBegin.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("ThatchedVillagers.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("correct.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("error.mp3");
    */

    UserDefault* def = UserDefault::getInstance();

    //audio

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioBegin.mp3", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }

    //background mode

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
        off = MenuItemImage::create("LightOff.png", "LightOff.png", CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
        off = MenuItemImage::create("DarkOff.png", "DarkOff.png", CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    }

    def->flush();

    this->addChild(_bgColor, -10);

    //interfaz
    play = MenuItemImage::create("PlayNormal.png", "PlaySelected.png", CC_CALLBACK_1(MenuScene::changeSceneToGame, this));
    highscores = MenuItemImage::create("ScoreNormal.png", "ScoreSelected.png", CC_CALLBACK_1(MenuScene::changeSceneToScores, this));
    settings = MenuItemImage::create("SetNormal.png","SetSelected.png", CC_CALLBACK_1(MenuScene::changeSceneToSettings, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + play->getContentSize().height / 4;
    play->setPosition(Vec2(x, y));
    highscores->setPosition(Vec2((x - play->getContentSize().width / 4 -20), (y - play->getContentSize().height / 2 -20)));
    settings->setPosition(Vec2((x + play->getContentSize().width / 4 + 20), (y - play->getContentSize().height / 2 - 20)));
    off->setPosition(Vec2(x*2 - off->getContentSize().width/2 -10, off->getContentSize().height/2 +10));

    auto menu = Menu::create(play, highscores, settings, off, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    ////////////////////////////
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    }
    def->flush();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MenuScene::changeSceneToSettings(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuScene::changeSceneToScores(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = Scoreboard::createScene();
    Director::getInstance()->replaceScene(scene);
}
void MenuScene::changeSceneToGame(Ref* pSender) {
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