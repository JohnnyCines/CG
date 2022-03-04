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
            x += lq; //percorrer o lado do quadrado para o próximo ponto
        }
        x = -length/2; //reinicializar eixo dos x
        z -= lq; 
    }
}
