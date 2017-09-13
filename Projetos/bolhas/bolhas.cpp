#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    Mat image;											//Imagem a ser modificada
	int width, height;									//Largura e altura da imagem
	int i,j;											//Variáveis auxiliares para percorrer a imagem
	CvPoint p;											//Ponto da imagem a ser usado no floodfill	
	unsigned long int contador_bolhas = 0;				//Variável para contagem de bolhas. A contagem é feita pela mudança RGB, 
														//sendo necessário ao menos 24 bits.
	unsigned long int contador_bolhas_com_buracos = 0;	//Variável para contagem de bolhas com buracos.
	unsigned long int contador_bolhas_sem_buracos = 0;	//Variável para contagem de bolhas sem buracos.
	Vec3b cor_bolha_com_buraco(255,0,0);				//Cor identificadora de bolhas com buracos (Azul)
	Vec3b branco(255,255,255);							//Cor das bolhas
	Vec3b preto (0,0,0);								//Cor de fundo da imagem
	Vec3b label;										//Cor para labelling
	

	//============== Aquisição da Imagem ========================================
	image = imread(argv[1],CV_LOAD_IMAGE_COLOR);		//Leitura da imagem
	if(!image.data){									//Teste de falha na leitura
        cout << "Imagem nao carregou corretamente.\n";
        return(-1);
	}
	
	width=image.size().width;							//Largura da imagem
    height=image.size().height;							//Altura da imagem
	
	//============== Remoção de bolhas que tocam a borda da imagem ==============
	
	//Remoção na lateral esquerda: índice j = 0 para primeira coluna, e índice i varre todas as linhas
	//Caso encontre um pixel branco, realiza o floodfill para a cor de fundo (preto)
	i = 0; j = 0;
	for(i = 0; i < height; i++){
		if(image.at<Vec3b>(i,j) == branco){
			p.x=j; p.y=i;
			floodFill(image,p,preto);
		}
	}
	
	//Remoção na lateral direita: índice j = largura - 1 para a última coluna, e índice i varre todas as linhas
	//Caso encontre um pixel branco, realiza o floodfill para a cor de fundo (preto)
	i = 0; j = width - 1;
	for(i = 0; i < height; i++){
		if(image.at<Vec3b>(i,j) == branco){
			p.x=j; p.y=i;
			floodFill(image,p,preto);
		}
	}
	
	//Remoção na linha superior: indice i = 0 para a primeira linha, e índice j varre todas as colunas
	//Caso encontre um pixel branco, realiza o floodfill para a cor de fundo (preto)
	i = 0; j = 0;
	for(j = 0; j < width; j++){
		if(image.at<Vec3b>(i,j) == branco){
			p.x=j; p.y=i;
			floodFill(image,p,preto);
	  }
	}

	//Remoção na linha inferior: índice i = altura - 1, e índice j varre todas as colunas
	//Caso encontre um pixel branco, realiza o floodfill para a cor de fundo (preto)
	i = height - 1; j = 0;
	for(j = 0; j < width; j++){
		if(image.at<Vec3b>(i,j) == branco){
			p.x=j; p.y=i;
			floodFill(image,p,preto);
	  }
	}
  
	
	//================ Alteração da cor de fundo da imagem ==========================
	p.x=0; p.y=0;										//O ponto 0,0 faz parte do fundo da imagem
	floodFill(image,p,Scalar(1,1,1)); 					//Após essa modificação, apenas os buracos estarão com cor preta (0,0,0)

	imwrite("1.png", image);
	//================ Identificar bolhas com buracos	===============================
	for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<Vec3b>(i,j) == preto){				             //Caso seja encontrado um pixel pertencente a um buraco
				if(image.at<Vec3b>(i,j-1) == cor_bolha_com_buraco){} //E o pixel anterior mostrar que a bolha já foi identificada,
																	 //Não fazer nada
				else if(image.at<Vec3b>(i,j-1) == branco){			 //Caso o pixel anterior não tenha a cor identificadora, mas seja branco
					p.x=j - 1; p.y=i;								 //Estamos tratando de uma bolha com buraco
					floodFill(image,p,cor_bolha_com_buraco);		 //Então mudamos a bolha para uma cor identificadora
				}
			}
		}
	}

	//================ Alteração da cor de fundo da imagem ==========================
	p.x=0; p.y=0;													//O ponto 0,0 faz parte do fundo da imagem
	floodFill(image,p,preto); 										//Deixa a cor de fundo como preto novamente

	imwrite("2.png", image);
	//================ Realizar o labelling das bolhas ==============================
	for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
			p.x=j; p.y=i;
			if(image.at<Vec3b>(i,j) == branco){						//Caso seja encontrado uma bolha branca
				contador_bolhas++;									//Incrementa o contador para labelling
				contador_bolhas_sem_buracos++;						//Incrementa a contagem de bolhas sem buraco
				label[0] = contador_bolhas & 0x0000FF;				//Atribui à componente B, os 8 bits menos significativos do contador
				label[1] = (contador_bolhas & 0x00FF00) >> 8;		//Atribui à componente G, os bits 15-8  do contador
				label[2] = (contador_bolhas & 0xFF0000) >> 16;		//Atribui à componente R, os bits 23-16 do contador
				floodFill(image,p,label);							//Realiza o labelling da bolha
			}
			else if(image.at<Vec3b>(i,j) == cor_bolha_com_buraco){  //Caso seja encontrado uma bolha com a cor identificadora que possui buraco
				contador_bolhas++;									//Incrementa o contador para labelling
				contador_bolhas_com_buracos++;						//Incrementa a contagem de bolhas com buraco
				label[0] =  contador_bolhas & 0x0000FF;				//Atribui à componente B, os 8 bits menos significativos do contador
				label[1] = (contador_bolhas & 0x00FF00) >> 8;		//Atribui à componente G, os bits 15-8  do contador
				label[2] = (contador_bolhas & 0xFF0000) >> 16;		//Atribui à componente R, os bits 23-16 do contador
				floodFill(image,p,label);							//Realiza o labelling da bolha
			}
		}
	}

	//============= Exibe resultado ===================================================
	cout << "Número de bolhas sem buracos: " << contador_bolhas_sem_buracos << endl;
	cout << "Número de bolhas com buracos: " << contador_bolhas_com_buracos << endl;
	cout << "Número total de bolhas: " 		 << contador_bolhas 			<< endl;

	namedWindow("Labelling",CV_WINDOW_KEEPRATIO);					//Cria janela
    imshow("Labelling", image);										//Exibe imagem na janela criada
    imwrite("labeling-result.png", image);							//Gera arquivo com a imagem resultante
    waitKey();														//Espera teclado ser pressionado para finalizar o programa

	return 0;
}
