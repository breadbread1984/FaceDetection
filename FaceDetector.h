#ifndef FACEDETECTION_H
#define FACEDETECTION_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <dlib/dnn.h>
#include <dlib/data_io.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>

using namespace std;
using namespace cv;
using namespace dlib;

class FaceDetector {
	template <long num_filters, typename SUBNET> using con5d = con<num_filters,5,5,2,2,SUBNET>;
	template <long num_filters, typename SUBNET> using con5  = con<num_filters,5,5,1,1,SUBNET>;
	template <typename SUBNET> using downsampler  = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16,SUBNET>>>>>>>>>;
	template <typename SUBNET> using rcon5  = relu<affine<con5<45,SUBNET>>>;
	using net_type = loss_mmod<con<1,9,9,1,1,rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

	net_type net;
public:
	FaceDetector();
	virtual ~FaceDetector();
	std::vector<Rect> detect(Mat img);
};

#endif

