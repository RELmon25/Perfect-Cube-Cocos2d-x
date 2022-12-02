#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //
    std::vector<std::string> Color;
    int i;
    std::string Mode;
    float min;
    float max;
    int CurrentScore;
    bool victory;
    int noLives;

    cocos2d::LayerColor* _bgColor;

    cocos2d::Label* score;

    //sprites
    cocos2d::Sprite* lives;
    cocos2d::Sprite* cube;
    cocos2d::Sprite* topIzq;
    cocos2d::Sprite* topDer;
    cocos2d::Sprite* botIzq;
    cocos2d::Sprite* botDer;

    //menu
    cocos2d::MenuItemImage* pause;
    cocos2d::MenuItemImage* home;

    void changeSceneToMenu(Ref* pSender);
    void changeSceneToPause(Ref* pSender);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void initMySprites(cocos2d::Sprite* MySprite, int bm);

    void youWinned();
    void youLose();
    void reset();

private:
    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

    bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif // __GAME_SCENE__