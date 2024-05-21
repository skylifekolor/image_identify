
// new_imageDlg.h: 头文件
//

#pragma once


// CnewimageDlg 对话框
class CnewimageDlg : public CDialogEx
{
	// 构造
public:
	CnewimageDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_IMAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	Mat GetSrcImage(bool showMessage);
	afx_msg
		void pasteImage(cv::Mat& background, const cv::Mat& image);
	//void pasteAndCropImage(cv::Mat& background, const cv::Mat& image);
	void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic k_image;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	CSliderCtrl size_slider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	CSliderCtrl light_slider;
	afx_msg void OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl cmp_slider;
	afx_msg void OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl sat_slider;
	afx_msg void OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl dim_slider;
	afx_msg void OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl oil_slider;
	afx_msg void OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl rel_slider;
	afx_msg void OnNMCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl old_slider;
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	CSliderCtrl gauss_slider;
	CSliderCtrl spc_slider;
	afx_msg void OnNMCustomdrawSlider11(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton17();
};
