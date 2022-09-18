#include <system.h>
#define DIN 0
#define LOAD 1
#define CLK 2
#define PUERTO portb
#define Decode 0x9
#define Intensity 0xA
#define ScanLimit 0xB
#define Shutdown 0xC
#define Test 0xF
rom char *llama = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0,0x0, 0x0, 0x0, 0x20, 0x7F, 0xC, 0xF,0x8};
rom char *llama1 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0, 0x0, 0x50, 0x20, 0x10, 0xF, 0xC, 0xF,0x8};
rom char *llama2 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0, 0x0, 0x8, 0xC, 0x8, 0xF, 0xC, 0xF,0x8};
rom char *llama3 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0, 0x0, 0x2, 0x7, 0x8, 0xF, 0xC, 0xF,0x8};
rom char *llama4 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0,0x0, 0x0, 0x0, 0x20, 0x7F, 0xC, 0xF,0xC};
rom char *llama5 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0,0x0, 0x0, 0x0, 0x20, 0x7F, 0xC, 0xF,0xA};
rom char *llama6 = {0x0, 0x0,0x0, 0x0,0x0, 0x0, 0x0,0x0,0x0, 0x0, 0x0, 0x20, 0x7F, 0xC, 0xF,0x9};	

void serializar(char numero)
{	
	for (signed char i=7; i>=0; i--)
	{
		test_bit(numero, i)? set_bit(PUERTO, DIN): clear_bit(PUERTO, DIN);
		set_bit(PUERTO, CLK);
		clear_bit(PUERTO, CLK);
	}
}
void escribir(char address, char data){
	clear_bit(PUERTO,LOAD);
	serializar(address);
	serializar(data);
	set_bit(PUERTO,LOAD);
	}
void dibujar(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama[i+offset]>>level);
		}
}
void dibujar1(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama1[i+offset]>>level);
		}
}
void dibujar2(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama2[i+offset]>>level);
		}
}
void dibujar3(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama3[i+offset]<<level);
		}
}	
void dibujar4(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama4[i+offset]<<level);
		}
}
void dibujar5(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama5[i+offset]<<level);
		}
}
void dibujar6(char offset,char level)
{
	for (char i = 0; i < 8; i++)
		{	
		escribir(i+1, llama6[i+offset]<<level);
		}
}	
void main()
{
trisb=0;
portb=0;
escribir(Decode,0x0);// no decodificamos
escribir(Intensity,0xF); //Intensidad de los led
escribir(ScanLimit,0x7);//utilizar todas las filas
escribir(Shutdown,1);//encender la pantalla
while(1){
	for(char x=0;x<=16;x++){
		if(x==9){
			dibujar1(x,0);
			delay_ms(50);
			dibujar2(x,0);
			delay_ms(50);
			dibujar3(x,0);
			delay_ms(1000);
			dibujar2(x,0);
			delay_ms(50);
			dibujar1(x,0);
			delay_ms(50);
			}
		dibujar(x,0);
		if(x==0){
			escribir(Shutdown,1);//encender la pantalla
			}
		if(x==9){
			delay_ms(1000);	
			dibujar4(x,0);
			delay_ms(50);
			dibujar5(x,0);
			delay_ms(50);
			dibujar6(x,0);
			delay_ms(1000);	
			}
		if(x>9){
			escribir(7,0x1);
			}
		if(x<9){
			escribir(2,0x1);
			}
		delay_ms(50);
		if(x==16){
			escribir(Shutdown,0);//encender la pantalla
			delay_ms(950);
			}
		}
	}
}
