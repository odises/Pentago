class slice
{
	private:
		GLfloat angel;
		GLfloat y_transfer;
		GLfloat z_rotate;
		//int part;
		int cw;
		//int ccw;
		int rotateStatus;
		int transferStatus;
		//-------------------
		int elements[9];

	public:
		slice();
		//slice(int);
		//void setPartNumber(int);
		void draw();
		bool rotateCw(GLfloat upperbound, GLfloat increament);
		bool rotateCcw(GLfloat upperbound, GLfloat increament);
		GLfloat yTransfer();
		GLfloat zRotate();
		int getValues(int index);
		void setValues(int index, int value);
		bool isFilled(int index);
		bool isFullyFilled();
		
};

class board
{
private:
	slice p1, p2, p3, p4;
	int s[18][6];
public:
	board();
	void setParts(int part, int index, int value);
	void load();
	int max_series(int x[], int number);
	bool isFullyFilled();
	bool isAccessible(int part, int index);
	int winner();
	void draw();
	bool cw(int part);
	bool ccw(int part);
};