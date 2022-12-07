#ifndef __EndGame__
#define __EndGame__

#include "cocos2d.h"

class EndGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::LayerColor* _bgColor;

    cocos2d::Label* score;

	//menu

	cocos2d::MenuItemImage* reiniciar;
    cocos2d::MenuItemImage* home;

	void changeSceneToGame(Ref* pSender);
    void changeSceneToMenu(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EndGame);
};

#endif // __Scoreboard__
