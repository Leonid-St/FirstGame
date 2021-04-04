#include <iostream>
#include <conio.h>
#include <random>
#include <time.h>
#include <ctime>
using namespace std;
struct snakePart {
    int x, y;
    snakePart* next;
    snakePart* prev;
};
class enemy {
public:
    int x, y;
    enemy* next;
    enemy* prev;
};
class kill {
public:
    int x, y;
    kill* next;
    kill *prev;
};

void printField(char** field, int fieldHeight, int fieldWidth) {
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            cout << field[i][j];
        }
        cout << endl;
    }
}
void clearField(char** field, int fieldHeight, int fieldWidth) {
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            if ((i == 0) or (j == fieldWidth - 1) or (j == 0) or (i == fieldHeight - 1)) { field[i][j] = '*'; }
            else { field[i][j] = ' '; }
        }
    }
}
int main(){
    srand(time(0));
    int fieldWidth, fieldHeight; 
    int numEnemy;
    int finall;
    setlocale(LC_ALL, "Russian");
   /* cout << "Введите ширину поля:";
    cin >> fieldWidth;
    cout << "Введите высоту поля:";
    cin >> fieldHeight;*/
    do {
        system("cls");
        cout << "Введите ширину поля: "; cin >> fieldWidth;
        cout << "Введите высоту поля: "; cin >> fieldHeight;
        cout << "Введите колво миньенов "; cin >> numEnemy;
        cout << "Введите кол во kill для win"; cin >> finall;
        //cout << "ВВедите количесво врагов:"; cin >> numEnemy;
    } while ((fieldWidth <= 2) or (fieldHeight <= 2));
       
    char** field = new char* [fieldHeight];
    //creating field
    for (int i = 0; i < fieldHeight; i++) {
        field[i] = new char[fieldWidth];
    }
    //field of zero
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            field[i][j] = ' ';
        }
        //cout field
        }
    for (int i = 0; i < fieldHeight; i++) {
        for (int j = 0; j < fieldWidth; j++) {
            cout << field[i][j];
        }
        cout << endl;
    }
    //инициализация 
    snakePart snake;
    snakePart* head=&snake;
    enemy enemy1;
    enemy* enemyH = &enemy1;
    enemy *enemyG =new enemy[numEnemy]; 
    enemy* enemyGG = enemyG;
    kill kil;
    kill* pkil = &kil;
   // enemy* enemyG= new enemy[numEnemy];
   
    // ставим голову змейки  в случайную точку поля 
    for (int i = 0; i < numEnemy; i++) {
        enemyG[i].x= rand() % fieldWidth;
        enemyG[i].y = rand() % fieldHeight;
    }
    enemy1.x = rand() % fieldWidth;
    enemy1.y = rand() % fieldHeight;
    snake.x = rand() % fieldWidth;
    snake.y = rand() % fieldHeight;
    kil.x = rand() % fieldWidth;
    kil.y = rand() % fieldHeight;
    int iterator=0;
   int CurrentLenght = 0;
   enemy1.next = NULL;
   enemy1.prev = NULL;
    snake.next = NULL;
    snake.prev = NULL;
    kil.next = NULL;
    kil.prev = NULL;
    bool alive =true;
    bool aliveEnemy1 = true;
    char symbol;//from kayboard;
    int k = 0; bool determ = false;
    while (alive) {
        symbol = _getch();
        if ((symbol == 'w') or (symbol == 'W')) {
            snake.y -= 2;
            if (snake.y < 0) { snake.y = fieldHeight - 1; }
        }
        if ((symbol == 's') or (symbol =='S')) {
            snake.y = (snake.y + 2) % fieldHeight; 
        }
        if ((symbol == 'a') or (symbol == 'A')) {
            snake.x -= 2;
            if (snake.x < 0) { snake.x = fieldWidth - 1; }
        
        }
        if ((symbol == 'd') or (symbol == 'D')) {
            snake.x = (snake.x + 2) % fieldWidth;
           // snake.x += 1; if (snake.x < 0) { snake.x = fieldWidth - 1; }
        }
        if (enemy1.x > snake.x) { enemy1.x -= 1; }
        if (enemy1.y > snake.y) { enemy1.y -= 1; }
        if (enemy1.x < snake.x) { enemy1.x += 1; }
        if (enemy1.y < snake.y) { enemy1.y += 1; }
        if (((kil.x+1 == snake.x) and (kil.y == snake.y))or ((kil.x == snake.x) and (kil.y + 1 == snake.y))or
            ((kil.x + 1 == snake.x) and (kil.y + 1 == snake.y)) or ((kil.x == snake.x) and (kil.y == snake.y))) {
            k++;
            system("cls");
            clearField(field, fieldHeight, fieldWidth);
            kil.x = rand() % fieldWidth;
            kil.y = rand() % fieldHeight;
        }
      
        if (k == finall) {
            alive = false; aliveEnemy1 = false;
        }
        //GG
        for (int i = 0; i < numEnemy; i++) {
            if ((enemyG[i].x > snake.x)) { enemyG[i].x -= 1; }
           
            if (enemyG[i].y > snake.y) { enemyG[i].y -= 1; }
           
            if (enemyG[i].x < snake.x) { enemyG[i].x += 1; }
          
            if (enemyG[i].y < snake.y) { enemyG[i].y += 1; }
            for (int j = 0; j < i;  j++) {
                if (((enemyG[j].y == enemyG[i].y) and (enemyG[j].x == enemyG[i].x))or
                    ((enemy1.x==enemyG[i].x)and(enemy1.y==enemyG[i].y))) {
                    enemyG[i].y = rand() % fieldHeight;
                    enemyG[i].x = rand() % fieldWidth;
                }
            }
        }
        snakePart* snakeCurrent = head;
        enemy* enemyCurrent = enemyH;
        enemy* enemyCurrentG = enemyGG;
        kill* kilCurrent = pkil;
        CurrentLenght = 0;
        if ((enemy1.x == snake.x) and (enemy1.y == snake.y)) { alive = false;}
        for (int i = 0; i < numEnemy; i++) {
            if ((enemyG[i].x == snake.x) and (enemyG[i].y == snake.y)) { alive = false; }
        }
        clearField(field, fieldHeight, fieldWidth);
        while (snakeCurrent != NULL) {
           /* if (CurrentLenght == 0) { field[snakeCurrent->y][snakeCurrent->x] = 'O'; }
            else { field[snakeCurrent->y][snakeCurrent->x] = '@'; }
                CurrentLenght++;
                snakeCurrent = snakeCurrent->next; */
            field[kilCurrent->y][kilCurrent->x] = '$';
            field[kilCurrent->y+1][kilCurrent->x] = '$';
            field[kilCurrent->y][kilCurrent->x+1] = '$';
            field[kilCurrent->y+1][kilCurrent->x+1] = '$';
            field[snakeCurrent->y][snakeCurrent->x] = '@';
            field[enemyCurrent->y][enemyCurrent->x] = 'K';
            for (int i = 0; i < numEnemy; i++) {
                field[(enemyCurrentG + i)->y][(enemyCurrentG + i)->x] = 'm';
            } 
          
             //(*a).b a->b
            snakeCurrent = snakeCurrent->next;
            enemyCurrent = enemyCurrent->next;
           // kilCurrent = kilCurrent->next;
            
        }
        system("cls");// cout << symbol;
        printField(field, fieldHeight, fieldWidth);
        cout << "ход: " << iterator << "при кол-ве врагов: " << numEnemy <<" ,kill:= "<<k<< endl;
        iterator++;

    }
   
   // cout << "YOU DEAD!";
    if ((aliveEnemy1 == false)and(alive==false)) {
        system("cls");
        cout << "ход: " << iterator << "при кол-ве миньенов : " << numEnemy << " ,kill:= " << k << endl; cout << endl; cout << endl;
        cout << "!!!YOU WIN!!!" << endl; cout << endl; cout << endl;
        system("pause");
    }
    else if((alive==false)and(aliveEnemy1==true)){
      //  cout << "ход: " << iterator << "при кол-ве  миньенов: " << numEnemy << " ,kill:= " << k << endl;
        cout << endl; cout << endl;
        cout << "!!!YOU DEAD!!!";
        cout << endl; cout << endl;
        system("pause");
    }
    return 0;
}

