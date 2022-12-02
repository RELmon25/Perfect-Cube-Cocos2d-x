#include "GameScene.h"
#include "MenuScene.h"
#include "PauseScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //scene->getPhysicsWorld()->setGravity( Vec2( 0, 0) );

    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
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
    if (!Layer::init())
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

    //background & mode

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

    def->flush();

    //interfaz

    lives = Sprite::create(Mode + Color[i] + "3L.png");
    noLives = 3;

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
    auto cubeBody = PhysicsBody::createBox(cube->getContentSize(), PhysicsMaterial(0, 1, 0));
    cubeBody->setContactTestBitmask(1);
    cubeBody->setCollisionBitmask(1);
    cubeBody->setDynamic(false);
    cube->setPhysicsBody(cubeBody);
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

    initMySprites(topIzq, 2);
    initMySprites(botIzq, 3);
    initMySprites(topDer, 2);
    initMySprites(botDer, 3);

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

    //
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //
    return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        //victory = true;
        youWinned();
    }
    else {
        //victory = false;
        youLose();
    }

    return true;
}


bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto grow = ScaleTo::create(5, 1.0f);
    cube->runAction(grow);
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    cube->stopAllActions();
    auto rotate = RotateTo::create(0.5f, 0);
    cube->runAction(rotate);
    cube->getPhysicsBody()->setDynamic(true);
    //std::chrono::seconds duration(2);
    //std::this_thread::sleep_for(duration);
    //if(victory) youWinned();
    //else youLose();
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
    auto scene = PauseScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScene::changeSceneToMenu(Ref* pSender) {
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameScene::initMySprites(cocos2d::Sprite* MySprite, int bm) {
    auto spriteBody = PhysicsBody::createBox(Size(MySprite->getContentSize().width + 7, MySprite->getContentSize().height + 5), PhysicsMaterial(0, 0.2f, 1));
    spriteBody->setContactTestBitmask(bm);
    spriteBody->setCollisionBitmask(bm);
    spriteBody->setDynamic(false);
    MySprite->setPhysicsBody(spriteBody);
}

void GameScene::youWinned() {
    CurrentScore++;
    std::string x;
    if (CurrentScore < 100) x = "0";
    if (CurrentScore < 10) x += "0";
    x += std::to_string(CurrentScore);
    score->setString(x);
    reset();
    return;
}

void GameScene::youLose() {
    noLives--;
    std::string x = std::to_string(noLives);
    lives->setTexture(Mode + Color[i] + x + "L.png");
    //if(noLives == 0);
    reset();
    return;
}

void GameScene::reset() {
    UserDefault* def = UserDefault::getInstance();

    auto bgMode = def->getIntegerForKey("GB_MODE", 0);

    if (bgMode == 0) Mode = "Light";
    else Mode = "Dark";

    def->flush();

    cube->getPhysicsBody()->setDynamic(false);

    DelayTime* pause = DelayTime::create(0.5);
    auto move = MoveTo::create(0.5f, Vec2(375/2, 537));
    auto rotate = RotateTo::create(0.5f, -45);
    auto degrow = ScaleTo::create(0.5, 0.1f);
    auto seq = Sequence::create(pause, move, rotate, degrow, nullptr);
    cube->runAction(seq);



    return;
}