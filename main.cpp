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
std::string trim(std::string str)
{
    int i = 0;
    int j = str.size()-1;

    while(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'){
    	i++;
    }
    while(str[j] == ' ' || str[j] == '\n' || str[j] == '\t'){
    	j--;
    }

    return str.substr(i,j-i+1);
}

//This is a utility function
bool isNumeric(std::string str){
	if((str[0]-'0') >= 1 && (str[0]-'0') <= 9){}
	else{
		return false;
	}
	for(int i = 1;i<str.size();i++){
		if((str[i]-'0') >= 0 && (str[i]-'0') <= 9){}
	else{
		return false;
	}
	}
	return true;
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
	//This will work even for branched object
	bool semicolon = false;
	for(int i = 1;i<n;i++){
		if(!semicolon && v[i] == '}'){
			semicolon = true;
		}
		if(v[i] == ':'){
			if(semicolon){
				return false;
			}
			semicolon = true;
		}
		if(v[i] == ',' || v[i] == '{'){
			if(!semicolon){
				return false;
			}
			semicolon = false;
		}
	}

	return semicolon;
}

bool checkList(std::string v, int n){
	std::string buff(v.begin()+1,v.end());
	buff.pop_back();
	buff.push_back(',');	//adding this so it doesn't leaves the end pair

	//tokenizing the string
	char *token;
	char *rest = buff.data();
	while((token = strtok_r(rest, ",", &rest))){
		std::string t = token;
		if(token[0] != '"' || token[strlen(token)-1] != '"'){
			return false;
		}
	}
	return true;
}

bool checkValues(std::vector<char>& v, int n){
	std::vector<std::vector<std::string>> kvpairs = seperatePairs(v,n);
	
	for(int i = 0;i<kvpairs.size();i++){
		std::string value = kvpairs[i][1];
		value = trim(value);
		//if value is another object then skip because it is already checked
		if(value[0] == '{' && value[value.size()-1] == '}'){
			continue;
		}
		//if value is a list check it's validity
		if(value[0]=='[' && value[value.size()-1] == ']'){
			if(!checkList(value,value.size())){
				return false;
			}
			continue;
		}
		//if value is a string then it's valid
		if(value[0]=='"' && value[value.size()-1] == '"'){
			continue;
		}
		if(value == "true" || value == "false" || value == "null" || isNumeric(value)){}
		else{
			return false;
		}
	}
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
	//check validity of key value syntax
	if(!checkPairs(v,n)){
		return false;
	}
	//check validiy of keys
	if(!checkKeys(v,n)){
		return false;
	}
	//check validity of values
	if(!checkValues(v,n)){
		return false;
	}

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