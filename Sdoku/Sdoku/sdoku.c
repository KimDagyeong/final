#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define MAX_SIZE 16

int board[MAX_SIZE][MAX_SIZE];
int solvedBoard[MAX_SIZE][MAX_SIZE]; // 정답을 저장할 배열
int size;
int cursorRow = 0, cursorCol = 0; // 커서 위치
int showSolution = 0;  // 정답 보기 상태를 나타내는 전역 변수, 초기값은 0
int isModified[MAX_SIZE][MAX_SIZE] = { 0 }; // 0으로 초기화

// ANSI 이스케이프 코드 정의
#define BLUE "\033[34m"
#define RED "\033[31m"
#define RESET "\033[0m"

int main() {
    while (1) { // 초기 화면으로 돌아가기 위한 최상위 루프
        printf("해결할 스도쿠 크기를 선택하세요 ~ ! \n[ 1. 4X4 | 2. 9X9 | 3. 16X16 | 4. 종료 ] : ");
        int choice;
        scanf("%d", &choice);

        if (choice == 4) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        // 기존의 크기 선택과 보드 초기화 코드 유지
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
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue; // 잘못된 입력일 경우 다시 초기 화면 출력
        }

        while (1) { // 보드 조작을 위한 내부 루프
            printBoard();
            printf("\n\n[ 화살표 키로 이동하고 수정하려면 Enter를 누르세요. ]\n");
            printf("[ s : 정답 보기, c : 정답 가리기, ESC : 초기 화면으로 돌아가기 ]\n");

            int key = _getch();

            if (key == 224) { // 방향키 입력
                key = _getch(); // 두 번째 입력 받기
                switch (key) {
                case 72: // 위 화살표
                    cursorRow = (cursorRow - 1 + size) % size;
                    break;
                case 80: // 아래 화살표
                    cursorRow = (cursorRow + 1) % size;
                    break;
                case 75: // 왼쪽 화살표
                    cursorCol = (cursorCol - 1 + size) % size;
                    break;
                case 77: // 오른쪽 화살표
                    cursorCol = (cursorCol + 1) % size;
                    break;
                }
            }
            else if (key == 13) { // Enter 키
                modifyBoard();
            }
            else if (key == 's' || key == 'S') { // 's' 키
                memcpy(solvedBoard, board, sizeof(board)); // solvedBoard에 board 복사
                if (solveSudoku()) {
                    showSolution = 1;
                    printBoard();
                    printf("\n*스도쿠 해결 완료*\n");
                }
            }
            else if (key == 'c' || key == 'C') { // 'c' 키
                showSolution = 0;
                printBoard();
            }
            else if (key == 27) { // ESC 키
                system("cls");
                // 보드를 초기 상태로 재설정
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        board[i][j] = 0; // 보드를 초기화
                        isModified[i][j] = 0; // 수정 여부도 초기화
                    }
                }
                showSolution = 0; // 정답 표시 상태 초기화
                break; // 내부 루프를 탈출하여 초기 화면으로 돌아감
            }
        }
    }
    return 0;
}