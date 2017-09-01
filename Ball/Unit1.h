//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Plitka
{
public:
int x;
int y;
int Width;
bool type;
Plitka(int nx,int ny,int nw,int nt)
        {
        x=nx;
        y=ny;
        Width=nw;
        type=nt;
        }
};



class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *MainLoopTimer;
        TTimer *EndGameTimer;
        TRadioGroup *RadioGroup1;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TLabel *Label1;
        TSpeedButton *SpeedButton3;
        void __fastcall MainLoopTimerTimer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:
	// User declarations
       Graphics::TBitmap*Scene;
       Graphics::TBitmap*BallImage;
       int Width,Height;
       int BallX,BallY;
       float SpeedBallX,SpeedBallY;
       bool BallZahvat;
        __fastcall TForm1(TComponent* Owner);
        void __fastcall ShowScene();
        void UpdatePlitki();
        void __fastcall DrawPlitki();
       int LifeCol,Scores,TimeToNextScore;
        TestBall();
        void __fastcall PrintText();
        void __fastcall GameOver();
        void __fastcall NewGame();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 