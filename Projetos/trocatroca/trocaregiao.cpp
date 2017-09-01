#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  int larg, alt;

  image = imread("mindful.png",CV_LOAD_IMAGE_COLOR);
	if(!image.data)
    cout << "A imagem não pôde ser carregada ou está corrompida." << endl;
  
  larg=image.size().width;
  alt=image.size().height;

  Mat troca(alt, larg, image.type());

  image(Rect(0, 0, larg/2, alt/2)).copyTo(troca(Rect(larg/2, alt/2, larg/2, alt/2)));

  image(Rect(0, alt/2, larg/2, alt/2)).copyTo(troca(Rect(larg/2,0, larg/2, alt/2)));

  image(Rect(larg/2,0,larg/2,alt/2)).copyTo(troca(Rect(0,alt/2, larg/2, alt/2)));

  image(Rect(larg/2,alt/2,larg/2,alt/2)).copyTo(troca(Rect(0,0, larg/2, alt/2)));

	imwrite("trocatroca.png", troca);
  imshow("image", troca);
  waitKey();
  return 0;
}

