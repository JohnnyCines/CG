void plano(float length, float divisions, char *fname){
    File * f = fopen(fname, "w");
    
    //ponto de partida dos eixos x e z
    float x = -length/2; 
    float z = length/2;
    
    //comprimento do lado de cada quadrado pequeno
    float lq = length/divisions;
    

    while(z>=-length/2){
        while(x<= length/2){
            fprintf(f, %f %f %f, x, 0.0, z); //guardar o ponto
            x += lq; //incrementar x para o próximo ponto
        }
        x = -length/2; //reinicializar eixo dos x
        z -= lq; //decrementar z para o próximo ponto
    }
}

void caixa(float dimension, float divisions, char *fname){
    File *f = fopen(fname, "w");

    //ponto de partida
    float x = -length/2;
    float z = -length/2;
    float y = -length/2;

    //diferença entre cada ponto
    float lq = length/divisions

    while(y<=length/2){
        while(z<=length/2){
            while (x<=length/2){
                fprintf(f, %f %f %f, x,y,z); //guardar
                x += lq; //incrementar
            }
            y+= lq; //incrementar
        }
        z+=lq; //incrementar
    }



}