#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 전역 변수
int comparisonCount = 0;  // 비교 횟수를 기록하는 변수
int moveCount = 0; // 교환 횟수를 기록하는 변수
int passCount = 0; // 퀵소트 패스 진행 횟수
int isFirst = 0;  // 첫 번째 실행 여부를 나타내는 변수 (0이면 첫 번째 실행)
int totalComparisons = 0;  // 총 비교 횟수
int totalMoveCount = 0; // 총 교환 횟수

// 배열 출력 함수
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // 배열 요소를 출력
    }
    printf("\n");
}

// 랜덤 배열 생성 함수
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 범위의 랜덤 값 생성
    }
}

// 반복적인 퀵소트 함수
void doQuickSort(int arr[], int left, int right) {
    int stack[SIZE]; // 스택을 사용해 재귀 없이 구현
    int top = -1;    // 스택의 최상위 인덱스 초기화

    // 초기 구간을 스택에 푸시
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        int end = stack[top--]; // 스택에서 오른쪽 경계 가져오기
        int start = stack[top--]; // 스택에서 왼쪽 경계 가져오기

        if (start >= end) continue; // 범위가 유효하지 않으면 넘어감

        int pivot = arr[start]; // 피벗 값 설정
        int low = start + 1;    // 피벗 다음 값부터 탐색
        int high = end;         // 배열의 끝에서 역방향 탐색

        // 분할 과정
        while (low <= high) {
            comparisonCount++; // 비교 횟수 증가

            // 피벗보다 작거나 같은 값을 찾을 때까지 low 증가
            while (low <= end && arr[low] <= pivot) {
                low++;
                comparisonCount++;
            }

            // 피벗보다 큰 값을 찾을 때까지 high 감소
            while (high > start && arr[high] >= pivot) {
                high--;
                comparisonCount++;
            }

            if (low < high) { // low와 high가 교차하지 않은 경우
                int temp = arr[low];
                arr[low] = arr[high];
                arr[high] = temp;
                moveCount += 3; // 교환 발생
            }
        }

        // 피벗 위치 교환
        if (start != high) {
            int temp = arr[start];
            arr[start] = arr[high];
            arr[high] = temp;
            moveCount += 3; // 피벗과 교환
        }

        // 첫 번째 실행에서 중간 배열 상태 출력
        if (passCount % 10 == 0 && isFirst == 0) {
            for (int i = 20; i < 40; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n\n");
            for (int i = 40; i < 60; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n\n");
        }

        passCount++; // 패스 횟수 증가

        // 새로운 구간을 스택에 푸시
        if (start < high - 1) {
            stack[++top] = start;
            stack[++top] = high - 1;
        }
        if (high + 1 < end) {
            stack[++top] = high + 1;
            stack[++top] = end;
        }
    }
}

int main() {
    srand(time(NULL)); // 난수 초기화
    int array[SIZE];   // 정렬할 배열

    for (int i = 0; i < 20; i++) { // 20번 반복
        generateRandomArray(array); // 랜덤 배열 생성

        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0; // 교환 횟수 초기화

        if (i == 0) {  // 첫 번째 실행
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result:\n");
            printArray(array, SIZE); // 결과 출력
            isFirst++; // 첫 실행 완료 플래그 설정
        }
        else {
            doQuickSort(array, 0, SIZE - 1); // 이후 실행
        }

        totalComparisons += comparisonCount;  // 총 비교 횟수 누적
        totalMoveCount += moveCount; // 총 교환 횟수 누적
    }

    // 평균 비교 및 교환 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
