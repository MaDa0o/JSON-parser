#include<iostream>
#include<vector>

/*
step:1 Validation of the json file.
->checking opening and closing brackets including nested objects.
->checking the key value syntax (: in between them)
->checking if key-value pairs are seperated by commas or not
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

bool checkValidity(std::vector<char>& v,int n){
	if(n<2){
		return false;
	}
	if(!checkBrackets(v,n)){
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