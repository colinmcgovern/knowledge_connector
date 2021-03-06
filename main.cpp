#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;

/*
  _____     ___        __  ___    _____                    
 / ___/__  / (_)__    /  |/  /___/ ___/__ _  _____ _______ 
/ /__/ _ \/ / / _ \  / /|_/ / __/ (_ / _ \ |/ / -_) __/ _ \
\___/\___/_/_/_//_/ /_/  /_/\__/\___/\___/___/\__/_/ /_//_/
                                                           
FEEL FREE TO COPY AND REUSE
*/

//TO COMPILE:  g++ header_to_function_list.cpp -std=c++11

char asciitolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

vector<string> get_topics(vector<string> input){

	bool capture = 0;
	string capture_string = "";

	vector<string> output;

	for(auto &line : input){

    	string start_string = "<h2>";
    	uint ss_index = 0;
    	for(char& c : line){

    		//Capture end
    		if(c=='<' && capture==1){
    			if(output=="")continue;
    			std::transform(capture_string.begin(), capture_string.end(), capture_string.begin(), asciitolower);
    			output.push_back(capture_string);
    			capture = 0;
    			ss_index = 0;
    			capture_string = "";
    		}

    		if(capture==1){
    			capture_string += c;
    		}

    		//Capture start
    		if(c==start_string[ss_index]){
    			ss_index++;
    		}

    		if(ss_index>=start_string.size()){
    			capture = 1;
    		}


    		cout << c << " " << capture << " " << ss_index << " " << output.size() << endl; //del
    	}
    }

	//del
	for(auto &v : output){
		cout << "output: " << v << endl;
	}

	return output;
}

bool c_assert(uint id, bool x){
	if(x==0){
		cout << id << " FAILED!!" << endl;
	}
}

int main ( int argc, char *argv[] ){

	//TESTS
	vector<string> v1 = {};
	vector<string> v2 = {"<h3>hello</h3>"};
	vector<string> v3 = {"hello"};
	vector<string> v4 = {"<h3>hello</h3>","<h3 test>HELLO</h3>"};
	vector<string> v5 = {"hello","hello"};
	c_assert(0,get_topics(v1)==v1);
	c_assert(1,get_topics(v2)==v3);
	c_assert(2,get_topics(v4)==v5);

	string output;

	if(argc!=2){
		cout << "Correct usage:" << endl;
		cout << "./header_to_function_list input_file" << endl;
		return 0;
	}

	ifstream infile(argv[1]);

	vector<string> file_strings;

	string line;
	while (getline(infile, line)){
	    istringstream iss(line);
	    file_strings.push_back(line);
	}

	cout << output << endl;
}
