/***********************************
Project: Tetris
Language: C++
API: Opengl
Date: April 12, 2012
***********************************/

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <cstdio>
#include <cstdint>



#include<math.h>


#include "Common.h"
#include "Tetris.h"
#include <mmsystem.h>


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//for screen


void introscreen();
void frame();
int window;
int view = 0;
char buf[100] = { 0 };


// variables' declaration and initialization
int newFigureFlag = TRUE;
int loseFlag = FALSE;
int keycont = FALSE;
int win = FALSE;
int ddnum;
int erasenum;
int checkbound =FALSE;
int fboo = FALSE;
int conrun = FALSE;
int delno = TRUE;
int song = 0;
int bound = FALSE;
int sumdelete = 0;
int rounddelete = 1;
int timer = 0;
int updatetime = 500;
int timemax = 60;
int cogray = 0;
int screen = TRUE;
int countscalf = 1;
int bo;
float scalfx = 1;
float scalfy = 1;
BOOLEAN crenew = TRUE;
Figure tetrisFigure(rand() % NUM_FIGURE);
Game tetrisGame;
string mapname = "0";
string timecount = "0";
// function prototypes
void Display(void);
void MyInit();
void Update(int value);
void HandleKeyPress(unsigned char key, int x, int y);
void RenderString(GLdouble x, GLdouble y, const std::string &string, float r, float g, float b, int f);



void renderbitmap(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void frame() {
	//Decorate
	//LEFT
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(-50, WINDOW_HEIGHT + 50);
	glVertex2i(0 , WINDOW_HEIGHT + 50);
	glVertex2i(0 , WINDOW_HEIGHT);
	glVertex2i(-50, WINDOW_HEIGHT);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(-50.0, WINDOW_HEIGHT );
	glVertex2i(0, WINDOW_HEIGHT );
	glVertex2i(0, WINDOW_HEIGHT - 50);
	glVertex2i(-50.0, WINDOW_HEIGHT - 50);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 50);
	glVertex2i(0, WINDOW_HEIGHT - 50);
	glVertex2i(0, WINDOW_HEIGHT - 100);
	glVertex2i(-50.0, WINDOW_HEIGHT - 100);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 100);
	glVertex2i(0, WINDOW_HEIGHT - 100);
	glVertex2i(0, WINDOW_HEIGHT - 150);
	glVertex2i(-50.0, WINDOW_HEIGHT - 150);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 150);
	glVertex2i(0, WINDOW_HEIGHT - 150);
	glVertex2i(0, WINDOW_HEIGHT - 200);
	glVertex2i(-50.0, WINDOW_HEIGHT - 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 200);
	glVertex2i(0, WINDOW_HEIGHT - 200);
	glVertex2i(0, WINDOW_HEIGHT - 250);
	glVertex2i(-50.0, WINDOW_HEIGHT - 250);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 250);
	glVertex2i(0, WINDOW_HEIGHT - 250);
	glVertex2i(0, WINDOW_HEIGHT - 300);
	glVertex2i(-50.0, WINDOW_HEIGHT - 300);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 300);
	glVertex2i(0, WINDOW_HEIGHT - 300);
	glVertex2i(0, WINDOW_HEIGHT - 350);
	glVertex2i(-50.0, WINDOW_HEIGHT - 350);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 350);
	glVertex2i(0, WINDOW_HEIGHT - 350);
	glVertex2i(0, WINDOW_HEIGHT - 400);
	glVertex2i(-50.0, WINDOW_HEIGHT - 400);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 400);
	glVertex2i(0, WINDOW_HEIGHT - 400);
	glVertex2i(0, WINDOW_HEIGHT - 450);
	glVertex2i(-50.0, WINDOW_HEIGHT - 450);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 450);
	glVertex2i(0, WINDOW_HEIGHT - 450);
	glVertex2i(0, WINDOW_HEIGHT - 500);
	glVertex2i(-50.0, WINDOW_HEIGHT - 500);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(-50.0, WINDOW_HEIGHT - 500);
	glVertex2i(0, WINDOW_HEIGHT - 500);
	glVertex2i(0, WINDOW_HEIGHT - 550);
	glVertex2i(-50.0, WINDOW_HEIGHT - 550);
	glEnd();

	//RIGHT
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT + 50);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT + 50);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT-50);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT-50);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 50);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 50);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 100);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 100);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 100);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 100);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 150);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 150);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 150);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 150);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 200);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 200);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 200);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 200);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 250);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 250);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 250);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 250);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 300);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 300);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 300);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 300);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 350);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 350);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 350);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 350);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 400);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 400);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 400);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 400);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 450);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 450);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 450);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 450);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 500);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 500);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 500);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 500);
	glVertex2i(WINDOW_WIDTH + 200, WINDOW_HEIGHT - 550);
	glVertex2i(WINDOW_WIDTH + 250, WINDOW_HEIGHT - 550);
	glEnd();
}

void introscreen() {
	//Text
	glColor3f(0.0, 1.0, 1.0);
	sprintf_s(buf, "MARBLE CRASH");
	renderbitmap(200, 400, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	glColor3f(1.0, 1.0, 1.0);
	sprintf_s(buf, "-- Press P to Start --");
	renderbitmap(200, 350, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "-- Press i to About --");
	renderbitmap(200, 300, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "-- Press ESC to Exit --");
	renderbitmap(200, 250, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "@CSS325 COMPUTER GRAPHIC -- King Mongkut's University of Technology Thonburi.");
	renderbitmap(20, 0, GLUT_BITMAP_HELVETICA_12, buf);
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();

}

void aboutdisplay() {
	//Red
	glColor3f(1.0, 0.0, 0.0);
	sprintf_s(buf, "Information");
	renderbitmap(230.0, 500.0, GLUT_BITMAP_TIMES_ROMAN_24, buf);
	//white
	glColor3f(1.0, 1.0, 1.0);
	sprintf_s(buf, "Marble Crash");
	renderbitmap(150, 450, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "A");
	renderbitmap(180, 380, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "MOVE TO LEFT");
	renderbitmap(340, 380, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "D");
	renderbitmap(180, 330, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "MOVE TO RIGHT");
	renderbitmap(340, 330, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "W");
	renderbitmap(180, 280, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "MOVE UP");
	renderbitmap(340, 280, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "S");
	renderbitmap(180, 230, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "MOVE DOWN");
	renderbitmap(340, 230, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "COMPUTER GRAPHIC -- King Mongkut's University of Technology Thonburi.");
	renderbitmap(30, 0, GLUT_BITMAP_HELVETICA_12, buf);
	//pink
	glColor3f(1.0, 0.0, 1.0);
	sprintf_s(buf, "Press B to go back");
	renderbitmap(370, 100, GLUT_BITMAP_HELVETICA_18, buf);
	//bluesky
	glColor3f(0.0, 1.0, 1.0);
	sprintf_s(buf, "Game Name :");
	renderbitmap(20, 450, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "Control :");
	renderbitmap(20, 380, GLUT_BITMAP_HELVETICA_18, buf);
	sprintf_s(buf, "Thank You!");
	renderbitmap(30, 100, GLUT_BITMAP_HELVETICA_18, buf);
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}




//draw text
void RenderString(GLdouble x, GLdouble y, const std::string &string, float r, float g, float b, int f)
{
	glColor3d(r, g, b);
	glRasterPos2d(x, y);
	if (f == 1) {
		for (int s = 0; s < string.size(); ++s) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[s]);
		}
	}
	else {
	for (int s = 0; s < string.size(); ++s) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[s]);
	}
	
	}
}




// handle keyboard
void HandleKeyPress(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(1);
	}
	// Control keys
	if (loseFlag == FALSE && keycont == FALSE) {
		switch (key) {
		case 's':
			tetrisFigure.Translate(0, -1);
			glutPostRedisplay();
			break;
		case 'a':
			tetrisFigure.Translate(-1, 0);
			glutPostRedisplay();
			break;
		case 'd':
			tetrisFigure.Translate(1, 0);
			glutPostRedisplay();
			break;
		case 'w':
			tetrisFigure.Rotate(LEFT);
			glutPostRedisplay();
			break;
		case 'e':
			tetrisFigure.Translate(0, 1);
			glutPostRedisplay();
			break;

		case 'i': view = 1;
			Display();
			break;

		case 'b': view = 0;
			Display();
			break;

		case 'p': 
			screen = FALSE;
			break;
			
		default:
			break;
		}
	}
	else {
		switch (key) {
		case 'n':
			tetrisGame.New();
			loseFlag = FALSE;
			win = FALSE;
			timer = 0;
			timemax = 60;
			glutPostRedisplay();
			break;
		default:
			break;
		}
	}
}

//draw other thing on screen
void drawelse(void) {
	string maxt;
	glColor3f(0, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(380, 400);
	glVertex2f(380, 460);
	glVertex2f(550, 460);
	glVertex2f(550, 400);
	glEnd();
	mapname = std::to_string(sumdelete);
	maxt = std::to_string(timemax);
	RenderString(390, 430, mapname, 1, 0, 0, 1);
	RenderString(390, 200, timecount, 1, 0, 0, 1);
	RenderString(390, 470, "Add score over 100", 1, 1, 1, 1);
	RenderString(390, 230, "Count time", 1, 1, 1, 1);
	RenderString(390, 160, "Time for Demon", 1, 1, 1, 1);
	RenderString(390, 130, maxt, 1, 0, 0, 1);
	RenderString(360, 50, "Marble", 1, 1, 0, 2);
	RenderString(440, 50, "Crash", 1, 0, 1, 2);
	RenderString(520, 50, "Game", 0, 1, 0, 2);
}



// display's function
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	

	//screen

	if (screen) {
		if (view == 0)
		{
			frame();
			introscreen();
		}
		if (view == 1)
		{
			frame();
			aboutdisplay();
		}
		glFlush();
	}
	else {
		if(song==0)
		PlaySound(TEXT("sound//Tetris.wav"), NULL, SND_LOOP | SND_ASYNC);

		if(song==0)
		song++;

		glClear(GL_DEPTH_BUFFER_BIT);
		drawelse();
		//check sumdelete
		if (sumdelete >= 100) {
			sumdelete = 0;
			win = TRUE;
		}
		if (loseFlag == FALSE && fboo == FALSE)
			tetrisFigure.Draw(); // only draw if loseFlag not TRUE
		

		tetrisGame.Draw();  // Draw the game
		glutSwapBuffers();
	}
	
	
			
}

// Initialization
void MyInit(void) {
	PlaySound(TEXT("sound//bgm_maoudamashii_orchestra20.wav"), NULL, SND_LOOP | SND_ASYNC);
	glClearColor(0.0, 0.0, 0.0, 0.0); //black background
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-50, (GLdouble)WINDOW_WIDTH + 250, -50, (GLdouble)WINDOW_HEIGHT + 50);
	srand(time(NULL));

	
	/*
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(-90.0, 100.0, -15.0, 100.0);
	srand(time(NULL));
	*/
}

// update function
void Update(int value) {
	if (screen) {
	
	
	}
	else {
		if (loseFlag == FALSE && win == FALSE) {

			if (fboo == FALSE) {
				bound = FALSE;
				newFigureFlag = tetrisFigure.Translate(0, -1);
			}
			if (!newFigureFlag &&  fboo == FALSE) {
				tetrisGame.SetConum(tetrisFigure.GetCol());
				tetrisGame.SetConum2(tetrisFigure.GetCol2());
				tetrisGame.Update(tetrisFigure);
				fboo = TRUE;
				keycont = TRUE;
				bound = TRUE;
				rounddelete = 1;


			}

			if (fboo == TRUE) {
				if (bound) {
					//bounding
					bo = tetrisGame.boundding();
					if (bo == 1) {

						bound = FALSE;
						checkbound = FALSE;
					}
				}
				else {
					if (delno) {
						//delete
						ddnum = tetrisGame.DeletePuyo();
						if (ddnum > 3) {
							sumdelete = sumdelete + (ddnum*rounddelete);
						}
						rounddelete++;
					}
					updatetime = 300;
					// puyo falling
					erasenum = tetrisGame.FallPuyo();
					printf("%d", erasenum);
					delno = FALSE;
					if (erasenum == 0) {
						delno = TRUE;
						bound = TRUE;
					}


					if (ddnum < 4) {
						fboo = FALSE;
						conrun = TRUE;
						keycont = FALSE;
						updatetime = 500;
					}
				}

			}
		}


		if (conrun == TRUE) {

			if (timer > timemax && cogray == 0) {
				keycont = TRUE;
				tetrisGame.graymap();
				keycont = FALSE;
				timer = 0;
				timemax--;
			}
			//create new figure
			tetrisFigure.New(rand() % (NUM_FIGURE-1) + 1);

		}
		conrun = FALSE;
		if (timer <= timemax) {
			if (updatetime >= 500)
				timer++;
		}
		timecount = std::to_string(timer);
	}
		glutTimerFunc(updatetime, Update, 0);
	
	glutPostRedisplay(); // Refresh Display
}



int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH + 300, WINDOW_HEIGHT + 100);      // window size
	glutInitWindowPosition(50, 50);      // window position on screen
	glutCreateWindow("Marble Crash Game");

	
	MyInit();  // initialization  
	glutDisplayFunc(Display);  // display
	glutKeyboardFunc(HandleKeyPress);  // keyboard 
	glutTimerFunc(400, Update, 0);
	// timer's function
	glutMainLoop();
	
}
