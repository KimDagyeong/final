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

// ANSI �̽������� �ڵ� ����
#define BLUE "\033[34m"
#define RED "\033[31m"
#define RESET "\033[0m"

int main() {
    while (1) { // �ʱ� ȭ������ ���ư��� ���� �ֻ��� ����
        printf("�ذ��� ������ ũ�⸦ �����ϼ��� ~ ! \n[ 1. 4X4 | 2. 9X9 | 3. 16X16 | 4. ���� ] : ");
        int choice;
        scanf("%d", &choice);

        if (choice == 4) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }

        // ������ ũ�� ���ð� ���� �ʱ�ȭ �ڵ� ����
        if (choice == 1) {
            size = 4;
        }

        else if (choice == 2) {
            size = 9;
        }

        else if (choice == 3) {
            size = 16;
        }

        else {
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue; // �߸��� �Է��� ��� �ٽ� �ʱ� ȭ�� ���
        }
    }
    return 0;
}