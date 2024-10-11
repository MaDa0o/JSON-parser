#include<iostream>
#include<vector>

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

	if(v.size()>=2 && v[0]=='{' && v[v.size()-1] == '}'){
		std::cout<<"Valid"<<std::endl;
		return 0;
	}
	else{
		std::cout<<"InValid"<<std::endl;
		return 1;
	}
	return 0;
}