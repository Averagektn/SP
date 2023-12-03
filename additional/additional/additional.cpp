#include <iostream>
#include <vector>
#include <Windows.h>
#include <chrono>

static std::vector<RGBTRIPLE> ReadBMP(const std::string& filename)
{
	std::vector<RGBTRIPLE> pixels;

	HANDLE hFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
		return pixels;
	}

	BITMAPFILEHEADER bmpFileHeader{};
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
		RGBTRIPLE pixel{};

		pixel.rgbtBlue = imageBuffer[i];
		pixel.rgbtGreen = imageBuffer[static_cast<std::vector<BYTE, std::allocator<BYTE>>::size_type>(i) + 1];
		pixel.rgbtRed = imageBuffer[static_cast<std::vector<BYTE, std::allocator<BYTE>>::size_type>(i) + 2];

		pixels.push_back(pixel);
	}

	return pixels;
}

static std::vector<std::vector<RGBTRIPLE>> divideVector(const std::vector<RGBTRIPLE>& pixels, int n)
{
	std::vector<std::vector<RGBTRIPLE>> dividedVectors(n);

	int numPixels = pixels.size();
	int pixelsPerVector = numPixels / n; 
	int startIndex = 0;
	int endIndex = pixelsPerVector;

	for (int i = 0; i < n; i++) 
	{
		dividedVectors[i].insert(dividedVectors[i].end(), pixels.begin() + startIndex, pixels.begin() + endIndex);

		startIndex = endIndex;
		endIndex += pixelsPerVector;
	}

	if (startIndex < numPixels) 
	{
		dividedVectors.back().insert(dividedVectors.back().end(), pixels.begin() + startIndex, pixels.end());
	}

	return dividedVectors;
}

static void CreateBMPFromPixels(const std::vector<RGBTRIPLE>& pixels, int width, int height, LPCWSTR filename)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	LONG size = width * height;

	bfh.bfType = 0x4D42;  
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size * sizeof(RGBTRIPLE); /// 3275658
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 138

	bih.biSize = sizeof(BITMAPINFOHEADER); 
	bih.biWidth = width; 
	bih.biHeight = height; 
	bih.biPlanes = 1; 
	bih.biBitCount = 24;  
	bih.biCompression = BI_RGB; 
	bih.biSizeImage = 0; 
	bih.biXPelsPerMeter = 0; 
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	HANDLE file = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE) 
	{
		std::cerr << "Invalid handle value" << std::endl;
		return;
	}

	DWORD bytesWritten;
	WriteFile(file, &bfh, sizeof(BITMAPFILEHEADER), &bytesWritten, NULL);
	WriteFile(file, &bih, sizeof(BITMAPINFOHEADER), &bytesWritten, NULL);
	
	WriteFile(file, pixels.data(), size * sizeof(RGBTRIPLE), &bytesWritten, NULL);

	CloseHandle(file);
}

int main() 
{
	clock_t start = clock();
	auto startTime = std::chrono::high_resolution_clock::now();

	int n = 10;
	int width = 5184;
	int height = 3456;
	std::string filename = "sample_5184x3456.bmp";

	std::vector<RGBTRIPLE> pixels = ReadBMP(filename);

	std::vector<std::vector<RGBTRIPLE>> data = divideVector(pixels, n);

	for (int i = 0; i < pixels.size(); i++)
	{
		int color = (pixels[i].rgbtBlue + pixels[i].rgbtGreen + pixels[i].rgbtRed) / 3;
		RGBTRIPLE pixel{ color, color, color };

		pixels[i] = pixel;
	}
	
	CreateBMPFromPixels(pixels, width, height, L"single_thread.bmp");

	clock_t end = clock();
	auto endTime = std::chrono::high_resolution_clock::now();
	double cpuTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << cpuTime << std::endl;

	return 0;
}
