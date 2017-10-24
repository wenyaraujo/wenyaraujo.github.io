#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

//Variáveis da interface
int   d_slider 		= 30;        	//valor inicial do borramento
float d_slider_max 	= 100;			//valor final do borramento

int   position_slider 	  = 50;		//valor inicial da posição. Por default, centralizado. 
float position_slider_max = 100; 	//valor final da posição

int   height_slider 	= 50;       //valor inicial da altura da imagem nítida
float height_slider_max = 100;    	//valor final da altura da imagem nítida - Tem q ser float

//Variáveis da função
int l1, l2;							//Localização da borda superior e inferior da transição nitido-borrado
float d, centro, altura;
unsigned char R,G,B;


Mat image;							//Imagem original
Mat image32F;						//Imagem original em ponto flutuante
Mat result;							//Imagem borrada
//Mat borrada;						//Imagem borrada em ponto flutuante
//Mat degrade;						//Imagem com o comportamento da função a ser aplicada na imagem original
//Mat degrade_negativo;				//Imagem com o comportamento da função a ser aplicada na imagem borrada
Mat resultado;						//Resultado da aplicação do degrade sobre a imagem original
Mat resultado2;						//Resultado da aplicação do degrade negativo sobre a imagem borrada 
Mat final;							//Soma da imagem original + imagem borrada com seus repectivos pesos




void atualiza_tanh(int, void*){
	
    Mat degrade(image.rows,image.cols,CV_8UC3);							//Imagem com o comportamento da função a ser aplicada na imagem original
    Mat degrade_negativo(image.rows,image.cols,CV_8UC3);				//Imagem com o comportamento da função a ser aplicada na imagem borrada

	altura = (float)(height_slider/height_slider_max)*image.rows/2;		//Varia de 0 até image.rows/2
    l1 = -altura;														//Altura da borda de transição nítido-borrado superior
    l2 =  altura;														//Altura da borda de transição nítido-borrado inferior
    d  =  (float)d_slider + 1;											//Intensidade da mudança
   	centro = (float)(position_slider/position_slider_max)*image.rows;   //0-> Nítido no topo; .5 -> Nítido no centro; 1 -> Nítido na base da imagem
    
    //Criação das imagens com degrade (vai ser aplicado na imagem original)    
   	//Degrade para imagem original
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            R = 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            G = 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            B = 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            degrade.at<Vec3b>(i,j)= (Vec3b){B,G,R};
        }
    }
    //Degrade para imagem borrada
    for(int i = 0; i < image.rows; i++){
    	for(int j = 0; j < image.cols; j++){
            degrade_negativo.at<Vec3b>(i,j)= (Vec3b){255,255,255} - degrade.at<Vec3b>(i,j);
        }
    }
 
    
    multiply(image, degrade, resultado, 1/255.0, -1);				//Aplicação do degrade na imagem original
    multiply(result, degrade_negativo, resultado2, 1/255.0, -1);	//Aplicação do degrade_negativo na imagem borrada
    
    final = resultado + resultado2;									//Obtenção da 

}

void borraImagem(Mat imagem, int numero_borramentos){
	//Criação da máscara
	Mat mask(3,3, CV_32F), mask1;
    float media[] = { 1, 1, 1,
                      1, 1, 1,
                      1, 1, 1 };
    mask = Mat(3, 3, CV_32F, media);
    scaleAdd(mask, 1/9.0, Mat::zeros(3, 3, CV_32F), mask1);
    swap(mask, mask1);

    //Conversão para ponto flutuante
    imagem.convertTo(image32F, CV_32F);
    
    //Borramento
    Mat borrada(imagem.rows,imagem.cols,CV_32F);
    for(int i=0; i<numero_borramentos; i++){
    	filter2D(image32F, borrada, CV_32F, mask, Point(1,1), 0);
        image32F=borrada;
    }
    borrada.convertTo(result, CV_8U);

}

void saturaImagem(Mat imagem, float fator){

	cvtColor(imagem,imagem,CV_BGR2HSV);

    for(int i = 0; i< imagem.rows; i++){
    	for(int j = 0; j<imagem.cols; j++){
    		if(imagem.at<Vec3b>(i,j)[1]*fator >= 255)
     			imagem.at<Vec3b>(i,j)[1] = 255;
     		else
     			imagem.at<Vec3b>(i,j)[1] = imagem.at<Vec3b>(i,j)[1]*fator;
     	}
     }

    cvtColor(imagem,imagem,CV_HSV2BGR);
}

int main (){
    
    VideoCapture video;

    video.open("Seattle.mp4");
    if(!video.isOpened())
        return -1;


    int width=video.get(CV_CAP_PROP_FRAME_WIDTH);
    int height=video.get(CV_CAP_PROP_FRAME_HEIGHT);
    cout << "largura=" << width << "\n";;
    cout << "altura =" << height<< "\n";;
    cout << "fps    =" << video.get(CV_CAP_PROP_FPS) << "\n";

    VideoWriter  out("out.avi", video.get(CV_CAP_PROP_FOURCC),
                                video.get(CV_CAP_PROP_FPS),
                                Size(video.get(CV_CAP_PROP_FRAME_WIDTH),
                                video.get(CV_CAP_PROP_FRAME_HEIGHT)),
                                true);

    int cont = 4;
    Mat aux;
    while(1){
        video >> image;
        if(!image.data)
            break;
        if(cont == 4){
            saturaImagem(image,2);
            borraImagem(image,20);
            atualiza_tanh(0,0);
            cont = 0;
            
            out << final;
            final.copyTo(aux);    
        }
        else
            out << aux;

        cont++;  

    }

    //image = imread("nature.jpg",CV_LOAD_IMAGE_COLOR);
    

    //namedWindow("Original",CV_WINDOW_KEEPRATIO);
    //imshow("Original", image);
        
   

  	//namedWindow("Resultado",CV_WINDOW_KEEPRATIO);    
    
    //createTrackbar("Altura ","Resultado",&height_slider,height_slider_max,atualiza_tanh);
    //atualiza_tanh(height_slider,0);

    //createTrackbar("Posicao","Resultado",&position_slider,position_slider_max,atualiza_tanh);
    //atualiza_tanh(position_slider,0);

    //createTrackbar("Borda  ","Resultado",&d_slider,d_slider_max,atualiza_tanh);
    //atualiza_tanh(d_slider,0);

    //waitKey(0);

    video.release();
    out.release();
    
    return 0;
}