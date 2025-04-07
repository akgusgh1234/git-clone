//2022114815 마현호
#include<stdio.h>
#define MAX_COL 100
#pragma warning (disable:4996)

typedef struct {
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

void printarray(term *a) {//1차원 배열 term을 출력하는 함수
	printf("ROW  COL  VAL\n");
	for (int i = 0; i <= a[0].value; i++) {//a배열에 있는 값에 대한 정보
		printf(" %2d  %2d  %2d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("\n");
	int count = 1;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			if (count <= a[0].value&& a[count].row == i && a[count].col == j) {
				printf(" *");//배열의 각 row,col에 저장된 값과 i,j를 비교하여 일치하면 *출력
				count++;
			}
			else
				printf("  ");//아니면 공백출력
			
		}
		printf("\n");
	}
}

void rotate90matrix(term a[], term b[]) {
	int numRows = a[0].row;
	int numCols = a[0].col;
	int numTerms = a[0].value;
	//90도 회전이므로 행과 열의 값이 바뀜
	b[0].row = numCols; 
	b[0].col = numRows;
	b[0].value = numTerms;

	for (int i = 1; i <= numTerms; i++) {
		b[i].row = a[i].col;
		b[i].col = numRows - 1 - a[i].row;
		b[i].value = a[i].value;
	}//90도 회전한 행과열,value값을 바뀐 b에 전달

	for (int i = 1; i <= numTerms - 1; i++) {//회전된 행렬을 정렬 행우선 정렬 행이 같을시 열기준 정렬
		for (int j = i + 1; j <= numTerms; j++) {
			if (b[i].row > b[j].row || (b[i].row == b[j].row && b[i].col > b[j].col)) {
				term temp = b[i];
				b[i] = b[j];
				b[j] = temp;//두 항을 교환
			}
		}
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