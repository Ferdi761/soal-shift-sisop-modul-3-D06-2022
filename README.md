<p align="center"> Praktikum 3 sisop kelompok D06
    <br> 
</p>

## NO. 1

Novak adalah seorang mahasiswa biasa yang terlalu sering berselancar di internet. Pada suatu saat, Ia menemukan sebuah informasi bahwa ada suatu situs yang tidak memiliki pengguna. Ia mendownload berbagai informasi yang ada dari situs tersebut dan menemukan sebuah file dengan tulisan yang tidak jelas. Setelah diperhatikan lagi, kode tersebut berformat base64. Ia lalu meminta kepada anda untuk membuat program untuk memecahkan kode-kode di dalam file yang Ia simpan di drive dengan cara decoding dengan base 64. Agar lebih cepat, Ia sarankan untuk menggunakan thread.

### 1a

Novak adalah seorang mahasiswa biasa yang terlalu sering berselancar di internet. Pada suatu saat, Ia menemukan sebuah informasi bahwa ada suatu situs yang tidak memiliki pengguna. Ia mendownload berbagai informasi yang ada dari situs tersebut dan menemukan sebuah file dengan tulisan yang tidak jelas. Setelah diperhatikan lagi, kode tersebut berformat base64. Ia lalu meminta kepada anda untuk membuat program untuk memecahkan kode-kode di dalam file yang Ia simpan di drive dengan cara decoding dengan base 64. Agar lebih cepat, Ia sarankan untuk menggunakan thread.

```
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
```

### 1b

Decode semua file .txt yang ada dengan base 64 dan masukkan hasilnya dalam satu file .txt yang baru untuk masing-masing folder (Hasilnya nanti ada dua file .txt) pada saat yang sama dengan menggunakan thread dan dengan nama quote.txt dan music.txt. Masing-masing kalimat dipisahkan dengan newline/enter.

```
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
```

### 1c

Pindahkan kedua file .txt yang berisi hasil decoding ke folder yang baru bernama hasil.

```

```

### 1d

Folder hasil di-zip menjadi file hasil.zip dengan password 'mihinomenest[Nama user]'. (contoh password : mihinomenestnovak)

```

```

### 1e

Karena ada yang kurang, kalian diminta untuk unzip file hasil.zip dan buat file no.txt dengan tulisan 'No' pada saat yang bersamaan, lalu zip kedua file hasil dan file no.txt menjadi hasil.zip, dengan password yang sama seperti sebelumnya.

```

```

## Soal 2

### Narasi Soal

Bluemary adalah seorang Top Global 1 di salah satu platform online judge. Suatu hari Ia ingin membuat online judge nya sendiri, namun dikarenakan Ia sibuk untuk mempertahankan top global nya, maka Ia meminta kamu untuk membantunya dalam membuat online judge sederhana. Online judge sederhana akan dibuat dengan sistem client-server dengan beberapa kriteria sebagai berikut:

### # A

Pada saat client terhubung ke server, terdapat dua pilihan pertama yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. Data input akan disimpan ke file **users.txt** dengan format **username:password**. Jika client memilih login, server juga akan meminta client untuk input id dan passwordnya lalu server akan mencari data di **users.txt** yang sesuai dengan input client. Jika data yang sesuai ditemukan, maka client dapat login dan dapat menggunakan command-command yang ada pada sistem. Jika tidak maka server akan menolak login client. Username dan password memiliki kriteria sebagai berikut:

- Username unique (tidak boleh ada user yang memiliki username yang sama)
- Password minimal terdiri dari 6 huruf, terdapat angka, terdapat huruf besar dan kecil

**Penyelesaian A**

Library yang digunakan adalah sebagai berikut:
c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

#define PORT 8080
#define MAX_LENGTH 1024
untuk server.c, sedangkan untuk client.c adalah sebagai berikut:
c
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_LENGTH 1024
#define PORT 8080

Pada bagian server.c dan client.c terdapat struct user_t untuk menyimpan data-data user.
Pada server.c adalah sebagai berikut:
c
struct user_t {
char name[1000];
char pwd[1000];
char file[1000];
char mode[1000];
int is_auth;
int socket;
} user;
Sedangkan pada client.c adalah sebagai berikut:
c
struct user_t {
int is_auth;
int socket;
char file[1000];
char input[1000];
char mode[1000];
} user;

Selanjutnya terdapat fungsi message di server.c untuk mengirim message.
c
void message(char input[]) {
char buffer[1024];
sprintf(buffer, "\n%s\n", input);
send(user.socket, buffer, 1024, 0);
}

Untuk login, pada server.c terdapat function `login`:
c
int login(char id[], char password[]) {
FILE *fp = fopen("users.txt", "r");
int is_auth = 0;
char buffer[1024];
while (fgets(buffer, 1024, fp) != NULL && is_auth == 0) {
char file_id[1024], file_password[1024];
char *token = strtok(buffer, ":");
strcpy(file_id, token);
token = strtok(NULL, "\n");
strcpy(file_password, token);

        if (strcmp(id, file_id) == 0 && strcmp(password, file_password) == 0) {
            is_auth = 1;
        } else {
            is_auth = 0;
        }
    }
    fclose(fp);
    return is_auth;

}

Selanjutnya untuk mengecek password apakah sudah sesuai dengan kriteria soal atau belum dapat menggunakan fungsi `checkpass`:
c
int checkPass(char pass[]) {
int flaga = 0;
int flagb = 0;
int flagc = 0;
if (strlen(pass) < 6) {
return 1;
} else {
for (int i = 0; i < strlen(pass); i++) {
if (isupper(pass[i])) {
flaga++;
}
if (islower(pass[i])) {
flagb++;
}
if (isdigit(pass[i])) {
flagc++;
}
}
}
if (flaga == 0 || flagb == 0 || flagc == 0) {
return 1;
}
return 0;
}

Kemudian untuk registrasi, pada server.c terdapat fungsi regist
c
int regist(char id[], char password[]) {
int cp;
int flag = 0;
FILE *fp = fopen("users.txt", "a+");
if (fp == NULL) {
printf("masuk");
cp = checkPass(password);
if (cp == 0) {
fprintf(fp, "%s:%s\n", id, password);
} else {
flag = 2;
}
} else {
char buffer[1024];
// fgets(buffer, 1024, fp);
// fscanf(fp, "%s", buffer);
// printf("%s\n", buffer);
while (fgets(buffer, 1024, fp) != NULL) {
char file_id[1024];
char *token = strtok(buffer, ":");
strcpy(file_id, token);
// printf("%s\n", file_id);

            if (strcmp(id, file_id) == 0) {
                message("Username already exist.");
                flag = 1;
                break;
            }
        }
        if (checkPass(password) == 1) {
            message("Password Invalid. Must have be at least 6 characters long, 1 lowercase, 1 uppercase, and 1 number");
            flag = 2;
        } else if (flag == 0) {
            fprintf(fp, "%s:%s\n", id, password);
        }
    }
    fclose(fp);
    return flag;

}

Berikutnya untuk menginputkan apakah user akan login atau register pada server.c digunakan fungsi signin
c
void \*signin() {
char buffer[1024];
while (1) {
if (user.is_auth == 0) {
message("1. Login\n""2. Register\n""Choices: ");

            read(user.socket, buffer, 1024);
            for (int i = 0; buffer[i]; i++) {
                buffer[i] = tolower(buffer[i]);
            }
            if (strcmp(buffer, "login") == 0 || strcmp(buffer, "1") == 0) {
                char id[1024];
                char password[1024];
                message("\e[1;1H\e[2J");
                message("Id: ");
                read(user.socket, id, 1024);

                message("Password: ");
                read(user.socket, password, 1024);

                user.is_auth = login(id, password);
                if (user.is_auth == 0) {
                    message("\e[1;1H\e[2J");
                    message("Login failed id/password is wrong!");
                    printf("Login failed id/password is wrong!\n");
                    break;
                } else if (user.is_auth == 1) {
                    strcpy(user.name, id);
                    strcpy(user.pwd, password);
                    strcpy(user.mode, "recvstrings");
                    // loginsukses();
                }
            }
            if (strcmp(buffer, "register") == 0 || strcmp(buffer, "2") == 0) {
                char id[1024];
                char password[1024];
                int rs;
                message("\e[1;1H\e[2J");
                message("ID: ");
                read(user.socket, id, 1024);

                message("Password: ");
                read(user.socket, password, 1024);

                rs = regist(id, password);
                // printf("%d\n", rs);
                if (rs == 1) {
                    message("\e[1;1H\e[2J");
                    message("Username already exist!");
                    printf("Username already exist!\n");
                    break;
                } else if (rs == 2) {
                    message("\e[1;1H\e[2J");
                    message("Password Invalid! Must have be at least 6 characters long, 1 uppercase, 1 lowercase, and 1 number");
                    printf("Password Invalid! Must have be at least 6 characters long, 1 uppercase, 1 lowercase, and 1 number\n");
                    break;
                } else {
                    message("\e[1;1H\e[2J");
                    message("Register Successfully!");
                    printf("Register Successfully!\n");
                    break;
                }
            }
        } else if (user.is_auth == 1) {
            // loginsukses();
        }
    }

}

Kemudian di client.c, terdapat fungsi input_user untuk mendapatkan input dari user
c
void *input_user(void *arg) {
while (strcmp(user.mode, "recvstrings") == 0) {
char buffer[1024] = {0};
bzero(buffer, MAX_LENGTH);
fgets(buffer, MAX_LENGTH, stdin);
buffer[strcspn(buffer, "\n")] = 0;

        send(user.socket, buffer, MAX_LENGTH, 0);
    }

}

Dan ada fungsi printing untuk melakukan print di client
c
void *printing(void *arg) {
if (strcmp(user.mode, "recvstrings") == 0) {
int sock = _(int _)arg;
char buffer[1024] = {0};
while (1) {
memset(buffer, 0, 1024);
if (recv(sock, buffer, 1024, 0) > 1) {
char buffer2[1024];
strcpy(buffer2, buffer);
char \*token = strtok(buffer2, "\n");
printf("%s", buffer);
}
}
}
}

### # B

Sistem memiliki sebuah database pada server untuk menampung problem atau soal-soal yang ada pada online judge. Database ini bernama **problems.tsv** yang terdiri dari **judul problem dan author problem (berupa username dari author), yang dipisah dengan \t**. File otomatis dibuat saat server dijalankan.

**Penyelesaian B**

Penyelesaian B

### # C

**Client yang telah login**, dapat memasukkan command yaitu ‘add’ yang berfungsi untuk menambahkan problem/soal baru pada sistem. Saat client menginputkan command tersebut, server akan meminta beberapa input yaitu:

- Judul problem (unique, tidak boleh ada yang sama dengan problem lain)
- Path file description.txt pada client (file ini berisi deskripsi atau penjelasan problem)
- Path file input.txt pada client (file ini berguna sebagai input testcase untuk menyelesaikan problem)
- Path file output.txt pada client (file ini berguna untuk melakukan pengecekan pada submission client terhadap problem)
  Seluruh file akan disimpan oleh server ke dalam folder dengan nama <judul-problem> yang di dalamnya terdapat file description.txt, input.txt dan output.txt. Penambahan problem oleh client

  ## NO. 3

Nami adalah seorang pengoleksi harta karun handal. Karena Nami memiliki waktu luang, Nami pun mencoba merapikan harta karun yang dimilikinya berdasarkan jenis/tipe/kategori/ekstensi harta karunnya. Setelah harta karunnya berhasil dikategorikan, Nami pun mengirimkan harta karun tersebut ke kampung halamannya.

### 3a

Di soal ini kami diminta untuk mengextract `hartakarun.zip` ke dalam folder “/home/[user]/shift3/”. Lalu, working directory berada di “/home/[user]/shift3/hartakarun/” yang mana file tersebut dikategorikan secara rekursif.

## 3b

Di soal ini kami disuruh untuk membuat dua folder yaitu "Unknown" dan "Hidden" dan semua file harus berada di dalam folder yang tepat. Untuk menampung file yang tidak memiliki ekstensi ada di folder "Unknown" serta untuk menampung file hidden ada di folder "Hidden".

```
void *mv(void *fName)
{
    char curDir[PATH_MAX];
    char dirName[200];
    char hdd[100];
    char hddName[100];
    char file[100];
    char extFile[100];
    int i;
    strcpy(extFile, fName);
    strcpy(hddName, fName);
    char *namaa = strrchr(hddName, '/');
    strcpy(hdd, namaa);

    if (hdd[1] == '.')
    {
        strcpy(dirName, "Hidden");
    }
    else if (strstr(fName, ".") != NULL)
    {
        strcpy(file, fName);
        strtok(file, ".");
        char *token = strtok(NULL, "");
        for (i = 0; token[i]; i++)
        {
            token[i] = tolower(token[i]);
        }
        strcpy(dirName, token);
    }
    else {
        strcpy(dirName, "Unknown");
    }
    int exist = cFile(extFile);
    if (exist)
        mkdir(dirName, 0777);

    if (getcwd(curDir, sizeof(curDir)) != NULL)
    {
        char *nama = strrchr(fName, '/');
        char namafile[200];
        strcpy(namafile, curDir);
        strcat(namafile, "/");
        strcat(namafile, dirName);
        strcat(namafile, nama);

        rename(fName, namafile);
    }
}
```

## 3c

Di soal ini kami disuruh untuk agar proses kategori bisa berjalan lebih cepat. Jadi di setiap satu file yang dikategorikan dioperasikan oleh satu thread.

```
void lof(char *bsPath)
{
    char path[1000];
    struct dirent *dp;
    struct stat buffer;
    DIR *dir = opendir(bsPath);
    int n = 0;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, bsPath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            if (stat(path, &buffer) == 0 && S_ISREG(buffer.st_mode))
            {
                pthread_t thread;
                int err = pthread_create(&thread, NULL, mv, (void *)path);
                pthread_join(thread, NULL);
            }
            lof(path);
        }
    }
    closedir(dir);
}
```

## 3d

Di soal ini kami disuruh untuk mengirimkan file ke Cocoyasi Village dengan menggunakan program client-server. Pada saat dijalankan, maka folder "/home/[user]/shift3/hartakarun/” akan di-zip menjadi file “hartakarun.zip”.

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void sFile(FILE *fp, int socketFd)
{
    int n;
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(socketFd, data, sizeof(data), 0) == -1)
        {
            perror("~Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int socketFd;
    struct sockaddr_in serverAdd;
    FILE *fp;
    char *fName = "hartakarun.zip";

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0)
    {
        perror("~Error in socket");
        exit(1);
    }
    printf("~Server socket created successfully.\n");

    serverAdd.sin_port = port;
    serverAdd.sin_addr.s_addr = inet_addr(ip);
    serverAdd.sin_family = AF_INET;


    e = connect(socketFd, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    if (e == -1)
    {
        perror("~Error in socket");
        exit(1);
    }
    printf("~Connected to Server.\n");

    char comm[100];
    scanf("%s", comm);
    if (strcmp(comm, "send hartakarun.zip") == 0)
    {
        // scanf("%s", fName);

        fp = fopen(fName, "r");
        if (fp == NULL)
        {
            perror("~Error in reading file.");
            exit(1);
        }

        sFile(fp, socketFd);
        printf("~File data sent successfully.\n");

        printf("~Closing the connection.\n");
        close(socketFd);
    }
    return 0;
}
```

## 3e

Di soal ini kami disuruh untuk client dapat mengirimkan file “hartakarun.zip” ke server dengan mengirimkan command ke server.

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void wFile(int socketFd)
{
    int n;
    FILE *fp;
    char *fName = "hartakarun.zip";
    char buffer[SIZE];

    fp = fopen(fName, "w");
    while (1)
    {
        n = recv(socketFd, buffer, SIZE, 0);
        if (n <= 0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
}

int main()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int socketFd, new_sock;
    struct sockaddr_in serverAdd, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0)
    {
        perror("~Error in socket");
        exit(1);
    }
    printf("~Server socket created successfully.\n");

    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = port;
    serverAdd.sin_addr.s_addr = inet_addr(ip);

    e = bind(socketFd, (struct sockaddr *)&serverAdd, sizeof(serverAdd));
    if (e < 0)
    {
        perror("~Error in bind");
        exit(1);
    }
    printf("~Binding successfull.\n");

    if (listen(socketFd, 10) == 0)
    {
        printf("~Listening....\n");
    }
    else
    {
        perror("~Error in listening");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(socketFd, (struct sockaddr *)&new_addr, &addr_size);
    wFile(new_sock);
    printf("~Data written in the file successfully.\n");

    return 0;
}
```

## ✍️ Authors <a name = "authors"></a>

- Achmad Ferdiansyah - 5025201245
- Nazhifah Elqolby 5025201156
- Ravin Pradhitya 5025201068
