#define VIDEO_ADDRESS 0xa0000

typedef signed char int8_t;
typedef signed short int16_t;

//struct point 
typedef struct
{
  int16_t x;
  int16_t y;
} point;

point point_constructor(int16_t x, int16_t y)
{
	point result;
	result.x = x;
	result.y = y;
	
	return result;
}
//

//struct square_draw_instruction
typedef struct
{
  point top_left;
  point buttom_right;
  int8_t color;
} square_draw_instruction;

square_draw_instruction square_draw_instruction_constructor(point top_left, point buttom_right, int8_t color)
{
  	square_draw_instruction result;
	
	result.top_left = top_left;
	result.buttom_right = buttom_right;
	result.color = color;
	
	return result;
}
//

void put_pixel(int16_t x, int16_t y, int8_t color)
{
	*((int8_t*)VIDEO_ADDRESS + x + 320*y) = color;
};

void draw_square(square_draw_instruction sqr_instruction)
{   
  int16_t min_x = 0;
  int16_t max_x = 0;
  
  int16_t min_y = 0;
  int16_t max_y = 0;
  
  if (sqr_instruction.top_left.x > sqr_instruction.buttom_right.x)
  {
	min_x = sqr_instruction.buttom_right.x;
	max_x = sqr_instruction.top_left.x;
  }
  else
  {
	min_x = sqr_instruction.top_left.x;
	max_x = sqr_instruction.buttom_right.x;  
  }
  
  if (sqr_instruction.top_left.y > sqr_instruction.buttom_right.y)
  {
	min_y = sqr_instruction.buttom_right.x;
	max_y = sqr_instruction.top_left.x;
  }
  else
  {
	min_y = sqr_instruction.top_left.y;
	max_y = sqr_instruction.buttom_right.y;  
  }
  
  for (int x = min_x; x < max_x; x ++)
  {
     for (int y = min_y; y < max_y; y++)
	 {
	   put_pixel(x, y, sqr_instruction.color);	 
	 }
  }
};

void draw_on_screen_by_matrix(int16_t screen[][10],int8_t columns, int8_t lines, int8_t proportion)
{
  for(int x = 0; x < columns; x++)
  {
	for (int y = 0; y < lines; y++)
	{
	  point top_left = point_constructor(x * proportion, y * proportion);
	  
	  point button_right = point_constructor((x * proportion) + proportion, (y * proportion) + proportion);
	  
	  square_draw_instruction sqt_instruction = square_draw_instruction_constructor(
		top_left,
		button_right,
		screen[x][y]);
	  
	  draw_square(sqt_instruction);
	};
  };
};
 
int kmain(void)
{   
  int16_t screen[16][10] = {0};
  
  //H
  screen[0][0] = 0x01;
  screen[0][1] = 0x01;
  screen[0][2] = 0x01;
  
  screen[1][1] = 0x01;
  
  screen[2][0] = 0x01;
  screen[2][1] = 0x01;
  screen[2][2] = 0x01;
    
  draw_on_screen_by_matrix(screen, 16, 10, 15);
  return 0;
};
