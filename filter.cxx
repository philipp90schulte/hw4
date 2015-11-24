/**
 * Noise filter by g[i] = (f[i-1] + f[i] + f[i+1])/3
 * Author: Philipp Schulte
 * Date: 24/11/2015
 * 
 * Description:
 * Write a program which reads the data from the file into an array, filters the data according to the procedure described 
 * above and then writes the results into a new file.
 * 
 * Structure your program well, in particular:
 * 
 * Write a function which reads the data into an array. The current file has 237 lines, allocate sufficient memory inside 
 *   your reading function. This requires dynamic allocation.
 * Have one function which filters the data. Interpret the data as periodic function, i.e. f[N]=f[0]. Just like in 
 *   previous programs, overwrite the original array and do not create a second array. Note that once your code works, you 
 *   can apply the filter function more than once to the data. It is interesting to see what happens to the data when you 
 *   apply the filter several times.
 * Write the final result inside an extra function into a file, do not overwrite the original data file.
 * Make sure that all memory that has been allocated via new has been freed by a respective delete.
 * 
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

//Header which declare the different functions
void readData(double* const p, string name, const int N);
void filterData(double* const p, const int N);
void print(const double* const p, const int N, const string outname);


int main(void){

	// Section to declare the used variables:
	string sourcename;
		cout << "Enter the complete (name and suffix) filename of your data file: " << endl;
		cin >> sourcename;
	
	int N = 237;
	    cout << "How many data do you want to read in?" << endl;
	    cin  >> N;
	double* p = new double[N];
	
	// Perform the read function:
	readData(p, sourcename, N);
	
	// Filter the entered data
	filterData(p, N);
	
	string outputname = "filteredNoise.txt";
	cout << "Enter a full name (name and suffix) for the filtered data file: " << endl;
	cin >> outputname;
	
	//print out the results
	print(p, N, outputname);
	
	delete[] p;
}

// Implement the additional functions
/**
 * readData function
 * 
 * Input parameters:
 *  - pointer to the created array p. The address is fixed by const
 *  - the entered name of the source file
 *  - the entered number of reading values or the default value 237
 *  
 *  Description:
 *  create an ifstream and read the data in a for loop limited by N.
 *  save the different values in the dynamic array.
 * 
 */
void readData(double* const p, string name, const int N) {
	// open the data stream:
	ifstream in(name.c_str());
	
	for (int i = 0; i < N; i++) 
			in >> p[i];
	
	in.close();
}


/**
 * readData function
 * 
 * Input parameters:
 *  - pointer to the created array p. The address is fixed by const
 *  - the entered number of reading values or the default value 237
 *  
 *  Description:
 *  Save the first and the second last value (h1 and h2)
 *  save in h3 the last value of the array. This is needed for the calculation algorithm.
 *  perform in a for loop the filter algorithem:
 *  - save the value of th current array entry in h4
 *  - calculate the filtered value for the current array position -> use the previous value saved in h3
 *  - store the value of h4 in h3 
 *  -> next round
 * 
 */
void filterData(double* const p, const int N) {
	// Sace the data p[0] = p[N-1];
	double h1 = p[0];
	double h2 = p[N-2];
	double h3 = p[N-1];
	
	
	for (int i = 0; i < N-1; i++) {
		double h4 = p[i];
		p[i] = (h3 + p[i] + p[i+1])/3;
		h3 = h4;
	}
	p[N-1] = (h2 + p[N-1] + h1)/3;
}


/**
 * readData function
 * 
 * Input parameters:
 *  - pointer to the created array p. The address is fixed by const
 *  - the entered number of reading values or the default value 237
 *  - the entered name of the output file
 *  
 *  Description:
 *  Open a data stream and create or overwrite the file named outname.
 *  use a for loop to save the data in the file.
 *  close the datastream
 * 
 */
void print(const double* const p, const int N, const string outname) {
	ofstream out(outname.c_str());
	
	for (int i = 0; i < N; i++)
		out << p[i] << endl;
	
	out.close();
	
}