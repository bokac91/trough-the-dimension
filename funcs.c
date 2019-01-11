#include "funcs.h"

//NOTE: Fajl sa funkcijama

/*NOTE: Flagovi*/
int bod_flag = 0;
int exit_flag = 0;
int osci_flag = 0;
int tracker_flag = 0;

/*NOTE: Koordinate*/
float bod_pozicija = 2;
float cilj1 = 22.5;
float cilj2 = 0;
float cilj3 = 0;
float igrac_r = 0.2;
float x_prepreka = 0;
float y_prepreka = 0;

/*NOTE: Ostalo*/
float boje[3] = {0.3, 0.3, 0};
int cilj2_pom = 0;
float globalSize = 0.3;
float niz[NIZ_SIZE];
int pom_bod = 35;
int provera_za_n = 0;
int rotacija_igraca = 0;
int total_broj = 1;
float v_brzine = 0.04;

//Kolizija
void kolizija(void) {
	
	int i;
	//Rastojanje izmedju centara igraca i prepreke
	float d;
	//NOTE: Ovde bi, tehnicki, trebalo da promenljivu 'i' takodje menjamo, da ide prvo od 0, pa od 21, itd, ali nije mi uspelo sa tom
	//NOTE: optimizacijom, treba to proveriti jos za svaki slucaj
	for (i=0; i<21*total_broj; i++) {
		
		//Mini optimizacija = proveravamo da li je igrac "negde blizu" objekta
		if (y_igrac > niz_k[i].y_pom-1) {
		
			//Trenutno rastojanje izmedju centara moja dva objekta
			d = sqrtf( fabs(powf((niz_k[i].x_pom - x_igrac), 2) + (powf((niz_k[i].y_pom - y_igrac), 2))) );
			
			if (d < igrac_r + (globalSize-0.025)) {
				animation_ongoing = 0;
				restart_flag = 1;
			}
		}
	}
	
}

//Crtanje bodova
void nacrtaj_bod(void) {
	
	//Materijalna svojstva bodova
	//Boja - plava
	GLfloat ambient_coeffs[] = {0, 0, 1, 1};
	GLfloat diffuse_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs[] = {0.6, 0.6, 0.6, 1};
	GLfloat shininess = 30;

	if (transf_flag != 2) {
		igrac_r = 0.15;
	}
	
	float d, pom_bod_x;
	int id_boda;
	
	//Za 1. nivo
	if (transf_flag == 1) {
		
		//Iscrtavanje bodova na svakih 15 pozicija
		if (((pom_bod-y_igrac >= 0) && (pom_bod-y_igrac <= 10)) ||
				((y_igrac-pom_bod >= 0) && (y_igrac-pom_bod <= 2))) {
			
			//Postavljanje x koordinate bOda (svaki parni clan niza je SIGURNO pozitivan broj) da bude 
			//tacno izmedju dve prepreke u jednom redu
			id_boda = ((pom_bod*2)-3)-3;
			if (fabs(niz_k[id_boda].x_pom) > fabs(niz_k[id_boda+1].x_pom)) {
				pom_bod_x = niz_k[id_boda].x_pom - ((niz_k[id_boda].x_pom - niz_k[id_boda+1].x_pom)/2.0);
			}
			else if (fabs(niz_k[id_boda].x_pom) < fabs(niz_k[id_boda+1].x_pom)) {
				pom_bod_x = niz_k[id_boda].x_pom - (-(niz_k[id_boda+1].x_pom - niz_k[id_boda].x_pom)/2.0);
			}

			//Nacrtaj plavicasti bOd
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glTranslatef(0, pom_bod, pom_bod_x);
				glutSolidSphere(0.15, 30, 30);
			glPopMatrix();
		
			//Odredjivanje rastojanja i provera kolizije
			d = sqrtf( fabs(powf((x_igrac - pom_bod_x), 2) + (powf((pom_bod - y_igrac), 2))) );
			
			if (d <= igrac_r + 0.15) {
				transf_flag = 2;
				tracker_flag = 1;
				cilj2_pom = pom_bod;
			}
		}
		//Uvecanje promenljive za iscrtavanje narednog bOda
		if ((y_igrac-pom_bod >= 0) && (pom_bod-y_igrac <= -2.1)) {
			//Uvecavam za, npr, 12, kako bih uvek imao negativan broj
			pom_bod += 14;
		}
	}
	
	//Za 2. nivo
	if ((transf_flag == 0 || transf_flag == 2) && transf_flag2 != 0 && transf_flag2 != 2) {

		//Iscrtavanje bodova na svakih 15 pozicija
		if (((pom_bod-y_igrac >= 0) && (pom_bod-y_igrac <= 10)) ||
				((y_igrac-pom_bod >= 0) && (y_igrac-pom_bod <= 2))) {
			
			//Postavljanje x koordinate bOda (svaki parni clan niza je SIGURNO pozitivan broj) da bude 
			//tacno izmedju dve prepreke u jednom redu
			id_boda = ((pom_bod*2)-3)-3;
			if (fabs(niz_k[id_boda].x_pom) > fabs(niz_k[id_boda+1].x_pom)) {
				pom_bod_x = niz_k[id_boda].x_pom - ((niz_k[id_boda].x_pom - niz_k[id_boda+1].x_pom)/2.0);
			}
			else if (fabs(niz_k[id_boda].x_pom) < fabs(niz_k[id_boda+1].x_pom)) {
				pom_bod_x = niz_k[id_boda].x_pom - (-(niz_k[id_boda+1].x_pom - niz_k[id_boda].x_pom)/2.0);
			}
			
			//Boja - zelena
			GLfloat ambient_coeffs2[] = {0, 1, 0, 1};
			GLfloat diffuse_coeffs2[] = {0.3, 0.3, 0.3, 1};
			GLfloat specular_coeffs2[] = {0.6, 0.6, 0.6, 1};
			GLfloat shininess2 = 30;
			//Nacrtaj zeleni bOd
			glPushMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
				glTranslatef(0, pom_bod, pom_bod_x);
				glutSolidSphere(0.15, 30, 30);
			glPopMatrix();
		
			//Odredjivanje rastojanja i provera kolizije
			d = sqrtf( fabs(powf((x_igrac - pom_bod_x), 2) + (powf((pom_bod - y_igrac), 2))) );
			
			if (d <= igrac_r + 0.15) {
				transf_flag2 = 2;
				tracker_flag = 2;
				exit_flag = 1;
			}
		}
		
		//Uvecanje promenljive za iscrtavanje narednog bOda
		if ((y_igrac-pom_bod >= 0) && (pom_bod-y_igrac <= -2.1)) {
			//Uvecavam za, npr, 12, kako bih uvek imao negativan broj
			pom_bod += 14;
		}
	}
	
}

//Crtanje cilja
void nacrtaj_cilj(void) {
	
	//Boja - crvena
	GLfloat ambient_coeffs[] = {0.7, 0, 0, 1};
	GLfloat diffuse_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs[] = {0.6, 0.6, 0.6, 1};
	GLfloat shininess = 30;
	
	if (y_igrac >= 15 && y_igrac <= 24) {
		
			glBegin(GL_LINES);
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glVertex3f(0, cilj1, -5);
				glVertex3f(0, cilj1, 5);
			glEnd();
		}
	
	if ((y_igrac >= cilj2_pom+10 && y_igrac <= cilj2_pom+19)) {
		
		if (cilj2_pom !=0) {
			
			cilj2 = cilj2_pom + 17.5;
			glBegin(GL_LINES);
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glVertex3f(0, cilj2, -5);
				glVertex3f(0, cilj2, 5);
			glEnd();
		}
	}

	if (exit_flag == 2) {
		if (y_igrac >= cilj3 + 10) {
			animation_ongoing = 0;
			restart_flag = 1;
		}
	}
	
	//Ako je uopste pokupljen 2. poen, mozemo da razmatramo crtanje narednog (poslednjeg) cilja
	if (transf_flag2 == 2) {
		
		if ((y_igrac >= pom_bod+15 && y_igrac <= pom_bod+30)) {
			
			cilj3 = pom_bod+22.5;
			glBegin(GL_LINES);
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glVertex3f(0, cilj3, -5);
				glVertex3f(0, cilj3, 5);
			glEnd();			

			if (y_igrac >= cilj3) {
				exit_flag = 2;
			}
		}
	}
}

//Crtanje igraca
void nacrtaj_igraca(void) {
	
	//Materijalna svojstva igraca
	//Boja - crvena
	GLfloat ambient_coeffs[] = {0.3, 0, 0, 1};
	GLfloat diffuse_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs[] = {0, 0, 0, 1};
	GLfloat shininess = 0;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	
	//NOTE: Ova koordinata pocinje od -2, pa raste.. (kretanje "na gore")
	y_igrac = -(pomeranje_y+2);
	glPushMatrix();
		glTranslatef(0, y_igrac, x_igrac);
		if (transf_flag == 1) {
			glRotatef(rotacija_igraca, 1, 1, 0);
			glutSolidSphere(igrac_r, 10, 10);
		}
		else if (transf_flag2 == 1) {
			glRotatef(rotacija_igraca, 1, 1, 1);
			glutSolidSphere(igrac_r, 2, 3);
		}
		else {
			glRotatef(rotacija_igraca, 1, 1, 0);
			glutWireSphere(igrac_r, 10, 10);
		}
	glPopMatrix();
	
	//Tri kockice ispod igraca (for fun)
	if (animation_ongoing) {
		glPushMatrix();
			glColor3f((0-pomeranje)/7.0, (0-pomeranje)/7.0, (0-pomeranje)/7.0);
			glTranslatef(0, y_igrac-0.25, x_igrac+0.1);
			glutSolidCube(0.05);
		glPopMatrix();	
		glPushMatrix();
			glColor3f((0-pomeranje)/7.0, (0-pomeranje)/7.0, (0-pomeranje)/7.0);
			glTranslatef(0, y_igrac-0.3, x_igrac);
			glutSolidCube(0.05);
		glPopMatrix();	
		glPushMatrix();
			glColor3f((0-pomeranje)/7.0, (0-pomeranje)/7.0, (0-pomeranje)/7.0);
			glTranslatef(0, y_igrac-0.25, x_igrac-0.1);
			glutSolidCube(0.05);
		glPopMatrix();	
	}
	
	//NOTE: Provera da li se presao cilj!
	float dodir;
	
	//Prelazak prvog cilja
	if (cilj1 > y_igrac) {
		dodir = cilj1 - y_igrac;
		if (dodir >= 0.018 && dodir <= 0.020) {
			transf_flag = 1;
		}
	}
	//Prelazak drugog cilja
	else if (cilj2 > y_igrac) {
		dodir = cilj2 - y_igrac;
		if (dodir >= 0.018 && dodir <= 0.020) {
			transf_flag2 = 1;
		}
	}
}

//Crtanje prepreka
void nacrtaj_prepreke(void) {
	
	int n = provera_za_n;
	
	//Materijalna svojstva prepreka
	//Boja - zuta
	GLfloat ambient_coeffs[] = {boje[0], boje[1], boje[2], 1};
	GLfloat diffuse_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat shininess = 25;
	
	while (n < (total_broj*22)) {
		
		//Ovako pravimo dvostruke prepreke jer delimo celobrojno
		y_prepreka = 3 + (n/2);
		x_prepreka = pow(-1, n)*niz[n];
		
		glPushMatrix();
			//glColor3f(boje[0], boje[1], boje[2]);
			//Koordinate objekta: (0, 1+(n/2), -1^(n) * randomBroj)
			//odnosno, u primeni: (0, 1, randomBroj), (0, 1.5, -randomBroj2), (0, 2, randomBroj3),...
			glTranslatef(0, y_prepreka, x_prepreka);
			glRotatef(30+rotacija_igraca, 0, 1, 1);
			//Smestanje svih koordinata u niz, u paru
			niz_k[n].y_pom = y_prepreka;
			niz_k[n].x_pom = x_prepreka;
			//Crtanje sfera prepreka/meteora prepreka
			if (transf_flag2 == 1) {
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				nacrtaj_prepreke_2();
			}
			else if (!transf_flag || transf_flag == 2) {
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glutWireSphere(globalSize, 15, 15);
			}
			else {
				shininess = 0.3;
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
				glMaterialf(GL_FRONT, GL_SHININESS, shininess);
				glutSolidSphere(globalSize, 5, 5);
			}
		glPopMatrix();
		
		n++;
		//NOTE: 0.023 je "magican broj" u slucaju mog projekta = ~ garantuje da samo jednom koordinata Y igraca bude u intervalu ovom dole
		if ((y_igrac <= (total_broj * 7) + 0.023) && (y_igrac >= (total_broj * 7) - 0.023)) {
			total_broj += 1;
			provera_za_n += 5;
		}
	}
}

void nacrtaj_prepreke_2(void) {
	
	if (!osci_flag) {
		if (globalSize < 0.47) {
			globalSize += 0.000025;
		}
		else {
			osci_flag = 1;
		}
	}
	else {
		if (globalSize >= 0.2) {
			globalSize -= 0.000025;
		}
		else {
			osci_flag = 0;
		}
	}
	
	glutSolidSphere(globalSize, 3, 6);
}

//Tracker u donjem-levom uglu za pracenje pokupljenih bodova
void nacrtaj_tracker(void) {
	
	//Boja - plava
	GLfloat ambient_coeffs[] = {0, 0, 1, 1};
	GLfloat diffuse_coeffs[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs[] = {0.6, 0.6, 0.6, 1};
	GLfloat shininess = 30;
	//Boja - zelena
	GLfloat ambient_coeffs2[] = {0, 1, 0, 1};
	GLfloat diffuse_coeffs2[] = {0.3, 0.3, 0.3, 1};
	GLfloat specular_coeffs2[] = {0.6, 0.6, 0.6, 1};
	GLfloat shininess2 = 30;
	
	if (!tracker_flag) {
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
			glMaterialf(GL_FRONT, GL_SHININESS, shininess);
			glTranslatef(0, -3.2-pomeranje, 3.4);
			glutSolidSphere(0.1, 20, 20);
		glPopMatrix();	
	}
	if (tracker_flag != 2) {
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs2);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs2);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs2);
			glMaterialf(GL_FRONT, GL_SHININESS, shininess2);
			glTranslatef(0, -3.2-pomeranje, 3.7);
			glutSolidSphere(0.1, 20, 20);
		glPopMatrix();	
	}
}

//Generisanje prepreka na random mestima
void rand_prepreke(void) {
	
	srand(time(NULL));
	int i=0;
	float r, max = 3.5;
	
	for (i=0; i<NIZ_SIZE; i++) {
		r = ((float)rand()/(float)RAND_MAX)*max;
		niz[i] = r;
	}
}

void resetuj_igru(void) {
	
	animation_ongoing = 1;
	restart_flag = 0;
	bod_flag = 0;
	transf_flag = 0;
	transf_flag2 = 0;
	tracker_flag = 0;
	osci_flag = 0;
	exit_flag = 0;
	
	pomeranje = 0;
	pomeranje_y = 0;
	
	y_igrac = -(pomeranje_y+3);	
	x_igrac = 0;
	igrac_r = 0.2;
				
	v_brzine = 0.04;
	rotacija_igraca = 0;
	total_broj = 1;
	provera_za_n = 0;
	pom_bod = 35;
	cilj2_pom = 0;
	
	//Za slucaj da je igrac izgubio dok je u "obrnutom univerzumu", vraca se sve na default
	transf_flag = 0;
	glClearColor(0.1, 0.1, 0.1, 0);
	boje[0] = 0.3;
	boje[1] = 0.3;
	boje[2] = 0;
	globalSize = 0.3;
				
	//Ponovno rasporedjivanje prepreka!
	rand_prepreke();
	//Pokretanje ispocetka
	glutTimerFunc(20, on_timer, 0);
}

//Prva transformacija sveta
void transformacija_sveta(void) {
	
	if (transf_flag == 1) {
		glClearColor(1, 1, 1, 0);
		boje[0] =	0.05;
		boje[1] = 0.05;
		boje[2] = 0;
		globalSize = 0.4;	
	}
	else if (transf_flag == 2) {
		glClearColor(0.1, 0.1, 0.1, 0);
		boje[0] = 0.3;
		boje[1] = 0.3;
		boje[2] = 0;
		globalSize = 0.3;	
		igrac_r = 0.2;
	}
}

//Druga transformacija sveta
void transformacija_sveta2(void) {
	
	if (transf_flag2 == 1) {
		transf_flag = 0;
		glClearColor(0, 0, 0, 0);
		boje[0] = 0.4;
		boje[1] = 0.48725;
		boje[2] = 0.4745;
	}
	else if (transf_flag2 == 2) {
		glClearColor(0.1, 0.1, 0.1, 0);
		boje[0] = 0.3;
		boje[1] = 0.3;
		boje[2] = 0;
		globalSize = 0.3;	
		igrac_r = 0.2;
	}
}
