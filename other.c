#include "funcs.h"

//NOTE: Fajl sa nekim ostalim funkcijama (~vezanim za sAm opengl)

//Funkcija koja reaguje na otpustanje dugmeta (koriscena za izgladjivanje animacije pomeranja igraca)
void on_keyboard_release(unsigned char key, int x, int y) {
	
	switch(key) {
		case 'a':
			animation_ongoing_2 = 0;
			break;
		case 'd':
			animation_ongoing_2 = 0;
			break;
	}
}

//Funkcija za pomeranje igraca u levo
void on_timer_a(int value3) {
	
	if (value3 != 0)
		return;
	
	if (x_igrac < 3.8) {
		x_igrac += 0.0043;
	}
	
	
	
	if (animation_ongoing_2) {
        glutTimerFunc(1, on_timer_a, 0);
	}
}

//Funkcija za pomeranje igraca u desno
void on_timer_d(int value2) {
	
	if (value2 != 0)
		return;
	
	if (x_igrac > -3.8) {
		x_igrac -= 0.0043;
	}

	if (animation_ongoing_2) {
        glutTimerFunc(1, on_timer_d, 0);
	}
}

//Funkcija za pomeranje ekrana, tj "kamere" (cija se brzina pomeranja postepeno uvecava)
void on_timer(int value) {
	
	//Provera callbacka funkcije
	if (value != 0)
		return;
	
	pomeranje -= v_brzine;
	if (exit_flag !=2) {
		pomeranje_y -= v_brzine;
	}
	else {
		pomeranje_y -= 3*v_brzine;
	}
	rotacija_igraca -= 5;
	
	//Ponovo se iscrtava slika
	glutPostRedisplay();
	
	if (animation_ongoing) {
		glutTimerFunc(17, on_timer, 0);
	}
}

