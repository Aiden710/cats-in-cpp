#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] =  {' ','±','±',' ',
                   '±','±','±','±',
                   ' ','±','±',' ',
                   '±','±','±','±'};
int carPos= WIN_WIDTH/2;
int score = 0;
int totalscore = 0 ;
double enemySpeed=1.00;
void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);

}
void setcursor(bool visible, DWORD size)
{
    if(size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);

}
void drawBorder()
{
    for(int i=0; i<SCREEN_HEIGHT; i++){
        for(int j=0; j<17; j++){
            gotoxy(0+j,i); cout << "±";
            gotoxy(WIN_WIDTH-j,i); cout<< "±";
        }
    }
    for(int i=0; i<SCREEN_HEIGHT; i++)
{
    gotoxy(SCREEN_WIDTH,i); cout<<"±";
}
}
void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand()%(33);
}
void drawEnemy(int ind)
{
    if(enemyFlag[ind] == true){
            gotoxy(enemyX[ind], enemyY[ind]);    cout<<" ** ";
            gotoxy(enemyX[ind], enemyY[ind]+1);  cout<<"*  *";
            gotoxy(enemyX[ind], enemyY[ind]+2);  cout<<" ** ";


}
}
void eraseEnemy(int ind)
{
    if(enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind],enemyY[ind] );  cout<<"    ";
        gotoxy(enemyX[ind],enemyY[ind]+1); cout<<"    ";
        gotoxy(enemyX[ind],enemyY[ind]+2); cout<<"    ";


    }
}
void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind]= 1;
    genEnemy(ind);
}
void drawCar()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gotoxy(j+carPos, i+22); cout << car[i][j];
        }
    }
}
void eraseCar()
{
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gotoxy(j+carPos, i+22); cout <<" ";
        }
    }
}
int collision()
{
    if(enemyY[0]+4 >= 23)
    {
        if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos <9 )
        {
            return 1;
        }
    }
    return 0;
}
void gameover(){
system("cls");
cout << endl;
cout << "\t\t----New Score: " << score << endl;
cout << "\t\t--- Highest-Score: " << totalscore << endl;
cout << "\t\t------------------"<<endl;
cout << "\t\t----Game Over-----"<<endl;
cout << "\t\t------------------"<<endl;
cout << "\t\t press any key to go back to menu.";

   ofstream file;

     file.open("sdpgrp8final.txt",ios::out|ios::app);
     file << "Score: " << score << endl;
     file << "Highest-score:" << totalscore << endl;

    file.close();

getch();
 }
 void updateScore()
 {
     gotoxy(WIN_WIDTH +7, 5); cout<<"Score: "<< score<<endl;
     gotoxy(WIN_WIDTH +3, 2); cout<<"Highest-score: "<<totalscore<<endl;
 }
 void highestScore()  //333333
 {
    if(totalscore > score)
    {
        //totalscore++;
        cout << "Highest-score:" << totalscore << endl;
    }
    else if( totalscore = score)
    {
        cout << "Highest-score:" << score << endl;
    }
    else if(totalscore < score)
    {
        cout << "Highest-score:" << score <<endl;
    }

 }
 void level()
 {
     if(score == 20)
     {
         enemySpeed = 2.00;
         score+= 5;

        cout<< "congratulation \n";
        cout << "You Complete \n";
        cout << "Level 1 ";
     }
     else if ( score > 50 )
     {
         enemySpeed = 2.00;
         score +=10;
        cout<< "congratulation\n";
        cout << "You Complete \n";
        cout << "Level 2 ";
     }

 }

 void instruction()
 {
     system("cls");
     cout<<"Instructions";
     cout << "\n----------";
     cout << "\n Avoid cars by movie left of right.";
     cout << "\n\n press 'a' to move left";
     cout << "\n press 'd' to move right";
     cout << "\n press 'escape' to exit";
     cout << "\n\n press any key to go back to menu";
     getch();

 }
 void play()
 {
     carPos = WIN_WIDTH/2;
     score = 0;
     enemyFlag[0] = 1;
     enemyFlag[1] = 0;
     enemyY[0] = enemyY[1] = 1;

     system("cls");
     drawBorder();
     updateScore();
     highestScore();
     genEnemy(0);
     genEnemy(1);

     gotoxy(WIN_WIDTH +7, 2); cout<< "Car Game" << endl;
     gotoxy(WIN_WIDTH +6, 4); cout << "---------";
      cout << endl;
     gotoxy(WIN_WIDTH +6, 6); cout << "---------";
     gotoxy(WIN_WIDTH +7, 12); cout << "Control";
     gotoxy(WIN_WIDTH +7, 13); cout << "--------";
     gotoxy(WIN_WIDTH +2, 14); cout << "A key - Left";
     gotoxy(WIN_WIDTH +2, 15); cout << "D key - Right";

      gotoxy(18, 5); cout << "Press any key to start";
      getch();
      gotoxy(18, 5); cout << "          ";

      while(1)
      {
          if(kbhit())
          {
              char ch = getch();
              if(ch == 'a' || ch =='A')
              {
                  if(carPos>18)
                    carPos-= 5;
              }
              if(ch=='d' || ch=='D')
              {
                  if(carPos <50)
                    carPos += 5;
              }
              if(ch== 27)
              {
                  break;
              }
          }
          drawCar();
          drawEnemy(0);
          drawEnemy(1);
          if( collision() == 1)
          {
              gameover();
              return ;
          }
          Sleep(50);
          eraseCar();
          eraseEnemy(0);
          eraseEnemy(1);
          if(enemyY[0] == 10)

              if(enemyFlag[1] == 0)
                  enemyFlag[1] = 1;

          if(enemyFlag[0] == 1)
            enemyY[0] += enemySpeed;

          if(enemyFlag[1] == 1)
            enemyY[1] += enemySpeed;

          if(enemyY[0] > SCREEN_HEIGHT-4)
          {
              resetEnemy(0);
              score ++;
              updateScore();

              highestScore();
              level();
          }
          if(enemyY[1] > SCREEN_HEIGHT-4)
          {
              resetEnemy(1);
              score++;
              updateScore();

              highestScore();
              level();
          }

      }

 }
 int main()
 {
     string name;
      ofstream file;
      int highestScore;

    file.open("sdpgrp8final.txt",ios::out|ios::app);
    cout << "Enter your name: ";
    getline(cin,name);
    file << name << endl;

    file.close();


     do{
        system("cls");
        gotoxy(10,5); cout<<"--------------------------";
        gotoxy(10,6); cout<<" |       Car Game        |";
        gotoxy(10,7); cout<< "-------------------------";
        gotoxy(10,9); cout<< "1. start Game";
        gotoxy(10,10); cout<< "2. Instructions";
        gotoxy(10,11); cout<< "3. Quit";
        gotoxy(10,13); cout<< "select option: ";


        char op = getche();

        if(op == '1')
        {
            play();
            level();
        }
        else if (op == '2')
            {
                instruction();
                }
        else if (op == '3')
        {
            exit(0);
        }


     }

     while(1);
     return 0;
 }

