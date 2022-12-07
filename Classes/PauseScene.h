#ifndef __Pause_Scene__
#define __Pause_Scene__

#include "cocos2d.h"

class PauseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::LayerColor* _bgColor;

	//sprites

	cocos2d::Sprite* mainIcon;
	//cocos2d::Sprite* blue_square;

	//menu

	cocos2d::MenuItemImage* mode;
	cocos2d::MenuItemImage* audio;
	cocos2d::MenuItemImage* restart;
	cocos2d::MenuItemImage* unpause;
	cocos2d::MenuItemImage* info;

	void changeMode(Ref* pSender);
	void changeAudio(Ref* pSender);
	void changeSceneToGameRestart(Ref* pSender);
	void changeSceneToGameUnpause(Ref* pSender);
	void changeSceneToInfo(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseScene);
};

#endif // __Pause_Scene__
