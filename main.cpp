#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

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

int* file1Input(string filePath,int len) {
	fstream file;
	file.open(filePath,ios::in);
	string line;
	int* X = new int[len];
	getline(file,line);
    int x=0;
    int pos=0;
    int found = line.find(',');
    while(found != string::npos) {
    	string sub = line.substr(pos,found-pos);
        X[x] = stoi(sub);
        pos = found + 1;
        found = line.find(",",pos);
        x++;
    }
    X[x] = stoi(line.substr(pos));

    return X;
}

double* file1Input_double(string filePath,int len) {
	fstream file;
	file.open(filePath,ios::in);
	string line;
	double* X = new double[len];
	getline(file,line);
    int x=0;
    int pos=0;
    int found = line.find(',');
    while(found != string::npos) {
    	string sub = line.substr(pos,found-pos);
        X[x] = stod(sub);
        pos = found + 1;
        found = line.find(",",pos);
        x++;
    }
    X[x] = stod(line.substr(pos));

    return X;
}

int** file2Input(string filePath, int yLen, int xLen) {
	fstream file;
	file.open(filePath,ios::in);
	string line;
	int** X = new int*[yLen];
	for(int i=0;i<yLen;i++) {
		X[i] = new int[xLen];
        getline(file,line);
        int x=0;
        int pos=0;
        int found = line.find(',');
        while(found != string::npos) {
        	string sub = line.substr(pos,found-pos);
            X[i][x] = stoi(sub);
            pos = found + 1;
            found = line.find(",",pos);
            x++;
        }
        X[i][x] = stoi(line.substr(pos));
	}
	return X;
}

double*** file3Input(string filePath, int zLen, int yLen,int xLen) {
	fstream file;
	file.open(filePath,ios::in);
	string line;
	double*** X = new double**[zLen];
	for(int i=0;i<zLen;i++) {
		getline(file,line);
		X[i] = new double*[yLen];
		for(int j=0;j<yLen;j++) {
			X[i][j] = new double[xLen];
        	getline(file,line);
        	int x=0;
        	int pos=0;
        	int found = line.find(',');
        	while(found != string::npos) {
        		string sub = line.substr(pos,found-pos);
        	    X[i][j][x] = stod(sub);
        	    pos = found + 1;
        	    found = line.find(",",pos);
        	    x++;
        	}
        	X[i][j][x] = stod(line.substr(pos));
		}
	}
	return X;
}

void print1D(int* X,int x) {
	for(int i=0;i<x;i++) {
		cout << X[i] << " ";
	}
	cout << endl;
}

void print2D(int** X,int y,int x) {
	for(int i=0;i<y;i++) {
		for(int j=0;j<x;j++) {
			cout << X[i][j] << " ";
		}
		cout << endl;
	}
}

void print3D(double*** X,int z,int y,int x) {
	for(int i=0;i<z;i++) {
		for(int j=0;j<y;j++) {
			for (int k = 0; k < x; k++) {
				cout << X[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void parameter() {
	S = file2Input("ga/S_"+to_string(FILE_pos)+".csv",PARK,SCALE);
	T = file2Input("ga/T_"+to_string(FILE_pos)+".csv",PARK,FACILITY);
	f = file2Input("ga/f_"+to_string(FILE_pos)+".csv",PARK,SCALE);
	q = file2Input("ga/q_"+to_string(FILE_pos)+".csv",PARK,SCALE);
	c = file1Input("ga/c_"+to_string(FILE_pos)+".csv",FACILITY);
	k = file1Input_double("ga/k_"+to_string(FILE_pos)+".csv",FACILITY);
	d = file1Input("ga/d_"+to_string(FILE_pos)+".csv",MAN);
	p = file3Input("ga/p_"+to_string(FILE_pos)+".csv",MAN,PARK,FACILITY);
}

class FLSC {

private:

    int manNum;
    int parkNum;
    int facilityNum;
    const int poolLength = 25;
    int** parent_pool;


public:


    FLSC();
    FLSC(int man, int park, int facility);
    void original_gene(int** parent_pool, int parkNum);
    void shuffle (int* x);

};

void FLSC:: original_gene(int** parent_pool, int park_num){
    srand(unsigned(time(NULL)));
    for(int i=0; i<poolLength; i++){
        for(int j=0; j< park_num; j++){
            parent_pool[i][j] = rand()%6;
        }
    }
    for(int i=0; i<poolLength; i++){
        for(int j=0; j<park_num; j++){
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }
}

void FLSC:: shuffle (int* x){

    time_t xx;
    srand((unsigned)time(NULL));
    
    for(int i=0;i<25;i++)
    {
        int n1=rand()%25;
        int n2=rand()%25;
        int temp=x[n1];
        x[n1]=x[n2];
        x[n2]=temp;
    }

}




int main(int argc,char* argv[]) {
	MAN = atoi(argv[1]);
	PARK = atoi(argv[2]);
	FACILITY = atoi(argv[3]);
	
	parameter();
	return 0;
}