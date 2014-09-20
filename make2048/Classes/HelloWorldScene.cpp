#include "HelloWorldScene.h"
#include "CardSprite.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	score = 0;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//加入游戏背景
	auto layerColorBG= LayerColor::create(Color4B(100, 170, 160, 255));
	this->addChild(layerColorBG);


	auto labTTFCardNumberName = LabelTTF::create("score", "HirakakuProN_WG", 80);
	labTTFCardNumberName->setPosition(Point(visibleSize.width/5, visibleSize.height-150));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "HirakakuProN_WG", 80);
	labTTFCardNumber->setPosition(Point(visibleSize.width/2+100, visibleSize.height-150));
	addChild(labTTFCardNumber); 



#if 0  //使用CC_CALLBACK_2进行触摸屏事件监听注册,当前无法触发onTouchEnded，不懂为什么
	//监听手势识别
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this); 

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif

#if 1   //使用闭包函数进行触摸屏事件监听注册
	//监听手势识别
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch * touch, Event * e){  

		log(" --- onTouchBegan --- ");  
		Point touchP0=touch->getLocation();
		firstX = touchP0.x;
		firstY = touchP0.y;

		return true;
		//return false; //此处返回false，则onTouchMoved，onTouchEnded 不会被触发  
	};  
	touchListener->onTouchMoved = [](Touch * touch, Event * e){  

		log(" --- onTouchMoved --- ");  

		//return true;
		//onTouchMoved 没有返回值  
	};  
	touchListener->onTouchEnded = [this](Touch * touch, Event * e){  

		log(" --- onTouchEnded --- ");  
		//获取x轴和y轴的移动范围
		Point touchP0=touch->getLocation();
		endX = firstX - touchP0.x;
		endY=firstX - touchP0.y;

		bool IsMoveOK = false;
		//判断x轴和y轴的距离
		if(  abs(endX) > abs(endY) )
		{
			//左右移动
			if(endX+5>0)
			{
				//左
				IsMoveOK = doLeft();
			}
			else
			{
				IsMoveOK = doRight();
			}
		}
		else
		{
			//上下移动
			if(endY+5 < 0)
			{
				IsMoveOK = doUp();
			}
			else
			{
				IsMoveOK = doDown();
			}

		}


		if(IsMoveOK)
		{
			autoCreateCard();
		}
		doCheckGameOver();

		//onTouchEnded 没有返回值  
	};  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif   

#if 0 //使用闭包函数进行键盘事件监听注册
	//监听键盘事件
	auto touchListener = EventListenerKeyboard::create();
	touchListener->onKeyPressed = [this](EventKeyboard::KeyCode code ,Event * e)
	{
		bool IsMoveOK = false;
		switch( code)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			IsMoveOK = doUp();
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			IsMoveOK = doDown();
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			IsMoveOK = doLeft();
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			IsMoveOK = doRight();
			break;
		default:
			break;
		}
		if(IsMoveOK)
		{
			autoCreateCard();
		}
		doCheckGameOver();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
#endif
	//生成卡牌
	createCardSprint(visibleSize);

	autoCreateCard();
	autoCreateCard();

    return true;
}

void HelloWorld::doCheckGameOver()
{
	bool isGameOver = true;

	for(int y = 0; y< 4; y++)
	{
		for(int x =0; x<4; x++)
		{
			if(		cardArr[x][y]->getNumber() == 0
				||  (x>0 && cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber() )
				||  (x<3 && cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber() )
				||  (y>0 && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber() )
				||  (y<3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber() )
				)
			{
				isGameOver = false;
			}
		}
	}


	if(isGameOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

void HelloWorld::autoCreateCard()
{
	bool HasRoom = false;
	for(int m=0; m<4; m++)
	{
		for(int n=0; n<4; n++)
		{
			if ( cardArr[m][n]->getNumber() <= 0 )
			{
				HasRoom = true;
				break;
			}
		}
		if(HasRoom)
		{
			break;
		}
	}

	if( !HasRoom)
	{
		return;
	}

	int i = CCRANDOM_0_1()*4;
	int j = CCRANDOM_0_1()*4;


	//判断是否存在位置
	if( cardArr[i][j]->getNumber() > 0)
	{
		autoCreateCard();//不存在位置，继续递归
	}
	else
	{
		cardArr[i][j]->setNumber(CCRANDOM_0_1()*10<1?4:2);//随机放入4 或者 2
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::createCardSprint(cocos2d::Size size)
{
	//卡牌宽度和搞 
	int lon=(size.width - 28)/4;

	//4*4的单元格
	for(int j = 0; j<4; j++)
	{
		for(int i=0; i<4; i++)
		{
			CardSprite* card = CardSprite::createCardSprite(0, lon, lon, lon*j+20, lon*i+20+size.height/6);
			addChild(card);

			//添加到二维数组
			cardArr[j][i] = card;
		}
	}
}

//插入手势识别事件
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Point touchP0=touch->getLocation();
	firstX = touchP0.x;
	firstY=touchP0.y;

	return true;
}

void HelloWorld::onTouchEnden(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//获取x轴和y轴的移动范围
	Point touchP0=touch->getLocation();
	endX = firstX - touchP0.x;
	endY=firstX - touchP0.y;

	bool IsMoveOK = false;
	//判断x轴和y轴的距离
	if(  abs(endX) > abs(endY) )
	{
		//左右移动
		if(endX+5>0)
		{
			//左
			IsMoveOK = doLeft();
		}
		else
		{
			IsMoveOK = doRight();
		}
	}
	else
	{
		//上下移动
		if(endY+5 > 0)
		{
			IsMoveOK = doUp();
		}
		else
		{
			IsMoveOK = doDown();
		}

	}


	if(IsMoveOK)
	{
		autoCreateCard();
	}
	doCheckGameOver();

	//return true;
}

//上下左右的方法
bool HelloWorld::doLeft()	 
{
	bool isdo =false;
	for(int y = 0; y<4; y++)
	{
		for(int x=0; x<4; x++)
		{
			for(int x1 = x+1; x1<4; x1++)
			{
				if(cardArr[x1][y]->getNumber() >0 )
				{
					if( cardArr[x][y] ->getNumber() <= 0 )//迭代
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x--;
						isdo = true;
					}
					else if( cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())//合并
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);
						isdo = true;

						score+=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());
					}
					break;
				}
			}
		}
	}

	log("doLeft");
	return isdo;
}
bool HelloWorld::doRight()	
{
	bool isdo =false;
	for(int y = 0; y<4; y++)
	{
		for(int x=3; x>=0; x--)
		{
			for(int x1 = x-1; x1>=0; x1--)
			{
				if(cardArr[x1][y]->getNumber() >0 )
				{
					if( cardArr[x][y] ->getNumber() <= 0 )//迭代
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x++;
						isdo = true;
					}
					else if( cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())//合并
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);
						isdo = true;

						score+=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

					}
					break;
				}
			}
		}
	}


	log("doRight");
	return isdo;
}
bool HelloWorld::doUp()	 
{
	bool isdo =false;
	for(int x = 0; x<4; x++)
	{
		for(int y=3; y>=0; y--)
		{
			for(int y1 = y-1; y1>=0; y1--)
			{
				if(cardArr[x][y1]->getNumber() >0 )
				{
					if( cardArr[x][y] ->getNumber() <= 0 )//迭代
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y++;
						isdo = true;
					}
					else if( cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())//合并
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);
						isdo = true;

						score+=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

					}
					break;
				}
			}
		}
	}

	log("doUp");
	return isdo;
}
bool HelloWorld::doDown()	 
{
		bool isdo =false;
	for(int x = 0; x<4; x++)
	{
		for(int y=0; y<4; y++)
		{
			for(int y1 = y+1; y1<4; y1++)
			{
				if(cardArr[x][y1]->getNumber() >0 )
				{
					if( cardArr[x][y] ->getNumber() <= 0 )//迭代
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y--;
						isdo = true;
					}
					else if( cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())//合并
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);
						isdo = true;

						score+=cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

					}
					break;
				}
			}
		}
	}

	log("doDown");
	return isdo;
}


