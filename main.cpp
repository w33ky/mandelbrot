#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"
#include "Color.h"

// prototypes
void disp(void);
void keyb(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

int mandelbrot(int n, Vector c);

int ITERATION = 50;
int WIN_X = 800;
int WIN_Y = 800;

float SCALE_X = 1.1;
float MOVE_X = -0.5;
float SCALE_Y = 1.1;
float MOVE_Y = 0;

int *matrix;
int *matrix_aa;

static int window;
FILE *fptr;

float pos_x(int n) {
	return (((2.0)/(WIN_X))*n)-1.0;
}

float pos_y(int n) {
	return (((2.0)/(WIN_Y))*n)-1.0;
}

//call mandelbrot {ITERATION {WIN_X WIN_Y {SCALE_X SCALE_Y {MOVE_X MOVE_Y}}}}
int main(int argc, char **argv) {
	printf("Parameter: %i\n", argc);
	if(argc >= 2) {
		ITERATION = atoi(argv[1]);
	}
	if(argc >= 3) {
		WIN_X = atoi(argv[2]);
		WIN_Y = atoi(argv[3]);
	}
	if(argc >= 5) {
		SCALE_X = atof(argv[4]);
		SCALE_Y = atof(argv[5]);
	}
	if(argc >= 7) {
		MOVE_X = atof(argv[6]);
		MOVE_Y = atof(argv[7]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(WIN_X, WIN_Y);
	glutInitWindowPosition(100, 100);

	window = glutCreateWindow("Mandelbrot");

	glutDisplayFunc(disp);
	glutKeyboardFunc(keyb);
	glutMouseFunc(mouse);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	printf("calling glutMainLoop\n");
	glutMainLoop();

	return 0;
}

void disp(void) {
	printf("Doing Loop\n");

	printf("Iterationen: %i\n", ITERATION);
	printf("Auflösung: %i x %i\n", WIN_X, WIN_Y);
	printf("Skalierung: %f x %f\n", SCALE_X, SCALE_Y);
	printf("Move: %f x %f\n", MOVE_X, MOVE_Y);

	//file stuff
	printf("prepare image\n");
	fptr=fopen("test.tga", "w");
	putc(0,fptr);
    putc(0,fptr);
    putc(2,fptr);
    putc(0,fptr); putc(0,fptr);
    putc(0,fptr); putc(0,fptr);
    putc(0,fptr);
    putc(0,fptr); putc(0,fptr);
    putc(0,fptr); putc(0,fptr);
    putc((WIN_X & 0x00FF),fptr);
    putc((WIN_X & 0xFF00) / 256,fptr);
    putc((WIN_Y & 0x00FF),fptr);
    putc((WIN_Y & 0xFF00) / 256,fptr);
    putc(24,fptr);
    putc(0,fptr);
    printf("preparation done\n");

    printf("calculating\n");
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		for(int x = 0; x < WIN_X; x++) {
			for(int y = 0; y < WIN_Y; y++) {
				float px = pos_x(x);
				float py = pos_y(y);
				Color color;
				Vector v((px*SCALE_X)+MOVE_X, (py*SCALE_Y)+MOVE_Y);

				int m = mandelbrot(ITERATION, v);
				if(m > 0) {
					color.set_r((1.0/ITERATION)*m);
					color.set_g(0);
					color.set_b(0);
					glColor4f(color.get_r_float(), color.get_g_float(), color.get_b_float(), 1.0);
					glVertex2f(px, py);

					putc(color.get_b_int(),fptr); //b
					putc(color.get_g_int(),fptr); //g
					putc(color.get_r_int(),fptr); //r

				}
				else {
					//glColor4f(0.0, 0.0, 0.0, 1.0);
					//glVertex2f(px, py);

					putc((int)(0),fptr);
					putc((int)(0),fptr);
					putc((int)(0),fptr);
				}
				//printf("x:%f y:%f -> m:%i\n", px, py, m);
			}
		}
	glEnd();
	glFlush();

	printf("calculation done\n");
	fclose(fptr);
}

void keyb(unsigned char key, int x, int y) {
	if(key == 'q') {
		glutDestroyWindow(window);
		exit(0);
	}
	if(key == 'y') {
		ITERATION -= 1;
		glutPostRedisplay();
	}
	if(key == 'x') {
		ITERATION += 1;
		glutPostRedisplay();
	}
	if(key == 'c') {
		ITERATION -= 10;
		glutPostRedisplay();
	}
	if(key == 'v') {
		ITERATION += 10;
		glutPostRedisplay();
	}
	if(key == 'b') {
		ITERATION -= 100;
		glutPostRedisplay();
	}
	if(key == 'n') {
		ITERATION += 100;
		glutPostRedisplay();
	}
	if(key == 'm') {
		ITERATION -= 1000;
		glutPostRedisplay();
	}
	if(key == ',') {
		ITERATION += 1000;
		glutPostRedisplay();
	}
	if(key == '+') {
		SCALE_X -= SCALE_X*0.2;
		SCALE_Y -= SCALE_Y*0.2;
		glutPostRedisplay();
	}
	if(key == '-') {
		SCALE_X += SCALE_X*0.2;
		SCALE_Y += SCALE_Y*0.2;
		glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y) {
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		printf("Mouse: %i, %i\n", x, y);
		MOVE_X += pos_x(x)*SCALE_X;
		MOVE_Y -= pos_y(y)*SCALE_Y;
		glutPostRedisplay();
	}
}

int mandelbrot(int n, Vector c) {
	Vector z1, z2;
	z2.x = 0;
	z2.y = 0;
	int i = 1;
	while(i <= n) {
		z1 = z2;
		z2 = VectorOP::add(VectorOP::quad(z1), c);
		if(VectorOP::absolut(z2) >= 2) {
			return i;
		}
		i++;
	}
	return 0;
}

void make_matrix(int *m, int *maa) {
	//m = (int *)malloc(WIN_X*WIN_Y*sizeof(int));
	m = new int[WIN_X*WIN_Y];
	//maa = (int *)malloc(4*WIN_X*WIN_Y*sizeof(int));
	maa = new int[4*WIN_X*WIN_Y];
}
