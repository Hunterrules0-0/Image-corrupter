#include <stdio.h>
#include <stdlib.h>


// this functions figures out if the picture is a png or not and will generate the start and end of the IDAT chunk may 
// add options for other image types in the future
int get_image_format(int Imagetype, const char * restrict image1[], FILE *ImageFP1, int IDAT_start_and_end[])
{
int i;
unsigned int calulated_crc;
long int offset = 1;
int c;
int ComfirmImageFormat = 0;
int IDAT_START;
int Endlocation;

fseek(ImageFP1, offset, SEEK_SET);	
c = fgetc(ImageFP1);
if (c == 'P'){

Imagetype = 1; //image is a png if this gets called


	



		
		ComfirmImageFormat = 0;
		for(int i = 1; i < 2; i=i){
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
					IDAT_START = offset + 5; //save the value of idat 
					i = 52;
					break;
			}
			
		}

		if(ComfirmImageFormat > 2){
			
		    //find end of the IDAT CHUNK
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
						Endlocation = offset - 5;

						
						i = 1000;
						IDAT_start_and_end[1] = IDAT_START;
						IDAT_start_and_end[2] = Endlocation;
					}
					
					

		    }		
		
		}else{printf("\n We cant find IDAT. is this a valid png file or dose my code suck that bad?"); exit(0);}
	
	
}

return(*IDAT_start_and_end);
}




int CorruptIDAT(int IDAT_Location, int End_IDAT_location ){
	int amount_of_bytes = 0;
	int ChosenNumber;
	for(int i = IDAT_Location; i < End_IDAT_location; i++){amount_of_bytes = i;}

	printf("\n Image file loaded there are 1 out of %i", amount_of_bytes);
	printf(" bytes to corrupt please select the amount of bytes that will randomly be chosen be corrupt \n\n");
	printf(" Amount of bytes:");
	scanf("%i", &ChosenNumber);
	for(int i = 0; i < ChosenNumber; i++){
		//Corrupt Image
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
	int store[3];
	int i;
	int Imagetype;
	char ImageBytes[50];
	FILE *ImageFP; // FP is short for file pointer
	ImageFP = fopen(image[1], "rb+"); // load our image
	 get_image_format(Imagetype, image, ImageFP, store);
	 printf("%i", store[1]);
	 CorruptIDAT(store[1], store[2]);
	
}




