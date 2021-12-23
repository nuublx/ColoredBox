#include <iostream>
using namespace std;
#define endl "\n"
//color changing function 
#include <windows.h>
void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
//class 

class ColoredBox
{
private:
	char** Box;
	static long long maxArea;
	long long len = 0, wid = 0;
	char ChBox = '#';
	int Color = 15;
public:
	ColoredBox();
	ColoredBox(long long length, long long width);
	ColoredBox(long long length, long long width, int clr, char FBox);
	void setLength(long long l);
	void setWidth(long long w);
	void setCharBox(char Character);
	void setColor(int clr);
	void display();
	void displayTransposed();
	void displayWider();
	void displayChess(int clr);
	static void setMaxArea(long long);
	long long getArea();
	static long long getMaxArea();
	~ColoredBox();
};

//**********implementation for class ColoredBox**************

  // intial value for maximum area
long long ColoredBox::maxArea = 0;

// implementation for constructors
ColoredBox::ColoredBox()
{
	Box = 0;
}
ColoredBox::ColoredBox(long long length, long long width) :len(length), wid(width)
{
	Box = new char* [len];
	for (int i = 0; i < len; i++) {
		Box[i] = new char[wid];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < wid; j++) {
			Box[i][j] = ChBox;
		}
	}
	setMaxArea(len * wid);
}
ColoredBox::ColoredBox(long long length, long long width, int clr, char FBox) : len(length), wid(width), Color(clr), ChBox(FBox)
{
	Box = new char* [len];
	for (int i = 0; i < len; i++) {
		Box[i] = new char[wid];
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < wid; j++) {
			Box[i][j] = ChBox;
		}
	}
	setMaxArea(len * wid);
}

// implementation for setters
void ColoredBox::setLength(long long l)
{
	len = l;
}
void ColoredBox::setWidth(long long w)
{
	wid = w;
}
void ColoredBox::setCharBox(char Character)
{
	ChBox = Character;
}
void ColoredBox::setColor(int clr)
{
	Color = clr;
}
void ColoredBox::setMaxArea(long long ar)
{
	if (maxArea < ar) {
		maxArea = ar;
	}
}

//implementation for getters
void ColoredBox::display()
{
	SetColor(Color);
	cout << "\n";
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < wid; j++) {
			cout << Box[i][j];
		}
		cout << "\n";
	}
	SetColor(15);
}
void ColoredBox::displayTransposed()
{
	SetColor(Color);
	for (int i = 0; i < wid; i++) {
		for (int j = 0; j < len; j++) {
			cout << Box[j][i];
		}
		cout << "\n";
	}
	SetColor(15);
}
void ColoredBox::displayWider()
{
	SetColor(Color);
	for (int i = 0; i < len; i++) {
		cout << Box[i][0];
		for (int j = 1; j < wid; j++) {
			cout << " " << Box[i][j];
		}
		cout << "\n";
	}
	SetColor(15);
}
void ColoredBox::displayChess(int clr)
{
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < wid; j++) {
			if ((i + j) & 1) {
				SetColor(clr);
				cout << Box[i][j];
			}
			else {
				SetColor(Color);
				cout << Box[i][j];
			}
		}
		cout << "\n";
	}
	SetColor(15);
}
long long ColoredBox::getArea()
{
	setMaxArea(len * wid);
	return len * wid;

}
long long ColoredBox::getMaxArea()
{
	return maxArea;
}

//implementation for destructor
ColoredBox::~ColoredBox()
{
	for (int i = 0; i < len; ++i) {
		delete[] Box[i];
	}
	delete[] Box;
}


// main function
int main() {
	int len, wid, col, col2;
	char boxChar;
	cout << "Enter length and width of the box separated by a space: ";
	cin >> len >> wid;
	ColoredBox* cb1;
	cb1 = new ColoredBox(len, wid);
	cb1->display();
	cout << "Set the box to another color: ";
	cin >> col;
	cb1->setColor(col);
	cout << "Displaying Transposed: " << endl;
	cb1->displayTransposed();
	cout << "Displaying Wider: " << endl;
	cb1->displayWider();
	cout << "Displaying Chess, enter the other color: " << endl;
	cin >> col2;
	cb1->displayChess(col2);
	cout << endl << "Area=" << cb1->getArea();
	cout << endl << "Max Area=" << cb1->getMaxArea();
	delete cb1;

	cout << endl << "Enter length,width,color,character of the box separated by spaces: ";
	cin >> len >> wid >> col >> boxChar;
	ColoredBox* cb2;
	cb2 = new ColoredBox(len, wid, col, boxChar);
	cb2->display();
	cout << "Displaying Transposed: " << endl;
	cb2->displayTransposed();
	cout << "Displaying Wider: " << endl;
	cb2->displayWider();
	cout << "Displaying Chess, enter the other color: " << endl;
	cin >> col2;
	cb2->displayChess(col2);
	cout << "Displaying original again:" << endl;
	cb2->display();
	cout << endl << "Area=" << cb2->getArea();
	cout << endl << "Max Area=" << cb2->getMaxArea();
	delete cb2;
	return 0;
}
