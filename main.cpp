#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "readFile.h"

using namespace std;



class FLSC {

private:

    int parkNum;
    int* parent_pool[][];


public:


    FLSC();
    void original_gene(parkNum);



};

void FLSC:: original_gene(int** parent_pool, int park_num){
    srand(unsigned(time(NULL)));
    for(int i=0; i<25; i++){
        for(int j=0; j< park_num; j++){
            parent_pool[i][j] = rand()%6;
        }
    }
    for(int i=0; i<25; i++){
        for(int j=0; j<park_num; j++){
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }
}




int main(int argc,char* argv[]) {
	MAN = atoi(argv[1]);
	PARK = atoi(argv[2]);
	FACILITY = atoi(argv[3]);
	
	

	parameter();
	return 0;
}