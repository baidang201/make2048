#ifndef _CardSprite_
#define _CardSprite_

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite
{
public:
	static CardSprite* createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	virtual bool init();

	CREATE_FUNC(CardSprite);


	//设置数字
	void setNumber(int num);

	//获取数字
	int getNumber();
private:
	//show NUM
	int number;
	void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	//定义显示数字的控件
	cocos2d::LabelTTF* labTTFCardNumber;


	//背景
	cocos2d::LayerColor* layerColorBG;

};


#endif // _CardSprite_