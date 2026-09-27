#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE 50000 // 성능 차이를 명확히 보기 위한 데이터 크기

// 위치 변경 유틸리티 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ---------------------------------------------------
// 1. 배운 정렬: 삽입 정렬 (Insertion Sort)
// ---------------------------------------------------
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ---------------------------------------------------
// 2. 배운 정렬: 퀵 정렬 (Quick Sort)
// ---------------------------------------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// ---------------------------------------------------
// 3. 배우지 않은 정렬: 힙 정렬 (Heap Sort)
// ---------------------------------------------------
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// ---------------------------------------------------
// 배열 복사 및 테스트 실행
// ---------------------------------------------------
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    int *original = (int*)malloc(sizeof(int) * DATA_SIZE);
    int *test_arr = (int*)malloc(sizeof(int) * DATA_SIZE);
    clock_t start, end;
    double time_taken;

    // 난수 생성 시드 초기화 및 배열 생성
    srand(time(NULL));
    for (int i = 0; i < DATA_SIZE; i++) {
        original[i] = rand() % 100000;
    }

    printf("[ 데이터 크기: %d 개 ]\n\n", DATA_SIZE);

    // 1. 삽입 정렬 테스트
    copy_array(original, test_arr, DATA_SIZE);
    start = clock();
    insertion_sort(test_arr, DATA_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("1. 삽입 정렬 (Insertion Sort) 소요 시간: %f 초\n", time_taken);

    // 2. 퀵 정렬 테스트
    copy_array(original, test_arr, DATA_SIZE);
    start = clock();
    quick_sort(test_arr, 0, DATA_SIZE - 1);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("2. 퀵 정렬 (Quick Sort) 소요 시간:      %f 초\n", time_taken);

    // 3. 힙 정렬 테스트
    copy_array(original, test_arr, DATA_SIZE);
    start = clock();
    heap_sort(test_arr, DATA_SIZE);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("3. 힙 정렬 (Heap Sort) 소요 시간:       %f 초\n", time_taken);

    free(original);
    free(test_arr);
    return 0;
}
