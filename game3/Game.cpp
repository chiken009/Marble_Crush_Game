#include<stdio.h>
#include<string.h>
#include "Common.h"
#include "Tetris.h"
#include<windows.h>
#include<math.h>

extern Figure tetrisFigure;
extern int loseFlag;
extern int keycont;
extern int win;
extern float scalfx;
extern float scalfy;
extern int countscalf;
extern int checkbound;
extern int updatetime;
float angle;
int graycount = 0;


// constructor 
Game::Game() {
	// Number of rows and columns
	num_col = (WINDOW_WIDTH) / (BLOCK_SIZE + BLOCK_SPACING);
	num_row = (WINDOW_HEIGHT) / (BLOCK_SIZE + BLOCK_SPACING);
}

// destructor
Game::~Game() {
}

// create new game
void Game::New() {
	int i, j;
	for (i = 0; i < num_row; ++i) {
		for (j = 0; j < num_col; ++j) {
			map[i][j] = 0;
		}
	}
	tetrisFigure.New(3);
}

// draw game
void Game::Draw() {
	int i, j;
	// Draw Boder
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 1, 1);
	glVertex3f(-10, -6, 0);
	glVertex3f(WINDOW_WIDTH - BLOCK_SIZE / 2 - 18, -6, 0);
	glVertex3f(WINDOW_WIDTH - BLOCK_SIZE / 2 - 18, WINDOW_HEIGHT, 0);
	glVertex3f(-10, WINDOW_HEIGHT, 0);
	glEnd();

	// draw game
	if (loseFlag == FALSE && win ==FALSE) {
		struct Rectangle rect;
		for (i = 0; i < num_row; ++i) {
			for (j = 0; j < num_col; ++j) {
				if (map[i][j]) {
				
					rect.left = j * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
					rect.bottom = i * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
					glPushMatrix();
					glColor3f(mapcol[i][j][0], mapcol[i][j][1], mapcol[i][j][2]);
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
			}
		}
	}
	else if (win) {
		char string[] = "YOU WIN";
		char string1[] = "press ESC to quit or n to start new game";
		int len;
		int len1;
		glRasterPos2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		len = (int)strlen(string);
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		}
		glRasterPos2f(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 50);
		len1 = (int)strlen(string1);
		for (i = 0; i < len1; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
		}
	}
	else {
		char string[] = "GAME OVER";
		char string1[] = "press ESC to quit or n to start new game";
		int len;
		int len1;
		glRasterPos2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		len = (int)strlen(string);
		for (i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		}
		glRasterPos2f(WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 50);
		len1 = (int)strlen(string1);
		for (i = 0; i < len1; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string1[i]);
		}
	}
}

//count connected puyopuyo
void Game::Count(int x, int y, int *q) {
	int c = map[y][x];      // mycolor
	map[y][x] = 0; (*q)++;   //setmap=0
	mapcont[y][x] = 1;       //setmap

	//check puypuyo from same color
	if (x + 1 < num_col && map[y][x + 1] == c) { Count(x + 1, y, q); }
	if (y + 1 < num_row && map[y + 1][x] == c) { Count(x, y + 1, q); }
	if (x - 1 >= 0 && map[y][x - 1] == c) { Count(x - 1, y, q); }
	if (y - 1 >= 0 && map[y - 1][x] == c) { Count(x, y - 1, q); }
	map[y][x] = c;


}

//count neighber gray puyopuyo
void Game::GrayCount() {
	int i, j;

	for (int i = 0; i < num_row; ++i) {
		for (int j = 0; j < num_col; ++j) {
			if (mapcont[i][j] > 0) {
				if (graycount < 4) {
					if (j + 1 < num_col && map[i][j + 1] == 6) { mapcont[i][j + 1] = 1; graycount++; }
					if (i + 1 < num_row && map[i + 1][j] == 6) { mapcont[i + 1][j] = 1; graycount++; }
					if (j - 1 >= 0 && map[i][j - 1] == 6) { mapcont[i][j - 1] == 1; graycount++; }
					if (i - 1 >= 0 && map[i - 1][j] == 6) { mapcont[i - 1][j] == 1; graycount++; }
				}

			}
		}
	}

}




// update game's state
int Game::Update(Figure &figure) {
	Block *tmp;
	int i, num;

	// update new figure
	tmp = figure.data;
	//update color
	for (i = 0; i < 2; ++i) {
		if (i == 0)
			map[tmp[i].GetPosY()][tmp[i].GetPosX()] = conum;
		else
			map[tmp[i].GetPosY()][tmp[i].GetPosX()] = conum2;
		for (int j = 0; j < 3; j++) {
			if (i == 0)
				mapcol[tmp[i].GetPosY()][tmp[i].GetPosX()][j] = col[conum][j];
			else
				mapcol[tmp[i].GetPosY()][tmp[i].GetPosX()][j] = col[conum2][j];
		}
	}

	// update full line
	num = figure.GetPosY();

	// do {

		// FallPuyo();
	// } while (dnum > 3);
	return 0;



}

// clear row
void Game::ClearRow(int row) {
	int i, j;
	if (row < 0 || row >= num_row)
		return;
	for (i = row; i < num_row - 2; ++i) {
		for (j = 0; j < num_col; ++j) {
			map[i][j] = map[i + 1][j];
			for (int k = 0; k < 3; k++) {
				mapcol[i][j][k] = mapcol[i + 1][j][k];
			}
		}
	}
	for (j = 0; j < num_col; ++j) {
		map[num_row - 1][j] = 0;
		for (int k = 0; k < 3; k++) {
			mapcol[num_row - 1][j][k] = 0;
		}
	}
}

// check if row is full
int Game::RowIsFull(int row) {
	int i;
	n = 0;
	if (row < 0 || row >= num_row)
		return FALSE;

	return TRUE;
}




// print the game as a matrix
void Game::Print() {
	int i, j;
	printf("%d %d\n", num_row, num_col);
	for (i = num_row - 1; i >= 0; --i) {
		for (j = 0; j < num_col; ++j) {
			printf("%2d", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");

}

// get grids
int Game::GetMap(int x, int y) {
	if ((x < 0) || (y < 0) || (x >= num_col)
		|| (y >= num_row))
		return -1;
	else
		return map[y][x];
}

void  Game::SetConum(int c) {
	conum = c;
}

void  Game::SetConum2(int c) {
	conum2 = c;
}

//delete puto
int Game::DeletePuyo(void)
{
	int x, y, c;
	int d = 0;


	for (y = 0; y < num_row; ++y) {
		for (x = 0; x < num_col; ++x) {

			for (int a = 0; a < num_row; ++a) {
				for (int b = 0; b < num_row; ++b) {
					mapcont[b][a] = 0;
				}
			}
			/// for color puyopuyo
			c = 0;
			if (map[y][x] != 0 && map[y][x] != 6) {
				Count(x, y, &c);
				// How many conected
				if (c >= 4) {
					graycount = 0;
					//count gray puyo
					GrayCount();
					//erase conected puyo
					Vanish(x, y);
					d += c;
				}       
						 
			}
		}
	}
	// return num of vanish
	return d;
}

void Game::Vanish(int x, int y)
{
	// vanish conected puyo
	for (int i = 0; i < num_row; ++i) {
		for (int j = 0; j < num_col; ++j) {
			if (mapcont[i][j] > 0)
				map[i][j] = 0;
		}
	}
}

//start falling puyo
int Game::FallPuyo(void)
{
	keycont = TRUE;
	int x, y, iy, ni = 0;
	for (y = 1; y < num_row; ++y) {       /// row
		for (x = 0; x < num_col; ++x) {      /// col
			if (map[y][x] != 0) {    /// find color puyo

				//fall down puyo for y 1 block
				if (map[y - 1][x] == 0) {
					ni++;
					map[y - 1][x] = map[y][x];
					for (int k = 0; k < 3; k++) {
						mapcol[y - 1][x][k] = mapcol[y][x][k];
						mapcol[y][x][k] = 0;
					}
					map[y][x] = 0;

				}



			}
		}
	}
	//draw
	struct Rectangle rect;
	for (int i = 0; i < num_row; ++i) {
		for (int j = 0; j < num_col; ++j) {
			if (map[i][j]) {
				rect.left = j * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				rect.right = rect.left + BLOCK_SIZE;
				rect.bottom = i * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				rect.top = rect.bottom + BLOCK_SIZE;
				glBegin(GL_QUADS);
				glColor3d(mapcol[i][j][0], mapcol[i][j][1], mapcol[i][j][2]);
				glVertex3f(rect.left, rect.top, 0);
				glVertex3f(rect.right, rect.top, 0);
				glVertex3f(rect.right, rect.bottom, 0);
				glVertex3f(rect.left, rect.bottom, 0);
				glEnd();
			}
		}
	}



	return ni;
}



void Game::SetMap(int x, int y, int co) {
	map[y][x] = co;
	for (int i = 0; i < 3; i++) {
		mapcol[y][x][i] = col[co][i];
	}
}

//draw map of game
void Game::drawmap() {
	struct Rectangle rect;

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 16, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(WINDOW_WIDTH - BLOCK_SIZE / 2, 0, 0);
	glVertex3f(WINDOW_WIDTH - BLOCK_SIZE / 2, WINDOW_HEIGHT, 0);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();


	for (int i = 0; i < num_row; ++i) {
		for (int j = 0; j < num_col; ++j) {
			if (map[i][j] != 0) {
				rect.left = j * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				rect.bottom = i * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				glPushMatrix();
				glColor3f(mapcol[i][j][0], mapcol[i][j][1], mapcol[i][j][2]);
				glTranslatef(rect.left + 10, rect.bottom + 10, 0);
				glScalef(scalfx, scalfy, 1);
				glBegin(GL_POLYGON);
				glScalef(scalfx, scalfy, 1);
				for (int i = 0; i < circle_points; i++) {
					angle = 2 * GL_PI*i / circle_points;
					glVertex2f(19 * cos(angle), 19 * sin(angle));
					glColor3f(1, 1, 1);
					glVertex2f(19 * cos(angle), 19 * sin(angle));
				}
				glEnd();
				glPopMatrix();
			}
		}
	}


}


void Game::DeleteMap(int px, int py) {
	map[py][px] = 0;
	for (int i = 0; i < 3; i++) {
		mapcol[py][px][i] = 0;

	}


}

//add gray puto
void Game::graymap() {
	keycont = TRUE;
	int x, y, iy, ni = 0;
	for (x = 0; x < num_col; ++x) {


		for (iy = num_row - 1; iy >= 0 && map[iy][x] == 0; --iy) {}

		map[iy + 1][x] = 6;

		for (int k = 0; k < 3; k++) {
			mapcol[iy + 1][x][k] = col[6][k];


		}


	}
	//draw puyo
	struct Rectangle rect;
	for (int i = 0; i < num_row; ++i) {
		for (int j = 0; j < num_col; ++j) {
			if (map[i][j] != 0) {
				rect.left = j * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				rect.bottom = i * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
				glPushMatrix();
				glColor3f(mapcol[i][j][0], mapcol[i][j][1], mapcol[i][j][2]);
				glTranslatef(rect.left + 10, rect.bottom + 10, 0);
				glBegin(GL_POLYGON);
				glScalef(scalfx, scalfy, 1);
				for (int i = 0; i < circle_points; i++) {
					angle = 2 * GL_PI*i / circle_points;
					glVertex2f(19 * cos(angle), 19 * sin(angle));
					glColor3f(1, 1, 1);
					glVertex2f(19 * cos(angle), 19 * sin(angle));
				}
				glEnd();
				glPopMatrix();
			}
		}
	}

}

//bounding puyo
int Game::boundding(){

	checkbound = TRUE;
	updatetime = 100;

	if (countscalf == 1) {
		scalfx += 0.1;
		scalfy -= 0.1;
	}

	if (scalfx > 1.5 && countscalf == 1) {
		countscalf = 2;
	}

	if (countscalf == 2) {
		scalfx -= 0.1;
		scalfy += 0.1;
	}

	if (countscalf == 2 && scalfx<=1) {
		scalfx = 1;
		scalfy = 1;
		countscalf = 1;
		checkbound = FALSE;
		updatetime = 500;

		return 1;
	}


	return 0;
}