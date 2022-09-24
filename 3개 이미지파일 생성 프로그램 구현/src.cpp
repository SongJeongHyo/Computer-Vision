#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
void main()
{
	BITMAPFILEHEADER hf; // BMP 파일헤더 14Bytes
	BITMAPINFOHEADER hInfo; // BMP 인포헤더 40Bytes
	RGBQUAD hRGB[256]; // 팔레트 (256 * 4Bytes)

	FILE* fp1;
	fp1 = fopen("lenna.bmp", "rb");
	if (fp1 == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp1);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp1);
	fread(hRGB, sizeof(RGBQUAD), 256, fp1);

	FILE* fp2;
	fp2 = fopen("lenna.bmp", "rb");
	if (fp2 == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp2);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp2);
	fread(hRGB, sizeof(RGBQUAD), 256, fp2);

	FILE* fp3;
	fp3 = fopen("lenna.bmp", "rb");
	if (fp3 == NULL) return;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, fp3);
	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, fp3);
	fread(hRGB, sizeof(RGBQUAD), 256, fp3);

	int ImgSize = hInfo.biWidth * hInfo.biHeight;

	BYTE* Image1 = (BYTE*)malloc(ImgSize);
	BYTE* Output1 = (BYTE*)malloc(ImgSize);
	BYTE* Image2 = (BYTE*)malloc(ImgSize);
	BYTE* Output2 = (BYTE*)malloc(ImgSize);
	BYTE* Image3 = (BYTE*)malloc(ImgSize);
	BYTE* Output3 = (BYTE*)malloc(ImgSize);
	fread(Image1, sizeof(BYTE), ImgSize, fp1);
	fread(Image2, sizeof(BYTE), ImgSize, fp2);
	fread(Image3, sizeof(BYTE), ImgSize, fp3);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	/* 영상처리 */

	
	for (int i = 0; i < ImgSize; i++)
		Output1[i] = Image1[i];

	int val = 50;
	for (int i = 0; i < ImgSize; i++) {
		if (Image2[i] + val > 255) {
			Output2[i] = 255;
		}
		else if (Image2[i] + val < 0) {
			Output2[i] = 0;
		}
		else {
			Output2[i] = Image2[i] + val;
		}
	}

	for (int i = 0; i < ImgSize; i++) {
		Output3[i] = 255 - Image3[i];
	}


	fp1 = fopen("output1.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp1);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp1);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp1);
	fwrite(Output1, sizeof(BYTE), ImgSize, fp1);
	fclose(fp1);
	free(Image1);
	free(Output1);

	fp2 = fopen("output2.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp2);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp2);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp2);
	fwrite(Output2, sizeof(BYTE), ImgSize, fp2);
	fclose(fp2);
	free(Image2);
	free(Output2);

	fp3 = fopen("output3.bmp", "wb");
	fwrite(&hf, sizeof(BYTE), sizeof(BITMAPFILEHEADER), fp3);
	fwrite(&hInfo, sizeof(BYTE), sizeof(BITMAPINFOHEADER), fp3);
	fwrite(hRGB, sizeof(RGBQUAD), 256, fp3);
	fwrite(Output3, sizeof(BYTE), ImgSize, fp3);
	fclose(fp3);
	free(Image3);
	free(Output3);
}