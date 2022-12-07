#ifndef __Scoreboard__
#define __Scoreboard__

#include "cocos2d.h"

class Scoreboard : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::LayerColor* _bgColor;

    cocos2d::Label* score1;
    cocos2d::Label* score2;
    cocos2d::Label* score3;

    //sprites

    cocos2d::Sprite* mainIcon;
    cocos2d::Sprite* imgFirst;
    cocos2d::Sprite* imgSecond;
    cocos2d::Sprite* imgThird;

	//menu

	cocos2d::MenuItemImage* regreso;
	void changeSceneToMenu(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scoreboard);
};

#endif // __Scoreboard__
