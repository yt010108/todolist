#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define UP 72
#define DOWN 80


#pragma pack(push, 1)
struct task {
    char deadline[20];
    char task[20];
    int Priority;
};
#pragma pack(pop)


int mainmenu()
{
    time_t t = time(NULL);
    printf("\n");
    printf("\t\t\tTO-DO LIST");
    printf("\n");
    printf("\n");
    printf("\n");
    printf(">> %s", ctime(&t));
    printf("≫ Press the arrow keys: ↑ or ↓ to navigate the options.\n");
    printf(">> Priority ranges from 1 to 3 \n");
    printf(">> Select to delete \n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t   ***********************************\n");


    return 0;
}

void addnewtask(void) {
    struct task t1;
    memset(&t1, 0, sizeof(t1));
    FILE* fp = fopen("task.bin", "a+b");//바꾸기
    mainmenu();
    printf("\t\t\tadd new task");
    printf("\n\t\t");
    printf("\n\t\t");
    printf("\n\t\tTask:");
    scanf("%s", t1.task);
    printf("\n\t\tDead line:");
    scanf("%s", t1.deadline);
    printf("\n\t\tPriority:");
    scanf("%d", &t1.Priority);
    fwrite(&t1, sizeof(t1), 1, fp);
    fclose(fp);
    printf("1");
}

int todolist() {

    struct task t1;
    memset(&t1, 0, sizeof(t1));
    FILE* fp = fopen("task.bin", "a+b");//바꾸기
    fseek(fp, 0, SEEK_SET);
    int menuNum1 = 1;
    int key;

    while (1) {
        int i = 1;
        int p = 1;//p = priority

        char tn[20];//task name
        mainmenu();
        printf("\t\t\t T A S K");
        printf("\n");
        printf("\n");

        while (1) {
            fseek(fp, 0, SEEK_SET);
            printf("\n\t    %d st", p);

            while (1) {
    
                if (fread(&t1, sizeof(t1), 1, fp) == 0)
                    break;
                
                if (p == t1.Priority)
                {
                    printf("\n\t\t");
                    if (menuNum1 == i)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
                        strcpy(tn, t1.task);
                      
                    }
                    printf("%s(%s)\n", t1.task, t1.deadline);
                    i++;
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
     
            }
            printf("\n\t\t");
            if (p == 3)break;
            p++;
            
        }


        if (menuNum1 == i)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
        printf("\n\t\tadd a new task\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("\n");
        printf("\t   ***********************************\n");
        key = _getch();
        if (key == 224) {
            key = _getch(); //224값 버림 
            fseek(fp, 0, SEEK_SET);
        }
        system("cls"); //화면 지우기 
        if (key == UP) { //위 방향키 
            if (menuNum1 > 1) { menuNum1--; }
        }
        else if (key == DOWN) { //아래 방향키
            if (menuNum1 < i) { menuNum1++; }
        } //menuNum -> 1 ~ i
        else if (key == 13) //enter
        {
            fseek(fp, 0, SEEK_SET);
            if (menuNum1 == i)//add new task
            {
                addnewtask();
                system("cls"); //화면 지우기 
            }
            else {//delete
                FILE* p1 = fopen("task.bin", "r+b");
                FILE* p2 = fopen("task.bin", "r+b");
                fseek(p1, 0, SEEK_SET);
                fseek(p2, 0, SEEK_SET);
                while (1) {
                    if (fread(&t1, sizeof(t1), 1, p1) == 0)
                        break;
                    fseek(p2, sizeof(t1), SEEK_CUR);
                    if (strcmp(tn, t1.task) == 0) {
                        fseek(p2, -44, SEEK_CUR);
                        memset(&t1, 0, sizeof(t1));
                        t1.Priority = 5;
                        fwrite(&t1, 44, 1, p2);
                        fclose(p1);
                        fclose(p2);
                        break;
                    }
                }
            }
        }

    }//end of while

}

int main() {

    todolist();

}