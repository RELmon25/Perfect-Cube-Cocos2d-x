#ifndef __Settings_Scene__
#define __Settings_Scene__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene
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
	cocos2d::MenuItemImage* regreso;
	cocos2d::MenuItemImage* info;

	void changeMode(Ref* pSender);
	void changeAudio(Ref* pSender);
	void changeSceneToMenu(Ref* pSender);
	void changeSceneToInfo(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SettingsScene);
};

#endif // __Settings_Scene__
