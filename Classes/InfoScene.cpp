#include "InfoScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* InfoScene::createScene()
{
    return InfoScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool InfoScene::init()
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
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
    }

    def->flush();

    this->addChild(_bgColor, -10);
    //

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;

    //animacion

    auto mySprite = Sprite::create("1.png");
    mySprite->setPosition(Vec2(x ,y + mySprite->getContentSize().height/4));
    this->addChild(mySprite, 0);

    Vector<SpriteFrame*> informacion;
    informacion.reserve(6);
    informacion.pushBack(SpriteFrame::create("1.png",Rect(0,0,visibleSize.width-20,352)));
    informacion.pushBack(SpriteFrame::create("2.png", Rect(0, 0, visibleSize.width - 20, 352)));
    informacion.pushBack(SpriteFrame::create("3.png", Rect(0, 0, visibleSize.width - 20, 352)));
    informacion.pushBack(SpriteFrame::create("4.png", Rect(0, 0, visibleSize.width - 20, 352)));
    informacion.pushBack(SpriteFrame::create("5.png", Rect(0, 0, visibleSize.width - 20, 352)));
    informacion.pushBack(SpriteFrame::create("6.png", Rect(0, 0, visibleSize.width - 20, 352)));

    Animation* animation = Animation::createWithSpriteFrames(informacion, 1.7f);
    Animate* animate = Animate::create(animation);

    mySprite->runAction(RepeatForever::create(animate));

    //interfaz

    regreso = MenuItemImage::create("Return.png","ReturnSelected.png", CC_CALLBACK_1(InfoScene::returnToPrevScene, this));

    regreso->setPosition(Vec2(x,y - mySprite->getContentSize().height / 4 - regreso->getContentSize().height/2 - 40));

    auto menu = Menu::create(regreso, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    ////////////////////////////
    return true;
}

void InfoScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void InfoScene::returnToPrevScene(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
    }
    def->flush();

    Director::getInstance()->popScene();
}