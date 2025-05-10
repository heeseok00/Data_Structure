#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    char data[MAX_SIZE];
    int front;  // 앞쪽 포인터 (head → front로 변경)
    int rear;   // 뒤쪽 포인터 (tail → rear로 변경)
} Deque;

// 기본 기능
void create(Deque *dq);
void addRear(Deque *dq, char data);    // 뒤쪽 삽입 (기존 enqueue)
void addFront(Deque *dq, char data);   // 앞쪽 삽입 (새로 추가)
char removeFront(Deque *dq);           // 앞쪽 삭제 (기존 dequeue)
char removeRear(Deque *dq);            // 뒤쪽 삭제 (새로 추가)
void print(Deque *dq);
char peekFront(Deque *dq);             // 앞쪽 데이터 확인
char peekRear(Deque *dq);              // 뒤쪽 데이터 확인
bool is_full(Deque *dq);
bool is_empty(Deque *dq);
int data_count(Deque *dq);
int front_position(Deque *dq);
int rear_position(Deque *dq);
bool is_member(Deque *dq, char data);
void replace_rear(Deque *dq, char new_data);
void clear(Deque *dq);

// 추가 기능
void reverse(Deque *dq);
char get_at(Deque *dq, int position);
void remove_at(Deque *dq, int position);
void insert_at(Deque *dq, char data, int position);
void sort_deque(Deque *dq);
void show_commands(void);

// Deque 생성 - 초기화
void create(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

// 뒤쪽 삽입 (기존 enqueue와 유사)
void addRear(Deque *dq, char data) {
    if (is_full(dq)) {
        printf("Error: Deque is full\n");
        
        // 공간 확보를 위해 데이터 이동 (shift)
        if (dq->front > 0) {
            int count = data_count(dq);
            for (int i = 0; i < count; i++) {
                dq->data[i] = dq->data[dq->front + 1 + i];
            }
            dq->rear = count - 1;
            dq->front = -1;
        } else {
            return;
        }
    }
    
    if (is_empty(dq)) {
        dq->front = -1;
        dq->rear = 0;
        dq->data[dq->rear] = data;
    } else {
        dq->rear++;
        dq->data[dq->rear] = data;
    }
}

// 앞쪽 삽입 (새로운 기능)
void addFront(Deque *dq, char data) {
    if (is_full(dq)) {
        printf("Error: Deque is full\n");
        return;
    }
    
    if (is_empty(dq)) {
        dq->front = -1;
        dq->rear = 0;
        dq->data[dq->rear] = data;
    } else if (dq->front == -1) {
        // 앞쪽에 여유 공간이 없는 경우, 모든 요소를 한 칸씩 뒤로 이동
        if (dq->rear == MAX_SIZE - 1) {
            printf("Error: Cannot add to front (no space to shift)\n");
            return;
        }
        
        for (int i = dq->rear; i >= 0; i--) {
            dq->data[i + 1] = dq->data[i];
        }
        dq->rear++;
        dq->data[0] = data;
    } else {
        // 앞쪽에 여유 공간이 있는 경우
        dq->data[dq->front] = data;
        dq->front--;
    }
}

// 앞쪽 삭제 (기존 dequeue와 유사)
char removeFront(Deque *dq) {
    if (is_empty(dq)) {
        printf("Error: Nothing to remove from front\n");
        return '\0';
    }
    
    dq->front++;
    char result = dq->data[dq->front];
    
    if (dq->front == dq->rear) {
        // Deque가 비게 되는 경우
        dq->front = -1;
        dq->rear = -1;
    }
    
    return result;
}

// 뒤쪽 삭제 (새로운 기능)
char removeRear(Deque *dq) {
    if (is_empty(dq)) {
        printf("Error: Nothing to remove from rear\n");
        return '\0';
    }
    
    char result = dq->data[dq->rear];
    dq->rear--;
    
    if (dq->front == dq->rear) {
        // Deque가 비게 되는 경우
        dq->front = -1;
        dq->rear = -1;
    }
    
    return result;
}

// Deque 출력
void print(Deque *dq) {
    if (is_empty(dq)) {
        printf("Deque is empty\n");
        return;
    }
    
    for (int i = dq->front + 1; i <= dq->rear; i++) {
        printf("%c ", dq->data[i]);
    }
    printf("\n");
}

// 앞쪽 데이터 확인
char peekFront(Deque *dq) {
    if (is_empty(dq)) {
        printf("Error: Deque is empty\n");
        return '\0';
    }
    
    return dq->data[dq->front + 1];
}

// 뒤쪽 데이터 확인
char peekRear(Deque *dq) {
    if (is_empty(dq)) {
        printf("Error: Deque is empty\n");
        return '\0';
    }
    
    return dq->data[dq->rear];
}

// Deque가 가득 찼는지 확인
bool is_full(Deque *dq) {
    return dq->rear == MAX_SIZE - 1;
}

// Deque가 비었는지 확인
bool is_empty(Deque *dq) {
    return (dq->front == -1 && dq->rear == -1) || (dq->front == dq->rear);
}

// 데이터 개수 확인
int data_count(Deque *dq) {
    if (is_empty(dq)) {
        return 0;
    }
    return dq->rear - dq->front;
}

// front 위치 반환
int front_position(Deque *dq) {
    return dq->front + 2;  // front + 2 (슬라이드 참고)
}

// rear 위치 반환
int rear_position(Deque *dq) {
    return dq->rear + 1;  // rear + 1 (슬라이드 참고)
}

// 특정 데이터 존재 여부 확인
bool is_member(Deque *dq, char data) {
    if (is_empty(dq)) {
        return false;
    }
    
    for (int i = dq->front + 1; i <= dq->rear; i++) {
        if (dq->data[i] == data) {
            return true;
        }
    }
    
    return false;
}

// rear 데이터 교체
void replace_rear(Deque *dq, char new_data) {
    if (is_empty(dq)) {
        printf("Error: Deque is empty\n");
        return;
    }
    
    dq->data[dq->rear] = new_data;
}

// Deque 비우기
void clear(Deque *dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Deque 뒤집기
void reverse(Deque *dq) {
    if (is_empty(dq) || data_count(dq) <= 1) {
        return;  // 비었거나 요소가 하나면 뒤집을 필요 없음
    }
    
    int start = dq->front + 1;
    int end = dq->rear;
    
    // 앞뒤 요소 교환
    while (start < end) {
        char temp = dq->data[start];
        dq->data[start] = dq->data[end];
        dq->data[end] = temp;
        start++;
        end--;
    }
}

// 특정 위치 데이터 반환
char get_at(Deque *dq, int position) {
    if (is_empty(dq) || position < 0 || position >= data_count(dq)) {
        printf("Error: Invalid position\n");
        return '\0';
    }
    
    return dq->data[dq->front + 1 + position];
}

// 특정 위치 데이터 제거
void remove_at(Deque *dq, int position) {
    if (is_empty(dq) || position < 0 || position >= data_count(dq)) {
        printf("Error: Invalid position\n");
        return;
    }
    
    // 해당 위치 이후의 요소들을 한 칸씩 앞으로 이동
    for (int i = dq->front + 1 + position; i < dq->rear; i++) {
        dq->data[i] = dq->data[i + 1];
    }
    
    dq->rear--;  // 크기 감소
    
    if (dq->front == dq->rear) {  // 비게 되는 경우
        dq->front = -1;
        dq->rear = -1;
    }
}

// 특정 위치에 데이터 삽입
void insert_at(Deque *dq, char data, int position) {
    if (is_full(dq)) {
        printf("Error: Deque is full\n");
        return;
    }
    
    if (position < 0 || position > data_count(dq)) {
        printf("Error: Invalid position\n");
        return;
    }
    
    // Deque가 비어있는 경우
    if (is_empty(dq)) {
        dq->front = -1;
        dq->rear = 0;
        dq->data[dq->rear] = data;
        return;
    }
    
    // 맨 뒤에 삽입하는 경우
    if (position == data_count(dq)) {
        dq->rear++;
        dq->data[dq->rear] = data;
        return;
    }
    
    // 해당 위치에 삽입하기 위해 요소 이동
    for (int i = dq->rear; i >= dq->front + 1 + position; i--) {
        dq->data[i + 1] = dq->data[i];
    }
    
    dq->data[dq->front + 1 + position] = data;
    dq->rear++;
}

// Deque 정렬
void sort_deque(Deque *dq) {
    if (is_empty(dq) || data_count(dq) <= 1) {
        return;  // 비었거나 요소가 하나면 정렬할 필요 없음
    }
    
    // 버블 정렬 구현
    int count = data_count(dq);
    for (int i = 0; i < count - 1; i++) {
        for (int j = dq->front + 1; j < dq->front + 1 + count - i - 1; j++) {
            if (dq->data[j] > dq->data[j + 1]) {
                // 위치 교환
                char temp = dq->data[j];
                dq->data[j] = dq->data[j + 1];
                dq->data[j + 1] = temp;
            }
        }
    }
}

// 사용 가능한 명령어 표시
void show_commands(void) {
    printf("\n===== Deque(Double-ended Queue) 명령어 목록 =====\n");
    printf("1. create          - Deque 생성 및 초기화\n");
    printf("2. +x              - 데이터 'x'를 뒤쪽에 추가 (addRear)\n");
    printf("3. <x              - 데이터 'x'를 앞쪽에 추가 (addFront)\n");
    printf("4. -               - 앞쪽에서 데이터 제거 (removeFront)\n");
    printf("5. >               - 뒤쪽에서 데이터 제거 (removeRear)\n");
    printf("6. L               - Deque의 모든 데이터 출력 (print)\n");
    printf("7. PF              - 앞쪽 데이터 확인 (peekFront)\n");
    printf("8. PR              - 뒤쪽 데이터 확인 (peekRear)\n");
    printf("9. F               - Deque가 가득 찼는지 확인 (is_full)\n");
    printf("10. E              - Deque가 비었는지 확인 (is_empty)\n");
    printf("11. #              - Deque에 있는 데이터 개수 확인 (data_count)\n");
    printf("12. HF             - front 위치 반환 (front_position)\n");
    printf("13. HR             - rear 위치 반환 (rear_position)\n");
    printf("14. ?x             - 'x'가 Deque에 있는지 확인 (is_member)\n");
    printf("15. =x             - rear 데이터를 'x'로 교체 (replace_rear)\n");
    printf("16. C              - Deque의 모든 데이터 삭제 (clear)\n");
    printf("17. R              - Deque의 데이터 순서 뒤집기 (reverse)\n");
    printf("18. G n            - n번 위치의 데이터 반환 (get_at)\n");
    printf("19. D n            - n번 위치의 데이터 제거 (remove_at)\n");
    printf("20. I x n          - n번 위치에 데이터 'x' 삽입 (insert_at)\n");
    printf("21. S              - Deque의 데이터 오름차순 정렬 (sort_deque)\n");
    printf("22. HELP           - 모든 명령어 목록 표시 (show_commands)\n");
    printf("23. Q              - 프로그램 종료 (quit)\n");
    printf("==========================\n\n");
}

int main() {
    Deque my_deque;
    char cmd, data;
    int position;
    
    // Deque 생성
    create(&my_deque);
    printf("Deque가 생성되었습니다.\n");
    
    // 첫 번째 명령어 입력 안내
    printf("\n명령어를 입력하세요: ");
    
    while (1) {
        scanf(" %c", &cmd);
        
        switch (cmd) {
            case '+':  // addRear
                scanf(" %c", &data);
                addRear(&my_deque, data);
                printf("'%c'를 뒤쪽에 추가했습니다.\n", data);
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case '<':  // addFront
                scanf(" %c", &data);
                addFront(&my_deque, data);
                printf("'%c'를 앞쪽에 추가했습니다.\n", data);
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case '-':  // removeFront
                data = removeFront(&my_deque);
                if (data != '\0') {
                    printf("앞쪽에서 '%c'를 제거했습니다.\n", data);
                    printf("현재 Deque: ");
                    print(&my_deque);
                }
                break;
                
            case '>':  // removeRear
                data = removeRear(&my_deque);
                if (data != '\0') {
                    printf("뒤쪽에서 '%c'를 제거했습니다.\n", data);
                    printf("현재 Deque: ");
                    print(&my_deque);
                }
                break;
                
            case 'L':  // print
            case 'l':
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'P':  // peek (front or rear)
            case 'p':
                scanf(" %c", &data);
                if (data == 'F' || data == 'f') {
                    data = peekFront(&my_deque);
                    if (data != '\0') {
                        printf("Deque의 앞쪽 데이터: %c\n", data);
                    }
                } else if (data == 'R' || data == 'r') {
                    data = peekRear(&my_deque);
                    if (data != '\0') {
                        printf("Deque의 뒤쪽 데이터: %c\n", data);
                    }
                } else {
                    printf("잘못된 peek 명령입니다. PF 또는 PR을 사용하세요.\n");
                }
                break;
                
            case 'F':  // is_full
            case 'f':
                printf("Deque가 가득 찼나요? %s\n", is_full(&my_deque) ? "Yes" : "No");
                break;
                
            case 'E':  // is_empty
            case 'e':
                printf("Deque가 비었나요? %s\n", is_empty(&my_deque) ? "Yes" : "No");
                break;
                
            case '#':  // data_count
                printf("Deque에 있는 데이터 개수: %d\n", data_count(&my_deque));
                break;
                
            case 'H':  // head/front position or rear position
            case 'h':
                scanf(" %c", &data);
                if (data == 'F' || data == 'f') {
                    printf("Front 위치: %d\n", front_position(&my_deque));
                } else if (data == 'R' || data == 'r') {
                    printf("Rear 위치: %d\n", rear_position(&my_deque));
                } else {
                    printf("잘못된 위치 명령입니다. HF 또는 HR을 사용하세요.\n");
                }
                break;
                
            case '?':  // is_member
                scanf(" %c", &data);
                printf("'%c'가 Deque에 있나요? %s\n", data, is_member(&my_deque, data) ? "Yes" : "No");
                break;
                
            case '=':  // replace_rear
                scanf(" %c", &data);
                replace_rear(&my_deque, data);
                printf("Rear 데이터를 '%c'로 교체했습니다.\n", data);
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'C':  // clear
            case 'c':
                clear(&my_deque);
                printf("Deque를 비웠습니다.\n");
                break;
                
            case 'R':  // reverse
            case 'r':
                reverse(&my_deque);
                printf("Deque를 뒤집었습니다.\n");
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'G':  // get_at
            case 'g':
                scanf("%d", &position);
                data = get_at(&my_deque, position);
                if (data != '\0') {
                    printf("%d번 위치의 데이터: %c\n", position, data);
                }
                break;
                
            case 'D':  // remove_at
            case 'd':
                scanf("%d", &position);
                remove_at(&my_deque, position);
                printf("%d번 위치의 데이터를 제거했습니다.\n", position);
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'I':  // insert_at
            case 'i':
                scanf(" %c %d", &data, &position);
                insert_at(&my_deque, data, position);
                printf("'%c'를 %d번 위치에 삽입했습니다.\n", data, position);
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'S':  // sort_deque
            case 's':
                sort_deque(&my_deque);
                printf("Deque를 정렬했습니다.\n");
                printf("현재 Deque: ");
                print(&my_deque);
                break;
                
            case 'Q':  // quit
            case 'q':
                printf("프로그램을 종료합니다.\n");
                return 0;
                
            default:
                // HELP 명령어 처리 (대소문자 모두 인식)
                if ((cmd == 'H' && getchar() == 'E' && getchar() == 'L' && getchar() == 'P') ||
                    (cmd == 'h' && getchar() == 'e' && getchar() == 'l' && getchar() == 'p')) {
                    show_commands();
                } else {
                    printf("알 수 없는 명령입니다. HELP를 입력하면 명령어 목록을 확인할 수 있습니다.\n");
                    
                    // 입력 버퍼 비우기
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                break;
        }
        
        printf("\n명령어를 입력하세요: ");
    }
    
    return 0;
}