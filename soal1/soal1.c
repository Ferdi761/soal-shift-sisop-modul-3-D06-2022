#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


void exec_order(char path[], char *argv[])
{
	pid_t child;
	int status;

	child = fork();

	if(child < 0)
	{
		exit(EXIT_FAILURE);
	}

	if(child == 0)
	{
		execv(path, argv);
		exit(0);
	}

	else
	{
		while((wait(&status)) > 0);
	}
}


void download_file(char filename[], char url[])
{
	char *argv[] = {"wget", url, "-O", filename, NULL};
	exec_order("/usr/bin/wget", argv);
}


void unzip_file(char filename[], char output[])
{
	char *argv[] = {"unzip", filename, "-d", output, NULL};
	exec_order("/usr/bin/unzip", argv);
}

// void zip_file(char filename[])


void create_dir(char dir[])
{
	char *argv[] = {"mkdir", "-p", dir, NULL};
	exec_order("/usr/bin/mkdir", argv);
}


// nyomot daristackoverflow untuk return jumlah file yg ada dlm folder
// implementasi pipe dalam function
void read_decoded_file(char filename[], char newfilename[])
{
	int pfds[2];

	pipe(pfds);
	pid_t pid = fork();
	if(pid == 0)
	{
		close(STDOUT_FILENO);
		close(1);
		dup(pfds[1]);
		close(pfds[0]);
		execlp("base64", "base64", filename, NULL);
	}

	else
	{
		char arr_temp[100];
		close(STDIN_FILENO);
		close(0);
		dup(pfds[0]);
		close(pfds[1]);
		wait(0);
		scanf("%[^\n]s", arr_temp);
	}	
}


void decode_file(char filename[])
{
	char *argv[] = {"base64", "-d", filename, NULL};
	// char *argvcat[] = {"cat", out_file, NULL};
	exec_order("/usr/bin/base64", argv);
	// exec_order("/usr/bin/cat", argvcat);
}

//param dir jgn lupa diberi akhiran tanda '/', contoh "folderku/"
void read_write_file(char output_file[], char dir[])
{
	DIR* FD;
	struct dirent* in_file;
	FILE *common_file;
	FILE *file_pipe;
	char buffer[10000];
	char output_file_destiny[200];
	//char path_temp[1000];

	strcpy(output_file_destiny, dir);
	strcat(output_file_destiny, "/");
	strcat(output_file_destiny, output_file);

	

	char *argvtouch[] = {"touch", "-f", output_file_destiny, NULL};
	exec_order("/usr/bin/touch", argvtouch);

	//open or create output file
	common_file = fopen(output_file_destiny, "a+");
	if(common_file == NULL)
	{
		fprintf(stderr, "error : Failed to open common_file - %s\n", strerror(errno));
		return;
	}

	//scanning directory
	if(NULL == (FD = opendir(dir)))
	{
		fprintf(stderr, "error : Failed to open directory - %s\n", strerror(errno));
		return;
	}

	while((in_file = readdir(FD)))
	{
		if(!strcmp(in_file->d_name, "."))
			continue;
		if(!strcmp(in_file->d_name, ".."))
			continue;

		//printf("%s\n", in_file->d_name);
		// strcpy(path_temp, "base64 -d ");
		// strcat(path_temp, in_file->d_name);
		// file_pipe = popen(path_temp, "r");

		// if(file_pipe == NULL)
		// {
		// 	printf("popen() failed to execute");
		// 	exit(1);
		// }

		// while(fgets(buffer, sizeof(buffer), file_pipe) != NULL)
		// {
		// 	fputs(buffer, common_file);
		// 	fputs("\n", common_file);
		// }
		// pclose(file_pipe);
		// memset(path_temp, 0, sizeof(path_temp));
	}

	
	fclose(common_file);

	return;
	
}


pthread_t tid_unzip[2];

void *th_unzip(void *arg)
{
	pthread_t id = pthread_self();
	// char *argvclear[] = {"clear", NULL};

	// if(pthread_equal(id, tid_unzip[0]))
	// {
	// 	exec_order("/usr/bin/clear", argvclear);
	// }

	if(pthread_equal(id, tid_unzip[0]))
	{
		unzip_file("quote.zip", "quote");
	}

	else if(pthread_equal(id, tid_unzip[1]))
	{
		unzip_file("music.zip", "music");
	}
}

pthread_t tid_rwf[2];

void *th_rwf(void *arg)
{
	pthread_t id = pthread_self();
	// char *argvclear[] = {"clear", NULL};

	// if(pthread_equal(id, tid_rwf[0]))
	// {
	// 	exec_order("/usr/bin/clear", argvclear);
	// }

	if(pthread_equal(id, tid_rwf[0]))
	{
		read_write_file("quote.txt", "quote");
	}

	else if(pthread_equal(id, tid_rwf[1]))
	{
		read_write_file("music.txt", "music");
	}
}


int main(int argc, char *argv[])
{
	int i_unzip, i_rwf, error;
	int length_tid_unzip = sizeof(tid_unzip) / sizeof(int);
	int length_tid_rwf = sizeof(tid_rwf) / sizeof(int);

	download_file("quote.zip", "https://docs.google.com/uc?export=download&id=1jR67_JAyozZPs2oYtYqEZxeBLrs-k3dt");
	download_file("music.zip", "https://docs.google.com/uc?export=download&id=1_djk0z-cx8bgISFsMiUaXzty2cT4VZp1");


	for(i_unzip = 0; i_unzip < length_tid_unzip; i_unzip++)
	{
		error = pthread_create(&(tid_unzip[i_unzip]), NULL, &th_unzip, NULL);
		
		if(error != 0)
		{
			printf("\n Gagal membuat thread");
		}

		else
		{
			printf("\n Sukses membuat thread\n");
		}

	}

	
	pthread_join(tid_unzip[0], NULL);
	pthread_join(tid_unzip[1], NULL);


	for(i_rwf = 0; i_rwf < length_tid_rwf; i_rwf++)
	{
		error = pthread_create(&(tid_rwf[i_rwf]), NULL, &th_rwf, NULL);
		
		if(error != 0)
		{
			printf("\n Gagal membuat thread");
		}

		else
		{
			printf("\n Sukses membuat thread\n");
		}

	}

	
	
	pthread_join(tid_rwf[0], NULL);
	pthread_join(tid_rwf[1], NULL);

	exit(0);
	// int cquote = count_file("quote");
	// int cmusic = count_file("music");
	// int fquote[cquote], fmusic[cmusic];

	return 0;
}