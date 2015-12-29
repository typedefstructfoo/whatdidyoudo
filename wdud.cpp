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

int slen(char *s)
{
	int c = 0;
	while(*s++) c++;
	return c;
}

int find_word(char *s, char *w)
{
	int wlen = slen(w);
	int j = 0;
	int result = -1;
	for(int i=0;s[i] != '\0'; i++)
	{
		if(s[i] == w[j])
		{
			j++;
		}else
		{
			j = 0;
		}

		if(j == wlen)
		{
			result = i-j+1;
			break;
		}
	}
	return result;
}

void print_with_colors(char *s)
{
	int pos  = find_word(s, "TODO");
	int wlen = slen("TODO"); 
	for(int i=0;s[i] != '\0'; i++)
	{
		if(pos >= 0)			
		{
			if(pos == i)			
				printf("\x1b[31;103;1m");

			if(pos+wlen == i)
				printf("\x1b[0m");
		}
		printf("%c", s[i]);
	}
	
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
			printf("%s: ", rnl(ctime(&tmp->rawtime)));
			print_with_colors(tmp->input_buffer);
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
	printf("What did you do?\n");
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
