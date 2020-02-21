#include "Common.h"
#include "Tetris.h"
#include <stdio.h>
#include <math.h>
extern Game tetrisGame;
extern float scalfx;
extern float scalfy;
extern int checkbound;


Block::Block() {
	int num_blocks_x = WINDOW_WIDTH / (BLOCK_SIZE + BLOCK_SPACING);
	int num_blocks_y = WINDOW_HEIGHT / (BLOCK_SIZE + BLOCK_SPACING);

	// Center top
	posX = num_blocks_x / 2;
	posY = num_blocks_y - 1;
}

Block::~Block() {
	Destroy();
}

void Block::Create() {
}



void Block::Draw(int a) {
	struct Rectangle rect;
	int num;
	num = a;
	
	float angle = 0;
	rect.left = posX * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
	rect.bottom = posY * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
	glPushMatrix();

	glColor3f(col[num][0], col[num][1], col[num][2]);
	glTranslatef(rect.left + 10, rect.bottom + 10, 0);
	if (checkbound) {
		glScalef(scalfx, scalfy, 1);
	}
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < circle_points; i++) {
		angle = 2 * GL_PI*i / circle_points;
		glVertex2f(19 * cos(angle), 19 * sin(angle));		
	}
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(-5, 10, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < circle_points; i++) {
		angle = 2 * GL_PI*i / circle_points;
		glVertex2f(6 * cos(angle), 6 * sin(angle));
	}
	glEnd();
	glPopMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(10, 0, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < circle_points; i++) {
		angle = 2 * GL_PI*i / circle_points;
		glVertex2f(6 * cos(angle), 6 * sin(angle));
	}
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0);
	glTranslatef(0, 0, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < circle_points; i++) {
		angle = 2 * GL_PI*i / circle_points;
		glVertex2f(2 * cos(angle), 2 * sin(angle));
	}
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0);
	glTranslatef(-10, 0, 0);
	glPushMatrix();
	glBegin(GL_POLYGON);
	for (int i = 0; i < circle_points; i++) {
		angle = 2 * GL_PI*i / circle_points;
		glVertex2f(2 * cos(angle), 2 * sin(angle));
	}
	glEnd();
	glPopMatrix();



	
	glPopMatrix();

}

void Block::Destroy() {
}

void Block::SetPosX(int x) {
	posX = x;
}

void Block::SetPosY(int y) {
	posY = y;
}

int Block::GetPosX() {

	return posX;
}

int Block::GetPosY() {

	return posY;
}

int Block::GetCol() {
	return colnum;
}

int Block::CanRotate(int direction, int originX, int originY) {
	int offsetX = posX - originX;
	int offsetY = posY - originY;
	if (!offsetX && !offsetY)
		return TRUE;
	int tmpX[3], tmpY[3], nextPosX, nextPosY;
	// Obstacle
	nextPosX = originX - offsetY;
	nextPosY = originY + offsetX;
	if (tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY)
		return FALSE;
	tmpX[0] = originX + offsetX - offsetY;
	tmpY[0] = originY + offsetX + offsetY;
	if (abs(offsetX) > 1 || abs(offsetY) > 1) {
		tmpX[1] = (tmpX[0] + posX) / 2;
		tmpX[2] = (tmpX[0] + originX - offsetY) / 2;
		tmpY[1] = (tmpY[0] + posY) / 2;
		tmpY[2] = (tmpY[0] + originY + offsetX) / 2;
		if (tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY || tetrisGame.GetMap(tmpX[2], tmpY[2]) != EMPTY)
			return FALSE;
	}
	else if (abs(offsetX) == 1 && abs(offsetY) == 1) {
		tmpX[1] = (tmpX[0] + posX) / 2;
		tmpY[1] = (tmpY[0] + posY) / 2;
		if (tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY)
			return FALSE;
	}
	else if (tetrisGame.GetMap(tmpX[0], tmpY[0]) != EMPTY)
		return FALSE;
	return TRUE;
}

int Block::Rotate(int direction, int originX, int originY) {
	int offsetX = posX - originX;
	int offsetY = posY - originY;

	if (!CanRotate(direction, originX, originY))
		return FALSE;
	int nextPosX, nextPosY;
	// Rotate
	nextPosX = originX - offsetY;
	nextPosY = originY + offsetX;
	SetPosX(nextPosX);
	SetPosY(nextPosY);
	return TRUE;
}

int Block::Translate(int offsetX, int offsetY) {
	int nextPosX = posX + offsetX, nextPosY = posY + offsetY;
	// Obstacle 
	if (tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY)
		return FALSE;
	SetPosX(nextPosX);
	SetPosY(nextPosY);
	return TRUE;
}

int Block::CanTranslate(int offsetX, int offsetY) {
	int nextPosX = posX + offsetX, nextPosY = posY + offsetY;
	// Obstacle 
	if (tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY)
		return FALSE;
	return TRUE;
}

void Block::setPos(int co) {
	// Obstacle 
	SetPosX(posX);
	SetPosY(posY);
	tetrisGame.SetMap(posX, posY, co);
}

void Block::delpos() {
	tetrisGame.DeleteMap(posX, posY + 1);
}
