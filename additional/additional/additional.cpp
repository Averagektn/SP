#include <iostream>
#include <vector>
#include <Windows.h>

std::vector<RGBQUAD> ReadBMP(const std::string& filename)
{
	std::vector<RGBQUAD> pixels;

	HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
		return pixels;
	}

	BITMAPFILEHEADER bmpFileHeader;
	DWORD bytesRead;
	if (!ReadFile(hFile, &bmpFileHeader, sizeof(BITMAPFILEHEADER), &bytesRead, NULL) || bytesRead != sizeof(BITMAPFILEHEADER)) 
	{
		std::cerr << "Incorrect file header: " << filename << std::endl;
		CloseHandle(hFile);
		return pixels;
	}

	if (bmpFileHeader.bfType != 0x4D42)
	{
		std::cerr << "Incorrect file format: " << filename << std::endl;
		CloseHandle(hFile);
		return pixels;
	}

	BITMAPINFOHEADER bmpInfoHeader;
	if (!ReadFile(hFile, &bmpInfoHeader, sizeof(BITMAPINFOHEADER), &bytesRead, NULL) || bytesRead != sizeof(BITMAPINFOHEADER)) 
	{
		std::cerr << "Unable to read data: " << filename << std::endl;
		CloseHandle(hFile);
		return pixels;
	}

	if (bmpInfoHeader.biBitCount != 24) 
	{
		std::cerr << "Image format is not supported: " << filename << std::endl;
		CloseHandle(hFile);
		return pixels;
	}

	DWORD imageSize = bmpInfoHeader.biSizeImage;
	if (imageSize == 0) 
	{
		imageSize = bmpFileHeader.bfSize - bmpFileHeader.bfOffBits;
	}

	std::vector<BYTE> imageBuffer(imageSize);

	if (!ReadFile(hFile, imageBuffer.data(), imageSize, &bytesRead, NULL) || bytesRead != imageSize) {
		std::cerr << "Unable to read image pixels: " << filename << std::endl;
		CloseHandle(hFile);
		return pixels;
	}

	CloseHandle(hFile);

	for (INT i = 0; i < imageSize; i += 3) 
	{
		RGBQUAD pixel{};

		pixel.rgbBlue = imageBuffer[i];
		pixel.rgbGreen = imageBuffer[i + 1];
		pixel.rgbRed = imageBuffer[i + 2];
		pixels.push_back(pixel);
	}

	return pixels;
}

int main() 
{
	std::string filename = "sample.bmp";
	std::vector<RGBQUAD> pixels = ReadBMP(filename);

	if (!pixels.empty()) {
		std::cout << "Read " << pixels.size() << " pixels from file: " << filename << std::endl;
	}

	return 0;
}
