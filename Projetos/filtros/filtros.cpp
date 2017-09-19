#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void menu(){
  cout << "\npressione a tecla para ativar o filtro: \n"
			"a - calcular modulo\n"
    		"m - media\n"
    		"g - gauss\n"
    		"v - vertical\n"
			"h - horizontal\n"
    		"l - laplaciano\n"
    		"j - laplaciano do gaussiano\n"
			"esc - sair\n" << endl;
}

int main(int argvc, char** argv){
  	
	float media[] 		= {	1, 1, 1,
				   			1, 1, 1,
				   			1, 1, 1 };

	float gauss[] 		= {	1, 2, 1,
				   			2, 4, 2,
				   			1, 2, 1 };

	float horizontal[]	= {-1, 0, 1,
					       -2, 0, 2,
					       -1, 0, 1 };

	float vertical[]	= {-1,-2,-1,
					    	0, 0, 0,
					    	1, 2, 1 };

	float laplacian[]	= { 0,-1, 0,
					       -1, 4,-1,
					        0,-1, 0 };

	float nada[]		= {	0, 0, 0,
					   		0, 1, 0,
					   		0, 0, 0 };

	VideoCapture video;
	Mat cap, frame, frame32f, frameFiltered, frameFiltered2;
	Mat mask(3,3,CV_32F), mask1;
	Mat result;
	double width, height, min, max;
	char key;
	int absolut;

	video.open(0); 
  	if(!video.isOpened()) 
    	return -1;
  	width  = video.get(CV_CAP_PROP_FRAME_WIDTH);
  	height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
  	cout << "largura = " << width  << "\n";
  	cout << "altura  = " << height << "\n";

  	menu();

  	namedWindow("Original",CV_WINDOW_KEEPRATIO);
  	namedWindow("Filtro",CV_WINDOW_KEEPRATIO);

  	while(1){

  		switch(key){
  			case 'm':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, media);
  					scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask1);
      				mask = mask1;
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);

  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					imshow("Original", frame);
  					imshow("Filtro", result);

  					imwrite("filtro_media_entrada.png",frame);
  					imwrite("filtro_media_saida.png",result);
  					
  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'g' || key == 'h' || key == 'v' || key == 'l' || key == 'j') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			case 'g':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, gauss);
  					scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      				mask = mask1;
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);

  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					imshow("Original", frame);
  					imshow("Filtro", result);

  					imwrite("filtro_gaussiano_entrada.png",frame);
  					imwrite("filtro_gaussiano_saida.png",result);
  					
  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'm' || key == 'h' || key == 'v' || key == 'l' || key == 'j') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			case 'h':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, horizontal);
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
  					
  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);

  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					imshow("Original", frame);
  					imshow("Filtro", result);
  					
  					imwrite("filtro_horizontal_entrada.png",frame);
  					imwrite("filtro_horizontal_saida.png",result);

  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'm' || key == 'g' || key == 'v' || key == 'l' || key == 'j') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			case 'v':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, vertical);
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);
  					
  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					imshow("Original", frame);
  					imshow("Filtro", result);

  					imwrite("filtro_vertical_entrada.png",frame);
  					imwrite("filtro_vertical_saida.png",result);
  					
  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'm' || key == 'g' || key == 'h' || key == 'l' || key == 'j') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			case 'l':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, laplacian);
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

  					//minMaxLoc(frameFiltered, &min, &max);

  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);
  					
  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					//result = result + abs(min);
  					imshow("Original", frame);
  					imshow("Filtro", result);
  					
  					imwrite("filtro_laplaciano_entrada.png",frame);
  					imwrite("filtro_laplaciano_saida.png",result);

  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'm' || key == 'g' || key == 'h' || key == 'v' || key == 'j') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			case 'j':
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro gaussiano
  					mask = Mat(3, 3, CV_32F, gauss);
  					scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      				mask = mask1;
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);

  					//Cálculo do filtro laplaciano
  					mask = Mat(3, 3, CV_32F, laplacian);
  					filter2D(frameFiltered, frameFiltered2, frame32f.depth(), mask, Point(1,1), 0);

  					//minMaxLoc(frameFiltered, &min, &max);

  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered2 = abs(frameFiltered2);
  					
  					//Apresentação do resultado
  					frameFiltered2.convertTo(result, CV_8U);
  					//result = result + abs(min);
  					imshow("Original", frame);
  					imshow("Filtro", result);

  					imwrite("filtro_lapl_gaussiano_entrada.png",frame);
  					imwrite("filtro_lapl_gaussiano_saida.png",result);
  					
  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 'm' || key == 'g' || key == 'h' || key == 'v' || key == 'l') break;
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  				}
  				break;

  			default:
  				while(1){
  					//Captura da imagem
  					video >> cap;
  					cvtColor(cap, frame, CV_BGR2GRAY);		//Deixa imagem em grayscale
  					flip(frame, frame, 1);					//Flip para ter efeito de espelho na webcam
  					frame.convertTo(frame32f, CV_32F);		//Para realizar cálculos com numeros decimais, converte para float

  					//Cálculo do filtro 
  					mask = Mat(3, 3, CV_32F, nada);
  					filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
  					
  					//Teste se a opção de absoluto está habilitada
  					if(absolut)
  						frameFiltered = abs(frameFiltered);

  					//Apresentação do resultado
  					frameFiltered.convertTo(result, CV_8U);
  					imshow("Original", frame);
  					imshow("Filtro", result);
  					
  					//Leitura do teclado
  					key = (char) waitKey(10);
  					if(key == 27) return 0;
  					if(key == 'a')
  						absolut=!absolut;
  					if(key !=  0) break;
  					
  				}
  				break;
  		}
  	}
  	return 0;
}