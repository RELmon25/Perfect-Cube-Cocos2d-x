/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Scoreboard.h"
#include "MenuScene.h"

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
    //background mode

    UserDefault* def = UserDefault::getInstance();

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) {
        _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
        mainIcon = Sprite::create("ScoreBlack.png");
    }
    else {
        _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));
        mainIcon = Sprite::create("ScoreWhite.png");
    }

    def->flush();

    this->addChild(_bgColor, -10);

    //animacion

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
    imgSecond->setPosition(Vec2(x, y));
    imgThird->setPosition(Vec2(x, y - h - 10));

    regreso->setPosition(Vec2(x,(y - h - 10 - h / 2) / 2));

    auto menu = Menu::create(regreso, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(mainIcon, 0);
    this->addChild(imgFirst, 0);
    this->addChild(imgSecond, 0);
    this->addChild(imgThird, 0);
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
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}