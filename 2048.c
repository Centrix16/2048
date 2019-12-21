/*
 * 2048 -- the legendary game is now in the console!
 * v0.5
 * 21.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 4
#define HEIGHT 4

typedef struct {
	int field[WIDTH][HEIGHT];
	int score;
} gfield;

gfield Field;

int randomv[] = {2,2,2,2,2,2,2,2,2,4};

void fillField(gfield *gf, int filler);
void outputField(gfield *gf);
void randomGeneration(gfield *gf);

void shiftUp(gfield *gf);
void shiftDown(gfield *gf);
void shiftLeft(gfield *gf);
void shiftRight(gfield *gf);

int is_go(gfield *gf);

int main()
{
	char c;

	fillField(&Field, 0);
	Field.score = 0;

	while (!is_go(&Field)) {
		switch (c=getch()) {
		case ' ':
			break;
		case 'w':
			shiftUp(&Field);
			break;
		case 's':
			shiftDown(&Field);
			break;
		case 'a':
			shiftLeft(&Field);
			break;
		case 'd':
			shiftRight(&Field);
			break;
		case 'c':
			fillField(&Field, 0);
			Field.score = 0;
			break;
		case 'e':
		case 27:
			return 0;
		default:
			printf("Error: unknow operaton \'%c\'\n", c);
			break;
		}
		system("cls");
		randomGeneration(&Field);
		outputField(&Field);
	}
	printf("\nGame Over!\n");
	return 0;
}

void fillField(gfield *gf, int filler)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			gf->field[y][x] = filler;
}

void outputField(gfield *gf)
{
	int maxLenCell(gfield *gf);
	int mlc = maxLenCell(gf);
	char cz = ' ';
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (gf->field[y][x])
				printf("%*d%s", mlc, gf->field[y][x], (WIDTH - x - 1) ? " " : "|\n");
			else
				printf("%*c%s", mlc, cz, (WIDTH - x - 1) ? " " : "|\n");
	printf("Score: %d\n", gf->score);
}

int maxLenCell(gfield *gf)
{
	int cell, lc, mlc = 1;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			cell = gf->field[y][x];
			lc = 1;
			while ((cell /= 10) > 0)
				lc++;
			if (lc > mlc)
				mlc = lc;
		}
	return mlc;
}

void randomGeneration(gfield *gf)
{
	int number, pos_0, numOf_0 = 0;
	int numberZeros(gfield *gf);

	if (!(numOf_0 = numberZeros(gf)))
		return;
	srand(time(NULL));
	number = randomv[rand() % 10];
	srand(time(NULL));
	pos_0 = rand() % numOf_0;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			if (!pos_0 && !gf->field[y][x]) {
				gf->field[y][x] = number;
				return;
			}
			if (!gf->field[y][x])
				pos_0--;
		}
}

void shiftUp(gfield *gf)
{
	for (int x = 0; x < WIDTH; x++)
		for (int y = 1, posFilling = 0, isPrevOpSum = 0; y < HEIGHT; y++)
			if (!gf->field[y][x]) {
				continue;
			} else if (gf->field[y][x] == gf->field[posFilling][x]
					&& !isPrevOpSum) {
				gf->field[posFilling][x] *= 2;
				gf->field[y][x] = 0;
				isPrevOpSum = 1;
				gf->score += gf->field[posFilling++][x];
			} else {
				if (gf->field[posFilling][x])
					posFilling++;
				if (y == posFilling)
					continue;
				gf->field[posFilling][x] = gf->field[y][x];
				gf->field[y][x] = 0;
				isPrevOpSum = 0;
			}
}

void shiftLeft(gfield *gf)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 1, posFilling = 0, isPrevOpSum = 0; x < WIDTH; x++)
			if (!gf->field[y][x]) {
				continue;
			} else if (gf->field[y][x] == gf->field[y][posFilling]
					&& !isPrevOpSum) {
				gf->field[y][posFilling] *= 2;
				gf->field[y][x] = 0;
				isPrevOpSum = 1;
				gf->score += gf->field[y][posFilling++];
			} else {
				if (gf->field[y][posFilling])
					posFilling++;
				if (x == posFilling)
					continue;
				gf->field[y][posFilling] = gf->field[y][x];
				gf->field[y][x] = 0;
				isPrevOpSum = 0;
			}
}

void shiftDown(gfield *gf)
{
	for (int x = 0; x < WIDTH; x++)
		for (int y = HEIGHT - 2, posFilling = HEIGHT - 1, isPrevOpSum = 0; y >= 0; y--)
			if (!gf->field[y][x]) {
				continue;
			} else if (gf->field[y][x] == gf->field[posFilling][x]
					&& !isPrevOpSum) {
				gf->field[posFilling][x] *= 2;
				gf->field[y][x] = 0;
				isPrevOpSum = 1;
				gf->score += gf->field[posFilling--][x];
			} else {
				if (gf->field[posFilling][x])
					posFilling--;
				if (y == posFilling)
					continue;
				gf->field[posFilling][x] = gf->field[y][x];
				gf->field[y][x] = 0;
				isPrevOpSum = 0;
			}
}

void shiftRight(gfield *gf)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = WIDTH - 2, posFilling = WIDTH - 1, isPrevOpSum = 0; x >= 0; x--)
			if (!gf->field[y][x]) {
				continue;
			} else if (gf->field[y][x] == gf->field[y][posFilling]
					&& !isPrevOpSum) {
				gf->field[y][posFilling] *= 2;
				gf->field[y][x] = 0;
				isPrevOpSum = 1;
				gf->score += gf->field[y][posFilling--];
			} else {
				if (gf->field[y][posFilling])
					posFilling--;
				if (x == posFilling)
					continue;
				gf->field[y][posFilling] = gf->field[y][x];
				gf->field[y][x] = 0;
				isPrevOpSum = 0;
			}
}

int numberZeros(gfield *gf)
{
	int numOf_0 = 0;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (!gf->field[y][x])
				numOf_0++;
	return numOf_0;
}

int is_go(gfield *gf)
{
	if (!numberZeros(gf)) {
		gfield f;
		for (int direction = 0; direction < 2; direction++) {
			for (int y = 0; y < HEIGHT; y++)
				for (int x = 0; x < WIDTH; x++)
					f.field[y][x] = gf->field[y][x];
			switch (direction) {
			case 0:
				shiftUp(&f);
				break;
			case 1:
				shiftLeft(&f);
				break;
			}
			for (int y = 0; y < HEIGHT; y++)
				for (int x = 0; x < WIDTH; x++)
					if (f.field[y][x] != gf->field[y][x])
						return 0;
		}
		return 1;
	}
	return 0;
}