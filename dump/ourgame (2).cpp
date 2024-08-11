#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<windows.h>
#include<MMSystem.h>


#define maxenemynum 20
int myx=100, myy=300;
int l=1200, w=600;
int my_missile_x[100000], my_missile_y[100000], n=0, m1=1;
int i, j;
int resumestate=0;
int musflag=1;
int resetstate=0;

int lives=5, point=0;
FILE *fp;
FILE *fscorename;

int my_missile_velocity=20;
int bulletvelocity=8;


int planewidth=150, myplaneht=40;
int eplanewidth=110, eplaneht=25;
int bottomht=100;

int backcordx=0,backcordy=0;

int eachbgwidth=100;

bool musicon=true;
char bg[6][20]= {"front.bmp","gameoverss.bmp","gamestartbg.bmp","gamebg6.bmp","skyfighter2.bmp","space.bmp"};


//char bg[5][20]={"space.bmp","gamestartbg.bmp","gamebg6.bmp","skyfighter2.bmp"};
int bgind=0;
char upbgimage[10][20]= {"bg1.bmp","bg2.bmp","bg3.bmp","bg4.bmp","bg5.bmp","bg6.bmp","bg7.bmp","bg8.bmp","bg9.bmp","bg10.bmp"};
int bgspeed=6;

char button[10][15]= {"resume.bmp","start.bmp","help.bmp","sound_off.bmp","credits.bmp","sound_on.bmp"};
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
struct resumecord
{
    int x;
    int y;
} rcord[5];

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


char playername[80];
int nameind=0;


//char pointstr[20];

int enemynumber=3;

struct coord
{
    int x;
    int y;
};

typedef struct
{
    int ex;
    int ey;
    int eind;
    bool eshow;
    coord e_bullet[100000];
    int enemyshot;
    int enemytime;
    int collide;

} enemies;

enemies e[20];

coord name_text,name_box;

int hall_of_fame_called=0;
//FILE *fileofname;

int saved=0;
coord savebutton;






FILE *fileofname;



void hall_of_fame()
{
    int no_of_data;

    hall_of_fame_called=1;
    FILE *database;
    database=fopen("hall_of_fame.txt","r");
    fscanf(database,"%d",&no_of_data);
    no_of_data++;

    players *player_data=(players*)malloc(no_of_data*sizeof(players));
    int readsuccessfully=0;

    for(int it=0; it<no_of_data-1; it++)
    {

        fscanf(database,"%d",&player_data[it].score);
        fgets(player_data[it].name,100,database);
        if(feof(database) || player_data[it].score<=0 )
        {
            break;
        }
        readsuccessfully++;
        printf("previous record:%d %s\n",player_data[it].score,player_data[it].name);
    }


    fclose(database);
    if(no_of_data==readsuccessfully+1)
    {
        printf("no error reading\n");
    }
    else
    {
        no_of_data=readsuccessfully+1;
    }


    char nameofplayer[100];
    FILE *file1=fopen("name.txt","r");
    int si=0;
    if(fp==NULL)
    {
        printf("error reading name file\n");
    }
    else
    {
        if(nameind==0)
        {
            strcpy(nameofplayer,"UNKNOWN PLAYER");
        }
        else if(nameind>0)
        {
            do
            {
                char key=fgetc(file1);
                if(feof(file1))
                {
                    fclose(file1);
                    break;
                }


                if(key!='\b')
                {
                    nameofplayer[si]=key;

                    // printf("checking:%c\t%d",playername[nameind],write);
                    si++;
                    nameofplayer[si]='\0';
                }


                else if(key=='\b')
                {

                    if(si<=0)
                    {
                        si=0;
                    }
                    else
                    {
                        si--;
                        nameofplayer[si]='\0';
                    }
                }


            }
            while(1);

        }
        printf("\nPLayer name=%s\n",nameofplayer);

    }

    database=fopen("hall_of_fame.txt","w");
    for(int it=0; it<no_of_data-1; it++)
    {
        if(point>=player_data[it].score)
        {
            for(int jt=no_of_data-1; jt>it; jt--)
            {
                player_data[jt].score=player_data[jt-1].score;
                strcpy(player_data[jt].name,player_data[jt-1].name);
            }
            player_data[it].score=point;
            strcpy(player_data[it].name,nameofplayer);
            break;
        }


    }

    int it=0,jt=0;






    fprintf(fp,"%d\n",no_of_data);
    if(no_of_data==1)
    {
        player_data[0].score=point;
        strcpy(player_data[0].name,nameofplayer);
    }
    for(int it=0; it<no_of_data; it++)
    {

        fprintf(database,"%d %s\n",player_data[it].score,player_data[it].name);

    }


    //printf("%d\n",no_of_data+1);

    fclose(database);
//    fclose(fileofname);


    free(player_data);
}


void my_bullet_movement(void)
{
    for(i=0; i<n; i++)
    {
        my_missile_x[i]+=my_missile_velocity;
    }

}



int f2called=0;
void enemy_movement(void)
{
    f2called++;

    if(f2called%200==0)
    {
        if(enemynumber<maxenemynum)
        {
            enemynumber=enemynumber+1;
        }
    }
    // printf("enemy number=%d\n",enemynumber);
    /* int *enenmy_y;
     enenmy_y=(int*)calloc(enemynumber,sizeof(int));*/
    int j=0;
    //printf("f2 called:%d,enemynumber:%d\n",f2called,enemynumber);
    for (i=0; i<enemynumber; i++)
    {
        if(e[i].ex<=1-eplanewidth)
        {
            e[i].collide=0;
            e[i].enemyshot=0;
            e[i].enemytime=0;
            e[i].ex=l+10;
            e[i].ey=(rand()%(w-eplaneht-bottomht))+bottomht;
            for (j=0; j<enemynumber; j++)
            {

                if(j!=i && e[i].ex>=e[j].ex-2*eplanewidth && e[i].ex<=(e[j].ex+2*eplanewidth) && e[i].ey>=e[j].ey-2*eplaneht && e[i].ey<=(e[j].ey+2*eplaneht))
                {

                    e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;



                }
            }

        }
        else
        {
            //e[i].ex-=3;
            e[i].ex=e[i].ex-(4);
        }
    }
}

void enemy_bullet_movement(void)
{
    for(int ind=0; ind<enemynumber; ind++)
    {
        for(i=0; i<m1; i++)
        {


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
        if(e[ind].ey>=myy-200 && e[ind].ey<=myy+200)
        {
            if(e[ind].e_bullet[m1-1].x<=5)
            {

                e[ind].e_bullet[m1-1].x=e[ind].ex;
                e[ind].e_bullet[m1-1].y=e[ind].ey+eplaneht-5;

            }
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
    //if(e[ind].enemyshot==1)
    //{
    //  e[ind].enemytime++;
    //}
    for (int ind=0; ind<enemynumber; ind++)

    {
        if(e[ind].enemyshot==1 || e[ind].collide==1)
        {
            e[ind].enemytime++;
        }

        for(i=0; i<m1; i++)
        {

            if(e[ind].e_bullet[i].x<myx+planewidth && e[ind].e_bullet[i].x>myx+5 && e[ind].e_bullet[i].y>=myy+10 && e[ind].e_bullet[i].y<myy+myplaneht+10)
                //if(e[ind].e_bullet[i].x<=myx+planewidth && e[ind].e_bullet[i].x>myx-5 && e[ind].e_bullet[i].y>=myy-10 && e[ind].e_bullet[i].y<myy+myplaneht+10)
            {

                lives-=1;
                iSetColor(rand()%256,rand()%256,rand()%256);
                // iText(e[ind].e_bullet[i].x,e[ind].e_bullet[i].y,"Collision");
                e[ind].e_bullet[i].x=-15;
                gulikhaise=1;
                iSetColor(rand()%255,rand()%255,rand()%255);
                //  PlaySound("mygunshoot.wav",NULL,SND_ASYNC);




            }
            else if(e[ind].ex<myx+planewidth-40 && e[ind].ex>myx-eplanewidth/2 && e[ind].ey>myy+myplaneht/2 && e[ind].ey+15<myy+myplaneht)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=l+1000;
                PlaySound("crash.wav",NULL,SND_ASYNC);
            }
            else if(e[ind].ex<myx+planewidth && e[ind].ex>myx-eplanewidth+10 && e[ind].ey>myy-eplaneht+10 && e[ind].ey+15<myy+myplaneht/2)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=l+1000;
                //PlaySound("crash.wav",NULL,SND_ASYNC);
            }
            else if(e[ind].ex<myx+planewidth/2 && e[ind].ex>myx-eplanewidth+10 && e[ind].ey>myy-eplaneht && e[ind].ey<myy-eplaneht+10)
                //else if(e[ind].ex<myx+planewidth && e[ind].ex>myx-eplanewidth && e[ind].ey>myy-eplaneht-20 && e[ind].ey<myy+myplaneht+10)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=l+1000;

                //PlaySound("crash.wav",NULL,SND_ASYNC);
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
            if(my_missile_x[i]>(e[ind].ex-5) && my_missile_x[i]<(e[ind].ex+eplanewidth) && my_missile_y[i]>(e[ind].ey-10) && my_missile_y[i]<(e[ind].ey+eplaneht))
            {
                e[ind].enemyshot=1;

                // if(e[ind].enemytime>=50){
                //  e[ind].ex=l+10;
                //e[ind].ey=rand()%(w-3);
                //e[ind].enemytime=0;
                //e[ind].enemyshot=0;
                //}
                my_missile_x[i]=l+1500;
                point+=50;


            }
        }
    }
    if(gulikhaise==1)
    {
        PlaySound("crash.wav",NULL,SND_ASYNC);
    }
}













/*void collision(void)
{
    if(gulikhaise==1 || dhakkalgse==1)
    {

        aftercollision++;
    }
    //if(e[ind].enemyshot==1)
    //{
       // e[ind].enemytime++;
   // }
    for (int ind=0; ind<enemynumber; ind++)

    {
        if(e[ind].enemyshot==1 || e[ind].collide==1)
        {
            e[ind].enemytime++;
        }

        for(i=0; i<m1; i++)
        {

            if(e[ind].e_bullet[i].x<=myx+planewidth && e[ind].e_bullet[i].x>myx-5 && e[ind].e_bullet[i].y>=myy-10 && e[ind].e_bullet[i].y<myy+myplaneht+10)
            {
                lives-=1;
                iSetColor(rand()%256,rand()%256,rand()%256);
                // iText(e[ind].e_bullet[i].x,e[ind].e_bullet[i].y,"Collision");
                e[ind].e_bullet[i].x=-15;
                gulikhaise=1;
                PlaySound("mygunshoot.wav",NULL,SND_ASYNC);
                // iSetColor(rand()%255,rand()%255,rand()%255);
                // iText(myx+planewidth+20,myy+planewidth+50,"Live: -1");

            }
            else if(e[ind].ex<myx+planewidth+20 && e[ind].ex>myx-eplanewidth && e[ind].ey>myy-eplaneht-20 && e[ind].ey<myy+myplaneht+10)
            {
                lives-=1;
                //  enemy1_x=l+10;



                point++;
                dhakkalgse=1;
                e[ind].collide=1;
                e[ind].ex=myx-eplanewidth-10;
                PlaySound("crash.wav",NULL,SND_ASYNC);
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
        //if(gameover==1)
        //{
           // iText(500,300,"GAME OVER");
        //}

        //exit(0);
        fp=fopen("highscore.txt","r");
        if(fp==NULL)
            printf("Cannot open file");
        else
        {
            fscanf(fp,"%d",&highest_score);
            fclose(fp);
            printf("prev highest score=%d\n",highest_score);
            if(point>=highest_score)
            {
                ishighest=1;
                fp=fopen("highscore.txt","w");
                fprintf(fp,"%d\n",point);

                highest_score=point;
                printf("new highest score=%d\n",highest_score);
                fclose(fp);
            }
            itoa(highest_score,highscore,10);

        }
        //printf("YOUR SCORE %d\n\n",point);
        //iText()


        // fscorename=fopen()

        // fclose(fp);

    }

    for(int ind=0; ind<enemynumber; ind++)
    {
        for( i=0; i<n; i++)
        {
            if(my_missile_x[i]>(e[ind].ex-5) && my_missile_x[i]<(e[ind].ex+eplanewidth+10) && my_missile_y[i]>(e[ind].ey-10) && my_missile_y[i]<(e[ind].ey+eplaneht+20))
            {
                e[ind].enemyshot=1;
//comment out frrom here to here
        // if(e[ind].enemytime>=50){
                //  e[ind].ex=l+10;
                 // e[ind].ey=rand()%(w-);
                 // e[ind].enemytime=0;
                  //e[ind].enemyshot=0;
                  //}
                //upto here

                my_missile_x[i]=l+1500;
                point+=50;


            }
        }
    }

    if(gulikhaise==1)
    {
        PlaySound("mygunshoot.wav",NULL,SND_ASYNC);
    }
}
*/
















char score_point[10];
char love[4];

//int write=0;

void iDraw()
{
    iClear();


    if(gamestate==-1)
    {

        if(musflag==1)
    {
        if(musicon==true)
        PlaySound("tense.wav", NULL,SND_ASYNC|SND_LOOP);
        else
            PlaySound(NULL,NULL,SND_SYNC);
        musflag=0;
    }
        iShowBMP(0,0,bg[bgind]);
        for (int i=1; i<5; i++)
        {
            if(i!=3)
                iShowBMP2(bcord[i].x,bcord[i].y,button[i],0);
            else
            {
                if(musicon==true)
                    iShowBMP2(bcord[3].x,bcord[3].y,button[3],0);
                else
                {
                    iShowBMP2(bcord[3].x,bcord[3].y,button[5],0);

                }


            }
        }
        if(resumestate==2)
        {
            iShowBMP2(bcord[0].x,bcord[0].y,button[0],0);
        }


        iPauseTimer(0);
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);

        iShowBMP(l-150,bottomht-20,"exitgame.bmp");



    }


    else if(gamestate==0)
    {
        iResumeTimer(1);
        iResumeTimer(2);
        iResumeTimer(3);
        iSetColor(255,rand()%255,rand()%255);

        itoa(point,score_point,10);
        itoa(lives,love,10);
        iText(l/2,bottomht/2,"SCORE:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(l/2+100,bottomht/2,score_point,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(l/4,bottomht/2,"LIVES:",GLUT_BITMAP_HELVETICA_18);
        iText(l/4+80,bottomht/2,love,GLUT_BITMAP_HELVETICA_18);
        iShowBMP(0,bottomht,bg[5]);
        if(resumestate==1)
        {
            iShowBMP2(l/4,w/2-100,"quit.bmp",0);
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);

        }

        /*for(i=0;i<10;i++){

            iShowBMP(upbg[i].x,upbg[i].y,upbgimage[i]);
        }*/
        if(resumestate==0 && gameover==0)
        {
            if(gulikhaise==0 && dhakkalgse==0)
            {
                /* iSetColor(200,200,0);

                 iFilledCircle(myx,myy,planewidth);

                 iFilledRectangle(myx-100,myy-planewidth-5,100,5);

                 iSetColor(255,0,0);*/
                iShowBMP2(myx,myy,"Alien.bmp",0);
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
                //if(musicon==true)
                //PlaySound("mylife.wav", NULL,SND_ASYNC);

                iShowBMP2(myx,myy,"Alien.bmp",0);
                iShowBMP2(myx+35,myy+myplaneht-10,"planeagunnn.bmp",255);

                for(i=0; i<n; i++)
                {
                    iFilledRectangle(my_missile_x[i],my_missile_y[i],5,5);
                }

                if(aftercollision>=50)
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

                    for (j=0; j<enemynumber; j++)
                    {

                        if(j!=i && e[i].ex>=e[j].ex-2*eplanewidth && e[i].ex<=(e[j].ex+2*eplanewidth) && e[i].ey>=e[j].ey-2*eplaneht && e[i].ey<=(e[j].ey+2*eplaneht))
                        {

                            e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;
                            //e[i].ex=e[i].ex



                        }
                    }


                    e[i].enemytime=0;
                    e[i].enemyshot=0;
                    e[i].collide=0;
                }

                if(e[i].enemytime>=50&& e[i].collide==1)
                {
                    e[i].ex=l+100;
                    e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;

                    for (j=0; j<enemynumber; j++)
                    {

                        if(j!=i && e[i].ex>=e[j].ex-2*eplanewidth && e[i].ex<=(e[j].ex+2*eplanewidth) && e[i].ey>=e[j].ey-2*eplaneht && e[i].ey<=(e[j].ey+2*eplaneht))
                        {

                            e[i].ey=rand()%(w-eplaneht-bottomht)+bottomht;



                        }
                    }





                    e[i].enemytime=0;
                    e[i].enemyshot=0;
                    e[i].collide=0;
                }

                int no=rand()%10;


                iShowBMP2(e[i].ex,e[i].ey,enemypic[no],0);

                if((e[i].enemyshot==1 || e[i].collide==1) && e[i].enemytime<=50 && e[i].ex>0)
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
             if(resetstate==1)
        {


            n=0;
            m1=1;
            lives=5;
            point=0;
            f2called=0;
            //saved=0;
            //nameind=0;

            for(i=0; i<enemynumber; i++)
            {
                e[i].collide=0;
                e[i].enemyshot=0;
                e[i].enemytime=0;
                e[i].ex=l+10;
                e[i].ey=(rand()%(w-eplaneht-bottomht))+bottomht;

            }
            gameover=0;
            gulikhaise=0;
            dhakkalgse=0;
            enemynumber=3;

            aftercollision=0;
            ishighest=0;
//        write=0;
            saved=0;
            nameind=0;
            resetstate=0;
             for (int ind=0; ind<enemynumber; ind++)
    {


                e[ind].e_bullet[m1-1].x=e[ind].ex;
                e[ind].e_bullet[m1-1].y=e[ind].ey+eplaneht-5;



    }
        }

        }
        iSetColor(rand()%256,rand()%256,rand()%256);
        if(gameover==1)
        {
            iShowBMP(0,0,bg[1]);
            //iSetColor(rand()%55+200,rand()%155+100,rand()%100);
            iSetColor(255,50,20);
            // iText(l/2,w/2,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(l/2-250,w/2-100,"YOUR SCORE IS",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(l/2+150,w/2-100,score_point,GLUT_BITMAP_TIMES_ROMAN_24);
            iText(l/2-250,w/2-200,"HIGHEST SCORE:",GLUT_BITMAP_TIMES_ROMAN_24);
            iText(l/2+150,w/2-200,highscore,GLUT_BITMAP_TIMES_ROMAN_24);

            iSetColor(255,rand()%200,rand()%50);
            iText(name_box.x-150,name_box.y+5,"Player's Name: ");
            iSetColor(255,255,255);
            iFilledRectangle(name_box.x,name_box.y,300,25);
//            write=1;
            iSetColor(0,0,0);
            // printf("checking:%c\t%d",playername[nameind],write);
            iText(name_text.x,name_text.y,playername);
            /* iSetColor(255,0,0);
             printf("player's name=%s\n",playername);
             iText(l/4,w-200,playername);
             iText(l/4+200,w-200,"scored");
             iText(l/4+300,w-200,score_point);*/
            //iText()
            if(ishighest==1)
            {
                iText(l/2-200,w/2-300,"CONGRATULATIONS!!YOU HAVE SCORED HIGHEST");
            }
            /* if(hall_of_fame_called==0)
             {
                 printf("player's name=%s\n",playername);
                 hall_of_fame();

             }*/


            // iShowBMP(l-200,bottomht-20,"savebutton.bmp");
            //if(saved==1 && hall_of_fame_called==0)
            //{
            //  fclose(fileofname);
            // hall_of_fame_called=1;
            //name_box.x=l+200;
            //name_text.x=l+200;
            //hall_of_fame();

            //}
            iShowBMP(savebutton.x,savebutton.y,"savebutton.bmp");
            if(saved==1 && hall_of_fame_called==0)
            {
                fclose(fileofname);
                hall_of_fame_called=1;
                name_box.x=l+200;
                name_text.x=l+200;
                savebutton.x=l+200;
                hall_of_fame();

            }
            iShowBMP(l-150,bottomht-20,"exitgame.bmp");

        }
        if(gameover==0)

        {
            iShowBMP(l-150,bottomht-50,"exitgame.bmp");
        }

    }


    else if(gamestate==1)
    {
        iSetColor(rand()%255,rand()%255,rand()%255);
        iText(500,300+50,"Settings menu under development");
        iText(500,300+25,"Instructions to play this game: ");
        iText(500,300-50,"Use Keyboard navigation button to move your plane");
        iText(500,300-50-25,"Use mouse to click menu");
        iShowBMP(l-150,bottomht-20,"exitgame.bmp");
    }
    if(gamestate!=(-1))
    {
        iShowBMP2(backcordx,backcordy,"back.bmp",0);

    }


}

void iMouseMove(int mx,int my)
{

}





int name_file_opened=0;



void iKeyboard(unsigned char key)
{
    if(key==' ' && gamestate==0)
    {
        iResumeTimer(0);
        n++;
        my_missile_x[n-1]=myx+planewidth;
        my_missile_y[n-1]=myy+myplaneht/2-10;
        if(musicon==true)
            PlaySound("gunshot.wav", NULL,SND_ASYNC);
    }
    if(key=='\b' && gamestate==0 && gameover==0)
    {
        resumestate=1;
    }


    if(gameover==1)
    {


        if(name_file_opened==0)
        {
            fileofname=fopen("name.txt","w");
            name_file_opened=1;
        }

        // printf("saved=%d\n",saved);
        if(saved==1)
        {
            hall_of_fame();
            printf("from saved=1\n",saved);
            fclose(fileofname);
        }

        if(saved==0)
        {
            if(key!='\b')
            {
                if(((key>='A' && key<='Z')||(key>='a' && key<='z') || (key>='0' && key<='9')||(key==' ') ))
                {
                    playername[nameind]=key;
                    fputc(key,fileofname);
                    // printf("checking:%c\t%d",playername[nameind],write);
                    nameind++;
                    playername[nameind]='\0';

                    if(musicon==true)
                    {

                        PlaySound("select.wav",NULL,SND_ASYNC);
                    }
                }
                //else{
                //write=0;
                //}

            }
            else if(key=='\b')
            {
                fputc(key,fileofname);
                if(musicon==true)
                {

                    PlaySound("select.wav",NULL,SND_ASYNC);
                }

                if(nameind<=0)
                {
                    nameind=0;
                }
                else
                {
                    nameind--;
                    playername[nameind]='\0';
                }
            }
        }

        //fprintf(fileofname,"\n");



    }




}


void iMouse(int button,int state,int mx,int my)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        for ( i=0; i<5; i++)
        {
            if(i!=3 && i!=0)
            {

                if(mx>=bcord[i].x+1 && mx<=(bcord[i].x+149)&& my>=bcord[i].y+1 && my<=bcord[i].y+30)
                {

                    if(gamestate==-1)
                    {
                        gamestate=i-1;
                        if(i==1)
                            {resetstate=1;
                            resumestate=0;
                            }
                        if(musicon==true)
                            PlaySound("select.wav", NULL,SND_ASYNC);
                    }
                }
            }
            else if(i==3)
            {
                if(mx>=bcord[i].x+1 && mx<=(bcord[i].x+149)&& my>=bcord[i].y+1 && my<=bcord[i].y+30)
                {
                    if(musicon==true)
                    {
                        musicon=false;
                        PlaySound("select.wav", NULL,SND_ASYNC);
                    }
                    else{
                        musicon=true;

                    }
                    musflag=1;
                }

            }
            else
            {
                if(mx>=bcord[0].x+1 && mx<=(bcord[0].x+149)&& my>=bcord[0].y+1 && my<=bcord[0].y+30)
                {

                gamestate=0;
                resumestate=0;
                PlaySound("select.wav", NULL,SND_ASYNC);
            }}


        }

        for ( i=0; i<2; i++)
        {
            if(mx>=rcord[i].x && mx<=(rcord[i].x+175)&& my>=rcord[i].y && my<=rcord[i].y+65)
            {
                if(gamestate==0 && resumestate==1)
                {
                    gamestate=i-1;
                    resumestate=0;
                    if(musicon==true)
                        PlaySound("select.wav", NULL,SND_ASYNC);
                }
            }


        }


        if((gameover==1 || gamestate!=0) && mx>=l-150 && mx<=(l-15) && my>=(bottomht-20) && my<=(bottomht+30) )
        {
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_SYNC);
            exit(0);
        }

        if(gameover==0 && gamestate==0 && mx>=l-150 && mx<=(l-15) && my>=(bottomht-50) && my<=(bottomht))
        {
            resumestate=1;
            iShowBMP2(l/4,w/2-100,"quit.bmp",0);
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_ASYNC);


        }

        if((gameover==1 || gamestate!=0) && mx>=l-200 && mx<=(l-150) && my>=(bottomht-20) && my<=(bottomht+30)&& saved==0)
        {
            saved=1;
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_ASYNC);
            savebutton.x=l+200;


        }
        if(gamestate!=-1 && mx>=backcordx && mx<=backcordx+50 && my>=backcordy && my<=backcordy+50)
        {
            if(gamestate==0)
            {
                resumestate=2;

            }
            gamestate=-1;
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_SYNC);
        }

    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        for ( i=0; i<5; i++)
        {
            if(i!=3 && i!=0)
            {

                if(mx>=bcord[i].x+1 && mx<=(bcord[i].x+149)&& my>=bcord[i].y+1 && my<=bcord[i].y+30)
                {

                    if(gamestate==-1)
                    {
                        gamestate=i-1;
                        if(i==1)
                            {resetstate=1;
                            resumestate=0;
                            }
                        if(musicon==true)
                            PlaySound("select.wav", NULL,SND_ASYNC);
                    }

                }
            }
            else if(i==3)
            {
                if(mx>=bcord[i].x+1 && mx<=(bcord[i].x+149)&& my>=bcord[i].y+1 && my<=bcord[i].y+30)
                {
                    if(musicon==true)
                    {
                        musicon=false;

                        PlaySound("select.wav", NULL,SND_ASYNC);
                    }
                    else{
                        musicon=true;

                    }
                    musflag=1;
                }

            }
            else
            {
                if(mx>=bcord[0].x+1 && mx<=(bcord[0].x+149)&& my>=bcord[0].y+1 && my<=bcord[0].y+30)
                {

                gamestate=0;
                resumestate=0;
                PlaySound("select.wav", NULL,SND_ASYNC);
            }}


        }

        for ( i=0; i<2; i++)
        {
            if(mx>=rcord[i].x && mx<=(rcord[i].x+175)&& my>=rcord[i].y && my<=rcord[i].y+65)
            {
                if(gamestate==0 && resumestate==1)
                {
                    gamestate=i-1;
                    resumestate=0;
                    if(musicon==true)
                        PlaySound("select.wav", NULL,SND_ASYNC);
                }
            }


        }


        if((gameover==1 || gamestate!=0) && mx>=l-150 && mx<=(l-15) && my>=(bottomht-20) && my<=(bottomht+30) )
        {
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_SYNC);
            exit(0);
        }

        if(gameover==0 && gamestate==0 && mx>=l-150 && mx<=(l-15) && my>=(bottomht-50) && my<=(bottomht))
        {
            resumestate=1;
            iShowBMP2(l/4,w/2-100,"quit.bmp",0);
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_ASYNC);


        }

        if((gameover==1 || gamestate!=0) && mx>=l-200 && mx<=(l-150) && my>=(bottomht-20) && my<=(bottomht+30)&& saved==0)
        {
            saved=1;
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_ASYNC);
            savebutton.x=l+200;


        }
        if(gamestate!=-1 && mx>=backcordx && mx<=backcordx+50 && my>=backcordy && my<=backcordy+50)
        {
            if(gamestate==0)
            {
                resumestate=2;

            }
            gamestate=-1;
            if(musicon==true)
                PlaySound("select.wav", NULL,SND_SYNC);
        }

    }
}

//int planewidth=100;

void iSpecialKeyboard(unsigned char key)
{
    if(gameover==1 && key==GLUT_KEY_END)
    {
        exit(0);
    }

    if(gameover==0 && gamestate==0 && resumestate==0)
    {
        if(key==GLUT_KEY_LEFT && myx>=5)
        {
            myx-=10;
            //if(myx<=planewidth)
            //{
            // myx=l-planewidth;
            //}
        }
        if(key==GLUT_KEY_RIGHT && myx<=l-planewidth)
        {
            myx+=10;
            //if(myx>=l-planewidth)
            //{
            // myx=planewidth;
            // }
        }

        if(key==GLUT_KEY_UP && myy<=w-myplaneht-10)
        {
            myy+=10;
        }
        if(key==GLUT_KEY_DOWN && myy>=bottomht)
        {
            myy-=10;
        }
    }

}





void setall()
{
    //nameind=0;***************************
    int sum=0;
    /*for(i=0; i<10; i++)
    {

        upbg[i].y=0;
        upbg[i].x=sum;

        sum=sum+eachbgwidth;
    }*/

    name_box.x=3*l/4;
    name_box.y=bottomht+200;
    name_text.x=name_box.x+20;
    name_text.y=name_box.y+5;

    savebutton.x=l-200;
    savebutton.y=bottomht-20;




    int i;
    int summ=w/6;
    int increase=0;
    for (i=4; i>=0; i--)
    {
        bcord[i].x=l/8;
        bcord[i].y=summ;
        summ+=45;
    }
    for(i=0; i<2; i++)
    {
        rcord[i].x=l/4+60+increase;
        rcord[i].y=w/2-100;
        increase+=205;


    }
    for(j=0; j<100000; j++)
    {
        my_missile_x[j]=myx;
        my_missile_y[j]=myy;
    }

    enemy_movement();
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
    // PlaySound("airplanerunning.wav",NULL,SND_ASYNC|SND_LOOP);
    iSetTimer(1,my_bullet_movement);
    iPauseTimer(0);
    iSetTimer(10,enemy_movement);
    iSetTimer(1,enemy_bullet_movement);
    iSetTimer(2000,enemy_bullet_position);
    iSetTimer(1,collision);

    // iSetTimer(50,renderbg);
    //PlaySound(TEXT("bgmusic.wav"),NULL,SND_ASYNC | SND_LOOP);
    iInitialize(l,w,"FIGHTER PLANE");


    return 0;
}
