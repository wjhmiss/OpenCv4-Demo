﻿#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	//【1】载入原始图和Mat变量定义   
	Mat srcImage = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图
	Mat midImage, dstImage;//临时变量和目标图的定义

	//【2】进行边缘检测和转化为灰度图
	Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测
	// opencv3：CV_GRAY2BGR
	// opencv4：COLOR_GRAY2BGR
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

	//【3】进行霍夫线变换
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	//【4】依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		// opencv3：CV_AA
		// opencv4：LINE_AA
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 2, LINE_AA);
	}

	//【5】显示原始图  
	imshow("【原始图】", srcImage);

	//【6】边缘检测后的图 
	imshow("【边缘检测后的图】", midImage);

	//【7】显示效果图  
	imshow("【C++ 效果图】", dstImage);

	waitKey(0);
	return 0;
}
