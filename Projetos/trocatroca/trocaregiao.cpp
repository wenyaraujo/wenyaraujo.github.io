#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  int width, height;

  image = imread("mindful.png",CV_LOAD_IMAGE_COLOR);
	if(!image.data)
    cout << "A imagem não pôde ser carregada ou está corrompida." << endl;
  
  width=image.size().width;
  height=image.size().height;

  Mat troca(height, width, image.type());

  image(Rect(0, 0, width/2, height/2)).copyTo(troca(Rect(width/2, height/2, width/2, height/2)));

  image(Rect(0, height/2, width/2, height/2)).copyTo(troca(Rect(width/2,0, width/2, height/2)));

  image(Rect(width/2,0,width/2,height/2)).copyTo(troca(Rect(0,height/2, width/2, height/2)));

  image(Rect(width/2,height/2,width/2,height/2)).copyTo(troca(Rect(0,0, width/2, height/2)));

	imwrite("trocatroca.png", troca);
  imshow("image", troca);
  waitKey();
  return 0;
}

