#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>

#include <cmath>
using namespace std;

class Image
{
	  public:
			 Image();
			 Image(int numRows, int numCols, int grayLevels);
			 ~Image();
			 Image(const Image& oldImage);
			 void operator=(const Image&);
			 void setImageInfo(int numRows, int numCols, int maxVal);
			 void getImageInfo(int &numRows, int &numCols, int &maxVal);
			 int getPixelVal(int row, int col);
			 void setPixelVal(int row, int col, int value);
			 bool inBounds(int row, int col);
			 void getSubImage(int upperLeftRow, int upperLeftCol, 
				int lowerRightRow, int lowerRightCol, Image& oldImage);
			 int meanGray();
			 // void enlargeImage(int value, Image& oldImage);
			 // void shrinkImage(int value, Image& oldImage);
			 // void reflectImage(bool flag, Image& oldImage);
			 // void translateImage(int value, Image& oldImage);
				//   /*
				// 	r' = r + t
				// 	c' = c + t
				//   */
			 // void rotateImage(int theta, Image& oldImage);
			 // Image operator+(const Image &oldImage);
			 // Image operator-(const Image& oldImage);
			 void negateImage(Image& oldImage);
	  private:
			  int N; // number of rows
			  int M; // number of columns
			  int Q; // number of gray levels
			  int **pixelVal;
};

Image::Image()
/* Creates an Image 0x0 */
{
	N = 0;
	M = 0;
	Q = 0;
	
	pixelVal = NULL;
}

Image::Image(int numRows, int numCols, int grayLevels)
/* Creates an Image of numRows x numCols and creates the arrays for it*/
{    
	
	N = numRows;
	M = numCols;
	Q = grayLevels;
	
	pixelVal = new int *[N];
	for(int i = 0; i < N; i++)
	{
		pixelVal[i] = new int [M];
		for(int j = 0; j < M; j++)
			pixelVal[i][j] = 0;
	}
}

Image::~Image()
/*destroy image*/
{
	N = 0;
	M = 0;
	Q = 0;
	
	for(int i = 0; i < N; i++)
		delete pixelVal [N];
	
	delete pixelVal;
}

Image::Image(const Image& oldImage)
/*copies oldImage into new Image object*/
{    
	N = oldImage.N;
	M = oldImage.M;
	Q = oldImage.Q;
	
	pixelVal = new int* [N];
	for(int i = 0; i < N; i++)
	{
		pixelVal[i] = new int [M];
		for(int j = 0; j < M; j++)
			pixelVal[i][j] = oldImage.pixelVal[i][j];
	}
}

void Image::operator=(const Image& oldImage)
/*copies oldImage into whatever you = it to*/
{
	N = oldImage.N;
	M = oldImage.M;
	Q = oldImage.Q;
	
	pixelVal = new int* [N];
	for(int i = 0; i < N; i++)
	{
		pixelVal[i] = new int [M];
		for(int j = 0; j < M; j++)
			pixelVal[i][j] = oldImage.pixelVal[i][j];
	}
}

void Image::setImageInfo(int numRows, int numCols, int maxVal)
/*sets the number of rows, columns and graylevels*/
{
	N = numRows;
	M = numCols;
	Q = maxVal;
}

void Image::getImageInfo(int &numRows, int &numCols, int &maxVal)
/*returns the number of rows, columns and gray levels*/
{
	numRows = N;
	numCols = M;
	maxVal = Q;
}

int Image::getPixelVal(int row, int col)
/*returns the gray value of a specific pixel*/
{
	return pixelVal[row][col];
}


void Image::setPixelVal(int row, int col, int value)
/*sets the gray value of a specific pixel*/
{
	pixelVal[row][col] = value;
}

bool Image::inBounds(int row, int col)
/*checks to see if a pixel is within the image, returns true or false*/
{
	if(row >= N || row < 0 || col >=M || col < 0)
		return false;
	//else
	return true;
}

void Image::getSubImage(int upperLeftRow, int upperLeftCol, int lowerRightRow, 
	int lowerRightCol, Image& oldImage)
/*Pulls a sub image out of oldImage based on users values, and then stores it
	in oldImage*/
{
	int width, height;
	
	width = lowerRightCol - upperLeftCol;
	height = lowerRightRow - upperLeftRow;
	
	Image tempImage(height, width, Q);
	
	for(int i = upperLeftRow; i < lowerRightRow; i++)
	{
		for(int j = upperLeftCol; j < lowerRightCol; j++)
			tempImage.pixelVal[i - upperLeftRow][j - upperLeftCol] = oldImage.pixelVal[i][j];
	}
	
	oldImage = tempImage;
}

int Image::meanGray()
/*returns the mean gray levels of the Image*/
{
	int totalGray = 0;
	
	for(int i = 0; i < N; i ++)
	{
		for(int j = 0; j < M; j++)
			totalGray += pixelVal[i][j];
	}
	
	int cells = M * N;
	
	return (totalGray / cells);
}

void Image::negateImage(Image& oldImage)
/*negates image*/
{
	int rows, cols, gray;
	rows = N;
	cols = M;
	gray = Q;
	
	Image tempImage(N,M,Q);
	
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
			tempImage.pixelVal[i][j] = -(pixelVal[i][j]) + 255;
	}
	
	oldImage = tempImage;
}

int readImageHeader(char[], int&, int&, int&, bool&);
int readImage(char[], Image&);
int writeImage(char[], Image&);

int main(int argc, char *argv[])
{
	int M, N, Q; // rows, cols, grayscale
	//int val;
	bool type;
	//int mean;
	int choice = 1;
	int value = 0;
	//bool able;
	int flipChoice = 0;
	//bool flag;
	int translate = 0;
	int rotate = -1;
	//int subULR, subULC, subLRR, subLRC;
	//int r, c;

	// read image header
	readImageHeader("img.pgm", N, M, Q, type);

	// allocate memory for the image array
	Image image(N, M, Q);

	//Image outImage();
	Image tempImage(image);
	Image secImage(image);

	// read image
	readImage("img.pgm", image);
	
	//print menu until user quits
	image.negateImage(image);
	writeImage("img2.pgm", image);

	return 0;
}

int readImage(char fname[], Image& image)
{
	int i, j;
	int N, M, Q;
	unsigned char *charImage;
	char header [100], *ptr;
	ifstream ifp;

	ifp.open(fname, ios::in | ios::binary);

	cout << "works\n";

	if (!ifp) 
	{
		cout << "Can't read image: " << fname << endl;
		exit(1);
	}

	cout << "works\n";

 	//read header

	ifp.getline(header,100,'\n');
	if ( (header[0]!=80) || (header[1]!=53) ) 
	{   
		cout << "Image " << fname << " is not PGM" << endl;
		exit(1);
	}

	ifp.getline(header,100,'\n');
	while(header[0]=='#')
		ifp.getline(header,100,'\n');

	M=strtol(header,&ptr,0);
	N=atoi(ptr);

	ifp.getline(header,100,'\n');
	Q=strtol(header,&ptr,0);

	charImage = (unsigned char *) new unsigned char [M*N];

	ifp.read( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

	if (ifp.fail()) 
	{
		cout << "Image " << fname << " has wrong size" << endl;
		exit(1);
	}

	ifp.close();

 //
 // Convert the unsigned characters to integers
 //

	int val;

	for(i=0; i<N; i++)
		for(j=0; j<M; j++) 
		{
			val = (int)charImage[i*M+j];
			image.setPixelVal(i, j, val);     
		}

	delete [] charImage;


	return (1);

}

int readImageHeader(char fname[], int& N, int& M, int& Q, bool& type)
{
	int i, j;
	unsigned char *charImage;
	char header [100], *ptr;
	ifstream ifp;

	ifp.open(fname, ios::in | ios::binary);

	cout << "works\n";

	if (!ifp) 
	{
		cout << "Can't read image: " << fname << endl;
		exit(1);
	}

	cout << "works\n";

 // read header

	type = false; // PGM

	ifp.getline(header,100,'\n');
	if ( (header[0] == 80) && (header[1]== 53) ) 
	{  
	  type = false;
	}
	else if ( (header[0] == 80) && (header[1] == 54) ) 
	{       
	  type = true;
	} 
	else 
	{
		cout << "Image " << fname << " is not PGM or PPM" << endl;
		exit(1);
	}

	ifp.getline(header,100,'\n');
	while(header[0]=='#')
		ifp.getline(header,100,'\n');

	M=strtol(header,&ptr,0);
	N=atoi(ptr);

	ifp.getline(header,100,'\n');

	Q=strtol(header,&ptr,0);

	ifp.close();

	return(1);
}

int writeImage(char fname[], Image& image)
{
	int i, j;
	int N, M, Q;
	unsigned char *charImage;
	ofstream ofp;

	image.getImageInfo(N, M, Q);

	charImage = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

	int val;

	for(i=0; i<N; i++)
	{
		for(j=0; j<M; j++) 
		{
		val = image.getPixelVal(i, j);
		charImage[i*M+j]=(unsigned char)val;
		}
	}

	ofp.open(fname, ios::out | ios::binary);

	if (!ofp) 
	{
		cout << "Can't open file: " << fname << endl;
		exit(1);
	}

	ofp << "P5" << endl;
	ofp << M << " " << N << endl;
	ofp << Q << endl;

	ofp.write( reinterpret_cast<char *>(charImage), (M*N)*sizeof(unsigned char));

	if (ofp.fail()) 
	{
		cout << "Can't write image " << fname << endl;
		exit(0);
	}

	ofp.close();

	delete [] charImage;

	return(1);

}
