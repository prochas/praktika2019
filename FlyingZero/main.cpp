#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <windows.h>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

const int MAX_ENEMIES=10000;
const int MAX_LEVEL_ENEMIES=4;
const int MAX_X=50;
const int MAX_Y=20;
const int MAX_PLAYERS=10000;
const int COLLISION_PAUSE=3000;
const int START_LIFE=5;
const int START_EURAI=0;

struct zaidejas
{
    string vardas;
    int eurai;

} zaidejai[MAX_PLAYERS];


struct enemy
{
    int x;
    int y;
    int dx;
    int dy;
    int gyvybes;

} enemies[MAX_ENEMIES];


//Inventorius
int deimantai=0;
int sarvai=0;
int selling;

int town=1;
int maxZaidejai=0;
string vardas;
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
void getAndShowItem();
void startGame();
void saveScore();
void enterName();
void loadScores();
void showTop10Scores();
void showOtherSkin();
void HTML();
void itemSelling();
void pasiekimuLentele();
void anotherStartData();
void zemelapis();


int main()
{
    enterName();
    startGame();

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
        //showOtherSkin();
        checkCollision();
        checkCollisionEnemies();
        showStatusBar();
    }
    return 0;
}

void enterName()
{
    clearScreen();

    positionXY(20, 10);
    cout << "Iveskite savo varda: ";
    cin >> vardas;

    clearScreen();

}


bool compare(zaidejas a, zaidejas b)
{
    //https://www.includehelp.com/cpp-programs/sorting-a-structure-in-cpp.aspx
    if(a.eurai < b.eurai)
        return 0;
    else
        return 1;
}


void showTop10Scores()
{
    clearScreen();

    sort(zaidejai,zaidejai+maxZaidejai, compare);

    positionXY(40, 10);
    cout << "TOP 10 SCORES ";

    for (int i=0; i<10; i++)
    {
        positionXY(38, 12+i);
        if (zaidejai[i].vardas.length()>0)
        {
            cout << zaidejai[i].vardas << " "<< zaidejai[i].eurai << endl;
        }

    }
    _sleep(COLLISION_PAUSE);
    getch();

    clearScreen();
}

void HTML()
{
    std::string line;

    std::string s1, s2, s3, s4;
    int count = 0;

    std::string sorted[100][4];

    std::ofstream File("output.html");


    std::ifstream Out("scores.txt");

    if (File.is_open() && Out.is_open())
    {
        File << "<!DOCTYPE html> \n <html> \n <head> \n <link rel = \"stylesheet\" type = \"text/css\" href = \"output.css\"> \n</head>\n";
        File << "<body> \n <h1 align=\"center\" style=\"color:black\">SCOREBOARD</h2> \n <table style=\"width:1000px\" align=\"center\"> \n <tr>\n";
        File << "<tr> \n <th>Player name</th> \n <th>EURAI</th> \n <th>PLAYER NAME</th> \n <th>Enemies killed</th> \n </tr>\n";


        while (Out >> s1 >> s2 >> s3 >> s4)
        {


            File << "<tr>\n";
            File << "<td> "<< s1 << "</td>\n";
            File << "<td>" << s2 << "</td>\n";
            File << "<td>" << s3 << "</td>\n";
            File << "<td>" << s4 << "</td>\n";
            File << "</tr>\n";

        }

        File << "</table> \n </h1> \n </body> \n </html> \n ";

        File.close();
    }
    else
        std::cout << "Unable to open file";
}

void saveScore()
{
    ofstream scores;
    scores.open("scores.txt", ios::app);

    scores << vardas << " ";
    scores << eurai << endl;

    scores.close();
}

void loadScores()
{
    string temp_vardas;
    int temp_eurai;
    ifstream scores ("scores.txt");
    if (scores.is_open())
    {
        maxZaidejai=0;
        while (scores >> temp_vardas >> temp_eurai)
        {
            //cout << temp_vardas << " " << temp_eurai << endl;
            zaidejai[maxZaidejai].eurai = temp_eurai;
            zaidejai[maxZaidejai].vardas = temp_vardas;

            maxZaidejai++;
        }
        scores.close();
    }

    else
        cout << "Unable to open file";
}


void startGame()
{
    startScreen();
    setStartData();
    loadScores();
    showTop10Scores();
    difficultyMenu();
    generateEnemies();
    showInventor();
    dy=1;
    dx=1;
}

void zemelapis()
{
    if(town==1)
    {
        ifstream fd("1.txt");
        char eil;
        while(!fd.eof())
        {
            fd.get(eil);
            if(eil=='n')
                cout<<endl;
            else
                cout<<eil;

        }
        fd.close();
    }
}


void pasiekimuLentele()
{
    clearScreen();

    positionXY(60, 10);
    cout << "PASIEKIMU LENTELE" << endl;

    cout << "1 LEVEL. Gaunate papildomus 2 sarvus " << endl;
    cout << "2 LEVEL. Gaunate papildomus  2 pinigus " << endl;
    cout << "3 LEVEL. Gaunate papildomus 2 deimantus " << endl;
    cout << "4 LEVEL. Gaunate papildomus 4 sarvus " << endl;
    cout << "5 LEVEL. Gaunate papildomus 4 pinigus " << endl;
    cout << "6 LEVEL. Gaunate papildomus 4deimantus " << endl;

    _sleep(COLLISION_PAUSE);
    getch();
    clearScreen();

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

void showOtherSkin()
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
    outputXY(herojusX, herojusY, 'W');
}


void getAndShowItem()
{
    clearScreen();

    positionXY(20, 10);

    cout << "Sveikinu, jus pasiemete ";

    int i;
    i=rand() % 10;

    if (i<5)
    {
        deimantai++;
        cout << "deimanta";
    }
    else
    {
        sarvai++;
        cout << "sarvus";
    }



    _sleep(COLLISION_PAUSE);
    getch();

    clearScreen();



}

void showInventor()
{
    clearScreen();

    positionXY(40, 10);
    cout << "Inventorius";

    positionXY(40, 12);
    cout << "Jus turite: " <<  deimantai << " deimantu";

    positionXY(52, 14);
    cout << sarvai << " sarvu";

    _sleep(COLLISION_PAUSE);
    getch();

    clearScreen();

}


void itemSelling()
{
    clearScreen();

    positionXY(20, 10);
    cout << "Ar norite parduoti turimus daiktus?";
    cin >> selling;

    if (selling==1)
    {

        positionXY(20, 12);
        cout << "Sveikinu, daiktai sekmingai parduoti";

        positionXY(20, 14);
        cout << "Uz tai gaunate papildomus eurus";
        eurai=eurai+2;

        _sleep(COLLISION_PAUSE);
        getch();
        clearScreen();

        deimantai=0;
        sarvai=0;
    }
    else if (selling==0)
    {
        positionXY(20, 14);
        cout << "Pardavimas atsauktas";
        _sleep(COLLISION_PAUSE);
        getch();

        clearScreen();
    }

}

void setStartData()
{
    // Nustato pradines zaidimo gyvybes ir taskus
    life=START_LIFE;
    eurai=START_EURAI;
    level=1;
    deimantai=0;
    sarvai=0;
}

void anotherStartData()
{
    if (level==1)
    {
        cout << "Sveikinu gavote papildomus sarvus" << endl;
        sarvai=sarvai+2;
    }
    else if (level==2)
    {
        cout << "Sveikinu gavot eurus" << endl;
        eurai=eurai+2;
    }
    else if (level==3)
    {
        deimantai=deimantai+2;
    }
    else if (level==4)
    {
        eurai=eurai+4;
    }
    else if (level==5)
    {
        deimantai=deimantai+4;
    }
    else if (level==6)
    {
        sarvai=sarvai+4;
    }

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

    saveScore();
    HTML();
    _sleep(COLLISION_PAUSE);
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
    cout << " F L Y I N G   Z E R O ";

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
    case 'i':
        showInventor();
        break;
    case 't':
        showTop10Scores();
        break;
    case 'm':
        itemSelling();
        break;
    case 'l':
        pasiekimuLentele();
    case 'b':
        zemelapis();
    }
}

void checkCollision()
{

    if ((abs(herojusX-x) < paklaidaX) && (abs(herojusY-y) < paklaidaY))
    {
        getAndShowItem();
        level++;
        anotherStartData();
        eurai=eurai+5;
        showOtherSkin();

        showInventor();
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
                startGame();
            }

            _sleep(COLLISION_PAUSE);
            clearScreen();
            randomizeEnemyPosition();
        }
    }

}
