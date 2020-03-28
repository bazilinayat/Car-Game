#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

int cx=0,cy=240;
int n=6;
int acx[12];
int acy[12];

int rxu,rxd,ryu,ryd;

int detect=0;

int collision1(int cx1,int cy1,int acx1[5],int acy1[5]){

	int i,j,k,l;
	int flag=0;
	int acx2,acy2;
	//can intersect with which quad
	for(i=0;i<n;i++){
		if((cx1+60>=acx[i] && cx1+60<=acx[i]+60)){
			acx2=acx[i];
			acy2=acy[i];
		}
	}

	//is intersecting or not
	for(i=cx1;i<=cx1+60;i++){
		for(j=cy1;j<=cy1+30;j++){
			flag=0;
			for(k=acx2;k<=acx2+60;k++){
				for(l=acy2;l<=acy2+30;l++){
					if(i==k && j==l){
						flag=1;
						break;
					}
				}
				if(flag==1)
					break;
			}
			if(flag==1)
				break;
		}
		if(flag==1)
			break;
	}

	if(flag==1)//collided
		return 1;
	else//not collided
		return 0;
}

void myinit(){
	int i;
	//initialise quad points
	for(i=0;i<n;i++){
		acx[i]=640-rand()%530;
		acy[i]=110+rand()%240;
	}

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
}

void mykey(unsigned char key,int x,int y){
	int i;
	//detection
	int done=collision1(cx,cy,acx,acy);
	if(done==1)
		detect=1;

	switch(key){
		case 'd':if(cx>640){//set car to initial point and new points for others
				 cx=0;
				 for(i=0;i<n;i++){
					 acx[i]=600-rand()%530;
					 acy[i]=110+rand()%240;
				 }
			 }
			 else{//car in field keep moving
				 cx=cx+(1+rand()%5);//2;
				 for(i=0;i<n;i++){
					 acx[i]=acx[i]-(1+rand()%5);
				 }
			 }
			 break;
		case 's':if(cy>120){//car cannot go below road
				 cy=cy-(1+rand()%5);//2;
				 for(i=0;i<n;i++){
					 acx[i]=acx[i]-(1+rand()%5);
				 }
			 }
			 break;
		case 'w':if(cy+30<360){//car cannot go above road
				 cy=cy+(1+rand()%5);//2;
				 for(i=0;i<n;i++){
					 acx[i]=acx[i]-(1+rand()%5);
				 }
			 }
			 break;
	}
	glutPostRedisplay();
}

void display(){
	int xs,ys;
	int i,j;
	int yu=297,xu=0,xd=0,yd=177;
	glClear(GL_COLOR_BUFFER_BIT);

	//water up and down
	glColor3f(0.1f,0.5f,1.0f);
	glBegin(GL_QUADS);
	{
		//up
		glVertex2i(0,0);
		glVertex2i(640,0);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(640,80);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(0,80);
	}//gl quad ends
	glEnd();
	glColor3f(0.1f,0.5f,1.0f);
	glBegin(GL_QUADS);
	{
		//down
		glVertex2i(0,480);
		glVertex2i(640,480);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(640,400);
		glColor3f(0.0,0.0,0.0);
		glVertex2i(0,400);
	}//end gl quads
	glEnd();

	//bridge
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	{
		//up
		glVertex2i(0,80);
		glVertex2i(640,80);
		glVertex2i(640,120);
		glVertex2i(0,120);

		//down
		glVertex2i(0,400);
		glVertex2i(640,400);
		glVertex2i(640,360);
		glVertex2i(0,360);

	}
	glEnd();

	//salts
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POINTS);
	{
		for(j=1;j<=50;j++){
			rxd=rand()%640;
			ryd=rand()%80;
			glVertex2i(rxd,ryd);
		}
		for(j=0;j<=50;j++){
			rxu=rand()%640;
			ryu=410+rand()%80;
			glVertex2i(rxu,ryu);
		}
	}
	glEnd();

	//bridge strips
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	{
		for(j=0;j<=640;j=j+40){
			//up
			glVertex2i(j,80);
			glVertex2i(j,120);

			//down
			glVertex2i(j,360);
			glVertex2i(j,400);
		}
	}
	glEnd();

	//bridge border
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(0,80);
		glVertex2i(640,80);
		glVertex2i(640,120);
		glVertex2i(0,120);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	{
		glVertex2i(0,400);
		glVertex2i(640,400);
		glVertex2i(640,360);
		glVertex2i(0,360);
	}
	glEnd();

	//strips
	glBegin(GL_QUADS);
	{
		//the yellow strip in middle
		glColor3f(1.0f,1.0f,0.0f);
		glVertex2i(0,237);
		glVertex2i(640,237);
		glVertex2i(640,243);
		glVertex2i(0,243);

		//the white strip upside with intervals
		while(xu<=640){
			glColor3f(1.0f,1.0f,1.0f);
			glVertex2i(xu,yu);
			glVertex2i(xu+30,yu);
			glVertex2i(xu+30,yu+6);
			glVertex2i(xu,yu+6);
			xu=xu+50;
		}

		//the white strip downside with intervals
		while(xd<=640){
			glColor3f(1.0f,1.0f,1.0f);
			glVertex2i(xd,yd);
			glVertex2i(xd+30,yd);
			glVertex2i(xd+30,yd+6);
			glVertex2i(xd,yd+6);
			xd=xd+50;
		}
	}//end gl quads
	glEnd();

	//draw the cars if there is no clission
	if(detect==0){
		//car
		glBegin(GL_QUADS);
		{
			glColor3f(0.5f,0.5f,0.5f);
			glVertex2i(cx,cy);
			glVertex2i(cx+60,cy);
			glVertex2i(cx+60,cy+30);
			glVertex2i(cx,cy+30);

			for(i=0;i<n;i++){
				switch(i){
					case 0:glColor3f(1.0f,0.5f,0.5f);
					       break;
					case 1:glColor3f(0.5f,1.0f,0.5f);
					       break;
					case 2:glColor3f(0.5f,0.5f,1.0f);
					       break;
					case 3:glColor3f(0.5f,1.0f,1.0f);
					       break;
					case 4:glColor3f(1.0f,0.5f,1.0f);
					       break;
				}
				glVertex2i(acx[i],acy[i]);
				glVertex2i(acx[i]+60,acy[i]);
				glVertex2i(acx[i]+60,acy[i]+30);
				glVertex2i(acx[i],acy[i]+30);
			}

		}//end gl wuads
		glEnd();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(cx+60-15,cy);
			glVertex2i(cx+60,cy+5);
			glVertex2i(cx+60,cy+25);
			glVertex2i(cx+60-15,cy+30);
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		{
			glVertex2i(cx+15,cy);
			glVertex2i(cx+15,cy+30);
			glVertex2i(cx,cy+25);
			glVertex2i(cx,cy+5);
		}
		glEnd();

		for(i=0;i<n;i++){

			glBegin(GL_LINE_LOOP);
			{
				glVertex2i(acx[i]+60-15,acy[i]);
				glVertex2i(acx[i]+60,acy[i]+5);
				glVertex2i(acx[i]+60,acy[i]+25);
				glVertex2i(acx[i]+60-15,acy[i]+30);
			}
			glEnd();
			glBegin(GL_LINE_LOOP);
			{
				glVertex2i(acx[i]+15,acy[i]);
				glVertex2i(acx[i]+15,acy[i]+30);
				glVertex2i(acx[i],acy[i]+25);
				glVertex2i(acx[i],acy[i]+5);
			}
			glEnd();

		}


	}//end if detect==0
	else{//exit the program if there is collission
		exit(0);
	}

	glFlush();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(350,150);
	glutCreateWindow("Traffic Wave");
	//setting my key as the callback function for key actions
	glutKeyboardFunc(mykey);
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}
