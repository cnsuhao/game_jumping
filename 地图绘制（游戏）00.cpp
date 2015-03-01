#define screenc  600
#define screenk  480
#define aspectlong 600
#include "stdio.h"
#include <windows.h>
#include <gl/glut.h>
#include <vector>
using std::vector;
FILE *fileaa;
FILE *fileee;
int xx,yy;
int xx2,yy2;
int lenn;
int aspect=0;
vector<int> mapdata(2,0);
void myInit(void)
{
     glClearColor(0.0,0.0,0.0,0.0);
     glPointSize(1.0);
     glColor3f(0.5f,0.5f,0.4f);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,screenc,0.0,screenk);
     fileaa=fopen(".\\map00.mmp","rb+");
     if(fileaa)
       fclose(fileaa);
     else{
       fileaa=fopen(".\\map00.mmp","wb+");
       fclose(fileaa);
     }
}
void myDisplay(void)
{
     glClear(GL_COLOR_BUFFER_BIT);
    fileee=fopen(".\\map00.mmp","rb");
    fseek(fileee,0,SEEK_END);
    lenn=ftell(fileee)/8;
    fseek(fileee,0,SEEK_SET);  
    
    for(int i=1;i<=lenn;++i)
    { 
      fread(&xx,4,1,fileee);
      fread(&yy,4,1,fileee);
      if(xx>=aspect*aspectlong&&xx<aspect*aspectlong+screenc)
      {
            glBegin(GL_POINTS);
                glVertex2i(xx-aspect*aspectlong,yy);
            glEnd();
      }
    }
    fclose(fileee);
    glFlush();
}
void myIdle(void)
{
       myDisplay();
}
void mouse22(int x,int y)
{
    fileaa=fopen(".\\map00.mmp","ab+");
    xx=x+aspect*aspectlong;
    yy=screenk-y;
    fwrite(&xx,4,1,fileaa);
    fwrite(&yy,4,1,fileaa);
    fclose(fileaa);
}
void keydown(unsigned char t,int x,int y)
{     
    vector<int>::iterator mapN;
    mapN=mapdata.begin();
    long lennnnn;
    FILE* map;
    int xt,yt;
    if(t=='a')
    {if(aspect>0)
           aspect-=1;
    }
     else if(t=='d')
     {   if(aspect<10)
           aspect+=1;
    }
     else if(t==27)
    {
        map=fopen(".\\map00.mmp","rb");
        fseek(map,0,SEEK_END);
        lennnnn=ftell(map)/8;
        fseek(map,0,SEEK_SET);   
        for(int i=1, k=0;i<=lennnnn;++i,mapN+=2)
        {
            fread(&xt,4,1,map);
            fread(&yt,4,1,map);
            if((mapN+2)!=mapdata.end()&&k==0)
            {           
                *mapN=xt;
                *(mapN+1)=yt;       
            }else{
                k=1;
                mapdata.push_back(xt);
                mapdata.push_back(yt);
            }
        }
        for(int i=2;i<=lennnnn;++i)
        {
            mapN=mapdata.begin();
            for(int k=2;k<=lennnnn;++k,mapN+=2)
            {
                if(*(mapN+2)<=*mapN)
                {
                    xt=*mapN;
                    *mapN=*(mapN+2);
                    *(mapN+2)=xt;
                    yt=*(mapN+1);
                    *(mapN+1)=*(mapN+3);
                    *(mapN+3)=yt;
                }
            }
        }
        fclose(map);
        map=fopen(".\\map00.mmp","wb+");
        for(mapN=mapdata.begin();mapN!=mapdata.end();mapN+=2)
        {
            xt=*mapN;
            yt=*(mapN+1);
            fwrite(&xt,4,1,map);
            fwrite(&yt,4,1,map);
        }
        fclose(map);
        exit(0);
    }
}
int main(int argc,char ** argv)
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowSize(screenc,screenk);
     glutInitWindowPosition(0,0);
     glutCreateWindow("my first attempt");
     glutDisplayFunc(&myDisplay);
     glutIdleFunc(&myIdle);
     glutKeyboardFunc(&keydown);
     glutMotionFunc(&mouse22);
     
     myInit();
     glutMainLoop();
     return 0;
}
     
