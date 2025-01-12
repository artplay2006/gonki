// ---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.MPlayer.hpp>
#include <Vcl.Imaging.pngimage.hpp>

// ---------------------------------------------------------------------------
class TForm1 : public TForm {
__published: // IDE-managed Components
	TTimer *TimerAuto1;
	TShape *Shape5;
	TShape *Shape9;
	TTimer *TimerStr;
	TTimer *TimerForPoints;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	TShape *Shape6;
	TShape *Shape7;
	TShape *Shape8;
	TImage *Image5player;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TTimer *TimerAutoDinamic;
	TButton *Button1;
	TTimer *BonusDvisz;
	TTimer *TenSeconds;
	TButton *Button2;
	TMediaPlayer *MediaPlayer1;
	void __fastcall dvichAuto1(TObject *Sender);

	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall dvichStr(TObject *Sender);
	void __fastcall TimerForPointsTimer(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall TimerAutoDinamicTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BonusDviszTimer(TObject *Sender);
	void __fastcall TenSecondsTimer(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall MediaPlayer1Notify(TObject *Sender);








private: // User declarations
public: // User declarations
	__fastcall TForm1(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
