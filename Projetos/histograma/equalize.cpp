#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  	Mat image, saida, histograma, histograma2;
  	int larg, alt;

  	int 		 histSize 	= 320;
  	float 		 range[] 	= { 0, 256 };
  	const float* histRange 	= { range };

  	int hist_w 	= 320; 
  	int hist_h 	= 180;
  	int bin_w 	= cvRound( (double) hist_w/histSize );
  	Mat histImage (hist_h, hist_w, CV_8UC3, Scalar( 0,0,0));
  	Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar( 0,0,0));

  	VideoCapture cap;
  	cap.open(0);

  	if(!cap.isOpened()){
    	cout << "deu ruim";
    	return -1;
    }

	while(1){

   		cap >> image;
   		flip(image,image,1);  					//espelhar a tela pra deixar a visualização mais fiel da realidade
   		cvtColor(image,image,CV_BGR2GRAY); 		//Convertendo RGB para Escala de Cinza
   		equalizeHist(image, saida); 			//Função do opencv para equalizar o histograma

   		histImage.setTo( Scalar(0));
   		histImage2.setTo(Scalar(0));

   		calcHist(&image, 1, 0, Mat(), histograma , 1, &histSize, &histRange, true, false);
   		calcHist(&saida, 1, 0, Mat(), histograma2, 1, &histSize, &histRange, true, false);

   		normalize(histograma , histograma , 0, histImage.rows , NORM_MINMAX, -1, Mat());
   		normalize(histograma2, histograma2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());

   		for(int i = 0; i < histSize; i++){
   			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(histograma.at<float>(i-1)) ) , Point( bin_w*(i), hist_h - cvRound(histograma.at<float>(i)) ),Scalar( 255, 255, 255), 2, 8, 0  );
   			line( histImage2,Point( bin_w*(i-1), hist_h - cvRound(histograma2.at<float>(i-1))) , Point( bin_w*(i), hist_h - cvRound(histograma2.at<float>(i)) ),Scalar( 255, 255, 255), 2, 8, 0  );
   		}

   		//histImage.copyTo(image( Rect(0,      0, histSize, hist_h)));
   		//histImage2.copyTo(image(Rect(0, hist_h, histSize, hist_h)));

   		namedWindow("entrada", CV_WINDOW_KEEPRATIO);
   		namedWindow("histograma Entrada", CV_WINDOW_KEEPRATIO);
   		namedWindow("saida", CV_WINDOW_KEEPRATIO);
   		namedWindow("histograma Saida", CV_WINDOW_KEEPRATIO);

   		imshow("histograma Entrada", histImage);
   		imshow("histograma Saida", histImage2);
   		imshow("entrada", image);
   		imshow("saida",saida);
		if(waitKey(30) >= 0) break;    
		
     	//imwrite("saida.png",saida);
     	//imwrite("entrada.png",image);
  }
  return 0;
}