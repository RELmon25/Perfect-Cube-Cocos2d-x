#include "SettingsScene.h"
#include "MenuScene.h"
#include "InfoScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
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

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
        mode = MenuItemImage::create("LightMode.png", "ModeSelected.png", CC_CALLBACK_1(SettingsScene::changeMode, this));
        mainIcon = Sprite::create("SetBlack.png");
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
        mode = MenuItemImage::create("DarkMode.png", "ModeSelected.png", CC_CALLBACK_1(SettingsScene::changeMode, this));
        mainIcon = Sprite::create("SetWhite.png");
    }

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        audio = MenuItemImage::create("Sound.png", "SoundSelected.png", CC_CALLBACK_1(SettingsScene::changeAudio, this));
        //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioBegin.mp3", true);
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    else {
        audio = MenuItemImage::create("NoSound.png", "SoundSelected.png", CC_CALLBACK_1(SettingsScene::changeAudio, this));
    }

    def->flush();

    this->addChild(_bgColor, -10);

    //animacion



    //interfaz

    info = MenuItemImage::create("Info.png", "InfoSelected.png", CC_CALLBACK_1(SettingsScene::changeSceneToInfo,this));
    regreso = MenuItemImage::create("Return.png","ReturnSelected.png", CC_CALLBACK_1(SettingsScene::changeSceneToMenu, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    float w = audio->getContentSize().width;
    float h = audio->getContentSize().height;

    mainIcon->setPosition(Vec2(x,(y + h + 60)));

    audio->setPosition(Vec2((x - w / 2 - 20), y));
    mode->setPosition(Vec2((x + w / 2 + 20),y));
    info->setPosition(Vec2((x - w / 2 - 20), (y - h - 20)));
    regreso->setPosition(Vec2((x + w / 2 + 20), (y - h - 20)));

    auto menu = Menu::create(audio, regreso, mode, info, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(mainIcon, 0);
    this->addChild(menu, 1);

    ////////////////////////////
    return true;
}


void SettingsScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SettingsScene::changeMode(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();

    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    }

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        def->setIntegerForKey("GB_MODE", 1);
        mode->setNormalImage(Sprite::create("DarkMode.png"));
        mainIcon->setTexture("SetWhite.png");
        _bgColor->setColor(Color3B(0, 0, 0));
    }
    else {
        def->setIntegerForKey("GB_MODE", 0);
        mode->setNormalImage(Sprite::create("LightMode.png"));
        mainIcon->setTexture("SetBlack.png");
        _bgColor->setColor(Color3B(255, 255, 255));
    }

    def->flush();
}

void SettingsScene::changeAudio(Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    UserDefault* def = UserDefault::getInstance();

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        def->setIntegerForKey("Sound", 1);
        audio->setNormalImage(Sprite::create("NoSound.png"));
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    else {
        def->setIntegerForKey("Sound", 0);
        audio->setNormalImage(Sprite::create("Sound.png"));
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioBegin.mp3", true);
        //CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }

    def->flush();
}
void SettingsScene::changeSceneToMenu(Ref* pSender) {
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

void SettingsScene::changeSceneToInfo(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = InfoScene::createScene();
    Director::getInstance()->pushScene(scene);
}