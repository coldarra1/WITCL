/**$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#if !defined(COLORCONV_H_)
#define COLORCONV_H_

struct RGB
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
};

struct HSI
{
	double	Hue;
	double	Saturation;
	double	Intensity;
};

struct FLAGS
{
	char	visited:1;
	char	marked:1;
	char	edged:1;
	char	center:1;
	char	color:1;
	char	dummy:3;
};

int RgbToHsi(RGB *, HSI *);
#endif
