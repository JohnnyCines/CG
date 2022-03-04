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
            fprintf(f, %f %f %f, x, 0.0, z-lq);
            fprintf(f, %f %f %f, x+lq, 0.0, z-lq);

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