#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image; 
  int larg, alt, sobj, sbur;  //variáveis para implementação do código.
  vector<int> obj; //vetor obj que auxilia na "varredura" dos pixels
	CvPoint p; 	//p é um ponto.

  image = imread("bolhas.png",CV_LOAD_IMAGE_GRAYSCALE); 
  if(!image.data)
    cout << "A imagem não pôde ser carregada ou está corrompida." << endl;

  larg=image.size().width; //definindo largura como sendo a da imagem lida
  alt=image.size().height; //definindo altura como sendo a da imagem lida


  // procurando objetos partindo do 0 e usando um for para varrer a imagem
  p.x=0;
  p.y=0;

  sobj=0;
  for(int i=0; i<alt; i++){
    for(int j=0; j<larg; j++){
      if(image.at<uchar>(i,j) == 255){
		    // achou um objeto
		    sobj++;
		    p.x=j;
		    p.y=i;
		    floodFill(image,p,sobj); //utilizando da função floodfill 
	    }
	  }
  }

  imshow("image", image);
  imwrite("flood.png", image);
  waitKey();

  //retirando objetos que tocam nas bordas

  for(int i=0; i<alt; i++){
    for(int j=0; j<larg; j++){
      if(i==0 | i==255 | j==0 | j==255){
        if(image.at<uchar>(i,j) != 0){
          p.x=j;
          p.y=i;
          floodFill(image,p,0);
        }
      }
    }
  }
  //trocando o fundo da imagem para valor 255

  p.x=0;
  p.y=0;
  floodFill(image,p,255);

	imshow("image", image);
  imwrite("ds.png", image);
  waitKey();

  //procurando objetos com buracos

  sbur=0;
  for(int i=0; i<alt; i++){
    for(int j=0; j<larg; j++){
      int flag=0;
      if(image.at<uchar>(i,j) == 0){ //achou um buraco

        int ant = (int) image.at<uchar>(i, j-1); //salva o valor do pixel anterior à semente do buraco encontrado

        for(int k=0; k<obj.size(); k++){
          if(ant == obj[k]){
            flag=1;
          }
        }
        if(flag==0){
          obj.push_back(ant);
          sbur++;
        }

        // rotulando o buraco com 255
        p.x=j;
        p.y=i;
        floodFill(image,p,255);
      }
    }
  }

  cout << "O número de bolhas que contém no mínimo 1 buraco e que não toca as bordas são: " << sbur << endl;

  return 0;
}
