#pragma once
#include <vector>
class AquaElem 
{
public:
	int type, mask;
	int px, py; //coordenadas do peixe
	int mx, my;
	int edge;
	bool dir, move;
	int time;
	int runtime;


    AquaElem(int t, int m, int e, int xi, int yi);
	void SetProperties(int t, int m, int e, int xi, int yi);
	void Draw(void);
	void Move();
	void Run();
	void HoldClick(int x, int y);
	bool isClicked(int x, int y);
	int getPositionX();
	int getPositionY();
	~AquaElem();
};

class Hunter :public AquaElem{
	int prey;
	int prey_d;
	int prey_x;
	int prey_y;
public:
	Hunter();
	int Eat();
	void Scout(int i, int x, int y);
	void Hunt();
};