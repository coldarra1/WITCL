%方差为0.002 的高斯噪声和强度为0.02 的椒盐噪声
I=imread('watermarked.bmp');
subplot(1,3,1);
imshow(I);
title('含水印图像');
J=imnoise(I,'gaussian',0,0.002);
imwrite(J,'watermarked1.bmp');
subplot(1,3,2);
imshow(J);
title('高斯噪声');
k=imnoise(I,'salt & pepper',0.02);
imwrite(k,'watermarked2.bmp');
subplot(1,3,3);
imshow(k);
title('椒盐噪声');
