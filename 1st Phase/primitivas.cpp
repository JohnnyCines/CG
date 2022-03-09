void plano(float length, float divisions, char *fname){
    File * f = fopen(fname, "w");
    
    //ponto de partida dos eixos x e z
    float x = -length/2; 
    float z = length/2;
    
    //comprimento do lado de cada quadrado pequeno
    float lq = length/divisions;
    

    while(z!=-length/2){
        while(x!= length/2){
            //guardar triângulos
            fprintf(f, %f %f %f, x, 0.0, z); 
            //linhas trocadas
            fprintf(f, %f %f %f, x+lq, 0.0, z-lq);
            fprintf(f, %f %f %f, x, 0.0, z-lq);

            fprintf(f, %f %f %f, x, 0.0, z);
            fprintf(f, %f %f %f, x+lq, 0.0, z);
            fprintf(f, %f %f %f, x+lq, 0.0, z-lq);

            x += lq; //incrementar x para o próximo ponto
        }
        x = -length/2; //reinicializar eixo dos x
        z -= lq; //decrementar z para o próximo ponto
    }
}

void caixa(float dimension, float divisions, char *fname){
    File *f = fopen(fname, "w");

    //diferença entre cada ponto
    float lq = length/divisions

    //ponto de partida nos extremos de y
    float x = -length/2;
    float z = length/2;
    float y = -length/2;

    //cálculo dos triângulos nas duas faces nos extremos de y
    while(y<length){
        while(z!=-length/2){
            while(x!= length/2){
                //guardar triângulos
                fprintf(f, %f %f %f, x, y, z); 
                fprintf(f, %f %f %f, x, y, z-lq);
                fprintf(f, %f %f %f, x+lq, y, z-lq);

                fprintf(f, %f %f %f, x, y, z);
                fprintf(f, %f %f %f, x+lq, y, z);
                fprintf(f, %f %f %f, x+lq, y, z-lq);

                x += lq; //incrementar x para o próximo ponto
            }
            x = -length/2; //reinicializar eixo dos x
            z -= lq; //decrementar z para o próximo ponto
        }
        y+=length; //incrementar y para o próximo extremo
    }

    //ponto de partida nos extremos de z
    x = -length/2;
    z = -length/2;
    y = -length/2;

    //cálculo dos triângulos nas duas faces nos extremos de z
    while(z<length){
        while(y!=length/2){
            while(x!= length/2){
                //guardar triângulos
                fprintf(f, %f %f %f, x, y, z); 
                fprintf(f, %f %f %f, x, y+lq, z);
                fprintf(f, %f %f %f, x+lq, y+lq, z);

                fprintf(f, %f %f %f, x, y, z);
                fprintf(f, %f %f %f, x+lq, y, z);
                fprintf(f, %f %f %f, x+lq, y+lq, z);

                x += lq; //incrementar x para o próximo ponto
            }
            x = -length/2; //reinicializar eixo dos x
            y += lq; //incrementar y para o próximo ponto
        }
        z+=length; //incrementar z para o próximo extremo
    }

    //ponto de partida nos extremos de x
    x = -length/2;
    z = length/2;
    y = -length/2;

    //cálculo dos triângulos nas duas faces nos extremos de x
    while(x<length){
        while(y!=length/2){
            while(z!= -length/2){
                //guardar triângulos
                fprintf(f, %f %f %f, x, y, z); 
                fprintf(f, %f %f %f, x, y, z-lq);
                fprintf(f, %f %f %f, x, y+lq, z-lq);

                fprintf(f, %f %f %f, x, y, z);
                fprintf(f, %f %f %f, x, y+lq, z);
                fprintf(f, %f %f %f, x, y+lq, z-lq);

                z -= lq; //decrementar z para o próximo ponto
            }
            z = length/2; //reinicializar eixo do z
            y += lq; //incrementar y para o próximo ponto
        }
        x+=length; //incrementar x para o próximo extremo
    }
}


void esfera(float r, int slices, int stacks, char *fname){
    
    float a,b
    float sl = 2.0f * M_PI / float(slices), st = M_PI / float(stacks);
    float px1,px2,px3,px4,py1,py2,pz1,pz2,pz3,pz4;
    
    for (a = 0.0f; a <= 2 * M_PI; a += sl) {
		for (b = -M_PI / 2.0f; b < M_PI / 2.0f; b += st) {

			if (a >= M_PI / 2.0f && a <= 3.0f * M_PI / 2.0f) {
				//triangulos que nao se veem
                px1 = r * cos(b) * sin(a);
                px2 = r * cos(b) * sin(a + sl);
                px3 = r * cos(b + st) * sin(a);
                px4 = r * cos(b + st) * sin(a + sl)
                
                py1 = r * sin(b);
                py2 = r * sin(b + st);
                
                pz1 = r * cos(b) * cos(a);
                pz2 = r * cos(b) * cos(a + sl);
                pz3 = r * cos(b + st) * cos(a);
                pz4 = r * cos(b + st) * cos(a + sl);
                
				//glVertex3f(r * cos(b) * sin(a), r * sin(b), r * cos(b) * cos(a));
				//glVertex3f(r * cos(b) * sin(a + sl), r * sin(b), r * cos(b) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a), r * sin(b + st), r * cos(b + st) * cos(a));
                
                fprintf(f, %f %f %f, px1, py1, pz1); 
                fprintf(f, %f %f %f, px2, py1, pz2);
                fprintf(f, %f %f %f, px3, py2, pz3);

				//glVertex3f(r * cos(b) * sin(a + sl), r * sin(b), r * cos(b) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a + sl), r * sin(b + st), r * cos(b + st) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a), r * sin(b + st), r * cos(b + st) * cos(a));
                
                fprintf(f, %f %f %f, px2, py1, pz2); 
                fprintf(f, %f %f %f, px4, py2, pz4);
                fprintf(f, %f %f %f, px3, py2, pz3);
			}
			else {
				//triangulos visiveis
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
                
				//glVertex3f(r * cos(b) * sin(a), r * sin(b), r * cos(b) * cos(a));
				//glVertex3f(r * cos(b) * sin(a + sl), r * sin(b), r * cos(b) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a), r * sin(b + st), r * cos(b + st) * cos(a));
                
                fprintf(f, %f %f %f, px1, py1, pz1); 
                fprintf(f, %f %f %f, px2, py1, pz2);
                fprintf(f, %f %f %f, px3, py2, pz3);

				//glVertex3f(r * cos(b) * sin(a + sl), r * sin(b), r * cos(b) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a + sl), r * sin(b + st), r * cos(b + st) * cos(a + sl));
				//glVertex3f(r * cos(b + st) * sin(a), r * sin(b + st), r * cos(b + st) * cos(a));
                
                fprintf(f, %f %f %f, px2, py1, pz2); 
                fprintf(f, %f %f %f, px4, py2, pz4);
                fprintf(f, %f %f %f, px3, py2, pz3);
                }
        }
    }
}
