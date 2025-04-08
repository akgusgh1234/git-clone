//2022114815 ����ȣ
#include<stdio.h>
#include<stdlib.h>
#define MAX_COL 1000
#pragma warning (disable:4996)

typedef struct {//��, ��, ���� ������ ����ü
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

void printarray(term* a) {//term ����ü ��� �Լ�
	printf("ROW  COL  VAL\n");
	for (int i = 0; i <= a[0].value; i++) {
		printf(" %2d  %2d  %2d\n", a[i].row, a[i].col, a[i].value);
	}
	printf("\n");

	// 2���� ���� ���
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


void rotate90matrix(term a[], term b[]) {//90�� ȸ�� �Լ�
	int numRows = a[0].row;
	int numCols = a[0].col;
	int numTerms = a[0].value;

	b[0].row = numCols; //b�� 0�� �ε����� ��, ��, �� ����
	b[0].col = numRows;
	b[0].value = numTerms;

	int count[MAX_COL] = { 0 };
	int startPos[MAX_COL] = { 0 };

	// �� ���� �ش��ϴ� �� ���� ����
	for (int i = 1; i <= numTerms; i++) {
		count[a[i].col]++;
	}

	// ���� ��ġ ���
	startPos[0] = 1;
	for (int i = 1; i < numCols; i++) {
		startPos[i] = startPos[i - 1] + count[i - 1];
	}

	// ȸ���� ��ġ�� ����
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