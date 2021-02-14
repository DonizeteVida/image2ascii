/*
 ============================================================================
 Name        : image2letter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include "data/definition.h"
#include "read.h"
#include "print.h"
#include "transform.h"

static void clearImage(struct Image *image) {
	for (int r = 0; r < image->height; r++) {
		free(image->pixels[r]);
	}
	free(image->pixels);
	free(image);
}

static int question(char* q) {
	puts(q);
	int res;
	scanf("%d", &res);
	return res;
}

static struct Image* redim(struct Image* image) {
	if(question("Deseja redimensionar a imagem?")){
		puts("Uhull !!");
		float fator;
		puts("Digite um fator de multiplicação, ele será usado em ambos os lados: ");
		puts("-> (2 dobra tamanho, enquanto .5 diminui em 50% os dois lados) <-");
		scanf("%f", &fator);
		if(fator <= 0) {
			fator = .5;
		}
		struct Image* new = scaleImage(image, fator);
		clearImage(image);
		return new;
	}
	return image;
}

int main(int argc, char *args[]) {
	char buffer[256] = {};

	puts("Bem vindo ao image2ascii, uma implementação em C que lê uma imagem e converte em diversos formatos.");
	puts("");
	puts("Apenas imagens JPEG são suportadas ( e olha lá )");
	puts("Primeiro, digite o nome do arquivo a ser convertido a partir do diretório atual: ");
	scanf("%s", buffer);

	struct Image* userImage = raw2Image(getRaw(buffer));
	toTerminal(userImage);

	return 0;

	puts("");
	puts("Se chegamos até aqui, conseguimos criar um modelo a qual vamos manusear posteriormente.");
	puts("Cada opção oferecerá sub rotinas a fim de controlar o output gerado.");

	do {
		userImage = redim(userImage);
		puts("Escolha a opção dentre os vários conversores disponíveis: ");
		puts("");
		puts("1 -> Gerar um arquivo de texto contendo o modelo de sua imagem");
		puts("2 -> Gerar um HTML colorido contendo o modelo de sua imagem");

		int opc = 0;
		scanf("%d", &opc);
		if(opc > 2 || opc < 1) {
			fprintf(stderr, "-> Vai a merda <-");
			exit(0);
		}
		switch (opc) {
			case 1: {
					do{
						puts("Bom, você escolheu um arquivo de texto, digite o nome do output.txt: ");
						scanf("%s", buffer);

						puts("Esse tipo de implementação necessita de um fator de sensibilidade da cor branca.");
						puts("Digite um valor entre 0 e 255, inclusive: ");
						int fator;
						scanf("%d", &fator);

						toAscii(buffer, userImage, fator);
						puts("Seu arquivo de texto foi gerado !!!");
					}while(!question("Sair da opção 1?"));
				break;
			}

			case 2: {
					do {
						puts("Bom, você escolheu HTML, digite o nome do output.html: ");
						scanf("%s", buffer);
						getchar();

						puts("Digite uma unica letra a ser gerada: EX (@, 8, 1, B)");
						char letter = getchar();

						puts("Digite o tamanho da letra a ser gerada: EX: (10, 20, 30)");
						int pixelSize;
						scanf("%d", &pixelSize);

						puts("Digite a cor de fundo: EX: ( red, black, blue )");
						char color[255];
						scanf("%s", color);

						toHtml(buffer, userImage, letter, pixelSize, color);
						puts("Seu arquivo de HTML foi gerado !!!");
					}while(!question("Sair da opção 2?"));
				break;
			}
		}
	}while(1);

	return 0;
}
