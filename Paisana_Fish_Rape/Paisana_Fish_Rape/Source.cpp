/******************************************************************************/
/**                                                    ,---------------.     **/
/**    COMPUTACAO GRAFICA                              |        .-.    |     **/
/**    MIEEC - FCTUC                                   |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - Hugo Paisana                         |  `---'   `-'  |     **/
/**             - Bruno DA Silva                       '---------------'     **/
/******************************************************************************/
/* DESCRICAO: Projeto 2 - Ambiente Aqu�tico                                   */
/*																			  */
/*																			  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//

#include <Windows.h>
#include <Mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <iostream>
#include "textures.h"
#include "AquaElem.h"


using namespace std;
//
//	Defini��es /////////////////////////////////////////////////////////////////
//

//#define _CRT_SECURE_NO_WARNINGS

#define PI 3.14
bool createfish = false;
bool left_button_state = 0;
int fish_index = 0;
vector <AquaElem> fish;

static int h=800, w=1000;
int peixe1 = 0;

void desenhafundo(){

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glBlendFunc(GL_DST_COLOR, GL_ZERO);

	textura(0, 1);

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);


}
// Desenha o peixe laranja

void desenhapeixe1_b(){
	gluOrtho2D(0, 1000, 0, 800);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glTranslated(25, 775, 0.0);

	glScalef(20, 20, 1);

	textura(2, 3);

	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void DesenhaLinhas(int xi, int yi, int xf, int yf){
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);								//Desenhar linhas entre pontos
	glVertex2i(xi, yi);
	glVertex2i(xi, yf);
	glVertex2i(xf, yf);
	glVertex2i(xf, yi);
	glEnd();
}

void plotButton(int xi, int yi, int xf, int yf){
	glBegin(GL_POLYGON);
	glVertex2i(xi, yi);
	glVertex2i(xi, yf);
	glVertex2i(xf, yf);
	glVertex2i(xf, yi);
	glEnd();
}

void barra(){
	gluOrtho2D(0, 1000, 0, 800);

	glColor3f(0, 0, 0);
	DesenhaLinhas(0, 750, 50, 800);
	glColor3f(0, 1, 0);
	plotButton(0, 750, 50, 800);

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON); //Barra
	glVertex2f(0, 750);
	glVertex2f(1000, 750);
	glVertex2f(1000, 800);
	glVertex2f(0, 800);
	glEnd();
}

// Desenha o sistema todo: peixes, moinho, bolhas
void desenha(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();

	glPushMatrix();
	desenhafundo();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	barra();
	glPopMatrix();

	for (int i = 0; i < fish.size(); i++){
		fish[i].Draw();
	}
	


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	desenhapeixe1_b();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glFlush();
}




void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	desenha();
	glPopMatrix();

	glutSwapBuffers();
}



void play_sound(int caso){
	if (caso == 1){
		PlaySound(TEXT("dolphin.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
}


void init(){
	srand (time(NULL));
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0.0, w, 0.0, h); //Display area
	InitTexture();
}


void move(int v){

	for (int i = 0; i < fish.size(); i++){
		fish[i].Move();
	}

	glutPostRedisplay();
	glutTimerFunc(30, move, 1);
}


void press_mouse(int button, int state, int x, int y){
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Mouse = (%d, %d) -> Waiting Fish<- \n", x, y);
		
		if (0<x && x<50 && 0<y && y<50){
			cout << "SpawnFish " << fish.size()<< endl;
			fish.push_back(AquaElem(3,4,35,x,y));
		}
		
		left_button_state = 1;
		
		for (int i = 0; i < fish.size(); i++){
			if (fish[i].isClicked(x, y)){
				fish_index = i;
			}
		}
		cout << fish_index << endl;
	}else{
		//left_button_state = 0;
	}
}

void move_mouse(int x, int y){

	if (fish[fish_index].isClicked(x, y)){
		fish[fish_index].HoldClick(x, y);
	}

	glutPostRedisplay();
}

int main(int  argc, char *argv[])
{

	//int x=10, y=10;
    glutInit(&argc, argv);				// inicializa��o da biblioteca GLUT
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB );

	glutInitWindowSize(w, h);
	glutInitWindowPosition(500,50);
	glutCreateWindow("Aquario_2D");


	init();
	glutDisplayFunc(display);
	glutMouseFunc(press_mouse);
	glutTimerFunc(0, move, 1);
	glutMotionFunc(move_mouse);
	glutMainLoop();						// inicializa��o do main loop do OpenGL

    return 0;
}