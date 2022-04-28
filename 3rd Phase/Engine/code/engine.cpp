#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iostream>
#include "group.h"

#include "tinyxml/tinyxml2.h"

using namespace std;
using namespace tinyxml2;
using std::vector;

//////////////////////////////////////////////////////////////////////////// Vars Globais ////////////////////////////////////////////////////////////////////////////

GLuint buffers[4]; //bufers 0 - plano; buffers 1 -> caixa; buffers 2 -> esfera; buffers 3 -> piramide
int flag0 = 0, flag1 = 0, flag2 = 0, flag3 = 0;
int counters[4] = { 0,0,0,4 };

Group* scene = new Group();

float alfa;
float beta;
float raio;

float posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ, fov, near, far;


//////////////////////////////////////////////////////////////////////////// Leitura do XML ////////////////////////////////////////////////////////////////////////////
int readFile(const char* fname) {
	string line;
	ifstream file(fname);
	int vbo=-1;

	if (file.fail()) {
		throw std::ios_base::failure(string("Couldn't find file: ") + fname);
	}

	else {
		if (strcmp(fname, "plane.3d") == 0) {
			vbo = 0;

			if (flag0 == 0) {
				vector<float> p;

				while (getline(file, line)) {
					size_t pos;

					float x, y, z;

					x = stof(line, &pos);
					line.erase(0, pos + 1);
					y = stof(line, &pos);
					line.erase(0, pos + 1);
					z = stof(line, &pos);

					p.push_back(x);
					p.push_back(y);
					p.push_back(z);
				}

				counters[0] = p.size() / 3;
				printf("%d\n", p.size());

				
				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
				flag0 = 1;
			}
		}

		else if (strcmp(fname, "box.3d") == 0) {
			vbo = 1;
			
			if (flag1 == 0) {
				vector<float> p;

				while (getline(file, line)) {
					size_t pos;

					float x, y, z;

					x = stof(line, &pos);
					line.erase(0, pos + 1);
					y = stof(line, &pos);
					line.erase(0, pos + 1);
					z = stof(line, &pos);

					p.push_back(x);
					p.push_back(y);
					p.push_back(z);
				}
				
				counters[1] = p.size() / 3;
				printf("%d\n", p.size());
				
				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(),p.data(), GL_STATIC_DRAW);
				flag1 = 1;
			}
		}
		
		else if (strcmp(fname, "sphere.3d") == 0) {
			vbo = 2;

			if (flag2 == 0) {
				vector<float> p;

				while (getline(file, line)) {
					size_t pos;

					float x, y, z;

					x = stof(line, &pos);
					line.erase(0, pos + 1);
					y = stof(line, &pos);
					line.erase(0, pos + 1);
					z = stof(line, &pos);

					p.push_back(x);
					p.push_back(y);
					p.push_back(z);
				}

				counters[2] = p.size() / 3;
				printf("%d\n", p.size());

				glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
				flag2 = 1;
			}
		}
		else {
			vbo = 3;

			if (flag3 == 0) {
				vector<float> p;

				while (getline(file, line)) {
					size_t pos;

					float x, y, z;

					x = stof(line, &pos);
					line.erase(0, pos + 1);
					y = stof(line, &pos);
					line.erase(0, pos + 1);
					z = stof(line, &pos);

					p.push_back(x);
					p.push_back(y);
					p.push_back(z);
				}

				counters[3] = p.size() / 3;
				printf("%d\n", p.size());

				glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
				flag3 = 1;
			}
		}
		
		
	}
	printf("%d\n", vbo);
	file.close();
	return vbo;
}

Group* readGroup(XMLElement* element) {
	Group* g = new Group();

	for (element = element->FirstChildElement(); element; element = element->NextSiblingElement()) {
		if (strcmp(element->Value(), "transform") == 0) {
			XMLElement* elementChild;
			for (elementChild = element->FirstChildElement(); elementChild; elementChild = elementChild->NextSiblingElement()) {

				char* name = (char*)elementChild->Value();
				
				float x = 0, y = 0, z = 0, angle = 0;

				if (strcmp(elementChild->Value(), "translate") == 0) {
					x = atof(elementChild->Attribute("x"));
					y = atof(elementChild->Attribute("y"));
					z = atof(elementChild->Attribute("z"));
				}

				if (strcmp(elementChild->Value(), "rotate") == 0) {
					x = atof(elementChild->Attribute("x"));
					y = atof(elementChild->Attribute("y"));
					z = atof(elementChild->Attribute("z"));
					angle = atof(elementChild->Attribute("angle"));
				}

				if (strcmp(elementChild->Value(), "scale") == 0) {
					x = atof(elementChild->Attribute("x"));
					y = atof(elementChild->Attribute("y"));
					z = atof(elementChild->Attribute("z"));
				}
				
				Operacoes* o = new Operacoes(strdup(name), x, y, z, angle);

				g->pushOps(o);

			}
					
		}

		if (strcmp(element->Value(), "models") == 0) {
			XMLElement* elementChild;
			
			for (elementChild = element->FirstChildElement(); elementChild; elementChild = elementChild->NextSiblingElement()) {
				const char* ficheiro = elementChild->Attribute("file");
				Model* m = new Model(readFile(ficheiro));
				g->pushModel(m);
			}

		}

		if (strcmp(element->Value(), "group") == 0) {
			Group* child = readGroup(element);
			g->pushFilho(child);
		}
	}
	return g;
}

Group* readXML(const char * file) {
	XMLDocument doc;
	doc.LoadFile(file);
	Group* g = new Group();

	XMLElement* pRoot = doc.FirstChildElement("world");

	XMLElement* camara = pRoot->FirstChildElement("camera");
	if (camara != NULL) {
		XMLElement* position = camara->FirstChildElement("position");
		posX = atof(position->Attribute("x"));
		posY = atof(position->Attribute("y"));
		posZ = atof(position->Attribute("z"));
		XMLElement* lookAt = camara->FirstChildElement("lookAt");
		lookX = atof(lookAt->Attribute("x"));
		lookY = atof(lookAt->Attribute("y"));
		lookZ = atof(lookAt->Attribute("z"));
		XMLElement* up = camara->FirstChildElement("up");
		upX = atof(up->Attribute("x"));
		upY = atof(up->Attribute("y"));
		upZ = atof(up->Attribute("z"));
		XMLElement* projection = camara->FirstChildElement("projection");
		fov = atof(projection->Attribute("fov"));
		near = atof(projection->Attribute("near"));
		far = atof(projection->Attribute("far"));

		raio = sqrtf(powf(posX, 2) + powf(posY, 2) + powf(posZ, 2));
		beta = asin(posY / raio);
		alfa = asin(posX / (raio * cos(beta)));

	}
	glGenBuffers(4, buffers);
	XMLElement* group = pRoot->FirstChildElement("group");
	
	g = readGroup(group);

	return g;
}

//////////////////////////////////////////////////////////////////////////// Desenho ////////////////////////////////////////////////////////////////////////////

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

void renderGroup(Group* g) {
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();

	for (Operacoes* op : g->getOps()) {
		if (strcmp(op->getName(), "translate") == 0) {
			glTranslatef(op->getX(), op->getY(), op->getZ());
		}
		if (strcmp(op->getName(), "rotate") == 0) {
			glRotatef(op->getAngle(), op->getX(), op->getY(), op->getZ());
		}
		if (strcmp(op->getName(), "scale") == 0) {
			glScalef(op->getX(), op->getY(), op->getZ());
		}
	}

	for (Model* m : g->getModel()) {
		int v = m->getVBO();

		glBindBuffer(GL_ARRAY_BUFFER, buffers[v]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, counters[v]);
	}

	for (Group* child : g->getFilhos()) {
		renderGroup(child);
	}

	glPopMatrix();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	
	/*
	gluLookAt(raio * cos(beta) * sin(alpha), raio * sin(beta), raio * cos(beta) * cos(alpha),
				0.0, 0.0, 0.0,
				0.0f, 1.0f, 0.0f);
	*/
	
	camera(posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ);
	//camera(raio*cos(beta)*sin(alfa), raio*sin(beta), raio * cos(beta) * cos(alfa), lookX, lookY, lookZ, upX, upY, upZ);
	drawAxis();

	renderGroup(scene);

	//glEnd();
	
	glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////// Processamento Teclado ////////////////////////////////////////////////////////////////////////////

void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {
	case 'w':
		beta += 0.25f;
		if (beta > 1.5f) {
			beta = 1.5f;
		}
		//printf("%f %f %f\n", raio * cos(beta) * sin(alfa), raio * sin(beta), raio * cos(beta) * cos(alfa));
		glutPostRedisplay();
		break;

	case 'a':
		alfa -= 0.2f;
		//printf("%f %f %f\n", raio * cos(beta) * sin(alfa), raio * sin(beta), raio * cos(beta) * cos(alfa));
		glutPostRedisplay();
		break;

	case 's':
		beta -= 0.25f;
		if (beta < -1.5f) {
			beta = -1.5f;
		}
		//printf("%f %f %f\n", raio * cos(beta) * sin(alfa), raio * sin(beta), raio * cos(beta) * cos(alfa));
		glutPostRedisplay();
		break;

	case 'd':
		alfa += 0.2f;
		//printf("%f %f %f\n", raio * cos(beta) * sin(alfa), raio * sin(beta), raio * cos(beta) * cos(alfa));
		glutPostRedisplay();
		break;

	}
}

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(fov, ratio, near, far);
	glMatrixMode(GL_MODELVIEW);
}

//////////////////////////////////////////////////////////////////////////// Main ////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(80,80);
	glutInitWindowSize(800,800);
	glutCreateWindow("Engine - Phase 2");
	

	
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processKeys);

#ifndef __APPLE__
	glewInit();
#endif

	if (argc != 2) {
		printf("Invalid input");
		return 0;
	}
	else {
		scene = readXML(argv[1]);
	}

//  OpenGL settings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}