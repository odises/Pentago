typedef struct cameras {
	float pos[3];
	float lookAt[3];
	float lookUp[3];
} camera;


static int border = 6,h=300,w=450;

struct status
{
	int turn;
	bool firstMove;
	int firstMovePart;
	int firstMoveIndex;
	bool secondMove;
	int secondMovePart;
	int secondMoveIndex;
	bool moving;
	bool endMoving;
	bool choosed;
	int narrow;
	bool winner;
};

// callback to initialize the scenes for each subwindow
void initScene(int argc, char **argv);

void init(camera *cam);

// callback for quiting
void quit();

void denoteSelectedSlice(status stats);

void denoteTurn(status stats);

//----------------------
// Resizing
//----------------------
void changeSize(int w1, int h1);

