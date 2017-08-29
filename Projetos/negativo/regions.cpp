#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;

  image= imread("pp.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu pp.png" << endl;
  namedWindow("janela",WINDOW_AUTOSIZE);


  for(int i=0; i< image.rows; i++){
    for(int j=0; j< image.cols; j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }
  
	imwrite("negativo.png", image);
  imshow("janela", image);  
  waitKey();
  return 0;
}
