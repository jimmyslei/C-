// 程序名称：范例：播放以资源形式保存的 mp3 音乐
 // 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
 // 作　　者：yangw80 <yw80@qq.com>
 // 最后修改：2011-10-7
 //
#include <graphics.h>
#include <conio.h> 
#include <stdio.h>
//#pragma comment(lib, "Winmm.lib")    // 引用 Windows Multimedia API
// #include "resource.h"     // 注：如果资源 ID 为宏定义，请取消这行注释

//////////////////////////////////////////////////////////////////
// 提取指定模块中的资源文件
// 参数：
 //     strDstFile:     目标文件名。提取的资源将保存在这里；
 //     strResType:     资源类型；
 //     strResName:     资源名称；
 // 返回值：
 //     true: 执行成功；
 //     false: 执行失败。
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}


// 主函数
void main()
{
	// 初始化图形窗口
	initgraph(640, 480);

	// 输出提示信息
	outtextxy(0, 0, _T("按任意键开始播放"));
	_getch();

	// 产生临时文件的文件名
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat(tmpmp3, _T("10215.mp3"));     // VC2008、VC2010 请用 _tcscat_s 函数

		// 将 MP3 资源提取为临时文件
	ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
	// 注：如果 MP3 资源的 ID 为宏 IDR_BACKGROUND，这样做：
		// ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_BACKGROUND));

		// 打开音乐
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);     // VC2008、VC2010 请用 _stprintf_s 函数
	mciSendString(mcicmd, NULL, 0, NULL);

	// 播放音乐
	mciSendString(_T("play mymusic"), NULL, 0, NULL);

	// 输出提示信息
	outtextxy(0, 0, _T("按任意键停止播放"));
	_getch();

	// 停止播放并关闭音乐
	mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	mciSendString(_T("close mymusic"), NULL, 0, NULL);

	// 删除临时文件
	DeleteFile(tmpmp3);

	// 输出提示信息
	outtextxy(0, 0, _T("按任意键退出程序"));
	_getch();

	// 关闭图形窗口
	closegraph();
}