#include "GameScene.h"
#include "MenuScene.h"
#include "PauseScene.h"
#include "EndGame.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    //inicio
    if (!Scene::init())
    {
        return false;
    }

    auto listener = EventListenerTouchOneByOne().create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //
    Color.push_back("Blue");
    Color.push_back("Mango");
    Color.push_back("Red");
    Color.push_back("Teal");
    Color.push_back("Mora");

    srand(time(NULL));

    i = rand() % 5;

    may = 160;
    men = 40;

    //background & mode & audio

    if (Color[i] == "Blue") _bgColor = LayerColor::create(Color4B(77, 177, 255, 255));
    if (Color[i] == "Mango") _bgColor = LayerColor::create(Color4B(255, 179, 0, 255));
    if (Color[i] == "Red") _bgColor = LayerColor::create(Color4B(255, 92, 119, 255));
    if (Color[i] == "Teal") _bgColor = LayerColor::create(Color4B(0, 206, 172, 255));
    if (Color[i] == "Mora") _bgColor = LayerColor::create(Color4B(176, 131, 240, 255));

    this->addChild(_bgColor, -10);

    UserDefault* def = UserDefault::getInstance();

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) Mode = "Light";
    else Mode = "Dark";

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0) CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Wallpaper.mp3", true);

    def->flush();

    lives = Sprite::create(Mode + Color[i] + "3L.png");
    noLives = 3;

    //interfaz

    cube = Sprite::create(Mode + "Cube.png");
    cube->setScale(0.1f, 0.1f);

    topIzq = Sprite::create(Mode + "Bar.png");
    topDer = Sprite::create(Mode + "Bar.png");
    botIzq = Sprite::create(Mode + "Bar.png");
    botDer = Sprite::create(Mode + "Bar.png");

    score = Label::createWithTTF("000", "fonts/q_modular.ttf", 30.0f);
    if (Mode == "Light") score->setColor(Color3B::WHITE);
    else score->setColor(Color3B::BLACK);
    score->setAlignment(TextHAlignment::CENTER);

    pause = MenuItemImage::create(Mode + Color[i] + "Pause.png", Mode + Color[i] + "PauseSelected.png", CC_CALLBACK_1(GameScene::changeSceneToPause, this));
    home = MenuItemImage::create(Mode + Color[i] + "Home.png", Mode + Color[i] + "HomeSelected.png", CC_CALLBACK_1(GameScene::changeSceneToMenu, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height - 20;
    float h = score->getContentSize().height;

    score->setPosition(Vec2(x, y - h / 2));

    cube->setPosition(Vec2(x, y - h - 80));
    cube->setRotation(-45.0f);

    h = lives->getContentSize().height;
    float w = lives->getContentSize().width;

    lives->setPosition(Vec2(origin.x + 15 + w / 2, y - h / 2));

    h = pause->getContentSize().height;
    w = pause->getContentSize().width;

    x = origin.x + visibleSize.width - 15;
    pause->setPosition(Vec2(x - w / 2, y - h / 2));
    home->setPosition(Vec2(x - w / 2, y - h / 2 - h - 20));

    auto menu = Menu::create(pause, home, NULL);
    menu->setPosition(Vec2::ZERO);

    topIzq->setPosition(Vec2(origin.x - topIzq->getContentSize().width / 2, origin.y + topIzq->getContentSize().height));
    botIzq->setPosition(Vec2(origin.x - botIzq->getContentSize().width / 2, origin.y + botIzq->getContentSize().height / 2));

    topDer->setPosition(Vec2(origin.x + visibleSize.width + topDer->getContentSize().width / 2, origin.y + topDer->getContentSize().height));
    botDer->setPosition(Vec2(origin.x + visibleSize.width + botDer->getContentSize().width / 2, origin.y + botDer->getContentSize().height / 2));



    this->addChild(score, 0);
    this->addChild(lives, 0);
    this->addChild(cube, 2);
    this->addChild(menu, 1);
    this->addChild(topIzq, 2);
    this->addChild(topDer, 2);
    this->addChild(botIzq, 2);
    this->addChild(botDer, 2);

    //

    auto action1 = MoveTo::create(0.5f, Vec2(origin.x - 80, origin.y + topIzq->getContentSize().height));
    topIzq->runAction(action1);

    auto action2 = MoveTo::create(0.5f, Vec2(origin.x - 20, origin.y + botIzq->getContentSize().height / 2));
    botIzq->runAction(action2);

    auto action3 = MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width + 80, origin.y + topDer->getContentSize().height));
    topDer->runAction(action3);

    auto action4 = MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width + 20, origin.y + botDer->getContentSize().height / 2));
    botDer->runAction(action4);

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto grow = ScaleTo::create(3, 1.0f);
    cube->runAction(grow);
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    cube->stopAllActions();
    auto rotate = RotateTo::create(0.25f, 0);
    float currentScale = cube->getScale();
    float currentSize = currentScale*cube->getContentSize().height;
    auto func = CallFuncN::create(CC_CALLBACK_0(GameScene::resete, this));
    auto fScore = CallFuncN::create(CC_CALLBACK_0(GameScene::incScore, this));
    auto fLife = CallFuncN::create(CC_CALLBACK_0(GameScene::loseLife, this));
    auto fclg = CallFuncN::create(CC_CALLBACK_0(GameScene::loseGame, this));
    if (currentSize < men) {
        auto move1 = MoveTo::create(0.5, Vec2( 187.5, 0 - (currentScale * cube->getContentSize().height)));
        DelayTime* pause = DelayTime::create(0.5);
        auto move2 = MoveTo::create(0, Vec2(187.5, 537));
        auto degrow = ScaleTo::create(0.25, 0.1);
        auto rotate2 = RotateTo::create(0.25, -45);      
        auto seq = Sequence::create(rotate, move1, fLife, pause, fclg, move2, rotate2, degrow, func, nullptr);
        cube->runAction(seq);
    }
    else {
        if (currentSize >= may) {
            auto move1 = MoveTo::create(0.25f, Vec2(187.5, 185 + (currentScale*cube->getContentSize().height)/2 ));
            DelayTime* pause = DelayTime::create(0.5);
            auto move2 = MoveTo::create(0.25, Vec2(187.5, 537));
            auto degrow = ScaleTo::create(0.25, 0.1);
            auto rotate2 = RotateTo::create(0.25, -45);
            auto seq = Sequence::create(rotate, move1, fLife, pause, fclg, move2, rotate2, degrow, func, nullptr);
            cube->runAction(seq);
        }
        else {
            auto move1 = MoveTo::create(0.25f, Vec2(187.5, 125 + (currentScale * cube->getContentSize().height)  / 2));
            DelayTime* pause = DelayTime::create(0.5);
            auto move2 = MoveTo::create(0.25, Vec2(187.5, 537));
            auto degrow = ScaleTo::create(0.25, 0.1);
            auto rotate2 = RotateTo::create(0.25, -45);
            auto seq = Sequence::create(rotate, move1, fScore, pause, move2, rotate2, degrow, func, nullptr);
            cube->runAction(seq);
        }
    }

    return;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void GameScene::changeSceneToPause(Ref* pSender) {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
        //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    def->flush();
    auto scene = PauseScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScene::changeSceneToMenu(Ref* pSender) {
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

void GameScene::loseLife() {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("error.mp3");
    def->flush();

    noLives--;
    std::string x = std::to_string(noLives);
    lives->setTexture(Mode + Color[i] + x + "L.png");
    
    /*
    if (noLives == 0) {
        UserDefault* def = UserDefault::getInstance();
        auto lastScore = def->getIntegerForKey("LastScore", 0);
        def->setIntegerForKey("LastScore",CurrentScore);
        def->flush();

        std::chrono::seconds duration(1);
        std::this_thread::sleep_for(duration);

        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

        auto scene = EndGame::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    */
}

void GameScene::loseGame() {
    if (noLives == 0) {
        UserDefault* def = UserDefault::getInstance();
        auto lastScore = def->getIntegerForKey("LastScore", 0);
        def->setIntegerForKey("LastScore", CurrentScore);
        def->flush();

        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

        auto scene = EndGame::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}

void GameScene::incScore() {
    UserDefault* def = UserDefault::getInstance();
    auto soundMode = def->getIntegerForKey("Sound", 0);
    if (soundMode == 0) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("correct.mp3");
    def->flush();
    CurrentScore++;
    std::string x;
    if (CurrentScore < 100) x = "0";
    if (CurrentScore < 10) x += "0";
    x += std::to_string(CurrentScore);
    score->setString(x);
}

void GameScene::resete() {
    i++;
    i %= 5;
    if (Color[i] == "Blue") _bgColor->setColor(Color3B(77, 177, 255));
    if (Color[i] == "Mango") _bgColor->setColor(Color3B(255, 179, 0));
    if (Color[i] == "Red") _bgColor->setColor(Color3B(255, 92, 119));
    if (Color[i] == "Teal") _bgColor->setColor(Color3B(0, 206, 172));
    if (Color[i] == "Mora") _bgColor->setColor(Color3B(176, 131, 240));

    /*
    UserDefault* def = UserDefault::getInstance();

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) Mode = "Light";
    else Mode = "Dark";

    auto soundMode = def->getIntegerForKey("Sound", 0);

    if (soundMode == 0 && !CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() ) CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    else CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    def->flush();
    ¨*/

    topIzq->setTexture(Mode + "Bar.png");
    topDer->setTexture(Mode + "Bar.png");
    botIzq->setTexture(Mode + "Bar.png");
    botDer->setTexture(Mode + "Bar.png");

    pause->setNormalImage(Sprite::create(Mode + Color[i] + "Pause.png"));
    pause->setSelectedImage(Sprite::create(Mode + Color[i] + "PauseSelected.png"));
    home->setNormalImage(Sprite::create(Mode + Color[i] + "Home.png"));
    home->setSelectedImage(Sprite::create(Mode + Color[i] + "HomeSelected.png"));

    if (Mode == "Light") score->setColor(Color3B::WHITE);
    else score->setColor(Color3B::BLACK);

    std::string x = std::to_string(noLives);
    lives->setTexture(Mode + Color[i] + x + "L.png");

    men = rand() % 85 + 45;
    int z = 260 - men;
    may = rand() % z + men + 10;

    auto action1 = MoveTo::create(0.5f, Vec2(0 - may/2, topIzq->getContentSize().height));
    topIzq->runAction(action1);

    auto action2 = MoveTo::create(0.5f, Vec2(0 - men/2, botIzq->getContentSize().height / 2));
    botIzq->runAction(action2);

    auto action3 = MoveTo::create(0.5f, Vec2(375 + may/2, topDer->getContentSize().height));
    topDer->runAction(action3);

    auto action4 = MoveTo::create(0.5f, Vec2(375 + men/2, botDer->getContentSize().height / 2));
    botDer->runAction(action4);
}