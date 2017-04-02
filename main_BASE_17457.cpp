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
    void crossover (int** parent_pool);

};

FLSC :: FLSC (int man, int park, int facility){

    manNum = man;
    parkNum = park;
    facilityNum = facility;

    parent_pool = new int *[75];

    for (int i = 0; i<75; i++) {
        parent_pool[i] = new bool[parkNum];
    }

}


void FLSC :: original_gene(int** parent_pool, int park_num){
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

void FLSC :: crossover (int** crossover){

    int randomIndex [poolLength] = {0};

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
                    parent_pool[k+poolLength][j]=parent_pool[randomIndex[k]][j]
                }
            }

            if (i==1)
            {

                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+poolLength][j+(parkNum/2)]=parent_pool[randomIndex[k]][j+(parkNum/2)]
                }    
            }

            if (i==2)
            {
                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+2*poolLength][j]=parent_pool[randomIndex[k]][j]
                }
            }

            else
            {
                for (int k = 0; k < poolLength; k++)
                {
                    parent_pool[k+2*poolLength][j+(parkNum/2)]=parent_pool[randomIndex[k]][j+(parkNum/2)]
                }

            }
        }
    }

}






int main(int argc,char* argv[]) {
	MAN = atoi(argv[1]);
	PARK = atoi(argv[2]);
	FACILITY = atoi(argv[3]);
	
	

	parameter();
	return 0;
}