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

#include "MenuScene.h"
#include "SettingsScene.h"
#include "Scoreboard.h"
#include "GameScene.h"

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background mode

    UserDefault* def = UserDefault::getInstance();

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) _bgColor = LayerColor::create(Color4B(255, 255, 255, 255));
    else _bgColor = LayerColor::create(Color4B(0, 0, 0, 255));

    def->flush();

    this->addChild(_bgColor, -10);

    //animacion

    //interfaz
    play = MenuItemImage::create("PlayNormal.png", "PlaySelected.png", CC_CALLBACK_1(MenuScene::changeSceneToGame, this));
    highscores = MenuItemImage::create("ScoreNormal.png", "ScoreSelected.png", CC_CALLBACK_1(MenuScene::changeSceneToScores, this));
    settings = MenuItemImage::create("SetNormal.png","SetSelected.png", CC_CALLBACK_1(MenuScene::changeSceneToSettings, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + play->getContentSize().height / 4;
    play->setPosition(Vec2(x, y));
    highscores->setPosition(Vec2((x - play->getContentSize().width / 4 -20), (y - play->getContentSize().height / 2 -20)));
    settings->setPosition(Vec2((x + play->getContentSize().width / 4 + 20), (y - play->getContentSize().height / 2 - 20)));

    auto menu = Menu::create(play, highscores, settings, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    ////////////////////////////
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MenuScene::changeSceneToSettings(Ref* pSender) {
    auto scene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuScene::changeSceneToScores(Ref* pSender) {
    auto scene = Scoreboard::createScene();
    Director::getInstance()->replaceScene(scene);
}
void MenuScene::changeSceneToGame(Ref* pSender) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}