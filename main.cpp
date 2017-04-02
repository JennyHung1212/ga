#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
using namespace std;

/* global variable*/
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


const int poolLength =20;
class FLSC {

private:

    int manNum;
    int parkNum;
    int facilityNum;
    int** parent_pool;
    int** facility_floor_area;


public:


    FLSC();
    FLSC(int man, int park, int facility);
    void original_gene(int** S);
    void shuffle (int* x);
    void crossover ();
    int** randomZ(int** q, int** T, int num);
    void display ();

    double fitness();

};

FLSC :: FLSC (int man, int park, int facility){

    //poolLength=20;
    manNum = man;
    parkNum = park;
    facilityNum = facility;

    parent_pool = new int *[75];

    for (int i = 0; i<75; i++) {
        parent_pool[i] = new int[parkNum];
    }

     for (int i = 0; i < 75; i++)
    {
        for (int j = 0; j < parkNum; j++)
        {
            parent_pool[i][j]=0;
        }
    }

    facility_floor_area = new int *[parkNum];
    for (int i = 0; i< parkNum; i++) {
    	facility_floor_area[i] = new int[facilityNum];
    }
    for (int i = 0; i< parkNum; i++) {
    	for (int j = 0; j < facilityNum; j++){
    		facility_floor_area[i][j]=0;
    	}
    }


}


void FLSC :: original_gene(int** S){
	int scale = 0;
    srand(unsigned(time(NULL)));
    for(int i=0; i<poolLength; i++){
        for(int j=0; j< parkNum; j++){
        	while(1){
		    	scale = rand()%6;
		    	if(scale != 0 && S[j][scale-1] == 1){
		    		parent_pool[i][j] = scale;
		    		break;
		    	}else if(scale == 0){
		    		parent_pool[i][j] = 0;
		    		break;
		    	}        		
        	}          
        }
    }

    for(int i=0; i<poolLength; i++){
        for(int j=0; j<parkNum; j++){
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }
}

void FLSC :: shuffle (int* x){

    time_t xx;
    srand((unsigned)time(NULL));
    
    for(int i=0;i<poolLength;i++)
    {
        int n1=rand()%25;
        int n2=rand()%25;
        int temp=x[n1];
        x[n1]=x[n2];
        x[n2]=temp;
    }

}

void FLSC :: crossover (){

    int randomIndex [poolLength];

    for (int i = 0; i < poolLength; i++)
    {
        randomIndex [i] = 0;
    }

    for (int i = 0; i < poolLength ; i++)
    {
        randomIndex[i]=i;
    }

    for (int i = 0; i < 4 ; i++)
    {
        shuffle(randomIndex);

        for (int j = 0; j < parkNum/2 ; j++)
        {
            if (i==0)
            {
                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+poolLength][j]=parent_pool[randomIndex[k]][j];
                }
            }

            if (i==1)
            {

                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+poolLength][j+(parkNum/2)]=parent_pool[randomIndex[k]][j+(parkNum/2)];
                }    
            }

            if (i==2)
            {
                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+2*poolLength][j]=parent_pool[randomIndex[k]][j];
                }
            }
            else
            {
                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+2*poolLength][j+(parkNum/2)]=parent_pool[randomIndex[k]][j+(parkNum/2)];
                }

            }
        }
    }

}


int** FLSC :: randomZ(int** q, int** T, int num){
	int denominator = 0;	
	int is_zero = 0;
	time_t xx;
	srand((unsigned)time(NULL));
	for(int i = 0; i < PARK; i++){

		if(parent_pool[num][i] != 0){
			denominator = q[i][parent_pool[num][i]-1];
			is_zero = 0;
		}else{
			is_zero = 1;
			denominator = 0;
		}
		
		//cout<<"DENOMINATOR: "<<denominator<<endl;
		//cout<<"IS_ZERO: "<<is_zero<<endl;

		while(1){
					
			for(int j = 0; j < FACILITY; j++){
				if(denominator != 0 && T[i][j] != 0){
					if(is_zero == 0){
						
						facility_floor_area[i][j] = rand()%denominator;
					}else{
						facility_floor_area[i][j] = 0;
					}
					
				}else{
					facility_floor_area[i][j] = 0;
				}				
			}
			int sum = 0;
			if(is_zero == 1){
				break;
			}else{
				for(int j =0; j<FACILITY; j++){
					sum = sum + facility_floor_area[i][j];
				}
			}
			if(sum < denominator){
				break;
			}
			
		}

	}
	return facility_floor_area;
	/*for(int i = 0; i < PARK; i++){
		for(int j = 0; j < FACILITY; j++){
			cout<<facility_floor_area[i][j]<<" ";
		}
		cout<<endl;
	}*/
}

void FLSC :: display(){

    cout<<"Crossover~~~~~~~~\n";
    for (int i = 0; i < 75; i++)
    {
        for (int j = 0; j < parkNum; j++)
        {
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }

}

double FLSC :: fitness(){

    


    
}


int main(int argc,char* argv[]) {
	MAN = atoi(argv[1]);
	PARK = atoi(argv[2]);
	FACILITY = atoi(argv[3]);
	
    FLSC test(MAN,PARK,FACILITY);
    parameter();
    test.original_gene(S);

    //cout<<"randomZ~~~~~~~"<<endl;
    /*for(int i=0; i<PARK; i++){
    	for(int j=0; j<5; j++){
    		cout<<q[i][j]<<" ";
    	}
    	cout<<endl;
    }*/
    test.randomZ(q, T, 1);
    // test.display();
    //test.crossover();
    //test.display();
	// parameter();


	return 0;
}