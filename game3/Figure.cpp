#include "Tetris.h"
#include "Common.h"
#include <stdio.h>
#include <time.h>

extern Game tetrisGame;
extern int loseFlag;
extern int keycont;
extern int updatetime;


Figure::Figure() {
	int numFigure = rand() % NUM_FIGURE;
	if (numFigure >= 0 && numFigure < NUM_FIGURE) {
		canRotate = (numFigure != 0) ? TRUE : FALSE;
		data = new Block[2];
		int num_blocks_x = WINDOW_WIDTH / (BLOCK_SIZE + BLOCK_SPACING);
		int num_blocks_y = WINDOW_HEIGHT / (BLOCK_SIZE + BLOCK_SPACING);
		// Center top
		posX = num_blocks_x / 2;
		posY = num_blocks_y - 1;

		cnum = (int)rand() % 5 + 1;
		cnum2 = (int)rand() % 5 + 1;

		int i;
		for (i = 0; i < 2; ++i) {
			data[i].SetPosX(posX + image[i][0]);
			data[i].SetPosY(posY + image[i][1]);
		}
	}
}


Figure::Figure(int numFigure) {
	if (numFigure >= 0 && numFigure < NUM_FIGURE) {
		canRotate = (numFigure != 0) ? TRUE : FALSE;
		data = new Block[2];
		int num_blocks_x = WINDOW_WIDTH / (BLOCK_SIZE + BLOCK_SPACING);
		int num_blocks_y = WINDOW_HEIGHT / (BLOCK_SIZE + BLOCK_SPACING);
		// Center top
		posX = num_blocks_x / 2;
		posY = num_blocks_y - 1;

		cnum = (int)rand() % 5 + 1;
		cnum2 = (int)rand() % 5 + 1;

		int i;
		for (i = 0; i < 2; ++i) {
			data[i].SetPosX(posX + image[i][0]);
			data[i].SetPosY(posY + image[i][1]);
		}
	}
}

Figure::~Figure() {
}

void Figure::Create(int numFigure) {

}


void Figure::Draw() {
	int i, colno = 0;

	for (i = 0; i < 2; ++i) {
		if (i == 0)
			data[i].Draw(cnum);
		else
			data[i].Draw(cnum2);
	}

}

Block* Figure::GetFigure() {
	return data;
}

void Figure::New(int numFigure) {
	if (numFigure >= 0 && numFigure < NUM_FIGURE) {
		canRotate = (numFigure != 0) ? TRUE : FALSE;
		int num_blocks_x = WINDOW_WIDTH / (BLOCK_SIZE + BLOCK_SPACING);
		int num_blocks_y = WINDOW_HEIGHT / (BLOCK_SIZE + BLOCK_SPACING);
		// Center top
		posX = num_blocks_x / 2;
		posY = num_blocks_y - 1;
		if (tetrisGame.GetMap(posX, posY) != 0 && loseFlag == FALSE) {
			keycont == FALSE;
			loseFlag = TRUE;
			return;
		}
		cnum = (int)rand() % 5 + 1;
		cnum2 = (int)rand() % 5 + 1;
		int i;
		for (i = 0; i < 2; ++i) {
			data[i].SetPosX(posX + image[i][0]);
			data[i].SetPosY(posY + image[i][1]);
		}
	}
}



int Figure::GetPosX() {
	return posX;
}

int Figure::GetPosY() {
	return posY;
}

int Figure::GetCol() {
	return cnum;
}

int Figure::GetCol2() {
	return cnum2;
}

void Figure::SetPosX(int x) {
	posX = x;
}

void Figure::SetPosY(int y) {
	posY = y;
}

//rotate
int Figure::Rotate(int direction) {
	int i;
	if (!canRotate) {
		return FALSE;
	}

	for (i = 0; i < 2; ++i) {
		if (!data[i].CanRotate(LEFT, posX, posY)) {
			return FALSE;
		}
	}

	for (i = 0; i < 2; ++i) {
		data[i].Rotate(LEFT, posX, posY);
	}
	return TRUE;
}

// check for translate
int Figure::Translate(int offsetX, int offsetY) {
	int i;
	int xpo, ypo;
	int cant[2];
	cant[0] = 0;
	cant[1] = 0;
	if (offsetX == 0 && offsetY == -1) {
		for (i = 0; i < 2; ++i) {
			if (!data[i].CanTranslate(offsetX, offsetY))
				cant[i] = 1;
		}
		if (cant[0] == 1 && cant[1] == 1) {
			keycont = FALSE;
			updatetime = 500;
			return FALSE;
		}
		else if (cant[0] == 0 && cant[1] == 1) {
			keycont = TRUE;
			data[1].setPos(cnum2);


			data[0].Translate(offsetX, offsetY);
			data[0].setPos(cnum);
			data[0].delpos();
			updatetime = 100;
			tetrisGame.drawmap();
			



			return TRUE;


		}
		else if (cant[0] == 1 && cant[1] == 0) {
			keycont = TRUE;
			data[0].setPos(cnum);


			data[1].Translate(offsetX, offsetY);
			data[1].setPos(cnum2);
			data[1].delpos(); 
			updatetime = 100;
			tetrisGame.drawmap();




			return TRUE;
		}
	}
	else {
		for (i = 0; i < 2; ++i) {
			if (!data[i].CanTranslate(offsetX, offsetY))
				
				return FALSE;
		}
	}


	for (i = 0; i < 2; ++i) {
		data[i].Translate(offsetX, offsetY);
	}
	SetPosX(posX + offsetX);
	SetPosY(posY + offsetY);
	return TRUE;
}


