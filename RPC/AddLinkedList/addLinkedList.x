struct numbers{
	int x;
	numbers* next;
};

program ADD_PROG{
	version ADD_VERS{
		int add(numbers)=1;
	}=1;
}=0x23451111;