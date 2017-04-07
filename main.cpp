#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//global variable

int FILE_pos = 1;
int MAN;
int PARK;
int FACILITY;
int BUDGET;
int SCALE = 5;


double*** p;
int** S;
int** T;
int** f;
int** q;
int* c;
double* k;
int* d;

int costIteration = 2;
int callIteration = 2;

//-------------------------------------------------------------------------------------------------------
//input function

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

//------------------------------------------------------------------------------------
//class FLSC

const int poolLength =20;

struct chromosome{
    int* scale;
    int** locationFacility;
    int numOfExercise;

    chromosome(){
        scale = new int[SCALE];
        locationFacility = new int*[PARK];
        for(int i = 0; i < PARK; i++){
            scale[i] = 0;
            locationFacility[i] = new int[FACILITY];
            for(int j = 0; j< FACILITY; j++){
                locationFacility[i][j] = 1;
            }
        }
        numOfExercise = 0;
    }

};

bool comparison(const chromosome& a, const chromosome& b){
    return a.numOfExercise < b.numOfExercise;
}


class FLSC {

private:

    int totalBudget;
    int manNum;
    int parkNum;
    int facilityNum;
    int totalCost;
    int** parent_pool;
    int** optimal_facility_area;
	int** kid_pool;
    vector <chromosome> chromosomeArray;

public:

    FLSC();
    FLSC(int man, int park, int facility, int budget);
    void original_gene(int** S);
    void crossover ();
    int** randomZ(int** q, int** T, int num_of_chromosome);
    void display_parent ();
    void display_kid ();
    void display_facility ();
    void display_cost ();
    double fitness(int num_of_chromosome);
    void mutation();
    int cost(int**f, int*c, int** facility_floor_area, int num_of_chromosome);
    void selection();
    void GA();
};

FLSC :: FLSC (int man, int park, int facility, int budget){

    manNum = man;
    parkNum = park;
    facilityNum = facility;
    totalBudget = budget;

    totalCost = 0;

    parent_pool = new int *[poolLength];
    kid_pool = new int* [poolLength*2];

    for (int i = 0; i<poolLength; i++) {
        parent_pool[i] = new int[parkNum];
        for (int j = 0; j < parkNum; j++){
            parent_pool[i][j]=0;
        }
    }

    for (int i = 0; i<poolLength*2; i++) {
        kid_pool[i] = new int[parkNum];
        for (int j = 0; j < parkNum; j++){
            kid_pool[i][j]=0;
        }
    }

    optimal_facility_area = new int *[parkNum];

    for (int i = 0; i< parkNum; i++) {
    	optimal_facility_area[i] = new int[facilityNum];
    }
    for (int i = 0; i< parkNum; i++) {
    	for (int j = 0; j < facilityNum; j++){
    		optimal_facility_area[i][j]=0;
    	}
    }
    for (int i = 0; i < poolLength*2; i++){
        chromosome temp;
        chromosomeArray.push_back(temp);
    }


}


void FLSC :: original_gene(int** S){
	int scale = 0;
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
}


void FLSC :: crossover (){

	for (int i = 0; i < poolLength/2; i++){
        for (int j = 0; j < parkNum/2; j++){
            kid_pool[2*i][j] = parent_pool[2*i][j];
        }
		for (int j = parkNum/2; j < parkNum; j++){
            kid_pool[2*i][j] = parent_pool[2*i+1][j];
        }
    }


    for (int i = 1; i < poolLength/2; i++){
        for (int j = 0; j < poolLength/2; j++){
            kid_pool[2*i-1][j] = parent_pool[2*i-1][j];
        }

        for (int j = parkNum/2; j < parkNum; j++){
            kid_pool[2*i-1][j] = parent_pool[2*i-2][j];
        }
        
    }

    for (int i = 0; i < parkNum; i++){       
        kid_pool[poolLength-1][i] = parent_pool[poolLength-1][i];
    }

    for (int i = parkNum/2; i < parkNum; i++){       
        kid_pool[poolLength-1][i]=parent_pool[poolLength-2][i];
    }

    for (int i = poolLength ; i < 2*poolLength; i++)
    {
        for (int j = 0; j < parkNum; j++)
        {
            kid_pool[i][j] = parent_pool[i-poolLength][j];
        }
    }

}

int** FLSC :: randomZ(int** q, int** T, int num_of_chromosome){

	int js_area = 0;	
	int is_zero = 0;
    
    int** facility_floor_area = new int *[parkNum];

    for (int i = 0; i< parkNum; i++) {
        facility_floor_area[i] = new int[facilityNum];
        for (int j = 0; j < facilityNum; j++){
            facility_floor_area[i][j]=0;
        }        
    }


	for(int i = 0; i < PARK; i++){

		if(kid_pool[num_of_chromosome][i] != 0){
			js_area = q[i][kid_pool[num_of_chromosome][i]-1];
			is_zero = 0;
		}else{
			is_zero = 1;
			js_area = 0;
		}

		while(1){
					
			for(int j = 0; j < FACILITY; j++){
				if(js_area != 0 && T[i][j] != 0){
					if(is_zero == 0){
						
						facility_floor_area[i][j] = rand() % js_area;
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
			if(sum < js_area){
				break;
			}
			
		}

	}
	return facility_floor_area;

}


int FLSC :: cost(int**f, int*c, int** facility_floor_area, int num_of_chromosome){
	int f_cost = 0;
	int c_cost = 0;
    int total_cost = 0;

	for(int i = 0; i < PARK; i++){
		if(kid_pool[num_of_chromosome][i] != 0){
			f_cost += f[i][kid_pool[num_of_chromosome][i]-1];
		}

	}
	for(int i = 0; i < PARK; i++){
		for(int j = 0; j < FACILITY; j++){
			c_cost += c[j] * facility_floor_area[i][j];
		}
	}

	total_cost = f_cost + c_cost;
	return total_cost;
}


double FLSC :: fitness(int num_of_chromosome){
   
    bool the_same ;
    int equalCount;
    int index;
    for(int i = 0; i < poolLength; i++){
        equalCount = 10;
        the_same = 0;
        cout<<"lala\n";
        for(int j = 0; j< parkNum; j++){
            cout<<"*"<<kid_pool[num_of_chromosome][j]<<" "; 

            cout<<"#"<<chromosomeArray[i].scale[j]<<" ";
        }
        for (int j = 0; j < parkNum; j++){

            if(chromosomeArray[i].scale[j] != kid_pool[num_of_chromosome][j]){
                equalCount--;
                cout<<equalCount<<"~~"<<endl;
                break;     
            }
                    
           
        }  
        cout<<endl;
        if (equalCount == parkNum){
            the_same=1;
            index=i;
            break;
        }

    }

    if(the_same == 1){
        cout<<"SAME!!!!!"<<endl;
        return chromosomeArray[index].numOfExercise;
    }
    else{

        int** availableDistribution = new int* [parkNum];
        int** ff_area = new int* [parkNum];
        int*** exerciseLocation = new int** [manNum]; 
        int* currentElders = new int[manNum];
        double tempMax;
        pair < double, pair<int, int> > pairPreference;
        vector < vector <pair < double, pair<int, int> > > > vectorPreference(parkNum);

        for (int i = 0; i< manNum; i++){
            currentElders[i] = d[i];
            exerciseLocation[i] = new int*[parkNum];
            for(int j = 0; j< parkNum; j++){
                exerciseLocation[i][j] = new int[facilityNum];
                for (int k = 0; k < facilityNum; k++){
                    exerciseLocation[i][j][k] = 0;
                }
            }

        }

        for (int i = 0; i< parkNum; i++) {
            ff_area[i] = new int[facilityNum];
            availableDistribution[i] = new int[facilityNum];
            
        }
        for (int i = 0; i< parkNum; i++) {
            for (int j = 0; j < facilityNum; j++){
                ff_area[i][j]=0;
            }
        }



        for(int i = 0; i < costIteration; i++){

            tempMax=0;
            double tempPeople=0;
            ff_area = randomZ(q, T, num_of_chromosome);
            while(cost(f, c, ff_area, num_of_chromosome) > totalBudget){
                ff_area = randomZ(q, T, num_of_chromosome);
            }
            for (int i = 0; i< parkNum; i++) {
                for (int j = 0; j < facilityNum; j++){
                    availableDistribution[i][j]= ff_area[i][j]*k[j];
                }
                cout<<endl;
            }


            while(1){
                bool negative = 1;
                for(int i = 0; i < manNum; i++){
                    for(int j = 0; j < parkNum; j++){
                        for(int k = 0; k < facilityNum; k++){
                            pairPreference.first=p[i][j][k];
                            pairPreference.second.first=j;
                            pairPreference.second.second=k;
                            vectorPreference[j].push_back(pairPreference);
                        }
                    }

                    priority_queue < pair < double, pair<int, int> > > queuePreference;

                    for(int j = 0; j < parkNum; j++){
                        for(int k = 0; k < facilityNum; k++){
                            queuePreference.push(vectorPreference[j][k]);
                        }
                    }


                    while(availableDistribution[queuePreference.top().second.first][queuePreference.top().second.second]==0 && !queuePreference.empty()){
                        p[i][queuePreference.top().second.first][queuePreference.top().second.second]= -1;
                        queuePreference.pop();

                    }

                    if(currentElders[i] <= availableDistribution [queuePreference.top().second.first][queuePreference.top().second.second] ){

                        exerciseLocation[i][queuePreference.top().second.first][queuePreference.top().second.second] += currentElders[i];
                        availableDistribution [queuePreference.top().second.first][queuePreference.top().second.second] -= currentElders[i];
                        currentElders[i]=0;
                        p[i][queuePreference.top().second.first][queuePreference.top().second.second]= -1;
                    }else{

                        currentElders[i] -=  availableDistribution [queuePreference.top().second.first][queuePreference.top().second.second];
                        exerciseLocation[i][queuePreference.top().second.first][queuePreference.top().second.second] += 
                            availableDistribution [queuePreference.top().second.first][queuePreference.top().second.second];
                        availableDistribution [queuePreference.top().second.first][queuePreference.top().second.second]=0;
                        p[i][queuePreference.top().second.first][queuePreference.top().second.second]= -1;
                    }
                                   
                }

                for(int i = 0; i < manNum; i++){
                    for(int j = 0; j < parkNum; j++){
                        for(int k = 0; k < facilityNum; k++){
                            if(p[i][j][k] != -1){
                                negative = 0;
                            }
                        }
                    }
                }

                if(negative == 1){
                    cout<<"NNNNNNN";
                    break;
                }

            }
            
            for(int i = 0; i < manNum; i++){
                for(int j = 0; j < parkNum; j++){
                    for(int k = 0; k < facilityNum; k++){
                        tempPeople += exerciseLocation[i][j][k];
                    }
                }
            }

            if (tempPeople>=tempMax){
                cout<<"~~~~~~~~~~~";
                tempMax = tempPeople;
                optimal_facility_area = ff_area;   
            }

        } 

        cout<<"$$$$$$$$$$$$$\n";
        chromosome tempChromosome;
        //tempChromosome.scale = kid_pool[num_of_chromosome];
        tempChromosome.numOfExercise = tempMax;

        for(int i = 0; i < parkNum; i++){
            tempChromosome.scale[i] = kid_pool[num_of_chromosome][i];
        }
        for(int i = 0; i < parkNum; i++){
            
            for(int j = 0; j < facilityNum; j++){
                cout<<optimal_facility_area[i][j]<<" ";
                //tempChromosome.locationFacility[i][j] = optimal_facility_area[i][j];
            }
            cout<< endl;
        }

        //tempChromosome.locationFacility = optimal_facility_area;


        //chromosomeArray.push_back(tempChromosome);
            

        return tempMax;

    }

}




void FLSC :: selection(){

    vector < pair <double, int> > vector_result;
    pair < double, int > result;

    for(int i = 0; i<poolLength*2; i++){
        result.first = fitness(i);
        cout<<"fit!\n";
        result.second = i;
        vector_result.push_back(result);
    }

    priority_queue < pair <double, int> > select;

    for(int i = 0; i < poolLength*2; i++){
        select.push(vector_result[i]);
    }

    for(int i = 0; i < poolLength; i++){
        parent_pool[i] = kid_pool[select.top().second];
        select.pop(); 
    }
    sort(chromosomeArray.begin(), chromosomeArray.end(), comparison);
    for(int i = 0; i < poolLength; i++){
        chromosomeArray.pop_back();
    }

    cout<<"Selection!~!\n";

}

void FLSC :: mutation(){

    const int mutationPosibility = 100;

    for (int i = 0; i < poolLength; i++){
        int r = rand()%mutationPosibility;
        if(r == 0) {
            int pos = rand()%parkNum;
            int changedNum = rand()%6;
            kid_pool[i][pos] = changedNum;
        }
    }
}

void FLSC :: display_parent(){

	cout<<"\nparent_pool~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(int i=0; i<poolLength; i++){
        for(int j=0; j<parkNum; j++){
            cout<<parent_pool[i][j]<<" ";
        }
        cout<<endl;
    }	

}

void FLSC :: display_kid(){

    cout<<"\nkid_pool~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < parkNum; j++){
            cout<<kid_pool[i][j]<<" ";
        }
        cout<<endl;
    }


}

void FLSC :: display_cost(){

    cout<<"\ntotalCost~~~~~~~~~~~~~~~~\n";
    cout<<"$"<<totalCost<<endl;

}

void FLSC :: GA(){

    original_gene(S);

    while(callIteration>1){
        crossover();
        mutation();
        cout<<"yoooo\n";
        selection();
        callIteration--;
    }

    cout<<"Max~~~~~~~~~~~~\n";
    cout<<chromosomeArray[0].numOfExercise<<endl;

    cout<<"y~~~~~~~~~~~~\n";
    for (int i = 0; i < parkNum; i++)
    {
        cout<<chromosomeArray[0].scale[i]<<" ";
    }
    cout<<endl;

    cout<<"Z~~~~~~~~~~~\n";
    for (int i = 0; i < parkNum; i++){
        for (int j = 0; j < facilityNum; j++){
            cout<<chromosomeArray[0].locationFacility[i][j]<<" ";
        }
        cout<<endl;
    }

}


//-------------------------------------------------------------------
//main function

int main(int argc,char* argv[]) {
	MAN = atoi(argv[1]);
	PARK = atoi(argv[2]);
	FACILITY = atoi(argv[3]);
    BUDGET = atoi(argv[4]);

	
    FLSC test(MAN,PARK,FACILITY,BUDGET);
    parameter();

    test.GA();
    //test.original_gene(S);
    // test.randomZ(q, T, 0);
    //test.crossover();
    // //test.cost(f, c, 0);
   // test.selection();

    // test.display_cost();
    // //test.display_facility();
    // test.display_kid();
    // test.display_parent();



	return 0;
}