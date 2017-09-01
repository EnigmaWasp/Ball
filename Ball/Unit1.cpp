//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool KeyLeft,KeyRight;
TList*Plitki;
int PlitkaSpeed;
int MaxBallSpeed;
int MaxLife;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 MaxLife=3;
 LifeCol=MaxLife;
 Scores=0;
 TimeToNextScore=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MainLoopTimerTimer(TObject *Sender)
{
if(KeyLeft)  SpeedBallX--;
        else
if(KeyRight) SpeedBallX++;
        else
        {
        if(SpeedBallX>0)SpeedBallX--;
        if(SpeedBallX<0)SpeedBallX++;
        }
if(SpeedBallX>MaxBallSpeed)SpeedBallX=MaxBallSpeed;else
if(SpeedBallX<-MaxBallSpeed)SpeedBallX=-MaxBallSpeed;
BallX+=SpeedBallX;
if(BallX>Width-30)BallX=Width-30;
if(BallX<0)BallX=0;
if(!BallZahvat)
        {
        BallY+=SpeedBallY;
        SpeedBallY+=0.5;
        if(SpeedBallY>5)SpeedBallY=5;
        }
TimeToNextScore++;
if(TimeToNextScore>40)
{
Scores+=1;
TimeToNextScore=0;
}
if((BallY>320) || (BallY<-40))
{
GameOver();
}
Scene->Canvas->Brush->Color=RGB(0,128,200);
Scene->Canvas->Rectangle(0,0,Width,Height);
UpdatePlitki();
TestBall();
DrawPlitki();
Scene->Canvas->Draw(BallX,BallY,BallImage);
PrintText();
ShowScene();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ShowScene()
{                               //Рисуем из 'заднего' буффера на экран
Form1->Canvas->Draw(0,0,Scene);
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
randomize();
Scene=new Graphics::TBitmap();//Создаем 'задний' экран
Height=Form1->ClientHeight;
Width= Form1->ClientWidth;
Scene->Width = Width;
Scene->Height= Height;
BallImage=new Graphics::TBitmap();
BallImage->LoadFromFile("Шарик.bmp");
BallImage->Transparent=true;
BallX=100;BallY=00;
SpeedBallX=0;
SpeedBallY=0;
KeyLeft=false;
KeyRight=false;
Plitki=new TList();
Plitki->Capacity=20;
BallZahvat=false;
PlitkaSpeed=-3;
MaxBallSpeed=8;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_LEFT)KeyLeft=false;
if(Key==VK_RIGHT)KeyRight=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
if(Key==VK_LEFT)KeyLeft=true;
if(Key==VK_RIGHT)KeyRight=true;
}
//---------------------------------------------------------------------------


void TForm1::UpdatePlitki()
{
Plitka*p;
int count=Plitki->Count;
for(int i=0;i<count;i++)
{
try{
p=(Plitka*)Plitki->Items[i];
}catch(...){
            //Пустой обработчик ошибок
           }
p->y+=PlitkaSpeed;
if(p->y<-10)
        {
        Plitki->Delete(i);
        p=NULL;
        }
}
if(count>0)
{
p=(Plitka*)Plitki->Last();

        if(p->y<250)
        {
        if(random(9)==1)
                {
                bool tip;
                if(random(10)==5)tip=true;else tip=false;
                int w=random(20)+40;
                p=new Plitka(random(Width-w),320,w,tip);
                Plitki->Add(p);
                }
        }
}
if(count==0)
{
int w=random(20)+40;
Plitki->Add(new Plitka(random(Width-w),320,w,false));
}
if(BallZahvat)BallY+=PlitkaSpeed;
}


void __fastcall TForm1::DrawPlitki()
{
Plitka*p;
int x,y,w;
int count=Plitki->Count;
for(int i=0;i<count;i++)
{
p=(Plitka*)Plitki->Items[i];
x=p->x;y=p->y;w=p->Width;
if(p->type)Scene->Canvas->Brush->Color=clRed;else
           Scene->Canvas->Brush->Color=clYellow;
Scene->Canvas->Rectangle(x,y,x+w,y+10);
}
}



TForm1::TestBall()
{
RECT Rect1=Rect(BallX,BallY,BallX+30,BallY+30);
RECT Rect3=Rect(0,0,0,0);
RECT Rect2;
Plitka*p;
int count=Plitki->Count;
for(int i=0;i<count;i++)
{
p=(Plitka*)Plitki->Items[i];
Rect2=Rect(p->x,p->y,p->x+p->Width,p->y+10);
if(IntersectRect(&Rect3,&Rect1,&Rect2))
        {
        if(p->type)
        {
        Plitki->Clear();
        GameOver();
        }
        if(BallX<p->x-25)BallX=p->x-30;else
        if(BallX>p->x+p->Width)BallX=p->x+p->Width;else
        {
        BallZahvat=true;
        SpeedBallY=0;
        BallY=p->y-30;
        return 1;
        }
        }
}
BallZahvat=false;
return 0;
}

void __fastcall TForm1::PrintText()
{
      Scene->Canvas->Brush->Color=clGreen;
      Scene->Canvas->TextOutA(10,10,"Жизней:"+IntToStr(LifeCol));
      Scene->Canvas->TextOutA(10,30,"Очков:"+IntToStr(Scores));
}

void __fastcall TForm1::GameOver()
{
        MainLoopTimer->Enabled=false;
        Form1->Canvas->Brush->Color=clWhite;
        Form1->Canvas->Pen->Width=5;
        Form1->Canvas->RoundRect(50,50,250,250,20,20);
        Form1->Canvas->Pen->Width=1;
        if(LifeCol>0)
        {
        LifeCol--;
        Form1->Canvas->Font->Size=15;
        Form1->Canvas->TextOutA(70,100,"Осталось попыток");
        Form1->Canvas->TextOutA(150,140,IntToStr(LifeCol));
        Form1->Canvas->Font->Size=8;
        Sleep(3000);
        BallY=20;
        SpeedBallY=0;
        MainLoopTimer->Enabled=true;
        }else
        {
        Form1->Canvas->Font->Size=15;
        Form1->Canvas->TextOutA(80,100,"Игра проиграна");
        Form1->Canvas->TextOutA(150,150,IntToStr(Scores));
        Form1->Canvas->Font->Size=8;
        Sleep(3000);
        NewGame();
        }

}

void __fastcall TForm1::NewGame()
{
         Plitki->Clear();
        MainLoopTimer->Enabled=false;
        Form1->Invalidate();
        Label1->Visible=true;
        RadioGroup1->Visible=true;
        SpeedButton1->Visible=true;
        SpeedButton2->Visible=true;
        Scores=0;
        LifeCol=MaxLife;
        SpeedBallY=0;
        BallX=100;
        BallY=20;
}
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{

        Label1->Visible=false;
        RadioGroup1->Visible=false;
        SpeedButton1->Visible=false;
        SpeedButton2->Visible=false;
        switch(RadioGroup1->ItemIndex)
        {
        case 0: PlitkaSpeed=-1;
                MaxBallSpeed=3;
                break;
        case 1:
                PlitkaSpeed=-3;
                MaxBallSpeed=8;
                break;

        case 2:
                PlitkaSpeed=-5;
                MaxBallSpeed=8;
                break;
        }

        MainLoopTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 ShellExecute(Handle,"open","Справка.txt",NULL,"",SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

