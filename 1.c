//2022114815 마현호
#include<stdio.h>
#include<stdlib.h>
#define MAX_COL 1000
#pragma warning (disable:4996)

typedef struct {//행, 열, 값을 저장할 구조체
	int col;
	int row;
	int value;
}term;
term a[1000];
term b[1000];

void readfile(const char* filename, term* a) {//sparse 파일을 읽는 함수
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		return;
	}
	(void)fscanf(fp, "%d %d", &a[0].row, &a[0].col);//최초의 두 숫자 행과 열에 저장

	int value = 0;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			int temp;//배열을 읽으면서 0이 아니면 a에 행,열,값을 저장
			(void)fscanf(fp, "%d", &temp);
			if (temp != 0) {
				a[value + 1].row = i;
				a[value + 1].col = j;
				a[value + 1].value = temp;
				value++;
			}
		}

	}
	fclose(fp);
	a[0].value = value;//마지막 0이 아닌값의 총 갯수를 저장
}

void printarray(term* a) {//term 구조체 출력 함수
	printf("ROW  COL  VAL\n");
	for (int i = 0; i <= a[0].value; i++) {
		printf(" %2d  %2d  %2d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("\n");

	// 2차원 형태 출력
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			int found = 0;
			for (int k = 1; k <= a[0].value; k++) {
				if (a[k].row == i && a[k].col == j) {
					found = 1;
					break;
				}
			}
			if (found) {
				printf(" *");
			}
			else {
				printf("  ");
			}
		}
		printf("\n");
	}
}


void rotate90matrix(term a[], term b[]) {//90도 회전 함수
	int numRows = a[0].row;
	int numCols = a[0].col;
	int numTerms = a[0].value;

	b[0].row = numCols; //b의 0번 인덱스에 행, 열, 값 전달
	b[0].col = numRows;
	b[0].value = numTerms;

	int count[MAX_COL] = { 0 };
	int startPos[MAX_COL] = { 0 };

	// 각 열에 해당하는 항 개수 세기
	for (int i = 1; i <= numTerms; i++) {
		count[a[i].col]++;
	}

	// 시작 위치 계산
	startPos[0] = 1;
	for (int i = 1; i < numCols; i++) {
		startPos[i] = startPos[i - 1] + count[i - 1];
	}

	// 회전된 위치에 삽입
	for (int i = 1; i <= numTerms; i++) {
		int col = a[i].col;
		int pos = startPos[col]++;
		b[pos].row = col;
		b[pos].col = numRows - 1 - a[i].row;
		b[pos].value = a[i].value;
	}
	
}




int main() {
	readfile("sparse1.txt",a);
	printf("[90도 회전하기 전]\n");
	printarray(a);
	rotate90matrix(a, b);
	printf("\n[90도 회전한 후]\n");
	printarray(b);
	readfile("sparse2.txt", a);
	printf("\n[90도 회전하기 전]\n");
	printarray(a);
	rotate90matrix(a, b);
	printf("\n[90도 회전한 후]\n");
	printarray(b);
}