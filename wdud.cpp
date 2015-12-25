#include <stdio.h>
#include <time.h>

#define CONTENT_SIZE 150
#define FILENAME "diary.txt"

struct wdud
{
	time_t rawtime;
	char input_buffer[CONTENT_SIZE];
};
 
wdud this_time;

void print(char *s)
{
	printf("%s\n", s);
}

char* rnl(char *s)
{
	char *t = s;
	while(*s != '\n' && *s != '\0')
	{
		s++;
	}
	*s = '\0';
	return t;
}

void initialize()
{
	FILE *file_pointer;
	file_pointer = fopen(FILENAME, "rb");
	char buf[sizeof(wdud)];

	if(file_pointer)
	{
		while(fread(buf, sizeof(buf), 1, file_pointer))
		{
			wdud *tmp = (wdud *)buf;
			time_t time_info = tmp->rawtime;
			//todo use sprintf or something..
			printf("%s: %s", rnl(ctime(&tmp->rawtime)), tmp->input_buffer);
		}
		fclose(file_pointer);
	}
}

void saveinput()
{
	FILE *file_pointer;
	file_pointer = fopen(FILENAME, "ab");
	fwrite(&this_time, sizeof(wdud), 1, file_pointer);
	fclose(file_pointer);
}

void getinput()
{
	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	print("What did you do?");
	fgets(this_time.input_buffer, CONTENT_SIZE, stdin);
	
	timeinfo = localtime(&rawtime);
	this_time.rawtime = rawtime;
}

int main(int argc, char *argv[])
{
	initialize();

	if(argc > 1)
	{
		if(argv[1][0] == 'w')
		{
			getinput();
			saveinput();
		}
	}
	return 0;
}
