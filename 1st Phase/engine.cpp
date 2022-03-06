#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>

#include "tinyxml/tinyxml2.h"

using namespace std;
using std::vector;


struct Coords
{
	float xx;
	float yy;
	float zz;
};


vector<Coords> triangles;

//no need to change
void changeSize(int w, int h) {

	if(h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glViewport(0, 0, w, h);
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

// desenha o eixo
void drawAxis() {

	glBegin(GL_LINES);

	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);

	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);

	glEnd();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawAxis();

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < triangles.size(); i += 3) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(triangles[i].xx, triangles[i].yy, triangles[i].zz);
		glVertex3f(triangles[i + 1].xx, triangles[i + 1].yy, triangles[i + 1].zz);
		glVertex3f(triangles[i + 2].xx, triangles[i + 2].yy, triangles[i + 2].zz);
	}

	glEnd();
	glutSwapBuffers();
}


void readFile(string fname) {
	string line;
	ifstream file(fname);

	if (file.fail()) {
		throw std::ios_base::failure(string("Ficheiro não encontrado: ") + fname);
	}

	else {
		while (getline(file, line)) {
			size_t pos;

			float x, y, z;

			x = std::stof(line, &pos);
			line.erase(0, pos + 1);
			y = std::stof(line, &pos);
			line.erase(0, pos + 1);
			z = std::stof(line, &pos);

			struct Coords Aux;
			Aux.xx = x;
			Aux.yy = y;
			Aux.zz = z;

			triangles.push_back(Aux);
		}
	}
	file.close();
}

void readXML(string f_path) {
	XMLDocument xmlDoc;
	XMLElement* element;

	if (!(xmlDoc.LoadFile(f_path.c_str()))) {

		element = xmlDoc.FirstChildElement();
		for (element = element->FirstChildElement(); element; element = element->NextSiblingElement()) {
			string ficheiro = element->Attribute("file");
			readFile(ficheiro);
		}
	}
	else {
		printf("XML File %s could not be found", f_path.c_str());
	}
}

/*
// write function to process keyboard events
void keys(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			zz -= 0.05f;
			glutPostRedisplay();
			break;

		case 's':
			zz += 0.05f;
			glutPostRedisplay();
			break;

		case 'a':
			xx -= 0.05f;
			glutPostRedisplay();
			break;

		case 'd':
			xx += 0.05f;
			glutPostRedisplay();
			break;

		case 'q':
			angle += 0.5f;
			glutPostRedisplay();
			break;

		case 'e':
			angle -= 0.5f;
			glutPostRedisplay();
			break;

		case ' ':
			xx = 0.0f;
			yy = 0.0f;
			zz = 0.0f;
			angle = 0.0f;
			sy = 1.0f;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glutPostRedisplay();
			break;
		
		default:
			break;
	}
}
*/

/*
void skeys(int key_code, int x, int y){
	switch (key_code) {

		case GLUT_KEY_DOWN:
			sy -= 0.1f;
			glutPostRedisplay();
			break;

		case GLUT_KEY_UP:
			sy += 0.1f;
			glutPostRedisplay();
			break;

		case GLUT_KEY_F1:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glutPostRedisplay();
			break;

		case GLUT_KEY_F2:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glutPostRedisplay();
			break;

		case GLUT_KEY_F3:
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glutPostRedisplay();
			break;

		default:
			break;
	}
}
*/

int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(80,80);
	glutInitWindowSize(1500,1000);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	
// put here the registration of the keyboard callbacks
	//glutKeyboardFunc(keys);
	//glutSpecialFunc(skeys);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
