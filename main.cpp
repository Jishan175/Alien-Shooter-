#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<windows.h>
#include<mmsystem.h>
#include<sstream>
#include <iostream>
#include <fstream>
#include "imageloader.h"
#include "imageloader.cpp"

using namespace std;
void sound_Control(int value);
void update(int value);
void pause();
void playerBullet();
void updatePlayerBullet(int value);
void check(float x1, float x2);
void enemycheck();
void enemyKill();
int enemy1_injured=0;
int enemy2_injured=0;
int enemy3_injured=0;
void updatePlayer(int value);
void optionbox();
void showHighScore();
void drawScene();
void startgame();
void lifeColor();
float alienoneBulletPosition;
int player_injury=0;
float alientwoBulletPosition;
float alienthreeBulletPosition;
float playerPositionx1;
float playerPositionx2;
float enemyonePositionx1;
float enemyonePositionx2;
float player_bulletposition=0.0f;
float current_score=0.0f;
int pausecontroll=0;

float enemytwoPositionx1;
float enemytwoPositionx2;

float enemythreePositionx1;
float enemythreePositionx2;
int sound_control_flag=0;
float _move = 0.0f;
GLuint _textureId;
float bullet_move = 0.0f;
float playerbullet_move=0.0f;
float Hero_move = 0.0f;
int width=640,height=600;
char exittext[] = "Exit Game";
char playerlife[] ="Life ";
char starttext[] = "Start Game";
char highscoretext[] = "High Score";
char continuetext[] = "Continue Game";
char gametitle[] = "Alien Shooter";
char score[] = "Score";
char highScore[] = "High Score";
char backbtn[] = "Back";
char gameOver[]="Game Over";
char gameWin[]="WIN !";
char howtoplay[]="How To Play";
char manual[]="Use left & Right arrow to move the player";
char manual2[]="Press esc to pause the game";
double game_score=1;
float game_high_score;
int mouseX = 0, mouseY = 0;

float getX(int val)
{
    return (float)val/(width/2);
}
float getY(int val)
{
    return (float)val/(height/2)+0.9f;
}




void resize(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow(640, 600);
}

void options( float x, float y, char *st)
{
  glutReshapeFunc(resize);


    sound_control_flag=0;
    int l,i;
    l=strlen( st ); // see how many characters are in text string.
    glColor3f(1.0,1.0,1.0);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }



}




void scoreCalculator( float x, float y, char *st)
{

    int l,i;
    l=strlen( st ); // see how many characters are in text string.
    glColor3f(1.0,1.0,1.0);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }



}


void playerLife(float c1,float c2, float c3){

    glColor3f (c1,c2,c3);
    glBegin(GL_POLYGON);
    glVertex2f(getX(140),getY(-540));
    glVertex2f(getX(140),getY(-525));
    glVertex2f(getX(100),getY(-525));
    glVertex2f(getX(100),getY(-540));
    glEnd();

    glFlush();


}


void optionbox(){

     glClear(GL_COLOR_BUFFER_BIT);
     glColor3d(1,0,0);
     glLoadIdentity(); //Reset the drawing perspective
     glMatrixMode(GL_MODELVIEW);

     glColor3f (0.3, 0.2,0.8);
     glBegin(GL_POLYGON);
     glVertex2f(getX(150),getY(-75));
     glVertex2f(getX(150),getY(-15));
     glVertex2f(getX(-190),getY(-15));
     glVertex2f(getX(-190),getY(-75));
     glEnd();


    glPushMatrix();
    options(-.24,0.74,gametitle);
    glPopMatrix();


    glColor3f (0, 1.0,0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-145));
    glVertex2f(getX(100),getY(-95));
    glVertex2f(getX(-140),getY(-95));
    glVertex2f(getX(-140),getY(-145));
    glEnd();

    glPushMatrix();
    options(-.19,0.48,starttext);
    glPopMatrix();


    glColor3f (0.6,0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-215));
    glVertex2f(getX(100),getY(-165));
    glVertex2f(getX(-140),getY(-165));
    glVertex2f(getX(-140),getY(-215));
    glEnd();

    glPushMatrix();
    options(-.25,0.23,continuetext);
    glPopMatrix();

    glColor3f (0.3, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-285));
    glVertex2f(getX(100),getY(-235));
    glVertex2f(getX(-140),getY(-235));
    glVertex2f(getX(-140),getY(-285));
    glEnd();

    glPushMatrix();
    options(-.21,0.021,highscoretext);
    glPopMatrix();

    glColor3f (0.8, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-355));
    glVertex2f(getX(100),getY(-305));
    glVertex2f(getX(-140),getY(-305));
    glVertex2f(getX(-140),getY(-355));
    glEnd();

    glPushMatrix();
    options(-.19,-0.22,exittext);
    glPopMatrix();



    glColor3f (0.3, 0.8, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-425));
    glVertex2f(getX(100),getY(-375));
    glVertex2f(getX(-140),getY(-375));
    glVertex2f(getX(-140),getY(-425));
    glEnd();

    glPushMatrix();
    options(-.19,-0.45,howtoplay);
    glPopMatrix();

    glutSwapBuffers();
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void initialize() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.00, 1.0, 200.0);
	Image* image = loadBMP("E:\\Graphics\\alien (5)\\alien\\bg.bmp");
	_textureId = loadTexture(image);

	delete image;
}


void lightSetting()
{

	GLfloat ambientIntensity[4] = {0.6, 0.6, 0.6, 1.0};

	GLfloat position[4] = {0.0, 1.0, 0.0, 0.0};

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientIntensity);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
}



void viewHighScore(){


float data;
   ifstream input("E://Graphics//alien (5)//alien//bin//Debug//HighScore.txt");
  if(input.is_open()){

    while(!input.eof()){
          string number;
          getline(input,number);
           data = atoi(number.c_str());
           game_high_score=data;
    }

  }

}


void highscoresave(){
float data;
   ifstream input("E://Graphics//alien (5)//alien//bin//Debug//HighScore.txt");
  if(input.is_open()){

    while(!input.eof()){
          string number;
          getline(input,number);
          data = atoi(number.c_str());
    }

  }

  if(data<game_score){
  ofstream myfile;
  myfile.open ("E://Graphics//alien (5)//alien//bin//Debug//HighScore.txt");
  myfile <<game_score;
  myfile.close();
  }

}


void highScoreBox(){

    glColor3f (0.3, 0.9,0.8);
    glBegin(GL_POLYGON);
    glVertex2f(getX(-200),getY(10));
    glVertex2f(getX(-200),getY(-20));
    glVertex2f(getX(-290),getY(-20));
    glVertex2f(getX(-290),getY(10));
    glEnd();

    glPushMatrix();
    options(-.85,0.85,backbtn);
    glPopMatrix();

    glColor3f (0.6,0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-215));
    glVertex2f(getX(100),getY(-165));
    glVertex2f(getX(-140),getY(-165));
    glVertex2f(getX(-140),getY(-215));
    glEnd();
    glFlush();
    glPushMatrix();
    options(-.29,0.23,highScore);
    glPopMatrix();


}

void manualBox(){

    glColor3f (0.3, 0.9,0.8);
    glBegin(GL_POLYGON);
    glVertex2f(getX(-200),getY(10));
    glVertex2f(getX(-200),getY(-20));
    glVertex2f(getX(-290),getY(-20));
    glVertex2f(getX(-290),getY(10));
    glEnd();

    glPushMatrix();
    options(-.85,0.85,backbtn);
    glPopMatrix();

    glColor3f (0.6,0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-215));
    glVertex2f(getX(100),getY(-100));
    glVertex2f(getX(-260),getY(-100));
    glVertex2f(getX(-260),getY(-215));
    glEnd();
    glFlush();
    glPushMatrix();
    options(-0.8,0.38,manual);
    glPopMatrix();

    glPushMatrix();
    options(-0.8,0.26,manual2);
    glPopMatrix();


}


void showManual(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    manualBox();
    glPopMatrix();
    glutSwapBuffers();


}
void mouse(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            //cout<<x<<endl;
            //cout<<y<<endl;
            if(state==GLUT_DOWN)
            {

                    if(mouseX >=180 && mouseX <= 420)
                            if(mouseY >= 125 && mouseY <= 175)
                            {
                               // initialize();
	                           // lightSetting();
	                           if(pausecontroll==0){
                                glutDisplayFunc(startgame);
                                sound_Control(1);
	                           }
	                           else{

	                           }
                            }

            }

              //cout<<y<<endl;
            if(state==GLUT_DOWN)
            {

                    if(mouseX >=180 && mouseX <= 420)
                            if(mouseY >=265 && mouseY <= 315)
                            {

                             glutDisplayFunc(showHighScore);
                             //  sound_Control(1);
                            // showHighScore();

                            }

            }


                if(state==GLUT_DOWN)
            {

                    if(mouseX >=180 && mouseX <= 420)
                            if(mouseY >=195 && mouseY <=245)
                            {
                                if(pausecontroll!=0){
                                glutDisplayFunc(startgame);
                                sound_Control(1);
                                }
                            }

            }

         if(state==GLUT_DOWN)
            {

                    if(mouseX >=30 && mouseX <= 120)
                            if(mouseY >=20 && mouseY <= 50)
                            {

                                glutDisplayFunc(optionbox);


                            }

            }

            if(state==GLUT_DOWN)
            {

                    if(mouseX >=180 && mouseX <= 420)
                            if(mouseY >=405 && mouseY <= 455)
                            {

                                glutDisplayFunc(showManual);
                               // cout<<"sdjfndsj";


                            }

            }


            if(state==GLUT_DOWN)
            {

                    if(mouseX >=180 && mouseX <= 420)
                            if(mouseY >=335 && mouseY <=385)
                            {
                             exit(0);
                            }

            }


        default:
            break;
    }
}


void playerBullet(){

    glTranslatef(Hero_move,playerbullet_move, 0.0f);
    updatePlayerBullet(-285);
    glColor3f (1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(getX(-280),getY(-480));

    glEnd();
    glFlush();
    player_bulletposition=getX(-280);

}


void alienBullet(int x_change)
{
    glPointSize(7);
    int x=x_change;
    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(getX(170+x),getY(5));
    glEnd();
    glFlush ();

}

void specialKeys(int key, int x, int y) {


    switch (key) {
      case GLUT_KEY_RIGHT:

          Hero_move+=0.02f;
          playerPositionx1=playerPositionx1+Hero_move;
          playerPositionx2=playerPositionx2+Hero_move;
          player_bulletposition=player_bulletposition+Hero_move;
          check(playerPositionx1,playerPositionx2);
          if(Hero_move==1.6){
            Hero_move+=0.0f;
          }
          updatePlayer(0);
          break;
      case GLUT_KEY_LEFT:
          Hero_move-=0.02f;

          playerPositionx1=playerPositionx1+Hero_move;
          playerPositionx2=playerPositionx2+Hero_move;
          player_bulletposition=player_bulletposition+Hero_move;
          check(playerPositionx1,playerPositionx2);
          updatePlayer(0);
          break;




    }
}


void processKeys(unsigned char key, int x, int y) {

     if (key == 27){ // escape key
           // exit(0);
           current_score=game_score;
           cout<<current_score;
           glutDisplayFunc(drawScene);
           sound_Control(0);
           pausecontroll=1;

      }
}

void Player()
{

    glTranslatef(Hero_move,0.0f, 0.0f);
    glColor3f (1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);





    glVertex2f(getX(-275),getY(-480));
    glVertex2f(getX(-275),getY(-460));
    glVertex2f(getX(-285),getY(-460));
    glVertex2f(getX(-285),getY(-480));


    glVertex2f(getX(-250),getY(-480));
    glVertex2f(getX(-250),getY(-520));
    glVertex2f(getX(-310),getY(-520));
    glVertex2f(getX(-310),getY(-480));


    glEnd();
    playerPositionx1=getX(-310);
    playerPositionx2=getX(-250);



    glFlush ();

//    PlaySound("Sunday.mp3", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
}


void alien_two(int x, int y)
{

    glTranslatef(0.0f,_move, 0.0f);

    int second_alienfire=x;
    glColor3f (0.0, 1.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(190+x),getY(40+y));
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(150+x),getY(80+y));
    glVertex2f(getX(150+x),getY(40+y));
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(200+x),getY(100+y));
    glVertex2f(getX(180+x),getY(80+y));
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex2f(getX(160+x),getY(80+y));
    glVertex2f(getX(140+x),getY(100+y));
    glVertex2f(getX(150+x),getY(80+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(195+x),getY(55+y));
    glVertex2f(getX(195+x),getY(65+y));
    glVertex2f(getX(190+x),getY(65+y));
    glVertex2f(getX(190+x),getY(55+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(35+y));
    glVertex2f(getX(170+x),getY(35+y));
    glEnd();





    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(70+y));
    glVertex2f(getX(175+x),getY(70+y));
    glEnd();




    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(70+y));
    glVertex2f(getX(155+x),getY(70+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(getX(175+x),getY(55+y));
    glVertex2f(getX(170+x),getY(65+y));
    glVertex2f(getX(165+x),getY(55+y));
    glEnd();

    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(48+y));
    glVertex2f(getX(175+x),getY(48+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(150+x),getY(55+y));
    glVertex2f(getX(150+x),getY(65+y));
    glVertex2f(getX(143+x),getY(65+y));
    glVertex2f(getX(143+x),getY(55+y));
    glEnd();


    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(175+x),getY(30+y));
    glVertex2f(getX(175+x),getY(40+y));
    glVertex2f(getX(165+x),getY(40+y));
    glVertex2f(getX(165+x),getY(30+y));
    glEnd();



    glColor3f (1.0, 0.6, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(getX(200+x),getY(5+y));
    glVertex2f(getX(200+x),getY(30+y));
    glVertex2f(getX(140+x),getY(30+y));
    glVertex2f(getX(140+x),getY(5+y));
    glEnd();
    enemytwoPositionx1=getX(200+x);
    enemytwoPositionx2=getX(140+x);



    glTranslatef(0.0f,bullet_move, 0.0f);
    alienBullet(second_alienfire);
    alientwoBulletPosition=getX(second_alienfire);

}

void alien_three(int x,int y){




    int thirdalien_fire=x;
    glColor3f (0.0, 1.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(190+x),getY(40+y));
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(150+x),getY(80+y));
    glVertex2f(getX(150+x),getY(40+y));
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(200+x),getY(100+y));
    glVertex2f(getX(180+x),getY(80+y));
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex2f(getX(160+x),getY(80+y));
    glVertex2f(getX(140+x),getY(100+y));
    glVertex2f(getX(150+x),getY(80+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(195+x),getY(55+y));
    glVertex2f(getX(195+x),getY(65+y));
    glVertex2f(getX(190+x),getY(65+y));
    glVertex2f(getX(190+x),getY(55+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(35+y));
    glVertex2f(getX(170+x),getY(35+y));
    glEnd();





    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(70+y));
    glVertex2f(getX(175+x),getY(70+y));
    glEnd();




    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(70+y));
    glVertex2f(getX(155+x),getY(70+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(getX(175+x),getY(55+y));
    glVertex2f(getX(170+x),getY(65+y));
    glVertex2f(getX(165+x),getY(55+y));
    glEnd();

    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(48+y));
    glVertex2f(getX(175+x),getY(48+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(150+x),getY(55+y));
    glVertex2f(getX(150+x),getY(65+y));
    glVertex2f(getX(143+x),getY(65+y));
    glVertex2f(getX(143+x),getY(55+y));
    glEnd();


    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(175+x),getY(30+y));
    glVertex2f(getX(175+x),getY(40+y));
    glVertex2f(getX(165+x),getY(40+y));
    glVertex2f(getX(165+x),getY(30+y));
    glEnd();



    glColor3f (1.0, 0.6, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(getX(200+x),getY(5+y));
    glVertex2f(getX(200+x),getY(30+y));
    glVertex2f(getX(140+x),getY(30+y));
    glVertex2f(getX(140+x),getY(5+y));
    glEnd();

    enemythreePositionx1=getX(200+x);
    enemythreePositionx2=getX(140+x);

     glTranslatef(0.0f,bullet_move, 0.0f);
     alienBullet(thirdalien_fire);
     alienthreeBulletPosition=getX(thirdalien_fire);


}





void alien_one(int x_change, int y_change)
{
    glTranslatef(0.0f,_move, 0.0f);
    srand (time(NULL));
    int first_alienfire=x_change;

    int x=x_change;
    int y=y_change;
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 1.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POLYGON);
    glVertex2f(getX(190+x),getY(40+y));
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(150+x),getY(80+y));
    glVertex2f(getX(150+x),getY(40+y));
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(getX(190+x),getY(80+y));
    glVertex2f(getX(200+x),getY(100+y));
    glVertex2f(getX(180+x),getY(80+y));
    glEnd();


    glBegin(GL_TRIANGLES);
    glVertex2f(getX(160+x),getY(80+y));
    glVertex2f(getX(140+x),getY(100+y));
    glVertex2f(getX(150+x),getY(80+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(195+x),getY(55+y));
    glVertex2f(getX(195+x),getY(65+y));
    glVertex2f(getX(190+x),getY(65+y));
    glVertex2f(getX(190+x),getY(55+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(35+y));
    glVertex2f(getX(170+x),getY(35+y));
    glEnd();





    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(185+x),getY(70+y));
    glVertex2f(getX(175+x),getY(70+y));
    glEnd();




    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(70+y));
    glVertex2f(getX(155+x),getY(70+y));
    glEnd();


    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(getX(175+x),getY(55+y));
    glVertex2f(getX(170+x),getY(65+y));
    glVertex2f(getX(165+x),getY(55+y));
    glEnd();

    glColor3f (0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(getX(165+x),getY(48+y));
    glVertex2f(getX(175+x),getY(48+y));
    glEnd();

    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(150+x),getY(55+y));
    glVertex2f(getX(150+x),getY(65+y));
    glVertex2f(getX(143+x),getY(65+y));
    glVertex2f(getX(143+x),getY(55+y));
    glEnd();


    glColor3f (0.9, 0.8, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(175+x),getY(30+y));
    glVertex2f(getX(175+x),getY(40+y));
    glVertex2f(getX(165+x),getY(40+y));
    glVertex2f(getX(165+x),getY(30+y));
    glEnd();



    glColor3f (1.0, 0.6, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(getX(200+x),getY(5+y));
    glVertex2f(getX(200+x),getY(30+y));
    glVertex2f(getX(140+x),getY(30+y));
    glVertex2f(getX(140+x),getY(5+y));
    glEnd();

    enemyonePositionx1=getX(200+x);
    enemyonePositionx2=getX(140+x);









    glTranslatef(0.0f,bullet_move, 0.0f);
    alienBullet(first_alienfire);

    alienoneBulletPosition=getX(first_alienfire);
   // Line();
    //glTranslatef(0.0f,0.0f, 0.0f);
    //Line();

    glFlush ();





}

void sound_Control(int value){


//    sndPlaySound("Sunday.wav",SND_ASYNC|SND_LOOP);//Play background music
   if(value==1){
    sndPlaySound("Enemy_Fire1.wav",SND_ASYNC|SND_LOOP);//Play background music
   }
   else if(value==0){
     sndPlaySound("menu.wav",SND_ASYNC|SND_LOOP);//Play background music
   }
   else if(value==2){
    sndPlaySound("over.wav",SND_ASYNC|SND_LOOP);//Play background music
   }


}




void Win()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);

    glColor3f (0.6,0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-215));
    glVertex2f(getX(100),getY(-165));
    glVertex2f(getX(-140),getY(-165));
    glVertex2f(getX(-140),getY(-215));
    glEnd();
    glPushMatrix();
    options(-.25,0.23,gameWin);
    glPopMatrix();

}


void Over()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);

    glColor3f (0.6,0.2, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(getX(100),getY(-215));
    glVertex2f(getX(100),getY(-165));
    glVertex2f(getX(-140),getY(-165));
    glVertex2f(getX(-140),getY(-215));
    glEnd();
    glFlush();
    glPushMatrix();
    options(-.25,0.23,gameOver);
    glPopMatrix();
    glutSwapBuffers();





}

void updatePlayerBullet(int value){

    playerbullet_move+=0.09;
    if(playerbullet_move-2.5>1.5)
    {

        playerbullet_move-=4.0;

    }
    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(20, updatePlayerBullet, 0); //Notify GLUT to call update again in 25 milliseconds

}



void updatePlayer(int value){
    game_score=game_score+0.001;
    if(Hero_move>1.6)
    {
        //cout<<speed<<endl;
        Hero_move = 1.6f;
    }

    if(Hero_move<0){
        Hero_move = 0.0f;
    }


    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(20, updatePlayer, 0); //Notify GLUT to call update again in 25 milliseconds


}


void update(int value)
{

    _move -= .002;
    if(_move+1.3<1.0)
    {
        _move+=0.01;
    }


    bullet_move-=.08;
    if(bullet_move+3.5<1.5)
    {

        bullet_move+=1.90;

    }






    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(20, update, 0); //Notify GLUT to call update again in 25 milliseconds
}


void showHighScore(){
    viewHighScore();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    highScoreBox();
    glPopMatrix();

    glPushMatrix();
        stringstream ss;
        ss <<game_high_score;
        string str = ss.str();
        char* char_type = (char*) str.c_str();
        //cout<<str<<endl;
        scoreCalculator(0.15,0.23,char_type); //new
        glPopMatrix();
       glutSwapBuffers();


    //   cout<<game

}



void oneInjured(){



    //sound_Control(1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_two(2000,8000);
    glPopMatrix();

    srand (time(NULL));


    int  x=rand() % -200 -100;
    int  y=rand() % -25-1;

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_two(x,y);
    glPopMatrix();
   // glutSwapBuffers();




     x=rand() % 400-500;
     y=rand() % -40-100;
    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_three(x,y);
    glPopMatrix();


    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    playerBullet();
    glPopMatrix();

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    Player();
    glPopMatrix();



    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    scoreCalculator(0.5,-0.9,score);
    glPopMatrix();

    glPushMatrix();
    options(0.2,-0.9,playerlife);
    glPopMatrix();



    check(playerPositionx1,playerPositionx2);

     glPushMatrix();
        stringstream ss;
        ss <<game_score;
        string str = ss.str();
        char* char_type = (char*) str.c_str();
        //cout<<str<<endl;
        scoreCalculator(0.7,-0.9,char_type); //new
        glPopMatrix();





    glutSwapBuffers();


}

void twoInjured(){

    int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);


     glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_two(2000,8000);
    glPopMatrix();
     glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_one(2000,8000);
    glPopMatrix();




     x=rand() % 400-500;
     y=rand() % -40-100;
    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_three(x,y);
    glPopMatrix();


    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    playerBullet();
    glPopMatrix();

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    Player();
    glPopMatrix();



    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    scoreCalculator(0.5,-0.9,score);
    glPopMatrix();

    glPushMatrix();
    options(0.2,-0.9,playerlife);
    glPopMatrix();



    check(playerPositionx1,playerPositionx2);

     glPushMatrix();
        stringstream ss;
        ss <<game_score;
        string str = ss.str();
        char* char_type = (char*) str.c_str();
        //cout<<str<<endl;
        scoreCalculator(0.7,-0.9,char_type); //new
        glPopMatrix();
        glutSwapBuffers();







}



void allInjured(){

    int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);


     glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_two(2000,8000);
    glPopMatrix();
     glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_one(2000,8000);
    glPopMatrix();

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_three(2000,8000);
    glPopMatrix();


    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    playerBullet();
    glPopMatrix();

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    Player();
    glPopMatrix();



    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    scoreCalculator(0.5,-0.9,score);
    glPopMatrix();

    glPushMatrix();
    options(0.2,-0.9,playerlife);
    glPopMatrix();



    check(playerPositionx1,playerPositionx2);

     glPushMatrix();
        stringstream ss;
        ss <<game_score;
        string str = ss.str();
        char* char_type = (char*) str.c_str();
        //cout<<str<<endl;
        scoreCalculator(0.7,-0.9,char_type); //new
        glPopMatrix();




    glutSwapBuffers();



}


void startgame(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);



    srand (time(NULL));
    int random_Y=rand() % 25+1;
    int random_X=rand() % 300 +1;



    glPushMatrix();
    alien_one(-random_X,-random_Y);
    glPopMatrix();

    srand (time(NULL));


    int  x=rand() % -200 -100;
    int  y=rand() % -25-1;

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_two(x,y);
    glPopMatrix();
   // glutSwapBuffers();




     x=rand() % 400-500;
     y=rand() % -40-100;
    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    alien_three(x,y);
    glPopMatrix();


    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    playerBullet();
    glPopMatrix();

    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    Player();
    glPopMatrix();



    glPushMatrix();
  //  glTranslatef(0.0f,_move, 0.0f);
    scoreCalculator(0.5,-0.9,score);
    glPopMatrix();

    glPushMatrix();
    options(0.2,-0.9,playerlife);
    glPopMatrix();



    check(playerPositionx1,playerPositionx2);

     glPushMatrix();
        stringstream ss;
        ss <<game_score;
        string str = ss.str();
        char* char_type = (char*) str.c_str();
        //cout<<str<<endl;
        scoreCalculator(0.7,-0.9,char_type); //new
        glPopMatrix();





        glutSwapBuffers();
    }



     //  cout<<"One"<<alienoneBulletPosition<<endl;
       //cout<<"Two"<<alientwoBulletPosition<<endl;
       //cout<<"Three"<<alienthreeBulletPosition<<endl;
   //    cout<<"Player x1"<<playerPositionx1<<endl;
     //  cout<<"Player x2"<<playerPositionx2<<endl;



void drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glLoadIdentity(); //Reset the drawing perspective
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    optionbox();
    glPopMatrix();



}

void check(float x1,float x2){
  //  sound_Control(1);
    if(alienoneBulletPosition>=x1 && alienoneBulletPosition<=x2){

       player_injury=player_injury+1;

    }
   else if(alientwoBulletPosition>=x2 && alientwoBulletPosition<=x1){
        player_injury=player_injury+1;

    }
   else if(alienthreeBulletPosition>=x2 && alienthreeBulletPosition<=x1){
        player_injury=player_injury+1;


    }


    player_injury++;

    lifeColor();

    enemycheck();



}


void enemycheck(){
    float player_pos=player_bulletposition*(-1);

    if(player_pos<=enemytwoPositionx1 && player_pos>=enemytwoPositionx2){
       ++enemy2_injured;
       enemyKill();
    }

    if(player_pos<=enemythreePositionx1 && player_pos>=enemythreePositionx2){
        ++enemy3_injured;
        enemyKill();
    }

    if(player_pos<=enemyonePositionx1 && player_pos>=enemyonePositionx2){
      ++enemy1_injured;
      enemyKill();


    }

}






void enemyKill(){



 if(enemy2_injured>=30 && enemy1_injured>=30 || enemy3_injured>=30 && enemy1_injured>=30 || enemy2_injured>=30 && enemy3_injured>=30){

       glutDisplayFunc(twoInjured);

  }

 else if(enemy1_injured>=30 ||enemy2_injured>=30|| enemy3_injured>=30){
       glutDisplayFunc(oneInjured);

  }

  else if(enemy1_injured>=20 && enemy2_injured>=20 && enemy3_injured>=20){

      glutDisplayFunc(allInjured);
      glutDisplayFunc(Win);
      highscoresave();

  }



}

void lifeColor(){
    if(player_injury<400){
         glPushMatrix();
         playerLife(0,1,0);
         glPopMatrix();


    }
    else if(player_injury>=401 && player_injury<=2000){
         glPushMatrix();
         playerLife(0.92,0.87,0);
         glPopMatrix();


    }

    else if (player_injury>=2000 && player_injury<=2500){
         glPushMatrix();
         playerLife(1,0,0);
         glPopMatrix();


    }
    else if(player_injury>2500){

        glutDisplayFunc(Over);
        highscoresave();
        sound_Control(2);

    }



}



    int main(int argc, char** argv){
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(width, height);
      glutCreateWindow("Alien Shooter");
    //sndPlaySound(TEXT("ESE.wav"), NULL, SND_ASYNC|SND_LOOP);
      sound_Control(0);
      glutDisplayFunc(drawScene);
      glutSpecialFunc(specialKeys);
      glutMouseFunc(mouse);
      glutKeyboardFunc( processKeys );
      glutTimerFunc(20, update, 0); //Add a timer
      glutTimerFunc(20, updatePlayer, 0); //Add a timer
      glutMainLoop();

      return 0;
}
