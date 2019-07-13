#include<stdio.h>          /* By RAJ GAURAV BTECH CS */
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
int a,b,c,d,p,row3,col3,notimes,col,row,rnotimes,rrow,rcol;
main()
{
int gdriver = DETECT,gmode;
initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
outtextxy(220,200," Enter your option...");
outtextxy(220,230," 1 For Free hand.");
outtextxy(220,260," 2 For Rectangle.");
outtextxy(220,290," 3 For Line.");
settextstyle(2,0,7);
setcolor(2);
outtextxy(240,160,"Paint tools....");
settextstyle(0,0,0);
setcolor(15);
scanf("%d",&p);                         /*gets the value 1||2||3 from the user*/
if(p==1)
{freehand();}
if(p==2)
{drawrectangle();}
if(p==3)
{drawline();}
else
{
exit(0);
}
}

freehand()
{
int f=1;
setfillstyle(1,15);    		/*sets background color as white(15)*/
bar(0,0,650,490);
setfillstyle(1,12);
bar(530,430,590,450);  		/*sets button(bar) as color(12)*/
outtextxy(543,437,"Exit");       /*names the button as exit*/
do
{
 do
 {
  mouse_times_released(&rnotimes,&rrow,&rcol) ;   /*gets mouse info like row value col value at button release*/
  mouse_times_pressed(&notimes,&row,&col);        /*gets mouse info like row value col calue at button press*/
  if(notimes>0&&row>430&&row<450&&col>530&&col<590)/*exit if mouse is clicked within the specified value*/
  {
    mouse_times_pressed(&notimes,&row,&col);
    exit(0);
  }
 if(notimes>0)/*sets a=1 if mouse clicked*/
 {a=1;}
 if(rnotimes>0)/*sets b=1 if mouse button is released*/
 {b=1;}
  if((a==1)&&(b!=1))/*checks for button press and not button released*/
  {
   if(f==1)     /*assigns row and col value to col3 and row3 to erase previous col3 row3 value*/
   {col3=c=col;
   row3=d=row;
   f=0;}
   mouse_info(&row3,&col3);/*gets the immediate mouse info*/
   setcolor(9);
   hidemouse();
   setviewport(0,0,634,424,1);/*view port is set in order not to Overwrite	 button exit*/
   line(col3,row3,c,d); /*draws a line*/
   c=col3;              /*assigns col3 value to c row3 to d for next line process*/
   d=row3;
  }
   showmouse();        /*showes the pointer */
 }
 while(b!=1);        /*ends if button is released*/
 f=1;b=0;a=0;        /*a,b is assigned 0 so that button release pressed will be 0*/
}
while(1);           /*continues*/
}

drawline()
{
 setfillstyle(1,15);
 bar(0,0,650,490);
 setfillstyle(1,12);
 bar(530,430,590,450);
 outtextxy(543,437,"Exit");
do
{
 do
 {
 showmouse();
 mouse_times_released(&rnotimes,&rrow,&rcol) ;
 mouse_times_pressed(&notimes,&row,&col);
 if(notimes>0&&row>430&&row<450&&col>530&&col<590)
 {
  mouse_times_pressed(&notimes,&row,&col);
 exit(0);
 }
 if(notimes>0)
 {a=1;}
 if(rnotimes>0)
 {b=1;}
 if((a==1)&&(b!=1))                   /*all same as freehand*/
  {
   mouse_info(&row3,&col3);
   hidemouse();
   setviewport(0,0,634,425,1);
   setcolor(9);
   line (col,row,col3,row3);           /*col row clicked position col3 row3 immediate mouse info */
   delay(1000);
   setcolor(15);
   line (col,row,col3,row3);      /*the line drawn is cleared so that size of line can be adjusted*/
   p=0;
  }
}
while(b!=1);
 showmouse();
 if(p==0)
  {
   setcolor(9);
   line (col,row,col3,row3); /*draws the final line*/
  }
  b=0;a=0;
  p=1;
 }
 while(1);
}

drawrectangle()
{
 setfillstyle(1,15);
 bar(0,0,650,490);
 setfillstyle(1,12);
 bar(530,430,590,450);
 outtextxy(543,437,"Exit");
 do
  {
  do
   {
    showmouse();
    mouse_times_released(&rnotimes,&rrow,&rcol) ;
    mouse_times_pressed(&notimes,&row,&col);
    if(notimes>0&&row>430&&row<450&&col>530&&col<590)
    {
     mouse_times_pressed(&notimes,&row,&col);
     exit(0);
    }
    if(notimes>0)
    {a=1;}
    if(rnotimes>0)
    {b=1;}
    if((a==1)&&(b!=1))
     {                        /*same as free hand and drawline*/
     hidemouse();
     mouse_info(&row3,&col3);
     setviewport(0,0,634,425,1);
     setcolor(9);
     rectangle(col,row,col3-5,row3-5); /*col row mouse clicked position col3,row3 Immediate  mouse info*/
     delay(1000);                      /*col-left ,row-top,col3-right,row3-bottom*/
     setcolor(15);
     rectangle(col,row,col3-5,row3-5);
     p=0;
     }
   }
   while(b!=1);
   showmouse();
   if(p==0)
    {
    setcolor(9);
    rectangle(col,row,col3-5,row3-5);
    }
   b=0;
   a=0;
   p=1;
   showmouse();
 }
 while(1);
 }

 mouse_times_pressed(int *notimes,int *row,int *col)
 {
 union REGS in_regs,out_regs;
 in_regs.x.bx=0;  /* 0 for left click*/
 in_regs.x.ax=5;  /* 5 is passed to in_regs.x.ax to detrmine mouse press info*/
 int86(0x33,&in_regs,&out_regs);
 *notimes=out_regs.x.bx;   /*passes rowvlaue to *notimes colvalue *col and 1 to *row*/
 *row=out_regs.x.dx;
 *col=out_regs.x.cx;
 }

 mouse_times_released(int *rnotimes,int *rrow,int *rcol)
 {
 union REGS in_regs,out_regs;
 in_regs.x.bx=0;
 in_regs.x.ax=6;                /* 6 is passed to in_regs.x.ax to detrmine mouse release info*/
 int86(0x33,&in_regs,&out_regs);
 *rnotimes=out_regs.x.bx;
 *rrow=out_regs.x.dx;
 *rcol=out_regs.x.cx;
 }

 showmouse()
 {
 union REGS inregs,outregs;
 inregs.x.ax = 1;  /*1 to show mouse*/
 int86(0x33,&inregs,&outregs);
 }

 hidemouse()
 {
 union REGS inregs,outregs;
 inregs.x.ax=2;                     /*2 to hide mouse*/
 int86(0x33,&inregs,&outregs);
 }

 mouse_info(int *row3,int *col3)
 {
 union REGS in_regs,out_regs;
 in_regs.x.ax=3;                                 /*3 to get Immediate  mouse info(row,col)*/
 int86(0x33,&in_regs,&out_regs);
 *row3=out_regs.x.dx;
 *col3=out_regs.x.cx;
 }



