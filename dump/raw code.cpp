#include "iGraphics.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int myx=100, myy=300, r=20;
int l=800, w=400;
int my_missile_x[100000], my_missile_y[100000], n=0, m1=1;
int i , j, enemy1_x=l-10, enemy1_y=rand()%w;
int enemy2_y=rand()%w, enemy3_y=rand()%w;
int enemy2_x=l-10, enemy3_x=l-10;
int enemy1_bullet_x[100000], enemy1_bullet_y, enemy2_bullet_y, enemy3_bullet_y;
int enemy2_bullet_x[100000], enemy3_bullet_x[100000];
int lives=3, point=0;
FILE *fp;


void my_bullet_movement(void)
{
    for(i=0; i<n; i++)
    {
        my_missile_x[i]+=13;
    }

}
void enemy_movement(void)
{
    if(enemy1_x<=3)
    {
        enemy1_x=l-10;
        enemy1_y=rand()%w;
    }
    else
        enemy1_x-=1;
    if(enemy2_x<=3)
    {
        enemy2_x=l-10;
        enemy2_y=rand()%w;
    }
    else
        enemy2_x-=3;
    if(enemy3_x<=3)
    {
        enemy3_x=l-10;
        enemy3_y=rand()%w;
    }
    else
        enemy3_x-=2;

}
void enemy_bullet_movement(void)
{
    for(i=0; i<m1; i++)
    {
        enemy1_bullet_x[i]-=4;
        enemy2_bullet_x[i]-=4;
        enemy3_bullet_x[i]-=6;
    }

}
void enemy_bullet_position(void)
{
    enemy1_bullet_x[m1-1]=enemy1_x;
    enemy1_bullet_y=enemy1_y;
    enemy2_bullet_x[m1-1]=enemy2_x;
    enemy2_bullet_y=enemy2_y;
    enemy3_bullet_x[m1-1]=enemy3_x;
    enemy3_bullet_y=enemy3_y;


}

void collision(void)
{
    for(i=0; i<m1; i++)
    {
        if(enemy1_bullet_x[i]<myx+r && enemy1_bullet_x[i]>myx-r && enemy1_bullet_y>myy-r && enemy1_bullet_y<myy+r)
        {
            lives-=1;
            enemy1_bullet_x[i]=-15;
        }
        else if(enemy2_bullet_x[i]<myx+r && enemy2_bullet_x[i]>myx-r && enemy2_bullet_y>myy-r && enemy2_bullet_y<myy+r)
        {
            lives-=1;
            enemy2_bullet_x[i]=-15;
        }
        else if(enemy3_bullet_x[i]<myx+r && enemy3_bullet_x[i]>myx-r && enemy3_bullet_y>myy-r && enemy3_bullet_y<myy+r)
        {
            lives-=1;
            enemy3_bullet_x[i]=-15;
        }
        else if(enemy1_x<myx+r && enemy1_x>myx-r-10 && enemy1_y>myy-r-10 && enemy1_y<myy+r)
        {
            lives-=1;
            enemy1_x=l+10;
            point++;
        }
         else if(enemy2_x<myx+r && enemy2_x>myx-r-10 && enemy2_y>myy-r-10 && enemy2_y<myy+r)
        {
            lives-=1;
            enemy2_x=l+10;
            point++;
        }
         else if(enemy3_x<myx+r && enemy3_x>myx-r-10 && enemy3_y>myy-r-10 && enemy3_y<myy+r)
        {
            lives-=1;
            enemy3_x=l+10;
            point++;
        }

        if(lives==0)
        {
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            iPauseTimer(4);
            //exit(0);
            fp=fopen("highscore.txt","w");
            if(fp==NULL)
                printf("Cannot open file");
            else
            {
                fprintf(fp,"%d",point);

            }
            printf("YOUR SCORE %d\n\n",point);

        }
    }
    for(i=0; i<n; i++)
    {
        if(my_missile_x[i]>enemy1_x-15 && my_missile_x[i]<enemy1_x && my_missile_y[i]>enemy1_y-6 && my_missile_y[i]<enemy1_y+10)
        {
            enemy1_x=l+10;
            my_missile_x[i]=l+15;
            point++;
        }
        else if(my_missile_x[i]>enemy2_x-15 && my_missile_x[i]<enemy2_x && my_missile_y[i]>enemy2_y-6 && my_missile_y[i]<enemy2_y+10)
        {
            enemy2_x=l-1;
            my_missile_x[i]=l+20;
            point++;
        }
        else if(my_missile_x[i]>enemy3_x-15 && my_missile_x[i]<enemy3_x && my_missile_y[i]>enemy3_y-6 && my_missile_y[i]<enemy3_y+10)
        {
            enemy3_x=l-2;
            my_missile_x[i]=l+30;
            point++;
        }
    }

}



void iDraw()
{
    iClear();
    //iShowBMP(0,0,"moor.bmp");
    iSetColor(200,200,0);

    iFilledCircle(myx,myy,r);

    iFilledRectangle(myx-100,myy-r-5,100,5);

    iSetColor(255,0,0);

    for(i=0; i<n; i++)
    {
        iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
    }
    iSetColor(0,0,255);

    iFilledRectangle(enemy1_x,enemy1_y,10,12);

    iFilledRectangle(enemy2_x,enemy2_y,10,12);

    iFilledRectangle(enemy3_x,enemy3_y,10,12);

    iSetColor(255,100,0);

    for(i=0; i<m1; i++)
    {
        iFilledRectangle(enemy1_bullet_x[i],enemy1_bullet_y,5,5);
        iFilledRectangle(enemy2_bullet_x[i],enemy2_bullet_y,5,5);
        iFilledRectangle(enemy3_bullet_x[i],enemy3_bullet_y,5,5);

    }

}

void iMouseMove(int mx,int my)
{

}

void iKeyboard(unsigned char key)
{
    if(key=='a')
    {


    }

}


void iMouse(int button,int state,int mx,int my)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        iResumeTimer(0);
        n++;
        my_missile_x[n-1]=myx;
        my_missile_y[n-1]=myy;



    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {

    }
}



void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_LEFT && myx>=15)
    {
        myx-=10;
    }
    if(key==GLUT_KEY_RIGHT && myx<=l-15)
    {
        myx+=10;
    }

    if(key==GLUT_KEY_UP && myy<=w-15)
    {
        myy+=10;
    }
    if(key==GLUT_KEY_DOWN && myy>=15)
    {
        myy-=10;
    }


}
int main()
{
    for(j=0; j<100000; j++)
    {
        my_missile_x[j]=myx;
        my_missile_y[j]=myy;
    }

    for(j=0; j<10; j++)
    {
        enemy1_bullet_x[j]=enemy1_x;
        enemy2_bullet_x[j]=enemy2_x;
        enemy3_bullet_x[j]=enemy3_x;
        enemy1_bullet_y=enemy1_y;
        enemy2_bullet_y=enemy2_y;
        enemy3_bullet_y=enemy3_y;
    }


    iSetTimer(1,my_bullet_movement);
    iPauseTimer(0);
    iSetTimer(10,enemy_movement);
    iSetTimer(1,enemy_bullet_movement);
    iSetTimer(4000,enemy_bullet_position);
    iSetTimer(1,collision);
    iInitialize(l,w,"fighter_plane");


    return 0;
}
