#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define NIZ_SIZE 512

/*NOTE: FLEGOVI */
//Flegovi za kontrolu animacije
extern int animation_ongoing;
extern int animation_ongoing_2;
//Fleg za bodove
extern int bod_flag;
//Fleg za pokretanje kraja igre
extern int exit_flag;
//Flag za ispomoc kod oscilacije prepreka na 2. nivou
extern int osci_flag;
//Flegovi za regulisanje pokretanja i restarovanja igre
extern int play_flag;
extern int restart_flag;
//Tracker flag za nestajanje istog prilikom skupljanja
extern int tracker_flag;
//Flegovi za 1. i 2. transformaciju sveta
extern int transf_flag;
extern int transf_flag2;

/*NOTE: KOORDINATE */
//Pozicija bOda
extern float bod_pozicija;
//Koordinate ciljeva (y-koordinate, naravno)
extern float cilj1;
extern float cilj2;
extern float cilj3;
//Poluprecnik igraca
extern float igrac_r;
//Koordinate igraca 
extern float x_igrac;
extern float y_igrac;
//Koordinate prepreka
extern float x_prepreka;
extern float y_prepreka;

//Struktura za koordinate svake prepreke
typedef struct {
	float y_pom;
	float x_pom;
}Koordinate;
Koordinate niz_k[NIZ_SIZE];

/*NOTE: OSTALO */
//Niz koordinata pocetnih bOja
extern float boje[3];
//Pomocna za iscrtavanje cilja
extern int cilj2_pom;
//Velicina poluprecnika prepreka
extern float globalSize;
//Staticki niz za random promenljive
extern float niz[NIZ_SIZE];
//Pomeranje ekrana i pomeranje igraca
extern float pomeranje;
extern float pomeranje_y;
//Pomocna za iscrtavanje bodova
extern int pom_bod;
//Pomocna za rad sa crtanjem prepreka (1)
extern int provera_za_n;
//Ugao rotacije igraca (oko svoje ose)
extern int rotacija_igraca;
//Pomocne za rad sa crtanjem prepreka (2)
extern int total_broj;
//Vektor brzine pomeranja ekrana (i igraca)
extern float v_brzine;

/*NOTE: FUNKCIJE */
//U fajlu other.c
void on_keyboard_release(unsigned char key, int x, int y);
void on_timer_a(int value3);
void on_timer_d(int value2);
void on_timer(int value);
//U fajlu funcs.c
void kolizija(void);
void nacrtaj_bod(void);
void nacrtaj_cilj(void);
void nacrtaj_igraca(void);
void nacrtaj_prepreke(void);
void nacrtaj_prepreke_2(void);
void nacrtaj_tracker(void);
void rand_prepreke(void);
void resetuj_igru(void);
void transformacija_sveta(void);
void transformacija_sveta2(void);
