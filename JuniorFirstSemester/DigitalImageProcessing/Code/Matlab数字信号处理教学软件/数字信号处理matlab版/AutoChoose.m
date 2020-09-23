function AutoChoose(handles)
global signal;
global fs;
global d;
y=signal;
Nn=256;
DigitalFilter_value=get(handles.DigitalFilter,'Value'); %ÂË²¨Æ÷ÀàÐÍ
FilterDesign_value=get(handles.FilterDesign,'Value');   %IIR¸÷ÖÖÂË²¨Æ÷
Windows_value=get(handles.Windows,'Value');             %FIR´°º¯ÊýÑ¡Ôñ
FilterType_value=get(handles.FilterType,'Value');  %µÍÍ¨¸ßÍ¨´øÍ¨´øÍ¨´ø×è
DisplayType_value=get(handles.DisplayType,'Value');%ÏÔÊ¾ÀàÐÍÏßÐÔµÄ»ò¶ÔÊýµÄ

Rp_value=str2double(get(handles.Rp,'String'));
Rs_value=str2double(get(handles.Rs,'String'));
Fs_value=str2double(get(handles.Fs,'String'));
fs=Fs_value;
% Fs=Fs_value;
Fp1_value=str2double(get(handles.Fp1,'String'));
Fp2_value=str2double(get(handles.Fp2,'String'));
Fs1_value=str2double(get(handles.Fs1,'String'));
Fs2_value=str2double(get(handles.Fs2,'String'));
wp1=tan((pi*Fp1_value/Fs_value)/2);
wp2=tan((pi*Fp2_value/Fs_value)/2);
ws1=tan((pi*Fs1_value/Fs_value)/2);
ws2=tan((pi*Fs2_value/Fs_value)/2);
wp=[wp1,wp2];ws=[ws1,ws2];
wap=2*Fs_value*tan(wp./2);was=2*Fs_value*tan(ws./2);
if(DigitalFilter_value==1)
    if(FilterDesign_value==1)
       if((FilterType_value==1)||(FilterType_value==2))
         % set(handles.Fp1,'string','30');set(handles.Fs1,'string','40')
          [n,Wn]=buttord(wp1,ws1,Rp_value,Rs_value,'s')
         set(handles.MinOrderDisplay,'string',num2str(n))
       else
          if((FilterType_value==3)||(FilterType_value==4))
              [n,Wn]=buttord(wap,was,Rp_value,Rs_value,'s')
              set(handles.MinOrderDisplay,'string',num2str(n))
          end
       end
%          switch FilterType_value
%                     case 1:
%                          [n,Wn]=buttord(wp1,ws1,Rp_value,Rs_value);
%                          set(handles.MinOrderDisplay,'string',num2str(n))
%                          set(handles.textFp1,'string','Í¨´ø½ØÖ¹ÆµÂÊ');
%                          set(handles.textFs1,'string','×è´ø½ØÖ¹ÆµÂÊ');
%                     case 2:
%                         [n,Wn]=buttord(wp1,ws1,Rp_value,Rs_value);
%                         set(handles.MinOrderDisplay,'string',num2str(n))
%                         set(handles.textFp1,'string','×è´ø½ØÖ¹ÆµÂÊ');
%                         set(handles.textFs1,'string','Í¨´ø½ØÖ¹ÆµÂÊ');
%                     case 3:
%                         [n,Wn]=buttord(wap,was,Rp_value,Rs_value);
%                         set(handles.MinOrderDisplay,'string',num2str(n))
%                         set(handles.textFp1,'string','×óÍ¨´ø½ØÖ¹ÆµÂÊFp1');
%                         set(handles.textFs1,'string','×ó×è´ø½ØÖ¹ÆµÂÊFs1');
%                         et(handles.textFp2,'string','ÓÒÍ¨´ø½ØÖ¹ÆµÂÊFp2');
%                         set(handles.textFs2,'string','ÓÒ×è´ø½ØÖ¹ÆµÂÊFs2');
%                         warn('Çë±£Ö¤Fs1<Fp1<Fp2<Fs1','My Warn Dialog','modal');
%                     case 4:
%                         [n,Wn]=buttord(wap,was,Rp_value,Rs_value);
%                         set(handles.MinOrderDisplay,'string',num2str(n))
%                         set(handles.textFp1,'string','×ó×è´ø½ØÖ¹ÆµÂÊFs1');
%                         set(handles.textFs1,'string','×óÍ¨´ø½ØÖ¹ÆµÂÊFp1');
%                         et(handles.textFp2,'string','ÓÒ×è´ø½ØÖ¹ÆµÂÊFs2');
%                         set(handles.textFs2,'string','ÓÒÍ¨´ø½ØÖ¹ÆµÂÊFp2');
%                         warn('Çë±£Ö¤Fp1<Fs1<Fs2<Fp1','My Warn Dialog','modal');   
%                 end
    else
        if(FilterDesign_value==2)
            if((FilterType_value==1)||(FilterType_value==2))
                [n,Wn]=cheb1ord(wp1,ws1,Rp_value,Rs_value,'s')
                set(handles.MinOrderDisplay,'string',num2str(n))
            else
                if((FilterType_value==3)||(FilterType_value==4))
                    [n,Wn]=cheb1ord(wap,was,Rp_value,Rs_value,'s')
                    set(handles.MinOrderDisplay,'string',num2str(n))
                end
            end
        else
            if(FilterDesign_value==3)
                if((FilterType_value==1)||(FilterType_value==2))
                    [n,Wn]=cheb2ord(wp1,ws1,Rp_value,Rs_value,'s')
                    set(handles.MinOrderDisplay,'string',num2str(n))
                else
                    if((FilterType_value==3)||(FilterType_value==4))
                        [n,Wn]=cheb2ord(wap,was,Rp_value,Rs_value,'s')
                        set(handles.MinOrderDisplay,'string',num2str(n))
                    end
                end
     else
        if(FilterDesign_value==4)
            if((FilterType_value==1)||(FilterType_value==2))
                [n,Wn]=ellipord(wp1,ws1,Rp_value,Rs_value,'s')
                set(handles.MinOrderDisplay,'string',num2str(n))
            else
                if((FilterType_value==3)||(FilterType_value==4))
                    [n,Wn]=ellipord(wap,was,Rp_value,Rs_value)
                    set(handles.MinOrderDisplay,'string',num2str(n))
                end
            end               
            end
        end 
        end
    end
else
    if(DigitalFilter_value==2)
      if((FilterType_value==1)||(FilterType_value==2))
          [n,Wn]=buttord(wp1,ws1,Rp_value,Rs_value);
          set(handles.MinOrderDisplay,'string',num2str(n))
       else
          if((FilterType_value==3)||(FilterType_value==4))
              [n,Wn]=buttord(wp,ws,Rp_value,Rs_value);
              set(handles.MinOrderDisplay,'string',num2str(n))
          end
       end  
    end
end
     
%Êý×ÖÂË²¨Æ÷IIR»òÕßFIRÑ¡Ôñ
switch DigitalFilter_value
    %Ñ¡ÔñIIRÂË²¨Æ÷    
    case 1
%IIRÖÐµÄButterworth¡¢Chebyshev1¡¢Chebyshev2Ñ¡Ôñ        
switch FilterDesign_value  
    %Ñ¡ÔñÉè¼ÆButterworthÂË²¨Æ÷
    case 1
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1          
%                  [b,a]=butter(n,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                 [z,p,k]=buttap(n);
                 [bp,ap]=zp2tf(z,p,k); 
                 [bs,as]=lp2lp(bp,ap,wp1); 
                 [bz,az]=bilinear(bs,as,1/2); 
                 [h,f]=freqz(bz,az,256,fs);  
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');            
                 d=filter(bz,az,y);
            %¸ßÍ¨ÂË²¨Æ÷
            case 2                            
%                  [b,a]=butter(n,Wn,'high');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                 [z,p,k]=buttap(n);
                 [bp,ap]=zp2tf(z,p,k); 
                 [bs,as]=lp2hp(bp,ap,wp1); 
                 [bz,az]=bilinear(bs,as,1/2); 
                 [h,f]=freqz(bz,az,256,fs);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
                 d=filter(bz,az,y);
            %´øÍ¨ÂË²¨Æ÷
            case 3   
%                  [b,a]=butter(n,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=buttap(n);
                [bp,ap]=zp2tf(z,p,k);
                bw=wap(2)-wap(1);
                w0=sqrt(wap(2)*wap(1))
                [bs,as]=lp2bp(bp,ap,w0,bw);
                [bz,az]=bilinear(bs,as,fs);
                [h,f]=freqz(bz,az,fs/2,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
%                  [b,a]=butter(n,Wn,'stop');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=buttap(n);
                [bp,ap]=zp2tf(z,p,k);
                bw=wap(2)-wap(1);
                w0=sqrt(wap(2)*wap(1))
                [bs,as]=lp2bs(bp,ap,w0,bw);
                [bz,az]=bilinear(bs,as,fs);
                [h,f]=freqz(bz,az,fs/2,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');             
        end
    %Ñ¡ÔñÉè¼ÆCheybyshev1ÂË²¨Æ÷
    case 2
         %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ 
       switch FilterType_value
             %µÍÍ¨ÂË²¨Æ÷
             case 1                   
%                  [b,a]=cheby1(n,Rp_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb1ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2lp(bp,ap,wp1);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
             %¸ßÍ¨ÂË²¨Æ÷
             case 2                  
%                  [b,a]=cheby1(n,Rp_value,Wn,'high');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb1ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2hp(bp,ap,wp1);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
               title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷     
            case 3
%                  [b,a]=cheby1(n,Rp_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb1ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2bp(bp,ap,wap);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷ 
            case 4
%                  [b,a]=cheby1(n,Rp_value,Wn,'stop');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb1ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2bs(bp,ap,wap);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');              
       end
        %Ñ¡ÔñÉè¼ÆCheybyshev2ÂË²¨Æ÷
        case 3
          %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ    
        switch FilterType_value
             %µÍÍ¨ÂË²¨Æ÷
             case 1                  
%                  [b,a]=cheby2(n,Rp_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb2ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2lp(bp,ap,wp1);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
             %¸ßÍ¨ÂË²¨Æ÷ 
             case 2                    
%                  [b,a]=cheby2(n,Rp_value,Wn,'high');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb2ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2hp(bp,ap,wp1);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
%                  [b,a]=cheby2(n,Rp_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb2ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2bp(bp,ap,wap);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
%                  [b,a]=cheby2(n,Rp_value,Wn,'stop');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=cheb2ap(n,Rp_value);
                [bp,ap]=zp2tf(z,p,k);
                [bs,as]=lp2bs(bp,ap,wap);
                [bz,az]=bilinear(bs,as,1/2);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');     
        end 
    %Ñ¡ÔñÉè¼ÆÍÖÔ²ÂË²¨Æ÷
    case 4
         %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ 
       switch FilterType_value
             %µÍÍ¨ÂË²¨Æ÷
             case 1                   
%                  [b,a]=ellip(n,Rp_value,Rs_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=ellipap(n,Rp_value,Rs_value);
                [A,B,C,D]=zp2ss(z,p,k);
                [AT,BT,CT,DT]=lp2lp(A,B,C,D,Wn);
                [num1,den1]=ss2tf(AT,BT,CT,DT);
                [bz,az]=bilinear(num1,den1,fs);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
             %¸ßÍ¨ÂË²¨Æ÷
             case 2                  
%                  [b,a]=ellip(n,Rp_value,Rs_value,Wn,'high');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=ellipap(n,Rp_value,Rs_value);
                [A,B,C,D]=zp2ss(z,p,k);
                [AT,BT,CT,DT]=lp2hp(A,B,C,D,Wn);
                [num1,den1]=ss2tf(AT,BT,CT,DT);
                [bz,az]=bilinear(num1,den1,fs);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷     
            case 3
%                  [b,a]=ellip(n,Rp_value,Rs_value,Wn);
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=ellipap(n,Rp_value,Rs_value);
                [A,B,C,D]=zp2ss(z,p,k);
                [AT,BT,CT,DT]=lp2bp(A,B,C,D,Wn);
                [num1,den1]=ss2tf(AT,BT,CT,DT);
                [bz,az]=bilinear(num1,den1,fs);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                axes(handles.Magnitude);
                if(DisplayType_value==1) plot(f,abs(h))
                else plot(f,20*log10(abs(h)))
                end
                grid on;
               title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷ 
            case 4
%                  [b,a]=ellip(n,Rp_value,Rs_value,Wn,'stop');
%                  [h,f]=freqz(b,a,Nn,Fs_value);
                [z,p,k]=ellipap(n,Rp_value,Rs_value);
                [A,B,C,D]=zp2ss(z,p,k);
                [AT,BT,CT,DT]=lp2bs(A,B,C,D,Wn);
                [num1,den1]=ss2tf(AT,BT,CT,DT);
                [bz,az]=bilinear(num1,den1,fs);
                [h,f]=freqz(bz,az,256,fs);
                d=filter(bz,az,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');           
       end                
end
    %Ñ¡ÔñFIRÂË²¨Æ÷    
    case 2
%FIRÖÐµÄWindowsÑ¡Ôñ        
switch Windows_value 
    %Ñ¡ÔñÉè¼ÆboxcarÂË²¨Æ÷
    case 1
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=boxcar(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                 
                 d=filter(b,1,y);
                 
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2           
                 w=boxcar(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                 d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=boxcar(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=boxcar(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                  title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');             
        end
    %Ñ¡ÔñÉè¼ÆbartlettÂË²¨Æ÷
    case 2
         %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ 
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=bartlett(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2           
                 w=bartlett(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                  title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=bartlett(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=bartlett(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');          
        end
        %Ñ¡ÔñÉè¼ÆblackmanÂË²¨Æ÷
    case 3
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=blackman(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2            
                 w=blackman(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=blackman(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=blackman(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');       
        end
    %Ñ¡ÔñÉè¼ÆhanningÂË²¨Æ÷
    case 4
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=hanning(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2            
                 w=hanning(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                  title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=hanning(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=hanning(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');        
        end
    %Ñ¡ÔñÉè¼ÆhammingÂË²¨Æ÷
    case 5
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=hamming(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2            
                 w=hamming(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=hamming(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=hamming(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');         
        end
    %Ñ¡ÔñÉè¼ÆkaiserÂË²¨Æ÷
    case 6
        %Ñ¡ÔñÂË²¨Æ÷ÀàÐÍ
        switch FilterType_value
            %µÍÍ¨ÂË²¨Æ÷
            case 1
                 w=kaiser(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %¸ßÍ¨ÂË²¨Æ÷
            case 2            
                 w=kaiser(n+1);
                 b=fir1(n,Wn,'high',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´øÍ¨ÂË²¨Æ÷
            case 3
                 w=kaiser(n+1);
                 b=fir1(n,Wn,w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                 title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
            %´ø×èÂË²¨Æ÷
            case 4
                 w=kaiser(n+1);
                 b=fir1(n,Wn,'stop',w);
                 [h,f]=freqz(b,1,Nn,Fs_value);
                  d=filter(b,1,y);
                 axes(handles.Magnitude);
                 if(DisplayType_value==1) plot(f,abs(h))
                 else plot(f,20*log10(abs(h)))
                 end
                 grid on;
                  title('ÂË²¨Æ÷·ùÆµÏìÓ¦');
                 axes(handles.Phase);
                 plot(f,angle(h));
                 grid on;
                 title('ÂË²¨Æ÷ÏàÆµÏìÓ¦');    
        end        
end    
end



