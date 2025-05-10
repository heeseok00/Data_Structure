#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10

typedef struct {
    char data[MAX_SIZE];
    int head;
    int tail;
} Queue;

// 기본 기능
void create(Queue *q);
void enqueue(Queue *q, char data);
char dequeue(Queue *q);
void print(Queue *q);
char peek(Queue *q);
bool is_full(Queue *q);
bool is_empty(Queue *q);
int data_count(Queue *q);
int head_position(Queue *q);
int tail_position(Queue *q);
bool is_member(Queue *q, char data);
void replace(Queue *q, char new_data);
void clear(Queue *q);

// 추가 기능 5개
void reverse(Queue *q);                // 1. 큐의 순서를 뒤집는 기능
char get_at(Queue *q, int position);   // 2. 특정 위치의 데이터 반환 기능
void remove_at(Queue *q, int position); // 3. 특정 위치의 데이터 제거 기능
void insert_at(Queue *q, char data, int position); // 4. 특정 위치에 데이터 삽입 기능
void sort_queue(Queue *q);            // 5. 큐의 데이터를 정렬하는 기능

// 추가 기능 6: 사용 가능한 명령어 보여주기
void show_commands(void);

// 큐 생성 - 초기화
void create(Queue *q) {
    q->head = -1;
    q->tail = -1;
}

// 데이터 삽입
void enqueue(Queue *q, char data) {
    if (is_full(q)) {
        printf("Error: Queue is full\n");
        
        // 공간 확보를 위해 데이터 이동 (shift)
        if (q->head > 0) {
            int count = data_count(q);
            for (int i = 0; i < count; i++) {
                q->data[i] = q->data[q->head + 1 + i];
            }
            q->tail = count - 1;
            q->head = -1;
        } else {
            return;
        }
    }
    
    if (is_empty(q)) {
        q->head = -1;
        q->tail = 0;
        q->data[q->tail] = data;
    } else {
        q->tail++;
        q->data[q->tail] = data;
    }
}

// 데이터 추출
char dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Error: Nothing to dequeue\n");
        return '\0';
    }
    
    q->head++;
    char result = q->data[q->head];
    
    if (q->head == q->tail) {
        // 큐가 비게 되는 경우
        q->head = -1;
        q->tail = -1;
    }
    
    return result;
}

// 큐 출력
void print(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    for (int i = q->head + 1; i <= q->tail; i++) {
        printf("%c ", q->data[i]);
    }
    printf("\n");
}

// 맨 앞 데이터 확인
char peek(Queue *q) {
    if (is_empty(q)) {
        printf("Error: Queue is empty\n");
        return '\0';
    }
    
    return q->data[q->head + 1];
}

// 큐가 가득 찼는지 확인
bool is_full(Queue *q) {
    return q->tail == MAX_SIZE - 1;
}

// 큐가 비었는지 확인
bool is_empty(Queue *q) {
    return (q->head == -1 && q->tail == -1) || (q->head == q->tail);
}

// 데이터 개수 확인
int data_count(Queue *q) {
    if (is_empty(q)) {
        return 0;
    }
    return q->tail - q->head;
}

// head 위치 반환
int head_position(Queue *q) {
    return q->head + 2;  // head + 2 (슬라이드 참고)
}

// tail 위치 반환
int tail_position(Queue *q) {
    return q->tail + 1;  // tail + 1 (슬라이드 참고)
}

// 특정 데이터 존재 여부 확인
bool is_member(Queue *q, char data) {
    if (is_empty(q)) {
        return false;
    }
    
    for (int i = q->head + 1; i <= q->tail; i++) {
        if (q->data[i] == data) {
            return true;
        }
    }
    
    return false;
}

// tail 데이터 교체
void replace(Queue *q, char new_data) {
    if (is_empty(q)) {
        printf("Error: Queue is empty\n");
        return;
    }
    
    q->data[q->tail] = new_data;
}

// 큐 비우기
void clear(Queue *q) {
    q->head = -1;
    q->tail = -1;
}

// 추가 기능 1: 큐 뒤집기
void reverse(Queue *q) {
    if (is_empty(q) || data_count(q) <= 1) {
        return;  // 비었거나 요소가 하나면 뒤집을 필요 없음
    }
    
    int start = q->head + 1;
    int end = q->tail;
    
    // 앞뒤 요소 교환
    while (start < end) {
        char temp = q->data[start];
        q->data[start] = q->data[end];
        q->data[end] = temp;
        start++;
        end--;
    }
}

// 추가 기능 2: 특정 위치 데이터 반환
char get_at(Queue *q, int position) {
    if (is_empty(q) || position < 0 || position >= data_count(q)) {
        printf("Error: Invalid position\n");
        return '\0';
    }
    
    return q->data[q->head + 1 + position];
}

// 추가 기능 3: 특정 위치 데이터 제거
void remove_at(Queue *q, int position) {
    if (is_empty(q) || position < 0 || position >= data_count(q)) {
        printf("Error: Invalid position\n");
        return;
    }
    
    // 해당 위치 이후의 요소들을 한 칸씩 앞으로 이동
    for (int i = q->head + 1 + position; i < q->tail; i++) {
        q->data[i] = q->data[i + 1];
    }
    
    q->tail--;  // 크기 감소
    
    if (q->head == q->tail) {  // 비게 되는 경우
        q->head = -1;
        q->tail = -1;
    }
}

// 추가 기능 4: 특정 위치에 데이터 삽입
void insert_at(Queue *q, char data, int position) {
    if (is_full(q)) {
        printf("Error: Queue is full\n");
        return;
    }
    
    if (position < 0 || position > data_count(q)) {
        printf("Error: Invalid position\n");
        return;
    }
    
    // 큐가 비어있는 경우
    if (is_empty(q)) {
        q->head = -1;
        q->tail = 0;
        q->data[q->tail] = data;
        return;
    }
    
    // 맨 뒤에 삽입하는 경우
    if (position == data_count(q)) {
        q->tail++;
        q->data[q->tail] = data;
        return;
    }
    
    // 해당 위치에 삽입하기 위해 요소 이동
    for (int i = q->tail; i >= q->head + 1 + position; i--) {
        q->data[i + 1] = q->data[i];
    }
    
    q->data[q->head + 1 + position] = data;
    q->tail++;
}

// 추가 기능 5: 큐 정렬
void sort_queue(Queue *q) {
    if (is_empty(q) || data_count(q) <= 1) {
        return;  // 비었거나 요소가 하나면 정렬할 필요 없음
    }
    
    // 버블 정렬 구현
    int count = data_count(q);
    for (int i = 0; i < count - 1; i++) {
        for (int j = q->head + 1; j < q->head + 1 + count - i - 1; j++) {
            if (q->data[j] > q->data[j + 1]) {
                // 위치 교환
                char temp = q->data[j];
                q->data[j] = q->data[j + 1];
                q->data[j + 1] = temp;
            }
        }
    }
}

// 추가 기능 6: 사용 가능한 명령어 표시
void show_commands(void) {
    printf("\n===== 큐(Queue) 명령어 목록 =====\n");
    printf("1. create          - 큐 생성 및 초기화 (char my_queue[Max_Size])\n");
    printf("2. +x              - 데이터 'x'를 큐에 추가 (enqueue)\n");
    printf("3. -               - 큐에서 데이터 제거 (dequeue)\n");
    printf("4. L               - 큐의 모든 데이터 출력 (print)\n");
    printf("5. P               - 큐의 맨 앞 데이터 확인 (peek)\n");
    printf("6. F               - 큐가 가득 찼는지 확인 (is_full)\n");
    printf("7. E               - 큐가 비었는지 확인 (is_empty)\n");
    printf("8. #               - 큐에 있는 데이터 개수 확인 (data_count)\n");
    printf("9. H               - head 위치 반환 (head_position)\n");
    printf("10. T              - tail 위치 반환 (tail_position)\n");
    printf("11. ?x             - 'x'가 큐에 있는지 확인 (is_member)\n");
    printf("12. =x             - tail 데이터를 'x'로 교체 (replace)\n");
    printf("13. C              - 큐의 모든 데이터 삭제 (clear)\n");
    printf("\n===== 추가 명령어 목록 =====\n");
    printf("14. R              - 큐의 데이터 순서 뒤집기 (reverse)\n");
    printf("15. G n            - n번 위치의 데이터 반환 (get_at)\n");
    printf("16. D n            - n번 위치의 데이터 제거 (remove_at)\n");
    printf("17. I x n          - n번 위치에 데이터 'x' 삽입 (insert_at)\n");
    printf("18. S              - 큐의 데이터 오름차순 정렬 (sort_queue)\n");
    printf("19. HELP           - 모든 명령어 목록 표시 (show_commands)\n");
    printf("==========================\n\n");
}

int main() {
    Queue my_queue;
    char cmd, data;
    int position;
    
    // 큐 생성
    create(&my_queue);
    printf("큐가 생성되었습니다.\n");
    
    // 첫 번째 명령어 입력 안내 (명령어 목록 표시 없이)
    printf("\n명령어를 입력하세요: ");
    
    while (1) {
        scanf(" %c", &cmd);
        
        switch (cmd) {
            case '+':  // enqueue
                scanf(" %c", &data);
                enqueue(&my_queue, data);
                printf("'%c'를 큐에 추가했습니다.\n", data);
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case '-':  // dequeue
                data = dequeue(&my_queue);
                if (data != '\0') {
                    printf("'%c'를 큐에서 제거했습니다.\n", data);
                    printf("현재 큐: ");
                    print(&my_queue);
                }
                break;
                
            case 'L':  // print
            case 'l':
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'P':  // peek
            case 'p':
                data = peek(&my_queue);
                if (data != '\0') {
                    printf("큐의 맨 앞 데이터: %c\n", data);
                }
                break;
                
            case 'F':  // is_full
            case 'f':
                printf("큐가 가득 찼나요? %s\n", is_full(&my_queue) ? "Yes" : "No");
                break;
                
            case 'E':  // is_empty
            case 'e':
                printf("큐가 비었나요? %s\n", is_empty(&my_queue) ? "Yes" : "No");
                break;
                
            case '#':  // data_count
                printf("큐에 있는 데이터 개수: %d\n", data_count(&my_queue));
                break;
                
            case 'H':  // head_position
            case 'h':
                printf("Head 위치: %d\n", head_position(&my_queue));
                break;
                
            case 'T':  // tail_position
            case 't':
                printf("Tail 위치: %d\n", tail_position(&my_queue));
                break;
                
            case '?':  // is_member
                scanf(" %c", &data);
                printf("'%c'가 큐에 있나요? %s\n", data, is_member(&my_queue, data) ? "Yes" : "No");
                break;
                
            case '=':  // replace
                scanf(" %c", &data);
                replace(&my_queue, data);
                printf("Tail 데이터를 '%c'로 교체했습니다.\n", data);
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'C':  // clear
            case 'c':
                clear(&my_queue);
                printf("큐를 비웠습니다.\n");
                break;
                
            case 'R':  // reverse
            case 'r':
                reverse(&my_queue);
                printf("큐를 뒤집었습니다.\n");
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'G':  // get_at
            case 'g':
                scanf("%d", &position);
                data = get_at(&my_queue, position);
                if (data != '\0') {
                    printf("%d번 위치의 데이터: %c\n", position, data);
                }
                break;
                
            case 'D':  // remove_at
            case 'd':
                scanf("%d", &position);
                remove_at(&my_queue, position);
                printf("%d번 위치의 데이터를 제거했습니다.\n", position);
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'I':  // insert_at
            case 'i':
                scanf(" %c %d", &data, &position);
                insert_at(&my_queue, data, position);
                printf("'%c'를 %d번 위치에 삽입했습니다.\n", data, position);
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'S':  // sort_queue
            case 's':
                sort_queue(&my_queue);
                printf("큐를 정렬했습니다.\n");
                printf("현재 큐: ");
                print(&my_queue);
                break;
                
            case 'Q':  // quit
            case 'q':
                printf("프로그램을 종료합니다.\n");
                return 0;
                
            default:
                if (cmd == 'H' || cmd == 'h' || cmd == 'E' || cmd == 'e' || cmd == 'L' || cmd == 'l' || cmd == 'P') {
                    // 이미 처리된 명령어들
                } else {
                    printf("알 수 없는 명령입니다. HELP를 입력하면 명령어 목록을 확인할 수 있습니다.\n");
                    
                    // 입력 버퍼 비우기
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                break;
        }
        
        // HELP 명령어 처리 (대소문자 모두 인식)
        if ((cmd == 'H' && getchar() == 'E' && getchar() == 'L' && getchar() == 'P') ||
            (cmd == 'h' && getchar() == 'e' && getchar() == 'l' && getchar() == 'p')) {
            show_commands();
        }
        
        printf("\n명령어를 입력하세요: ");
    }
    
    return 0;
}