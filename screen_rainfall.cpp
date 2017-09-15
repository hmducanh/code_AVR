#include <mega8.h>
#include <string.h>
#include <glcd.h>
#include <delay.h>
#include <font5x7.h>
#include <stdio.h>

void in_so(int x)
{
    char c[9]; 
    int cnt = 0, i = 0; 
    while(1)
    {       
        int res = x % 10;  
        if(x < 10)
        {
            c[cnt] = x + 48;
            break;
        }
        c[cnt] = res + 48;
        ++cnt;
        x = (x - res) / 10;
    }              
    for(i = cnt; i >= 0; i--)
        glcd_putchar(c[i]);
}

void level_of_water(int x)
{
    int i; 
    for(i = 0; i < x; i++)
    {
        glcd_line(61, 44 - 3 * i, 69, 44 - 3 * i);
    }
}
              
void draw(int x)
{
    glcd_line(0, 0, 0, 48);
    glcd_line(0, 0, 82, 0);
    glcd_line(82, 0, 82, 48);
    glcd_line(0, 48, 82, 48);
    glcd_moveto(2, 3);
    glcd_outtext("Rainfall"); 
    glcd_line(48, 0, 48, 11); 
    glcd_line(0, 11, 48, 11);   
    glcd_moveto(2, 16);
    glcd_outtext("Count ");
    in_so(x);      
    glcd_moveto(2, 31);
    glcd_outtext("Indensity");  
    glcd_line(58, 13, 58, 45);
    glcd_line(72, 13, 72, 45);
    glcd_line(58, 45, 72, 45); 
    // 58 15 == 72 15    
    glcd_line(54, 7, 58, 13);
    glcd_line(76, 7, 72, 13);
    level_of_water(x);
}        

void main(void)
{
    int res = 0, cnt = 0;
    GLCDINIT_t glcd_init_data;
    DDRC.5 = 1;
    PORTC.5 = 0;
    glcd_init_data.font=font5x7;
    glcd_init_data.readxmem=NULL;
    glcd_init_data.writexmem=NULL;
    glcd_init_data.temp_coef=188;
    glcd_init_data.bias=3;
    glcd_init_data.vlcd=58;
    glcd_init(&glcd_init_data);
    DDRD.1 = 0;
    PORTD.1 = 1;
    draw(0);
    while(1)
    {          
         draw(cnt);
         if(PIND.1 == 0)
         {
            if(res == 0) 
            {
                res = 1;
                ++cnt;
                glcd_clear();
                cnt = ((cnt > 10) ? 1 : cnt);
            }
         }                                  
         else
            res = 0;   
    }   
}
