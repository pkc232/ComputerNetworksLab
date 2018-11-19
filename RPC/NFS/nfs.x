struct fileName{
	char name[100];
};
struct contentsOut{
	char content[1000];	
};

program readContent{
	version read_vers{
		contentsOut getContent(fileName)=1;
	}=1;
}=0x23451111;