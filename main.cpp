#include<iostream>
#include<vector>
#include<string.h>

/*
1. Validation of the json file.
->checking opening and closing brackets including nested objects.
->checking the key value syntax (: in between them)
->checking if key-value pairs are seperated by commas or not
->checking the validity of data types and keys
*/

//This is a utility function
std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

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

//This is a utility function
std::vector<std::vector<std::string>> seperatePairs(std::vector<char>& v,int n){
	std::vector<std::vector<std::string>> pairs;
	std::string buff(v.begin()+1,v.end());
	buff.pop_back();
	buff.push_back(',');	//adding this so it doesn't leaves the end pair

	//tokenizing the string
	char *token;
	char *rest = buff.data();
	while((token = strtok_r(rest, ",", &rest))){
		std::string t = token;
		std::string key = t.substr(0,t.find(':'));
		std::string value = t.substr(t.find(':')+1);
		pairs.push_back({key,value});
	}
	return pairs;
}

bool checkKeys(std::vector<char>& v,int n){
	std::vector<std::vector<std::string>> kvpairs = seperatePairs(v,n);
	for(int i = 0;i<kvpairs.size();i++){
		std::string key = kvpairs[i][0];
		
		std::size_t found = key.find('"');
		if(found == std::string::npos){
			return false;
		}
		key = key.substr(found+1);
		found = key.find('"');
		if(found == std::string::npos){
			return false;
		}
	}
	return true;
}

bool checkPairs(std::vector<char>& v,int n){
	//Only unbranched implementation for now
	bool semicolon = false;
	for(int i = 0;i<n;i++){
		if(v[i] == ':'){
			if(semicolon){
				return false;
			}
			semicolon = true;
		}
		if(v[i] == ','){
			if(!semicolon){
				return false;
			}
			semicolon = false;
		}
	}

	return semicolon;
}

bool checkValidity(std::vector<char>& v,int n){
	if(n<2){
		return false;
	}
	//check brackets
	if(!checkBrackets(v,n)){
		return false;
	}
	//check validity of key value syntax
	if(!checkPairs(v,n)){
		return false;
	}
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