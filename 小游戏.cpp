#define screenc  600
#define screenk  480
#define headwidth 5
#define headhigh 4
#define screenwidth 1800
#define screenhigh 760
#define bodylong 15
#define yaolong 5
#define jiaolong 2
#include "stdio.h"
#include <windows.h>
#include <gl/glut.h>
#include <vector>
using std::vector;
vector<int> mapdata(100,0);
short abb[7]={0,0,0,0,0,0,0}; 
int list;
float x=10,y=bodylong+50,h=0,sx=0,sy=0;
float gy=0,gy2;
float vy=6,Gg=0.5;
void analyze(void);
int aspect=0;
FILE* map;
long lennnnn;

void startpicture(void);

void getmap(void)
{
    int x,y;
    vector<int>::iterator mapN;
    mapN=mapdata.begin();
    switch(aspect)
    {
        case 0:
            map=fopen(".\\map\\map0.mmp","rb");
            break;
        case 2:
            map=fopen(".\\map\\map1.mmp","rb");           
            break;
        case 4:
            map=fopen(".\\map\\map2.mmp","rb");
            break;
        case 6:
            exit(0);
    }
    if(map&&(aspect==0||aspect==2||aspect==4))
    {
        fseek(map,0,SEEK_END);
        lennnnn=ftell(map)/8;
        fseek(map,0,SEEK_SET);   
        for(int i=1, k=0;i<=lennnnn;++i,mapN+=2)
        {
            fread(&x,4,1,map);
            fread(&y,4,1,map);
            if((mapN)!=mapdata.end()&&k==0)
            {           
                *mapN=x;
                *(mapN+1)=y;        
            }else{
                k=1;
                mapdata.push_back(x);
                mapdata.push_back(y);
            }
        }
        fclose(map);
        aspect+=1;
    }else if(aspect==0||aspect==2||aspect==4)
        exit(0);  

}
void getlist(void)
{
     list=glGenLists(11);
     glNewList(list, GL_COMPILE);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
           glVertex2i(-headwidth,headhigh);
           glVertex2i(headwidth,headhigh);
           glVertex2i(headwidth,-headhigh);
           glVertex2i(-headwidth,-headhigh);
        glEnd();   
      glEndList();  
      glNewList(list+1, GL_COMPILE);  
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
           glVertex2i(-headwidth/2,-headhigh);
           glVertex2i(-headwidth/2,-bodylong);
           glVertex2i(headwidth/2,-headhigh);
           glVertex2i(headwidth/2,-bodylong);
        glEnd();
     glEndList();
     glNewList(list+2,GL_COMPILE);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINES);
           glVertex2i(-headwidth/2,-headhigh);
           glVertex2i(-headwidth/2-2,-bodylong);
           glVertex2i(headwidth/2,-headhigh);
           glVertex2i(headwidth/2+2,-bodylong);
        glEnd();     
     glEndList();
} 
void myInit(void)
{
     glutIgnoreKeyRepeat(-1);
     glClearColor(0.0,0.0,0.0,0.0);
     glPointSize(4.0);
     glColor3f(0.5f,0.5f,0.4f);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,screenc,0.0,screenk);
     getlist();
     //getmap();
}
void myDisplay(void)
{
    static int tiee=0;
    int len=1;
    if(aspect==0||aspect==2||aspect==4)
        startpicture();
    getmap();
    glPointSize(2.0);    
    glClear(GL_COLOR_BUFFER_BIT);
    analyze();
    glBegin(GL_POINTS);
    for(vector<int>::iterator mapN=mapdata.begin();(mapN)!=mapdata.end()&&len<=lennnnn;mapN+=2,++len)
    {
        if(*mapN>=sx&&*mapN<=sx+screenc)
             glVertex2i(*mapN-(int)sx,*(mapN+1));
        if(*mapN>sx+screenc)
             break;
    }
    glEnd();
    if(aspect==1||aspect==5)
    {
        glLineWidth(2.0);
        glColor3f(1.0,0,0);
        glBegin(GL_LINE_LOOP);
           glVertex2i(1720-(int)sx,70);
           glVertex2i(1720-(int)sx,50);
           glVertex2i(1770-(int)sx,50);
           glVertex2i(1770-(int)sx,70);
        glEnd();
    }else if(aspect==3)
    {
        glLineWidth(2.0);
        glColor3f(1.0,0,0);
        glBegin(GL_LINE_LOOP);
           glVertex2i(20-(int)sx,470);
           glVertex2i(20-(int)sx,450);
           glVertex2i(70-(int)sx,450);
           glVertex2i(70-(int)sx,470);
        glEnd();
    }
    glTranslatef(x-sx,y+sy,0.0);
    glCallList(list);
    if((tiee%20<10))
     glCallList(list+1);
    else
     glCallList(list+2);
    glTranslatef(-x+sx,-y-sy,0.0);
    glutSwapBuffers();
    Sleep(20);
    if(tiee==20)
        tiee=0;
    else if(abb[0]==1||abb[1]==1||abb[2]==1)
        tiee+=1;
}
void analyze(void)
{
    int bigy=0;
    int bigy2=0;
    int bigy3=0;
    int jy=1;
    int xxx=0;
    static float t=vy/Gg+1; 
    if(abb[2]==1&&t==vy/Gg+1&&abb[3]==0)
    {
        abb[3]=1;
        t=0;
    } 
    gy=vy-Gg*t;   
    for(vector<int>::iterator mapN=mapdata.begin();(mapN)!=mapdata.end()&&jy<=lennnnn;mapN+=2,++jy)
    {
        if(*mapN>x+12)
        {
                break;
        }else if(*mapN>=x-12&&*mapN<=x+12)
        {
            if(*mapN>=x-10)
            {
                if(*(mapN+1)<=y&&*(mapN+1)>=y-bodylong&&bigy2!=-1)
                {
                    if(*(mapN+1)>y-0.5*bodylong)
                         bigy2=-1;
                    else if(*(mapN+1)>=bigy2)
                         bigy2=*(mapN+1);
                }
            }
            if(*mapN<=x+10)
            {
                if(*(mapN+1)<=y&&*(mapN+1)>=y-bodylong&&bigy3!=-1)
                {
                    if(*(mapN+1)>y-0.5*bodylong)
                         bigy3=-1;
                    else if(*(mapN+1)>=bigy3)
                         bigy3=*(mapN+1);
                }           
            }
            if(*mapN>=x-10&&*mapN<=x+10)
            {  
                if(*(mapN+1)>=y+gy-bodylong&&*(mapN+1)<=y-bodylong&&*(mapN+1)>=bigy)
                   bigy=*(mapN+1);
                else if(*(mapN+1)<=y+gy+headhigh&&*(mapN+1)>=y+headhigh&&xxx!=-1)
                {
                    t=vy/Gg+1;
                    xxx=-1;
                }            
            }
        }
    }   
    if(bigy==0)
    {
           y+=gy;
           t+=1;
    }else{
           abb[3]=0;
           y=bigy+bodylong;
        
        t=vy/Gg+1;
    }    
     if(abb[0]==1&&bigy3>=0)
    {    
        if(x>2+headwidth)
        {
            x-=2;
            if(bigy3!=0&&bigy3>=bigy&&abb[2]!=1)
            {
                   y=bigy3+bodylong;
            }
            if(x-sx<(screenc)/3&&sx>2)
                sx-=2;
        }
    }
    if(abb[1]==1&&bigy2>=0)
    {
        if(x<screenwidth-headwidth-2)
        {
            x+=2;
            if(bigy2!=0&&bigy2>=bigy&&abb[2]!=1)
            {     
                    y=bigy2+bodylong;
            }
            if(x-sx>(screenc)/3*2&&sx<screenwidth-screenc)
                 sx+=2;
        }  
    }
    if((aspect==1||aspect==5)&&x>1720&&x<1770&&y>50-headhigh&&y<70+bodylong)
        aspect+=1;
    else if(aspect==3&&x>20&&x<70&&y>450-headhigh&&y<470+bodylong)
        aspect+=1; 
}
void myIdle(void)
{
    myDisplay();
}
void keyup(unsigned char t,int x,int y)
{
     if(t=='a')
        abb[0]=0;
     else if(t=='d')
        abb[1]=0;
     else if(t=='w')
        abb[2]=0;
}
void keydown(unsigned char t,int x,int y)
{     
     if(t=='a')
        abb[0]=1;
     else if(t=='d')
        abb[1]=1;
     else if(t=='w')
     {
            abb[2]=1;
            abb[3]=0;
     }
     else if(t==27)
     {      
        exit(0);
     } 
}
void startpicture(void)
{
    long lenn;
    FILE *fileee;
    int xx,yy;
    glClear(GL_COLOR_BUFFER_BIT);
    fileee=fopen(".\\map\\map00.mmp","rb");
    fseek(fileee,0,SEEK_END);
    lenn=ftell(fileee)/8;
    fseek(fileee,0,SEEK_SET);  
    glColor3f(0.5,0.5,0.5);
    glPointSize(4.0);
    for(int i=1;i<=lenn;++i)
    { 
      fread(&xx,4,1,fileee);
      fread(&yy,4,1,fileee);
            glBegin(GL_POINTS);
                glVertex2i(xx,yy);
            glEnd();
    }
    fclose(fileee);
    glutSwapBuffers();
    Sleep(1000);
}
int main(int argc,char ** argv)
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
     glutInitWindowSize(screenc,screenk);
     glutInitWindowPosition(100,50);
     glutCreateWindow("Ð¡ÓÎÏ·");
     glutDisplayFunc(&myDisplay);
     glutIdleFunc(&myIdle);
     glutKeyboardFunc(&keydown);
     glutKeyboardUpFunc(&keyup);  
     myInit();
     glutMainLoop();
     return 0;
}
