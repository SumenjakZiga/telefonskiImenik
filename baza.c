#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct{
	char ime[20];
	char priimek[20];
	char tel[20];
	char dan[20];
	char mesec[20];
	char leto[20];
}oseba;

void zapisOsebe(oseba*, int);
int preberiOsebo(oseba*, int, int);
/*
Flags:
1-Preverja enakosti
2-iskanje in izpisovanje, ime in priimek
3.iskanje in izpisovanje ime 
*/
int preveriEnakost(oseba*, oseba*, int, int);
void iskanje(oseba*, oseba*);
void izpisOsebe(oseba*);
void iskanjeIme(oseba*, oseba*);

int main(int argv, char* argc[]){
	if(argv <= 1){
		printf("Ni vnešenih zastavic.\n");
	
	}else if(!strcmp(argc[1], "-c")){
		FILE *fd=fopen("spo.dat", "w+");
		fwrite("0", 1, sizeof("0"), fd);
		printf("Binarna datoteka ustvarjena.\n");
		fclose(fd);

	}else if(!strcmp(argc[1], "-o") && argv == 15){
		int fd=atoi(argc[2]);
		if(!strcmp(argc[3], "-tel") && !strcmp(argc[5], "-ime") && !strcmp(argc[7], "-priimek") && !strcmp(argc[9], "-dan") && !strcmp(argc[11], "-mesec") && !strcmp(argc[13], "-leto")){
			char *vel=(char*) malloc(sizeof(char));
			oseba* os=(oseba*)malloc(sizeof(oseba));
			
			pread(fd, vel, 1,0);
			strcpy(os->tel,argc[4]);
			strcpy(os->ime,argc[6]);
			strcpy(os->priimek,argc[8]);
			strcpy(os->dan,argc[10]);
			strcpy(os->mesec,argc[12]);
			strcpy(os->leto,argc[14]);
			//printf("%d", atoi(vel));
			if(atoi(vel)==0){
				zapisOsebe(os, fd);
			}else{
				int enakost=preberiOsebo(os, fd, 1);
				if(enakost)zapisOsebe(os, fd);
			}
			free(vel);
			free(os);
			close(fd);
		}

	}else if(!strcmp(argc[1], "-o") && !strcmp(argc[3], "-ime") && !strcmp(argc[5], "-priimek") && argv==7){
		int fd=atoi(argc[2]);
		oseba* os=(oseba*)malloc(sizeof(oseba));
		strcpy(os->ime,argc[4]);
		strcpy(os->priimek,argc[6]);
		preberiOsebo(os, fd, 2);

		free(os);
		close(fd);
	}else if(!strcmp(argc[1], "-o") && !strcmp(argc[3], "-priimek") && argv==5){
		int fd=atoi(argc[2]);
		oseba* os=(oseba*)malloc(sizeof(oseba));
		strcpy(os->priimek,argc[4]);
		preberiOsebo(os, fd, 3);

		free(os);
		close(fd);
	}else printf("Vnešene zastavice niso pravilne!\n");
	
	return 0;
}

void zapisOsebe(oseba* os, int fd){
	char *vel=(char*) malloc(sizeof(char));
	pread(fd, vel, 1,0);
	//printf("%S")
        vel[0]+=1;
	pwrite(fd, vel, strlen("1"), 0);

	char odmik[2]=" B";
	odmik[1]=strlen(os->tel)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->tel, strlen(os->tel), lseek(fd, 0, SEEK_END));

	odmik[1]=strlen(os->ime)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->ime, strlen(os->ime), lseek(fd, 0, SEEK_END));

	odmik[1]=strlen(os->priimek)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->priimek, strlen(os->priimek), lseek(fd, 0, SEEK_END));
		
	odmik[1]=strlen(os->dan)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->dan, strlen(os->dan), lseek(fd, 0, SEEK_END));

	odmik[1]=strlen(os->mesec)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->mesec, strlen(os->mesec), lseek(fd, 0, SEEK_END));

	odmik[1]=strlen(os->leto)+48;
	pwrite(fd, odmik, strlen(odmik), lseek(fd, 0, SEEK_END));
	pwrite(fd, os->leto, strlen(os->leto), lseek(fd, 0, SEEK_END));
	
	free(vel);
}

int preberiOsebo(oseba* os, int fd, int flag){
	int enakost=1;
	char *vel=(char*) malloc(sizeof(char));
	pread(fd, vel, 1,0);
	int offsetTel=0;

	char *dol=(char*)malloc(sizeof(char));
	int offset=3;
	for(int x=0;x<atoi(vel) && enakost;x++){
		oseba *dva=(oseba*)malloc(sizeof(oseba));

		pread(fd, dol, 1, offset);
		pread(fd, dva->tel, atoi(dol), ++offset);
		offsetTel=offset;
		//printf("%s", dva->tel);
		offset+=atoi(dol)+1;

		pread(fd, dol, 1, offset);
		pread(fd, dva->ime, atoi(dol), ++offset);
		//printf("%s", dva->ime);
		offset+=atoi(dol)+1;

		pread(fd, dol, 1, offset);
		pread(fd, dva->priimek, atoi(dol), ++offset);
		//printf("%s", dva->priimek);
		offset+=atoi(dol)+1;

		pread(fd, dol, 1, offset);
		pread(fd, dva->dan, atoi(dol), ++offset);
		//printf("%s", dva->dan);
		offset+=atoi(dol)+1;

		pread(fd, dol, 1, offset);
		pread(fd, dva->mesec, atoi(dol), ++offset);
		//printf("%s", dva->mesec);
		offset+=atoi(dol)+1;

		pread(fd, dol, 1, offset);
		pread(fd, dva->leto, atoi(dol), ++offset);
		//printf("%s", dva->leto);
		offset+=atoi(dol)+1;

		if(enakost && flag)enakost=preveriEnakost(os, dva, fd, offsetTel);
		if(flag==2)iskanje(os, dva);
		if(flag==3)iskanjeIme(os, dva);
		free(dva);
	}
	
	free(vel);
	free(dol);
	return enakost;
}

int preveriEnakost(oseba* ena, oseba* dva, int fd, int offset){
	if(!strcmp(ena->ime, dva->ime) && !strcmp(ena->priimek, dva->priimek) && !strcmp(ena->dan, dva->dan) && !strcmp(ena->mesec, dva->mesec) && !strcmp(ena->leto, dva->leto)){
		//printf("delam");
		pwrite(fd, ena->tel, strlen(dva->tel), offset);
		return 0;
	}
	return 1;
}

void iskanje(oseba* ena, oseba* dva){
	if(!strcmp(ena->ime, dva->ime) && !strcmp(ena->priimek, dva->priimek))izpisOsebe(dva);
}

void izpisOsebe(oseba* os){
	printf("%s\t%s\t%s\t%s.%s.%s\n", os->tel, os->ime, os->priimek, os->dan, os->mesec, os->leto);
}

void iskanjeIme(oseba* ena, oseba* dva){
	if(!strcmp(ena->priimek, dva->priimek))izpisOsebe(dva);
}
