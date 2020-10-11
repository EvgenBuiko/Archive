#include <stdlib.h>
#include <gl/glut.h>
#include <time.h>
#include <windows.h>

enum enObjMoveDirection
{
	stay = 0,
	left,
	up, 
	right,
	down
};

float angle = 0.0f;
// sphere position relative to window
float posX = 250.0f, posY = 250.0f;
// cube position relative to window
float goalX = 0.0f, goalY = 0.0f;
// control values of position offset and rotation during animation
int animationStep = 0;
bool isWin = false;
enObjMoveDirection move = stay;
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

void renderBitmapString( float x, float y, float z, void* font, char* string) 
{
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void drawCube()
{
	glTranslatef(goalX, goalY, 0.0f);

	/* Setup cube vertex data. */
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -10;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 10;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -10;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 10;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 10;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -10;
	int i;
	glRotatef(10.f, 1.0f, 1.0f, 0.0f);
	for (i = 0; i < 6; i++) {
		switch (i) // programming color :)
		{
		case 0: glColor3f(1.0f, 0.0f, 0.0f); break;
		case 1: glColor3f(0.0f, 1.0f, 0.0f); break;
		case 2:	glColor3f(1.0f, 1.0f, 0.0f); break;
		case 3:	glColor3f(0.0f, 0.0f, 1.0f); break;
		case 4:	glColor3f(1.0f, 0.0f, 1.0f); break;
		case 5:	glColor3f(0.0f, 1.0f, 1.0f); break;
		default: break;
		}
		// draw face of cube
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
	glTranslated(0.0, 0.0, 0.0);
}

void processNormalKeys(unsigned char key, int x, int y) 
{
	if( key == 27 )
		exit(0); // Escape key. Available when win!
	// wait complete previous animation of moving
	if (move != stay || isWin )
		return;
	// check what key pressed
	switch (key)
	{
	case 'w': move = up; break;
	case 's': move = down; break;
	case 'a': move = left; break;
	case 'd': move = right;	break;
	default: break;
	}
}

void renderScene(void) 
{
	if (isWin)
		return;

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// zero transformation
	glLoadIdentity();

	glPushMatrix();
	drawCube();
	glPopMatrix();

	glPushMatrix();

	// set current offset before moving
	float offsetX = 0.0f;
	float offsetY = 0.0f;
	if( move == left || move == right )
		offsetX = animationStep * ( ( move == left ) ? -10.0 : 10.0 ) / 5;
	if( move == up || move == down )
		offsetY = animationStep * ( ( move == up ) ? 10.0 : -10.0 ) / 5;
	// set current position of sphere
	glTranslated(posX + offsetX, posY + offsetY, 0.0);
	// set current rotation
	switch (move)
	{
	case left: glRotatef(angle, 0.0f, 1.0f, 0.0f); break;
	case right:	glRotatef(angle, 0.0f, -1.0f, 0.0f); break;
	case up: glRotatef(angle, 1.0f, 0.0f, 0.0f); break;
	case down: glRotatef(angle, -1.0f, 0.0f, 0.0f); break;
	default: break;
	}
	// set sphere color
	glColor3f(1.0f, 0.0f, 0.0f);
	// draw sphere
	glutWireSphere(15.0, 15.0, 15.0);
	// update variables of animation step
	if (move != stay)
	{
		// 180 degrees because turn over
		angle = animationStep * (180.0f / 5);
		animationStep++;
		if ( animationStep > 5 )
		{
			move = stay;
			angle = 0.0f;
			animationStep = 0;
			// set new sphere position
			posX += offsetX;
			posY += offsetY;
		}
		else
		{
			Sleep(20);
		}
	}
	glPopMatrix();
	// check center of sphere in cube?
	if ((posX == goalX || (posX >= goalX - 10 && posX <= goalX + 10)) &&
		(posY == goalY || (posY >= goalY - 10 && posY <= goalY + 10))
		)
	{
		glPushMatrix();
		renderBitmapString(220, 240, 0, GLUT_BITMAP_HELVETICA_18, (char*)"YOU WIN"); 
		glPopMatrix();
		isWin = true;
	}
	// swap buffers for rendering (double buffering)
	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	// use the projection matrix
	glMatrixMode(GL_PROJECTION);
	// Reset matrix
	glLoadIdentity();
	// set orthographic projection
	glOrtho(0.0, 500.0, 0.0, 500.0, -100.0, 100.0);
	// come back to model
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	// randomize cube position
	srand(static_cast<unsigned int>(time(0)));
	goalX = rand() % 500;
	goalY = rand() % 500;

	// GLUT window initialization and creation
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutCreateWindow("cs 445 Program 2");

	// check scene depth (see what happens with sphere in cube using/comment this line)
	glEnable(GL_DEPTH_TEST);
	// initializing GLUT's window common callback functions
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);

	// call main loop for start
	glutMainLoop();
	return 0;
}