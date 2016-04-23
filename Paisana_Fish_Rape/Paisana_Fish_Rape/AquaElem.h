#pragma once
class AquaElem {

	int type, mask;
	int px, py; //coordenadas do peixe
	int mx, my;
	int edge;
	bool dir, move;
	int time;

public:
	AquaElem(int t, int m, int e, int xi, int yi);
	void Draw(void);
	void Move();
	void Run();
	void HoldClick(int x, int y);
	bool isClicked(int x, int y);
	~AquaElem();
};
