/*
 * 2048 -- the legendary game is now in the console!
 * v0.7
 * 26.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLEN 1024

typedef struct {
	int *field;
	int score;
	int h;
	int w;
} gfield;

gfield Field;

int randomv[] = {2,2,2,2,2,2,2,2,2,4};

void fillField(gfield *gf, int filler);
void outputField(gfield *gf);
void randomGeneration(gfield *gf);
int *at(gfield *gf, int y, int x);
void set_h(gfield *gf, int val);
void set_w(gfield *gf, int val);
void set_score(gfield *gf, int val);
void initField(gfield *gf);
void freeField(gfield *gf);

void shiftUp(gfield *gf);
void shiftDown(gfield *gf);
void shiftLeft(gfield *gf);
void shiftRight(gfield *gf);

int is_go(gfield *gf);

int main()
{
	char c;
	int h, w;

	printf("Enter height: ");
	scanf("%d", &h);
	printf("Enter width: ");
	scanf("%d", &w);
	set_h(&Field, h);
	set_w(&Field, w);
	initField(&Field);

	fillField(&Field, 0);
	set_score(&Field, 0);

	printf("Press 'space' to start...\n");

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
			set_score(&Field, 0);
			break;
		case 'e':
		case 27:
			freeField(&Field);
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
	freeField(&Field);
	return 0;
}

void fillField(gfield *gf, int filler)
{
	for (int y = 0; y < gf->h; y++)
		for (int x = 0; x < gf->w; x++)
			*at(gf, y, x) = filler;
}

void outputField(gfield *gf)
{
	int maxLenCell(gfield *gf);
	int mlc = maxLenCell(gf);
	char cz = ' ';
	for (int y = 0; y < gf->h; y++)
		for (int x = 0; x < gf->w; x++)
			if (*at(gf, y, x))
				printf("%*d%s", mlc, *at(gf, y, x), (gf->w - x - 1) ? " " : "|\n");
			else
				printf("%*c%s", mlc, cz, (gf->w - x - 1) ? " " : "|\n");
	printf("Score: %d\n", gf->score);
}

int maxLenCell(gfield *gf)
{
	int cell, lc, mlc = 1;
	for (int y = 0; y < gf->h; y++)
		for (int x = 0; x < gf->w; x++) {
			cell = *at(gf, y, x);
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
	for (int y = 0; y < gf->h; y++)
		for (int x = 0; x < gf->w; x++) {
			if (!pos_0 && !*at(gf, y, x)) {
				*at(gf, y, x) = number;
				return;
			}
			if (!*at(gf, y, x))
				pos_0--;
		}
}

int *at(gfield *gf, int y, int x)
{
	return &(gf->field[gf->w * y + x]);
}

void set_h(gfield *gf, int val)
{
	gf->h = val;
}

void set_w(gfield *gf, int val)
{
	gf->w = val;
}

void set_score(gfield *gf, int val)
{
	if (val < 0)
		val = -val;
	gf->score = val;
}

void initField(gfield *gf)
{
	int size = gf->h * gf->w;
	if ((gf->field = (int *) malloc(size * sizeof(int))) == NULL) {
		printf("Error: not enough memory\n");
		exit(0);
	}
}

void freeField(gfield *gf)
{
	free(gf->field);
}

void shiftUp(gfield *gf)
{
	for (int x = 0; x < gf->w; x++)
		for (int y = 1, posFilling = 0, isPrevOpSum = 0; y < gf->h; y++)
			if (!*at(gf, y, x)) {
				continue;
			} else if (*at(gf, y, x) == *at(gf, posFilling, x)
					&& !isPrevOpSum) {
				*at(gf, posFilling, x) *= 2;
				*at(gf, y, x) = 0;
				isPrevOpSum = 1;
				gf->score += *at(gf, posFilling++, x);
			} else {
				if (*at(gf, posFilling, x))
					posFilling++;
				if (y == posFilling)
					continue;
				*at(gf, posFilling, x) = *at(gf, y, x);
				*at(gf, y, x) = 0;
				isPrevOpSum = 0;
			}
}

void shiftLeft(gfield *gf)
{
	for (int y = 0; y < gf->h; y++)
		for (int x = 1, posFilling = 0, isPrevOpSum = 0; x < gf->w; x++)
			if (!*at(gf, y, x)) {
				continue;
			} else if (*at(gf, y, x) == *at(gf, y, posFilling)
					&& !isPrevOpSum) {
				*at(gf, y, posFilling) *= 2;
				*at(gf, y, x) = 0;
				isPrevOpSum = 1;
				gf->score += *at(gf, y, posFilling++);
			} else {
				if (*at(gf, y, posFilling))
					posFilling++;
				if (x == posFilling)
					continue;
				*at(gf, y, posFilling) = *at(gf, y, x);
				*at(gf, y, x) = 0;
				isPrevOpSum = 0;
			}
}

void shiftDown(gfield *gf)
{
	for (int x = 0; x < gf->w; x++)
		for (int y = gf->h - 2, posFilling = gf->h - 1, isPrevOpSum = 0; y >= 0; y--)
			if (!*at(gf, y, x)) {
				continue;
			} else if (*at(gf, y, x) == *at(gf, posFilling, x)
					&& !isPrevOpSum) {
				*at(gf, posFilling, x) *= 2;
				*at(gf, y, x) = 0;
				isPrevOpSum = 1;
				gf->score += *at(gf, posFilling--, x);
			} else {
				if (*at(gf, posFilling, x))
					posFilling--;
				if (y == posFilling)
					continue;
				*at(gf, posFilling, x) = *at(gf, y, x);
				*at(gf, y, x) = 0;
				isPrevOpSum = 0;
			}
}

void shiftRight(gfield *gf)
{
	for (int y = 0; y < gf->h; y++)
		for (int x = gf->w - 2, posFilling = gf->w - 1, isPrevOpSum = 0; x >= 0; x--)
			if (!*at(gf, y, x)) {
				continue;
			} else if (*at(gf, y, x) == *at(gf, y, posFilling)
					&& !isPrevOpSum) {
				*at(gf, y, posFilling) *= 2;
				*at(gf, y, x) = 0;
				isPrevOpSum = 1;
				gf->score += *at(gf, y, posFilling--);
			} else {
				if (*at(gf, y, posFilling))
					posFilling--;
				if (x == posFilling)
					continue;
				*at(gf, y, posFilling) = *at(gf, y, x);
				*at(gf, y, x) = 0;
				isPrevOpSum = 0;
			}
}

int numberZeros(gfield *gf)
{
	int numOf_0 = 0;
	for (int y = 0; y < gf->h; y++)
		for (int x = 0; x < gf->w; x++)
			if (!*at(gf, y, x))
				numOf_0++;
	return numOf_0;
}

int is_go(gfield *gf)
{
	if (!numberZeros(gf)) {
		gfield f;
		for (int direction = 0; direction < 2; direction++) {
			for (int y = 0; y < gf->h; y++)
				for (int x = 0; x < gf->w; x++)
					*at(&f, y, x) = *at(&f, y, x);
			switch (direction) {
			case 0:
				shiftUp(&f);
				break;
			case 1:
				shiftLeft(&f);
				break;
			}
			for (int y = 0; y < gf->h; y++)
				for (int x = 0; x < gf->w; x++)
					if (*at(&f, y, x) != *at(&f, y, x))
						return 0;
		}
		return 1;
	}
	return 0;
}