/*
 * 2048 -- the legendary game is now in the console!
 * v0.3
 * 11.12.2019
 * by Centrix
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 4
#define HEIGHT 4

int Field[HEIGHT][WIDTH];
int score = 0;

int random[] = {2,2,2,2,2,2,2,2,2,4};

void fillField(int field[HEIGHT][WIDTH], int filler);
void outputField(int field[HEIGHT][WIDTH]);
void randomGeneration(int field[HEIGHT][WIDTH]);

void shiftUp(int field[HEIGHT][WIDTH]);
void shiftDown(int field[HEIGHT][WIDTH]);
void shiftLeft(int field[HEIGHT][WIDTH]);
void shiftRight(int field[HEIGHT][WIDTH]);

int is_go(int field[HEIGHT][WIDTH]);

int main()
{
	char c;

	fillField(Field, 0);

	while (!is_go(Field)) {
		switch (c=getch()) {
		case ' ':
			break;
		case 'w':
			shiftUp(Field);
			break;
		case 's':
			shiftDown(Field);
			break;
		case 'a':
			shiftLeft(Field);
			break;
		case 'd':
			shiftRight(Field);
			break;
		case 'c':
			fillField(Field, 0);
			score = 0;
			break;
		case 'e':
		case 27:
			return 0;
		default:
			printf("Error: unknow operaton \'%c\'\n", c);
			break;
		}
		system("cls");
		randomGeneration(Field);
		outputField(Field);
	}
	printf("\nGame Over!\n");
	return 0;
}

void fillField(int field[HEIGHT][WIDTH], int filler)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			field[y][x] = filler;
}

void outputField(int field[HEIGHT][WIDTH])
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (field[y][x])
				printf("%4d%s", field[y][x], (WIDTH - x - 1) ? " " : "|\n");
			else
				printf("    %s", (WIDTH - x - 1) ? " " : "|\n");
	printf("Score: %d\n", score);
}

void randomGeneration(int field[HEIGHT][WIDTH])
{
	int number, pos_0, numOf_0 = 0;
	int numberZeros(int field[HEIGHT][WIDTH]);

	if (!(numOf_0 = numberZeros(field)))
		return;
	srand(time(NULL));
	number = random[rand() % 10];
	srand(time(NULL));
	pos_0 = rand() % numOf_0;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++) {
			if (!pos_0 && !field[y][x]) {
				field[y][x] = number;
				return;
			}
			if (!field[y][x])
				pos_0--;
		}
}

void shiftUp(int field[HEIGHT][WIDTH])
{
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 1, posFilling = 0, isPrevOpSum = 0; y < HEIGHT; y++) {
			if (!field[y][x]) {  /* если в тек. ячейке 0 */
				continue;
			} else if (field[y][x] == field[posFilling][x]
					&& !isPrevOpSum) {
				field[posFilling][x] *= 2;
				field[y][x] = 0;
				isPrevOpSum = 1;
				score += field[posFilling++][x];
			} else {
				if (field[posFilling][x])
					posFilling++;
				if (y == posFilling)
					continue;
				field[posFilling][x] = field[y][x];
				field[y][x] = 0;
				isPrevOpSum = 0;
			}
		}
	}
}

void shiftLeft(int field[HEIGHT][WIDTH])
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 1, posFilling = 0, isPrevOpSum = 0; x < WIDTH; x++) {
			if (!field[y][x]) {  /* если в тек. ячейке 0 */ 
				continue;
			} else if (field[y][x] == field[y][posFilling]
					&& !isPrevOpSum) {
				field[y][posFilling] *= 2;
				field[y][x] = 0;
				isPrevOpSum = 1;
				score += field[y][posFilling++];
			} else {
				if (field[y][posFilling])
					posFilling++;
				if (x == posFilling)
					continue;
				field[y][posFilling] = field[y][x];
				field[y][x] = 0;
				isPrevOpSum = 0;
			}
		}
	}
}

void shiftDown(int field[HEIGHT][WIDTH])
{
	for (int x = 0; x < WIDTH; x++) {
		for (int y = HEIGHT - 2, posFilling = HEIGHT - 1, isPrevOpSum = 0; y >= 0; y--) {
			if (!field[y][x]) {  /* если в тек. ячейке 0 */ 
				continue;
			} else if (field[y][x] == field[posFilling][x]
					&& !isPrevOpSum) {
				field[posFilling][x] *= 2;
				field[y][x] = 0;
				isPrevOpSum = 1;
				score += field[posFilling--][x];
			} else {
				if (field[posFilling][x])
					posFilling--;
				if (y == posFilling)
					continue;
				field[posFilling][x] = field[y][x];
				field[y][x] = 0;
				isPrevOpSum = 0;
			}
		}
	}
}

void shiftRight(int field[HEIGHT][WIDTH])
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = WIDTH - 2, posFilling = WIDTH - 1, isPrevOpSum = 0; x >= 0; x--) {
			if (!field[y][x]) {  /* если в тек. ячейке 0 */ 
				continue;
			} else if (field[y][x] == field[y][posFilling]
					&& !isPrevOpSum) {
				field[y][posFilling] *= 2;
				field[y][x] = 0;
				isPrevOpSum = 1;
				score += field[y][posFilling--];
			} else {
				if (field[y][posFilling])
					posFilling--;
				if (x == posFilling)
					continue;
				field[y][posFilling] = field[y][x];
				field[y][x] = 0;
				isPrevOpSum = 0;
			}
		}
	}
}

int numberZeros(int field[HEIGHT][WIDTH])
{
	int numOf_0 = 0;
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			if (!field[y][x])
				numOf_0++;
	return numOf_0;
}

int is_go(int field[HEIGHT][WIDTH])
{
	int f[HEIGHT][WIDTH];
	if (!numberZeros(field)) {
		for (int direction = 0; direction < 2; direction++) {
			for (int y = 0; y < HEIGHT; y++)
				for (int x = 0; x < WIDTH; x++)
					f[y][x] = field[y][x];
			switch (direction) {
			case 0:
				shiftUp(f);
				break;
			case 1:
				shiftLeft(f);
				break;
			}
			for (int y = 0; y < HEIGHT; y++)
				for (int x = 0; x < WIDTH; x++)
					if (f[y][x] != field[y][x])
						return 0;
		}
		return 1;
	}
	return 0;
}