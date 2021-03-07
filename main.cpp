#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <iostream>

using namespace std;
using std::unordered_map;

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

    		//Capture cancel
    		if(c=='/'){
    			capture = 0;
    			ss_index = 0;
    			capture_string = "";
    		}

    		//Capture end
    		if(c=='<' && capture==1){
    			if(capture_string=="")continue;
    			std::transform(capture_string.begin(), capture_string.end(), capture_string.begin(), asciitolower);
    			output.push_back(capture_string);
    			capture = 0;
    			ss_index = 0;
    			capture_string = "";
    		}

    		//Capture
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


    		// cout << c << " " << capture << " " << ss_index << " " << output.size() << endl; //del
    	}
    }

	//del
	// for(auto &v : output){
	// 	cout << "output: " << v << endl;
	// }

	return output;
}

unordered_map<string,string> get_topic_to_id(vector<string> input, vector<string> topics){

	unordered_map<string,string> output;

	for(auto &line : input){
		for(auto &topic : topics){

			std::transform(line.begin(), line.end(), line.begin(), asciitolower);
			std::transform(topic.begin(), topic.end(), topic.begin(), asciitolower);

			if (line.find(topic) != std::string::npos) {
				
				string new_id = "";
				bool capture = 0;

				for(char& c : line){

					//Capture end
					if(c=='"' && capture == 1){
						capture = 0;
						continue;
					}

					//Capture
					if(capture){
						new_id += c;
					}

					//Capture start 
					if(c=='"' && capture == 0){
						capture  = 1;
					}

					//cout << c << " " << capture << " " << new_id << endl; //del
				}

				output.emplace(make_pair(topic,new_id));
				//cout << "Added: " << topic << " /// " << new_id << endl; //del
			}
		}
	}

	return output;
}

bool c_assert(uint id, bool x){
	if(x==0){
		cout << id << " FAILED!!" << endl;
	}
}

int main ( int argc, char *argv[] ){

	//TEST get_topics()
	vector<string> v1 = {};
	vector<string> v2 = {"<h2>hello</h2>"};
	vector<string> v3 = {"hello"};
	vector<string> v4 = {"<h2>hello</h2>","<h2 test>HELLO</h2>"};
	vector<string> v5 = {"hello","hello"};
	vector<string> v6 = {"<h2>hello</h3><h2 test>HELLO</h2>"};
	c_assert(0,get_topics(v1)==v1);
	c_assert(1,get_topics(v2)==v3);
	c_assert(2,get_topics(v4)==v5);
	c_assert(3,get_topics(v6)==v5);

	//TEST add_links
	vector<string> i1 = {"<li><a href=\"#abstraction\">Abstraction</li>"};
	vector<string> t1 = {"abstraction"};
	vector<string> i2 = {"<li><a href=\"#abstraction\">Abstraction</li>","<li><a href=\"#correct\">test topic</li>"};
	vector<string> t2 = {"abstraction","test topic"};
	unordered_map<string,string> o1 = {make_pair("abstraction","#abstraction")};
	unordered_map<string,string> o2 = {make_pair("abstraction","#abstraction"),make_pair("test topic","#correct")};
	c_assert(4,get_topic_to_id(i1,t1)==o1);
	c_assert(5,get_topic_to_id(i1,t2)==o1);
	c_assert(6,get_topic_to_id(i2,t2)==o2);
	c_assert(7,get_topic_to_id(i2,t1)==o1);

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
