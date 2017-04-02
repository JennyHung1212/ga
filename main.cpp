
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;



void original_gene(int** parent_pool, int park_num){
    srand(unsigned(time(NULL)));
    for(int i=0; i<25; i++){
        for(int j=0; j< park_num; j++){
            if(rand()%6 == 0){
                parent_pool[i][j] = 0;
            }else if(rand()%6 == 1){
                parent_pool[i][j] = 1;
            }else if(rand()%6 == 2){
                parent_pool[i][j] = 2;
            }else if(rand()%6 == 3){
                parent_pool[i][j] = 3;
            }else if(rand()%6 == 4){
                parent_pool[i][j] = 4;
            }else if(rand()%6 == 5){
                parent_pool[i][j] = 5;
            }
        }
    }
    for(int i=0; i<25; i++){
        for(int j=0; j<park_num; j++){
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int park_num;
    cout<<"Enter park number:"<<endl;
    cin>>park_num;
    int** parent_pool= new int* [25];
    for(int i=0; i<25; i++){
        parent_pool[i] = new int[park_num];
    }
    original_gene(parent_pool, park_num);
}
//s
