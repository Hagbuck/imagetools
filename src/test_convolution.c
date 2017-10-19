

int tab[3][3]; 			//matrice de convulation
int image[256][256];	//image de taille 256*256


for(j=0;j<256;j++){
	for(i=0;i<256;i++){
		for(x=0;x<3;x++){ 
			for(y=0;y<3;y++){ 
				somme=somme+image[i][j]*tab[y+i][x+j]; 
			}
		}
	image[i+1][j+1]=somme;
	} 
}