#include "FaceDetector.h"

FaceDetector::FaceDetector()
{
	deserialize("models/mmod_human_face_detector.dat") >> net;
}

FaceDetector::~FaceDetector()
{
}

std::vector<Rect> FaceDetector::detect(Mat img)
{
	dlib::cv_image<dlib::bgr_pixel> cimg(img);
	dlib::matrix<dlib::rgb_pixel> pyr;
	dlib::assign_image(pyr,cimg);
	int scale = 1;
	while(pyr.size() < 1800 * 1800) {
		pyramid_up(pyr);
		scale *= 2;
	}
	auto dets = net(pyr);
	std::vector<Rect> faces;
	for(auto & d : dets) {
		dlib::point tl = d.rect.tl_corner();
		long width = d.rect.width();
		long height = d.rect.height();
		Rect face(tl.x() / scale,tl.y() / scale,width / scale, height / scale);
		faces.push_back(face);
	}
	return faces;
}

