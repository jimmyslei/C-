#pragma once
#include <graphics.h>
#include <stdio.h>
#define PIC_WIDTH 1200
#define PIC_HEIGHT 750

void logicFunction();
void RendererRipple();

IMAGE res_img;
IMAGE process_img(PIC_WIDTH, PIC_HEIGHT);
DWORD *img_ptr1;
DWORD *img_ptr2;

short * buf = new short[PIC_HEIGHT* PIC_WIDTH + PIC_WIDTH];
short * buf2 = new short[PIC_HEIGHT* PIC_WIDTH + PIC_WIDTH];

void ThrowStone(int x, int y, int stonesize, int stonestrength) {
	if ((x >= PIC_WIDTH - stonesize) || (x < stonesize) ||
		(y >= PIC_HEIGHT - stonesize) || (y < stonesize)) {
		return;
	}

	for (int posx = x - stonesize; posx < x + stonesize; posx++)
	{
		for (int posy = y - stonesize; posy < y + stonesize; posy++)
		{
			if ((posx - x)*(posx - x) + (posy - y)*(posy - y) < stonesize*stonesize)
			{
				buf[PIC_WIDTH *posy + posx] += stonestrength;
			}
		}
	}
}

void NextAmplitude() {
	for (int i = PIC_WIDTH; i < PIC_HEIGHT*(PIC_WIDTH - 1); i++)
	{
		buf2[i] = ((buf[i - PIC_WIDTH] + buf[i + PIC_WIDTH] + buf[i - 1] + buf[i + 1]) >> 1) - buf2[i];
		buf2[i] -= buf2[i] >> 5;
	}

	short *ptmp = buf;
	buf = buf2;
	buf2 = ptmp;
}

void logicFunction() {
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();

		if (msg.uMsg == WM_MOUSEMOVE)
		{
			ThrowStone(msg.x, msg.y, 3, 256);
		}
		else if (msg.uMsg == WM_LBUTTONDOWN) {
			ThrowStone(msg.x, msg.y, 3, 2560);
		}

		FlushMouseMsgBuffer();
	}
	NextAmplitude();
}

void RendererRipple() {
	int i = 0;
	for (int y = 0; y < PIC_HEIGHT; y++)
	{
		for (int x = 0; x < PIC_WIDTH; x++)
		{
			short data = 1024 - buf[i];

			int a = ((x - PIC_WIDTH / 2)*data / 1024) + PIC_WIDTH / 2;
			int b = ((y - PIC_HEIGHT / 2)*data / 1024) + PIC_HEIGHT / 2;

			if (a >= PIC_WIDTH)
			{
				a = PIC_WIDTH - 1;
			}
			if (a < 0)
			{
				a = 0;
			}
			if (b >= PIC_HEIGHT)
			{
				b = PIC_HEIGHT - 1;
			}
			if (b < 0)
			{
				b = 0;
			}

			img_ptr2[i] = img_ptr1[a + (b*PIC_WIDTH)];
			i++;
		}
	}

	putimage(0, 0, &process_img);
}