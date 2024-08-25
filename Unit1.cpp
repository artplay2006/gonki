// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include<fstream>
#include "Unit1.h"
#include<ctime>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int VStr = 5,stopstart1=5,stopstart2=0,stopstart3=0,stopstart4=0;
int VAuto1=5,VAuto2=5,VAuto3=5,Vme=16;
int Points=0,FactorPoints=1;
TImage *carsdop[4], *cars[4], *bonus[5];
int indxcar,indxmaincar=0,indxbonus,indxactivatebonus=-1;
int record;bool ch = True, ExiT = False;int s=0;
int currentSong=0;const int MaxSong=2;
void TxtReadWrite(){
	fstream f;
	f.open("record.txt",ios::in);
	f>>record;
	f.close();
	if(record<Points){
		ShowMessage("Ты побил рекорд");
		f.open("record.txt",ios::out);
		f<<Points;
		f.close();
	}
}
void GameOver(TTimer *timerauto, TTimer *timerstr,TTimer *timerforpoints,TTimer *timerautodinamic,TTimer *timerbonus,
TTimer *tenseconds,TSpeedButton *SpeedButton1){
	timerauto->Enabled=False;timerstr->Enabled=False;timerforpoints->Enabled=False;timerautodinamic->Enabled=False;
	timerbonus->Enabled=False;tenseconds->Enabled=False;
	SpeedButton1->Enabled=false;
	SpeedButton1->Visible=false;
	ShowMessage("Game Over Ты заработал "+IntToStr(Points)+" очков");
	TxtReadWrite();
}
bool Crash(TImage *player,TImage *car){
	if(player->Top<car->Top+185 && player->Top+185>car->Top &&
	((player->Left<car->Left+87 && player->Left>car->Left) ||
	(player->Left+87>car->Left && player->Left+87<car->Left+87)))
	{
		return true;
	}
	else{return false;}
}
void Start(TTimer *TimerAuto1,TTimer *TimerStr,TTimer *TimerForPoints,TTimer *TimerAutoDinamic,TImage *Image5player,
TSpeedButton *SpeedButton1, TButton *Button1, TImage *cars[], TImage *carsdop[]){
	TxtReadWrite();
	TimerAuto1->Enabled=True;
	TimerStr->Enabled=True;
	TimerForPoints->Enabled=True;
	TimerAutoDinamic->Enabled=True;
    Image5player->Left=521;
	Image5player->Top=560;
	Image5player->Enabled=True;
	Image5player->Visible=True;
	SpeedButton1->Enabled=True;
	SpeedButton1->Visible=True;
	Button1->Enabled=false;
	Button1->Visible=false;
	for(int i=0;i<4;i++){
		 cars[i]->Visible=False;
		 cars[i]->Top = 799;
	}
    for(int i=0;i<4;i++){
		 carsdop[i]->Top = -196;
		 carsdop[i]->Left=-200;
		 carsdop[i]->Visible=False;
	}
	for(int i=0;i<5;i++){
		bonus[i]->Visible=False;
		bonus[i]->Top=-96;
	}
	VAuto1=5,VAuto2=5,VAuto3=5,Vme=5, VStr = 5;
	Points=0;
}
void ActivateBonus(int numberbonus, int &v0, int &v1, int &v2, int &v3){
	if(numberbonus==0){
		v0+=3,v1+=3,v2+=3,v3+=3;
	}
	if(numberbonus==1){
		v0-=3,v1-=3,v2-=3,v3-=3;
	}
}
void DisActivate(int &indxactivatebonus, int &v0, int &v1, int &v2, int &v3){
	if(indxactivatebonus==0){
		v0-=3,v1-=3,v2-=3,v3-=3;
	}
	if(indxactivatebonus==1){
		v0+=3,v1+=3,v2+=3,v3+=3;
	}
	indxactivatebonus=-1;
}
// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
for(int i=0;i<4;i++){
carsdop[i]=new TImage(this);
carsdop[i]->Parent = this;
carsdop[i]->Top = -196;
carsdop[i]->Left=-200;
carsdop[i]->Width = 87;
carsdop[i]->Height = 185;
carsdop[i]->Picture->LoadFromFile("car"+IntToStr(6+i)+".png");
carsdop[i]->Proportional=True;
carsdop[i]->Visible=False;
}

for(int i=0;i<4;i++){
	cars[i]=new TImage(this);
	cars[i]->Parent=(this);
	cars[i]->Top = 799;
	cars[i]->Width = 87;
	cars[i]->Height = 185;
	cars[i]->Picture->LoadFromFile("car"+IntToStr(i+1)+".png");
	cars[i]->Proportional=True;
	cars[i]->Visible=False;
}

for(int i=0;i<5;i++){
bonus[i]=new TImage(this);
bonus[i]->Parent = this;
bonus[i]->Top = -96;
bonus[i]->Left=-200;
bonus[i]->Width = 87;
bonus[i]->Height = 87;
bonus[i]->Picture->LoadFromFile("bonus"+IntToStr(i)+".jpg");
bonus[i]->Proportional=True;
bonus[i]->Visible=False;
}
MediaPlayer1->FileName = "lil_jon_-_get_low.mp3";
MediaPlayer1->Open();
MediaPlayer1->Play();
}


// ---------------------------------------------------------------------------
bool f_l = False;
bool f_r = False;
// ---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
	if (Key == 37||Key == 65) {
		f_l = True;
	}
	if (Key == 39|| Key == 68) {
		f_r = True;
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::dvichAuto1(TObject *Sender) {
srand(time(0));
cars[0]->Top += stopstart1;
cars[1]->Top += stopstart2;
cars[2]->Top += stopstart3;
cars[3]->Top += stopstart4;
			if (cars[0]->Top >= 800) {
			stopstart1=0;
			cars[0]->Visible=false;
			cars[0]->Top = -96;
			cars[1]->Visible=true;
			cars[1]->Left=15+rand()%994;
			stopstart2=VAuto1;
			indxmaincar=1;
			}

			if(cars[1]->Top>=350&&cars[1]->Top<799&&TimerAutoDinamic->Enabled==False){
			indxcar=rand()%4;
			carsdop[indxcar]->Visible=True;
			carsdop[indxcar]->Left=15+rand()%994;
			TimerAutoDinamic->Enabled=True;
			}

			if(cars[1]->Top>=800){
			cars[2]->Left=15+rand()%994;
			stopstart2=0;
			cars[1]->Visible=false;
			cars[1]->Top = -96;
			cars[2]->Visible=true;
			stopstart3=VAuto3;
			indxmaincar=2;
			}
			if(cars[2]->Top>=600&&cars[2]->Top<799&&BonusDvisz->Enabled==False&&Points>30&&indxactivatebonus==-1){
			indxbonus=rand()%12;
				if(indxbonus>=0&&indxbonus<=4){
				bonus[indxbonus]->Visible=True;
				bonus[indxbonus]->Left=15+rand()%994;
				BonusDvisz->Enabled=True;}
				else{
				indxbonus=-1;
				}
			}
			if(cars[2]->Top>=800){
			cars[3]->Left=15+rand()%994;
			stopstart3=0;
			cars[2]->Visible=false;
			cars[2]->Top = -96;
			cars[3]->Visible=true;
			stopstart4=VAuto1;
			indxmaincar=3;
			}
			if(cars[2]->Top>=600&&cars[2]->Top<799&&BonusDvisz->Enabled==False&&Points>30&&indxactivatebonus==-1){
			indxbonus=rand()%12;
				if(indxbonus>=0&&indxbonus<=4){
				bonus[indxbonus]->Visible=True;
				bonus[indxbonus]->Left=15+rand()%994;
				BonusDvisz->Enabled=True;}
				else{
				indxbonus=-1;
				}
			}
			if(cars[3]->Top>=800){
			cars[0]->Left=15+rand()%994;
			stopstart4=0;
			cars[3]->Visible=false;
			cars[3]->Top = -96;
			cars[0]->Visible=true;
			stopstart1=VAuto1;
			indxmaincar=0;
			}
			if(cars[0]->Top>=350&&cars[0]->Top<799&&TimerAutoDinamic->Enabled==False){
			indxcar=rand()%4;
			carsdop[indxcar]->Visible=True;
			carsdop[indxcar]->Left=15+rand()%994;
			TimerAutoDinamic->Enabled=True;
			}
			if(indxactivatebonus!=4){
			if (f_l == true && Image5player->Left > 20) {
			Image5player->Left -= Vme;
			}
			if (f_r == true && Image5player->Left <= 1000) {
			Image5player->Left += Vme ;
			}}
			else{
			if (f_l == true && Image5player->Left <= 1000) {
			Image5player->Left += Vme;
			}
			if (f_r == true && Image5player->Left > 20) {
			Image5player->Left -= Vme ;
			}}
}

void __fastcall TForm1::dvichStr(TObject *Sender)
{
if((Crash(Image5player, cars[indxmaincar])||Crash(Image5player, carsdop[indxcar]))){
	GameOver(TimerAuto1,TimerStr,TimerForPoints,TimerAutoDinamic,BonusDvisz,TenSeconds,SpeedButton1);
	Button1->Enabled=true;
	Button1->Visible=true;
	Button2->Enabled=true;
	Button2->Visible=true;
    MediaPlayer1->Visible=True;
	indxactivatebonus=-1;s=0;
	f_l=False;f_r=False;
}
Shape2->Top += VStr;  if (Shape2->Top >= 900) {Shape2->Top = -10;}
Shape3->Top += VStr;  if (Shape3->Top >= 900) {Shape3->Top = -10;}
Shape4->Top += VStr;  if (Shape4->Top >= 900) {Shape4->Top = -10;}
Shape5->Top += VStr;  if (Shape5->Top >= 900) {Shape5->Top = -10;}
Shape6->Top += VStr;  if (Shape6->Top >= 900) {Shape6->Top = -10;}
Shape7->Top += VStr;  if (Shape7->Top >= 900) {Shape7->Top = -10;}
Shape8->Top += VStr;  if (Shape8->Top >= 900) {Shape8->Top = -10;}
Shape9->Top += VStr;  if (Shape9->Top >= 900) {Shape9->Top = -10;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerForPointsTimer(TObject *Sender)
{
Points+=FactorPoints;
Label1->Caption=IntToStr(Points)+"  RECORD:"+IntToStr(record);
if(VStr<12){
if(VStr==11){
Vme+=1;
}
if(Points%10==9||Points%10==5){
VAuto1+=1;VAuto2+=1;VAuto3+=1;VStr+=1;
}}
else{
if(Points%100==2||Points%100==4||Points%100==8){
VAuto1+=1;VAuto2+=1;VAuto3+=1;VStr+=1;
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
//static bool ch=True;
if(ch==True){
	TimerAuto1->Enabled=False;
	TimerStr->Enabled=False;
	TimerForPoints->Enabled=False;
	TimerAutoDinamic->Enabled=False;
	BonusDvisz->Enabled=False;
	TenSeconds->Enabled=False;
	SpeedButton1->Caption="CONTINUE";
	Button2->Enabled=True;Button2->Visible=True;
	MediaPlayer1->Visible=True;
	ch=False;
}
else{
	TimerAuto1->Enabled=True;
	TimerStr->Enabled=True;
	TimerForPoints->Enabled=True;
	TimerAutoDinamic->Enabled=True;
	if(indxactivatebonus!=-1){TenSeconds->Enabled=True;}
    if(indxbonus!=-1){BonusDvisz->Enabled=True;}
	SpeedButton1->Caption="PAUSE";
	Button2->Enabled=False;Button2->Visible=False;
	MediaPlayer1->Visible=False;
	ch=True;ExiT=False;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerAutoDinamicTimer(TObject *Sender)
{
carsdop[indxcar]->Top+=VAuto3;
if (carsdop[indxcar]->Top >= 800) {
	carsdop[indxcar]->Visible=False;
	carsdop[indxcar]->Top=-96;
	TimerAutoDinamic->Enabled=False;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Start(TimerAuto1,TimerStr,TimerForPoints,TimerAutoDinamic,Image5player,SpeedButton1, Button1,cars,carsdop);
Button2->Enabled=False;Button2->Visible=False;
FactorPoints=1;
Shape3->Top=112;Shape2->Top=313;Shape5->Top=504;Shape2->Top=313;Shape9->Top=696;
Shape4->Top=504;Shape6->Top=313;Shape2->Top=313;Shape8->Top=112;
Shape7->Top=696;
MediaPlayer1->Visible=False;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BonusDviszTimer(TObject *Sender)
{
bonus[indxbonus]->Top+=VStr;
if(bonus[indxbonus]->Top>=800){
	bonus[indxbonus]->Visible=false;
	bonus[indxbonus]->Left=15+rand()%994;
	bonus[indxbonus]->Top=-96;
	BonusDvisz->Enabled=false;
}
if(Crash(Image5player, bonus[indxbonus])){
	indxactivatebonus=indxbonus;
	bonus[indxbonus]->Visible=false;
	bonus[indxbonus]->Top=-96;
	switch(indxactivatebonus){
		case 0:
		ActivateBonus(indxactivatebonus, VStr,VAuto1,VAuto2,VAuto3);TenSeconds->Enabled=true;FactorPoints=2;
		break;
		case 1:
		ActivateBonus(indxactivatebonus, VStr,VAuto1,VAuto2,VAuto3);TenSeconds->Enabled=true;
		break;
		case 2:
		Points+=5;indxactivatebonus=-1;;
		break;
		case 3:
		Points-=30;indxactivatebonus=-1;;
		break;
		case 4:
		TenSeconds->Enabled=True;
		break;
	}
	BonusDvisz->Enabled=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TenSecondsTimer(TObject *Sender)
{
//static int s=0;
s++;
if(s==9){
	if(indxactivatebonus==0||indxactivatebonus==1){DisActivate(indxactivatebonus, VStr,VAuto1,VAuto2,VAuto3);FactorPoints=1;}
	if(indxactivatebonus==4){indxactivatebonus=-1;}
	s=0;
	TenSeconds->Enabled=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == 37||Key == 65) {
		f_l = False;
	}
	if (Key == 39||Key == 68) {
		f_r = False;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
if(SpeedButton1->Caption=="CONTINUE" && ExiT==false){
	ShowMessage("Если вы выйдете из игры во время паузы, то ваш нынешний прогресс не сохранится.\nВы уверены что хотите покинуть игру?");
	ExiT=true;
}
else{
	Close();
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MediaPlayer1Notify(TObject *Sender)
{
	if (MediaPlayer1->NotifyValue == nvSuccessful)
	{currentSong++;
		switch (currentSong)
    {
		case 0:
			MediaPlayer1->FileName = "lil_jon_-_get_low.mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
        case 1:
			MediaPlayer1->FileName = "Teriyaki_Boyz_-_Tokyo_Drift_Fast_Furious_(musmore.com).mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
            break;
		case 2:
			MediaPlayer1->FileName = "Ludacris - Act A Fool (OST Форсаж 2).mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
		case 3:
			MediaPlayer1->FileName = "Static-X-The Only-kissvk.com.mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
		case 4:
			MediaPlayer1->FileName = "dj-smash_-_moscow-never-sleeps.mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
		case 5:
			MediaPlayer1->FileName = "Static-X-Hollow -Project Regeneration--kissvk.com.mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
		case 6:
			MediaPlayer1->FileName = "Pain - Shut Your Mouth.mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			break;
		case 7:
			MediaPlayer1->FileName = "Static-X_-_Control_It_(musmore.com).mp3";
			MediaPlayer1->Open();
			MediaPlayer1->Play();
			currentSong=-1;
			break;
	}
	}
}
//---------------------------------------------------------------------------

