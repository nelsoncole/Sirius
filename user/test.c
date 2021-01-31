#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <sys/sys.h>

#include <gx.h>
#include <stdint.h>


FILE *f;

int main(int argc, char **argv) {

	f = fopen("a.txt","w");

	if( f == NULL) {
		
		printf("open error\n");

		return -1;

	}


	fputc('\r',f);
	fputc('\n',f);
	fputc('b',f);

	fclose(f);

	return 0;

	if(argc < 2) return 5;

	char *wallpaper = (char *) malloc(0x400000); // 4 MiB
	int size;

	unsigned int width, height, sig;

	char *_wallpaper = wallpaper;
	char *p;

	f = fopen(argv[1],"r");
	if(f == NULL) printf("error: fopen\n");
	else {

	
		fseek(f, 0,SEEK_END);
		size = (int) ftell(f);
		fseek(f, 0,SEEK_SET);

		if(fread(wallpaper, 1, size, f) != size) printf("error: fread\n");
		else {

			p = strtok(_wallpaper,"\n ");

			printf("%s\n",p);

			p = strtok('\0', "\n ");
			width = strtoul (p,NULL, 10);
			p = strtok('\0', "\n ");
			height = strtoul (p,NULL, 10);
			p = strtok('\0', "\n ");
			sig = strtoul (p,NULL, 10);
			_wallpaper = strtok('\0', "\n"); 

			printf("width %d height %d sig %d\n",width, height,sig);

		
			app_color_clearscreen((-1));
			char a[4];
			char rgb[4];

			int off = 0;
			for(int y=0;y < height;y++) {

				for(int x=0;x < width;x++) {

					*(unsigned int*)a =  (*(unsigned int*)((_wallpaper) + (3*off++))) &0xffffff;

					rgb[0] = a[2];
					rgb[1] = a[1];
					rgb[2] = a[0];
					rgb[3] = 0xff;
					PutPixelBuff(x,y,*(unsigned int*)rgb,G->BankBuffer);

				}
			}


			app_refreshrate();
			
		}

	}


	free(wallpaper);

	return 0;
}










