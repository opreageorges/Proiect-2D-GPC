/*
* Pentru libraria de audio:
* Download link: https://www.ambiera.com/irrklang/downloads.html
* Se adauga:
* irrKlang.lib in Linker -> Input -> Additional Dependencies
* irrKlang-1.6.0\include in C\C++ -> General -> Additional Include Directories
* irrKlang-1.6.0\lib\Win32-visualStudio in Linker -> General -> Additional Library Directories
*/

#pragma warning(disable : 4996)
#include <windows.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <irrKlang.h>
#include <ik_ISound.h>
#include <vector>
#include<glm.hpp>
// Jucatorul
#include "Jucator.h"

// Versiunile de inamici
#include "Bikers.h"
#include "Masina.h"
#include "Ambulanta.h"
#include "Tir.h"
#include "Loader.h"

////////////////////////////////////////////////////////////////////
//	Variables
////////////////////////////////////////////////////////////////////

// Obiectul care incaraca modele 3D
Loader* l;

// Enginul audio
irrklang::ISoundEngine* audio_engine = irrklang::createIrrKlangDevice();

// Suntele din joc
const char* crash_sound = "Sound/car crash.wav";
const char* main_game_sound = "Sound/drive loop.wav";
const char* start_sound = "Sound/close dor, start engine, drive.wav";
const char* cuplu_de_betoniera = "Sound/cdb.wav";
bool cuplu_de_betoniera_one_time = true;
irrklang::ISoundSource* cuplu_de_betoniera_ISoundSource;
irrklang::ISound* main_game_sound_ISound;
irrklang::ISound* betoniera_ISound = audio_engine->play2D(audio_engine->getSoundSource(cuplu_de_betoniera), false, true, true);

//Radio
#define doNotLoadRadioBecauseItTakesAges false;
bool radioPaused = false;

#if !doNotLoadRadioBecauseItTakesAges
	const char* maneleStation = "Sound/Manele Station.mp3";
	const char* doomStation = "Sound/Doom Station.mp3";
	const char* popularaStation = "Sound/Populare Station.mp3";
	const char* psychedelicStation = "Sound/Psychedelic Trance Hallucinations Station.mp3";
	const char* rockStation = "Sound/Rock Station.mp3";
	const char* pianoStation = "Sound/Piano Station.mp3";
	const char* nfsmwStation = "Sound/NFS Most Wanted Station.mp3";
	const char* elevatorStation = "Sound/Elevator Station.mp3";
	const char* crazyfStation = "Sound/Crazy Frog Station.mp3";


	irrklang::ISound* manele = audio_engine->play2D(maneleStation, true, true, true);
	irrklang::ISound* doom = audio_engine->play2D(doomStation, true, true, true);
	irrklang::ISound* populara = audio_engine->play2D(popularaStation, true, true, true);
	irrklang::ISound* psychedelic = audio_engine->play2D(psychedelicStation, true, true, true);
	irrklang::ISound* rock = audio_engine->play2D(rockStation, true, true, true);
	irrklang::ISound* piano = audio_engine->play2D(pianoStation, true, true, true);
	irrklang::ISound* nfsmw = audio_engine->play2D(nfsmwStation, true, true, true);
	irrklang::ISound* elevator = audio_engine->play2D(elevatorStation, true, true, true);
	irrklang::ISound* crazyf = audio_engine->play2D(crazyfStation, true, true, true);
#endif

// Numarul maxim de framuri pe secunda
int fps = 60;

// Pentru calculul de fps 
int initial_time = (int)time(NULL);
int frames = 0;

// daca e 1 jocul merge daca e 0 ai pierdut
double ok;

// Initializeaza jucatorul si inamicul
Jucator juc;
Inamic* inamic;

// Scorul jucatorului
int score;

// Jocul este in pauza
bool paused;

bool first_time_start = true;


////////////////////////////////////////////////////////////////////
//	Initializers
////////////////////////////////////////////////////////////////////


Inamic* genereazaInamic() {
	Inamic* in;
	int randomizator = rand() % 100;
	if (randomizator < 40) {
		in = new Masina(audio_engine);
	}
	else if (randomizator < 70) {
		in = new Tir(audio_engine);
	}
	else if (randomizator < 90) {
		in = new Ambulanta(audio_engine);
	}
	else {
		in = new Bikers(audio_engine);
	}
	(*in).set_Loader(l);
	return in;

}

//Radio
void radioStation(int station) {
#if !doNotLoadRadioBecauseItTakesAges
	switch (station)
	{
	case 0:
		manele->setVolume(0);
		doom->setVolume(0);
		populara->setVolume(0);
		psychedelic->setVolume(0);
		piano->setVolume(0);
		elevator->setVolume(0);
		rock->setVolume(0);
		nfsmw->setVolume(0);
		crazyf->setVolume(0);
		break;
	case 1:
		radioStation(0);
		manele->setVolume(100);
		break;
	case 2:
		radioStation(0);
		doom->setVolume(100);
		break;
	case 3:
		radioStation(0);
		populara->setVolume(100);
		break;
	case 4:
		radioStation(0);
		psychedelic->setVolume(100);
		break;
	case 5:
		radioStation(0);
		piano->setVolume(100);
		break;
	case 6:
		radioStation(0);
		elevator->setVolume(100);
		break;
	case 7:
		radioStation(0);
		rock->setVolume(100);
		break;
	case 8:
		radioStation(0);
		nfsmw->setVolume(100);
		break;
	case 9:
		radioStation(0);
		crazyf->setVolume(100);
		break;
	case 10:
		radioStation(0);
		manele->setVolume(100);
		doom->setVolume(100);
		populara->setVolume(100);
		psychedelic->setVolume(100);
		piano->setVolume(100);
		elevator->setVolume(100);
		rock->setVolume(100);
		nfsmw->setVolume(100);
		crazyf->setVolume(100);
		break;
	default:
		break;
	}
#endif
}

// Initializeaza toate variabilele de la inceputul jocului (Util pentru restart)
void initGame() {
	score = 0;

	if (first_time_start) {
		audio_engine->getSoundSource(crash_sound);
		audio_engine->getSoundSource(start_sound);
		radioStation(0);
	}
	main_game_sound_ISound = audio_engine->play2D(audio_engine->getSoundSource(main_game_sound), true, true, true);

	juc = Jucator();
	juc.set_Loader(l);
	inamic = genereazaInamic();

	ok = 1;

	first_time_start = false;
	paused = false;
}

//Initializare verificare coliziune
void initGameColiziune() {
	score = 0;

	ok = 1;

	paused = false;
}

////////////////////////////////////////////////////////////////////
//	Functionality
////////////////////////////////////////////////////////////////////

// Functie care se ocupa de logica jocului in timp ce e activ
void game()
{
	std::vector<double> enemy_y = (*inamic).get_y();
	if (std::count(enemy_y.begin(), enemy_y.end(), juc.get_y()) > 0 && ((*inamic).get_x() < juc.get_x() + (*inamic).get_coliziune() && (*inamic).get_x() > juc.get_x() - (*inamic).get_coliziune() + 10)) {
		ok = 0;
		main_game_sound_ISound->stop();
		betoniera_ISound->stop();
		radioStation(0);
		audio_engine->play2D(audio_engine->getSoundSource(crash_sound), false, false, true);
		return;
	}
	else if (std::count(enemy_y.begin(), enemy_y.end(), juc.get_y()) > 0 && ((*inamic).get_x() < juc.get_x() + (*inamic).get_coliziune() + 45) && !(inamic->get_a_claxonat())) {
		audio_engine->play2D(audio_engine->getSoundSource((*inamic).get_claxon()), false, false, true);
	}

	if (juc.get_x() >= 10 && cuplu_de_betoniera_one_time) {
		//std::cout << "test";
		betoniera_ISound->setIsPaused(false);
		cuplu_de_betoniera_one_time = false;
	}
	else if (juc.get_x() < 0) {
		cuplu_de_betoniera_one_time = true;
	}

	(*inamic).misca(1);
	if (betoniera_ISound->isFinished()) {
		betoniera_ISound->setPlayPosition(0);
		betoniera_ISound->setIsPaused(true);
	}

	if ((*inamic).get_x() < juc.get_x() - ((*inamic).getDestroyCoord()))
	{
		score += (*inamic).getPuncte();
		delete inamic;
		inamic = genereazaInamic();
	}
}

// Functia care se ocupa de tastele speciale
void keyboard(int key, int x, int y)
{
	if (paused || ok == 0) {
		return;
	}
	switch (key) {
	case GLUT_KEY_UP:
		juc.miscasus();
		break;
	case GLUT_KEY_DOWN:
		juc.miscajos();
		break;
	case GLUT_KEY_RIGHT:
		juc.miscaDreapta();
		break;
	case GLUT_KEY_LEFT:
		juc.miscaStanga();
		break;
	}

}

// Functia care se ocupa de tastele normale
void normalKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '0':
		std::cout << juc.get_x();
		break;
	case ' ':
		paused = !paused;
		break;
	case 'r':
		main_game_sound_ISound->setIsPaused(true);
		initGame();
		break;
	case 'z':
		initGameColiziune();
		break;
	case 'm':
		radioStation(0);
		break;
	case '1':
		if (ok == 1) {
			radioStation(1);
		}
		else {
			radioStation(0);
		}
		break;
	case '2':
		if (ok == 1) {
			radioStation(2);
		}
		else {
			radioStation(0);
		}
		break;
	case '3':
		if (ok == 1) {
			radioStation(3);
		}
		else {
			radioStation(0);
		}
		break;
	case '4':
		if (ok == 1) {
			radioStation(4);
		}
		else {
			radioStation(0);
		}
		break;
	case '5':
		if (ok == 1) {
			radioStation(5);
		}
		else {
			radioStation(0);
		}
		break;
	case '6':
		if (ok == 1) {
			radioStation(6);
		}
		else {
			radioStation(0);
		}
		break;
	case '7':
		if (ok == 1) {
			radioStation(7);
		}
		else {
			radioStation(0);
		}
		break;
	case '8':
		if (ok == 1) {
			radioStation(8);
		}
		else {
			radioStation(0);
		}
		break;
	case '9':
		if (ok == 1) {
			radioStation(9);
		}
		else {
			radioStation(0);
		}
		break;
	case 'b':
		if (ok == 1) {
			radioStation(10);
		}
		else {
			radioStation(0);
		}
	}
}


void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	
	// Reset Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////
//	Update functions
////////////////////////////////////////////////////////////////////

// Functia care updateaza logica jocului
void update(int) {

	if (main_game_sound_ISound->getIsPaused()) {
		main_game_sound_ISound->setIsPaused(false);
	}

	if (!paused && ok == 1) {
		game();
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / fps, update, 0);
}

////////////////////////////////////////////////////////////////////
//	Draw functions
////////////////////////////////////////////////////////////////////

// Scrie un text pe ecran
void RenderString(float x, float y, void* font, const std::string sir)
{
	int lungime = sir.length();
	const unsigned char* caster = (const unsigned char*)sir.c_str();;
	glPushMatrix();
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char*)caster);
	glPopMatrix();
}

// Functia care deseneaza imaginea de fundal
void drawBackground() {
	glPushMatrix();
	float culoare_asfalt[4] = { 0.267, 0.267, 0.278 , 1.0};
	//glColor3f(0.267, 0.267, 0.278);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_asfalt);
	// Banda Stanga
	glBegin(GL_QUADS);
	glVertex3i(-10, 14, 0);// Stanga jos
	glVertex3i(-10, 5.5, 0); // Dreapta jos
	glVertex3i(200, 5.5, 0); // Dreapta sus
	glVertex3i(200, 14, 0);// Stanga sus
	glEnd();

	// Banda Mijloc
	glBegin(GL_QUADS);
	glVertex3i(-10, 5.5, 0);// Stanga jos
	glVertex3i(-10, -5.5, 0); // Dreapta jos
	glVertex3i(200, -5.5, 0); // Dreapta sus
	glVertex3i(200, 5.5, 0);// Stanga sus
	glEnd();

	// Banda Dreapta
	glBegin(GL_QUADS);
	glVertex3i(-10, -5.5, 0);// Stanga jos
	glVertex3i(-10, -14, 0); // Dreapta jos
	glVertex3i(200, -14, 0); // Dreapta sus
	glVertex3i(200, -5.5, 0);// Stanga sus
	glEnd();

	float culoare_iarba[4] = { 0.0, 0.604, 0.09 , 1.0 };
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_iarba);
	//glColor3f(0.0, 0.604, 0.09);
	// Iarba Stanga
	glPushMatrix();
	glTranslated(0, 21, 0.2);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);

	l->draw("padure");
	glPopMatrix();

	// Iarba Dreapta
	glPushMatrix();
	glTranslated(0, -21, 0.2);
	glRotated(90, 1, 0, 0);
	glRotated(90, 0, 1, 0);

	l->draw("padure");
	glPopMatrix();

	float culoare_linie[4] = { 0.949f, 0.953f, 0.957f , 1.0f };
	for (int i = 0; i < 100; i++) {
		for (int line = 0; line < 2; line++) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, culoare_linie);
			glBegin(GL_QUADS);
			glVertex3f(0 + i * 10, 5.5 - line * 10, 0.1);// Stanga jos
			glVertex3f(0 + i * 10, 4.5 - line * 10, 0.1); // Dreapta jos
			glVertex3f(5 + i * 10, 4.5 - line * 10, 0.1); // Dreapta sus
			glVertex3f(5 + i * 10, 5.5 - line * 10, 0.1);// Stanga sus
			glEnd();
		}
	}

	glPopMatrix();
}

// Functia care deseneaza tot
void drawScene(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	GLfloat lightpos[] = { -20, 0, 1, 1.0 };

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glLoadIdentity();
	gluLookAt(0 + juc.get_x(), 0 + juc.get_y(), 2,
		10 + juc.get_x(), 0 + juc.get_y(), 0,
		0.0f, 0.0f, 30.0f);

	drawBackground();

	juc.draw();
	(*inamic).draw();
	
	glDisable(GL_DEPTH);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	// Zona in care poti desena chestii 2D pentru HUD
	
	if (ok == 0) {
		RenderString(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, std::string("GAME OVER"));
	}

	RenderString(-100, -100, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Depaseste masinile!     Scor: ") + std::to_string(score));

	// Se termina zona
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH);
	glutSwapBuffers();
	//glFlush();

	// Calculeaza fps-ul
	frames++;
	int final_time = (int)time(NULL);
	if (final_time - initial_time == 1) {
		std::cout << frames << '\n';
		initial_time = final_time;
		frames = 0;
	}

}

////////////////////////////////////////////////////////////////////
//	Main
////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	glewExperimental = GL_TRUE;
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Depaseste masinile - mini game - Don't Press B");
	l = l->getInstance();
	initGame();

	l->loadOBJ("OBJS/logan/Dacia.fbx", "logan");
	//l->loadOBJ("OBJS/Inamic/Inamic.fbx", "inamic");
	l->loadOBJ("OBJS/Tir/Tir.fbx", "tir");
	l->loadOBJ("OBJS/Ambulanta/Ambulanta.fbx", "ambulanta");
	l->loadOBJ("OBJS/Bikers/Biker.fbx", "bikers");
	l->loadOBJ("OBJS/forest/Forest2.obj", "padure");
	//l->loadOBJ("OBJS/e46/e46.blend", "e46");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(changeSize);
	
	audio_engine->play2D(audio_engine->getSoundSource(start_sound), false, false, true);
#if !doNotLoadRadioBecauseItTakesAges
	if (!radioPaused) {
		radioPaused = !radioPaused;
		manele->setIsPaused(false);
		doom->setIsPaused(false);
		populara->setIsPaused(false);
		psychedelic->setIsPaused(false);
		rock->setIsPaused(false);
		piano->setIsPaused(false);
		nfsmw->setIsPaused(false);
		elevator->setIsPaused(false);
		crazyf->setIsPaused(false);
	}
#endif
	glutTimerFunc(60, update, 0);
	
	glutKeyboardFunc(normalKeyboard);
	glutSpecialFunc(keyboard);
	
	glutMainLoop();

	audio_engine->drop();
}