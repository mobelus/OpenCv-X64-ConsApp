// CannyStill.cpp

// Sample code was taken from
// https://github.com/MicrocontrollersAndMore/OpenCV_3_Windows_10_Installation_Tutorial

/*
Configuration Properties->VC++ Directories
Include Directories = C:\C_Libraries\opencv - 3 - 1\build\include;
Library Directories = C:\C_Libraries\opencv - 3 - 1\build\x64\vc12\lib;
//*/

/*
To enable debugging :

1) Project->HelloWorld Properties
2) "Configuration Properties -> C/C++ -> General"
3) On the right, change "Debug Information Format" to "Program Database For Edit And Continue (/ZI)"
4) "Configuration Properties -> C/C++ -> Optimization"
5) On the right, change "Optimization" to "Disabled (/Od)"
6) "Configuration Properties -> C/C++ -> Linker"
7) On the left, select "Debugging"
8) On the right, change "Generate Debug Info" to "Yes"
9) Click ok
10) Set your breakpoints
11) Rebuild your application

Also when running your application use Ctrl + F5 to build and run it, this keeps the console window open long enough for you to see your output.
//*/

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows

//using namespace cv;
//using namespace std;


static void help()
{
	std::cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
		"Usage:\n"
		"./houghcircles <image_name>, Default is ../data/board.jpg\n" << std::endl;
}

#if 0
int main(int argc, char** argv)
{
	/*
	cv::CommandLineParser parser(argc, argv, "{help h ||}{@image|../data/board.jpg|}");
	
	if (parser.has("help"))
	{
		help();
		return 0;
	}
	*/

}
#endif

bool cvExample_SearchCircles(cv::Mat imgOriginalCopy, cv::Mat &imgFinalResult)
{
	cv::Mat img = imgOriginalCopy;
	if (imgOriginalCopy.empty())
	{
		return false;
	}

	cv::Mat cimg;
	medianBlur(img, imgOriginalCopy, 5);
	cvtColor(imgOriginalCopy, cimg, cv::COLOR_GRAY2BGR);
//	cvtColor(imgOriginalCopy, imgFinalResult, cv::COLOR_GRAY2BGR);
	std::vector<cv::Vec3f> circles;
	HoughCircles(imgOriginalCopy, circles, cv::HOUGH_GRADIENT, 1, 10,
		100, 30, 1, 30 // change the last two parameters
		// (min_radius & max_radius) to detect larger circles
		);

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Vec3i c = circles[i];
		circle(imgFinalResult, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
		circle(imgFinalResult, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
	}


	/*
	cv::Mat img = imgOriginalCopy;
	if (img.empty())
	{return false;}

	cv::Mat cimg;
	medianBlur(img, img, 5);
	cvtColor(img, cimg, cv::COLOR_GRAY2BGR);
	std::vector<cv::Vec3f> circles;
	HoughCircles(img, circles, cv::HOUGH_GRADIENT, 1, 10,
		100, 30, 1, 30 // change the last two parameters
		// (min_radius & max_radius) to detect larger circles
		);

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Vec3i c = circles[i];
		circle(cimg, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
		circle(cimg, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
	}
	*/

	//imshow("detected circles", cimg); cv::waitKey();

	//imgFinalResult = cimg;
	cv::namedWindow("imgCircles", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	cv::imshow("imgCircles", imgFinalResult); cv::waitKey(0);
}



bool cvExample_ShowSomeFunctions(cv::Mat imgOriginalCopy, cv::Mat &imgFinalResult)
{
	cv::Mat imgGrayscale;       // grayscale of input image
	cv::Mat imgBlurred;         // intermediate blured image
	cv::Mat imgCanny;           // Canny edge image

	if (imgOriginalCopy.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return false;                                              // and exit program
	}

	cv::cvtColor(imgOriginalCopy, imgGrayscale, CV_BGR2GRAY);       // convert to grayscale

	cv::GaussianBlur(imgGrayscale,  // input image
		imgBlurred,                 // output image
		cv::Size(5, 5),             // smoothing window width and height in pixels
		1.5);                       // sigma value, determines how much the image will be blurred

	cv::Canny(imgBlurred,           // input image
		//imgCanny,                   // output image
		imgFinalResult,
		100,                        // low threshold
		200);                       // high threshold

	// declare windows
	// CV_WINDOW_AUTOSIZE is the default
	cv::namedWindow("imgOriginalCopy", CV_WINDOW_AUTOSIZE);     // note: you can use CV_WINDOW_NORMAL which allows resizing the window
	cv::imshow("imgOriginalCopy", imgOriginalCopy); cv::waitKey(0); // show window, until user presses a key

	cv::namedWindow("imgGrayscale", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	cv::imshow("imgGrayscale", imgGrayscale); cv::waitKey(0);

	cv::namedWindow("imgBlurred", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	cv::imshow("imgBlurred", imgBlurred); cv::waitKey(0);

	cv::namedWindow("imgCanny", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	//cv::imshow("imgCanny", imgCanny); cv::waitKey(0);
	cv::imshow("imgCanny", imgFinalResult); cv::waitKey(0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	cv::Mat imgOriginal;  // input  image
	cv::Mat imgOriginalCopy;  // input  image
	cv::Mat imgFinal;     // output image

//	imgOriginal = cv::imread("img.jpg");          // open image
//	imgOriginal = cv::imread("..\\..\\pic\\pic.jpg");          // open image
//	imgOriginal = cv::imread("..\\..\\..\\pic\\pic.jpg");          // open image
	imgOriginal = cv::imread("C:\\_WORK_RGS\\MyFiles\\DISSER\\ISTRATOV\\videos\\ConsoleApplicationOpenCV\\pic\\pic.jpg");          // open image

	if (imgOriginal.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}
	else
	{
		imgOriginalCopy = imgOriginal;
	}



	// Exaple Function we will need:
	//cvExample_ShowSomeFunctions(imgOriginal, imgFinal);

	//imgOriginal = imgOriginalCopy;
	cvExample_SearchCircles(imgOriginal, imgFinal);


	// declare windows
	// CV_WINDOW_AUTOSIZE is the default
	cv::namedWindow("imgOriginal", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	cv::imshow("imgOriginal", imgOriginal); cv::waitKey(0);

	cv::namedWindow("imgFinal", CV_WINDOW_AUTOSIZE);        // or CV_WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
	cv::imshow("imgFinal", imgFinal); cv::waitKey(0);
	
	cv::waitKey(0);                 // hold windows open until user presses a key
	return(0);
}
