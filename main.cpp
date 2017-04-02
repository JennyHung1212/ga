
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
            }else if(rand()%5 == 1){
                parent_pool[i][j] = 1;
            }else if(rand()%5 == 2){
                parent_pool[i][j] = 2;
            }else if(rand()%5 == 3){
                parent_pool[i][j] = 3;
            }else if(rand()%5 == 4){
                parent_pool[i][j] = 4;
            }
        }
    }
}
