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

// ������ �ذ� �Լ�
int solveSudoku() {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (solvedBoard[row][col] == 0) { // ���� ���忡�� �� ĭ ã��
                for (int num = 1; num <= size; num++) {
                    if (isSafe(row, col, num)) {
                        solvedBoard[row][col] = num; // ���� ���忡 ���� ä���
                        if (solveSudoku()) { // ��� ȣ��
                            return 1;
                        }
                        solvedBoard[row][col] = 0; // ��Ʈ��ŷ
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

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
            int temp[4][4] = {
                {4, 0, 0, 0},
                {0, 3, 0, 0},
                {3, 0, 1, 4},
                {1, 4, 0, 2}
            };
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    board[i][j] = temp[i][j];
        }

        else if (choice == 2) {
            size = 9;
            int temp[9][9] = {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
            };
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    board[i][j] = temp[i][j];
        }

        else if (choice == 3) {
            size = 16;
            int temp[16][16] = {
                {0, 0, 0, 8, 3, 0, 0, 5, 0, 12, 16, 6, 0, 0, 9, 7},
                {0, 0, 0, 10, 0, 0, 13, 9, 7, 0, 3, 0, 0, 0, 16, 0},
                {0, 7, 16, 0, 15, 0, 0, 0, 0, 0, 8, 0, 1, 13, 0, 0},
                {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 2, 0, 0, 14, 12},
                {0, 3, 9, 0, 5, 15, 0, 0, 0, 0, 0, 12, 0, 14, 11, 1},
                {8, 4, 0, 14, 7, 0, 11, 13, 0, 3, 6, 0, 0, 16, 0, 0},
                {0, 1, 0, 12, 0, 0, 14, 0, 9, 7, 11, 10, 2, 15, 8},
                {16, 13, 10, 11, 12, 0, 1, 2, 0, 15, 0, 5, 3, 4, 0, 0},
                {12, 0, 0, 1, 0, 0, 15, 0, 0, 0, 0, 9, 4, 0, 0, 0},
                {0, 8, 0, 0, 0, 5, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0},
                {7, 0, 0, 0, 10, 3, 0, 0, 0, 5, 0, 0, 0, 0, 0, 8},
                {0, 0, 0, 0, 0, 0, 12, 0, 4, 0, 0, 0, 0, 6, 5, 2},
                {11, 16, 0, 5, 14, 1, 2, 0, 0, 0, 9, 15, 13, 0, 0, 10},
                {9, 10, 12, 6, 0, 0, 0, 0, 0, 8, 0, 0, 0, 2, 0, 0},
                {3, 14, 0, 0, 9, 0, 5, 0, 11, 2, 0, 0, 16, 0, 6, 15},
                {0, 0, 2, 4, 8, 13, 16, 0, 0, 0, 12, 0, 7, 0, 3, 0}
            };
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    board[i][j] = temp[i][j];
        }

        else {
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            continue; // �߸��� �Է��� ��� �ٽ� �ʱ� ȭ�� ���
        }

        while (1) { // ���� ������ ���� ���� ����
            printBoard();
            printf("\n\n[ ȭ��ǥ Ű�� �̵��ϰ� �����Ϸ��� Enter�� ��������. ]\n");
            printf("[ s : ���� ����, c : ���� ������, ESC : �ʱ� ȭ������ ���ư��� ]\n");

            int key = _getch();

            if (key == 224) { // ����Ű �Է�
                key = _getch(); // �� ��° �Է� �ޱ�
                switch (key) {
                case 72: // �� ȭ��ǥ
                    cursorRow = (cursorRow - 1 + size) % size;
                    break;
                case 80: // �Ʒ� ȭ��ǥ
                    cursorRow = (cursorRow + 1) % size;
                    break;
                case 75: // ���� ȭ��ǥ
                    cursorCol = (cursorCol - 1 + size) % size;
                    break;
                case 77: // ������ ȭ��ǥ
                    cursorCol = (cursorCol + 1) % size;
                    break;
                }
            }
            else if (key == 13) { // Enter Ű
                modifyBoard();
            }
            else if (key == 's' || key == 'S') { // 's' Ű
                memcpy(solvedBoard, board, sizeof(board)); // solvedBoard�� board ����
                if (solveSudoku()) {
                    showSolution = 1;
                    printBoard();
                    printf("\n*������ �ذ� �Ϸ�*\n");
                }
            }
            else if (key == 'c' || key == 'C') { // 'c' Ű
                showSolution = 0;
                printBoard();
            }
            else if (key == 27) { // ESC Ű
                system("cls");
                // ���带 �ʱ� ���·� �缳��
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        board[i][j] = 0; // ���带 �ʱ�ȭ
                        isModified[i][j] = 0; // ���� ���ε� �ʱ�ȭ
                    }
                }
                showSolution = 0; // ���� ǥ�� ���� �ʱ�ȭ
                break; // ���� ������ Ż���Ͽ� �ʱ� ȭ������ ���ư�
            }
        }
    }
    return 0;
}