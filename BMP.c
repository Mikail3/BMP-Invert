/*
* Auteur 1: Mikail Cinar
* Auteur 2: Rasit Akay
* Link naar github repository: https://github.com/Mikail3/cee-programming-BMP-invert
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//declaration
typedef uint32_t DWORD; 
typedef int32_t  LONG; 
typedef uint16_t WORD;

#pragma pack(push, 1) //Disable padding
	typedef struct SaveRGBTemporary //Struct to temporarily save 1 byte value
	{
	unsigned char tempRGB;
	}RGBSAVE;
	#pragma pack(pop)
	
//Struct to save fileheader
#pragma pack(push, 1) //Disable padding
typedef struct BMPHeader
{
	WORD hType; 	//File type
	DWORD hSize; 	//File size (byte)
	WORD hZero; 	//Reserved (0)
	WORD hZero2;	//Reserved (0)
	DWORD hOffset;	//Offset fileheader to actual bitmap (bit)
}HEADER;
#pragma pack(pop)

//Struct to save infoheader
#pragma pack(push, 1) //Disable padding
typedef struct INFOHeader
{
	DWORD iSize;		//Struct size (byte)
	LONG iWidth;		//Bitmap width (pixel)
	LONG iHeight;		//Bitmap height (pixel)
	WORD iColorPlane;	//Amount of color planes (1)
	WORD iBits;			//Amount of bits per pixel
	DWORD iCompress;	//Compression type
	DWORD iImageSize;	//Image size (byte)
	LONG iPPMX;			//X axis pixels per meter
	LONG iPPMY;			//Y axis pixels per meter
	DWORD iColors;		//Amount colors used in bitmap
	DWORD iColorsImp;	//Amount important colors
}INFOHEADER;
#pragma pack(pop)

int main()
{
	FILE *filePointerIn = NULL;
	
	filePointerIn = fopen("input.bmp", "rb"); //Open input file as read-only
	if(filePointerIn == NULL)
	{
			printf("Kan het bestand niet openen\n");
			exit(EXIT_FAILURE);
			return 0;
	}
	else
	{
			
	}
	
	FILE *filePointerOut = NULL;
	
	filePointerOut = fopen("output.bmp", "wb"); //Open/create output file as writable
	{
		printf("Kan het bestand niet aanmaken\n");
		exit(EXIT_FAILURE);
		return 0;
	}
	else
	{
	}
	
	HEADER headFile;
	INFOHEADER infoHead;
	
	
	fread(&headFile, sizeof(headFile), 1, filePointerIn);
	fwrite(&headFile, sizeof(headFile), 1, filePointerOut);
	fread(&infoHead, sizeof(infoHead), 1, filePointerIn);
	fwrite(&infoHead, sizeof(infoHead), 1, filePointerOut);
	
	RGBSAVE saveVariable;
	
	unsigned char testClause = 0; //Variable to check error at end of file to stop loop
	do
	{
		testClause = fread(&saveVariable.tempRGB, 1, 1, filePointerIn); //Read value
		saveVariable.tempRGB = saveVariable.tempRGB ^ 0xFF; //Invert value
		fwrite(&saveVariable.tempRGB, 1, 1, filePointerOut); //Write value
	} while(testClause == 1);
	
	
	fclose(filePointerIn);
	fclose(filePointerOut);
	return 0;
}
