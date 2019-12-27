/*
 * 2048 -- the legendary game is now in the console!
 * v0.8
 * 27.12.2019
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

typedef struct {
	int *rand_m;
	int sm_comp;
	int lg_comp;
	int sm_comp_size;
	int lg_comp_size;
	int fill;
} grand;

gfield Field;
grand Rand;

void fillField(gfield *gf, int filler);
void outputField(gfield *gf);
void randomGeneration(gfield *gf, grand *gr);
int *at(gfield *gf, int y, int x);
void set_h(gfield *gf, int val);
void set_w(gfield *gf, int val);
void set_score(gfield *gf, int val);
void initField(gfield *gf);
void freeField(gfield *gf);

void set_smc_r(grand *gr, int val);
void set_lgc_r(grand *gr, int val);
void set_smc_size_r(grand *gr, int val);
void set_lgc_size_r(grand *gr, int val);
void initRand(grand *gr);
void freeRand(grand *gr);

void shiftUp(gfield *gf);
void shiftDown(gfield *gf);
void shiftLeft(gfield *gf);
void shiftRight(gfield *gf);

int is_go(gfield *gf);

int main()
{
	char c;
	int h, w;

	printf("\t\t\t2048\n\n");

	printf("Enter height: ");
	scanf("%d", &h);
	printf("Enter width: ");
	scanf("%d", &w);

	set_h(&Field, h);
	set_w(&Field, w);
	set_score(&Field, 0);
	initField(&Field);
	fillField(&Field, 0);

	set_smc_r(&Rand, 2);
	set_lgc_r(&Rand, 4);
	set_smc_size_r(&Rand, 9);
	set_lgc_size_r(&Rand, 1);
	initRand(&Rand);

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
			freeRand(&Rand);
			return 0;
		default:
			printf("Error: unknow operaton \'%c\'\n", c);
			break;
		}
		system("cls");
		randomGeneration(&Field, &Rand);
		outputField(&Field);
	}
	printf("\nGame Over!\n");

	freeField(&Field);
	freeRand(&Rand);

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

void randomGeneration(gfield *gf, grand *gr)
{
	int number, pos_0, numOf_0 = 0;
	int numberZeros(gfield *gf);

	if (!(numOf_0 = numberZeros(gf)))
		return;
	srand(time(NULL));
	number = gr->rand_m[rand() % 10];
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
		freeField(gf);
		exit(0);
	}
}

void freeField(gfield *gf)
{
	free(gf->field);
}

void set_smc_r(grand *gr, int val)
{
	gr->sm_comp = val;
}

void set_lgc_r(grand *gr, int val)
{
	gr->lg_comp = val;
}

void set_smc_size_r(grand *gr, int val)
{
	gr->sm_comp_size = val;
}
void set_lgc_size_r(grand *gr, int val)
{
	gr->lg_comp_size = val;
}

void initRand(grand *gr)
{
	int i;
	int size = gr->sm_comp_size + gr->lg_comp_size;
	if ((gr->rand_m = (int *) malloc(size * sizeof(int))) == NULL) {
		printf("Error: not enough memory\n");
		freeRand(gr);
		exit(0);
	}

	for (i = 0; i < gr->sm_comp_size; i++)
		gr->rand_m[i] = gr->sm_comp;
	for (; i < size; i++)
		gr->rand_m[i] = gr->lg_comp;
}

void freeRand(grand *gr)
{
	free(gr->rand_m);
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
		f.h = gf->h;
		f.w = gf->w;
		initField(&f);
		for (int direction = 0; direction < 2; direction++) {
			for (int y = 0; y < gf->h; y++)
				for (int x = 0; x < gf->w; x++)
					*at(&f, y, x) = *at(gf, y, x);
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
					if (*at(&f, y, x) != *at(gf, y, x)) {
						freeField(&f);
						return 0;
					}
		}
		freeField(&f);
		return 1;
	}
	return 0;
}