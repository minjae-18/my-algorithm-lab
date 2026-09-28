#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
// 3. 배우지 않은 정렬: 힙 정렬 (Heap Sort) - [AI 학습]
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
// 배열 복사 유틸리티 함수
// ---------------------------------------------------
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// ---------------------------------------------------
// 메인 함수: 성능 측정 로직
// ---------------------------------------------------
int main() {
    // 보고서 내용과 일치하도록 3가지 데이터 크기로 연속 테스트 진행
    int sizes[] = {10000, 50000, 100000};
    int num_sizes = 3;

    printf("=======================================================================\n");
    printf("%-15s | %-15s | %-15s | %-15s\n", "데이터 크기(N)", "삽입 정렬(초)", "퀵 정렬(초)", "힙 정렬(초)");
    printf("=======================================================================\n");

    // 난수 생성 시드 초기화
    srand(time(NULL));

    for (int s = 0; s < num_sizes; s++) {
        int current_size = sizes[s];
        
        // [중요] 스택 메모리 초과 방지를 위한 동적 할당 (malloc 사용)
        int *original = (int*)malloc(sizeof(int) * current_size);
        int *test_arr = (int*)malloc(sizeof(int) * current_size);
        
        // 데이터 크기만큼 난수 배열 생성
        for (int i = 0; i < current_size; i++) {
            original[i] = rand() % 100000;
        }

        clock_t start, end;
        double time_insertion, time_quick, time_heap;

        // --- 1. 삽입 정렬 측정 ---
        copy_array(original, test_arr, current_size);
        start = clock();
        insertion_sort(test_arr, current_size);
        end = clock();
        time_insertion = ((double)(end - start)) / CLOCKS_PER_SEC;

        // --- 2. 퀵 정렬 측정 ---
        copy_array(original, test_arr, current_size);
        start = clock();
        quick_sort(test_arr, 0, current_size - 1);
        end = clock();
        time_quick = ((double)(end - start)) / CLOCKS_PER_SEC;

        // --- 3. 힙 정렬 측정 ---
        copy_array(original, test_arr, current_size);
        start = clock();
        heap_sort(test_arr, current_size);
        end = clock();
        time_heap = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 측정 결과 표 형식으로 출력
        printf("%-15d | %-15.5f | %-15.5f | %-15.5f\n", current_size, time_insertion, time_quick, time_heap);

        // 사용 완료된 메모리 해제
        free(original);
        free(test_arr);
    }
    printf("=======================================================================\n");

    return 0;
}
