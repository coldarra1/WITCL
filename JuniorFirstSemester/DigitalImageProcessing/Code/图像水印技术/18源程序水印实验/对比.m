clear 
close all
f1='';
[f1,p]=uigetfile('*.jpg;*.bmp;*.tif;*.gif','打开原始图像文件');
addpath(p);
if f1==0;
return;
end;
Wori=imread(f1);    % 原始水印
Wori=im2bw(Wori,0.5);

f2='';
[f2,p]=uigetfile('*.jpg;*.bmp;*.tif;*.gif','打开原始图像文件');
addpath(p);
if f2==0;
return;
end;
Wpick=imread(f2);        % 待检测水印
subplot(1,2,1);
imshow(Wori);
title('original watermark');
subplot(1,2,2);
imshow(Wpick);
title('picked out watermark');
a=0;
b=0;
size1=size(Wori);
M1=size1(1);
M2=size1(2);
W1=ones(M1,M2);
W2=ones(M1,M2);
for i=1:M1
    for j=1:M2
        if (Wori(i,j)==0)
            W1(i,j)=-1;
        end
        if (Wpick(i,j)==0)
            W2(i,j)=-1;
        end
        a=a+W1(i,j)*W2(i,j);
        b=b+W2(i,j)^2;
    end
end
NC=a/b
%  将NC的值与阀值比较 得出结论