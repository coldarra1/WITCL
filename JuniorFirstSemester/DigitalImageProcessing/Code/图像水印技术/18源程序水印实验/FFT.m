M=256;%原图像长度
N=32;%水印图像长度
K=8;
%显示原图像
f1='';
[f1,p]=uigetfile('*.jpg;*.bmp;*.tif;*.gif','打开原始图像文件');
addpath(p);
if f1==0;
return;
end;
I=imread(f1); 
subplot(2,2,1);

imshow(I);title(' 原始公开图像');
%显示水印图像
f2='';
[f2,p]=uigetfile('*.jpg;*.bmp;*.tif;*.gif','打开原始图像文件');
addpath(p);
if f2==0;
return;
end;
subplot(2,2,2);J=imread(f2);imshow(J);title(' 水印图像');
%水印嵌入
for p=1:N
for q=1:N
x=(p-1)*K+1;y=(q-1)*K+1;
BLOCK=I(x:x+K-1,y:y+K-1);
BLOCK=fft(BLOCK);
if J(p,q )==0
a=-1;
else
a=1;
end
BLOCK=BLOCK*(1+a*0.02);
BLOCK=ifft(BLOCK);
I(x:x+K-1,y:y+K-1)=BLOCK;
end
end
%显示嵌入水印后的图像
subplot(2,2,3);imshow(I);title(' 含水印的图像')
imwrite(I,'watermarked.bmp','bmp');