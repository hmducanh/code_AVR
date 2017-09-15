#include <mega8.h>
#include <string.h>
#include <glcd.h>
#include <delay.h>
#include <font5x7.h>

void chim_bay(int res, int cnt, int kt, int check)
{   
    glcd_moveto(30, 15);
    glcd_putchar('*');
    while(1)
    {           
        if(PIND.1 == 0)
        {          
            if(!res)
                res = 1, kt = 0, check = 0;
            ++cnt;
        }
        else
        {  
            res = 0;
            cnt = 0; 
        }           
        if(cnt > 0 && cnt <= 100)
        {            
            if(!kt)
                glcd_clear(), kt = 1;
            glcd_moveto(30, 5);   
            glcd_putchar('*');
        }
        else       
        {              
            if(!check)
            glcd_clear(), check = 1;
            glcd_moveto(30, 15);
            glcd_putchar('*');
        } 
    }
}

void main()
{
    GLCDINIT_t glcd_init_data;
    int res = 0, cnt = 0, kt = 0, check = 0;
    glcd_init_data.font=font5x7;
    glcd_init_data.readxmem=NULL;
    glcd_init_data.writexmem=NULL;
    glcd_init_data.temp_coef=188;
    glcd_init_data.bias=3;
    glcd_init_data.vlcd=58;
    glcd_init(&glcd_init_data); 
    DDRD.1 = 0;      
    PORTD.1 = 1; 
    DDRC.5 = 1;      
    PORTC.5 = 0;
    chim_bay(res, cnt, kt, check);
}
