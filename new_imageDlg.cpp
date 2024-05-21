
// new_imageDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "new_image.h"
#include "new_imageDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include <opencv2/highgui/highgui_c.h>
#include <cmath> 
#include <random>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString filePath,filePath_b; //打开的文件路径
Mat image; //原图像
Mat NextImg; //处理后的图像
Mat saveImg;//保存的图像


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CnewimageDlg 对话框



CnewimageDlg::CnewimageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_IMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnewimageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_showimage, k_image);
	DDX_Control(pDX, IDC_SLIDER1, size_slider);
	DDX_Control(pDX, IDC_SLIDER2, light_slider);
	DDX_Control(pDX, IDC_SLIDER3, cmp_slider);
	DDX_Control(pDX, IDC_SLIDER4, sat_slider);
	DDX_Control(pDX, IDC_SLIDER5, dim_slider);
	DDX_Control(pDX, IDC_SLIDER6, oil_slider);
	DDX_Control(pDX, IDC_SLIDER7, rel_slider);
	DDX_Control(pDX, IDC_SLIDER11, spc_slider);
}

BEGIN_MESSAGE_MAP(CnewimageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CnewimageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CnewimageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CnewimageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CnewimageDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CnewimageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CnewimageDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CnewimageDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON7, &CnewimageDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CnewimageDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CnewimageDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CnewimageDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CnewimageDlg::OnBnClickedButton11)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CnewimageDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CnewimageDlg::OnNMCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &CnewimageDlg::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &CnewimageDlg::OnNMCustomdrawSlider5)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, &CnewimageDlg::OnNMCustomdrawSlider6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, &CnewimageDlg::OnNMCustomdrawSlider7)

	ON_BN_CLICKED(IDC_BUTTON18, &CnewimageDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON14, &CnewimageDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CnewimageDlg::OnBnClickedButton15)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER11, &CnewimageDlg::OnNMCustomdrawSlider11)
	ON_BN_CLICKED(IDC_BUTTON12, &CnewimageDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CnewimageDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON17, &CnewimageDlg::OnBnClickedButton17)
END_MESSAGE_MAP()


// CnewimageDlg 消息处理程序

BOOL CnewimageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//滑动条
	//图片大小调整
	size_slider.SetRange(1, 10);//设置滑动范围
	size_slider.SetTicFreq(0.1);//每一个单位画一刻度
	size_slider.SetPos(5);//设置滑块初始位置
	//亮度调整
	light_slider.SetRange(1, 100);//设置滑动范围
	light_slider.SetTicFreq(10);//每一个单位画一刻度
	light_slider.SetPos(50);//设置滑块初始位置
	//对比度
	cmp_slider.SetRange(1, 100);//设置滑动范围
	cmp_slider.SetTicFreq(10);//每一个单位画一刻度
	cmp_slider.SetPos(50);//设置滑块初始位置
	//饱和度
	sat_slider.SetRange(1, 100);//设置滑动范围
	sat_slider.SetTicFreq(10);//每一个单位画一刻度
	sat_slider.SetPos(50);//设置滑块初始位置
	//模糊度调整
	dim_slider.SetRange(1, 11);//设置滑动范围
	dim_slider.SetTicFreq(2);//每一个单位画一刻度
	dim_slider.SetPos(1);//设置滑块初始位置
	//油画效果
	oil_slider.SetRange(1, 11);//设置滑动范围
	oil_slider.SetTicFreq(2);//每一个单位画一刻度
	oil_slider.SetPos(1);//设置滑块初始位置
	//浮雕效果
	rel_slider.SetRange(0, 10);//设置滑动范围
	rel_slider.SetTicFreq(1);//每一个单位画一刻度
	rel_slider.SetPos(0);//设置滑块初始位置
	//椒盐噪声调整
	spc_slider.SetRange(0, 1000);//设置滑动范围
	spc_slider.SetTicFreq(100);//每一个单位画一刻度
	spc_slider.SetPos(0);//设置滑块初始位置

	//图片显示
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_showimage)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CnewimageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

Mat CnewimageDlg::GetSrcImage(bool showMessage)
{
	Mat srcImage = NextImg;
	//Mat bgImage = 
	if (srcImage.empty())
	{
		srcImage = image;
		if (srcImage.empty())
		{
			if (showMessage == true)
				MessageBox(_T("请先打开图像！！！"));
			return srcImage;
		}
	}
	return srcImage;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


//当图片缩小时，扩充白色底片
void CnewimageDlg::pasteImage(cv::Mat& background, const cv::Mat& image) {
	// 确定底片和图像的尺寸
	int backgroundWidth = background.cols;
	int backgroundHeight = background.rows;
	int imageWidth = image.cols;
	int imageHeight = image.rows;

	// 计算粘贴位置
	int pasteX = (backgroundWidth - imageWidth) / 2;
	int pasteY = (backgroundHeight - imageHeight) / 2;

	Rect rect = cv::Rect(pasteX, pasteY, min(backgroundWidth - 2, imageWidth), min(backgroundHeight - 2, imageHeight));

	// 将图像粘贴在中间
	image.copyTo(background(rect));


	// 将结果复制到背景图像中
	background.copyTo(background);
}


void CnewimageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CnewimageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开图片
void CnewimageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	filePath = _T("");
	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*||");//可以打开BMP	、JPG、PNG格式的文件
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK) {
		//读取图像文件名
		filePath = dlgFileOpenImg.GetPathName();
	}
	else {
		return;
	}

	//CString to string  string s(CString.GetBuffer());
	string picpath = filePath.GetBuffer(0);

	image = imread(picpath);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(image, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);

}

//退出函数
void CnewimageDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT i;
	i = MessageBox(TEXT("确认要退出程序吗？"), TEXT("温馨提示"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}
	CDialogEx::OnOK();
}

//转灰度图
void CnewimageDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	cvtColor(image, NextImg, COLOR_BGR2GRAY);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
}


void CnewimageDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	// 读取彩色图片
	Mat src = image;
	if (src.empty())
	{
		return;
	}
	vector<Mat> bgr_planes;
	// 图像RGB颜色通道分离
	split(src, bgr_planes);
	// 将直方图像素值分为多少个区间/直方图有多少根柱子
	int histSize = 256;
	// 256不会被使用
	float range[] = { 0, 256 };
	const float* histRange = { range };
	// 一些默认参数，一般不变
	bool uniform = true, accumulate = false;
	Mat b_hist, g_hist, r_hist;
	// 参数依次为：
	// 输入图像: &bgr_planes[0]
	// 输入图像个数：1
	// 使用输入图像的第几个通道：0
	// 掩膜：Mat()
	// 直方图计算结果：b_hist，b_hist存储histSize个区间的像素值个数
	// 直方图维度：1
	// 直方图像素值范围分为多少区间（直方图条形个数）：256
	// 是否对得到的直方图数组进行归一化处理；uniform
	// 当输入多个图像时，是否累积计算像素值的个数accumulate
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// b_hist表示每个像素范围的像素值个数，其总和等于输入图像长乘宽。
	// 如果要统计每个像素范围的像素值百分比，计算方式如下
	// b_hist /= (float)(cv::sum(b_hist)[0]);
	// g_hist /= (float)(cv::sum(g_hist)[0]);
	// r_hist /= (float)(cv::sum(r_hist)[0]);

	/* 以下的参数都是跟直方图展示有关，c++展示图片不那么容易*/
	// 一些绘图参数
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	// 创建一张黑色背景图像，用于展示直方图绘制结果
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	// 将直方图归一化到0到histImage.rows，最后两个参数默认就好。
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		//遍历hist元素（注意hist中是float类型）
		// 绘制蓝色分量
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		// 绘制绿色分量
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		// 绘制红色分量
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("dst image", histImage);
	waitKey(0);
	destroyAllWindows();
}

//展示灰度直方图

void CnewimageDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat image_gray, hist;   //定义输入图像，灰度图像, 直方图
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;
	if (srcImage.type() == CV_8UC1)
	{
		image_gray = srcImage;
	}
	else
	{
		cvtColor(NextImg, image_gray, COLOR_BGR2GRAY);  //灰度化
	}

	//获取图像直方图
	int histsize = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
	calcHist(&image_gray, 1, 0, Mat(), hist, 1, &histsize, &histRanges, true, false);

	//创建直方图显示图像
	int hist_h = 300;//直方图的图像的高
	int hist_w = 512; //直方图的图像的宽
	int bin_w = hist_w / histsize;//直方图的等级
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));//绘制直方图显示的图像

	//绘制并显示直方图
	normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化直方图
	for (int i = 1; i < histsize; i++)
	{
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("histImage", histImage);

	waitKey(0);  //暂停，保持图像显示，等待按键结束
}

//直方图均衡化,同时实现了对灰度图像及彩色图像均可进行处理
Mat histogramEqualization(const cv::Mat& image) {
	cv::Mat equalizedImage;

	if (image.channels() == 1) {
		// 灰度图像
		cv::equalizeHist(image, equalizedImage);
	}
	else if (image.channels() == 3) {
		// 彩色图像
		std::vector<cv::Mat> channels;
		cv::split(image, channels); // 分离通道

		// 对每个通道分别进行直方图均衡化
		for (int i = 0; i < 3; ++i) {
			cv::equalizeHist(channels[i], channels[i]);
		}

		// 合并通道
		cv::merge(channels, equalizedImage);
	}

	return equalizedImage;
}


void CnewimageDlg::OnBnClickedButton11()
{

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	//// 灰度图像直方图均衡化
	//cv::Mat grayImage;
	//cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); // 转换为灰度图像
	//cv::Mat equalizedGrayImage = histogramEqualization(grayImage);

	// 彩色图像直方图均衡化
	cv::Mat equalizedColorImage = histogramEqualization(srcImage);

	NextImg = equalizedColorImage;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
}

void CnewimageDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	NextImg = image;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(image, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
}

Mat cropCenter(cv::Mat& src, int targetWidth, int targetHeight) {
	// 获取原始图像的大小
	int srcWidth = src.cols;
	int srcHeight = src.rows;

	// 计算裁剪的起始坐标
	int startX = (srcWidth - targetWidth) / 2;
	int startY = (srcHeight - targetHeight) / 2;

	// 裁剪图像
	cv::Rect roi(startX, startY, targetWidth, targetHeight);
	cv::Mat croppedImage = src(roi).clone(); // 使用 clone() 复制图像区域

	return croppedImage;
}
//调整图像大小
void CnewimageDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	// 获取滑动条当前值
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int sliderValue = pSlider->GetPos();

	double scaleFactor = sliderValue / 5.0;


	// 计算调整后的图像大小
	cv::Size newSize(srcImage.cols * scaleFactor, srcImage.rows * scaleFactor);

	// 调整图像大小
	cv::Mat resizedImage;
	cv::resize(srcImage, resizedImage, newSize);

	// 显示调整后的图像
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);

	//cv::Size maxSize(srcImage.cols * scaleFactor, srcImage.rows * 2);

	// 创建白色底片 确保白色图片是原图的2倍
	Mat whiteBackground(rect.Height(), rect.Width(), CV_8UC3, cv::Scalar(255, 255, 255));

	if (sliderValue < 5)
	{
		// 粘贴图像
		pasteImage(whiteBackground, resizedImage);
	}
	else if (sliderValue == 5)
	{
		return;
	}
	else
	{
		whiteBackground = cropCenter(resizedImage, srcImage.cols, srcImage.rows);
	}

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(whiteBackground, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);

	*pResult = 0;
	//放大功能未实现，且滑动条处于5时，也进行了底片填充，且没有实现图片保存NextImg(或者可以考虑保存在view路径中)
}

//图片旋转
void Rotate(const Mat& srcImage, Mat& destImage, double angle)
{
	Point2f center(srcImage.cols / 2, srcImage.rows / 2);//中心
	Mat M = getRotationMatrix2D(center, angle, 1);//计算旋转的仿射变换矩阵 
	warpAffine(srcImage, destImage, M, Size(srcImage.cols, srcImage.rows));//仿射变换  
	circle(destImage, center, 2, Scalar(255, 0, 0));
}

//v2:没有调用函数
void RotImage(const Mat& srcImage, Mat& dstImage, double angle)
{
	//弧度
	double sita = angle * CV_PI / 180;
	double a = (srcImage.cols - 1) / 2.0 + 0.5;
	double b = (srcImage.rows - 1) / 2.0 + 0.5;

	int nRowNum = srcImage.rows;
	int nColNum = srcImage.cols;
	dstImage.create(nRowNum, nColNum, srcImage.type());

	double f1 = -a * cos(sita) + b * sin(sita) + a;
	double f2 = -a * sin(sita) - b * cos(sita) + b;

	for (int i = 0; i < nRowNum; i++)
	{
		for (int j = 0; j < nColNum; j++)
		{
			int x = cvRound(j * cos(sita) - i * sin(sita) + f1);
			int y = cvRound(j * sin(sita) + i * cos(sita) + f2);
			if (x > 0 && x < nColNum && y > 0 && y < nRowNum)
			{
				dstImage.at<Vec3b>(i, j) = srcImage.at<Vec3b>(y, x);
			}
		}
	}
}

//顺时针旋转
void CnewimageDlg::OnBnClickedButton7()
{
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;


	double angle = -90;//角度
	Rotate(srcImage, NextImg, angle);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	//image = NextImg;
}

//逆时针旋转
void CnewimageDlg::OnBnClickedButton8()
{
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;


	double angle = 90;//角度
	Rotate(srcImage, NextImg, angle);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	//image = NextImg;
}

//图片对称
Mat symmetricImage(const cv::Mat& image, bool horizontal)
{
	cv::Mat symmetricImg;
	if (horizontal) {
		// 水平对称
		cv::flip(image, symmetricImg, 1);
	}
	else {
		// 垂直对称
		cv::flip(image, symmetricImg, 0);
	}
	return symmetricImg;
}

//水平对称
void CnewimageDlg::OnBnClickedButton9()
{
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;


	// 水平对称
	Mat horizontalSymmetric = symmetricImage(srcImage, true);

	NextImg = horizontalSymmetric;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	//image = NextImg;
	// 垂直对称
	/*cv::Mat verticalSymmetric = symmetricImage(image, false);*/
}


void CnewimageDlg::OnBnClickedButton10()
{
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	// 垂直对称
	cv::Mat verticalSymmetric = symmetricImage(srcImage, false);

	NextImg = verticalSymmetric;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	//image = NextImg;
}

//调整亮度

Mat adjustBrightness(const cv::Mat& srcimage, double brightnessScale)
{
	Mat brightenedImage;

	// 将输入图像乘以亮度调整比例，结果存储在brightenedImage
	image.convertTo(brightenedImage, -1, brightnessScale, 0);

	return brightenedImage;
}

void CnewimageDlg::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
	int sliderValue2 = pSlider->GetPos();//滑动条的值
	double brightnessScale = sliderValue2 / 50.0;

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;


	// 调整亮度
	Mat brightenedImage = adjustBrightness(srcImage, brightnessScale);
	//NextImg = brightenedImage;
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(brightenedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;

}

//调整对比度 对比度的调整怎么跟亮度一样
Mat adjustContrast(const Mat& srcimage, double contrastScale)
{
	Mat contrastedImage;

	// 将输入图像乘以对比度调整比例，结果存储在contrastedImage
	srcimage.convertTo(contrastedImage, -1, contrastScale, 0);

	return contrastedImage;
}

void CnewimageDlg::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER3);
	int sliderValue = pSlider->GetPos();//滑动条的值
	double contrastScale = sliderValue / 50.0;

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;


	// 调整对比度
	Mat contrastedImage = adjustContrast(srcImage, contrastScale);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(contrastedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;
}

//调整饱和度
Mat adjustSaturation(const cv::Mat& image, double saturationFactor) {
	cv::Mat saturatedImage;

	// 将图像从BGR颜色空间转换为HSV颜色空间
	cv::cvtColor(image, saturatedImage, cv::COLOR_BGR2HSV);

	// 将饱和度通道乘以饱和度调整因子
	for (int i = 0; i < saturatedImage.rows; ++i) {
		for (int j = 0; j < saturatedImage.cols; ++j) {
			saturatedImage.at<cv::Vec3b>(i, j)[1] *= saturationFactor;
		}
	}

	// 将图像从HSV颜色空间转换回BGR颜色空间
	cv::cvtColor(saturatedImage, saturatedImage, cv::COLOR_HSV2BGR);

	return saturatedImage;
}

void CnewimageDlg::OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER4);
	int sliderValue = pSlider->GetPos();//滑动条的值
	double contrastScale = sliderValue / 50.0;

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	//调整饱和度
	Mat saturatedImage = adjustSaturation(srcImage, contrastScale);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(saturatedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;
}

//模糊度调整
Mat adjustBlur(const cv::Mat& srcimage, int blurAmount)
{
	Mat blurredImage;

	// 使用高斯滤波来实现模糊效果
	GaussianBlur(srcimage, blurredImage, cv::Size(blurAmount, blurAmount), 0);

	return blurredImage;
}

void CnewimageDlg::OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER5);
	int sliderValue = pSlider->GetPos();//滑动条的值

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	//调整模糊度
	Mat blurredImage = adjustBlur(srcImage, sliderValue);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(blurredImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;
}

//油画效果 与intensity无关了
Mat adjustOilPainting(const cv::Mat& srcimage, int radius)
{
	cv::Mat oilPaintedImage;

	// 应用均值迁移滤波器来实现油画效果
	cv::medianBlur(srcimage, oilPaintedImage, radius);

	// 通过调整像素值来增强油画效果
	cv::Mat mask;
	cv::cvtColor(srcimage, mask, cv::COLOR_BGR2GRAY);
	cv::threshold(mask, mask, 245, 255, cv::THRESH_BINARY_INV);

	cv::Mat output;
	oilPaintedImage.copyTo(output);
	cv::bitwise_and(oilPaintedImage, oilPaintedImage, output, mask);
	cv::bitwise_not(mask, mask);
	cv::add(srcimage, output, output, mask);

	return output;
}

void CnewimageDlg::OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER6);
	int sliderValue = pSlider->GetPos();//滑动条的值

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	//调整油画滤镜
	int radius = sliderValue;  // 油画效果的半径，试着改变这个值以调整效果
	cv::Mat oilPaintedImage = adjustOilPainting(srcImage, radius);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(oilPaintedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;
}

//浮雕效果
Mat adjustEmbossing(const cv::Mat& image, double strength)
{
	cv::Mat grayImage;
	if (image.channels() == 3) {
		cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY); // 如果是彩色图像，转换为灰度图像
	}
	else {
		grayImage = image.clone(); // 如果是灰度图像，直接复制
	}

	// 定义浮雕卷积核
	cv::Mat embossKernel = (cv::Mat_<float>(3, 3) <<
		-2 * strength, -strength, 0,
		-strength, 1, strength,
		0, strength, 2 * strength);

	// 对灰度图像应用卷积核
	cv::Mat embossedImage;
	cv::filter2D(grayImage, embossedImage, CV_8U, embossKernel);

	// 如果输入图像是灰度图像，则直接返回浮雕后的图像；否则将灰度图像转换为彩色图像
	if (image.channels() == 1) {
		return embossedImage;
	}
	else {
		cv::Mat embossedColorImage;
		cv::cvtColor(embossedImage, embossedColorImage, cv::COLOR_GRAY2BGR);
		return embossedColorImage;
	}
}

void CnewimageDlg::OnNMCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER7);
	int sliderValue = pSlider->GetPos();//滑动条的值

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	// 调整浮雕效果
	double strength = sliderValue / 10.0;  // 浮雕效果的强度，可调整
	cv::Mat embossedImage = adjustEmbossing(srcImage, strength);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(embossedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;

	*pResult = 0;
}


//边缘锐化
void CnewimageDlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	Mat blur;
	GaussianBlur(srcImage, blur, Size(0, 0), 25);
	addWeighted(srcImage, 1.5, blur, -0.5, 0, NextImg);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(NextImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
}

//空域滤波去噪 高斯滤波
Mat gaussianFilter(const cv::Mat& srcimage, int kernel_size, double sigma) 
{
	cv::Mat filteredImage;
	cv::GaussianBlur(srcimage, filteredImage, cv::Size(kernel_size, kernel_size), sigma);
	return filteredImage;
}

void CnewimageDlg::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	Mat gaussianFilteredImage = gaussianFilter(srcImage, 5, 1.5);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(gaussianFilteredImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
}

//频域滤波去噪 高通滤波器

Mat highPassFilterDenoising(const cv::Mat& image, double sigma) {
	// 高斯模糊
	cv::Mat blurred;
	cv::GaussianBlur(image, blurred, cv::Size(0, 0), sigma);

	// 高通滤波器 = 原始图像 - 模糊图像
	cv::Mat highPass = image - blurred;

	// 原始图像 + 高通滤波器
	cv::Mat denoised = image + highPass;

	return denoised;
}

void CnewimageDlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	double sigma = 3.0;  // 高斯模糊的标准差

	// 高斯高通滤波器去噪
	cv::Mat denoisedImage = highPassFilterDenoising(srcImage, sigma);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(denoisedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
}

//椒盐噪声
Mat AddJiaoyanNoise(Mat img, double SNR) {

	Mat dstImage = img.clone();
	for (int k = 0; k < SNR; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//盐噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < SNR; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//椒噪声
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;


}

void CnewimageDlg::OnNMCustomdrawSlider11(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER11);
	int sliderValue = pSlider->GetPos();//滑动条的值

	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;
	int snr = sliderValue;
	//椒盐噪声
	Mat spicedImg= AddJiaoyanNoise(srcImage, snr);

	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(spicedImg, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
	saveImg = imagedst;
	*pResult = 0;
}
//拼图效果

void CnewimageDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	Mat border;
	filePath_b = _T("");
	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*||");//可以打开BMP	、JPG、PNG格式的文件
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK) {
		//读取图像文件名
		filePath_b = dlgFileOpenImg.GetPathName();
	}
	else {
		return;
	}

	//CString to string  string s(CString.GetBuffer());
	string picpath_b = filePath_b.GetBuffer(0);

	border = imread(picpath_b);

	cv::resize(border, border, srcImage.size());
	cv::Mat hConcatenatedImage;
	cv::hconcat(border, srcImage, hConcatenatedImage);	
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(hConcatenatedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);

}

//叠加效果
void CnewimageDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImage = GetSrcImage(false);
	if (srcImage.empty())return;

	Mat border;
	filePath_b = _T("");
	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("ALLSUPORTFILE(*.*)|*.*||");//可以打开BMP	、JPG、PNG格式的文件
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK) {
		//读取图像文件名
		filePath_b = dlgFileOpenImg.GetPathName();
	}
	else {
		return;
	}

	//CString to string  string s(CString.GetBuffer());
	string picpath_b = filePath_b.GetBuffer(0);

	border = imread(picpath_b);

	cv::resize(border, border, srcImage.size());
	double alpha = 0.5; // 第一张图像的权重
	double beta = 1.0 - alpha; // 第二张图像的权重

	// 叠加两张图像
	cv::Mat blendedImage;
	cv::addWeighted(border, alpha, srcImage, beta, 0.0, blendedImage);
	Mat imagedst;
	//以下操作获取图形控件尺寸并以此改变图片尺寸  
	CRect rect;
	GetDlgItem(IDC_showimage)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(blendedImage, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);

}

//保存图片


void CnewimageDlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* bmpShow = GetDlgItem(IDC_showimage);
	CDC* pdc = bmpShow->GetDC();
	CImage  imag;
	CRect rect;

	GetClientRect(&rect);        //获取画布大小
	bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

	TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤
	// 构造保存文件对话框    
	CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("保存图片");  //保存对话窗口标题名
	CString picturePath;
	if (IDOK == fileDlg.DoModal())  //按下确认键
	{
		picturePath = fileDlg.GetPathName();  //文件路径
	}

	HRESULT hResult = imag.Save(picturePath); //保存图片
	ReleaseDC(pdc);
	imag.ReleaseDC();

}
