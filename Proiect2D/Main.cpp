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
#include "ColoanaOficiala.h"
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

// Marimea zonei de joc
GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;

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

// Nr de puncte la care se mareste dificultatea
int pct = 1000;

// Jocul este in pauza
bool paused;

bool first_time_start = true;

// Pozitia liniilor delimitatoare
double delimiter_pos = 0;



////////////////////////////////////////////////////////////////////
//	Initializers
////////////////////////////////////////////////////////////////////

// Functia de initializare a ferestrei
void init(void)
{
	glClearColor(0.53f, 0.53f, 0.53f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

Inamic* genereazaInamic() {

	int randomizator = rand() % 100;
	if (randomizator < 40) {
		return new Masina(audio_engine);
	}
	else if (randomizator < 70) {
		return new Tir(audio_engine);
	}
	else if (randomizator < 90) {
		return new Ambulanta(audio_engine);
	}
	else {
		return new ColoanaOficiala(audio_engine);
	}

}

// Initializeaza toate variabilele de la inceputul jocului (Util pentru restart)
void initGame() {
	score = 0;

	if (first_time_start) {
		cuplu_de_betoniera_ISoundSource = audio_engine->getSoundSource(cuplu_de_betoniera);
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
		audio_engine->play2D(audio_engine->getSoundSource(crash_sound), false, false, true);
		return;
	}
	else if (std::count(enemy_y.begin(), enemy_y.end(), juc.get_y()) > 0 && ((*inamic).get_x() < juc.get_x() + (*inamic).get_coliziune() + 250) && !(inamic->get_a_claxonat())) {
		audio_engine->play2D(audio_engine->getSoundSource((*inamic).get_claxon()), false, false, true);
	}

	if (juc.get_x() >= 100 && cuplu_de_betoniera_one_time) {
		audio_engine->play2D(cuplu_de_betoniera_ISoundSource, false, false, true);
		cuplu_de_betoniera_one_time = false;
	}
	else if (juc.get_x() < 0) {
		cuplu_de_betoniera_one_time = true;
	}

	(*inamic).misca(10);

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
	case ' ':
		paused = !paused;
		break;
	case 'r':
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

void updateDelimiters() {
	delimiter_pos -= 6;

	if (delimiter_pos < -800)
		delimiter_pos = 0;
}

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

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);
	glutBitmapString(font, (const unsigned char*)caster);
}

void drawDelimiters() {
	for (int line = 0; line < 2; line++) {
		glPushMatrix();
		glTranslated(delimiter_pos, 0.0, 0.0);

		glLineWidth(15);

		// Prima linie de delimitare
		glBegin(GL_LINES);
		glVertex2i(0, 80);
		glVertex2i(100, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(200, 80);
		glVertex2i(300, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(400, 80);
		glVertex2i(500, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(600, 80);
		glVertex2i(700, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(800, 80);
		glVertex2i(900, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1000, 80);
		glVertex2i(1100, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1200, 80);
		glVertex2i(1300, 80);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1400, 80);
		glVertex2i(1500, 80);
		glEnd();


		// A doua linie de delimitare
		glBegin(GL_LINES);
		glVertex2i(0, 240);
		glVertex2i(100, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(200, 240);
		glVertex2i(300, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(400, 240);
		glVertex2i(500, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(600, 240);
		glVertex2i(700, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(800, 240);
		glVertex2i(900, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1000, 240);
		glVertex2i(1100, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1200, 240);
		glVertex2i(1300, 240);
		glEnd();

		glBegin(GL_LINES);
		glVertex2i(1400, 240);
		glVertex2i(1500, 240);
		glEnd();

		glPopMatrix();
	}
}

// Functia care deseneaza imaginea de fundal
void drawBackground() {
	glColor3f(0.4f, 0.91f, 0.36f);

	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();
	RenderString(100.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, std::string("Depaseste masinile!     Scor: ") + std::to_string(score));

	// Delimitare sosea
	glLineWidth(3);
	glColor3f(1, 1, 1);

	// Delimitam soseaua de iarba partea de jos
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Delimitam soseaua de iarba partea de sus
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Liniile intrerupte
	glPushMatrix();
	updateDelimiters();
	drawDelimiters();
	glPopMatrix();
}

// Functia care deseneaza tot
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground();


	if (ok == 0) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_8_BY_13, std::string("GAME OVER"));
	}

	juc.draw();
	(*inamic).draw();

	glutSwapBuffers();
	glFlush();

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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Depaseste masinile - mini game");
	init();
	initGame();
	glutDisplayFunc(drawScene);
	audio_engine->play2D(audio_engine->getSoundSource(start_sound), false, false, true);
	
	glutTimerFunc(9000, update, 0);
	
	glutKeyboardFunc(normalKeyboard);
	glutSpecialFunc(keyboard);

	
	glutMainLoop();
	audio_engine->drop();
}