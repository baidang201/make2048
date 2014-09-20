#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);


	//插入手势识别事件
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	virtual void onTouchEnden(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	//上下左右的方法
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();


	//随机卡牌生成
	void autoCreateCard();

	//游戏是否继续
	void doCheckGameOver();
private:
	int firstX,firstY,endX,endY;

	//定义一个二维数组
	CardSprite* cardArr[4][4];

	//创建卡牌
	void createCardSprint(cocos2d::Size size);

	int score;
	cocos2d::LabelTTF* labTTFCardNumber;
};

#endif // __HELLOWORLD_SCENE_H__
