#include "HelloWorldScene.h"
#include "MenuScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //inicio
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("AudioBegin.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("ThatchedVillagers.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("correct.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("error.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("trumpets.mp3");
    //

    UserDefault* def = UserDefault::getInstance();

    //audio

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("AudioBegin.mp3", true);
    }

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    //background mode
    if (bgMode == 0) _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
    else _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));

    def->flush();

    this->addChild(_bgColor, -10);

    /////////////////

    blueSquare = Sprite::create("BlueSquare.png");
    redRombo = Sprite::create("RedRombo.png");
    mangoRombo = Sprite::create("MangoRombo.png");

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    float w = blueSquare->getContentSize().width;
    float h = blueSquare->getContentSize().height;

    blueSquare->setPosition(Vec2(x, y * 2 + h / 2 ));
      redRombo->setPosition(Vec2(x, y * 2 + h / 2 ));
    mangoRombo->setPosition(Vec2(x, y * 2 + h / 2 ));

    this->addChild(blueSquare, 1);
    this->addChild(redRombo, 0);
    this->addChild(mangoRombo, 0);

    auto move1 = MoveTo::create(0.25, Vec2(x, y + 15));
    auto spin = RotateBy::create(0.5, -405);
    DelayTime* pause1 = DelayTime::create(0.75);
    auto func = CallFuncN::create(CC_CALLBACK_1(HelloWorld::ToMainMenu, this));

    DelayTime* pause2 = DelayTime::create(0.75);
    auto move2 = MoveTo::create(0.0, Vec2(x, y + 15));
    auto move3 = MoveTo::create(0.5, Vec2(x - w / 4 - 20, y - h / 2 - 20 + 15));
    auto move4 = MoveTo::create(0.5, Vec2(x + w / 4 + 20, y - h / 2 - 20 + 15));

    auto seq2 = Sequence::create(pause2, move2, move3, nullptr);
    mangoRombo->runAction(seq2);

    auto seq3 = Sequence::create(pause2, move2, move4, nullptr);
    redRombo->runAction(seq3);

    auto seq = Sequence::create(move1, spin, pause1, func, nullptr);
    blueSquare->runAction(seq);
    ////////////////////////////
    return true;
}

void HelloWorld::ToMainMenu(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    def->flush();
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}