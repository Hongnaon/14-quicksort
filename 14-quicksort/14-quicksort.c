#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// ���� ����
int comparisonCount = 0;  // �� Ƚ���� ����ϴ� ����
int moveCount = 0; // ��ȯ Ƚ���� ����ϴ� ����
int passCount = 0; // ����Ʈ �н� ���� Ƚ��
int isFirst = 0;  // ù ��° ���� ���θ� ��Ÿ���� ���� (0�̸� ù ��° ����)
int totalComparisons = 0;  // �� �� Ƚ��
int totalMoveCount = 0; // �� ��ȯ Ƚ��

// �迭 ��� �Լ�
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]); // �迭 ��Ҹ� ���
    }
    printf("\n");
}

// ���� �迭 ���� �Լ�
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000; // 0~999 ������ ���� �� ����
    }
}

// �ݺ����� ����Ʈ �Լ�
void doQuickSort(int arr[], int left, int right) {
    int stack[SIZE]; // ������ ����� ��� ���� ����
    int top = -1;    // ������ �ֻ��� �ε��� �ʱ�ȭ

    // �ʱ� ������ ���ÿ� Ǫ��
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        int end = stack[top--]; // ���ÿ��� ������ ��� ��������
        int start = stack[top--]; // ���ÿ��� ���� ��� ��������

        if (start >= end) continue; // ������ ��ȿ���� ������ �Ѿ

        int pivot = arr[start]; // �ǹ� �� ����
        int low = start + 1;    // �ǹ� ���� ������ Ž��
        int high = end;         // �迭�� ������ ������ Ž��

        // ���� ����
        while (low <= high) {
            comparisonCount++; // �� Ƚ�� ����

            // �ǹ����� �۰ų� ���� ���� ã�� ������ low ����
            while (low <= end && arr[low] <= pivot) {
                low++;
                comparisonCount++;
            }

            // �ǹ����� ū ���� ã�� ������ high ����
            while (high > start && arr[high] >= pivot) {
                high--;
                comparisonCount++;
            }

            if (low < high) { // low�� high�� �������� ���� ���
                int temp = arr[low];
                arr[low] = arr[high];
                arr[high] = temp;
                moveCount += 3; // ��ȯ �߻�
            }
        }

        // �ǹ� ��ġ ��ȯ
        if (start != high) {
            int temp = arr[start];
            arr[start] = arr[high];
            arr[high] = temp;
            moveCount += 3; // �ǹ��� ��ȯ
        }

        // ù ��° ���࿡�� �߰� �迭 ���� ���
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

        passCount++; // �н� Ƚ�� ����

        // ���ο� ������ ���ÿ� Ǫ��
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
    srand(time(NULL)); // ���� �ʱ�ȭ
    int array[SIZE];   // ������ �迭

    for (int i = 0; i < 20; i++) { // 20�� �ݺ�
        generateRandomArray(array); // ���� �迭 ����

        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0; // ��ȯ Ƚ�� �ʱ�ȭ

        if (i == 0) {  // ù ��° ����
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);

            printf("Result:\n");
            printArray(array, SIZE); // ��� ���
            isFirst++; // ù ���� �Ϸ� �÷��� ����
        }
        else {
            doQuickSort(array, 0, SIZE - 1); // ���� ����
        }

        totalComparisons += comparisonCount;  // �� �� Ƚ�� ����
        totalMoveCount += moveCount; // �� ��ȯ Ƚ�� ����
    }

    // ��� �� �� ��ȯ Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
