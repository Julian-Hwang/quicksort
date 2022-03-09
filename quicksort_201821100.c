#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double toc(double tstart);
typedef struct DATA { double x; double y; double sum;} DTYPE; //정렬할 (배정도 실수형, 배정도 실수형) 데이터로 정의
//#define DTYPE double //데이터를 정의하면서 정의된 DTYPE은 주석처리
DTYPE* mk_rand_data(int N);
void sort_201821100(DTYPE arr[], int N);
int partition(DTYPE A[], int N);

int main(int argc, char* argv[])
{
  DTYPE* arr;
  double tstart;
  int N, i;
  N = atoi(argv[1]);
  srand(time(NULL));
  arr=mk_rand_data(N);
  printf("\n sort .... \n");
  tstart = clock();
  sort_201821100(arr, N);
  printf("sort_201821100: %f\n", toc(tstart));
}

DTYPE* mk_rand_data(int N)
{
	DTYPE* arr = (DTYPE*)malloc(sizeof(DTYPE) * N); //데이터 double 크기 만큼 동적할당 하기
	int index = 0;
	for (index; index < N; index++)
	{
		arr[index].x = rand() / (double)RAND_MAX; //x값들 랜덤선언하기
		arr[index].y = rand() / (double)RAND_MAX; //y값들 랜덤선언하기

		arr[index].sum = arr[index].x + arr[index].y; //x와 y의 합들 나열
	}
	return arr;
}

void sort_201821100(DTYPE A[], int N)
{
	int piv;
	
	if (N > 1) {
		piv = partition(A, N); //중간에 피봇값이 리턴, 왼쪽은 작은 값들 오른쪽은 큰값들이 배치된다.
		sort_201821100(A, piv); //if) piv=5이면 5는 왼쪽 파티션이다.
		sort_201821100(A + piv + 1, N - piv – 1); // if) 오른쪽 6,3
	}
}

int partition(DTYPE A[], int N) { //인덱스를 리턴
	int P = N / 2;
	int i = 0, j = N;
	for (i = 0; i < j; i++) //x와 y의 합을 나타내기 위한 loop문 선언
	{
		A[i].sum = A[i].x + A[i].y;
	}
	
	double pivot; //피봇 선언
	SWAP(A[N / 2], A[0]);
	pivot = A[0].sum; //x와y의 합을 이용한 피봇의 첫 번째 원소
	while (1) { //파티션이 완료될 때 까지
		while ((A[++i].sum > pivot) && (i < N)); //피봇보다 큰 값을 만날 때 까지 내림차순 정렬
		while ((A[--j].sum < pivot) && (j > 0)); //피봇보다 작은 값을 만날 때 까지 내림차순 정렬
		if (i >= j) break; //위에서 계산된 I와 j가 만나거나 엇갈리면 종료된다.
		SWAP(A[i], A[j]); //swap구문으로 두 원소를 교환한다.
	}
	SWAP(A[0], A[j]); //피봇정렬완료
	return j;
}
