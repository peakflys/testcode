#include <stdio.h>
#include "temp.h"
int main(int argc, char** argv)
{
	if(argc < 3)
	{
		printf("formate error\nexample: ./a.out 10000 1000\n");	
		return 0;
	}
	size_t key = atoi(argv[1]);
	size_t size = atoi(argv[2]);
	int real_size = 4 * size;
	shm_t* sh_data = frame_shm_create(key, real_size);
	int i = 0;
	int* data = (int*)sh_data->data;
	int loop = sh_data->size/4; //loop should be equal to size
	for(i = 0; i < loop; ++i)
		data[i] = i;
	while(1)
	{
		for(i = 0; i < loop; ++i)
		{
			if(data[i] != i)
			{
				printf("pos: %d, %d != %d  check error!\n", i, data[i], i);	
				break;
			}
		}
		sleep(2);
		printf("tick...\n");
	}
	return 0;
}
