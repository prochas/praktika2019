#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h>


using namespace std;

const int MAX_ENEMIES=10000;
const int MAX_LEVEL_ENEMIES=4;

struct enemy
{
    int x;
    int y;
    int dx;
    int dy;
    int gyvybes;

} enemies[MAX_ENEMIES];

const int MAX_X=50;
const int MAX_Y=20;
const int COLLISION_PAUSE=3000;
const int START_LIFE=5;
const int START_EURAI=0;

int inv;
int level=1;
int life=START_LIFE;
int eurai=START_EURAI;
int difficulty;
int greitis = 400;
int x=2;
int y=2;
int dx=0;
int dy=0;
int herojusX=5;
int herojusY=5;
int herojusDx=0;
int herojusDy=0;
int paklaidaX=2;
int paklaidaY=2;

void _sleep(int timeMs); // Po susidurimo ivyksta
void outputXY(int x, int y, char c);
void moveEnemy(); // Priesininko judejimas ( O simbolis )
void moveEnemies(); // Priesininku judejimas
void moveHero(); // Judinti savo heroju
void changeHeroDirection(char c);
void checkCollision(); //Tikrina herojaus ir prieso susidurima;
void checkCollisionEnemies();
void clearScreen(); // Isvalo ekrana;
void randomizeEnemyPosition(); // Atsitiktinai sugeneruoja priesininko pozicija
void generateEnemies();
void difficultyMenu();
void showDifficulty();
void positionXY(int x, int y);
void startScreen();
void showStatusBar();
void showGameOver();
void setStartData();
void showLevel();
void showInventor();
void showDropItems();



int main()
{

    startScreen();
    difficultyMenu();
    generateEnemies();
    showInventor();
    dy=1;
    dx=1;
    while (true)
    {
        for (int i=0; i<MAX_LEVEL_ENEMIES+level; i++)
        {
            outputXY(enemies[i].x, enemies[i].y, '&');

        }
        outputXY(x, y, 'X');
        _sleep(greitis);
        moveEnemy();
        moveEnemies();
        moveHero();
        checkCollision();
        checkCollisionEnemies();
        showStatusBar();

    }

    return 0;
}

void difficultyMenu()
{
    char c;
    difficulty=0;
    positionXY(40, 10);
    cout << "Pasirinkite norima sunkuma: " << endl;
    positionXY(45, 12);
    cout << "1. EASY" << endl;
    positionXY(45, 14);
    cout << "2. MEDIUM" << endl;
    positionXY(45, 16);
    cout << "3. HARD" << endl;

    while (difficulty==0)
    {
        c = getch();
        if (c=='1')
        {
            difficulty=1;
        }
        else if (c=='2')
        {
            difficulty=2;
        }
        else if (c=='3')
        {
            difficulty=3;
        }
    }
    showDifficulty();

}


void showDropItems()
{
    clearScreen();

    positionXY(20, 10);
    cout << "Sveikinu, jums iskrito Deimantas";

    _sleep(COLLISION_PAUSE);
    getch();

    clearScreen();



}

void showInventor()
{

    positionXY(80, 30);
    cout << "Inventorius";


}

void setStartData()
{
    // Nustato pradines zaidimo gyvybes ir taskus
    life=START_LIFE;
    eurai=START_EURAI;
    level=1;
}

void showLevel()
{
    clearScreen();

    positionXY(40, 10);
    cout << "LEVEL " << level;
    _sleep(COLLISION_PAUSE);
    getch();

    clearScreen();

}

void showGameOver()
{
    clearScreen();

    positionXY(40, 10);
    cout << "GAME OVER";
    positionXY(40, 12);
    cout << " Eurai: ";
    cout << eurai;

    getch();

    clearScreen();

    setStartData();

}

void showStatusBar()
{
    positionXY(10, 30);
    cout << "Life: ";
    cout << life;

    cout << " Eurai: ";
    cout << eurai;


}

void startScreen()
{
    positionXY(45, 10);
    cout << "SVEIKI ATVYKE";

    positionXY(41, 12);
    cout << " F L Y I N G   Z E R O " << endl;
    getch();
    clearScreen();
}

void showDifficulty()
{
    cout << "Pasirinktas lygis: ";
    switch(difficulty)
    {
    case 1:
        cout << "EASY";
        break;
    case 2:
        cout << "MEDIUM";
        break;
    case 3:
        cout << "HARD";
        break;
    }
    clearScreen();
}

void _sleep(int timeMs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(timeMs));
}

void positionXY(int x, int y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output,pos);
}

void outputXY(int x, int y, char c)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output,pos);
    cout << c;
}

void moveEnemy()
{
    outputXY(x, y, ' ' );
    x=x+dx;
    if (x>MAX_X)
    {
        x=MAX_X;
        dx=-dx;
    }

    if (x<0)
    {
        x=0;
        dx=-dx;
    }
    y=y+dy;

    if (y>MAX_Y)
    {
        y=MAX_Y;
        dy=-dy;
    }

    if (y<0)
    {
        y=0;
        dy=-dy;
    }
}
void moveEnemies()
{
    for (int i=0; i<MAX_LEVEL_ENEMIES+level; i++)
    {
        int x=enemies[i].x;
        int y=enemies[i].y;
        int dx=enemies[i].dx;
        int dy=enemies[i].dy;
        outputXY(x, y, ' ' );
        x=x+dx;
        if (x>MAX_X)
        {
            x=MAX_X;
            dx=-dx;
        }

        if (x<0)
        {
            x=0;
            dx=-dx;
        }
        y=y+dy;

        if (y>MAX_Y)
        {
            y=MAX_Y;
            dy=-dy;
        }

        if (y<0)
        {
            y=0;
            dy=-dy;
        }
        enemies[i].x=x;
        enemies[i].y=y;
        enemies[i].dx = dx;
        enemies[i].dy = dy;
    }
}


void moveHero()
{
    if (kbhit())
    {
        // Change to direction determined by key pressed
        changeHeroDirection(getch());
    }
    outputXY(herojusX, herojusY, ' ' );
    herojusX=herojusX+herojusDx;
    if (herojusX>MAX_X)
    {
        herojusX=MAX_X;
    }

    if (herojusX<0)
    {
        herojusX=0;
    }
    herojusY=herojusY+herojusDy;

    if (herojusY>MAX_Y)
    {
        herojusY=MAX_Y;
    }

    if (herojusY<0)
    {
        herojusY=0;

    }
    outputXY(herojusX, herojusY, 'O');
}

void changeHeroDirection(char key)
{
    switch (key)
    {
    case 'w':
        herojusDx=0;
        herojusDy=-1;
        break;
    case 'd':
        herojusDx=1;
        herojusDy=0;
        break;
    case 's':
        herojusDx=0;
        herojusDy=1;
        break;
    case 'a':
        herojusDx=-1;
        herojusDy=0;
        break;
    }
}

void checkCollision()
{

    if ((abs(herojusX-x) < paklaidaX) && (abs(herojusY-y) < paklaidaY))
    {
        level++;
        eurai=eurai+5;

        showInventor();
        showDropItems();
        showLevel();

        clearScreen();
        randomizeEnemyPosition();
    }


}


void clearScreen()
{
    // Clear the screen
    system("cls");
}


void randomizeEnemyPosition()
{
    x=rand() % MAX_X;
    y=rand() % MAX_Y;
}

void generateEnemies()
{
    for (int i=0; i<MAX_ENEMIES; i++)
    {
        int x=rand() % MAX_X;
        int y=rand() % MAX_Y;
        enemies[i].x = x;
        enemies[i].y = y;
        enemies[i].dx = 1;
        enemies[i].dy = 1;
    }
}

void checkCollisionEnemies()
{
    int a, b;
    for (int i=0; i<MAX_LEVEL_ENEMIES+level; i++)
    {

        a=enemies[i].x;
        b=enemies[i].y;

        if ((abs(herojusX-a) < paklaidaX) && (abs(herojusY-b) < paklaidaY))
        {
            cout << " BOOM " << endl;
            life--;
            if(life==0)
            {
                showGameOver();
            }

            _sleep(COLLISION_PAUSE);
            clearScreen();
            randomizeEnemyPosition();
        }
    }



}
