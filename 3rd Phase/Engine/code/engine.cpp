#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
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

GLuint buffers[5]; //bufers 0 - plano; buffers 1 -> caixa; buffers 2 -> esfera; buffers 3 -> piramide; buffers 4 -> bule
int flag0 = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
int counters[5] = { 0,0,0,0,0 };

Group* scene = new Group();

float alfa;
float beta;
float raio;

float posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ, fov, near, far;


//////////////////////////////////////////////////////////////////////////// Leitura do XML ////////////////////////////////////////////////////////////////////////////
int readFile(const char* fname) {
	
	ifstream file(fname);
	int vbo=-1;

	if (file.fail()) {
		throw std::ios_base::failure(string("Couldn't find file: ") + fname);
	}

	else {
		string line;
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
		else if (strcmp(fname, "box.3d") == 0) {
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
		else {
			vbo = 4;

			if (flag4 == 0) {
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

				counters[4] = p.size() / 3;
				printf("%d\n", p.size());

				glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
				flag4 = 1;
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
				vector<Vertice*> p;
				float x = 0, y = 0, z = 0, angle = 0, tempo = 0;
				int align = 0;

				if (strcmp(elementChild->Value(), "translate") == 0) {

					XMLElement* childTranslate = elementChild->FirstChildElement();

					if (childTranslate == NULL) {
						x = atof(elementChild->Attribute("x"));
						y = atof(elementChild->Attribute("y"));
						z = atof(elementChild->Attribute("z"));
						printf("%f %f %f\n", x, y, z);
						Operacoes* o = new Operacoes(strdup(name), p, x, y, z, angle, align,tempo);
						g->pushOps(o);

					}
					else {
						tempo = stof(elementChild->Attribute("time"));
						char* a = (char*)elementChild->Attribute("align");

						if (strcmp(a, "True") == 0) {
							align = 1;
						}

						for (childTranslate = elementChild->FirstChildElement(); childTranslate; childTranslate = childTranslate->NextSiblingElement()) {
							x = atof(childTranslate->Attribute("x"));
							y = atof(childTranslate->Attribute("y"));
							z = atof(childTranslate->Attribute("z"));
							Vertice* v = new Vertice(x, y, z);
							p.push_back(v);
						}
						Operacoes* o = new Operacoes(strdup("catmull"), p, x, y, z, angle, align, tempo);
						g->pushOps(o);
					}
				}

				if (strcmp(elementChild->Value(), "rotate") == 0) {
					x = atof(elementChild->Attribute("x"));
					y = atof(elementChild->Attribute("y"));
					z = atof(elementChild->Attribute("z"));
					if (elementChild->Attribute("angle") != NULL) {
						angle = stof(elementChild->Attribute("angle"));
						tempo = -1;
					}
					else {
						tempo = stof(elementChild->Attribute("time"));
						angle = -1;
					}
					
					Operacoes* o = new Operacoes(strdup(name), p, x, y, z, angle, align, tempo);
					g->pushOps(o);
				}

				if (strcmp(elementChild->Value(), "scale") == 0) {
					x = atof(elementChild->Attribute("x"));
					y = atof(elementChild->Attribute("y"));
					z = atof(elementChild->Attribute("z"));
					
					Operacoes* o = new Operacoes(strdup(name), p, x, y, z, angle, align, tempo);
					g->pushOps(o);
				}
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
	glGenBuffers(5, buffers);
	XMLElement* group = pRoot->FirstChildElement("group");
	
	g = readGroup(group);

	return g;
}

//////////////////////////////////////////////////////////////////////////// Curvas e funções aux ////////////////////////////////////////////////////////////////////////////
void buildRotMatrix(float* x, float* y, float* z, float* m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


float length(float* v) {

	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return res;

}

void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	

	for (int i = 0; i < 3; i++) {
		float p[4] = { p0[i], p1[i], p2[i], p3[i] };
		float a[4];

		// Compute A = M * P
		multMatrixVector(*m, p, a);

		// Compute pos = T * A
		pos[i] = pow(t, 3) * a[0] + pow(t, 2) * a[1] + t * a[2] + a[3];

		// compute deriv = T' * A
		deriv[i] = 3 * pow(t, 2) * a[0] + 2 * t * a[1] + a[2];
	}
}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, float **p, int pcount) {

	float count = gt * pcount;

	float t = gt * count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + pcount - 1) % pcount;
	indices[1] = (indices[0] + 1) % pcount;
	indices[2] = (indices[1] + 1) % pcount;
	indices[3] = (indices[2] + 1) % pcount;

	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
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

void renderCatmullRomCurve(float **p, int pcount) {
	float pos[3];
	float deriv[3];

	float gt = 0;

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 100; i++) {
		getGlobalCatmullRomPoint(gt, pos, deriv, p, pcount);
		glVertex3f(pos[0], pos[1], pos[2]);

		gt += 0.01;
	}

	glEnd();

}

void renderGroup(Group* g) {
	
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();

	for (Operacoes* op : g->getOps()) {
		if (strcmp(op->getName(), "catmull") == 0) {
			static float t = 0;
			
			vector<Vertice*> v = op->getPontos();
			int pcount = v.size();
			
			float** p = (float**)malloc(pcount * sizeof(float*));
			for (int i = 0; i < pcount; ++i) p[i] = (float*)malloc(3 * sizeof(float));
			
			for (int i = 0; i < pcount; i++) {
				p[i][0] = v[i]->getX();
				p[i][1] = v[i]->getY();
				p[i][2] = v[i]->getZ();
				
			}

			renderCatmullRomCurve(p, pcount);

			float* objpos = (float*)malloc(sizeof(float) * 4);
			float* objderiv = (float*)malloc(sizeof(float) * 4);

			float tempo = op->getTempo();

			if (tempo > 0) {
				float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(tempo * 1000);
				float rt = elapsed / (tempo * 1000);

				getGlobalCatmullRomPoint(rt, objpos, objderiv, p, pcount);
				
				glTranslatef(objpos[0], objpos[1], objpos[2]);
			}

			if (op->getAlign() == 1) {
				float x[3] = { objderiv[0], objderiv[1], objderiv[2] };
				normalize(x);

				float y_0[3] = { 0, 1, 0 };

				float z[3];
				cross(x, y_0, z);
				normalize(z);

				float y[3];
				cross(z, x, y);
				normalize(y);

				float m[16];

				buildRotMatrix(x, y, z, m);

				glMultMatrixf(m);

			}
			t += 0.001;
		}

		else if (strcmp(op->getName(), "translate") == 0) {
			glTranslatef(op->getX(), op->getY(), op->getZ());
		}
		else if (strcmp(op->getName(), "rotate") == 0) {
			if (op->getAngle() != -1) {
				glRotatef(op->getAngle(), op->getX(), op->getY(), op->getZ());
			}
			else {
				float currAngle = 0;

				float tempo = op->getTempo();
				if (tempo > 0) {
					float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int)(tempo * 1000);
					currAngle = (elapsed * 360) / (tempo * 1000);
				}

				glRotatef(currAngle, op->getX(), op->getY(), op->getZ());
			}
		}
			
		else if (strcmp(op->getName(), "scale") == 0) {
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
	//t += 0.001;
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
	//camera(posX, posY, posZ, lookX, lookY, lookZ, upX, upY, upZ);
	camera(raio*cos(beta)*sin(alfa), raio*sin(beta), raio * cos(beta) * cos(alfa), lookX, lookY, lookZ, upX, upY, upZ);
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
	glutIdleFunc(renderScene);
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