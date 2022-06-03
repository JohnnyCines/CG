#include <stdio.h> 
#include <stdlib.h>        //FILE*, fopen, fprintf
#define _USE_MATH_DEFINES
#include <cmath>          //M_PI
#include "primitivas.h"   //plano, caixa
#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <math.h>

using namespace std;

struct Coords
{
    float xx;
    float yy;
    float zz;
};

struct Pontos
{
    int p1;  
    int p2;
    int p3;
    int p4;
    int p5;
    int p6;
    int p7;
    int p8;
    int p9;
    int p10;
    int p11;
    int p12;
    int p13;
    int p14;
    int p15;
    int p16;
};


vector<Coords> triangles;  
vector<Pontos> sup;

float m[4][4] = { {-1.0f,  3.0f, -3.0f,  1.0f},
                  { 3.0f, -6.0f,  3.0f, 0.0f},
                  {-3.0,  3.0f,  0.0f,  0.0f},
                  { 1.0f, 0.0f,  0.0f,  0.0f}};

void plano(float length, float divisions, char* fname) {
    FILE* f;
    fopen_s(&f, fname, "w");

    //ponto de partida dos eixos x e z
    float x = -length / 2;
    float z = length / 2;

    //comprimento do lado de cada quadrado pequeno
    float lq = length / divisions;

    while (z != -length / 2) {
        while (x != length / 2) {

            //guardar tri�ngulos
            fprintf(f, "%f %f %f %f %f %f\n", x, 0.0, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, 0.0, z - lq, 0.0, 1.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z - lq, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x , 0.0, z - lq, 0.0, 1.0, 0.0);

            //tri�ngulos inversos
            fprintf(f, "%f %f %f %f %f %f\n", x, 0.0, z, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, 0.0, z - lq, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z, 0.0, -1.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, 0.0, z - lq, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, 0.0, z-lq, 0.0, -1.0, 0.0);



            x += lq; //incrementar x para o pr�ximo ponto
        }
        x = -length / 2; //reinicializar eixo dos x
        z -= lq; //decrementar z para o pr�ximo ponto
    }

    fclose(f);
}


void caixa(float length, float divisions, char* fname) {
    FILE* f;
    fopen_s(&f, fname, "w");

    //diferen�a entre cada ponto
    float lq = length / divisions;
    
    //ponto de partida nos extremos de y
    float x = -length / 2.0f;
    float z = length / 2.0f;
    float y = length / 2.0f;
    
    //c�lculo dos tri�ngulos nas duas faces nos extremos de y
    while (z > -length / 2) {
        while (x < length / 2) {
        //guardar tri�ngulos
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z - lq, 0.0, 1.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y, z, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y, z - lq, 0.0, 1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z - lq, 0.0, 1.0, 0.0);

            //tri�ngulos da face sim�trica
            fprintf(f, "%f %f %f %f %f %f\n", x, -y, z, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, -y, z - lq, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, -y, z, 0.0, -1.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", x + lq, -y, z, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, -y, z - lq, 0.0, -1.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, -y, z - lq, 0.0, -1.0, 0.0);

            x += lq; //incrementar x para o pr�ximo ponto
        }
        x = -length / 2; //reinicializar eixo dos x
        z -= lq; //decrementar z para o pr�ximo ponto
    }

    
    //ponto de partida nos extremos de z
    x = -length / 2;
    z = length / 2;
    y = length / 2;

    //c�lculo dos tri�ngulos nas duas faces nos extremos de z
    while (y > -length / 2) {
        while (x < length / 2) {
            //guardar tri�ngulos
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z, 0.0, 0.0, 1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y - lq, z, 0.0, 0.0, 1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y - lq, z, 0.0, 0.0, 1.0);

            fprintf(f, "%f %f %f %f %f %f\n", x, y, z, 0.0, 0.0, 1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y - lq, z, 0.0, 0.0, 1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y, z, 0.0, 0.0, 1.0);

            //tri�ngulos da face oposta
            fprintf(f, "%f %f %f %f %f %f\n", x, y, -z, 0.0, 0.0, -1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y - lq, -z, 0.0, 0.0, -1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y - lq, -z, 0.0, 0.0, -1.0);

            fprintf(f, "%f %f %f %f %f %f\n", x, y, -z, 0.0, 0.0, -1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y, -z, 0.0, 0.0, -1.0);
            fprintf(f, "%f %f %f %f %f %f\n", x + lq, y - lq, -z, 0.0, 0.0, -1.0);

            x += lq; //incrementar x para o pr�ximo ponto
        }
        x = -length / 2; //reinicializar eixo dos x
        y -= lq; //incrementar y para o pr�ximo ponto
    }
   
    //ponto de partida nos extremos de x
    x = length / 2;
    z = length / 2;
    y = length / 2;

    //c�lculo dos tri�ngulos nas duas faces nos extremos de x

    while (y > -length / 2.0f) {
        while (z > -length / 2.0f) {
            //guardar tri�ngulos
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z, 1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y-lq, z, 1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y - lq, z - lq, 1.0, 0.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", x, y, z, 1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y - lq, z - lq, 1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", x, y, z-lq, 1.0, 0.0, 0.0);

            //tri�ngulos da face sim�trica
            fprintf(f, "%f %f %f %f %f %f\n", -x, y, z, -1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", -x, y - lq, z - lq, -1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", -x, y-lq, z, -1.0, 0.0, 0.0);

            fprintf(f, "%f %f %f %f %f %f\n", -x, y, z, -1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", -x, y, z-lq, -1.0, 0.0, 0.0);
            fprintf(f, "%f %f %f %f %f %f\n", -x, y - lq, z - lq, -1.0, 0.0, 0.0);

            z -= lq; //decrementar z para o pr�ximo ponto
        }
        z = length / 2; //reinicializar eixo do z
        y -= lq; //decrementar y para o pr�ximo ponto
    }
    
    fclose(f);
}

void esfera(float r, int slices, int stacks, char* fname) {
    FILE* f;
    fopen_s(&f, fname, "w");

    float a, b;
    float sl = 2.0f * M_PI / float(slices), st = M_PI / float(stacks);
    float px1, px2, px3, px4, py1, py2, pz1, pz2, pz3, pz4;

    //alfa (angulo formado por xx e zz) vai de 0 a 2*pi
    for (a = 0.0f; a <= 2 * M_PI; a += sl) {

        //beta (angulo formado por plano xz e yy) vai de -pi/2 a pi/2
        for (b = -M_PI / 2.0f; b < M_PI / 2.0f; b += st) {

            //triangulos que nao se veem
            px1 = r * cos(b) * sin(a);
            px2 = r * cos(b) * sin(a + sl);
            px3 = r * cos(b + st) * sin(a);
            px4 = r * cos(b + st) * sin(a + sl);     

            py1 = r * sin(b);
            py2 = r * sin(b + st);

            pz1 = r * cos(b) * cos(a);
            pz2 = r * cos(b) * cos(a + sl);
            pz3 = r * cos(b + st) * cos(a);
            pz4 = r * cos(b + st) * cos(a + sl);

            fprintf(f, "%f %f %f %f %f %f\n", px1, py1, pz1, cos(b) * sin(a), sin(b), cos(b) * cos(a));
            fprintf(f, "%f %f %f %f %f %f\n", px2, py1, pz2, cos(b) * sin(a+sl), sin(b), cos(b) * cos(a+sl));
            fprintf(f, "%f %f %f %f %f %f\n", px3, py2, pz3, cos(b+st) * sin(a), sin(b+st), cos(b+st) * cos(a));

            fprintf(f, "%f %f %f %f %f %f\n", px2, py1, pz2, cos(b) * sin(a + sl), sin(b), cos(b) * cos(a + sl));
            fprintf(f, "%f %f %f %f %f %f\n", px4, py2, pz4, cos(b + st) * sin(a + sl), sin(b + st), cos(b + st) * cos(a + sl));
            fprintf(f, "%f %f %f %f %f %f\n", px3, py2, pz3, cos(b + st) * sin(a), sin(b + st), cos(b + st) * cos(a));
        }
    }
    fclose(f);
}


void cone(float radius, float height, int slices, int stacks, char* fname) {
    FILE* f;
    fopen_s(&f, fname, "w");

    float sl = 2 * M_PI / float(slices);
    float st = radius / float(stacks);
    float alt = height / float(stacks);
    float coneAngle = atan(radius / height);

    float a, b;

    for (a = 0; a <= 2 * M_PI; a += sl) {
        //face de baixo
        float xb1 = radius * sin(a + sl);
        float zb1 = radius * cos(a + sl);

        float xb2 = radius * sin(a);
        float zb2 = radius * cos(a);

        fprintf(f, "%f %f %f %f %f %f\n", 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
        fprintf(f, "%f %f %f %f %f %f\n", xb1, 0.0, zb1, 0.0, -1.0, 0.0);
        fprintf(f, "%f %f %f %f %f %f\n", xb2, 0.0, zb2, 0.0, -1.0, 0.0);


        float aux = 0.0f;
        for (b = float(radius); b > st; b -= st) {

            float x1 = b * sin(a);
            float x2 = b * sin(a + sl);
            float x3 = (b - st) * sin(a);
            float x4 = (b - st) * sin(a + sl);

            float z1 = b * cos(a);
            float z2 = b * cos(a + sl);
            float z3 = (b - st) * cos(a);
            float z4 = (b - st) * cos(a + sl);

            fprintf(f, "%f %f %f %f %f %f\n", x1, aux, z1, cos(coneAngle) * sin(a), sin(coneAngle), cos(coneAngle) * cos(a));
            fprintf(f, "%f %f %f %f %f %f\n", x2, aux, z2, cos(coneAngle) * sin(a + sl), sin(coneAngle), cos(coneAngle) * cos(a + sl));
            fprintf(f, "%f %f %f %f %f %f\n", x3, aux + alt, z3, cos(coneAngle) * sin(a), sin(coneAngle), cos(coneAngle) * cos(a));

            fprintf(f, "%f %f %f %f %f %f\n", x2, aux, z2, cos(coneAngle) * sin(a + sl), sin(coneAngle), cos(coneAngle) * cos(a + sl));
            fprintf(f, "%f %f %f %f %f %f\n", x4, aux + alt, z4, cos(coneAngle) * sin(a + sl), sin(coneAngle), cos(coneAngle) * cos(a + sl));
            fprintf(f, "%f %f %f %f %f %f\n", x3, aux + alt, z3, cos(coneAngle) * sin(a), sin(coneAngle), cos(coneAngle) * cos(a));

            aux += alt;
        }

        fprintf(f, "%f %f %f %f %f %f\n", 0.0, height, 0.0, cos(coneAngle) * sin(a), sin(coneAngle), cos(coneAngle) * cos(a));
        fprintf(f, "%f %f %f %f %f %f\n", st * sin(a), aux, st * cos(a), cos(coneAngle) * sin(a), sin(coneAngle), cos(coneAngle) * cos(a));
        fprintf(f, "%f %f %f %f %f %f\n", st * sin(a + sl), aux, st * cos(a + sl), cos(coneAngle) * sin(a + sl), sin(coneAngle), cos(coneAngle) * cos(a + sl));

    }
    fclose(f);
}



void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

    if (a[0] == 0 && a[1] == 0 && a[2] == 0) {
        a[0] = 1;
        a[1] = 1;
        a[2] = 1;
    }
    else {
        float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        a[0] = a[0] / l;
        a[1] = a[1] / l;
        a[2] = a[2] / l;
    }
}

void getderiU(float u, float v, int i, float* deru) {
    float vv[4] = { powf(v,3), powf(v,2), v, 1.0 };
    
    float matrizX[4][4] = { { triangles[sup[i].p1].xx, triangles[sup[i].p5].xx, triangles[sup[i].p9].xx, triangles[sup[i].p13].xx},
                            { triangles[sup[i].p2].xx, triangles[sup[i].p6].xx, triangles[sup[i].p10].xx, triangles[sup[i].p14].xx },
                            { triangles[sup[i].p3].xx, triangles[sup[i].p7].xx, triangles[sup[i].p11].xx, triangles[sup[i].p15].xx},
                            { triangles[sup[i].p4].xx, triangles[sup[i].p8].xx, triangles[sup[i].p12].xx, triangles[sup[i].p16].xx} };


    float matrizY[4][4] = { { triangles[sup[i].p1].yy, triangles[sup[i].p5].yy, triangles[sup[i].p9].yy, triangles[sup[i].p13].yy},
                            { triangles[sup[i].p2].yy, triangles[sup[i].p6].yy, triangles[sup[i].p10].yy, triangles[sup[i].p14].yy },
                            { triangles[sup[i].p3].yy, triangles[sup[i].p7].yy, triangles[sup[i].p11].yy, triangles[sup[i].p15].yy},
                            { triangles[sup[i].p4].yy, triangles[sup[i].p8].yy, triangles[sup[i].p12].yy, triangles[sup[i].p16].yy} };

    float matrizZ[4][4] = { { triangles[sup[i].p1].zz, triangles[sup[i].p5].zz, triangles[sup[i].p9].zz, triangles[sup[i].p13].zz},
                            { triangles[sup[i].p2].zz, triangles[sup[i].p6].zz, triangles[sup[i].p10].zz, triangles[sup[i].p14].zz },
                            { triangles[sup[i].p3].zz, triangles[sup[i].p7].zz, triangles[sup[i].p11].zz, triangles[sup[i].p15].zz},
                            { triangles[sup[i].p4].zz, triangles[sup[i].p8].zz, triangles[sup[i].p12].zz, triangles[sup[i].p16].zz} };

    float a[4];
    float ax[4], ay[4], az[4];
    float ax2[4], ay2[4], az2[4];

    multMatrixVector(*m, vv, a);

    multMatrixVector(*matrizX, a, ax);
    multMatrixVector(*matrizY, a, ay);
    multMatrixVector(*matrizZ, a, az);

    multMatrixVector(*m, ax, ax2);
    multMatrixVector(*m, ay, ay2);
    multMatrixVector(*m, az, az2);

    deru[0] = 3 * powf(u, 2) * ax2[0] + 2 * u * ax2[1] + ax2[2];
    deru[1] = 3 * powf(u, 2) * ay2[0] + 2 * u * ay2[1] + ay2[2];
    deru[2] = 3 * powf(u, 2) * az2[0] + 2 * u * az2[1] + az2[2];
}

void getderiV(float u, float v, int i, float* derv) {
    float vvd[4] = { 3*powf(v,3), 2*v, 1.0, 0.0 };

    float matrizX[4][4] = { { triangles[sup[i].p1].xx, triangles[sup[i].p5].xx, triangles[sup[i].p9].xx, triangles[sup[i].p13].xx},
                            { triangles[sup[i].p2].xx, triangles[sup[i].p6].xx, triangles[sup[i].p10].xx, triangles[sup[i].p14].xx },
                            { triangles[sup[i].p3].xx, triangles[sup[i].p7].xx, triangles[sup[i].p11].xx, triangles[sup[i].p15].xx},
                            { triangles[sup[i].p4].xx, triangles[sup[i].p8].xx, triangles[sup[i].p12].xx, triangles[sup[i].p16].xx} };


    float matrizY[4][4] = { { triangles[sup[i].p1].yy, triangles[sup[i].p5].yy, triangles[sup[i].p9].yy, triangles[sup[i].p13].yy},
                            { triangles[sup[i].p2].yy, triangles[sup[i].p6].yy, triangles[sup[i].p10].yy, triangles[sup[i].p14].yy },
                            { triangles[sup[i].p3].yy, triangles[sup[i].p7].yy, triangles[sup[i].p11].yy, triangles[sup[i].p15].yy},
                            { triangles[sup[i].p4].yy, triangles[sup[i].p8].yy, triangles[sup[i].p12].yy, triangles[sup[i].p16].yy} };

    float matrizZ[4][4] = { { triangles[sup[i].p1].zz, triangles[sup[i].p5].zz, triangles[sup[i].p9].zz, triangles[sup[i].p13].zz},
                            { triangles[sup[i].p2].zz, triangles[sup[i].p6].zz, triangles[sup[i].p10].zz, triangles[sup[i].p14].zz },
                            { triangles[sup[i].p3].zz, triangles[sup[i].p7].zz, triangles[sup[i].p11].zz, triangles[sup[i].p15].zz},
                            { triangles[sup[i].p4].zz, triangles[sup[i].p8].zz, triangles[sup[i].p12].zz, triangles[sup[i].p16].zz} };

    float a[4];
    float ax[4], ay[4], az[4];
    float ax2[4], ay2[4], az2[4];

    multMatrixVector(*m, vvd, a);

    multMatrixVector(*matrizX, a, ax);
    multMatrixVector(*matrizY, a, ay);
    multMatrixVector(*matrizZ, a, az);

    multMatrixVector(*m, ax, ax2);
    multMatrixVector(*m, ay, ay2);
    multMatrixVector(*m, az, az2);

    derv[0] = powf(u, 3) * ax2[0] + powf(u, 2) * ax2[1] + u * ax2[2] + ax2[3];
    derv[1] = powf(u, 3) * ay2[0] + powf(u, 2) * ay2[1] + u * ay2[2] + ay2[3];
    derv[2] = powf(u, 3) * az2[0] + powf(u, 2) * az2[1] + u * az2[2] + az2[3];
}

void getpos(float u, float v, int i, float* pos) { 
    float vv[4] = {powf(v,3), powf(v,2), v, 1.0};
 
    float matrizX[4][4] = { { triangles[sup[i].p1].xx, triangles[sup[i].p5].xx, triangles[sup[i].p9].xx, triangles[sup[i].p13].xx},
                            { triangles[sup[i].p2].xx, triangles[sup[i].p6].xx, triangles[sup[i].p10].xx, triangles[sup[i].p14].xx },
                            { triangles[sup[i].p3].xx, triangles[sup[i].p7].xx, triangles[sup[i].p11].xx, triangles[sup[i].p15].xx},
                            { triangles[sup[i].p4].xx, triangles[sup[i].p8].xx, triangles[sup[i].p12].xx, triangles[sup[i].p16].xx} };

    
    float matrizY[4][4] = { { triangles[sup[i].p1].yy, triangles[sup[i].p5].yy, triangles[sup[i].p9].yy, triangles[sup[i].p13].yy},
                            { triangles[sup[i].p2].yy, triangles[sup[i].p6].yy, triangles[sup[i].p10].yy, triangles[sup[i].p14].yy },
                            { triangles[sup[i].p3].yy, triangles[sup[i].p7].yy, triangles[sup[i].p11].yy, triangles[sup[i].p15].yy},
                            { triangles[sup[i].p4].yy, triangles[sup[i].p8].yy, triangles[sup[i].p12].yy, triangles[sup[i].p16].yy} };
   
    float matrizZ[4][4] = { { triangles[sup[i].p1].zz, triangles[sup[i].p5].zz, triangles[sup[i].p9].zz, triangles[sup[i].p13].zz},
                            { triangles[sup[i].p2].zz, triangles[sup[i].p6].zz, triangles[sup[i].p10].zz, triangles[sup[i].p14].zz },
                            { triangles[sup[i].p3].zz, triangles[sup[i].p7].zz, triangles[sup[i].p11].zz, triangles[sup[i].p15].zz},
                            { triangles[sup[i].p4].zz, triangles[sup[i].p8].zz, triangles[sup[i].p12].zz, triangles[sup[i].p16].zz} };
   
    float a[4];
    float ax[4], ay[4], az[4];
    float ax2[4], ay2[4], az2[4];

    multMatrixVector(*m, vv, a);
    
    multMatrixVector(*matrizX, a, ax);
    multMatrixVector(*matrizY, a, ay);
    multMatrixVector(*matrizZ, a, az);

    multMatrixVector(*m, ax, ax2);
    multMatrixVector(*m, ay, ay2);
    multMatrixVector(*m, az, az2);

    pos[0] = powf(u, 3) * ax2[0] + powf(u, 2) * ax2[1] + u * ax2[2] + ax2[3];
    pos[1] = powf(u, 3) * ay2[0] + powf(u, 2) * ay2[1] + u * ay2[2] + ay2[3];
    pos[2] = powf(u, 3) * az2[0] + powf(u, 2) * az2[1] + u * az2[2] + az2[3];
}

void bezier(const char* forigin, float tess, char* file) {
    FILE* fout;
    fopen_s(&fout, file, "w");
    string line;
    ifstream f;
        
    f.open(forigin);
    int n;

    getline(f, line);
    size_t pos;

    n = stoi(line, &pos);

    for (int i = 0; i < n; i++) {
        struct Pontos Aux {};
        getline(f, line);
        
        size_t pos;
        
        Aux.p1 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p2 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p3 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p4 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p5 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p6 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p7 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p8 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p9 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p10 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p11 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p12 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p13 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p14 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p15 = stoi(line, &pos);
        line.erase(0, pos + 1);
        Aux.p16 = stoi(line, &pos);

        sup.push_back(Aux);
        
    }

    int npontos;

    getline(f, line);
    size_t pos2;

    npontos = stof(line, &pos2);

    for (int i = 1; i <= npontos; i++) {
        getline(f, line);
        
        float x, y, z;

        x = stof(line, &pos2);
        line.erase(0, pos2 + 1);
        y = stof(line, &pos2);
        line.erase(0, pos2 + 1);
        z = stof(line, &pos2);

        struct Coords Aux {};
        Aux.xx = x;
        Aux.yy = y;
        Aux.zz = z;

        triangles.push_back(Aux);
    }

    float step = 1 / tess;

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < tess; u++) {
            for (int v = 0; v < tess; v++) {

                float* posA = (float*)malloc(sizeof(float) * 3);
                float* posB = (float*)malloc(sizeof(float) * 3);
                float* posC = (float*)malloc(sizeof(float) * 3);
                float* posD = (float*)malloc(sizeof(float) * 3);

                float* derUA = (float*)malloc(sizeof(float) * 3);
                float* derUB = (float*)malloc(sizeof(float) * 3);
                float* derUC = (float*)malloc(sizeof(float) * 3);
                float* derUD = (float*)malloc(sizeof(float) * 3);

                float* derVA = (float*)malloc(sizeof(float) * 3);
                float* derVB = (float*)malloc(sizeof(float) * 3);
                float* derVC = (float*)malloc(sizeof(float) * 3);
                float* derVD = (float*)malloc(sizeof(float) * 3);

                float* norA = (float*)malloc(sizeof(float) * 3);
                float* norB = (float*)malloc(sizeof(float) * 3);
                float* norC = (float*)malloc(sizeof(float) * 3);
                float* norD = (float*)malloc(sizeof(float) * 3);

                getpos(float(u) * step, float(v) * step, i, posA);
                getpos(float(u) * step, float(v+1) * step , i, posB);
                getpos(float(u+1) * step, float(v) * step, i, posC);
                getpos(float(u+1) * step, float(v+1) * step, i, posD);

                getderiU(float(u) * step, float(v) * step, i, derUA);
                getderiU(float(u) * step, float(v + 1) * step, i, derUB);
                getderiU(float(u + 1) * step, float(v) * step, i, derUC);
                getderiU(float(u + 1) * step, float(v + 1) * step, i, derUD);

                getderiV(float(u) * step, float(v) * step, i, derVA);
                getderiV(float(u) * step, float(v + 1) * step, i, derVB);
                getderiV(float(u + 1) * step, float(v) * step, i, derVC);
                getderiV(float(u + 1) * step, float(v + 1) * step, i, derVD);

                
                cross(derVA, derUA, norA);
                normalize(norA);
                norA[0] = norA[0] * (-1.0);
                norA[1] = norA[1] * (-1.0);
                norA[2] = norA[2] * (-1.0);

                cross(derVB, derUB, norB);
                normalize(norB);
                norB[0] = norB[0] * (-1.0);
                norB[1] = norB[1] * (-1.0);
                norB[2] = norB[2] * (-1.0);

                cross(derVC, derUC, norC);
                normalize(norC);
                norC[0] = norC[0] * (-1.0);
                norC[1] = norC[1] * (-1.0);
                norC[2] = norC[2] * (-1.0);

                cross(derVD, derUD, norD);
                normalize(norD);
                norD[0] = norD[0] * (-1.0);
                norD[1] = norD[1] * (-1.0);
                norD[2] = norD[2] * (-1.0);

                fprintf(fout, "%f %f %f %f %f %f\n", posA[0], posA[1], posA[2], norA[0], norA[1], norA[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posC[0], posC[1], posC[2], norC[0], norC[1], norC[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posB[0], posB[1], posB[2], norB[0], norB[1], norB[2]);

                fprintf(fout, "%f %f %f %f %f %f\n", posB[0], posB[1], posB[2], norB[0], norB[1], norB[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posC[0], posC[1], posC[2], norC[0], norC[1], norC[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posD[0], posD[1], posD[2], norD[0], norD[1], norD[2]);
                
                /*
                fprintf(fout, "%f %f %f %f %f %f\n", posA[0], posA[1], posA[2], norA[0], norA[1], norA[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posB[0], posB[1], posB[2], norB[0], norB[1], norB[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posC[0], posC[1], posC[2], norC[0], norC[1], norC[2]);

                fprintf(fout, "%f %f %f %f %f %f\n", posB[0], posB[1], posB[2], norB[0], norB[1], norB[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posD[0], posD[1], posD[2], norD[0], norD[1], norD[2]);
                fprintf(fout, "%f %f %f %f %f %f\n", posC[0], posC[1], posC[2], norC[0], norC[1], norC[2]);
                */

                free(posA);
                free(posB);
                free(posC);
                free(posD);

                free(derUA);
                free(derUB);
                free(derUC);
                free(derUD);

                free(derVA);
                free(derVB);
                free(derVC);
                free(derVD);

                free(norA);
                free(norB);
                free(norC);
                free(norD);
            }
        }
    }
    
    fclose(fout);
}
