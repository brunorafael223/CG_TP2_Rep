#include "AquaElem.h"
#include "glut.h"
#include "math.h"
#define PI 3.14

AquaElem::AquaElem(int t, int m, int e, int xi, int yi){
	type = t;
	px = xi;
	py = yi;
	my = yi;
	edge = e;
	mask = m;
	dir = true;
	time = 0;
	runtime = 0;
}
void AquaElem::SetProperties(int t, int m, int e, int xi, int yi){
	type = t;
	px = xi;
	py = yi;
	my = yi;
	edge = e;
	mask = m;
	dir = true;
	time = 0;
	runtime = 0;
}
void AquaElem::Draw(void){
	int direction = 1;
	if (dir){ direction = 1; }
	else{ direction = -1; }
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

	gluOrtho2D(0, 1000, 0, 800);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glBlendFunc(GL_DST_COLOR, GL_ZERO);

	glTranslated(px, 800 - py, 0.0);
	 
	//MASCARA
	glScalef(direction*edge, edge, 1);
	glBindTexture(GL_TEXTURE_2D, mask);
	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);	// inferior esquerdo
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);	// inferior direito
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);	// superior direito
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);	// superior esquerdo
	glEnd();

	//Draw Elem
	glBlendFunc(GL_ONE, GL_ONE);
	glBindTexture(GL_TEXTURE_2D, type); //Load texture
	glBegin(GL_QUADS);								 //Desenha pelos vertices ortho
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glEnd();

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void AquaElem::Move(){
	if (move){
		if (px < 1000 && dir){ px++; }
		if (px == 1000 && dir){ dir = !dir; }
		if (px > 10 && !dir){ px--; }
		if (px <= 10 && !dir){ dir = !dir; }
		py = my + 50 * sin(time*PI / 180);
		time++;
	}
}
void AquaElem::Run(){
	py = my + 2*sin(runtime*PI / 180);
	runtime += 100; 
}
bool AquaElem::isClicked(int x, int y){
	if ((px - edge) < x && x < (px + edge) && (py - edge) < y && y < (py + edge)){
		mx = px;
		my = py;
		return(true);
	}
	else{
		return (false);
	}
}
void AquaElem::HoldClick(int x, int y){
	px = x;
	py = y;
	time = 0;
}
int AquaElem::getPositionX(){
	return(px);
}
int AquaElem::getPositionY(){
	return(py);
}

Hunter::Hunter():AquaElem(0, 0, 0, 0, 0){
	prey = 0;
	prey_d=1000;
	prey_x = 0;
	prey_y = 0;
}
void Hunter::Scout(int i,int x, int y){ //Procura qual o peixe mais próximo e segue as coordenadas dele num passo realtivamente mais rapido ..
	int d = sqrt((px - x)*(px - x) + abs(py - y)*(px - x));
	if (d < prey_d)
	{
		prey = i;
		prey_x = x;
		prey_y = y;
		
	}	
}
void Hunter::Hunt(){  //Segue a presa
	if (prey != -1){
		//printf("\nPrey:fish %d (x,y)=(%d,%d)", prey, prey_x, prey_y);
		
		if (px < prey_x){
			px++; dir = true;
		}
		else{
			px--; dir = false;
		}
		
		if (py < prey_y){
			py++;
		}else{
			py--;
		}
	}

}
int Hunter::Eat(){
	if ((px - edge) < prey_x && prey_x < (px + edge) && (py - edge) < prey_y && prey_y < (py + edge)){
		return(prey);
	}
	else{
		return(-1);
	}
}

AquaElem::~AquaElem()
{
}
