// �������ƣ���������������Դ��ʽ����� mp3 ����
 // ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
 // �������ߣ�yangw80 <yw80@qq.com>
 // ����޸ģ�2011-10-7
 //
#include <graphics.h>
#include <conio.h> 
#include <stdio.h>
//#pragma comment(lib, "Winmm.lib")    // ���� Windows Multimedia API
// #include "resource.h"     // ע�������Դ ID Ϊ�궨�壬��ȡ������ע��

//////////////////////////////////////////////////////////////////
// ��ȡָ��ģ���е���Դ�ļ�
// ������
 //     strDstFile:     Ŀ���ļ�������ȡ����Դ�����������
 //     strResType:     ��Դ���ͣ�
 //     strResName:     ��Դ���ƣ�
 // ����ֵ��
 //     true: ִ�гɹ���
 //     false: ִ��ʧ�ܡ�
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// �����ļ�
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// д���ļ�
	DWORD dwWrite = 0; // ����д���ֽ�
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}


// ������
void main()
{
	// ��ʼ��ͼ�δ���
	initgraph(640, 480);

	// �����ʾ��Ϣ
	outtextxy(0, 0, _T("���������ʼ����"));
	_getch();

	// ������ʱ�ļ����ļ���
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat(tmpmp3, _T("10215.mp3"));     // VC2008��VC2010 ���� _tcscat_s ����

		// �� MP3 ��Դ��ȡΪ��ʱ�ļ�
	ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
	// ע����� MP3 ��Դ�� ID Ϊ�� IDR_BACKGROUND����������
		// ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_BACKGROUND));

		// ������
	TCHAR mcicmd[300];
	_stprintf(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);     // VC2008��VC2010 ���� _stprintf_s ����
	mciSendString(mcicmd, NULL, 0, NULL);

	// ��������
	mciSendString(_T("play mymusic"), NULL, 0, NULL);

	// �����ʾ��Ϣ
	outtextxy(0, 0, _T("�������ֹͣ����"));
	_getch();

	// ֹͣ���Ų��ر�����
	mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	mciSendString(_T("close mymusic"), NULL, 0, NULL);

	// ɾ����ʱ�ļ�
	DeleteFile(tmpmp3);

	// �����ʾ��Ϣ
	outtextxy(0, 0, _T("��������˳�����"));
	_getch();

	// �ر�ͼ�δ���
	closegraph();
}