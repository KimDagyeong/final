#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define MAX_SIZE 16

int board[MAX_SIZE][MAX_SIZE];
int solvedBoard[MAX_SIZE][MAX_SIZE]; // ������ ������ �迭
int size;
int cursorRow = 0, cursorCol = 0; // Ŀ�� ��ġ
int showSolution = 0;  // ���� ���� ���¸� ��Ÿ���� ���� ����, �ʱⰪ�� 0
int isModified[MAX_SIZE][MAX_SIZE] = { 0 }; // 0���� �ʱ�ȭ