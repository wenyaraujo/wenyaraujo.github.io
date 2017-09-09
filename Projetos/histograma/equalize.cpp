#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, out;
  int width, height;
  vector<Mat> channels;
  char key;

  VideoCapture cap;
  cap.open(0);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
    }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	while(1){

   cap >> image;
   flip(image,image,1);  //espelhar a tela pra deixar a visualização mais fiel da realidade
   cvtColor(image,image,CV_BGR2GRAY); //Convertendo RGB para Escala de Cinza
   equalizeHist(image, out); //Função do opencv para equalizar o histograma

   namedWindow("source");
   namedWindow("output");
   imshow("souce", image);
   imshow("output",out);
   key = waitKey(30);  
   if(key==27) break;
   if(key==112){
     imwrite("saida.png",out);
     imwrite("entrada.png",image);
   } 
  }
  return 0;
}


