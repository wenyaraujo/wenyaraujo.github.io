#include <iostream>
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  	Mat image,image2;

  	//Variáveis necessárias para a construção do histograma
  	int 		 histSize 	= 64;                   //Número de subdivisões horizontais
  	float 		 range[] 	= { 0, 256 };           //Limites inferior e superior do histograma
  	const float* histRange 	= { range };
  	Mat histograma, histograma2;                    //Objeto onde o histograma será armazenado
  	Mat histImage,histImage2;

  	double alert, media;

  	VideoCapture cap;
  	cap.open(0);

  	if(!cap.isOpened()){
    	cout << "Erro de abertura da webcam.";
    	return -1;
    }

	while(1){

   		cap >> image;
   		flip(image,image,1);                          //espelhar a tela pra deixar a visualização mais fiel da realidade
   		cvtColor(image,image,CV_BGR2GRAY);            //Convertendo RGB para Escala de Cinza
   		usleep(10000);                                //10ms delay

   		cap >> image2;
   		flip(image2,image2,1);                        //espelhar a tela pra deixar a visualização mais fiel da realidade
   		cvtColor(image2,image2,CV_BGR2GRAY);          //Convertendo RGB para Escala de Cinza

   		//Reinicializando as imagens dos histogramas
   		histImage.setTo( Scalar(0));
   		histImage2.setTo(Scalar(0));

   		//Calculando o histograma das imagens
   		calcHist(&image, 1, 0, Mat(), histograma , 1, &histSize, &histRange, true, false);
   		calcHist(&image2, 1, 0, Mat(), histograma2, 1, &histSize, &histRange, true, false);

      //Realizando a comparação entre os dois histogramas obtidos
   		alert = compareHist(histograma, histograma2,CV_COMP_CORREL);

      //Definição do limiar de diferença entre os histogramas
   		media = 0.999;

      //Apresentação dos resultados
      if(alert < media)
        cout << alert << " MOVIMENTO" << endl;
   		
      namedWindow("entrada", CV_WINDOW_KEEPRATIO);
      imshow("entrada", image);
	  if(waitKey(10) >= 0) break;    	
	}

  	imwrite("saida.png",image2);
  	imwrite("entrada.png",image);
  	return 0;
}