#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct {
    char data[MAX_SIZE];
    int size;
    int pos;
} ArrayADT;

void create(ArrayADT *arr) {
    arr->size = 0;
    arr->pos = -1;
    memset(arr->data, 0, MAX_SIZE);
}

void insert(ArrayADT *arr, char value) {
    if (arr->size >= MAX_SIZE) {
        printf("Array is full.\n");
        return;
    }
    if (arr->size == 0) {
        arr->data[0] = value;
        arr->pos = 0;
    } else {
        for (int i = arr->size; i > arr->pos + 1; i--) {
            arr->data[i] = arr->data[i - 1];
        }
        arr->data[arr->pos + 1] = value;
        arr->pos++;
    }
    arr->size++;
}

void delete(ArrayADT *arr) {
    if (arr->size == 0 || arr->pos >= arr->size) {
        printf("Nothing to delete.\n");
        return;
    }
    for (int i = arr->pos; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    if (arr->pos >= arr->size && arr->size > 0) arr->pos = arr->size - 1;
}

void traverse_front(ArrayADT *arr) {
    for (int i = 0; i < arr->size; i++) {
        printf("%c ", arr->data[i]);
    }
    printf("\n");
}

void traverse_rear(ArrayADT *arr) {
    for (int i = arr->size - 1; i >= 0; i--) {
        printf("%c ", arr->data[i]);
    }
    printf("\n");
}

char get_data(ArrayADT *arr) {
    if (arr->size == 0 || arr->pos >= arr->size || arr->pos < 0) {
        printf("No data at current position.\n");
        return '\0';
    }
    return arr->data[arr->pos];
}

void replace(ArrayADT *arr, char new_value) {
    if (arr->size == 0 || arr->pos >= arr->size || arr->pos < 0) {
        printf("Cannot replace, invalid position.\n");
        return;
    }
    arr->data[arr->pos] = new_value;
}

bool empty(ArrayADT *arr) {
    return arr->size == 0;
}

void move(ArrayADT *arr, const char* cmd) {
    if (cmd[0] == 'M') {
        if (cmd[1] == 'P' && arr->pos > 0) arr->pos--;
        else if (cmd[1] == 'N' && arr->pos < arr->size - 1) arr->pos++;
        else {
            int index = atoi(&cmd[1]);
            if (index >= 0 && index < arr->size) arr->pos = index;
        }
    }
}

int data_count(ArrayADT *arr) {
    return arr->size;
}

void print(ArrayADT *arr) {
    printf("[ ");
    for (int i = 0; i < arr->size; i++) {
        printf("%c ", arr->data[i]);
    }
    printf("] (pos: %d)\n", arr->pos);
}

// 배열 전체 데이터를 초기화하는 함수 clear_all 을 정의해보았습니다.
void clear_all(ArrayADT *arr) {
    arr->size = 0;
    arr->pos = -1;
    memset(arr->data, 0, MAX_SIZE);
}

// 배열에서 특정 문자의 위치를 찾아 반환하는 함수 find_char 를 정의해보았습니다.
int find_char(ArrayADT *arr, char target) {
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == target) return i;
    }
    return -1;
}

// 배열 데이터를 반대로 뒤집는 함수 flip_array 를 정의해보았습니다.
void flip_array(ArrayADT *arr) {
    for (int i = 0; i < arr->size / 2; i++) {
        char temp = arr->data[i];
        arr->data[i] = arr->data[arr->size - 1 - i];
        arr->data[arr->size - 1 - i] = temp;
    }
}

int main() {
    ArrayADT myArray;
    create(&myArray);

    insert(&myArray, 'a');
    insert(&myArray, 'b');
    insert(&myArray, 'c');
    insert(&myArray, 'd');
    insert(&myArray, 'e');

    move(&myArray, "M2");
    traverse_front(&myArray);
    move(&myArray, "M0");
    print(&myArray);
    move(&myArray, "Mn");
    move(&myArray, "MP");
    move(&myArray, "MN");
    print(&myArray);

    insert(&myArray, 'f');
    insert(&myArray, 'g');
    print(&myArray);

    move(&myArray, "Mn");
    delete(&myArray);
    print(&myArray);

    move(&myArray, "M1");
    delete(&myArray);
    print(&myArray);

    printf("Current data: %c\n", get_data(&myArray));
    replace(&myArray, 'h');
    print(&myArray);

    clear_all(&myArray);
    printf("Is empty: %s\n", empty(&myArray) ? "Yes" : "No");

    return 0;
}