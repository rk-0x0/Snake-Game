
#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

int x,y,state,st,score;
int t;

class node
{  public:
    int j,k,p,q;
    node *next,*prev;
};
void new_prey();
class S
{  public:
    node *head,*tail;

    S()
    {
        head=new node;
        tail=new node;

        head->p=head->j=60;
        head->q=head->k=40;

        tail->p=tail->j=60;
        tail->p=tail->k=20;

        head->next=tail;
        tail->prev=head;
        tail->next=NULL;
        head->prev=NULL;
    }

void erase(int m,int n)
{
    glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);
        glVertex2i(m-10,n+10);
        glVertex2i(m-10,n-10);
        glVertex2i(m+10,n-10);
        glVertex2i(m+10,n+10);
        glEnd();
}

void redraw(int m,int n)
{
    glBegin(GL_QUADS);
     glVertex2i(m-10,n+10);
     glVertex2i(m-10,n-10);
     glVertex2i(m+10,n-10);
     glVertex2i(m+10,n+10);
    glEnd();
}

bool checkStrangled(int x, int y)
{
    int p[3];
    glReadPixels
        (
        x,y,
        1, 1,
        GL_RGB, GL_INT,
        &p[0]
        );

     p[0]=p[0]/2147483647;
     p[1]=p[1]/2147483647;
     p[2]=p[2]/2147483647;

      if(p[0]==0 && p[1]==1 && p[2]==1)
        return true;



return false;
}
void snake()
{    node* temp;
     bool b;
     int i=1,f=0;
     temp=head;
    while(temp!=NULL)
     {
       if(temp->next!=NULL)
       {
           temp->next->p=temp->j;
           temp->next->q=temp->k;
       }

      if(temp->next==NULL)
        erase(temp->j,temp->k);

      if(temp->j<10 || temp->j>590 || temp->k<10 || temp->k>590)
      {
        cout<<"\n Crashed with wall \n!!!  Game Over !!!\n\n"<<"\n   Score : "<<score*10<<endl;
        exit(0);
      }

        if(temp==head)
        {
        if(state==1 )
        temp->q +=20;
        else if(state==2 )
        temp->q -=20;
        else if(state==3)
        temp->p -=20;
        else if(state==4)
       temp->p +=20;
        }
    //redraw
        if(temp==head)
        {
            b=checkStrangled(temp->p,temp->q);
            if(b)
            {
                cout<<"\n\tStrangled\n !!!  Game Over !!!\n\n"<<"\n\tScore : "<<score*10<<endl;
                exit(0);
            }
        }
        glColor3f(0.0,1.0,1.0);
        if(temp==head)
            glColor3f(1.0,0.0,1.0);

        redraw(temp->p,temp->q);



        temp->j=temp->p;
        temp->k=temp->q;

    //prey_Eaten_Or_Not
        if(temp->p==(x+10) && temp->q==y-10)
        {   ++score;
           new_prey();
           t=t-2;
           if(t<20)
           {
               cout<<"Congrats! You have completed the challange\n"<<"\tScore : "<<score;
               exit(0);
           }
           f=1;
        }

        glFlush();
        temp=temp->next;
    }

//new node
if(f==1)
    {
       node* temp1 = new node;
       temp1->j=tail->j;
       temp1->k=tail->k;
       temp1->p=tail->p;
       temp1->q=tail->q;
       temp1->next=NULL;
       tail->next=temp1;
       tail=temp1;

    }
f=0;
}
};

S saap;

void Timer(int value)
{
   saap.snake();
   glutTimerFunc(t, Timer, 0); // next Timer call milliseconds later
}

void boundry()
{
    //glClearColor(0.0,0.0,0.0,0.0);
   // glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_QUADS);
    //leftWall
     glVertex2f(0.0,0.0);
     glVertex2f(10.0,0.0);
     glVertex2f(10.0,600.0);
     glVertex2f(0.0,600.0);
    //downWall
     glVertex2f(0.0,0.0);
     glVertex2f(0.0,10.0);
     glVertex2f(600.0,10.0);
     glVertex2f(600.0,0.0);
    //rightWall
     glVertex2f(590.0,0.0);
     glVertex2f(600.0,0.0);
     glVertex2f(600.0,600.0);
     glVertex2f(590.0,600.0);
    //topWall
     glVertex2f(600.0,600.0);
     glVertex2f(600.0,590.0);
     glVertex2f(0.0,590.0);
     glVertex2f(0.0,600.0);

    glEnd();

/*    for(int i=30;i<590;i=i+20)
    {
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
         glVertex2i(i,10);
         glVertex2i(i,590);
        glEnd();
    }
    for(int j=10;j<590;j=j+20)
    {
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINES);
         glVertex2i(10,j);
         glVertex2i(590,j);
        glEnd();
    }*/

    glFlush();
}


void checkNext(int ch,int &x,int &y)
{
    switch(ch)
    {
    case 1:
        x=30;y=40;
        break;
    case 2:
        x=30;y=570;
        break;
    case 3:
        x=570;y=40;
        break;
    case 4:
        x=570;y=570;
    default:
        x=300;y=300;
        break;
    }
}


void new_prey()
{
  //boundry();
  int i=1;
  bool b=true;

    x= rand() % 590  + 10;
    y= rand() % 590 + 10;

   if(x>=590 || x<=10)
        x=40;
    if(y<=10 || y>=590)
        y=40;


   do
   {
       b= saap.checkStrangled(x,y);
       if(b)
       {
           checkNext(i,x,y);
           i++;
       }

   }
    while(b);

    x=x- ((x-10)%20);
    y=y+ ((590-y)%20);

   glColor3f(0.0,1.0,0.0);
   glBegin(GL_QUADS);
      glVertex2i(x,y);
      glVertex2i(x+20,y);
      glVertex2i(x+20,y-20);
      glVertex2i(x,y-20);
    glEnd();
    glFlush();


}



void my_display()
{

}
void my_reshape(GLsizei x,GLsizei y)
{
    glutReshapeWindow(600,600);
}
void my_keyboard(int key, int x, int y)
{
   switch(key)
   {

   case  GLUT_KEY_UP:
    state=1;
    break;
   case GLUT_KEY_DOWN:
    state=2;
    break;
   case GLUT_KEY_LEFT:
    state=3;
    break;
   case GLUT_KEY_RIGHT:
    state = 4;
    break;
   case 27:
    exit(0);
    break;
   default:
    break;

   }
   //glutPostRedisplay();
}

void myinit()
{
    srand (time(NULL));
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,0,600);
   glClearColor(0.0,0.0,0.0,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   boundry();
    new_prey();
    state=1;
    t=150;
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Snake");

    glutDisplayFunc(my_display);
    glutReshapeFunc(my_reshape);
    glutSpecialFunc(my_keyboard);
    myinit();
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();

    return 0;
}

