#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	cocos2d::LayerColor* _bgColor;

	//sprites

	cocos2d::Sprite* blueSquare;
	cocos2d::Sprite* redRombo;
	cocos2d::Sprite* mangoRombo;

	//function
	void ToMainMenu(Ref* pSender);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__