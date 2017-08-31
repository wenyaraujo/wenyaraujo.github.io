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

	int x1, y1, x2, y2;

		do{ 
			cout << "digite o primeiro ponto (x):" << endl;
			cin >> x1;
			}
			while(x1 >=image.rows);

		do{ 
			cout << "digite o primeiro ponto (y):" << endl;
			cin >> y1;
			}
			while(y1 >=image.cols);

		do{ 
			cout << "digite o segundo ponto (x):" << endl;
			cin >> x2;
			}
			while(x2 >=image.rows);

		do{ 
			cout << "digite o segundo ponto (y):" << endl;
			cin >> y2;
			}
			while(y2 >=image.cols);
	
  for(int i=x1; i<x2; i++){
    for(int j=y1; j<y2; j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }
  
	imwrite("points.png",image);
  imshow("saida", image);  
  waitKey();
  return 0;
}
