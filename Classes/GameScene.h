#ifndef __GAME_SCENE__
#define __GAME_SCENE__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    //
    std::vector<std::string> Color;
    int i;
    std::string Mode;
    float men;
    float may;
    int CurrentScore;
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

    //

    void loseLife();
    void incScore();
    void resete();
    void loseGame();
};

#endif // __GAME_SCENE__