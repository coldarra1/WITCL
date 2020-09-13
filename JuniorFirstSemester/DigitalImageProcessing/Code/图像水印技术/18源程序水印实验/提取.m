N=32;
K=8;
I=imread('lena.bmp','bmp');
J=imread('watermarked.bmp','bmp');
for p=1:N
for q=1:N
x=(p-1)*K+1;
y=(q-1)*K+1;
BLOCK1=I(x:x+K-1,y:y+K-1);
BLOCK2=J(x:x+K-1,y:y+K-1);
BLOCK1=ifft(BLOCK1);
BLOCK2=ifft(BLOCK2); 
a=BLOCK2(1,1)/BLOCK1(1,1)-1;
if a<0
W(p,q)=0;
else
W(p,q)=1;
end
end
end
%显示提取的水印
subplot(2,2,4);imshow(W);title(' 提取的水印');
%保存写入的文件
imwrite(W,'Wpick.bmp','bmp');