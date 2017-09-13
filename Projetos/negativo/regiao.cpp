#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;

//carregando a imagem

  image= imread("pp.png",CV_LOAD_IMAGE_GRAYSCALE); 
  if(!image.data)
    cout << "nao abriu pp.png" << endl;

//declarando variáveis para inserção dos pontos pelo usuário

	int x1, y1, x2, y2;

//atribuindo valores às variáveis, através do "Do-while" 

	cout << "O tamanho da imagem é: " << image.size().height << "/"<< image.size().width << " Escreva pontos dentro desse limite."<< endl;

	do{ 
		cout << "digite o primeiro ponto (x):" << endl;
		cin >> x1;
		if(x1 >= image.rows || x1 < 0)
			cout << "Número Inválido :). Insira Novamente." << endl;
		}
		while(x1 >=image.rows);

	do{ 
		cout << "digite o primeiro ponto (y):" << endl;
		cin >> y1;
		if(y1 >= image.cols || y1 < 0)
			cout << "Número Inválido :). Insira Novamente." << endl;
		}
		while(y1 >=image.cols);

	do{ 
		cout << "digite o segundo ponto (x):" << endl;
		cin >> x2;
		if(x2 >= image.rows || x2 < 0)
			cout << "Número Inválido :). Insira Novamente." << endl;
		}
		while(x2 >=image.rows);

	do{ 
		cout << "digite o segundo ponto (y):" << endl;
		cin >> y2;
		if(y2 >= image.cols || y2 < 0)
			cout << "Número Inválido :). Insira Novamente." << endl;
		}
		while(y2 >=image.cols);
	
	//aqui utilizou-se um "for" para fazer a iteração e,
	//do ponto inicial informado pelo usuário, até o ponto
	//final, ele irá aplicar o negativo.

  for(int i=x1; i<x2; i++){
    for(int j=y1; j<y2; j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j); //nesta linha ocorre a aplicação do negativo. 
	  												 //"255" menos o valor do pixel alocado.
    }
  }
  
	imwrite("points.png",image);
  imshow("saida", image);  
  waitKey();
  return 0;
}
