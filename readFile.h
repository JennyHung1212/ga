int FILE_pos = 1;
int MAN;
int PARK;
int FACILITY;
int SCALE = 5;

double*** p;
int** S;
int** T;
int** f;
int** q;
int* c;
double* k;
int* d;

int* file1Input(std::string filePath,int len);
double* file1Input_double(std::string filePath,int len);
int** file2Input(std::string filePath, int yLen, int xLen);
double*** file3Input(std::string filePath, int zLen, int yLen,int xLen);
void print1D(int* X,int x);
void print2D(int** X,int y,int x);
void print3D(double*** X,int z,int y,int x);
void parameter();
