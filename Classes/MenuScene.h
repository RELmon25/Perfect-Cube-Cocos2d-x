#ifndef __Menu_Scene__
#define __Menu_Scene__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::LayerColor* _bgColor;

	//menu

	cocos2d::MenuItemImage* settings;
	cocos2d::MenuItemImage* play;
	cocos2d::MenuItemImage* highscores;
	cocos2d::MenuItemImage* off;

	void changeSceneToSettings(Ref* pSender);
	void changeSceneToScores(Ref* pSender);
	void changeSceneToGame(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __Menu_Scene__
