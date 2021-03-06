#include "CameraPerspective.h"
#include "CameraEnvironmental.h"

#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"
#include "PrimDisc.h"

Mat RenderFrame(ICamera& camera)
{
	// scene objects
	
	CPrimSphere s1(Vec3f(-2, 1.7f, 0), 2);
    CPrimSphere s2(Vec3f(1, -1, 1), 2.2f);
	CPrimSphere s3(Vec3f(3, 0.8f, -2), 2);
	CPrimPlane p1(Vec3f(0, -1, 0), Vec3f(0, 1, 0));

	// Add disc primitive here
    //CPrimDisc s1(Vec3f(-2, 1.7f, 0), Vec3f(0, 1, 0), 2);

	CPrimTriangle t1(Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2));
	CPrimTriangle t2(Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3));
	
	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray

	// colors
	const auto background = RGB(0, 0, 0); // background color
	const auto red = RGB(1, 0, 0); // s1
	const auto green = RGB(0, 1, 0); // s2
	const auto blue = RGB(0, 0, 1); // s3
	const auto yellow = RGB(1, 1, 0); // p1
	const auto cyan = RGB(0, 1, 1); // t1
	const auto white = RGB(1, 1, 1); // t2

	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {

            camera.InitRay(ray, x, y);
            img.at<Vec3f>(y, x) = background;
            if (s1.intersect(ray)) {
                img.at<Vec3f>(y, x) = red;
            }
            if (s2.intersect(ray)) {
                img.at<Vec3f>(y, x) = green;
            }
            if (s3.intersect(ray)) {
                img.at<Vec3f>(y, x) = blue;
            }
            if (p1.intersect(ray)) {
                img.at<Vec3f>(y, x) = yellow;
            }
            if (t1.intersect(ray)) {
                img.at<Vec3f>(y, x) = cyan;
            }
            if (t2.intersect(ray)) {
                img.at<Vec3f>(y, x) = white;
            }
			// img.at<Vec3f>(y, x) = col; // store pixel color
		}
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(1000, 800);
	// render three images with different camera settings
	
	CCameraPerspective cam1(resolution, Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60);
	Mat img1 = RenderFrame(cam1);
	imwrite("perspective1.jpg", img1);
	
	CCameraPerspective cam2(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45);
	Mat img2 = RenderFrame(cam2);
	imwrite("perspective2.jpg", img2);
	
	CCameraPerspective cam3(resolution, Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45);
	Mat img3 = RenderFrame(cam3);
	imwrite("perspective3.jpg", img3);

	// Add Environmental camera here as cam4
    CCameraEnvironmental cam4(resolution, Vec3f(-8, 3, 8), 45);
	Mat img4 = RenderFrame(cam4);
	imwrite("environmental4.jpg", img4);

	return 0;
}