#include "group.h"

using namespace std;
using std::vector;


Vertice::Vertice() {
    x = 0;
    y = 0;
    z = 0;
};

Vertice::Vertice(float xx, float yy, float zz) {
    x = xx;
    y = yy;
    z = zz;
};

float Vertice::getX() {
    return x;
};

float Vertice::getY() {
    return y;      
};

float Vertice::getZ() {
    return z;
};


///////////////////////////////// Luzes /////////////////////////////////////////

Luz::Luz() {
    type = -1;
    posx = 0.0;
    posy = 0.0;
    posz = 0.0;
    dirx = 0.0;
    diry = 0.0;
    dirz = 0.0;
    cutoff = 0.0;
};

Luz::Luz(int t, float px, float py, float pz, float dx, float dy, float dz, float c) {
    type = t;
    posx = px;
    posy = py;
    posz = pz;
    dirx = dx;
    diry = dy;
    dirz = dz;
    cutoff = c;
};

int Luz::getType() {
    return type;
};

float Luz::getPosX() {
    return posx;
};

float Luz::getPosY() {
    return posy;
};

float Luz::getPosZ() {
    return posz;
};

float Luz::getDirX() {
    return dirx;
};

float Luz::getDirY() {
    return diry;
};

float Luz::getDirZ() {
    return dirz;
};

float Luz::getCutOff() {
    return cutoff;
};

///////////////////////////////// Cor /////////////////////////////////////////
Cor::Cor() {

};

Cor::Cor(Vertice* d, Vertice* a, Vertice* s, Vertice* e, int shine) {
    diffuse = d;
    ambient = a;
    specular = s;
    emissive = e;
    shininess = shine;
};

Vertice* Cor::getDiffuse() {
    return diffuse;
};

Vertice* Cor::getAmbient() {
    return ambient;
};

Vertice* Cor::getSpecular() {
    return specular;
};

Vertice* Cor::getEmissive() {
    return emissive;
};

int Cor::getShininess() {
    return shininess;
};


//////////////////////////////// Model ////////////////////////////////////////

Model::Model() {
    nvbo = -1;
};

Model::Model(int vbo, Cor* c) {
    nvbo = vbo;
    cor = c;
};

int Model::getVBO() {
    return nvbo;
};

Cor* Model::getCor() {
    return cor;
}

//////////////////////////////////// Operações ////////////////////////////////////

Operacoes::Operacoes() {
    name = "";
    x = 0;
    y = 0;
    z = 0;
    angle = 0;
    align = 0;
    tempo = 0;
};

Operacoes::Operacoes(char* nameO, vector<Vertice*> p, float xx, float yy, float zz, float angleO, int a, float tp) {
    name = nameO;
    pontos = p;
    x = xx;
    y = yy;
    z = zz;
    angle = angleO;
    align = a;
    tempo = tp;
};

char* Operacoes::getName() {
    return name;
};

vector<Vertice*> Operacoes::getPontos() {
    return pontos;
};

float Operacoes::getX() {
    return x;
};

float Operacoes::getY() {
    return y;
};

float Operacoes::getZ() {
    return z;
};

float Operacoes::getAngle() {
    return angle;
};

int Operacoes::getAlign() {
    return align;
};

float Operacoes::getTempo() {
    return tempo;
};

////////////////////////////////////// Group //////////////////////////////////

Group::Group() {

};

Group::Group(vector<Operacoes*> op, vector<Model*> m, vector<Group*> c) {
    ops = op;
    models = m;
    filhos = c;
};

vector<Operacoes*> Group::getOps() {
    return ops;
};

vector<Model*> Group::getModel() {
    return models;
};

vector<Group*> Group::getFilhos() {
    return filhos;
};

void Group::pushOps(Operacoes* o) {
    ops.push_back(o);
};

void Group::pushModel(Model* m) {
    models.push_back(m);
};

void Group::pushFilho(Group* c) {
    filhos.push_back(c);
};