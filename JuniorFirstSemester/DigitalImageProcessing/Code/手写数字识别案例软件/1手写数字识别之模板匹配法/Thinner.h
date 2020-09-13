//***************************************************************************
// 文件：Thinner.h
// 功能：四种不同的细化算法
//***************************************************************************

void beforethin(unsigned char *ip, unsigned char *jp, 
				unsigned long lx, unsigned long ly);
void ThinnerHilditch(void *image, unsigned long lx, unsigned long ly);
void ThinnerPavlidis(void *image, unsigned long lx, unsigned long ly);
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly);
//注意该函数lWidth应该是Height；
BOOL WINAPI ThiningDIBSkeleton (LPSTR lpDIBBits, LONG lWidth, LONG lHeight);