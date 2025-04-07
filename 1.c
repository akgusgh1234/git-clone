//2022114815 ����ȣ
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

void readfile(const char* filename, term* a) {//sparse ������ �д� �Լ�
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("���� ���� ����\n");
		return;
	}
	(void)fscanf(fp, "%d %d", &a[0].row, &a[0].col);//������ �� ���� ��� ���� ����

	int value = 0;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			int temp;//�迭�� �����鼭 0�� �ƴϸ� a�� ��,��,���� ����
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
	a[0].value = value;//������ 0�� �ƴѰ��� �� ������ ����
}

void printarray(term *a) {//1���� �迭 term�� ����ϴ� �Լ�
	printf("ROW  COL  VAL\n");
	for (int i = 0; i <= a[0].value; i++) {//a�迭�� �ִ� ���� ���� ����
		printf(" %2d  %2d  %2d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("\n");
	int count = 1;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			if (count <= a[0].value&& a[count].row == i && a[count].col == j) {
				printf(" *");//�迭�� �� row,col�� ����� ���� i,j�� ���Ͽ� ��ġ�ϸ� *���
				count++;
			}
			else
				printf("  ");//�ƴϸ� �������
			
		}
		printf("\n");
	}
}

void rotate90matrix(term a[], term b[]) {
	int numRows = a[0].row;
	int numCols = a[0].col;
	int numTerms = a[0].value;
	//90�� ȸ���̹Ƿ� ��� ���� ���� �ٲ�
	b[0].row = numCols; 
	b[0].col = numRows;
	b[0].value = numTerms;

	for (int i = 1; i <= numTerms; i++) {
		b[i].row = a[i].col;
		b[i].col = numRows - 1 - a[i].row;
		b[i].value = a[i].value;
	}//90�� ȸ���� �����,value���� �ٲ� b�� ����

	for (int i = 1; i <= numTerms - 1; i++) {//ȸ���� ����� ���� ��켱 ���� ���� ������ ������ ����
		for (int j = i + 1; j <= numTerms; j++) {
			if (b[i].row > b[j].row || (b[i].row == b[j].row && b[i].col > b[j].col)) {
				term temp = b[i];
				b[i] = b[j];
				b[j] = temp;//�� ���� ��ȯ
			}
		}
	}
}


int main() {
	readfile("sparse1.txt",a);
	printf("[90�� ȸ���ϱ� ��]\n");
	printarray(a);
	rotate90matrix(a, b);
	printf("\n[90�� ȸ���� ��]\n");
	printarray(b);
	readfile("sparse2.txt", a);
	printf("\n[90�� ȸ���ϱ� ��]\n");
	printarray(a);
	rotate90matrix(a, b);
	printf("\n[90�� ȸ���� ��]\n");
	printarray(b);
}