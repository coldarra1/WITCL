function varargout = SignalProcessing(varargin)
% SIGNALPROCESSING M-file for SignalProcessing.fig
%      SIGNALPROCESSING, by itself, creates a new SIGNALPROCESSING or raises the existing
%      singleton*.
%
%      H = SIGNALPROCESSING returns the handle to a new SIGNALPROCESSING or the handle to
%      the existing singleton*.
%
%      SIGNALPROCESSING('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SIGNALPROCESSING.M with the given input arguments.
%
%      SIGNALPROCESSING('Property','Value',...) creates a new SIGNALPROCESSING or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SignalProcessing_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SignalProcessing_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SignalProcessing

% Last Modified by GUIDE v2.5 29-Oct-2012 14:10:58

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SignalProcessing_OpeningFcn, ...
                   'gui_OutputFcn',  @SignalProcessing_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before SignalProcessing is made visible.
function SignalProcessing_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SignalProcessing (see VARARGIN)

% Choose default command line output for SignalProcessing
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SignalProcessing wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = SignalProcessing_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --------------------------------------------------------------------
function Untitled_1_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_12_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_10_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_11_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_13_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_14_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function dft1_Callback(hObject, eventdata, handles)
% hObject    handle to dft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla
axes(handles.axes2);

% Y = dft(signal,N);         
% a= Fs/2*linspace(0,1,N/2+1); % 单边拉普拉斯变换
% axes(handles.axes2);
% plot(a,2*abs(Y(1:N/2+1)))
% title('快速傅里叶变换')
% grid;
%离散傅里叶变换（利用对有限长的序列进行周期性的延拓）
global signal;
global Fs;
N=length(signal);
Ts=1/Fs;                              %采样周期
T=N*Ts;                               %信号周期
w=2*pi/T;                             %频率的抽样间隔
n=0:N-1;k=0:N-1;
Xk=signal*exp(-j*2*pi/N).^(n'*k);
axes(handles.axes2);
stem(Fs/2*n(1:N/2+1)/(N/2+1),abs(Xk(1:N/2+1)),'.')
xlabel('Frequency (Hz)') 
title('DFT|X(K)|')
axes(handles.axes3);
stem(n,angle(Xk),'.');
title('arg|X(k)|');
grid;



% --------------------------------------------------------------------
function dtft1_Callback(hObject, eventdata, handles)
% hObject    handle to dtft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%离散时间傅里叶变换（时域离散频域连续）信号为离散非周期信号
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla
global signal;
N=length(signal);
% fs=str2num(get(handles.caiyangFs,'string'));
% ts=1/fs;
% ws=2*pi/ts;
n=0:N-1;
w=linspace(-2*pi,2*pi,500);      %将频率区间分为500份
X=signal*exp(-j*n'*w);        %离散时间傅里叶变换
a=min(abs(X));
b=max(abs(X));
c=min(angle(X));
d=max(angle(X));
axes(handles.axes2);
plot(w,X);
grid;
axis([-2*pi,2*pi,-1.1*b,1.1*b]);
ylabel('频谱');xlabel('数字角频率，范围-2*pi到2*pi');
axes(handles.axes3);
plot(w,abs(X));
grid;
axis([-2*pi,2*pi,1.1*a,1.1*b]);
ylabel('幅度谱');

axes(handles.axes4);
plot(w,angle(X));
grid;
axis([-2*pi,2*pi,1.1*c,1.1*d]);
ylabel('相位谱');

% --------------------------------------------------------------------
function fft1_Callback(hObject, eventdata, handles)
% hObject    handle to fft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla
axes(handles.axes2);
global signal;
global Fs;
global sft;           %信号的傅里叶变换
L=length(signal);
NFFT = 2^nextpow2(L);
Y = fft(signal,NFFT)/L;  
sft=Y;
a= Fs/2*linspace(0,1,NFFT/2+1); % 单边拉普拉斯变换
axes(handles.axes2);
if Fs>500 plot(a,2*abs(Y(1:NFFT/2+1)))
else stem(a,2*abs(Y(1:NFFT/2+1)),'.')
end
title('快速傅里叶变换')
grid;


% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function formulainput_Callback(hObject, eventdata, handles)
% hObject    handle to formulainput (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% set(handles.input1,'visible','off');
% set(handles.input2,'visible','on');

% --------------------------------------------------------------------
function Untitled_7_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function pulseseries1_Callback(hObject, eventdata, handles)
% hObject    handle to pulseseries1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%绘制单位脉冲信号
% set(handles.input1,'visible','on')
% set(handles.input2,'visible','off')
global signal;
global Fs;
global stype;
stype=1;
set(handles.signalend,'enable','off');      
set(handles.Fs1,'enable','off');   
Fs=str2num(get(handles.Fs1,'string'));
n0=str2num(get(handles.signalstart,'string')); %信号起始点
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
if ((n0 < xs) | (n0 > xe) | (xs > xe))         % 检查输入参数正确性
	error('参数必须满足 xs <= n0 <= xe')
end
n = [xs:xe];                                    % 生成位置向量
y= [(n-n0) == 0];                              % 生成单个脉冲序列
axes(handles.axes1);stem(n,y,'.');title('单位脉冲信号')
signal=y;



% --------------------------------------------------------------------
function jieyueseries2_Callback(hObject, eventdata, handles)
% hObject    handle to jieyueseries2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%绘制单位阶跃信号
% set(handles.input1,'visible','on')
% set(handles.input2,'visible','off')
global signal;
global Fs;
global stype;
stype=2;
set(handles.signalend,'enable','off'); 
set(handles.Fs1,'enable','off');
%Fs=str2num(get(handles.Fs1,'string'));
n0=str2num(get(handles.signalstart,'string')); %信号起始点
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
if ((n0 < xs) | (n0 > xe) | (xs > xe))         % 检查输入参数正确性
	error('参数必须满足 xs <= n0 <= xe')
end
n = [xs:xe];                                    % 生成位置向量
y= [(n-n0) >= 0];                              % 生成单个脉冲序列
axes(handles.axes1);stem(n,y,'.');title('单位阶跃序列');
signal=y;

% --------------------------------------------------------------------
function Sexpseries5_Callback(hObject, eventdata, handles)
% hObject    handle to Sexpseries5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%实指数信号
% set(handles.input1,'visible','on')
% set(handles.input2,'visible','off')
global signal;
global stype;
stype=5;
set(handles.signalend,'enable','off'); 
set(handles.Fs1,'enable','off');
set(handles.signalstart,'enable','off')
%Fs=str2num(get(handles.Fs1,'string'));
% set(handles.Xstartpoint,'string','0');
% set(handles.Xendpoint,'string','100');
%n0=str2num(get(handles.signalstart,'string')); %信号起始点
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
% if ((n0 < xs) | (n0 > xe) | (xs > xe))         % 检查输入参数正确性
% 	error('参数必须满足 xs <= n0 <= xe')
% end
if (xs>xe)
    error('参数必须满足xs<xe')
end
str={'y=c*(a.^n) a=','b','c'};
strdef={'2','0','1'};
Data=inputdlg(str,'y=c*(a.^n)设置参数',1,strdef);
a=str2double(Data(1));b=str2double(Data(2));c=str2double(Data(3));
n=[xs:xe];
y=c*(a.^n) 
signal=y;
axes(handles.axes1);
stem(n,y,'.')
title('实指数序列y=c*(a^n)');

% --------------------------------------------------------------------
function recseries3_Callback(hObject, eventdata, handles)
% hObject    handle to recseries3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%矩形序列
% set(handles.input1,'visible','on');
% set(handles.input2,'visible','off');
global signal;
global Fs;
global stype;
stype=3;
set(handles.signalend,'enable','on'); 
set(handles.Fs1,'enable','off');
Fs=str2num(get(handles.Fs1,'string'));
n0=str2num(get(handles.signalstart,'string')); %信号起始点
n1=str2num(get(handles.signalend,'string'));   %信号终点
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
if ((n0 < xs) | (n0 > xe) | (xs > xe)|(n1<n0)|(n1>xe)>(n1<xs)|(n1>xe))         % 检查输入参数正确性
	error('参数必须满足 xs <= n0 <=n1<= xe')
end
% for n=xs:xe
% if ((n>=n0)&(n<=n1))
%     y=1;
% else y=0
% end
% y(:)=y;
% end
n = [xs:xe]; 
y=[(n>=n0)&(n<=n1)]
axes(handles.axes1);stem(n,y,'.');title('矩形序列');axis([xs xe 0 2]);
signal=y;



% --------------------------------------------------------------------
function triangleseries4_Callback(hObject, eventdata, handles)
% hObject    handle to triangleseries4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%三角波和锯齿波的产生
% set(handles.input1,'visible','on');
% set(handles.input2,'visible','off');
global signal;
global stype;
stype=4;
set(handles.signalend,'enable','off');
set(handles.Xstartpoint,'enable','off'); %横坐标起始点
set(handles.signalstart,'enable','off');
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
Fs=str2num(get(handles.Fs1,'string'));
n=[0:xe];
str={'请输入width='};
strdef={'0.4'};
SCData=inputdlg(str,'确定锯齿波峰值的位置',1,strdef);
Width=str2double(SCData(1));
t=xs:1/Fs:xe;
y=sawtooth(2*pi*t,Width);
signal=y;
axes(handles.axes1);
plot(t,y);xlabel('时间/s');title('三角波和锯齿波');




% --------------------------------------------------------------------
function sinsseries6_Callback(hObject, eventdata, handles)
% hObject    handle to sinsseries6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%正弦序列
% set(handles.input1,'visible','on');
% set(handles.input2,'visible','off');
set(handles.Fs1,'enable','on');
global signal;
global Fs;
global stype;
stype=6;
set(handles.signalend,'enable','off'); 
% set(handles.Xstartpoint,'string','0')
% set(handles.Xendpoint,'string','100')
Fs=str2num(get(handles.Fs1,'string'));
n0=str2num(get(handles.signalstart,'string')); %信号起始点
n1=str2num(get(handles.signalend,'string'));   %信号终点
xs=str2num(get(handles.Xstartpoint,'string')); %横坐标起始点
xe=str2num(get(handles.Xendpoint,'string'));   %横坐标终点
n = [xs:xe]; 
str={'函数sin(2*pi*f*t) 信号频率f='};
strdef={'50'};
SCData=inputdlg(str,'频率设置',1,strdef);
f=str2double(SCData);
if Fs<=(2*f)                                    
    errordlg('不满足香农采样定理！请重新输入','参数设置错误','modal')
end
T = 1/Fs; % 采样时间
L =(xe-xs+1); % 信号长度
t = 0:T:(L-1)/Fs; % 时间矢量
y=sin(2*pi*f*t);
signal=y;
axes(handles.axes1);
stem(n,y,'.')
xlabel('时间/s');ylabel('信号幅值');title('正弦序列')





% --------------------------------------------------------------------
function dcsig_Callback(hObject, eventdata, handles)
% hObject    handle to dcsig (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.Xstartpoint,'enable','off'); 
set(handles.Xendpoint,'enable','off');
set(handles.signalstart,'enable','off');
set(handles.signalend,'enable','off');
% set(handles.input1,'visible','on');
% set(handles.input2,'visible','off');
global signal;global Fs;
N=500;
Fs=str2num(get(handles.Fs1,'string'));
str={'频率f1=','频率f2='};
strdef={'50','100'};
SSDATA=inputdlg(str,'信号参数设置',1,strdef);
f1=str2double(SSDATA(1));
f2=str2double(SSDATA(2));

T=1/Fs;
 k=0:N-1;
t=(0:N-1)/Fs;
signal=zeros(size(t));
signal(50:150)=cos(2*pi*f1*(k(50:150)-50)*T);
signal(250:350)=cos(2*pi*f2*(k(250:350)-250)*T);
axes(handles.axes1);plot(k,signal);grid;
title('信号中有两不同频率的正弦信号');




% --------------------------------------------------------------------
function atomsig_Callback(hObject, eventdata, handles)
% hObject    handle to atomsig (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
% set(handles.input1,'visible','on');
% set(handles.input2,'visible','off');
axes(handles.axes1);
cla
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
str={'Sig1时间中心t1=','频率中心f1=','Sig2时间中心t2=','频率中心f2='};
strdef={'28','0.25','100','0.25'};
ATOM=inputdlg(str,'原子信号参数设置',1,strdef);
t1=str2double(ATOM(1));
f1=str2double(ATOM(2));
t2=str2double(ATOM(3));
f2=str2double(ATOM(4));
figure
signal=atoms(128,[t1,f1,20,1;t2,f2,20,1]);%原子信号长度128，时间中心t1=28,t2=100,频率中心f1=f2=0.25




function input2signal1_Callback(hObject, eventdata, handles)
% hObject    handle to input2signal1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of input2signal1 as text
%        str2double(get(hObject,'String')) returns contents of input2signal1 as a double


% --- Executes during object creation, after setting all properties.
function input2signal1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to input2signal1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function input2signal2_Callback(hObject, eventdata, handles)
% hObject    handle to input2signal2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of input2signal2 as text
%        str2double(get(hObject,'String')) returns contents of input2signal2 as a double


% --- Executes during object creation, after setting all properties.
function input2signal2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to input2signal2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Xstartpoint_Callback(hObject, eventdata, handles)
% hObject    handle to Xstartpoint (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Xstartpoint as text
%        str2double(get(hObject,'String')) returns contents of Xstartpoint as a double


% --- Executes during object creation, after setting all properties.
function Xstartpoint_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xstartpoint (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Xendpoint_Callback(hObject, eventdata, handles)
% hObject    handle to Xendpoint (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Xendpoint as text
%        str2double(get(hObject,'String')) returns contents of Xendpoint as a double


% --- Executes during object creation, after setting all properties.
function Xendpoint_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xendpoint (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function signalstart_Callback(hObject, eventdata, handles)
% hObject    handle to signalstart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of signalstart as text
%        str2double(get(hObject,'String')) returns contents of signalstart as a double


% --- Executes during object creation, after setting all properties.
function signalstart_CreateFcn(hObject, eventdata, handles)
% hObject    handle to signalstart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function signalend_Callback(hObject, eventdata, handles)
% hObject    handle to signalend (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of signalend as text
%        str2double(get(hObject,'String')) returns contents of signalend as a double


% --- Executes during object creation, after setting all properties.
function signalend_CreateFcn(hObject, eventdata, handles)
% hObject    handle to signalend (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Fs1_Callback(hObject, eventdata, handles)
% hObject    handle to Fs1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fs1 as text
%        str2double(get(hObject,'String')) returns contents of Fs1 as a double


% --- Executes during object creation, after setting all properties.
function Fs1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fs1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end





% --------------------------------------------------------------------
function readwave_Callback(hObject, eventdata, handles)
% hObject    handle to readwave (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;global Fs;
% set(handles.input1,'visible','off');
% set(handles.input2,'visible','off');
[filename, pathname] = uigetfile('*.wav', 'Please select an wav file');
[y,Fs,bits]=wavread(filename);%读出信号，采样率和采样位数。
y=y(:,1);%我这里假设你的声音是双声道，我只取单声道作分析，如果你想分析另外一个声道，请改成y=y(:,2)
sigLength=length(y);
Y = fft(y,sigLength);
Pyy = Y.* conj(Y) / sigLength;
halflength=floor(sigLength/2);
f1=Fs*(0:halflength)/sigLength;
signal=y;
axes(handles.axes1);       %绘制时域图
t=(0:sigLength-1)/Fs; 
plot(t,y);xlabel('时间Time(s)');



% --- Executes on button press in display1.
function display1_Callback(hObject, eventdata, handles)
% hObject    handle to display1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global signal1;global Fs;
% set(handles.input1,'visible','off');
% set(handles.input2,'visible','on');
Fs=str2num(get(handles.Fs2,'string'));
xe=str2num(get(handles.Xlength,'string'));
rand=get(handles.randomnoise1,'value')
t=[0:1/Fs:(xe-1)/Fs];
s1=get(handles.input2signal1,'string');
y1=eval(s1);ly=length(y1);lx=length(t);
if (lx~=ly) 
    errordlg('请保证横轴长度与信号的长度相等','参数设置错误','modal')
end
switch rand
    case 0
        y1=y1;
    case 1
        y1=y1+0.3*randn(1,length(y1));
end
signal1=y1;signal=y1;
axes(handles.axes1);
% stem(t,y1,'.');
plot(t,y1);
xlabel('时间/s');


% --- Executes on button press in display2.
function display2_Callback(hObject, eventdata, handles)
% hObject    handle to display2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal2;global Fs;
% set(handles.input1,'visible','off');
% set(handles.input2,'visible','on');
Fs=str2num(get(handles.Fs2,'string'));
xe=str2num(get(handles.Xlength,'string'));
t=[0:1/Fs:(xe-1)/Fs];
s2=get(handles.input2signal2,'string');
rand=get(handles.randomnoise2,'value')
y2=eval(s2);ly=length(y2);lx=length(t);
if (lx~=ly) 
    errordlg('请保证横轴长度与信号的长度相等','参数设置错误','modal')
end
switch rand
    case 0
        y2=y2;
    case 1
        y2=y2+0.3*randn(1,length(y2));
end
signal2=y2;
axes(handles.axes2);stem(t,y2,'.');xlabel('时间/s');





function Fs2_Callback(hObject, eventdata, handles)
% hObject    handle to Fs2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Fs2 as text
%        str2double(get(hObject,'String')) returns contents of Fs2 as a double


% --- Executes during object creation, after setting all properties.
function Fs2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Fs2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Xstart2_Callback(hObject, eventdata, handles)
% hObject    handle to Xstart2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Xstart2 as text
%        str2double(get(hObject,'String')) returns contents of Xstart2 as a double


% --- Executes during object creation, after setting all properties.
function Xstart2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xstart2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Xlength_Callback(hObject, eventdata, handles)
% hObject    handle to Xlength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Xlength as text
%        str2double(get(hObject,'String')) returns contents of Xlength as a double


% --- Executes during object creation, after setting all properties.
function Xlength_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Xlength (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in listbox1.
function listbox1_Callback(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns listbox1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox1


% --- Executes during object creation, after setting all properties.
function listbox1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton7.
function pushbutton7_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in randomnoise1.
function randomnoise1_Callback(hObject, eventdata, handles)
% hObject    handle to randomnoise1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of randomnoise1
%添加随机噪声
% rand=get(handles.randomnoise1,'Value');
% handles.rand=rand;
% guidata(hObject,handles);

% --- Executes on button press in randomnoise2.
function randomnoise2_Callback(hObject, eventdata, handles)
% hObject    handle to randomnoise2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of randomnoise2
%添加随机噪声
% rand=get(handles.randomnoise2,'Value');
% handles.rand=rand;
% guidata(hObject,handles);


% --------------------------------------------------------------------
function Untitled_20_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_21_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function stft1_Callback(hObject, eventdata, handles)
% hObject    handle to stft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.stftuipanel,'visible','on');
warndlg('请保证输入的信号为连续信号,请先输入参数！', 'My Warn Dialog','modal');


% --------------------------------------------------------------------
function Untitled_19_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in stftlistbox.
function stftlistbox_Callback(hObject, eventdata, handles)
% hObject    handle to stftlistbox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns stftlistbox contents as cell array
%        contents{get(hObject,'Value')} returns selected item from stftlistbox


% --- Executes during object creation, after setting all properties.
function stftlistbox_CreateFcn(hObject, eventdata, handles)
% hObject    handle to stftlistbox (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function windwidth_Callback(hObject, eventdata, handles)
% hObject    handle to windwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of windwidth as text
%        str2double(get(hObject,'String')) returns contents of windwidth as a double


% --- Executes during object creation, after setting all properties.
function windwidth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to windwidth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in stftOK.
function stftOK_Callback(hObject, eventdata, handles)
% hObject    handle to stftOK (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global Fs;  
x=signal;
Nw=str2num(get(handles.windwidth,'string'));
val=get(handles.stftlistbox,'value');
N=length(x);
if (Fs<1000) 
    errordlg('请保证输入的信号为连续信号','信号输入错误','modal')
end
NFFT = 2^nextpow2(N);
F=fft(x,NFFT)/N;
a= Fs/2*linspace(0,1,NFFT/2+1); % 单边拉普拉斯变换
axes(handles.axes2);plot(a,2*abs(F(1:NFFT/2+1)));
title('信号频域特性')
[a,b]=size(x);
switch val
    case 1
     figure
     h=window(@boxcar,Nw);
     if (b==1)
     tfrstft(x,1:N,N,h);
     else tfrstft(x',1:N,N,h);
     end
%    L=Nw/2;                   %窗重叠的长度
%    Ts=round((N-Nw)/L)+1;     %round为取最近的整数
%    %nfft=128;
%    nfft=NFFT;
%    TF=zeros(Ts,nfft);        %返回Ts*nfft的零矩阵
%    for i=1:Ts
%      xw=x((i-1)*L+1:i*L+L);
%      temp=fft(xw,nfft); 
%      temp=fftshift(temp);   %对fft的输出进行重新排列，将零频分量移到频谱的中心
%      TF(i,:)=temp;  
%    end
%    axes(handles.axes3);
%    title('信号时频特性')
%    mesh(abs(TF));              %用MESH命令绘制的三维网格图      
%    axes(handles.axes4);
%    contour(abs(TF));           %     
%    axis equal tight            %设置坐标部分比率?
%    grid;
case 2
    figure
    h=window(@triang,Nw);
    if (b==1)
    tfrstft(x,1:N,N,h);
    else tfrstft(x',1:N,N,h);
    end
case 3
   figure
   h=window(@hanning,Nw);
   if (b==1)
    tfrstft(x,1:N,N,h);
   else tfrstft(x',1:N,N,h);
   end
case 4
   figure
   h=window(@hamming,Nw);
   if (b==1)
    tfrstft(x,1:N,N,h);
    else tfrstft(x',1:N,N,h);
    end  
end
        


% --------------------------------------------------------------------
function Untitled_22_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function dct1_Callback(hObject, eventdata, handles)
% hObject    handle to dct1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global ft;
x=signal;
Xk1=dct(x);
ft=Xk1;
axes(handles.axes2);
plot(Xk1);title('离散余弦变换');
grid on;


% --------------------------------------------------------------------
function idct1_Callback(hObject, eventdata, handles)
% hObject    handle to idct1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global Fs;
global ft;
Xk=ft;
y=idct(Xk);
axes(handles.axes3);
if Fs>500
plot(y);
else stem(y);
end
title('离散余弦反变换')
grid;


% --------------------------------------------------------------------
function nowind_Callback(hObject, eventdata, handles)
% hObject    handle to nowind (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
[row,colum]=size(signal);
if colum==1
    x=signal;
else 
    x=signal';
end
figure
tfrwv(x);


% --------------------------------------------------------------------
function windhamming_Callback(hObject, eventdata, handles)
% hObject    handle to windhamming (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
[row,colum]=size(signal);
if colum==1
    x=signal;
else 
    x=signal';
end
figure
tfrpwv(x);


% --------------------------------------------------------------------
function Untitled_23_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_24_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function filterdesign_Callback(hObject, eventdata, handles)
% hObject    handle to filterdesign (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
filterdesign();


% --------------------------------------------------------------------
function Untitled_26_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_26 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_27_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
WaveTrans();

% --------------------------------------------------------------------
function Untitled_28_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
WaveTrans();


% --------------------------------------------------------------------
function Untitled_31_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_32_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_33_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% global f;
% global fs
% y=f;
% str={'请输入通带截止频率：fp=','请输入阻带截止频率：fss='};
% strdef={'20','50'};
% SCData=inputdlg(str,'低通滤波器参数',1,strdef);
% fp=str2double(SCData(1));
% fss=str2double(SCData(2));
% % Wp=1;Ws=2;
% wp=2*pi*fp/fs;
% ws=2*pi*fss/fs;
% wap=tan(wp/2);was=tan(ws/2);
% Rp=3;Rs=20;
% [N,Wn]=cheb1ord(wap,was,Rp,Rs,'s');
% [z,p,k]=cheb1ap(N,Rp);
% [bp,ap]=zp2tf(z,p,k);
% [bs,as]=lp2lp(bp,ap,wap);
% [bz,az]=bilinear(bs,as,1/2);
% [h,f]=freqz(bz,az,256,fs);
% axes(handles.axes2)
% plot(f,abs(h));grid on;
% title('切比雪夫1型低通滤波器幅度响应')
% axes(handles.axes3)
% d=filter(bz,az,y);
% % stem(d,'.k');
% plot(d(1:length(d)/2))
% grid on;
% title('滤波以后的信号')
% axes(handles.axes4)
% y=fft(d);
% NFFT=length(y);
% f=fs/2*linspace(0,1,NFFT/2);
% plot(f,abs(y(1:NFFT/2)));
% title('滤波后的傅立叶变换');
% grid on;


% --------------------------------------------------------------------
function Untitled_34_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function tuo_Callback(hObject, eventdata, handles)
% hObject    handle to tuo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function hanning_Callback(hObject, eventdata, handles)
% hObject    handle to hanning (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function boxcar_Callback(hObject, eventdata, handles)
% hObject    handle to boxcar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function kaise_Callback(hObject, eventdata, handles)
% hObject    handle to kaise (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ButterworthLP_Callback(hObject, eventdata, handles)
% hObject    handle to ButterworthLP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ButterworthHP_Callback(hObject, eventdata, handles)
% hObject    handle to ButterworthHP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ButterworthBP_Callback(hObject, eventdata, handles)
% hObject    handle to ButterworthBP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ButterworthBS_Callback(hObject, eventdata, handles)
% hObject    handle to ButterworthBS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




function Rp_Callback(hObject, eventdata, handles)
% hObject    handle to Rp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Rp as text
%        str2double(get(hObject,'String')) returns contents of Rp as a double


% --- Executes during object creation, after setting all properties.
function Rp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Rp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function Rs_Callback(hObject, eventdata, handles)
% hObject    handle to Rs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of Rs as text
%        str2double(get(hObject,'String')) returns contents of Rs as a double


% --- Executes during object creation, after setting all properties.
function Rs_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Rs (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function Cherbyshev2LP_Callback(hObject, eventdata, handles)
% hObject    handle to Cherbyshev2LP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Cherbyshev1LP_Callback(hObject, eventdata, handles)
% hObject    handle to Cherbyshev1LP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --------------------------------------------------------------------
function Untitled_44_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_44 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_45_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_45 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_46_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_46 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton9.
function pushbutton9_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
var=get(handles.pushbutton9,'value');
if var==1;
    close(gui)
end;

% --------------------------------------------------------------------
function Untitled_35_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_35 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_36_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_36 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global signal2;
fs=str2num(get(handles.Fs2,'string'));
Xn=str2num(get(handles.Xlength,'string'));
t=[0:1/fs:(Xn-1)/fs];
y1=signal;y2=signal2;
l1=length(y1);l2=length(y2);
if l1~=l2
    errordlg('两信号长度不等，请重新输入','输入错误','modal')
end
y=y1+y2;
axes(handles.axes3)
stem(t,y,'.');title('序列相加')  



% --------------------------------------------------------------------
function Untitled_37_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_37 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global signal2;
fs=str2num(get(handles.Fs2,'string'));
Xn=str2num(get(handles.Xlength,'string'));
t=[0:1/fs:(Xn-1)/fs];
y1=signal;y2=signal2;
l1=length(y1);l2=length(y2);
if l1~=l2
    errordlg('两信号长度不等，请重新输入','输入错误','modal')
end
y=y1.*y2;
axes(handles.axes3)
stem(t,y,'.');title('序列相乘');


% --------------------------------------------------------------------
function Untitled_38_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%时域翻转
global signal;
w=linspace(-2*pi,2*pi,500);
N=length(signal);
if N>=500
  N=500;
else N=length(signal);
end
n=0:N-1;
x=signal(1:N);
[x1,m]=sigfold(x,n);
y=x*exp(-j*n'*w);
y1=x1*exp(-j*n'*w);
%Y=x*exp(j*n'*w);
% figure
% subplot(321);stem(n,x,'.');title('原信号X（n）')
% subplot(322);plot(w,y);title('X(exp^(jw))')
% subplot(323);stem(m,x1,'.');title('时域翻转X（-n）')
% subplot(324);plot(w,y1);title('信号翻转后X(exp^(-jw))')
axes(handles.axes3)
stem(m,x1,'.');title('时域翻转X（-n）')

% --------------------------------------------------------------------
function Untitled_40_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_40 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%时域移位？？？？？？？？？？？
global signal;
w=linspace(-2*pi,2*pi,500);
N=length(signal);
if N>=500
  N=500;
else N=length(signal);
end
n=0:N-1;
x=signal(1:N);
m=0:N-1;
str={'时域移位的尺度n0='};
strdef={'2'};
data=inputdlg(str,'x(n+n0)',1,strdef);
n0=str2double(data(1));
[x1,n]=sigshift(x,m,n0);
y1=x1*exp(-j*n'*w); 
% figure
% subplot(311)
axes(handles.axes3)
stem(n,x1,'.');title('移位信号')
%subplot(312)
%plot(w,y1)

% --------------------------------------------------------------------
function Untitled_42_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_42 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global signal2;
%global fs;
x1=signal;x2=signal2;
l1=length(x1);l2=length(x2);
%n1=0:l1-1;n2=0:l2-1;
l3=length(x1)+length(x2)-1;
%n3=0:N3;
NFFT1=2^nextpow2(l1);NFFT2=2^nextpow2(l2);
NFFT3=2^nextpow2(l3);
%a1=fs/2*linspace(0,1,NFFT1/2+1); % 单边拉普拉斯变换
%a2=fs/2*linspace(0,1,NFFT2/2+1);
y1=fft(x1,NFFT1)/l1;y2=fft(x2,NFFT2)/l2;
NFFT4=2^nextpow2(NFFT1+NFFT2-1);
y4=ifft((y1.*y2));
nx1=0:(l1-1);nx2=0:(l2-1);
[y,ny]=conv_m(x1,nx1,x2,nx2);
y3=y;
axes(handles.axes3)
stem(ny,y,'.');title('两信号的时域卷积');
figure
subplot(221);stem(y1,'.');title('信号1的傅里叶变换');
subplot(222);stem(y2,'.');title('信号2的傅里叶变换');
subplot(223);stem(y3,'.');title('两信号时域卷积');
subplot(224);stem(y4,'.');title('两信号频域乘积的反傅里叶变换');




% --------------------------------------------------------------------
function Untitled_50_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_50 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_51_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_51 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_52_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_52 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%信号序列产生；
global signal;
global fs;
Fs=fs;xn=signal;
%用修正协方差方法估计相关矩阵
X=corrmtx(xn,7,'mod'); 

%用MUSIC算法估计序列的功率谱
axes(handles.axes2)
pmusic(X,2);
title('基于MUSIC算法的功率谱估计')
ylabel('功率谱幅度(dB)')
xlabel('归一化频率(rad/sample)')


% --------------------------------------------------------------------
function xcorrelation_Callback(hObject, eventdata, handles)
% hObject    handle to xcorrelation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global fs;
y=signal;
Cx=xcorr(y,'unbiased'); %1001
Cxk=fft(Cx,1024); %1024
Pxx=abs(Cxk); %1024
t=0:round(1024/2-1);%round表示四舍五入取整 512
k=t*fs/1024; %512
%k=str2num(get(handles.Edit_fm,'String'));
P=10*log(Pxx(t+1)); %512
axes(handles.axes3);
plot(k,P); 
%axis([-Xaxis,Xaxis,-Yaxis,Yaxis]);
title('自相关函数法');

% --------------------------------------------------------------------
function PNone_Callback(hObject, eventdata, handles)
% hObject    handle to PNone (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes3);
global signal;
global fs;
y=signal;
periodogram(y,[],1024,fs);


% --------------------------------------------------------------------
function PBoxcar_Callback(hObject, eventdata, handles)
% hObject    handle to PBoxcar (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes3);
global signal;
global fs;
y=signal;
window=boxcar(length(y));
periodogram(y,window,1024,fs);
clear;

% --------------------------------------------------------------------
function PHamming_Callback(hObject, eventdata, handles)
% hObject    handle to PHamming (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes3);
global signal;
global fs;
y=signal;
window=hamming(length(y));
periodogram(y,window,1024,fs);

% --------------------------------------------------------------------
function PBlackman_Callback(hObject, eventdata, handles)
% hObject    handle to PBlackman (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes3);
global signal;
global fs;
y=signal;
window=blackman(length(y));
periodogram(y,window,1024,fs);

% --------------------------------------------------------------------
function PBartlett_Callback(hObject, eventdata, handles)
% hObject    handle to PBartlett (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes3);
global signal;
global fs;
y=signal;
window=bartlett(length(y));
periodogram(y,window,1024,fs);


% --------------------------------------------------------------------
function Untitled_53_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_53 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_54_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_54 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_55_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_55 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_56_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_56 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load wbarb
figure(1);
image(X);colormap(map);
title('原图');
[cA,cH,cV,cD]=dwt2(X,'db7');
A1=upcoef2('a',cA,'db7',1);
H1=upcoef2('h',cH,'db7',1);
V1=upcoef2('v',cV,'db7',1);
D1=upcoef2('d',cD,'db7',1);
figure(2);
colormap(map);
colnb=size(map,1);
subplot(2,2,1);
image(wcodemat(cA,colnb));
title('分解A1');
subplot(2,2,2);
image(wcodemat(cH,colnb));
title('分解H1');
subplot(2,2,3);
image(wcodemat(cV,colnb));
title('分解V1');
subplot(2,2,4);
image(wcodemat(cD,colnb));
title('分解D1');
I=idwt2(cA,cH,cV,cD,'db7');
figure(3);
image(I);colormap(map);
title('利用分解图重构');


% --------------------------------------------------------------------
function Untitled_57_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_57 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load chirp;
s=y;
[c,l]=wavedec(s,3,'db3');
ls=length(s);
figure(1);
subplot(211);
plot(s);
Ylabel('s');
sound(y,Fs);
[cal1,cdl1]=dwt(s,'db1');
subplot(223);
plot(cal1);
Ylabel('cal1');
subplot(224);
plot(cdl1);
Ylabel('cdl1');
%a1=upcoef('a',cal1,'db1',1,ls);
%d1=upcoef('d',cdl1,'db1',1,ls);


% --------------------------------------------------------------------
function Untitled_58_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_58 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load chirp;
s=y;
ls=length(s);
[cal1,cdl1]=dwt(s,'db1');
s1=cal1;
ls1=length(s1);
[c,l]=wavedec(s1,3,'db3');
figure(2);
subplot(211);
plot(s1);
Ylabel('s');
sound(cal1,Fs);
[cal2,cdl2]=dwt(s1,'db1');
subplot(223);
plot(cal2);
Ylabel('cal2');
subplot(224);
plot(cdl2);
Ylabel('cdl2');
a1=upcoef('a',cal2,'db1',1,ls1);
d1=upcoef('d',cdl2,'db1',1,ls1);

% --------------------------------------------------------------------
function Untitled_59_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_59 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load chirp;
s=y;
[cal1,cdl1]=dwt(s,'db1');
s=cal1;
[cal2,cdl2]=dwt(s,'db1');
s=cal2;
ls=length(s);
[c,l]=wavedec(s,3,'db3');
thr=35;
ls=length(s);
figure(3);
subplot(211);
plot(s);
Ylabel('s');
sound(cal2,Fs);
[cal3,cdl3]=dwt(s,'db1');
subplot(223);
plot(cal3);
Ylabel('cal3');
subplot(224);
plot(cdl3);
Ylabel('cdl3');
a1=upcoef('a',cal3,'db1',1,ls);
d1=upcoef('d',cdl3,'db1',1,ls);

% --------------------------------------------------------------------
function Untitled_60_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_60 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load chirp;
y=chirp;
s=y;
ls=length(s);
[c,l]=wavedec(s,3,'db3');
thr=35;
ls=length(s);
sound(y,Fs);
[cal1,cdl1]=dwt(s,'db1');
s=cal1;w='db1';
lx=length(s);
figure(1)
subplot(221);
plot(s);
Ylabel('s');
dwtmode('zpd');
[cazpd,cdzpd]=dwt(s,w);
lxtzpd=16*length(cazpd)
xzpd=idwt(cazpd,cdzpd,w,lx);
subplot(222);
plot(xzpd);
Ylabel('xzpd');
sound(xzpd,Fs);
dwtmode('sym');
[casym,cdsym]=dwt(s,w);
lxtsym=16*length(casym)
xsym=idwt(casym,cdsym,w,lx);
subplot(223);
plot(xsym);
Ylabel('xsym');
sound(xsym,Fs);
dwtmode('spd');
[caspd,cdspd]=dwt(s,w);
lxtspd=16*length(caspd)
xspd=idwt(caspd,cdspd,w,lx);
subplot(224);
plot(xspd);
Ylabel('xspd');
sound(xspd,Fs);


% --------------------------------------------------------------------
function Untitled_61_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_61 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
% global lev;
% global alpha;
% str={'请输入lev=','请输入alpha='};
% strdef={'5','2'};
% SCData=inputdlg(str,'输入参数',1,strdef);
% lev=str2double(SCData(1));
% alpha=str2double(SCData(2));
% load noisbump;
lev=5;
alpha=2;
x=signal;
%x=noisbump;
wname='sym6';
[c,l]=wavedec(x,5,wname);
sigma=wnoisest(c,l,1);
thr=wbmpen(c,l,sigma,alpha);
keepapp=1;
xd=wdencmp('gbl',c,l,wname,lev,thr,'s',keepapp);
axes(handles.axes1);
plot(x);title('原始信号')
grid;
axes(handles.axes2);
plot(xd);title('消噪信号')
grid;
% --------------------------------------------------------------------
function Untitled_62_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_62 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
load sinsin
init=20100111;
randn('seed',init);
x=X+18*randn(size(X));
[thr,sorh,keepapp]=ddencmp('den','wv',x);
xd=wdencmp('gbl',x,'sym4',2,thr,sorh,keepapp);
axes(handles.axes1);
imshow(X,map);
title('原图');
axes(handles.axes2);
imshow(x,map);
title('加噪图');
axes(handles.axes3);
imshow(xd,map);
title('消噪后图');
axes(handles.axes4);
cla


% --------------------------------------------------------------------
function Untitled_66_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_66 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global fs;
Fs=fs;
%n=0:1/Fs:.3;
% w0=200*pi;
% w1=400*pi;
%xn=cos(w0*n)+sin(w1*n)+randn(size(n));
xn=signal;

% 使用Yuler-Walker方法估计序列功率谱；
p=floor(length(xn)/3)+1;
nfft=1024;
[xpsd,f]=pyulear(xn,p,nfft,Fs,'half');

% 绘制功率谱估计
pmax=max(xpsd);
xpsd=xpsd/pmax;
xpsd=10*log10(xpsd+0.000001);
axes(handles.axes2)
plot(f,xpsd);
% handles.h=h;
% guidata(hObject,handles);

title('基于Yule-Walker方法的功率谱估计')
ylabel('功率谱密度(dB)')
xlabel('频率(Hz)')
grid on;
ymin = min(xpsd)-2;
ymax = max(xpsd)+2;


% --------------------------------------------------------------------
function Untitled_67_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_67 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global fs;
Fs=fs; % 采样频率
xn=signal;

% 使用Burg算法估计序列功率谱；
p=floor(length(xn)/3)+1;
nfft=1024;
[xpsd,f]=pburg(xn,p,nfft,Fs,'half');

% 绘制功率谱估计
pmax=max(xpsd);
xpsd=xpsd/pmax;
xpsd=10*log10(xpsd+0.000001);
axes(handles.axes2)
plot(f,xpsd);

% handles.h=h;
% guidata(hObject,handles);
title('基于Burg算法的功率谱估计')
ylabel('功率谱密度(dB)')
xlabel('频率(Hz)')
grid on;
ymin = min(xpsd)-2;
ymax = max(xpsd)+2;


% --------------------------------------------------------------------
function Untitled_68_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_68 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global fs;
Fs=fs; % 采样频率
xn=signal;
% 使用协方差法估计序列功率谱；
p=floor(length(xn)/3)+1;
nfft=1024;
[xpsd,f]=pcov(xn,p,nfft,Fs,'half');

% 绘制功率谱估计
pmax=max(xpsd);
xpsd=xpsd/pmax;
xpsd=10*log10(xpsd+0.000001);
axes(handles.axes2)
plot(f,xpsd);
title('基于协方差方法的功率谱估计')
ylabel('功率谱密度(dB)')
xlabel('频率(Hz)')
grid on;


% --------------------------------------------------------------------
function idft1_Callback(hObject, eventdata, handles)
% hObject    handle to idft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%有限长序列傅里叶反变换实现程序
global signal;
N=length(signal);
n=0:N-1;k=0:N-1;
Xk=signal*exp(-j*2*pi/N).^(n'*k); %离散傅里叶变换
x=(Xk*exp(j*2*pi/N).^(n'*k))/N;%离散傅里叶逆变换
axes(handles.axes4);
if N>200
    plot(x)
else
stem(n,x,'.');
end
title('IDFT|X(k)|');
grid;

% --------------------------------------------------------------------
function Untitled_64_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_64 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ifft1_Callback(hObject, eventdata, handles)
% hObject    handle to ifft1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global signal;
global sft;
N1=length(signal);
n=0:N1-1;
X1k=fft(signal);                %计算N点DFT[x1(n)]
xn=ifft(X1k);
axes(handles.axes3);
if N1>100
plot(xn)
else stem(xn,'.')
end
grid;
title('快速傅里叶反变换');

% --- Executes on button press in pushbutton11.
function pushbutton11_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes1)
grid on;
axes(handles.axes2)
grid on;
axes(handles.axes3)
grid on;
axes(handles.axes4)
grid on;


% --------------------------------------------------------------------
function Untitled_69_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_69 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;global fs;
xn=signal;Fs=fs;
%用修正协方差方法估计相关矩阵
X=corrmtx(xn,12,'mod'); 

%用特征向量方法估计序列的功率谱
axes(handles.axes2)
peig(X,3,'whole') 
title('基于特征向量方法的功率谱估计')
ylabel('功率谱幅度(dB)')
xlabel('归一化频率(rad/sample)')



% --------------------------------------------------------------------
function Untitled_70_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_70 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
global fs;
Fs=fs; % 采样频率
xn=signal;
% 使用改进协方差方法估计序列功率谱；
p=floor(length(xn)/3)+1;
nfft=1024;
[xpsd,f]=pmcov(xn,p,nfft,Fs,'half');

% 绘制功率谱估计
pmax=max(xpsd);
xpsd=xpsd/pmax;
xpsd=10*log10(xpsd+0.000001);
axes(handles.axes2)
plot(f,xpsd);
title('基于改进协方差方法的功率谱估计')
ylabel('功率谱密度(dB)')
xlabel('频率(Hz)')
grid on;

% --------------------------------------------------------------------
function Untitled_71_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_71 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
global fs;
xn=signal;Fs=fs;
% 使用改进协方差方法估计序列功率谱；
p=floor(length(xn)/3)+1;
nfft=1024;
[xpsd,f]=pmem(xn,p,nfft,Fs,'half');

% 绘制功率谱估计
pmax=max(xpsd);
xpsd=xpsd/pmax;
xpsd=10*log10(xpsd+0.000001);
axes(handles.axes2)
plot(f,xpsd);
title('基于改进协方差方法的功率谱估计')
ylabel('功率谱密度(dB)')
xlabel('频率(Hz)')
grid on;

% --------------------------------------------------------------------
function Untitled_72_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_72 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
%global fs;Fs=fs;
N=length(signal);
xn=signal;
var=sqrt(1/exp(1.0));
e=var*randn(1,N);
xn=xn+e;


% 估计自相关函数；
m=-500:500;
[r,lag]=xcorr(xn,500,'biased');

R=[r(501) r(502) r(503) r(504);
   r(500) r(501) r(502) r(503);
   r(499) r(500) r(501) r(502);
   r(498) r(499) r(500) r(501)];

[V,D]=eig(R);
V3=[V(1,3),V(2,3),V(3,3),V(4,3)].';
V3=[V(1,4),V(2,4),V(3,4),V(4,4)].';

p=0:3;
wm=[0:0.002*pi:2*pi];
B=[(exp(-j)).^(wm'*p)];
A=B.';

%最小方差功率谱估计
z=A'*inv(R)*A;
Z=diag(z');
pmv=1./Z;
axes(handles.axes2)
plot(wm/pi,pmv);
title('基于最小方差的功率谱估计')
ylabel('功率谱幅度(dB)')
xlabel('角度频率,w/pi')
grid on;


% --------------------------------------------------------------------
function Untitled_73_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_73 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
global fs;
Fs=fs;xn=signal;
l=length(xn);
% 计算序列的自相关函数
m=-500:500;
[r,lag]=xcorr(xn,500,'biased');

axes(handles.axes2)
hndl=stem(m,r);
h=hndl;
handles.h=h;
guidata(hObject,handles);
set(hndl,'Marker','.')
set(hndl,'MarkerSize',2);
ylabel('自相关函数R(m)')
% 利用间接法计算功率谱
k=0:1000;
w=(pi/500)*k;
M=k/500;
X=r*(exp(-j*pi/500).^(m'*k));
magX=abs(X);
axes(handles.axes3)
plot(M,10*log10(magX));
xlabel('功率谱的BT法估计')

% --------------------------------------------------------------------
function Untitled_74_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_74 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
global fs;
xn=signal;Fs=fs;

%参数设置
nfft=1024;
window=boxcar(1001);
noverlap=0;
p=0.9;
%计算序列的PSD
[Pxx,Pxxc]=psd(xn,nfft,Fs,window,noverlap,p);
%绘制图形
index=0:round(nfft/2-1);
%k=index*Fs/nfft;
k=index;
plot_Pxx=10*log10(Pxx(index+1));
plot_Pxxc=10*log10(Pxxc(index+1));
%功率谱的对数曲线
axes(handles.axes2)
plot(k,plot_Pxx);
ylabel('功率谱的对数曲线')
%置信区间中的功率谱曲线
axes(handles.axes3)
plot(k,[plot_Pxx plot_Pxx-plot_Pxxc plot_Pxx+plot_Pxxc]);
xlabel('置信区间中的功率谱曲线')

% --------------------------------------------------------------------
function Untitled_75_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_75 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
global signal;
global fs;
xn=signal;Fs=fs;
% 用 Welch 平均估计序列的功率谱；
nfft=1024;
window=hamming(100);
noverlap=20;
range='half';
[Pxx,f] = pwelch(xn,window,noverlap,nfft,Fs);
plot_Pxx=10*log10(Pxx);
axes(handles.axes2)
h=plot(f,plot_Pxx);
handles.h=h;
guidata(hObject,handles);
title('Welch 法平均功率谱估计')


% --- Executes on button press in pushbutton12.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes1)
cla
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla


% --------------------------------------------------------------------
function Untitled_76_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_76 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_77_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_77 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% global signal;
% global Zsignal;
% f = signal;
% F=ztrans(f);
% Zsignal=F;
% [n,d]=numden(F);
% a=sym2poly(n);
% b=sym2poly(d);
% axes(handles.axes2);
% zplane(a,b)
% title('零极点图')
% [H,w]=freqz(a,b,1000);
% magH=abs(H);phaH=angle(H);
% axes(handles.axes3);
% plot(w,magH);
% xlabel('');
% ylabel('幅度');
% title('幅度响应');
% grid;
% axes(handles.axes4);
% plot(w,phaH);
% xlabel('角频率');
% ylabel('相位');
% title('相位响应');
% grid;
a0=handles.a;b0=handles.b;c0=handles.c;M0=handles.M;
a1=handles.a1;b1=handles.b1;c1=handles.c1;M1=handles.M1;
b=[a1,b1,c1,M1];
a=[a0,b0,c0,M0];
[z,p,k]=tf2zp(b,a);
disp('零点：');disp(z');disp('极点：');disp(p');disp('增益：');disp(k');
axes(handles.axes1);
zplane(z,p);title('系统的极、零点分布图');
axes(handles.axes3);
clc;



% --------------------------------------------------------------------
function Untitled_78_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_78 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a0=handles.a;b0=handles.b;c0=handles.c;M0=handles.M;
a1=handles.a1;b1=handles.b1;c1=handles.c1;M1=handles.M1;
b=[a1,b1,c1,M1];
a=[a0,b0,c0,M0];
[H,w]=freqz(b,a,100);
magH=abs(H);
axes(handles.axes2);
stem(w,magH);grid;
xlabel('角频率');ylabel('幅度') ;title('幅度相应');


% --------------------------------------------------------------------
function Untitled_79_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_79 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_80_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_80 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla
global signal;
x=signal;
y=hilbert(x);
axes(handles.axes2)
% plot(imag(y));
plot(y)
title('序列Hilbert变换结果')
axes(handles.axes3)
plot(imag(y));
axes(handles.axes4)
plot(real(y));

% --------------------------------------------------------------------
function Untitled_81_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_81 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.axes2)
cla
axes(handles.axes3)
cla
axes(handles.axes4)
cla
global signal;
x=signal;
N=128;
M=N;
W=exp(-j*2*pi/M);

% A=1CZT
A=1;
Y1=czt(x,M,W,A);
axes(handles.axes2)
plot(abs(Y1(1:N/2)));
title('A=1时的CZT');
grid on;
% ¨¨A¨CZT
fs=40;
M=60;
f0=7.2;
DELf=0.05;
A=exp(j*2*pi*f0/fs);
W=exp(-j*2*pi*DELf/fs);
Y3=czt(x,M,W,A);
n2=f0:DELf:f0+(M-1)*DELf;
axes(handles.axes3)
plot(n2,abs(Y3));
ylabel('详细构造A后的CZT')
grid on;



function a_Callback(hObject, eventdata, handles)
% hObject    handle to a (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of a as text
%        str2double(get(hObject,'String')) returns contents of a as a double


% --- Executes during object creation, after setting all properties.
function a_CreateFcn(hObject, eventdata, handles)
% hObject    handle to a (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function b_Callback(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b as text
%        str2double(get(hObject,'String')) returns contents of b as a double


% --- Executes during object creation, after setting all properties.
function b_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function b1_Callback(hObject, eventdata, handles)
% hObject    handle to b1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of b1 as text
%        str2double(get(hObject,'String')) returns contents of b1 as a double


% --- Executes during object creation, after setting all properties.
function b1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to b1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function c1_Callback(hObject, eventdata, handles)
% hObject    handle to c1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of c1 as text
%        str2double(get(hObject,'String')) returns contents of c1 as a double


% --- Executes during object creation, after setting all properties.
function c1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to c1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function a1_Callback(hObject, eventdata, handles)
% hObject    handle to a1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of a1 as text
%        str2double(get(hObject,'String')) returns contents of a1 as a double


% --- Executes during object creation, after setting all properties.
function a1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to a1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function c_Callback(hObject, eventdata, handles)
% hObject    handle to c (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of c as text
%        str2double(get(hObject,'String')) returns contents of c as a double


% --- Executes during object creation, after setting all properties.
function c_CreateFcn(hObject, eventdata, handles)
% hObject    handle to c (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function M1_Callback(hObject, eventdata, handles)
% hObject    handle to M1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of M1 as text
%        str2double(get(hObject,'String')) returns contents of M1 as a double


% --- Executes during object creation, after setting all properties.
function M1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to M1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function N_Callback(hObject, eventdata, handles)
% hObject    handle to N (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of N as text
%        str2double(get(hObject,'String')) returns contents of N as a double


% --- Executes during object creation, after setting all properties.
function N_CreateFcn(hObject, eventdata, handles)
% hObject    handle to N (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function M_Callback(hObject, eventdata, handles)
% hObject    handle to M (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of M as text
%        str2double(get(hObject,'String')) returns contents of M as a double


% --- Executes during object creation, after setting all properties.
function M_CreateFcn(hObject, eventdata, handles)
% hObject    handle to M (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --------------------------------------------------------------------
function Untitled_82_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_82 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a0=handles.a;b0=handles.b;c0=handles.c;M0=handles.M;
a1=handles.a1;b1=handles.b1;c1=handles.c1;M1=handles.M1;
b=[a1,b1,c1,M1];
a=[a0,b0,c0,M0];
[H,w]=freqz(b,a,100);
phaH=angle(H);
axes(handles.axes3);
stem(w,phaH);grid;
xlabel('角频率');ylabel('相位');
title('相位响应')
