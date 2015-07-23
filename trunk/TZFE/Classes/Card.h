#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Card:public Sprite
{
public:
	static Card *createSprite(int num, int width, int height, float x, float y);
	virtual bool init();
	CREATE_FUNC(Card);
	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);
private:
	//��ʾ�ڽ��������
	int number;
	void enemyInit(int num, int width, int height, float x, float y);
	//������ʾ���ֵĿؼ�
	Label *labelNum;
	//��ʾ����
	LayerColor *layerColorBg;
	

};