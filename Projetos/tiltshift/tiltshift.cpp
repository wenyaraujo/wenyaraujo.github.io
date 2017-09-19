#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;

double alfa, beta;
int alfa_slider = 0;                //valor inicial do borramento
int alfa_slider_max = 100;  //valor final do borramento

int position_slider = 50;          //valor inicial da posição. Por default, centralizado. 
int position_slider_max = 100; //valor final da posição

int height_slider = 0;        //valor inicial da altura da imagem nítida
int height_slider_max = 100;    //valor final da altura da imagem nítida

char TrackbarName[50];

Mat degrade;

//void multiply(image, image2, saida, double scale=1, int dtype=-1 )

//void addWeighted(src1, alfa, src2, beta, 0, dst, -1);



/* Essa parte é para borrar a imagem*/
int main (){
    Mat image, image32F, result;
      //quer por ela como variavel da main ou global?
    Vec3b valor_degrade;
    unsigned char R,G,B;

    Mat mask(3,3, CV_32F), mask1;

    float media[] = { 1, 1, 1,
                                      1, 1, 1,
                                        1, 1, 1 };
    mask = Mat(3, 3, CV_32F, media);
    scaleAdd(mask, 1/9.0, Mat::zeros(3, 3, CV_32F), mask1);
    swap(mask, mask1);

    image = imread("aew.png",CV_LOAD_IMAGE_COLOR);
    Mat borrada(image.rows,image.cols,CV_32F);
    Mat degrade(image.rows,image.cols,CV_8UC3);
    Mat degrade_negativo(image.rows,image.cols,CV_8UC3);
    
    imshow("aew", image);
    waitKey();

    image.convertTo(image32F, CV_32F);


    for(int i=0; i<20; i++){
        filter2D(image32F, borrada, CV_32F, mask, Point(1,1), 0);
        image32F=borrada;
    }

    borrada.convertTo(result, CV_8U);
    imshow("aew", result);
    waitKey();
    // Nesse momento temso: image -> imagem original; result -> imagem borrada

    
    int l1, l2, d, centro, altura;
    altura = image.rows/4;
    l1 = -altura;
    l2 =  altura;
    d  =   6;
    centro = image.rows/2;    //entrada da interface (0-100%)*image.rows (na interface, por padrão é 50%)
    
    //Criação das imagens com degrade (vai ser aplicado na imagem original)    
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            R = (unsigned char) 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            G = (unsigned char) 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            B = (unsigned char) 255*0.5*(tanh(((i-centro)-l1)/(d))-tanh(((i-centro)-l2)/(d)));
            valor_degrade = (Vec3b){B,G,R};
            degrade.at<Vec3b>(i,j)= valor_degrade;
        }
    }
    
    imshow("degrade", degrade);
    waitKey();
    
    //Criação do degrade negativo (vai ser aplicado na imagem borrada)
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            degrade_negativo.at<Vec3b>(i,j)= (Vec3b){255,255,255} - degrade.at<Vec3b>(i,j);
        }
    }
    imshow("degrade", degrade_negativo);
    waitKey();
    
    Mat resultado, resultado2, final;
    
    multiply(image, degrade, resultado, 1/255.0, -1);
    multiply(result, degrade_negativo, resultado2, 1/255.0, -1);
    
  
    final = resultado + resultado2;
   
  
    imshow("Resultado", final);
    waitKey();
    
    
    
    
    
    
    return 0;
}

