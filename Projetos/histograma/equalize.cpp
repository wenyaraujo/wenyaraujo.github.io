#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, saida;
  int larg, alt;
  vector<Mat> canais;

  VideoCapture cap;
  cap.open(0);

  if(!cap.isOpened()){
    cout << "deu ruim";
    return -1;
    }

  larg  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  alt = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	while(1){

   cap >> image;
   flip(image,image,1);  //espelhar a tela pra deixar a visualização mais fiel da realidade
   cvtColor(image,image,CV_BGR2GRAY); //Convertendo RGB para Escala de Cinza
   equalizeHist(image, saida); //Função do opencv para equalizar o histograma

   namedWindow("entrada");
   namedWindow("saida");
   imshow("entrada", image);
   imshow("saida",saida);
	 if(waitKey(30) >= 0) break;    
		
     imwrite("saida.png",saida);
     imwrite("entrada.png",image);
    
  }
  return 0;
}


