/******************************************************************************/
/**                                                    ,---------------.     **/
/**    COMPUTACAO GRAFICA                              |        .-.    |     **/
/**    MIEEC - FCTUC                                   |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - ...................                  |  `---'   `-'  |     **/
/**             - ...................                  `---------------'     **/
/******************************************************************************/
/* DESCRICAO: Texto que devera descrever os objectivos e os resultados .....  */
/*            do programa. .................................................  */
/*		      ..............................................................  */
/******************************************************************************/
// 
//	Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
//
//	Definições /////////////////////////////////////////////////////////////////
//
// Exemplo da definição de uma constante
#define PI    3.1415927
#define SAIR {fclose(fp_arquivo); return -1;}
#define CTOI(C) (*(int*)&C)
GLuint texture_id[11];
//
//	Funções ////////////////////////////////////////////////////////////////////
//

// Função para fazer o load das texturas de acordo com o indice
int LoadBMP(char *file, int id){
	GLubyte *image;
	GLubyte Header[0x54];
	GLuint DataPos, imageSize;
	GLsizei Width, Height;
	int nb = 0;
	// Abre o arquivo e efetua a leitura do Header do arquivo BMP
	FILE * fp_arquivo = fopen(file, "rb");
	if (!fp_arquivo)
		return -1;
	if (fread(Header, 1, 0x36, fp_arquivo) != 0x36)
		SAIR;
	if (Header[0] != 'B' || Header[1] != 'M')
		SAIR;
	if (CTOI(Header[0x1E]) != 0)
		SAIR;
	if (CTOI(Header[0x1C]) != 24)
		SAIR;
	// Recupera a informação dos atributos de
	// altura e largura da imagem
	Width = CTOI(Header[0x12]);
	Height = CTOI(Header[0x16]);
	(CTOI(Header[0x0A]) == 0) ? (DataPos = 0x36) : (DataPos = CTOI(Header[0x0A]));
	imageSize = Width*Height * 3;
	// Efetura a Carga da Imagem
	image = (GLubyte *)malloc(imageSize);
	int retorno;
	retorno = fread(image, 1, imageSize, fp_arquivo);
	if (retorno != imageSize)
	{
		free(image);
		SAIR;
	}
	// Inverte os valores de R e B
	int t, i;
	for (i = 0; i < (int)imageSize; i += 3)
	{

		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	// Tratamento da textura para o OpenGL
	glBindTexture(GL_TEXTURE_2D, texture_id[id]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Faz a geraçao da textura na memória-
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE,
		image);
	fclose(fp_arquivo);
	free(image);
	return 1;
}
// Função para aplicar uma textura ao objecto
void textura(int id1, int id2){

	glBindTexture(GL_TEXTURE_2D, texture_id[id2]); //MASCARA
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);	// inferior esquerdo
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);	// inferior direito
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);	// superior direito
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);	// superior esquerdo
	glEnd();

	glBlendFunc(GL_ONE, GL_ONE); //PEIXE		
	glBindTexture(GL_TEXTURE_2D, texture_id[id1]); //Load texture
	glBegin(GL_QUADS);							   //Desenha pelos vertices ortho
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glEnd();
}
//Inicializar texturas
void InitTexture(){
	//determinação dos ficheiros a carregar que vão servir de texturas
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(11, texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	LoadBMP("aquario.bmp", 0);
	glBindTexture(GL_TEXTURE_2D, texture_id[1]);
	LoadBMP("aquariomask.bmp", 1);
	glBindTexture(GL_TEXTURE_2D, texture_id[2]);
	LoadBMP("Clown_fish.bmp", 2);
	glBindTexture(GL_TEXTURE_2D, texture_id[3]);
	LoadBMP("Clown_fishmask.bmp", 3);
}