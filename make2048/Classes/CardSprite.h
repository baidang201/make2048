#ifndef _CardSprite_
#define _CardSprite_

#include "cocos2d.h"

class CardSprite:public cocos2d::Sprite
{
public:
	static CardSprite* createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	virtual bool init();

	CREATE_FUNC(CardSprite);


	//��������
	void setNumber(int num);

	//��ȡ����
	int getNumber();
private:
	//show NUM
	int number;
	void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	//������ʾ���ֵĿؼ�
	cocos2d::LabelTTF* labTTFCardNumber;


	//����
	cocos2d::LayerColor* layerColorBG;

};


#endif // _CardSprite_