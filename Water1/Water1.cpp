
#include "water.h"

int main()
{
	initgraph(PIC_WIDTH, PIC_HEIGHT);

	loadimage(&res_img, _T("timg.bmp"));

	img_ptr1 = GetImageBuffer(&res_img);
	img_ptr2 = GetImageBuffer(&process_img);

	memset(buf, 0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));
	memset(buf2, 0, (PIC_HEIGHT*PIC_WIDTH + PIC_WIDTH) * sizeof(short));

	BeginBatchDraw();

	while (true)
	{
		logicFunction();

		RendererRipple();

		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;

}