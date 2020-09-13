
function varargout = Cluster(varargin)

% CLUSTER M-file for Cluster.fig
%      CLUSTER, by itself, creates a new CLUSTER or raises the existing
%      singleton*.
%
%      H = CLUSTER returns the handle to a new CLUSTER or the handle to
%      the existing singleton*.
%
%      CLUSTER('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CLUSTER.M with the given input arguments.
%
%      CLUSTER('Property','Value',...) creates a new CLUSTER or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Cluster_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Cluster_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Cluster

% Last Modified by GUIDE v2.5 02-Dec-2011 01:07:46

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Cluster_OpeningFcn, ...
                   'gui_OutputFcn',  @Cluster_OutputFcn, ...
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


% --- Executes just before Cluster is made visible.
function Cluster_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Cluster (see VARARGIN)

% Choose default command line output for Cluster
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Cluster wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Cluster_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
global patternStatus;
patternStatus=0;

% --- Executes on button press in Clear.
function Clear_Callback(hObject, eventdata, handles)
% hObject    handle to Clear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global activex;
activex.invoke('ResetNum');

%handlse.activex2.DrawStandardNum;

% --- Executes on button press in Input1.
function Input1_Callback(hObject, eventdata, handles)
InputStandardNum(1,handles);

% --- Executes on button press in Input2.
function Input2_Callback(hObject, eventdata, handles)
InputStandardNum(2,handles);

% --- Executes on button press in Input3.
function Input3_Callback(hObject, eventdata, handles)
InputStandardNum(3,handles);

% --- Executes on button press in Input4.
function Input4_Callback(hObject, eventdata, handles)
InputStandardNum(4,handles);

% --- Executes on button press in Input5.
function Input5_Callback(hObject, eventdata, handles)
InputStandardNum(5,handles);

% --- Executes on button press in Input6.
function Input6_Callback(hObject, eventdata, handles)
InputStandardNum(6,handles);

% --- Executes on button press in Input7.
function Input7_Callback(hObject, eventdata, handles)
InputStandardNum(7,handles);

% --- Executes on button press in Input8.
function Input8_Callback(hObject, eventdata, handles)
InputStandardNum(8,handles);

% --- Executes on button press in Input9.
function Input9_Callback(hObject, eventdata, handles)
InputStandardNum(9,handles);

% --- Executes on button press in Input0.
function Input0_Callback(hObject, eventdata, handles)
InputStandardNum(0,handles);


function InputStandardNum(num,handles)
global activex;
activex.invoke('DrawStandardNum',num);


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over Clear.
function Clear_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to Clear (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in ClearRight.
function ClearRight_Callback(hObject, eventdata, handles)
% hObject    handle to ClearRight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes(handles.ShowResult);
temp=imread('Clear.bmp');
imshow(temp);
set(handles.textResult,'String','');
%cla reset;


% --- Executes on button press in HandWrite.
function HandWrite_Callback(hObject, eventdata, handles)
% hObject    handle to HandWrite (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
a=get(handles.PicLeft,'Position');
b=get(handles.Input,'Position');
c=[a(1)+b(1)-1 a(2)+b(2)+2 a(3) a(4)];
set(handles.PicLeft,'Visible','Off');
global activex;
activex=actxcontrol('CLUSTERL.Clusterl1ctrl.1',c);
set(handles.InputStandard,'visible','On');
set(handles.Clear,'visible','On');
set(handles.OpenPic,'visible','Off');
set(handles.HandWrite,'Enable','Off');
set(handles.PicPattern,'Enable','On');
set(handles.InputPattern,'String','当前为手写模式');

% --- Executes on button press in PicPattern.
function PicPattern_Callback(hObject, eventdata, handles)
% hObject    handle to PicPattern (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global activex;
delete(activex); 

set(handles.PicLeft,'Visible','On');
set(handles.InputStandard,'visible','Off');
set(handles.Clear,'visible','Off');
set(handles.OpenPic,'visible','On');
set(handles.HandWrite,'Enable','On');
set(handles.PicPattern,'Enable','Off');
set(handles.InputPattern,'String','当前为位图模式');
axes(handles.PicLeft);
temp=imread('Clear.bmp');
imshow(temp);



% --- Executes on button press in OpenPic.
function OpenPic_Callback(hObject, eventdata, handles)
% hObject    handle to OpenPic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[fname,pname]=uigetfile({'*.bmp';'*.jpg';'*.*'},'File Selector');
global Data;%源图像
global pic;%二值图像
Data=imread([pname fname]);
axes(handles.PicLeft);
pic=im2bw(Data,0.3);
imshow(Data);
global patternStatus;
patternStatus=1;


%显示聚类结果
function ShowResult( pattern,patternnum, handles )
global Data;
global height;
global width;
axes(handles.ShowResult);
imshow(Data);
pos=get(handles.ShowResult,'Position');
widthRatio=pos(3)/width;
heightRatio=pos(4)/height;
if(widthRatio<heightRatio)
    heightRatio=widthRatio;
else
    widthRatio=heightRatio;
end
for i=1:patternnum
    str1=num2str(pattern(i).index);
    str2=['类号:' num2str(pattern(i).category)];
    text((pattern(i).rightbottom_x*widthRatio),(height*heightRatio-pattern(i).lefttop_y*heightRatio+3),str1,'Units','pixels','Color','Blue');%显示索引
    text((pattern(i).lefttop_x*widthRatio-3),(height*heightRatio-pattern(i).rightbottom_y*heightRatio-6),str2,'Units','pixels','Color','Red');%显示类别
end


% --------------------------------------------------------------------
function ZuiJinLin_Callback(hObject, eventdata, handles)
% hObject    handle to ZuiJinLin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZuiLinJin( m_pattern,patternNum );%最临近聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','最临近规则聚类结果');
set(gcf,'Pointer','arrow');





% --------------------------------------------------------------------
function Cluster_Callback(hObject, eventdata, handles)
% hObject    handle to Cluster (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Unknown_Callback(hObject, eventdata, handles)
% hObject    handle to Unknown (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --------------------------------------------------------------------
function ZuiDaZuiXiaoJuLi_Callback(hObject, eventdata, handles)
% hObject    handle to ZuiDaZuiXiaoJuLi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZuiDaZuiXiaoJuLi( m_pattern,patternNum );%最大最小距离法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','最大最小距离法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function Layer_Callback(hObject, eventdata, handles)
% hObject    handle to Layer (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ZuiDuanJuLi_Callback(hObject, eventdata, handles)
% hObject    handle to ZuiDuanJuLi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZuiDuanJuLi( m_pattern,patternNum );%最短距离法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','最短距离法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function ZuiChangJuLi_Callback(hObject, eventdata, handles)
% hObject    handle to ZuiChangJuLi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZuiChangJuLi( m_pattern,patternNum );%最长距离法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','最长距离法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function ZhongJianJuLi_Callback(hObject, eventdata, handles)
% hObject    handle to ZhongJianJuLi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZhongJianJuLi( m_pattern,patternNum );%中间距离法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','中间距离法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function ZhongXin_Callback(hObject, eventdata, handles)
% hObject    handle to ZhongXin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ZhongXin( m_pattern,patternNum );%重心法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','重心法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function LePingJunJuLi_Callback(hObject, eventdata, handles)
% hObject    handle to LePingJunJuLi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_LeiPingJunJuLi( m_pattern,patternNum );%类平均距离法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','类平均距离法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function Dynamic_Callback(hObject, eventdata, handles)
% hObject    handle to Dynamic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function KJunZhi_Callback(hObject, eventdata, handles)
% hObject    handle to KJunZhi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_KJunZhi( m_pattern,patternNum );%K均值法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','K均值法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function ISODATA_Callback(hObject, eventdata, handles)
% hObject    handle to ISODATA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ISODATA( m_pattern,patternNum );%ISODATA聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','ISODATA聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function Fuzzy_Callback(hObject, eventdata, handles)
% hObject    handle to Fuzzy (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function FuzzyCluster_Callback(hObject, eventdata, handles)
% hObject    handle to FuzzyCluster (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_FuzzyCluster( m_pattern,patternNum );%模糊聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','模糊聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function Genetic_Callback(hObject, eventdata, handles)
% hObject    handle to Genetic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function GA_Callback(hObject, eventdata, handles)
% hObject    handle to GA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_GA( m_pattern,patternNum );%遗传算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','遗传算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function CSA_Callback(hObject, eventdata, handles)
% hObject    handle to CSA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSA( m_pattern,patternNum );%遗传算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','克隆选择算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function EP_Callback(hObject, eventdata, handles)
% hObject    handle to EP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EP( m_pattern,patternNum );%进化规划算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','进化规划算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function ES_Callback(hObject, eventdata, handles)
% hObject    handle to ES (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ES( m_pattern,patternNum );%进化策略算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','进化策略算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function popCluster_Callback(hObject, eventdata, handles)
% hObject    handle to popCluster (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --------------------------------------------------------------------
function AF_Callback(hObject, eventdata, handles)
% hObject    handle to C_ArtificialFish (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AF( m_pattern,patternNum );%人工鱼群算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','人工鱼群算法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function SFLA_Callback(hObject, eventdata, handles)
% hObject    handle to SFLA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_SFLA( m_pattern,patternNum );%蛙跳算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','蛙跳算法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function AntUnknown_Callback(hObject, eventdata, handles)
% hObject    handle to AntUnknown (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AntCluster( m_pattern,patternNum );%蚁群算法聚类(未知聚类数目)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','蚁群算法聚类结果(未知聚类数目)');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function AntKnown_Callback(hObject, eventdata, handles)
% hObject    handle to AntKnown (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AntClusterKnown( m_pattern,patternNum );%蚁群算法聚类(已知聚类数目)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','蚁群算法聚类结果(已知聚类数目)');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function PSO_Callback(hObject, eventdata, handles)
% hObject    handle to PSO (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_PSO( m_pattern,patternNum );%粒子群算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','粒子群算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function MoNiTuiHuo_Callback(hObject, eventdata, handles)
% hObject    handle to MoNiTuiHuo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_MoNiTuiHuo( m_pattern,patternNum );%模拟退火算法聚类
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','模拟退火算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function KJunZhi2_Callback(hObject, eventdata, handles)
% hObject    handle to KJunZhi2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_KJunZhi2( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','K均值法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function LIANGZI_Callback(hObject, eventdata, handles)
% hObject    handle to LIANGZI (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)




% --------------------------------------------------------------------
function UserHelp_Callback(hObject, eventdata, handles)
% hObject    handle to UserHelp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
str1='聚类分析软件使用帮助：';
str2='聚类分析软件主界面分为输入面板（左）和输出面板（右），输入面板用于输入聚类样品，输出面板显示聚类结果。';
strb1='';
str3='聚类分析过程按如下操作步骤进行。';
str4='1.    输入样品。';
str5='      输入样品有两种方式：1) 位图输入 2) 手写输入';
str6='      1) 位图输入：';
str7='                    点击左上方^输入模式^面板中的^位图模式^按钮(软件启动后默认为位图模式），';
str8='                    输入面板即转换为位图输入，点击^打开一幅图片^按钮，弹出^打开位图对话框^，';
str9='                    选择一张含有聚类样品的图像，点击打开，输入面板中即显示出当前位图。';
str10='     2) 手写输入：';
str11='                   点击左上方^输入模式^面板中的^手写模式^按钮，输入面板即转换为手写输入，';
str12='                   此时可在面板中用鼠标手写数字或图形样品，也可以通过点击^输入标准数字^';
str13='                   面板中的数字按钮输入标准数字。';
str14='2.	选择聚类算法';
str15='     输入样品后，在主菜单中选择一种聚类算法，进行聚类分析。';
str16='3.	显示聚类结果';
str17='     聚类完成后，会在输出面板中显示聚类结果，样品右上方为样品序号，样品左下方为样品所属类别号。';
str=char(str1,str2,strb1,str3,strb1,str4,str5,strb1,str6,str7,str8,str9,strb1,str10,str11,str12,str13,strb1,str14,str15,strb1,str16,str17);
helpdlg(str,'聚类分析软件使用帮助');

% --------------------------------------------------------------------
function IGA_Callback(hObject, eventdata, handles)
% hObject    handle to IGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_IGA( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','免疫算法聚类结果');
set(gcf,'Pointer','arrow');









% --------------------------------------------------------------------
function QGA2_Callback(hObject, eventdata, handles)
% hObject    handle to QGA2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handset(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_QGA2( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','量子进化算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function QGA_Callback(hObject, eventdata, handles)
% hObject    handle to QGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_QGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','量子进化算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function exam_Callback(hObject, eventdata, handles)
% hObject    handle to exam (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=TEST( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','调试');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function CSO_Callback(hObject, eventdata, handles)
% hObject    handle to CSO (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSO( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','猫群算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function CPSO_Callback(hObject, eventdata, handles)
% hObject    handle to CPSO (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CPSO( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','猫群+粒子群算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function BFO_Callback(hObject, eventdata, handles)
% hObject    handle to BFO (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_BFO( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','细菌觅食算法聚类结果');
set(gcf,'Pointer','arrow');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% --------------------------------------------------------------------
function IM_Callback(hObject, eventdata, handles)%免疫算法聚类
% hObject    handle to IM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function C_IGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_IGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_IGA( m_pattern,patternNum );
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','免疫算法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function C_AIGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_AIGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AIGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','自适应免疫算法聚类结果');
set(gcf,'Pointer','arrow');








% --------------------------------------------------------------------
function C_DIGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_DIGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_DIGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','动态免疫算法聚类结果');
set(gcf,'Pointer','arrow');








% --------------------------------------------------------------------
function C_CSA_Callback(hObject, eventdata, handles)
% hObject    handle to C_CSA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','克隆选择算法聚类结果');
set(gcf,'Pointer','arrow');





% --------------------------------------------------------------------
function C_EAIGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_EAIGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EAIGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强自适应免疫算法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function C_EDIGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_EDIGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EDIGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强动态算法聚类结果');
set(gcf,'Pointer','arrow');





% --------------------------------------------------------------------
function EAIGA_Callback(hObject, eventdata, handles)
% hObject    handle to C_EAIGA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EAIGA( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强自适应免疫算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function C_IP_Callback(hObject, eventdata, handles)%免疫规划聚类
% hObject    handle to C_IP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_IP( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','免疫规划法算聚类结果');
set(gcf,'Pointer','arrow');




% --------------------------------------------------------------------
function C_AIP_Callback(hObject, eventdata, handles)
% hObject    handle to C_AIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AIP( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','自适应免疫规划算法聚类结果');
set(gcf,'Pointer','arrow');
% --------------------------------------------------------------------
function C_DIP_Callback(hObject, eventdata, handles)
% hObject    handle to C_DIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_DIP( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','动态免疫规划算法聚类结果');
set(gcf,'Pointer','arrow');





% --------------------------------------------------------------------
function C_EAIP_Callback(hObject, eventdata, handles)
% hObject    handle to C_EAIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EAIP( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强自适应免疫规划算法聚类结果');
set(gcf,'Pointer','arrow');
% --------------------------------------------------------------------
function C_EDIP_Callback(hObject, eventdata, handles)
% hObject    handle to C_EDIP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EDIP( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强动态免疫规划算法聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function IS_Callback(hObject, eventdata, handles)%免疫策略聚类
% hObject    handle to IS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function C_IS_Callback(hObject, eventdata, handles)
% hObject    handle to C_IP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_IS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','免疫策略算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function C_AIS_Callback(hObject, eventdata, handles)
% hObject    handle to C_AIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_AIS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','自适应免疫策略算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function C_EAIS_Callback(hObject, eventdata, handles)
% hObject    handle to C_EAIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EAIS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强免疫策略算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function C_DIS_Callback(hObject, eventdata, handles)
% hObject    handle to C_DIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_DIS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','动态免疫策略算法聚类结果');
set(gcf,'Pointer','arrow');


% --------------------------------------------------------------------
function C_EDIS_Callback(hObject, eventdata, handles)
% hObject    handle to C_EDIS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_EDIS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','加强动态免疫策略算法聚类结果');
set(gcf,'Pointer','arrow');


% % --------------------------------------------------------------------
% function C_EDIP_Callback(hObject, eventdata, handles)
% % hObject    handle to C_EDIP (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function C_CSAE_Callback(hObject, eventdata, handles)
% hObject    handle to C_CSAE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSAE( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','克隆选择算法E聚类结果');
set(gcf,'Pointer','arrow');

% --------------------------------------------------------------------
function C_CSS_Callback(hObject, eventdata, handles)
% hObject    handle to C_CSS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','克隆选择策略聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function C_CSSE_Callback(hObject, eventdata, handles)
% hObject    handle to C_CSSE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_CSSE( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','克隆选择策略E聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function Untitled_2_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Untitled_13_Callback(hObject, eventdata, handles)
% hObject    handle to Untitled_13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --------------------------------------------------------------------
function ABC_Callback(hObject, eventdata, handles)
% hObject    handle to ABC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_ABC( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','蜂群算法聚类结果');
set(gcf,'Pointer','arrow');





% --------------------------------------------------------------------
function Memetic_Callback(hObject, eventdata, handles)
% hObject    handle to Memetic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_MTC( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','Memetic算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function DE_Callback(hObject, eventdata, handles)
% hObject    handle to DE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_DE( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','差分进化算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function TS_Callback(hObject, eventdata, handles)
% hObject    handle to TS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function C_TS_Callback(hObject, eventdata, handles)
% hObject    handle to C_TS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_TS( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','禁忌搜索算法聚类结果');
set(gcf,'Pointer','arrow');



% --------------------------------------------------------------------
function QGA3_Callback(hObject, eventdata, handles)
% hObject    handle to QGA3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_QGA3( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','量子计算算法聚类结果');
set(gcf,'Pointer','arrow');




% --------------------------------------------------------------------
function WSO_Callback(hObject, eventdata, handles)
% hObject    handle to WSO (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(gcf,'Pointer','watch');
[m_pattern,patternNum]=GetFeature(handles);%得到特征
if(patternNum==0)
    msgbox('输入面板无样品，请重新输入样品');
    set(gcf,'Pointer','arrow');
    return;
end
m_pattern=C_WSO( m_pattern,patternNum );%K均值法聚类（matlab工具箱函数)
ShowResult(m_pattern,patternNum,handles);
set(handles.textResult,'String','狼群算法聚类结果');
set(gcf,'Pointer','arrow');
