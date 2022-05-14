/*
* Pentru libraria de audio:
* Download link: https://www.ambiera.com/irrklang/downloads.html
* Se adauga:
* irrKlang.lib in Linker -> Input -> Additional Dependencies
* irrKlang-1.6.0\include in C\C++ -> General -> Additional Include Directories
* irrKlang-1.6.0\lib\Win32-visualStudio in Linker -> General -> Additional Library Directories
*/

#include <windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <irrKlang.h>
#include <ik_ISound.h>

// Jucatorul
#include "Jucator.h"

// Versiunile de inamici
#include "Bikers.h"
#include "Masina.h"
#include "Ambulanta.h"
#include "Tir.h"


////////////////////////////////////////////////////////////////////
//	Variables
////////////////////////////////////////////////////////////////////

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

	int randomizator = rand() % 100;
	if (randomizator < 400) {
		return new Masina(audio_engine);
	}
	else if (randomizator < 70) {
		return new Tir(audio_engine);
	}
	else if (randomizator < 90) {
		return new Ambulanta(audio_engine);
	}
	else {
		return new Bikers(audio_engine);
	}

}

// Initializeaza toate variabilele de la inceputul jocului (Util pentru restart)
void initGame() {
	score = 0;

	if (first_time_start) {
		audio_engine->getSoundSource(crash_sound);
		audio_engine->getSoundSource(start_sound);
	}
	main_game_sound_ISound = audio_engine->play2D(audio_engine->getSoundSource(main_game_sound), true, true, true);

	juc = Jucator();
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
	if (std::count(enemy_y.begin(), enemy_y.end(), juc.get_y()) > 0 && ((*inamic).get_x() < juc.get_x() + (*inamic).get_coliziune() && (*inamic).get_x() > juc.get_x() - (*inamic).get_coliziune())) {
		ok = 0;
		main_game_sound_ISound->stop();
		betoniera_ISound->stop();
		audio_engine->play2D(audio_engine->getSoundSource(crash_sound), false, false, true);
		return;
	}
	else if (std::count(enemy_y.begin(), enemy_y.end(), juc.get_y()) > 0 && ((*inamic).get_x() < juc.get_x() + (*inamic).get_coliziune() + 45) && !(inamic->get_a_claxonat())) {
		audio_engine->play2D(audio_engine->getSoundSource((*inamic).get_claxon()), false, false, true);
	}

	if (juc.get_x() >= 10 && cuplu_de_betoniera_one_time) {
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

	if ((*inamic).get_x() < ((*inamic).getDestroyCoord()))
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
	case '1':
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
	}
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
	const unsigned char *caster = (const unsigned char*)sir.c_str();;

	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char*)caster);
}

void drawDelimiters() {
	for (int i = 0; i < 100; i++) {
		for (int line = 0; line < 2; line++) {
			glColor3f(0.949, 0.953, 0.957);
			glBegin(GL_QUADS);
			glVertex3i(0 + i* 10, 5.5 - line * 10, 0);// Stanga jos
			glVertex3i(0 + i * 10, 4.5 - line * 10, 0); // Dreapta jos
			glVertex3i(5 + i * 10, 4.5 - line * 10, 0); // Dreapta sus
			glVertex3i(5 + i * 10, 5.5 - line * 10, 0);// Stanga sus
			glEnd();
		}
	}
}

// Functia care deseneaza imaginea de fundal
void drawBackground() {
	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat rosu[] = { 1.0, 0.0, 0.0, 0.0 };


	glColor3f(0.267, 0.267, 0.278);

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

	glColor3f(0.0, 0.604, 0.09);
	// Iarba Stanga
	glBegin(GL_QUADS);
	glVertex3i(-10, 140, 0);// Stanga jos
	glVertex3i(-10, 14, 0); // Dreapta jos
	glVertex3i(200, 14, 0); // Dreapta sus
	glVertex3i(200, 140, 0);// Stanga sus
	glEnd();

	// Iarba Dreapta
	glBegin(GL_QUADS);
	glVertex3i(-10, -14, 0);// Stanga jos
	glVertex3i(-10, -140, 0); // Dreapta jos
	glVertex3i(200, -140, 0); // Dreapta sus
	glVertex3i(200, -14, 0);// Stanga sus
	glEnd();


	
	drawDelimiters();

}

// Functia care deseneaza tot
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat pozitial0[] = { 400.0, 300.0, 5.0, 0.0 };
	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat gri[] = { 0.3, 0.3, 0.3, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, alb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, alb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, negru);*/


	glLoadIdentity();
	gluLookAt(0 + juc.get_x(), 0 + juc.get_y(), 2,
		10 + juc.get_x(), 0 + juc.get_y(), 0,
		0.0f, 0.0f, 30.0f);

	drawBackground();

	if (ok == 0) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_8_BY_13, std::string("GAME OVER"));
	}

	juc.draw();
	(*inamic).draw();

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
	RenderString(0, 0, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Depaseste masinile!     Scor: ") + std::to_string(score));
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Depaseste masinile - mini game");
	initGame();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(changeSize);
	//audio_engine->play2D(audio_engine->getSoundSource(start_sound), false, false, true);
	
	glutTimerFunc(60, update, 0);
	
	glutKeyboardFunc(normalKeyboard);
	glutSpecialFunc(keyboard);
	
	glutMainLoop();
	audio_engine->drop();
}