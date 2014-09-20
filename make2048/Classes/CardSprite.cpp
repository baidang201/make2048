#include "CardSprite.h"
USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	CardSprite* enemy=new CardSprite();

	if(enemy && enemy->init() )
	{
		enemy->enemyInit(numbers, wight, height, CardSpriteX, CardSpriteY);

		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init()
{
	if(!Sprite::init())
	{
		return false;
	}

	return true;
}




//设置数字
void CardSprite::setNumber(int num)
{
	number = num;

	//美化根据数字大小调整字体大小
	if(number >= 1024)
	{
		labTTFCardNumber->setFontSize(40);
	}
	else if(number >= 128)
	{
		labTTFCardNumber->setFontSize(60);
	}
	else if(number >= 16)
	{
		labTTFCardNumber->setFontSize(90);
	}
	else if(number >= 0)
	{
		labTTFCardNumber->setFontSize(100);
	}

	switch(number)
	{
	case 0:
		layerColorBG->setColor(Color3B(200, 190, 180));
		break;
	case 2:
		layerColorBG->setColor(Color3B(240, 230, 220));
		break;
	case 4:
		layerColorBG->setColor(Color3B(240, 220, 200));
		break;
	case 8:
		layerColorBG->setColor(Color3B(240, 180, 120));
		break;
	case 16:
		layerColorBG->setColor(Color3B(240, 140, 90));
		break;
	case 32:
		layerColorBG->setColor(Color3B(240, 120, 90));
		break;
	case 64:
		layerColorBG->setColor(Color3B(240, 90, 60));
		break;
	case 128:
		layerColorBG->setColor(Color3B(240, 90, 60));
		break;
	case 256:
		layerColorBG->setColor(Color3B(240, 200, 70));
		break;
	case 512:
		layerColorBG->setColor(Color3B(240, 200, 70));
		break;
	case 1024:
		layerColorBG->setColor(Color3B(0, 130, 0));
		break;
	case 2048:
		layerColorBG->setColor(Color3B(0, 130, 0));
		break;
	default:
		break;
	}							


	if(number > 0)
	{
		labTTFCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else
	{
		labTTFCardNumber->setString("");
	}
}

//获取数字
int CardSprite::getNumber()
{
	return number;
}

void CardSprite::enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	number = numbers;

	layerColorBG = LayerColor::create(  Color4B(200, 190, 180, 255), wight-15, height-15);
	layerColorBG->setPosition(Point(CardSpriteX, CardSpriteY) );


	if(number >0 )
	{
		labTTFCardNumber = LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN_WG", 100);
		labTTFCardNumber ->setPosition(Point(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	else
	{
		labTTFCardNumber = LabelTTF::create("", "HirakakuProN_WG", 100);
		labTTFCardNumber ->setPosition(Point(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2));
		layerColorBG->addChild(labTTFCardNumber);
	}

	addChild(layerColorBG);
}