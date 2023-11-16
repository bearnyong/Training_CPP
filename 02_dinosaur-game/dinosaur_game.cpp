#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void SetConsoleView() {
    //콘솔 창의 크기와 제목을 지정하는 함수
    system("mode con : cols=100 lines=25");
    system("title Google Dinosaurs. By BlockdMask"); //clone BlockdMask
}

void GotoXY(int x, int y) {
    //커서의 위치를 x, y로 이동하는 함수
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
    //키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
    if(_kbhit() != 0) {
        return _getch();
    }
    return 0;
}

void DrawDino(int dinoY) {
    GotoXY(0, dinoY);
    static bool legFlag = true;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n");
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    
    if(legFlag) {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = false;
    }
    else {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = true;
    }
}

void DrawTree(int treeX) {
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("$$$$");
    
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf(" $$ ");

    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" $$ ");

    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $$ ");

    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf(" $$ ");
}

void DrawGameOver(const int score) {
    //충돌시 GAME OVER 그려줌
    system("cls");
    
    int x = 18;
    int y = 8;

    GotoXY(x,y);
    printf("==============================");

    GotoXY(x,y+1);
    printf("====== G A M E. O V E R ======");

    GotoXY(x,y+2);
    printf("==============================");

    GotoXY(x,y+5);
    printf("SCORE : %d", score);

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    system("pause");
}

bool isCollision(const int treeX, const int dinoY) {
    //충돌시 true, 아니면 false
    //트리의 x가 공룡의 몸체 쪽에 있을 때, 공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY(0,0);
    printf("treeX : %d, dinoY : %d", treeX, dinoY);

    if(treeX <= 8 && treeX >= 4 && dinoY > 8) {
        return true;
    }
    return false;
}

int main() {
    SetConsoleView();
    while(true) {
        //게임 루프, 게임 시작시 초기화
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        
        clock_t start, curr; //점수 변수 초기화
        start = clock(); //시작시간 초기화

        while(true) {
            //한 판에 대한 루프
            if(isCollision(treeX, dinoY)){
                //충돌체크 트리의 x값과 공룔의 y값으로 판단
                break;
            }

            if(GetKeyDown() == 'z' && isBottom) {
                //z키가 눌렸고, 바닥이 아닐 때 점프
                isJumping = true;
                isBottom = false;
            }

            if(isJumping) {
                //점프중이라면 Y를 감소, 점프가 끝났다면 Y를 증가
                dinoY -= gravity;
            } else { 
                dinoY += gravity;
            }

            if(dinoY >= DINO_BOTTOM_Y) {
                //Y가 계속해서 증가하는 걸 막기 위해 바닥을 지정
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            treeX -= 2;
            if(treeX<=0) {
                //나무가 왼쪽으로 (x음수) 가도록하고 나무의 위치가 왼쪽 끝으로 가면 다시 오른쪽 끝으로 소환
                treeX = TREE_BOTTOM_X;
            }

            if(dinoY <= 3) {
                //점프의 맨 위를 찍으면 점프가 끝난 상황
                isJumping = false;
            }

            DrawDino(dinoY); //draw dino
            DrawTree(treeX); //draw Tree

            curr = clock(); //현재 시간 받아오기
            if(((curr-start)/CLOCKS_PER_SEC)>=1) {
                //1초가 넘었을 때
                score++; //score up
                start = clock(); //시작 시간 초기화
            }

            Sleep(60);
            system("cls"); //clear

            //점수출력을?1초마다?해주는것이?아니라?항상?출력해주면서,?1초가?지났을때?++?해줍니다.
            GotoXY(22, 0); //커서를 가운데 위쪽으로 옮긴다. 콘솔창이?cols=100이니까?2*x이므로?22정도?넣어줌
            printf("Score : %d", score); //점수 출력
        }

        DrawGameOver(score); //게임 오버 메뉴
    }
    return 0;
}