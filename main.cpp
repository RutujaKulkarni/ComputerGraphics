#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define BASE_HEIGHT 4.0/2
#define BASE_RADIUS 1.0/2
#define HEAD_HEIGHT 1.25/2
#define HEAD_RADIUS 0.75/2
#define NECK_HEIGHT 0.5/2
#define EYE_LEVEL 0.75/2
#define NOSE_LENGTH 0.5/2
#define LOWER_ARM_HEIGHT 2.0/2
#define LOWER_ARM_WIDTH 0.5/2
#define UPPER_ARM_HEIGHT 1.25/2
#define UPPER_ARM_WIDTH 0.5/2
#define ARM_TRANSLATION 0.22/2
#define alpha 0.0
#define pi 3.14159265
#define BALL_RADIUS 0.5

using namespace std;

static GLfloat angle[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

GLUquadricObj *p;
GLfloat x = 0.0;
GLfloat y = 0.0;
GLfloat xpos = 0.0;
GLfloat ypos = 0.0;
GLfloat zpos = 0.0;
int collisionCount = 0;
GLfloat ballPos [] = {3.0, 3.0, 0};
GLfloat ballVel [] = {0.0, 0.0, 0.0};
GLfloat ballAcc [] = {0.0, -9.81, 0};
GLfloat forceOnBall [] = {0.0, 0.0, 0.0};

GLfloat Robotaccln [] = {0.0, 0.0, 0.0};
//bounding boxes for collision
GLfloat robotBoundingMin [] = {0.0, 0.0, 0.0};
GLfloat robotBoundingMax [] = {0.0, 0.0, 0.0};
//
GLfloat ballBoundingMin [] = {0.0, 0.0, 0.0};
GLfloat ballBoundingMax [] = {0.0, 0.0, 0.0};

GLfloat ROBOT_MASS = 1.2;
GLfloat BALL_MASS = 1;
GLfloat WALL_MASS = 1;

GLfloat ambient[4];
GLfloat diffuse[4];
GLfloat specular[4];
GLfloat shine[] = {50.0f};
float width = 1100;
float height = 900;
void base(void);
void head(void);
void neck(void);
void upRightArm(void);
void upLeftArm(void);
void rightHand(void);
void leftHand(void);
void init(void);
void display(void);
void reshape (int width, int height);
void keyboard(unsigned char, int, int);
void processArrowKeys(int, int, int);
void lsphere (void);
void init1 (void);
bool checkCollision();
void moveBall();
GLfloat velx = 0.0;
GLuint fontOffset;

void base (void) {
    glPushMatrix();
    //head plastic red
    ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1.0;
    diffuse[0] = 0.5; diffuse[1] = 0.0; diffuse[2] = 0.0; diffuse[3] = 1.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.6; specular[3] = 1.0;
    shine[0] = 0.25*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    gluQuadricDrawStyle(p, GLU_FILL);
    gluCylinder (p, BASE_RADIUS, BASE_RADIUS, BASE_HEIGHT, 20, 20);
    glPopMatrix();
    glPushMatrix();
    gluQuadricDrawStyle (p, GLU_FILL);
    glTranslatef (0.0, BASE_HEIGHT, 0.0);
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
    glTranslatef (0.0, 0.0, -BASE_HEIGHT);
    gluDisk (p, 0.0, BASE_RADIUS, 20, 20);
    glPopMatrix();
}

void neck (void) {
    glPushMatrix();
    //head plastic red
    ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1.0;
    diffuse[0] = 0.5; diffuse[1] = 0.0; diffuse[2] = 0.0; diffuse[3] = 1.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.6; specular[3] = 1.0;
    shine[0] = 0.25*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glTranslatef(0.0, BASE_HEIGHT, 0.0);
    glRotatef (-90.0, 1.0, 0.0, 0.0);
    gluQuadricDrawStyle(p, GLU_FILL);
    gluCylinder (p, HEAD_RADIUS/2, HEAD_RADIUS/2, HEAD_HEIGHT, 8, 6);
    glPopMatrix();
}

void head (void) {
    glPushMatrix();
    //head plastic red
    ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1.0;
    diffuse[0] = 0.5; diffuse[1] = 0.0; diffuse[2] = 0.0; diffuse[3] = 1.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.6; specular[3] = 1.0;
    shine[0] = 0.25*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glRotatef (-90.0, 1.0, 0.0, 0.0);
    gluQuadricDrawStyle(p, GLU_FILL);
    gluCylinder (p, HEAD_RADIUS, HEAD_RADIUS, HEAD_HEIGHT, 20, 20);

    glPushMatrix();

    gluDisk (p, 0.0, HEAD_RADIUS, 20, 20);
    glTranslatef (0.0, 0.0, HEAD_HEIGHT);
    gluDisk (p, 0.0, HEAD_RADIUS, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.25, -HEAD_RADIUS+0.12, EYE_LEVEL);

    //Bronze right eye
    ambient[0] = 0.2125; ambient[1] = 0.1275; ambient[2] = 0.054; ambient[3] = 1.0;
    diffuse[0] = 0.714; diffuse[1] = 0.4284; diffuse[2] = 0.18144; diffuse[3] = 1.0;
    specular[0] = 0.3935; specular[1] = 0.2719; specular[2] = 0.1667; specular[3] = 1.0;
    shine[0] = 0.2*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    gluQuadricDrawStyle(p, GLU_FILL);
    gluSphere (p, 0.125, 6, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef (-0.25, -HEAD_RADIUS+0.12, EYE_LEVEL);
    //Bronze left eye
    ambient[0] = 0.2125; ambient[1] = 0.1275; ambient[2] = 0.054; ambient[3] = 1.0;
    diffuse[0] = 0.714; diffuse[1] = 0.4284; diffuse[2] = 0.18144; diffuse[3] = 1.0;
    specular[0] = 0.3935; specular[1] = 0.2719; specular[2] = 0.1667; specular[3] = 1.0;
    shine[0] = 0.2*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    gluQuadricDrawStyle(p, GLU_FILL);
    gluSphere (p, 0.125, 6, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -HEAD_RADIUS, NOSE_LENGTH);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluQuadricDrawStyle(p, GLU_FILL);
    gluCylinder(p, 0.125, 0, NOSE_LENGTH, 8,6);
    glPopMatrix();

    glPopMatrix();
}

void rightHand(void) {
glPushMatrix();

    //black rubber lower right arm
    ambient[0] = 0.02; ambient[1] = 0.02; ambient[2] = 0.02; ambient[3] = 1.0;
    diffuse[0] = 0.01; diffuse[1] = 0.01; diffuse[2] = 0.01; diffuse[3] = 1.0;
    specular[0] = 0.4; specular[1] = 0.4; specular[2] = 0.4; specular[3] = 1.0;
    shine[0] = 0.0781*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glTranslatef(0.0, 0.5 * LOWER_ARM_HEIGHT, ARM_TRANSLATION);
    glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
    glutSolidCube(1.0);
    glPopMatrix();
}

void leftHand(void) {
    glPushMatrix();
    //black rubber lower left arm
    ambient[0] = 0.02; ambient[1] = 0.02; ambient[2] = 0.02; ambient[3] = 1.0;
    diffuse[0] = 0.01; diffuse[1] = 0.01; diffuse[2] = 0.01; diffuse[3] = 1.0;
    specular[0] = 0.4; specular[1] = 0.4; specular[2] = 0.4; specular[3] = 1.0;
    shine[0] = 0.0781*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glTranslatef(0.0, 0.5 * LOWER_ARM_HEIGHT, -ARM_TRANSLATION);
    glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
    glutSolidCube(1.0);
    glPopMatrix();
}

void upRightArm(void) {
    glPushMatrix();
    //black rubber upper right arm
    ambient[0] = 0.02; ambient[1] = 0.02; ambient[2] = 0.02; ambient[3] = 1.0;
    diffuse[0] = 0.01; diffuse[1] = 0.01; diffuse[2] = 0.01; diffuse[3] = 1.0;
    specular[0] = 0.4; specular[1] = 0.4; specular[2] = 0.4; specular[3] = 1.0;
    shine[0] = 0.0781*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glTranslatef(0.0, 0.5 * UPPER_ARM_HEIGHT, ARM_TRANSLATION);
    glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
    glutSolidCube(1.0);
    glPopMatrix();
}

void upLeftArm(void) {
    glPushMatrix();
    //black rubber upper left arm
    ambient[0] = 0.02; ambient[1] = 0.02; ambient[2] = 0.02; ambient[3] = 1.0;
    diffuse[0] = 0.01; diffuse[1] = 0.01; diffuse[2] = 0.01; diffuse[3] = 1.0;
    specular[0] = 0.4; specular[1] = 0.4; specular[2] = 0.4; specular[3] = 1.0;
    shine[0] = 0.0781*128.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glTranslatef(0.0, 0.5 * UPPER_ARM_HEIGHT, -ARM_TRANSLATION);
    glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
    glutSolidCube(1.0);
    glPopMatrix();
}

void init1(void){
  GLfloat light_position[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void lsphere(void){
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  //gold
  ambient[0] = 0.2472; ambient[1] = 0.1995; ambient[2] = 0.0745; ambient[3] = 1.0;
  diffuse[0] = 0.7516; diffuse[1] = 0.6064; diffuse[2] = 0.2264; diffuse[3] = 1.0;
  specular[0] = 0.6282; specular[1] = 0.5558; specular[2] = 0.366; specular[3] = 1.0;
  shine[0] = 0.4*128.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shine);
  glutSolidSphere(BALL_RADIUS, 20, 16);
  glPopMatrix();
  glFlush();
}

bool checkCollision(){
  //check for 6 faces of the cube surrounding the ball and decide the force accordingly
  bool collided = false;
  //checking all of the corners of the bounding box of the ball

	if(ballPos[0] >= 5.0 || ballPos[0] <= -5.0){ //apply force to the ball in x component
		ballVel[0] *= -0.95; //(-1*ballVel[0]*BALL_MASS)/(BALL_MASS + WALL_MASS);
	}
	if(ballPos[1] >= 5.0 || ballPos[1] <= 0.5){
		ballVel[1] *= -0.95;
	}
	if(ballPos[2] >= 5.0 || ballPos[2] <= -5.0){//edit the z limit decrease
		ballVel[2] *= -0.95; //(-1*ballVel[2]*BALL_MASS)/(BALL_MASS + WALL_MASS);
	}
  float d = sqrt( (xpos - ballPos[0])*(xpos - ballPos[0]) + (zpos - ballPos[2])*(zpos - ballPos[2]) );
  if(d <= (BASE_RADIUS+BALL_RADIUS)){
    collisionCount++;
    float div = sqrt((ballPos[0] - xpos)*(ballPos[0] - xpos) + (ballPos[2] - zpos)*(ballPos[2] - zpos));
    ballAcc[0] = (ballPos[0] - xpos)/div;
    ballAcc[2] = (ballPos[2] - zpos)/div;
  }
	return collided;//collX && collZ;
}

void moveBall(int t){
    glPushMatrix();
    checkCollision();
    //have to calculate velocity every 500 millis
    ballVel[0]+=ballAcc[0] * 0.005; //0.5 is diff in time
    ballVel[1]+=ballAcc[1] * 0.005; //gravity comp
    ballVel[2]+=ballAcc[2] * 0.005;

    ballPos[0]+=ballVel[0] * 0.005;
    ballPos[1]+=ballVel[1] * 0.005;
    ballPos[2]+=ballVel[2] * 0.05;
    if(ballPos[1] <= 0.5){
    	ballPos[1] = 0.5;
    }

    if(ballAcc[0] > 0){
      ballAcc[0] -= 0.1;
    }else if(ballAcc[0] < 0){
      ballAcc[0] += 0.1;
    }
    if(ballAcc[2] > 0){
      ballAcc[2] -= 0.1;
    }else if(ballAcc[2] < 0){
      ballAcc[2] += 0.1;
    }
    glTranslatef(ballPos[0], ballPos[1], ballPos[2]);
    lsphere();
    glPopMatrix();
    glutPostRedisplay();
}

void display(void) {
	  glutTimerFunc(500,moveBall,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;
    gluPerspective( 50, ar, 0.1, 30);
    glFrustum(0, w, 0, h, -1.0f, 1.0f);
    glMatrixMode( GL_MODELVIEW );
    //eyex, eyey, eyez, cX , cY  , cZ , upX, upY, upZ
    gluLookAt(0.3 , 5.3, 12.0, 0.0, 1.25, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    checkCollision(); //call collision
    glTranslatef(ballPos[0], ballPos[1], ballPos[2]);
    lsphere();
    glPopMatrix();

    //glPushMatrix();
    //std::string s = "Collisions :" + std::to_string(collisionCount);

    // ambient[0] = 0.25; ambient[1] = 0.20725; ambient[2] = 0.20725;
    // diffuse[0] = 1.0; diffuse[1] = 0.829; diffuse[2] = 0.829;
    // specular[0] = 0.2966; specular[1] = 0.2966; specular[2] = 0.2966;
    // shine[0] = 0.088*128.0;
    // glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    // glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    // glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    // float n = .5; /* Centre in the middle of the window */
    // glRasterPos2f(n - (float) width / 2, 0.);
    // int len = s.length();
    // for (int i = 0; i < len; i++) {
    //     glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    // }
    // for (auto ch : s)
    // {
    //   std::cout << "printing" <<std::endl;
    //   glutBitmapCharacter(GLUT_STROKE_ROMAN, ch);
    // }
    //glPopMatrix();

    //play ground begins
    glPushMatrix();
    ambient[0] = 0.5; ambient[1] = 0.5; ambient[2] = 0.5;
    diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0;
    specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.5;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    glBegin(GL_POLYGON);
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(-5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, 5.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();

    glBegin(GL_POLYGON);
    glVertex3f(5.0, 0.0, -5.0);
    glVertex3f(5.0, 5.0, -5.0);
    glVertex3f(-5.0, 5.0, -5.0);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glEnd();

    glPopMatrix();
    //playground ends

    glTranslatef (xpos, ypos, zpos);
    glRotatef(angle[0], 0.0, 1.0, 0.0);
    base();
    neck();

    glPushMatrix();
    glTranslatef(0.0, BASE_HEIGHT + HEAD_HEIGHT/2, 0.0);
    glRotatef(angle[2], 1.0, 0.0, 0.0);
    glRotatef(angle[1], 0.0, 1.0, 0.0);
    head();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glRotatef(270.0, 0.0, 1.0, 0.0);
    glRotatef(angle[4], 0.0, 0.0, 1.0);
    rightHand();
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    glRotatef(0.0, 0.0, 0.0, 180.0);
    glRotatef(angle[6], 0.0, 0.0, 1.0);
    upRightArm();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-BASE_RADIUS, BASE_HEIGHT - BASE_RADIUS / 2, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glRotatef(270.0, 0.0, 1.0, 0.0);
    glRotatef(angle[3], 0.0, 0.0, 1.0);
    leftHand();
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    glRotatef(0.0, 0.0, 0.0, 180.0);
    glRotatef(angle[5], 0.0, 0.0, 1.0);
    upLeftArm();
    glPopMatrix();
    //setting bounding boxes for collision
    robotBoundingMin[0] = xpos-BASE_RADIUS;
    robotBoundingMin[1] = ypos;
    robotBoundingMin[2] = zpos-BASE_RADIUS;

    robotBoundingMax[0] = xpos+BASE_RADIUS;
    robotBoundingMax[1] = BASE_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT;
    robotBoundingMax[2] = zpos+BASE_RADIUS;

    ballBoundingMin[0] = ballPos[0]-BALL_RADIUS;
    ballBoundingMin[1] = ballPos[1]-BALL_RADIUS;
    ballBoundingMin[2] = ballPos[2]-BALL_RADIUS;

    ballBoundingMax[0] = ballPos[0]+BALL_RADIUS;
    ballBoundingMax[1] = ballPos[1]+BALL_RADIUS;
    ballBoundingMax[2] = ballPos[2]+BALL_RADIUS;
    //setting bounding boxes for collision finished
    glFlush();
    glutSwapBuffers();
}

  void keyboard (unsigned char key, int x, int y) {
  switch (key) {
  	case 'a':
      angle[1] += 5.0;
  	  if (angle[1] > 90.0)
  	    angle[1] = 90.0;
  	break;
    case 'z':
      angle[1] -= 5.0;
      if (angle[1] < -90.0)
        angle[1] = -90.0;
    break;
    case 'o':
      angle[2] += 5.0;
      if (angle[2] > 45.0)
        angle[2] = 45.0;
    break;
    case 'p':
      angle[2] -= 5.0;
      if (angle[2] < -45.0)
        angle[2] = -45.0;
    break;
    case 'k':
      angle[3] -= 5.0;
    break;
    case 'l':
      angle[3] += 5.0;
    break;
    case 'h':
      angle[4] -= 5.0;
      break;
    case 'j':
      angle[4] += 5.0;
      break;
    case 'n':
      angle[5] -= 5.0;
      break;
    case 'm':
      angle[5] += 5.0;
      break;
    case 'v':
      angle[6] -= 5.0;
      break;
    case 'b':
      angle[6] += 5.0;
      break;
    case 'e':
      angle[0] = angle[1] = angle[2] = angle[3] = angle[4] = angle[5] = angle[6] = xpos = ypos = zpos = 0.0;
    break;
    case 'r':
      angle[0] = angle[1] = angle[2] = angle[3] = angle[4] = angle[5] = angle[6] = 0.0;
    break;
    case 'q':
      exit(0);
    break;
  }
  glutPostRedisplay();
}

void processArrowKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP: //move forward
			xpos -= cos(90 * pi/180 + angle[0] * pi/180); //consider this as displacement in x direction
			//Robotaccln[0] = -(cos(90 * pi/180 + angle[0] * pi/180))/(0.5*0.5); // acceleration = d(vel)/d(time) vel = displacement/time
			zpos += sin(90 * pi/180 + angle[0] * pi/180);
			//Robotaccln[2] = (sin(90 * pi/180 + angle[0] * pi/180))/(0.5*0.5);
			if (xpos > 5)
			xpos = 5;
			if (zpos > 5)
			zpos = 5;
			if (xpos < -5)
			xpos = -5;
			if (zpos < -5)
			zpos = -5;
			break;
		case GLUT_KEY_DOWN: //move back
			xpos += cos(90 * pi/180 + angle[0] * pi/180);
			//Robotaccln[0] = (cos(90 * pi/180 + angle[0] * pi/180))/(0.5*0.5);
			zpos -= sin(90 * pi/180 + angle[0] * pi/180);
			//Robotaccln[2] = -(sin(90 * pi/180 + angle[0] * pi/180))/(0.5*0.5);
			if (xpos > 5)
			xpos = 5;
			if (zpos > 5)
			zpos = 5;
			if (xpos < -5)
			xpos = -5;
			if (zpos < -5)
			zpos = -5;
			break;
		case GLUT_KEY_LEFT: angle[0] -= 5.0; break;
		case GLUT_KEY_RIGHT: angle[0] += 5.0; break;
		case GLUT_KEY_PAGE_UP: ypos += 1.0; break;
		case GLUT_KEY_PAGE_DOWN: ypos -= 1.0; break;
	}

  glutPostRedisplay();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, (GLfloat) w / (GLfloat) h, 0.5, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void init (void) {
  GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
  GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  //makeRasterFont();
  p = gluNewQuadric();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("My Game");
	init();
	init1();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc (processArrowKeys);
	glutMainLoop();
	return 0;
}
