/*
[전반적인 설명]
주제: 연결리스트를 이용한 음악 플레이리스트 구현
기존에 제가 작성해둔 8개 ADT에 추가로 4가지의 기능을 추가하여 총 12개의 기능을 구현하였습니다. 
기능은 다음과 같습니다. 
1. addMusic - 새로운 음악 추가하는 기능 
2. playMusic - 현재 선택된 음악을 재생하는 기능
3. nextMusic : 다음 음악으로 이동하는 기능
4. pauseMusic - 현재 선택된 음악을 일시정지하는 기능
5. previousMusic - 이전 음악으로 이동하는 기능
6. sufflePlaylist - 플레이리스트 섞는 기능
7. deleteMusic - 현재 선택된 음악 삭제하는 기능
8. musicInfo - 현재 선택된 음악 정보 출력하는 기능
9. countMusic - 현재 플레이리스트 곡 개수 출력하는 기능
10. searchMusic - 제목으로 노래 검색하는 기능
11. showCommand - 사용 가능한 명령어와 단축키 목록 출력하는 기능
12. quitPorgram - 프로그램 종료하는 기능 
*/


#include <stdio.h> //prinf() 입력을 위해서
#include <stdlib.h> //malloc(),free() 같은 메모리 관련 함수 쓰기 위해서 추가함.
#include <string.h> // strcpy() 같은 문자열 처리 함수 쓸려고 추가함.
#include <time.h> // shuffle 기능을 추가할 때 rand(), srand() 함수 넣으려고 추가함.


// 먼저 Music 구조체를 정의해줌.
typedef struct Music { //구조체 타입 이름을 'Music'으로 간단히 사용하기 위해 typedef를 선언했습니다.
    //넉넉한 공간으로 문자 배열 만들기 위해 100으로 설정했습니다.
    char title[100]; // 노래 제목
    char artist[100]; // 가수 이름
    char album[100]; // 앨범 이름
    char releaseDate[20]; // 발매일

    struct Music* next; // 다음 노드를 가리키는 포인터 변수 'next' 선언
    struct Music* prev; // 이전 노드를 가리키는 포인터 변수 'prev' 선언
} Music;

/*
addMusic (새로운 노래를 리스트에 추가하는 함수) 기능을 먼저 구현해보려고 합니다.
*/

//title,artist,album,releaseDate 정보를 받아 position 위치에 새 노래노드를 만들고, 그 다음 이걸 연결 리스트에 끼워 넣고, 새로운 head 포인터를 반환하는 함수를 만들었습니다.
Music* addMusic(Music* head, const char* title, const char* artist, const char* album, const char* releaseDate, int position) {
    // malloc()으로 새로운 Music 노드 생성.
    Music* newMusic = (Music*)malloc(sizeof(Music));
    //메모리 부족한 경우 (NULL), 오류 체크 후 기존 head 그대로 반환.
    if (newMusic == NULL) {
        printf("메모리 할당 실패!\n");
        return head;
    }

    // 입력받은 문자열들을 각각 구조체에 복사사
    strcpy(newMusic->title, title);
    strcpy(newMusic->artist, artist);
    strcpy(newMusic->album, album);
    strcpy(newMusic->releaseDate, releaseDate);
    //연결 아직 안했으니까 next,prev는 NULL로 초기화.
    newMusic->next = NULL;
    newMusic->prev = NULL;

    // head가 NULL이면 현재 리스트가 비어있다는 뜻이니까 무조건 맨앞임. 맨 앞 삽입시 기존 head의 prev을 newMusic으로 연결. 마지막으로 새노드가 head가 되므로 그걸 반환.
    if (position == 0 || head == NULL) {
        newMusic->next = head;
        if (head != NULL) {
            head->prev = newMusic;
        }
        return newMusic; // 새로운 head
    }

    // current 포인터로 리스트를 따라가며 원하는 위치까지 이동. position-1 까지 가는 이유는 그 다음에 새 노드를 넣기 위해서.
    Music* current = head;
    int i = 0;
    while (current != NULL && i < position - 1) {
        current = current->next;
        i++;
    }

    // 리스트 끝보다 뒤라 범위를 벗어난 경우 안내문 출력되게 함. 
    if (current == NULL) {
        printf("삽입하려는 위치가 리스트 범위를 벗어났습니다.\n");
        free(newMusic); // 메모리 누수 방지
        return head;
    }

    // 중간 또는 끝에 삽입
    newMusic->next = current->next;
    newMusic->prev = current;

    if (current->next != NULL) {
        current->next->prev = newMusic;
    }
    current->next = newMusic;

    return head; // 변경된 head 반환
}


// 마지막으로, 메모리 누수 없이 프로그램 종료하게 끔 전체 노드를 메모리 해제하는 함수 작성함.
void freePlaylist(Music* head) {
    Music* current = head;
    while (current != NULL) {
        Music* temp = current;
        current = current->next;
        free(temp);
    }
}

/*
playMusic 기능 추가. 
- 현재 재생 중인 노래 (currentSong)을 받아서, 화면에 '지금 재생하고 있는 노래' 정보를 출력하는 기능을 만들어보았습니다.
-진짜 음악재생기능을을 구현하기는 현실적으로 어려울 것 같아. 그냥 현재 재생중인 노래 정보를 메시지 형태로 보여주는 정도로만만 기능을 구현해보았습니다.
*/
void playMusic(Music* currentSong){
    if (currentSong == NULL){
        printf("재생할 노래가 없습니다\n");
        return;
    }
    printf("\n현재 재생 중: %s - %s\n",currentSong->artist, currentSong->title);
}

/*
pauseMusic 기능 추가. 
-진짜 일시정지를 구현하기는 현실적으로 어려울 것 같아. 그냥 '일시정지했다'는 메시지만 보여주는 정도로 기능을 구현해보았습니다.
*/
void pauseMusic(Music* currentSong) {
    if (currentSong == NULL) {
        printf("일시정지할 노래가 없습니다\n");
        return;
    }
    printf("\n노래 일시정지: %s - %s\n", currentSong->artist, currentSong->title);
}

/*
nextMusic (현재 재생중인 노래에서 몇곡 뒤로 이동하는 기능)을 구현해보았습니다.
-지금 듣고 있는 노래 기준으로 (currentSong)
사용자가 입력한 숫자 (count)만큼 다음곡으로 이동하는 기능입니다. 
*/

//
Music* nextMusic(Music* currentSong, int count){
    //먼저, 현재 재생중인 노래가 없는 경우 설정.
    if (currentSong ==NULL){
        printf("다음으로 이동할 노래가 없습니다.\n");
        return NULL;
    }

    //사용자가 지정한 count만큼 이동을 시도하고, 현재 노래의 다음노래가 존재하지 않는다면 (마지막 곡), '마지막 노래라서 이동 못합니다'와 같은 메시지 뜨게 함.
    for (int i =0; i< count; i++){
        if (currentSong->next != NULL){
            currentSong = currentSong->next;
        } else{
            printf("마지막 노래입니다. 더 이상 이동할 수 없습니다.\n");
            break;
        }
    }
    printf("\n현재 선택된 노래: %s - %s\n",currentSong->artist,currentSong->title);
    return currentSong; 
    //nextMusic은 이동 후 currentSong을 return 해서 업데이트해줘야 함.
}

/*
previousMusic (현재 듣고 있는 노래에서 몇곡 전으로 (previous) 이동하는 기능)을 추가했습니다. 
-이것도 사용자가 입력한 count값에 맞게 이동하도록 구성했습니다.
*/
Music* previousMusic(Music* currentSong, int count) {
    //현재 재생중인 노래가 없는 경우 설정.
    if (currentSong == NULL) {
        printf("이전으로 이동할 노래가 없습니다.\n");
        return NULL;
    }

    for (int i = 0; i < count; i++) {

        // count만큼 이동하는 함수. 만약 맨앞까지 가면 안내문 출력되도록 설정했음.
        if (currentSong->prev != NULL) {
            currentSong = currentSong->prev;
        } else {
            printf("처음 노래입니다. 더 이상 이동할 수 없습니다.\n");
            break;
        }
    }
    printf("\n현재 선택된 노래: %s - %s\n", currentSong->artist, currentSong->title);
    return currentSong;
}

/*
shufflePlaylist (플레이리스트에 있는 모든 노래를 랜덤하게 섞어주는 기능) 를 추가해보았습니다. 
*/
void shufflePlaylist(Music** head) {
    //시작하기 앞서, 만약 노래가 하나도 없다면 '섞을 노래가 없습니다'라는 문구 출력 후 함수 바로 종료되게 설정.
    if (*head == NULL) {
        printf("섞을 노래가 없습니다.\n");
        return;
    }

    // 노래들을 node[] 배열에 순서대로 하나씩 저장.
    // 비교적 간단히 구현하기 위해 동적배열 사용하지 않고 그냥 최대 100곡으로 제한하여 구현해봤습니다.

    Music* nodes[100]; 
    int count = 0;
    Music* current = *head;
    while (current != NULL && count < 100) {
        nodes[count++] = current;
        current = current->next;
    }

    /*
    rand()로 무작위로 번호 뽑아서 i번째와 j번째를 교환하려고함. -> 전체 노래 순서가 완전히 랜덤하게 섞임. 
    */ 
    srand(time(NULL)); // 이걸 통해 매번 실행할때마다 다른 결과가 나오게 해줌.
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // i번째와 j번째 swap
        Music* temp = nodes[i];
        nodes[i] = nodes[j];
        nodes[j] = temp;
    }

    // 섞은 순서대로 '노래1->노래2>노래3->...' 형태로 다시 연결하려고 함. 그래서 서로 next와 prev 연결 다시 해주기.
    for (int i = 0; i < count - 1; i++) {
        nodes[i]->next = nodes[i + 1];
        nodes[i + 1]->prev = nodes[i];
    }
    nodes[count - 1]->next = NULL; // 마지막 노래는 NULL로 설정
    nodes[0]->prev = NULL; //첫 번째 노래는 NULL로 설정정

    *head = nodes[0]; // 리스트의 새로운 시작은 섞인 첫 번쨰 노래로 설정.

    printf("플레이리스트가 섞였습니다!\n");
}

/*deleteMusic (현재 재생중인 노래 삭제하는 기능) 구현
1. 현재 재생 중인 함수 (currentSong)을 삭제하려고 해. 
2. 삭제 후에는 가능하다면 다음 노래로 넘어가려고 함. 
3. 만약 노래가 없으면, 이전 노래로 넘어감. 
4. 만약 둘 다 없으면 (플레이리스트가 완전히 비게 되면) currentSong을 NULL로 만듦.
*/
Music* deleteMusic(Music** head, Music* currentSong) {
    // 삭제할 노래가 없다면 그냥 안내메시지 출력하고 NULL 반환.
    if (currentSong == NULL) {
        printf("삭제할 노래가 없습니다.\n");
        return NULL;
    }

    // 삭제한 뒤, 어디로 넘어갈지 저장할 포인터(nextSong) 준비비
    Music* nextSong = NULL;

    // 삭제할 노래의 앞 노래와 뒤 노래를 연결 끊고 다시 이어주기.
    if (currentSong->prev != NULL) {
        currentSong->prev->next = currentSong->next;
    } else {
        // 현재 노래가 첫 번째 노래(head)였다면, head를 현재 노래의 다음노래로 업데이트 해줌. 
        *head = currentSong->next;
    }
//삭제한 뒤에도 플레이리스트가 끊기지 않게 연결.
    if (currentSong->next != NULL) {
        currentSong->next->prev = currentSong->prev;
        nextSong = currentSong->next;
    } else if (currentSong->prev != NULL) {
        nextSong = currentSong->prev;
    }

    printf("\n삭제한 노래: %s - %s\n", currentSong->artist, currentSong->title);
    free(currentSong);

    return nextSong; //삭제가 끝난 뒤, 다음에 재생할 노래를 반환해서 currentSong 포인터 업데이트할 수 있게끔 구성.
}

// musicInfo(currentSong) 기능 구현
/*
단축키를 누르면 현재 선택한 노래의 정보 (가수, 노래 제목, 앨범, 발매일 전부 보기)를 자세히 출력하려고 함. 
*/
void musicInfo(Music* currentSong) {
    //현재 노래가 없을 경우 안내문 출력 후 종료.
    if (currentSong == NULL) {
        printf("현재 선택된 노래가 없습니다.\n");
        return;
    }
    //노래 있으면, 현재 선택된 노래 정보 출력.
    printf("\n--- 현재 선택된 노래 정보 ---\n");
    printf("노래 제목: %s\n", currentSong->title);
    printf("가수: %s\n", currentSong->artist);
    printf("앨범: %s\n", currentSong->album);
    printf("발매일: %s\n", currentSong->releaseDate);
    printf("---------------------------------\n");
    // 구분선 넣어서 좀 깔끔하게 출력되게끔 했음.
}

/*
-countMusic(playlist) (플레이리스트에 현재 노래가 몇 곡 있는지 세는 기능) 구현.
-head부터 쭉 따라가면서 노드를 하나씩 세기만 하면 됨. 
*/
int countMusic(Music* head) {
    //노래 수를 세는 변수를 0으로 초기화.
    int count = 0;

    //현재 노래 포인터(current)를 head (맨 처음 노래)로 설정.
    Music* current = head;

    //노래가 끝날때까지 하나하나 넘어가면서 반복.
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//searchMusic (노래 제목이나 가수 이름에 특정 단어가 포함된 노래를 찾아 출력하는 함수) 구현
/*
1. strstr() 함수 써서 제목이나 가수 이름 안에 keyword가 포함돼 있는지 찾으려고 함. 
2. 없으면 '못 찾았습니다' 출력되도록 함.
*/
void searchMusic(Music* head, const char* keyword) {
    //플레이리스트가 비어있으면, 검색할 노래없으니까 바로 종료.
    if (head == NULL) {
        printf("검색할 노래가 없습니다.\n");
        return;
    }

    int found = 0;
    Music* current = head;
    //리스트의 끝(NULL) 나올 때까지 반복해서 모든 노래 확인
    while (current != NULL) {
        //현재 노래의 제목이나 가수 이름 안에 입력한 keyword가 포함되어있으면 그 노래 정보를 출력하고 found=1 로 표시 (찾았다는 뜻.)
        if (strstr(current->title, keyword) != NULL || strstr(current->artist, keyword) != NULL) {
            printf("\n[검색 결과]\n");
            printf("노래 제목: %s\n", current->title);
            printf("가수: %s\n", current->artist);
            printf("앨범: %s\n", current->album);
            printf("발매일: %s\n", current->releaseDate);
            found = 1;
        }
        //다음 노래로 넘어가게 함.
        current = current->next;
    }

    // 검색을 다 돌았는데 found=0이면 못찾았다는 메시지 출력.
    if (!found) {
        printf("'%s'와 일치하는 노래를 찾을 수 없습니다.\n", keyword);
    }
}

//showCommands(사용 가능한 모든 명령어와 기능을 사용자에게 보여주는 기능) 구현. 
void showCommands() {
    printf("\n--- 명령어 목록 ---\n");
    printf("a: 노래 추가\n");
    printf("p: 현재 노래 재생\n");
    printf("s: 현재 노래 일시정지\n");
    printf("n: 다음 노래로 이동\n");
    printf("b: 이전 노래로 이동\n");
    printf("x: 플레이리스트 셔플\n");
    printf("d: 현재 노래 삭제\n");
    printf("i: 현재 노래 정보 보기\n");
    printf("c: 플레이리스트에 있는 노래 수 세기\n");
    printf("f: 노래 검색하기\n");
    printf("m: 명령어 목록 보기\n");
    printf("q: 프로그램 종료\n");
    printf("--------------------\n"); //가독성위에 표시선 한줄 추가했음.
}


int main() {
    /* 먼저, 노래를 저장할 공간을 새로 만듭니다.
   이를 위해 각 노래를 만들 때 
   'Music*newMusic = (Music*)malloc(sizeof(Music));' 를 사용하려 합니다.
   또한, 그 공간이 제대로 만들어졌는지 확인하는 구문을 사용함으로써 메모리 할당 실패했을 때 프로그램을 안전하게 끝내게끔 했습니다.
   이를 위해 각 노래를 만드는 코드에 NULL문을 추가적으로 넣으려고 합니다.
   */

// 기본 노래 3개를 만드려고 합니다.


   // 첫 번째 노래 만들기
   Music*song1 = (Music*)malloc(sizeof(Music));
   if (song1==NULL){printf("메모리 할당 실패!\n");
    return 1;} //이 경우는 에러가 발생한 상황에 비정상 종료를 하는 상황이므로 'return 1'을 사용하여 비정상 종료

    /*song1이 가리키는 구조체 안에 title,artist,album,releaseDate라는 공간에 필요한 문자열을 삽입하는 코드를 만들어봤습니다.
    이를 위해 문자열을 한 글자씩 복사해주는 함수인 'strcpy()' 함수를 사용해봤습니다 */

    strcpy(song1->title,"Dynamite");
    strcpy(song1->artist,"BTS");
    strcpy(song1->album,"BE");
    strcpy(song1->releaseDate,"2020-08-21");

    // 이때 song1은 아직 연결된 다른 노드가 없기 때문에 next와 prev를 null로 설정해줍니다.
    song1->next = NULL;
    song1->prev = NULL;

    // 두 번째 노래 만들기 (첫 번째와 방식 동일)
   Music*song2 = (Music*)malloc(sizeof(Music));
   if (song2==NULL){printf("메모리 할당 실패!\n");
    return 1;}

    strcpy(song2->title,"Butter");
    strcpy(song2->artist,"BTS");
    strcpy(song2->album,"Butter (Single)");
    strcpy(song2->releaseDate,"2021-05-21");
    song2->next = NULL;
    song2->prev = NULL;

    // 세 번째 노래 만들기 (첫 번째와 방식 동일)
   Music*song3 = (Music*)malloc(sizeof(Music));
   if (song3==NULL){printf("메모리 할당 실패!\n");
    return 1;}

    strcpy(song3->title,"Permission to Dance");
    strcpy(song3->artist,"BTS");
    strcpy(song3->album,"Butter (Single)");
    strcpy(song3->releaseDate,"2021-07-09");
    song3->next = NULL;
    song3->prev = NULL;

// 노래 연결
song1->next = song2;
song2->prev = song1;
song2->next = song3;
song3->prev = song2;

//head 설정
Music* head = song1;


//현재 선택된 노래를 head로 초기화, 이후 playMusic, nextMusic,deleteMusic 등을 구현하려면 현재 재생 중인 노래를 가리키는 포인터가 필요함.
Music* currentSong = head;

 // 이제 지금까지 작성한 코드를 바탕으로 사용자가 입력하는 명령어에 따라 그에 맞는 결과가 출력하도록 하는 출력문들 작성.
 char command;
 while (1) {
     printf("\n명령어를 입력하세요: ");
     scanf(" %c", &command);

     if (command == 'a') {
         int position;
         char title[100], artist[100], album[100], releaseDate[20];

         printf("추가할 위치를 입력하세요: ");
         scanf("%d", &position);
         getchar(); // 숫자 입력 후 엔터 제거

         printf("노래 제목: ");
         scanf("%[^\n]", title);
         getchar();

         printf("가수 이름: ");
         scanf("%[^\n]", artist);
         getchar();

         printf("앨범 이름: ");
         scanf("%[^\n]", album);
         getchar();

         printf("발매일 (YYYY-MM-DD): ");
         scanf("%[^\n]", releaseDate);
         getchar();

         Music* newSong = (Music*)malloc(sizeof(Music));
         if (newSong == NULL) {
             printf("메모리 할당 실패!\n");
             break;
         }
         strcpy(newSong->title, title);
         strcpy(newSong->artist, artist);
         strcpy(newSong->album, album);
         strcpy(newSong->releaseDate, releaseDate);
         newSong->next = NULL;
         newSong->prev = NULL;

         head = addMusic(head, title, artist, album, releaseDate, position); 



         // 추가 후 플레이리스트 출력
         printf("\n---- 플레이리스트 ----\n\n");
         Music* current = head;
         while (current != NULL) {
             printf("노래 제목: %s\n", current->title);
             printf("가수: %s\n", current->artist);
             printf("앨범: %s\n", current->album);
             printf("발매일: %s\n\n", current->releaseDate);
             current = current->next;
         }   

     } else if (command == 'p'){
        playMusic(currentSong);
     } else if (command == 's'){
        pauseMusic(currentSong);
     } else if (command == 'n') {
        int count;
        printf("몇 곡 이동할까요? (기본 1곡): ");
        if (scanf("%d",&count) !=1) {
            count = 1; // 입력 실패하면 1로 기본 설정.
            while (getchar() != '\n'); //입력 버퍼 비우기
        } 
        currentSong = nextMusic(currentSong, count); 
    } 

    else if (command == 'b') { // b = back
        int count;
        printf("몇 곡 뒤로 갈까요? (기본 1곡): ");
        if (scanf("%d", &count) != 1) {
            count = 1;
            while (getchar() != '\n');
        }
        currentSong = previousMusic(currentSong, count);
    }
    else if (command == 'x') { // x = shuffle
        shufflePlaylist(&head);
        currentSong = head; // shuffle 후 첫 곡으로 이동

        printf("현재 선택한 노래: %s - %s\n", currentSong->artist,currentSong->title);
        //shuffle 후 첫 곡으로 이동했다는 사실을 알려주는게 편할 것 같아서 작성해봤습니다.
    }
//deleteMusic 관련된 명령어 등록
    else if (command == 'd') {
        currentSong = deleteMusic(&head, currentSong);
    }

    //musicInfo(currentSong)의 단축키 등록.
    else if (command == 'i') { // i = info
        musicInfo(currentSong);
    }
    //countMusic의 단축키 등록.
    else if (command == 'c') {
        int total = countMusic(head);
        printf("\n현재 플레이리스트에는 %d곡이 있습니다.\n", total);
    }

    //searchMusic의 단축키 등록
    else if (command == 'f') {
        char keyword[100];
        printf("검색할 키워드를 입력하세요: ");
        scanf(" %[^\n]", keyword);
        getchar();
        searchMusic(head, keyword);
    }

    //showCommands의 단축키 등록
    else if (command == 'm') {
        showCommands();
    }
    
    else if (command == 'q') {
         printf("\n프로그램을 종료합니다.\n");
         break;
     } else {
         printf("잘못된 입력입니다. 다시 입력하세요.\n");
     }
 }

 // 프로그램 종료 시 메모리 해제
 freePlaylist(head);
 return 0;
}