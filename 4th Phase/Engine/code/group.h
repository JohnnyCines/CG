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

class Luz {
    int type; //0 -> point; 1 -> directional; 2 -> spot;
    float posx;
    float posy;
    float posz;
    float dirx;
    float diry;
    float dirz;
    //float modo;
    float cutoff;

public:
    Luz();
    Luz(int t, float px, float py, float pz, float dx, float dy, float dz, float c);

    int getType();
    float getPosX();
    float getPosY();
    float getPosZ();
    float getDirX();
    float getDirY();
    float getDirZ();
    float getCutOff();
};


class Cor {
    Vertice* diffuse;
    Vertice* ambient;
    Vertice* specular;
    Vertice* emissive;
    int shininess;

public:
    Cor();
    Cor(Vertice* d, Vertice* a, Vertice* s, Vertice* e, int shine);

    Vertice* getDiffuse();
    Vertice* getAmbient();
    Vertice* getSpecular();
    Vertice* getEmissive();
    int getShininess();
};


class Model {
    int nvbo;
    Cor* cor;

public:
    Model();
    Model(int vbo, Cor* c);

    int getVBO();
    Cor* getCor();
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