//#include <stdlib.h>
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

/*
#include "tinyxml/tinyxml2.h"
#include "tinyxml/tinyxml2.cpp"
*/

using namespace std;
//using namespace tinyxml2;
using std::vector;

//struct para guardar os vertices de triangulos
struct Coords
{
	float xx;
	float yy;
	float zz;
};


vector<Coords> triangles;

float alpha = 0.25;
float beta = 0.5;
float raio = 7.5;

//float posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ;

//no need to change
void processKeys(unsigned char c, int xx, int yy) {

	// put code to process regular keys in here
	switch (c) {
	case 'w':
		if (beta < 1.5f) {
			beta += 0.25f;
		}
		glutPostRedisplay();
		break;

	case 'a':
		alpha -= 0.2f;
		glutPostRedisplay();
		break;

	case 's':
		if (beta > -1.5f) {
			beta -= 0.25f;
		}
		glutPostRedisplay();
		break;

	case 'd':
		alpha += 0.2f;
		glutPostRedisplay();
		break;

	}

}


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


void camera(float pX, float pY, float pZ, float lX, float lY, float lZ, float uX, float uY, float uZ) {
	gluLookAt(pX, pY, pZ,
				lX, lY, lZ,
				uX, uY, uZ);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	
	gluLookAt(raio * cos(beta) * sin(alpha), raio * sin(beta), raio * cos(beta) * cos(alpha),
				0.0, 0.0, 0.0,
				0.0f, 1.0f, 0.0f);
	
	//camera(posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ);
	//drawAxis();

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

//funçao que vai ler os ficheiros .3d e desenhar as figuras
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

			struct Coords Aux {};
			Aux.xx = x;
			Aux.yy = y;
			Aux.zz = z;

			triangles.push_back(Aux);
		}
	}
	file.close();
}

//funçao que vai ler o ficheiro XML e extrair informação sobre a camara, assim como
//quais os ficheiros 3d a ler

/*
int readXML(char* f) {
	XMLDocument doc;

	XMLError eResult = doc.LoadFile(f);

	XMLNode* root = doc.FirstChild();

	if (strcmp("world", root->Value()) != 0) {
		printf("Esperado valor 'world', obtido %s\n", root->Value());
		return 1;
	}

	if (root==nullptr) {
		printf("Não há dados\n");
		return 1;
	}

	XMLNode* camera = root->FirstChildElement("camera");

	if (strcmp("camera", camera->Value()) != 0) {
		printf("Esperado valor 'camera', obtido %s\n", camera->Value());
		return 1;
	}

	if (camera == nullptr) {
		printf("Não há dados\n");
		return 1;
	}

	XMLNode* setting = camera->FirstChildElement();

	while (setting != nullptr) {

		XMLElement *element = setting->ToElement();

		if (strcmp("positon", setting->Value()) == 0){
			posX = atof(element->Attribute("x"));
			posY = atof(element->Attribute("y"));
			posZ = atof(element->Attribute("z"));
		}

		if (strcmp("lookAt", setting->Value()) == 0) {
			lookX = atof(element->Attribute("x"));
			lookY = atof(element->Attribute("y"));
			lookZ = atof(element->Attribute("z"));
		}

		if (strcmp("up", setting->Value()) == 0) {
			upX = atof(element->Attribute("x"));
			upY = atof(element->Attribute("y"));
			upZ = atof(element->Attribute("z"));
		}

		setting = setting->NextSiblingElement();
	}

	XMLNode* group = root->FirstChildElement("group");

	if (strcmp("group", group->Value()) != 0) {
		printf("Esperado valor 'group', obtido %s\n", group->Value());
		return 1;
	}

	if (group == nullptr) {
		printf("Não há dados\n");
		return 1;
	}

	XMLNode* models = group->FirstChildElement("models");

	if (strcmp("models", models->Value()) != 0) {
		printf("Esperado valor 'models', obtido %s\n", models->Value());
		return 1;
	}

	if (models == nullptr) {
		printf("Não há dados\n");
		return 1;
	}

	tinyxml2::XMLNode* model = models->FirstChildElement("model");

	while (model != nullptr) {
		tinyxml2::XMLElement* element = model->ToElement();

		if (strcmp("model", model->Value()) != 0) {
			printf("Esperado valor 'model', obtido %s\n", model->Value());
			return 1;
		}

		string ficheiro = element->Attribute("file");
		readFile(ficheiro);

		model = model->NextSiblingElement();
	}
	return 0;
}*/
int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(80,80);
	glutInitWindowSize(1500,1000);
	glutCreateWindow("Engine - Phase 1");
	
	/*
	if (argc != 3) {
		printf("Invalid input");
		return 0;
	}
	else {
		readFile(argv[1]);
		//readFile(argv[2]);
	}
	*/
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(processKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
