struct input{
	char data[100];	
};

struct output{
	char data[1000];	
};

program nfsDir{
	version dir_vers{
		output getDir(input)=1;
	}=1;	
}=0x23451111;