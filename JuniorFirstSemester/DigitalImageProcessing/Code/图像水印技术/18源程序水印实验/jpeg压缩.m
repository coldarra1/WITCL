J=imread('watermarked.bmp','bmp');
subplot(1,2,1)
title('Ô´Í¼Ïñ');
imshow(J);
imwrite(J,'watermarked1.jpg','jpeg','quality',45);
subplot(1,2,2);
title('Ñ¹ËõºóÍ¼Ïñ');
imshow(J);