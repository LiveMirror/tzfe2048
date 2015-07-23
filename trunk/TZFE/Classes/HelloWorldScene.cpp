#include "HelloWorldScene.h"


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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���뱳��
	auto bgColor = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(bgColor);

	//���Ϸ�������Ϸ�ķ���
	auto labelNumberName = Label::create("����", "HirakakuProN-W6", 80);
	labelNumberName->setPosition(Point(visibleSize.width/5, visibleSize.height-150));
	this->addChild(labelNumberName);

	scoreLabel =  Label::create("0", "HirakakuProN-W6", 80);
	scoreLabel->setPosition(Point(visibleSize.width/5 + 100, visibleSize.height-150));
	this->addChild(scoreLabel);


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	//�������ɿ�Ƭ�ķ���
	createCard(visibleSize);
    
	//�������������Ƭ
	autoCreateCard();
	autoCreateCard();
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *t, cocos2d::Event *e)
{
	Point p = t->getLocation();
	firstX = p.x;
	firstY = p.y;
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *e)
{
	Point p = t->getLocation();
	endX = firstX - p.x;
	endY = firstY - p.y;
	if(abs(endX) > abs(endY))
	{
		//�����ƶ�
		if(endX + 5 > 0)
		{
			if(doLeft())
			{
				autoCreateCard();
				doCheckGameOver();
			}
		}
		else
		{
			if(doRight())
			{
				autoCreateCard();
				doCheckGameOver();
			}
		}
	}
	else
	{
		//�����ƶ�
		if(endY + 5 >0)
		{
			if(doDown())
			{
				autoCreateCard();
				doCheckGameOver();
			}
		}
		else
		{
			if(doUp())
			{
				autoCreateCard();
				doCheckGameOver();
			}
		}
	}
}

bool HelloWorld::doLeft()
{
	log("doLeft...");
	bool isDo = false;
	for (int y=0; y<4; y++)
	{
		for (int x=0;x<4;x++)
		{
			for (int x1=x+1; x1<4; x1++)
			{
				if(cardArr[x1][y]->getNumber()>0)
				{
					if(cardArr[x][y]->getNumber()<=0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						isDo = true;
					}
					else if(cardArr[x][y]->getNumber()==cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());

						isDo = true;
					}
					break;
				}
			}
		}
	}
	return isDo;
}

bool HelloWorld::doRight()
{
	log("doRight...");
	bool isDo = false;
	for (int y=0; y<4; y++)
	{
		for (int x=3;x>=0;x--)
		{
			for (int x1=x-1; x1>=0; x1--)
			{
				if(cardArr[x1][y]->getNumber()>0)
				{
					if(cardArr[x][y]->getNumber()<=0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isDo = true;
					}
					else if(cardArr[x][y]->getNumber()==cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x1][y]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						isDo = true;
					}
					break;
				}
			}
		}
	}
	return isDo;
}

bool HelloWorld::doDown()
{
	log("doDown...");
	bool isDo = false;
	for (int x=0; x<4; x++)
	{
		for (int y=0; y<4; y++)
		{
			for (int y1=y+1; y1<4; y1++)
			{
				if(cardArr[x][y1]->getNumber()>0)
				{
					if(cardArr[x][y]->getNumber()<=0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isDo = true;
					}
					else if(cardArr[x][y]->getNumber()==cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						isDo = true;
					}
					break;
				}
			}
		}
	}
	return isDo;
}

bool HelloWorld::doUp()
{
	log("doUp...");
	bool isDo = false;
	for (int x=0; x<4; x++)
	{
		for (int y=3; y>=0; y--)
		{
			for (int y1=y-1; y1>=0; y1--)
			{
				if(cardArr[x][y1]->getNumber()>0)
				{
					if(cardArr[x][y]->getNumber()<=0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isDo = true;
					}
					else if(cardArr[x][y]->getNumber()==cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						cardArr[x][y1]->setNumber(0);

						//���÷���
						score += cardArr[x][y]->getNumber();
						scoreLabel->setString(__String::createWithFormat("%i", score)->getCString());
						isDo = true;
					}
					break;
				}
			}
		}
	}
	return isDo;
}

void HelloWorld::createCard(cocos2d::Size size)
{
	//�����Ԫ��Ŀ�͸�
	int width = (size.height-28)/4;
	//4*4�ĵ�Ԫ��
	for (int j = 0; j < 4; j ++)
	{
		for (int i = 0;i < 4; i ++)
		{
			Card *card = Card::createSprite(0, width, width, width*j+20, width*i+20);
			card->setAnchorPoint(Point(0, 0));
			addChild(card);
			cardArr[j][i] = card;
		}
	}
}

//�Զ����ɿ�Ƭ
void HelloWorld::autoCreateCard()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;
	if(cardArr[i][j]->getNumber() > 0)
	{
		autoCreateCard();
	}
	else
	{
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1? 4:2);
	}
}

void HelloWorld::doCheckGameOver()
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y ++)
	{
		for (int x = 0; x < 4; x ++)
		{
			if(cardArr[x][y]->getNumber() == 0 
				||(x > 0 && cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber())
				||(x < 3 && cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber())
				||(y > 0 && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber())
				||(y < 3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()))
			{
				isGameOver = false;
			}
		}
	}

	if(isGameOver)
	{
		//������Ϸ
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
