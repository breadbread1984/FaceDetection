#include <cstdlib>
#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/opencv.hpp>
#include "FaceDetector.h"

using namespace std;
using namespace boost::program_options;
using namespace cv;

int main(int argc,char ** argv)
{
	options_description desc;
	string input;
	string output;
	desc.add_options()
		("help,h","print current message")
		("input,i",value<string>(&input),"input image")
		("output,o",value<string>(&output)->default_value("output.png"),"output image");
	variables_map vm;
	store(parse_command_line(argc,argv,desc),vm);
	notify(vm);

	if(0 != vm.count("help")) {
		cout<<desc;
		return EXIT_SUCCESS;
	}
	FaceDetector fd;
	if(0 != vm.count("input")) {
		Mat img = imread(input);
		if(img.empty()) {
			cout<<"invalid image"<<endl;
			return EXIT_FAILURE;
		}
		std::vector<Rect> faces = fd.detect(img);
		for(auto & face : faces) 
			cv::rectangle(img,face,Scalar(0,0,255),img.cols / 100);
		imwrite(output,img);
		return EXIT_SUCCESS;
	}

	VideoCapture vc(0);
	namedWindow("faces");
	Mat img;
	while(vc.read(img)) {
		std::vector<Rect> faces = fd.detect(img);
		for(auto & face : faces)
			cv::rectangle(img,face,Scalar(0,0,255),img.cols / 100);
		cout<<faces.size()<<endl;
		imshow("faces",img);
		char k = waitKey(1);
		if('q' == k) break;
	}

	return EXIT_SUCCESS;
}

