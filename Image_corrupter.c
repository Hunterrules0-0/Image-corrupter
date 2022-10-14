#include <stdio.h>
#include <stdlib.h>
#include "./tools/crc.c"
#include <zlib.h>

// this functions figures out if the picture is a png or not
int get_image_format(int Imagetype, const char * restrict image1[], FILE *ImageFP1)
{
int i;
unsigned int calulated_crc;
long int offset = 1;
int c;
int ComfirmImageFormat = 0;
int IDAT_START;
int Endlocation;
unsigned char buffer[256 * 128 * 16];

fseek(ImageFP1, offset, SEEK_SET);	
c = fgetc(ImageFP1);
if (c == 'P'){

Imagetype = 1; //image is a png if this gets called
printf("reading for chunks\n");

for(int i = 1; i < 20; i++){
	offset++;
	fseek(ImageFP1, offset, SEEK_SET);	//check the image byte. It uses the offset as a pointer to which bytes we want to check
	c = fgetc(ImageFP1); //store the image byte into a var for later
	if(c == 'I' || c == 'H' || c == 'D' || c == 'R'){
		ComfirmImageFormat++;
	}
	

}
	if(ComfirmImageFormat == 4){ //find IDAT location
		printf("\nCan 90 percent comfirm its a png\n");
		ComfirmImageFormat = 0;
		for(int i = 1; i < 50; i++){
			offset++; //add 1 to offset
			fseek(ImageFP1, offset, SEEK_SET);	
			c = fgetc(ImageFP1);
			if(c == 'D'){
				ComfirmImageFormat++; 
				
			}else if(c == 'A' || c == 'T'){
				ComfirmImageFormat++;
				
			}else if(c != 'D' && c != 'A' && c != 'T'){
				ComfirmImageFormat == 0;
			}

			switch (ComfirmImageFormat){
				case 3:
					IDAT_START = offset - 2; //save the value of idat 
					i = 52;
					break;
			}
			
		}
	}else{printf("\nIt seems you have met a terriable fate havent you. The program couldnt find the IDAT chunk in the png image"); exit(0);}
		if(ComfirmImageFormat > 2){
			printf("\n hooray succesfully found IDAT chunk location"); //IDAT LOCATION STORED IN IDAT_START
		    //find end of the IDAT CHUNK so we can calulate the crc
			ComfirmImageFormat = 0;
		
		    for(int i = 1; i < 1000; i){
		    	offset++; //add 1 to offset

		    	fseek(ImageFP1, offset, SEEK_SET);	
		    	c = fgetc(ImageFP1);
		    		if(c == 'E' || c == 'N' || c == 'D'){
																		
						ComfirmImageFormat++;
					}
					if(c != 'E' && c != 'N' && c != 'D'){
						ComfirmImageFormat = 0;

					}
					if(ComfirmImageFormat == 3){
						printf("\n found end");
						printf("\n %x", c);
						Endlocation = offset - 6;

						i = -1;
						for(offset = IDAT_START; offset < Endlocation; offset++){
							i++;
							fseek(ImageFP1, offset, SEEK_SET);	//check the image byte. It uses the offset as a pointer to which bytes we want to check
							c = fgetc(ImageFP1); //store the image byte into a var for later
							buffer[i] = c;
								
							

							
						}	
						printf("reading");
						fclose(ImageFP1);
						ImageFP1 = fopen("Image_Data", "a");
						for(int e = 0; e < i; e++){
						fputc (buffer[e], ImageFP1);

						}
						i = 1000;

					}
					
					

		    }		

		}else{printf("\n We cant find IDAT. is this a valid png file or dose my code suck that bad?"); exit(0);}
	
// document
//get other info 
//maybe calc crc?
}

}






//ImageCorrupter.c  <./ Image name here>

// Int main
// the part where our code starts
//
// It uses 2 Arguments ARGC and Image
// ARGC is not important and dosent relate to the code. Its just something thats required in most c programs to make arguments work
// Image Is the image the user Specifys when running 
//
int main(int argc,  const char * restrict image[])
{
	int i;
	int Imagetype;
	char ImageBytes[50];
	FILE *ImageFP; // FP is short for file pointer
	ImageFP = fopen(image[1], "rb+"); // load our image
	 get_image_format(Imagetype, image, ImageFP);
        
}




