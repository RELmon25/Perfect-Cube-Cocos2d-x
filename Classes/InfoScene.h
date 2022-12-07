#ifndef __InfoScene__
#define __InfoScene__

#include "cocos2d.h"

class InfoScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	cocos2d::LayerColor* _bgColor;

    //animation
    cocos2d::Vector<cocos2d::SpriteFrame*> explicacion;

	//menu

	cocos2d::MenuItemImage* regreso;
	void returnToPrevScene(Ref* pSender);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InfoScene);
};

#endif // __InfoScene__
