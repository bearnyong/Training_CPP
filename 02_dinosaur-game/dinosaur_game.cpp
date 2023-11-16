#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void SetConsoleView() {
    //�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
    system("mode con : cols=100 lines=25");
    system("title Google Dinosaurs. By BlockdMask"); //clone BlockdMask
}

void GotoXY(int x, int y) {
    //Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
    //Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
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
    //�浹�� GAME OVER �׷���
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
    //�浹�� true, �ƴϸ� false
    //Ʈ���� x�� ������ ��ü �ʿ� ���� ��, ������ ���̰� ������� �ʴٸ� �浹�� ó��
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
        //���� ����, ���� ���۽� �ʱ�ȭ
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        
        clock_t start, curr; //���� ���� �ʱ�ȭ
        start = clock(); //���۽ð� �ʱ�ȭ

        while(true) {
            //�� �ǿ� ���� ����
            if(isCollision(treeX, dinoY)){
                //�浹üũ Ʈ���� x���� ������ y������ �Ǵ�
                break;
            }

            if(GetKeyDown() == 'z' && isBottom) {
                //zŰ�� ���Ȱ�, �ٴ��� �ƴ� �� ����
                isJumping = true;
                isBottom = false;
            }

            if(isJumping) {
                //�������̶�� Y�� ����, ������ �����ٸ� Y�� ����
                dinoY -= gravity;
            } else { 
                dinoY += gravity;
            }

            if(dinoY >= DINO_BOTTOM_Y) {
                //Y�� ����ؼ� �����ϴ� �� ���� ���� �ٴ��� ����
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            treeX -= 2;
            if(treeX<=0) {
                //������ �������� (x����) �������ϰ� ������ ��ġ�� ���� ������ ���� �ٽ� ������ ������ ��ȯ
                treeX = TREE_BOTTOM_X;
            }

            if(dinoY <= 3) {
                //������ �� ���� ������ ������ ���� ��Ȳ
                isJumping = false;
            }

            DrawDino(dinoY); //draw dino
            DrawTree(treeX); //draw Tree

            curr = clock(); //���� �ð� �޾ƿ���
            if(((curr-start)/CLOCKS_PER_SEC)>=1) {
                //1�ʰ� �Ѿ��� ��
                score++; //score up
                start = clock(); //���� �ð� �ʱ�ȭ
            }

            Sleep(60);
            system("cls"); //clear

            //���������?1�ʸ���?���ִ°���?�ƴ϶�?�׻�?������ָ鼭,?1�ʰ�?��������?++?���ݴϴ�.
            GotoXY(22, 0); //Ŀ���� ��� �������� �ű��. �ܼ�â��?cols=100�̴ϱ�?2*x�̹Ƿ�?22����?�־���
            printf("Score : %d", score); //���� ���
        }

        DrawGameOver(score); //���� ���� �޴�
    }
    return 0;
}