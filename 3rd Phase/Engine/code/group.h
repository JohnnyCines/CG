#ifndef _GROUP_H_
#define _GROUP_H_

#include <vector>
#include <string>
#include <GL/glut.h>

using namespace std;
using std::vector;


class Vertice{
    private:
        float x;
        float y;
        float z;

    public:
        Vertice();
        Vertice(float xx, float yy, float zz);

        float getX();
        float getY();
        float getZ();
};


class Model {
    int nvbo;

public:
    Model();
    Model(int vbo);

    int getVBO();
};



class Operacoes{
    char* name;
    vector<Vertice*> pontos;
    float x,y,z,angle;
    int align;
    float tempo;

public:
    Operacoes();
    Operacoes(char* nameO, vector<Vertice*>, float xx, float yy, float zz, float angleO, int align, float tempo);

    char* getName();
    vector<Vertice*> getPontos();
    float getX();
    float getY();
    float getZ();
    float getAngle();
    int getAlign();
    float getTempo();
};



class Group {
    vector<Operacoes*> ops;
    vector<Model*> models;
    vector<Group*> filhos;

public:
    Group();
    Group(vector<Operacoes*> op, vector<Model*> m, vector<Group*> c);

    vector<Operacoes*> getOps();
    vector<Model*> getModel();
    vector<Group*> getFilhos();

    void pushOps(Operacoes* o);
    void pushModel(Model* m);
    void pushFilho(Group* c);
};

#endif