#include "funcs.h"

//Dimenzije glavnog prozora
static int w_width = 800;
static int w_height = 800;

/*NOTE: Flegovi*/
int	animation_ongoing = 0;
int	animation_ongoing_2 = 0;
int play_flag = 0;
int restart_flag = 0;
int transf_flag = 0;
int transf_flag2 = 0;

/*NOTE: Koordinate*/
float x_igrac = 0;
float y_igrac = 0;

/*NOTE: Ostalo*/
float pomeranje = 0;
float pomeranje_y = 0;

//Funkcije
static void on_reshape(int width, int height);
static void on_keyboard_press(unsigned char key, int x, int y);
static void on_display(void);

int main(int argc, char** argv) {
		
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	glutInitWindowSize(w_width, w_height);
	glutInitWindowPosition(250, 50);
	glutCreateWindow("Put kroz dimenziju");
	
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard_press);
	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(on_keyboard_release);
	
	glClearColor(0.1, 0.1, 0.1, 0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	//Generisanje prepreka
	rand_prepreke();
	
	glutMainLoop();
	
	return 0;
}

static void on_reshape(int width, int height) {
	w_width = width;
	w_height = height;
}

//Funkcija koja reaguje na sAm pritisak dugmeta
static void on_keyboard_press(unsigned char key, int x, int y) {
	
	switch(key) {
		case 27:
			exit(0);
			break;
		case 'p':
			if (!animation_ongoing && !play_flag) {
				glutTimerFunc(17, on_timer, 0);
				animation_ongoing = 1;
				play_flag = 1;
				break;
			}
			break;
		case 'r':
			if (restart_flag) {
				resetuj_igru();
			}
			break;
		case 'a':
			if (!animation_ongoing_2) {
				if (!transf_flag || transf_flag == 2) {
					glutTimerFunc(1, on_timer_a, 0);
					animation_ongoing_2 = 1;
				}
				else {
					glutTimerFunc(1, on_timer_d, 0);
					animation_ongoing_2 = 1;
				}
				break;
			}
		case 'd':
			if (!animation_ongoing_2) {
				if (!transf_flag || transf_flag == 2) {
					glutTimerFunc(1, on_timer_d, 0);
					animation_ongoing_2 = 1;
				}
				else {
					glutTimerFunc(1, on_timer_a, 0);
					animation_ongoing_2 = 1;
				}
			}
			break;
	}
}

//Glavna funkcija za prikaz
static void on_display(void) {

	GLfloat light_position[] = {1, 0, 0, 0};
	GLfloat light_ambient[] = {0.8, 0.8, 0.8, 1};
	GLfloat light_diffuse[] = {1, 1, 1, 1};	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, w_width, w_height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(30, 1, 1, 0);
	
	//Ugao gledanja na objekat
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(15, 0, 0,
						0, -1, 0, 
					  0, 1, 0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	
	//"Pomeranje sveta"
	glTranslatef(0, pomeranje-1.5, 0);
	
	//Tracker za poen(e)
	nacrtaj_tracker();
	
	//Crtanja
	if (transf_flag) {
		transformacija_sveta();
		nacrtaj_bod();
	}

	if (transf_flag2) {
		transformacija_sveta2();
		nacrtaj_bod();
	}
	
	nacrtaj_cilj();
	nacrtaj_prepreke();
	nacrtaj_igraca();
	
	//Provera, u svakoj iteraciji, da li je doslo do kolizije
	if (exit_flag != 2) {
		kolizija();
	}
	
	glFlush();
	glutSwapBuffers();
}
