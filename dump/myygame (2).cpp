#include "iGraphics.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<iostream>
#include<windows.h>
#include<mmsystem.h>


#define maxenemynum 20
int myx=100, myy=300;
int l=1200, w=700;
int my_missile_x[100000], my_missile_y[100000], n=0, m1=1;
int i, j;

int lives=5, point=0;
FILE *fp;
FILE *fscorename;


int planewidth=130, myplaneht=40;
int eplanewidth=90, eplaneht=30;
int bottomht=50;

int eachbgwidth=100;

bool musicon=true;
char bg[6][20]= {"front.bmp","gamestartbg.bmp","gamebg6.bmp","skyfighter2.bmp","space.bmp","gameoverss.bmp"};


//char bg[5][20]= {"space.bmp","gamestartbg.bmp","gamebg6.bmp","skyfighter2.bmp"};
int bgind=0;
char upbgimage[10][20]= {"bg1.bmp","bg2.bmp","bg3.bmp","bg4.bmp","bg5.bmp","bg6.bmp","bg7.bmp","bg8.bmp","bg9.bmp","bg10.bmp"};
int bgspeed=6;

char button[10][15]= {"menuplay.bmp","menuset.bmp","menucredit.bmp"};
char button2[10][15];
char homemenu[25];
char play[25];
char highscore[25];
char ins[25];


char enemypic[10][20]= {"Enemy1.bmp","Enemy2.bmp","Enemy3.bmp","Enemy4.bmp","Enemy5.bmp","Enemy6.bmp","Enemy7.bmp","Enemy8.bmp","Enemy9.bmp","Enemy10.bmp"};

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

typedef struct
{
    char name[100];
    int score;

} players;



//char pointstr[20];

int enemynumber=3;

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
    int enemyshot;
    int enemytime;
    int collide;

};

enemies e[20];
void my_bullet_movement(void)
{
    for(i=0; i<n; i++)
    {
        my_missile_x[i]+=20;
    }

}



int f2called=0;
void enemy_movement(void)
{
    f2called++;

    if(f2called%2000==0)
    {
        if(enemynumber<maxenemynum)
        {
            enemynumber=enemynumber+1;
        }
    }
    //printf("enemy number=%d\n",enemynumber);
    /* int *enenmy_y;
     enenmy_y=(int*)calloc(enemynumber,sizeof(int));*/
    int j=0;
    //printf("f2 called:%d,enemynumber:%d\n",f2called,enemynumber);
    for (i=0; i<enemynumber; i++)
    {
        if(e[i].ex<=1-eplanewidth)
        {
            e[i].ex=l+10;
            e[i].ey=(rand()%(w-2*eplaneht-bottomht))+bottomht;
            for (j=0; j<i; j++)
            {
                if(e[i].ex>=e[j].ex-eplanewidth && e[i].ex<=(e[j].ex+eplanewidth) && e[i].ey>=e[j].ey-2*eplaneht && e[i].ey<=(e[j].ey+2*eplaneht))
                {

                    e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;



                }
            }

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

            int bulletvelocity=8;
            e[ind].e_bullet[i].x=e[ind].e_bullet[i].x-bulletvelocity;
        }
    }
}


/*
void enemy_bullet_position(void)
{
    for (int ind=0; ind<enemynumber; ind++)
    {
        e[ind].e_bullet[m1-1].x=e[ind].ex;
        e[ind].e_bullet[m1-1].y=e[ind].ey+30;

    }
}
*/

void enemy_bullet_position(void)
{
    for (int ind=0; ind<enemynumber; ind++)
    {
        if(e[ind].e_bullet[m1-1].x<=5)
        {
            e[ind].e_bullet[m1-1].x=e[ind].ex;
            e[ind].e_bullet[m1-1].y=e[ind].ey+30;
        }

    }
}




int gameover=0;
int gulikhaise=0;
int dhakkalgse=0;


int aftercollision=0;

int highest_score;
int ishighest=0;

void collision(void)
{
    if(gulikhaise==1 || dhakkalgse==1)
    {

        aftercollision++;
    }
    /*if(e[ind].enemyshot==1)
    {
        e[ind].enemytime++;
    }*/
    for (int ind=0; ind<enemynumber; ind++)

    {
        if(e[ind].enemyshot==1 || e[ind].collide==1)
        {
            e[ind].enemytime++;
        }

        for(i=0; i<m1; i++)
        {

            if(e[ind].e_bullet[i].x<myx+planewidth && e[ind].e_bullet[i].x>myx-5 && e[ind].e_bullet[i].y>=myy+20 && e[ind].e_bullet[i].y<myy+myplaneht+20)
            {
                lives-=1;
                iSetColor(rand()%256,rand()%256,rand()%256);
                // iText(e[ind].e_bullet[i].x,e[ind].e_bullet[i].y,"Collision");
                e[ind].e_bullet[i].x=-15;
                gulikhaise=1;
                iSetColor(rand()%255,rand()%255,rand()%255);
                // iText(myx+planewidth+20,myy+planewidth+50,"Live: -1");
                if(musicon==true)
        PlaySound("mylife.wav", NULL,SND_ASYNC);


            }
            else if(e[ind].ex<myx+planewidth+20 && e[ind].ex>myx-eplanewidth+20 && e[ind].ey>myy-eplaneht && e[ind].ey+15<myy+myplaneht/2+30)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=l+1000;
            }
             else if(e[ind].ex<myx+planewidth/2 && e[ind].ex>myx-eplanewidth+20 && e[ind].ey>myy-eplaneht+myplaneht/2+30 && e[ind].ey+15<myy+myplaneht+20)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=l+1000;
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
        fp=fopen("highscore.txt","r+");
        if(fp==NULL)
            printf("Cannot open file");
        else
        {
            highest_score=fscanf(fp,"%d",&highest_score);
            if(point>=highest_score)
            {
                ishighest=1;
                fprintf(fp,"%d\n",point);
                highest_score=point;
            }
            itoa(highest_score,highscore,10);

        }
        //printf("YOUR SCORE %d\n\n",point);
        //iText()


        // fscorename=fopen()

        fclose(fp);

    }

    for(int ind=0; ind<enemynumber; ind++)
    {
        for( i=0; i<n; i++)
        {
            if(my_missile_x[i]>(e[ind].ex-5) && my_missile_x[i]<(e[ind].ex+eplanewidth) && my_missile_y[i]>(e[ind].ey-10) && my_missile_y[i]<(e[ind].ey+eplaneht+20))
            {
                e[ind].enemyshot=1;
                /*
                               if(e[ind].enemytime>=50){
                                e[ind].ex=l+10;
                                e[ind].ey=rand()%(w-3);
                                e[ind].enemytime=0;
                                e[ind].enemyshot=0;
                                }*/
                my_missile_x[i]=l+1500;
                point+=50;


            }
        }
    }

}

char score_point[10];
char love[4];
void iDraw()
{
    iClear();



    if(gamestate==-1)
    {
        iShowBMP(0,0,bg[bgind]);
        for (int i=0; i<3; i++)
        {
            iShowBMP2(bcord[i].x,bcord[i].y,button[i],0);
        }

        iPauseTimer(0);
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);
    }

    else if(gamestate==0)
    {
        iResumeTimer(1);
        iResumeTimer(2);
        iResumeTimer(3);
        iSetColor(255,0,0);

        itoa(point,score_point,10);
        itoa(lives,love,10);
        iText(l/2,bottomht/2,"SCORE:");
        iText(l/2+50,bottomht/2,score_point);
        iText(l/4,bottomht/2,"LIVES:");
        iText(l/4+50,bottomht/2,love);
        iShowBMP(0,bottomht,bg[4]);

        /*for(i=0;i<10;i++){

            iShowBMP(upbg[i].x,upbg[i].y,upbgimage[i]);
        }*/

        if(gulikhaise==0 && dhakkalgse==0)
        {
            /* iSetColor(200,200,0);

             iFilledCircle(myx,myy,planewidth);

             iFilledRectangle(myx-100,myy-planewidth-5,100,5);

             iSetColor(255,0,0);*/
            iShowBMP2(myx,myy,"alien.bmp",0);
            //iShowBMP2(myx+35,myy+30,"planeagunn.bmp",0);

            for(i=0; i<n; i++)
            {
                iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
            }
        }
        else if(gulikhaise==1 || dhakkalgse==1)
        {
            /* iSetColor(255,00,0);

             iFilledCircle(myx,myy,planewidth);

             iFilledRectangle(myx-100,myy-planewidth-5,100,5);

             iSetColor(255,0,0);

             for(i=0; i<n; i++)
             {
                 iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);

             }*/

            iShowBMP2(myx,myy,"alien.bmp",0);
            iShowBMP2(myx+35,myy+30,"planeagunnn.bmp",255);

            for(i=0; i<n; i++)
            {
                iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
            }

            if(aftercollision>=100)
            {

                gulikhaise=0;
                dhakkalgse=0;
                aftercollision=0;
            }
        }
        iSetColor(0,0,255);


        for (i=0; i<enemynumber; i++)
        {
            // iFilledRectangle(e[i].ex,e[i].ey,10,12);
            if(e[i].enemytime>=50&& e[i].enemyshot==1)
            {
                e[i].ex=l+10;
                e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;
                e[i].enemytime=0;
                e[i].enemyshot=0;
                e[i].collide=0;
            }

            if(e[i].enemytime>=50&& e[i].collide==1)
            {
                e[i].ex=l+100;
                e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;
                e[i].enemytime=0;
                e[i].enemyshot=0;
                e[i].collide=0;
            }

            int no=rand()%10;


            iShowBMP2(e[i].ex,e[i].ey,enemypic[no],0);

            if((e[i].enemyshot==1 || e[i].collide==1) && e[i].enemytime<=50 )
            {
                iShowBMP2(e[i].ex+30,e[i].ey+12,"planeagunnn.bmp",255);

            }

            //else{
            //  iShowBMP2(e[i].ex,e[i].ey,"Enemy2.bmp",0);
            //}
            // iShowBMP2(e[i].ex,e[i].ey,"Aliencopy.bmp",0);
            //if(enemyshot==1 && enem)
        }

        iSetColor(255,100,0);
        for(int ind=0; ind<enemynumber; ind++)
        {
            for(i=0; i<m1; i++)
            {
                iFilledRectangle(e[ind].e_bullet[i].x, e[ind].e_bullet[i].y-eplaneht/2-5,5,5);
                // iFilledRectangle(e[ind].e_bullet[i].x, e[ind].e_bullet[i].y,5,5);
                // iShowBMP2(e[ind].e_bullet[i].x,e[ind].e_bullet[i].y,"bullet.bmp",0);

            }
        }
        iSetColor(rand()%256,rand()%256,rand()%256);
        if(gameover==1)
        {
            iShowBMP(0,0,bg[1]);
            iSetColor(rand()%55+200,rand()%155+100,rand()%100);
            iText(l/2,w/2,"GAME OVER");
            iText(l/2,w/2-100,"YOUR SCORE IS");
            iText(l/2+150,w/2-100,score_point);
            iText(l/2,w/2-200,"HIGHEST SCORE:");
            iText(l/2+150,w/2-200,highscore);
            if(ishighest==1)
            {
                iText(l/2-200,w/2-300,"CONGRATULATIONS!!YOU HAVE SCORED HIGHEST");
            }


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
        if(gamestate==0)
        {
            iResumeTimer(0);
            n++;
            my_missile_x[n-1]=myx+planewidth;
            my_missile_y[n-1]=myy+myplaneht/2;
            if(musicon==true)
                PlaySound("gunshot.wav", NULL,SND_ASYNC);

        }
    }
    if(key=='\b')
    {
        gamestate=-1;
        if(musicon==true)
        PlaySound("select.wav", NULL,SND_ASYNC);

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
                    if(musicon==true)
                        PlaySound("select.wav", NULL,SND_ASYNC);


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
                    if(musicon==true)
        PlaySound("select.wav", NULL,SND_ASYNC);

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
    /*for(i=0; i<10; i++)
    {

        upbg[i].y=0;
        upbg[i].x=sum;

        sum=sum+eachbgwidth;
    }*/
    int summ=w/6;
    for (int i=2; i>=0; i--)
    {
        bcord[i].x=l/8;
        bcord[i].y=summ;
        summ+=w/6;
    }
    for(j=0; j<100000; j++)
    {
        my_missile_x[j]=myx;
        my_missile_y[j]=myy;
    }
    for(int ind=0; ind<enemynumber; ind++)

    {
        e[ind].collide=0;
        e[ind].enemyshot=0;
        e[ind].enemytime=0;

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
    //  if(gamestate==0){
    iSetTimer(1,my_bullet_movement);
    iPauseTimer(0);
    iSetTimer(10,enemy_movement);
    iSetTimer(1,enemy_bullet_movement);
    iSetTimer(6000,enemy_bullet_position);
    iSetTimer(1,collision);
    // iSetTimer(50,renderbg);
    if(musicon==true)
        PlaySound("tense.wav", NULL,SND_ASYNC|SND_LOOP);

    iInitialize(l,w,"FIGHTER PLANE");


    return 0;
}
