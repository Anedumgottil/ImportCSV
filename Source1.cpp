/*
Author: Anthony Nedumgottil - anedum2@uic.edu
Part of this code was taken from http://forums.codeguru.com/showthread.php?396459-Reading-CSV-file-into-an-array
More documentation on vectors can be found here http://www.cplusplus.com/reference/vector/vector/

---------------------------------STUFF TO DO---------------------------------

*/
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <climits>

#define V 9
using namespace std;
/*
changeMatrix: Changes the matrix depending if the county is within a certain % of eachother
The value of the matrix will be changed to 1 if the boolean is true and it will remain a 0 if it is false
*/
void changeMatrix(int** &matrix, bool did_change, int county1, int county2){

	if (did_change == true){
		if (county1 != county2){
			matrix[county2][county1] = 1;
			matrix[county1][county2] = 1;
			//cout << county1 << " " << county2<<endl;
		}
//		else
//			matrix[county2][county1] = 0;
	}
//	if (did_change == false)
//		matrix[county2][county1] = 0;
/*
	if ((did_change && (county1 != county2))){
		matrix[county2][county1] = 0;
		matrix[county1][county2] = 1;
	}
	else
		matrix[county2][county1] = 0;
*/
}
/*
computeAverage: computes the average of the data by adding all the values within the vector
and dividing it by the total number of values in the vector
*/
double computeAverage(vector<double> data){
	double average = 0;

	average = (accumulate(data.begin(), data.end(), 0) / data.size());

	return average;
}
/*
changeValue: determines if the two counties are withing a certain % of eachother and returns a true if they are
and a flase if they are not.
Alpha is the average of the entire data
(1+i) * alpha
*/
bool changeValue(double county1, double county2, double alpha, double i){

	if ((county1 * (0.99) <= county2) && (county2 <= county1 * (1.01))){
		//if (county2 < county1 + (1.01)){
			return true;
		//}
	//	else
	//		return false;
	}
	else
		return false;
}
/*
displayBool: displays the boolean as a string True and False rather than a 1 or 0
*/
void displayBool(bool value){
	if (value)
		cout << "True" << endl;
	else
		cout << "False" << endl;
}
/*
displaysMatrix: displays the content inside of the 2d array named matrix

*/
void displayMatrix(int** matrix, int num_of_entities){

	for (int i = 0; i < num_of_entities; i++){
		for (int j = 0; j < num_of_entities; j++){
			cout << matrix[i][j] << "\t ";
		}
		cout << endl;
	}
}

/*
calculateDegree: Calculates the degree
*/
void calculateDegree(int** matrix, vector<int> &degree, int num_of_entities){
	int sum = 0;

	for (int i = 0; i < num_of_entities; i++){
		for (int j = 0; j < num_of_entities; j++){
			sum = sum + matrix[i][j];
		}
		degree.push_back(sum);
		sum = 0;
	}
}

int minDistance(int dist[], bool sptSet[], int num_of_entities)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < num_of_entities; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int num_of_entities)
{
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < num_of_entities; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int** matrix, int src, int num_of_entities)
{
	int dist[num_of_entities];     // The output array.  dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[num_of_entities]; // sptSet[i] will true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < num_of_entities; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < num_of_entities - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < num_of_entities; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist, num_of_entities);
}

int main(){
	string line, field, input_name, input_name_with_extention, output_name;
	vector< vector<string> > array;  // The 2D array
	vector<string> v, header;         // vector v : Array of values for one line only
	vector<double> num_values;
	vector<int> d;
	vector<vector<int>> degree;
	double average, degreeChange, degreeStart, degreeEnd;
	int num_of_entities;
	bool did_change=true;

	input_name = "2005";
	input_name_with_extention = input_name + string(".csv");
	output_name = input_name + string("_Output2.csv");

	ifstream in(input_name_with_extention);

	while (getline(in, line))    // Get next line in file
	{
		v.clear();			// Clears the vector
		stringstream ss(line);

		while (getline(ss, field, ','))  //	Break line  into comma delimitted fields
		{
			v.push_back(field);  //	Add each field to the 1D array
		}
		array.push_back(v);  //	Add the 1D array to the 2D array
	}

	//	Stores the numbers of size of the array into an int
	num_of_entities = (short)array.size();
	//	Creates a 2d array that has the size of the array
	int** matrix = new int*[num_of_entities];

	for (int i = 0; i < num_of_entities; i++){
		matrix[i] = new int[num_of_entities];
	}
	/*
	//	Prints out what was read in
	for (unsigned int i = 0; i<array.size(); i++){
		for (unsigned int j = 0; j<array[i].size(); j++){
			cout << array[i][j] << " "; // (separate fields by " ")
		}
		cout << endl;
	}
	*/
	cout << "Reading file : " << input_name_with_extention << endl;

	cout << "1)--------------------------------" << endl;
	//	Sets all the values in the matrix to 0
	cout << "Setting all the matrix values to 0" << endl;
	for (int a = 0; a < num_of_entities; a++){
		for (int b = 0; b < num_of_entities; b++){
			matrix[a][b] = 0;
		}
	}
	cout << "2)--------------------------------" << endl;

	// Converts the data value from each country and stores it in a seperate vector
	for (int i = 0; i < num_of_entities; i++){
		num_values.push_back(stod(array[i][1]));
	}

	// Computes and displays the average of the countries
	average = computeAverage(num_values);

	cout << "Average is " << average << "." << endl;

	cout << "The size of the array is: " << array.size() << "." << endl;

	cout << "3)--------------------------------" << endl;

	//Values for the starting and ending degree
	degreeChange = 0.01;
	degreeStart = 0.01;
	degreeEnd = 0.01;


	cout << "Changing the matrix and caculating the degrees." << endl;
	while (degreeStart <= degreeEnd){

		for (int i = 0; i< num_of_entities; i++){
			for (int j = 0; j < num_of_entities; j++){
				did_change = changeValue(num_values[i], num_values[j], average, degreeStart);
				changeMatrix(matrix, did_change, i, j);
				//displayBool(did_change);
			}
		}
		cout << num_values[1] << " vs " << num_values[0] << " ";
		displayBool(changeValue(num_values[1], num_values[0], average, degreeStart));
		cout << "Value :" <<matrix[1][0]<<endl;
		//	Clears the vector of the previous data
		d.clear();
		cout << "Calcuating for " << degreeStart << endl;
		//	Calculates the degree and stores in in Vector d
		calculateDegree(matrix, d, num_of_entities);

		//	Adds the number of degrees to the header of the output csv file
		header.push_back("Degree " + to_string(degreeStart));
		header.push_back(",");

		//	Adds the values of Vector d to the Multidimentional Vector degree
		degree.push_back(d);

		degreeStart += degreeChange;


	}
	cout << "Done!" << endl;

	cout << "4)--------------------------------" << endl;
	cout << "Writing the matrix to the output CSV file." << endl;

	ofstream fout(output_name);
	if (fout.is_open()){
		fout << "Name" << "," << "Value" << ",";
		for (unsigned int a = 0; a < header.size(); a++){
			fout << header[a];			//prints out the header
		}
		fout << endl;
		for (unsigned int i = 0; i<array.size(); i++){
			for (unsigned int j = 0; j<array[i].size(); j++){
				fout << array[i][j] << ",";
			}
			for (unsigned int b = 0; b < degree.size(); b++){
				fout << degree[b][i] << ",";
			}

			fout << endl;
		}
		for (int i = 0; i < num_of_entities; i++){
			for (int j = 0; j < num_of_entities; j++){
				fout << matrix[i][j] << ",";
			}
			fout << endl;
		}
	}
	cout << "Done!" << endl;
	//displayMatrix(matrix, num_of_entities);

	cout << "Saved file as : " << output_name << endl;

	//Pauses the command prompt on windows so the program does not exit imideatly 
	system("pause");

	return 0;
}