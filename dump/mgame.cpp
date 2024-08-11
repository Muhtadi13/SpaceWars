#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<windows.h>
#include<MMSystem.h>

int myx=100, myy=300;
int l=1000, w=600;
int my_missile_x[100000], my_missile_y[100000], n=0, m1=1;
int i, j;

int lives=10, point=0;
FILE *fp;

int planewidth=150, myplaneht=32;
int eplanewidth=110, eplaneht=40;

int eachbgwidth=100;

bool musicon=true;
char bg[5][20]={"demoBG.bmp","skyfighter2.bmp","skyfighter3.bmp","bg1.bmp"};
int bgind=0;
char upbgimage[10][20]= {"bg1.bmp","bg2.bmp","bg3.bmp","bg4.bmp","bg5.bmp","bg6.bmp","bg7.bmp","bg8.bmp","bg9.bmp","bg10.bmp"};
int bgspeed=6;

char button[10][15]= {"menuplay.bmp","menuset.bmp","menucredit.bmp"};
char button2[10][15];
char homemenu[25];
char play[25];
char highscore[25];
char ins[25];

int gamestate=-1;

struct buttoncord
{
    int x;
    int y;
} bcord[5];

struct background
{
    int x;
    int y;
};
background upbg[10],lowbg[10];



char pointstr[20];

int enemynumber=2;

struct coord
{
    int x;
    int y;
};

struct enemies
{
    int ex;
    int ey;
    int eind;
    bool eshow;
    coord e_bullet[100000];

};

enemies e[20];
void my_bullet_movement(void)
{
    for(i=0; i<n; i++)
    {
        my_missile_x[i]+=13;
    }

}



int f2called=0;
void enemy_movement(void)
{
    f2called++;

    if(f2called%2000==0)
    {

        enemynumber=enemynumber+1;
    }
    /* int *enenmy_y;
     enenmy_y=(int*)calloc(enemynumber,sizeof(int));*/
    int j=0;
    //printf("f2 called:%d,enemynumber:%d\n",f2called,enemynumber);
    for (i=0; i<enemynumber; i++)
    {
        if(e[i].ex<=1-eplanewidth)
        {
            e[i].ex=l+10;
            e[i].ey=rand()%(w-eplaneht);

        }
        else
        {
            e[i].ex-=3;
        }
    }
}

void enemy_bullet_movement(void)
{
    for(int ind=0; ind<enemynumber; ind++)
    {
        for(i=0; i<m1; i++)
        {

            int bulletvelocity=4;
            e[ind].e_bullet[i].x=e[ind].e_bullet[i].x-bulletvelocity;
        }
    }
}

void enemy_bullet_position(void)
{
    for (int ind=0; ind<enemynumber; ind++)
    {
        e[ind].e_bullet[m1-1].x=e[ind].ex;
        e[ind].e_bullet[m1-1].y=e[ind].ey+30;

    }
}

int gameover=0;
int gulikhaise=0;
int dhakkalgse=0;



void collision(void)
{
    for (int ind=0; ind<enemynumber; ind++)
    {
        for(i=0; i<m1; i++)
        {

            if(e[ind].e_bullet[i].x<myx+planewidth && e[ind].e_bullet[i].x>myx-5 && e[ind].e_bullet[i].y>=myy && e[ind].e_bullet[i].y<myy+myplaneht)
            {
                lives-=1;
                iSetColor(rand()%256,rand()%256,rand()%256);
                iText(e[ind].e_bullet[i].x,e[ind].e_bullet[i].y,"Collision");
                e[ind].e_bullet[i].x=-15;
                gulikhaise=1;
                iSetColor(rand()%255,rand()%255,rand()%255);
                iText(myx+planewidth+20,myy+planewidth+50,"Live: -1");

            }
            else if(e[ind].ex<myx+planewidth && e[ind].ex>myx-eplanewidth && e[ind].ey>myy-eplaneht && e[ind].ey+15<myy+myplaneht)
            {
                lives-=1;
                //  enemy1_x=l+10;
                e[ind].ex=l;
                point++;
                dhakkalgse=1;
            }
        }
    }

    if(lives==0)
    {
        iPauseTimer(0);
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);
        iPauseTimer(4);
        gameover=1;
        if(gameover==1)
        {
            iText(500,300,"GAME OVER");
        }
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

    for(int ind=0; ind<enemynumber; ind++)
    {
        for( i=0; i<n; i++)
        {
            if(my_missile_x[i]>(e[ind].ex-5) && my_missile_x[i]<(e[ind].ex+eplanewidth) && my_missile_y[i]>(e[ind].ey+15) && my_missile_y[i]<(e[ind].ey+eplaneht))
            {
                e[ind].ex=l+10;
                e[ind].ey=rand()%(w-3);
                my_missile_x[i]=l+1500;
                point+=50;

            }
        }
    }

}



void iDraw()
{
    iClear();

    if(gamestate==-1)
    {
    //iShowBMP(0,0,bg[bgind]);
        for (int i=0; i<3; i++)
        {
            iShowBMP2(bcord[i].x,bcord[i].y,button[i],0);
        }
    }

    else if(gamestate==0)
    {

       //iShowBMP(0,0,bg[0]);

        /*for(i=0;i<10;i++){

            iShowBMP(upbg[i].x,upbg[i].y,upbgimage[i]);
        }*/

        if(gulikhaise==0 && dhakkalgse==0)
        {
            /* iSetColor(200,200,0);

             iFilledCircle(myx,myy,planewidth);

             iFilledRectangle(myx-100,myy-planewidth-5,100,5);

             iSetColor(255,0,0);*/
            iShowBMP2(myx,myy,"Alien.bmp",0);

            for(i=0; i<n; i++)
            {
                iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
            }
        }
        else if(gulikhaise==1 || dhakkalgse==1)
        {
            iSetColor(255,00,0);

            iFilledCircle(myx,myy,planewidth);

            iFilledRectangle(myx-100,myy-planewidth-5,100,5);

            iSetColor(255,0,0);

            for(i=0; i<n; i++)
            {
                iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
            }
            gulikhaise=0;
            dhakkalgse=0;
        }
        iSetColor(0,0,255);


        for (i=0; i<enemynumber; i++)
        {
            // iFilledRectangle(e[i].ex,e[i].ey,10,12);
            iShowBMP2(e[i].ex,e[i].ey,"Enemy.bmp",0);
        }

        iSetColor(255,100,0);
        for(int ind=0; ind<enemynumber; ind++)
        {
            for(i=0; i<m1; i++)
            {
                iFilledRectangle(e[ind].e_bullet[i].x, e[ind].e_bullet[i].y,5,5);

            }
        }
        iSetColor(rand()%256,rand()%256,rand()%256);
        if(gameover==1)
        {
            iText(1000,600,"GAME OVER");
        }

    }
    else if(gamestate==1)
    {
        iSetColor(rand()%255,rand()%255,rand()%255);
        iText(500,300+50,"Settings menu under development");
        iText(500,300+25,"Instructions to play this game: ");
        iText(500,300-50,"Use Keyboard navigation button to move your plane");
        iText(500,300-50-25,"Use mouse to click menu");
    }

}

void iMouseMove(int mx,int my)
{

}

void iKeyboard(unsigned char key)
{
    if(key==' ')
    {
        iResumeTimer(0);
        n++;
        my_missile_x[n-1]=myx+planewidth;
        my_missile_y[n-1]=myy+myplaneht/2;
    }

}


void iMouse(int button,int state,int mx,int my)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        for ( i=0; i<3; i++)
        {
            if(mx>=bcord[i].x && mx<=(bcord[i].x+300)&& my>=bcord[i].y && my<=bcord[i].y+100)
            {
                if(gamestate==-1)
                {
                    gamestate=i;
                }
            }


        }

    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        for (i=0; i<3; i++)
        {
            if(mx>=bcord[i].x && mx<=(bcord[i].x+300)&& my>=bcord[i].y && my<=bcord[i].y+100)
            {
                if(gamestate==-1)
                {
                    gamestate=i;
                }
            }

        }
    }
}

//int planewidth=100;

void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_LEFT && myx>=5)
    {
        myx-=10;
        //if(myx<=planewidth)
       // {
         //   myx=l-planewidth;
        //}
    }
    if(key==GLUT_KEY_RIGHT && myx<=l-planewidth)
    {
        myx+=10;
        //if(myx>=l-planewidth)
        //{
           // myx=planewidth;
        //}
    }

    if(key==GLUT_KEY_UP && myy<=w-myplaneht-10)
    {
        myy+=10;
    }
    if(key==GLUT_KEY_DOWN && myy>=20)
    {
        myy-=10;
    }


}



void setall()
{
    int sum=0;
    for(i=0; i<10; i++)
    {

        upbg[i].y=0;
        upbg[i].x=sum;

        sum=sum+eachbgwidth;
    }
    int summ=100;
    for (int i=2; i>=0; i--)
    {
        bcord[i].x=150;
        bcord[i].y=summ;
        summ+=150;
    }
    for(j=0; j<100000; j++)
    {
        my_missile_x[j]=myx;
        my_missile_y[j]=myy;
    }
    for(int ind=0; ind<enemynumber; ind++)
    {
        for(j=0; j<10; j++)
        {
            e[ind].e_bullet[j].x=e[ind].ex;
            e[ind].e_bullet[j].y=e[ind].ey+5;
        }
    }


}
/*
void renderbg(){

    for(int i=0;i<10;i++){
        upbg[i].x-=bgspeed;
        if(upbg[i].x<0){
            upbg[i].x=w-eachbgwidth;
        }
    }
}
*/
int main()
{


    setall();
    iSetTimer(1,my_bullet_movement);
    iPauseTimer(0);
    iSetTimer(10,enemy_movement);
    iSetTimer(1,enemy_bullet_movement);
    iSetTimer(4000,enemy_bullet_position);
    iSetTimer(1,collision);
    // iSetTimer(50,renderbg);
    // PlaySound(TEXT("bgmusic.wav"),NULL,SND_ASYNC | SND_LOOP);
    iInitialize(l,w,"FIGHTER PLANE");


    return 0;
}
