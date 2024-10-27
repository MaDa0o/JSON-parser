#include<iostream>
#include<vector>
#include<string.h>

/*
1 Validation of the json file.
->checking opening and closing brackets including nested objects.
->checking the key value syntax (: in between them)
->checking if key-value pairs are seperated by commas or not
->checking the validity of data types and keys
*/

bool checkBrackets(std::vector<char>& v,int n){
	std::vector<char> stk1;
	std::vector<char> stk2;
	std::vector<char> stk3;

	for(int i = 0;i<n;i++){
		if(v[i] == '{'){
			stk1.push_back('{');
		}else if(v[i]=='}'){
			stk1.pop_back();
		}else if(v[i] == '('){
			stk2.push_back('(');
		}else if(v[i]==')'){
			stk2.pop_back();
		}else if(v[i] == '['){
			stk3.push_back('[');
		}else if(v[i]==']'){
			stk3.pop_back();
		}
	}
	if(stk1.empty() && stk2.empty() && stk3.empty()){
		return true;
	}
	return false;
}

std::vector<std::string> seperatePairs(std::vector<char>& v,int n){
	std::vector<std::string> pairs;
	std::string buff(v.begin()+1,v.end());
	buff.pop_back();
	buff.push_back(',');	//adding this so it doesn't leaves the end pair

	//tokenizing the string
	char *token;
	char *rest = buff.data();
	while((token = strtok_r(rest, ",", &rest))){
		std::string t = token;
		pairs.push_back(t);
	}
	return pairs;
}

bool checkKeys(std::vector<char>& v,int n){
	std::vector<std::string> kvpairs = seperatePairs(v,n);
	return true;
}

bool checkValidity(std::vector<char>& v,int n){
	if(n<2){
		return false;
	}
	//check brackets
	if(!checkBrackets(v,n)){
		return false;
	}
	//check validity of key value pairs
	//check validiy of keys
	if(!checkKeys(v,n)){
		return false;
	}
	//check validity of data types
	return true;
}

int main(int argc, char *argv[]){
	std::string filename = (std::string)argv[1];
	std::vector<char> v;
	if (FILE *fp = fopen(filename.c_str(), "r"))
	{
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			v.insert(v.end(), buf, buf + len);
		fclose(fp);
	}

	if(checkValidity(v,v.size())){
		std::cout<<"Json is Valid"<<"\n";
	}else{
		std::cout<<"Json is Invalid"<<"\n";
		return 1;
	}
	
	return 0;
}