#include <stdio.h>
#include <math.h>
#include "gamepad_cmd.h"

const int axis_x_unit = pow(2,AXIS_X_BITS) -1;			//x value bit suu
const int axis_y_unit = pow(2,AXIS_Y_BITS) -1;			//y value bit suu
const int axis_t_unit = pow(2,AXIS_T_BITS) -1;			//turn value bit suu
const int axis_x_reso = (AXIS_VAL_MAX * 2) / (axis_x_unit+1);	//x value per bit
const int axis_y_reso = (AXIS_VAL_MAX * 2) / (axis_y_unit+1);	//y value per bit
const int axis_t_reso = (AXIS_VAL_MAX * 2) / (axis_t_unit+1);	//turn value per bit
//Gpads_cmd raw_cmd;				//Commands which got from Game Pad

void chatterCallback(void){
    //It's interrupt function
    //Get gamepad's command
}

//Function who makes shooting command
unsigned char makeFirCmd(ros_robo15::Gamepad_cmd p_cmd){

    unsigned char r_cmd = 0;
    unsigned char buf	= 0;

    //Add bias value
    p_cmd.right_axis_x	+= AXIS_VAL_BIAS;

    //Make shooting command
    if	    (p_cmd.button_x) r_cmd = SHOOT_ONES;
    else if (p_cmd.button_a) r_cmd = SHOOT_TWER;
    else if (p_cmd.button_b) r_cmd = SHOOT_ENMY;

    r_cmd = r_cmd << 4;

    //Make turning command
    buf			=  p_cmd.right_axis_x / axis_t_reso;
    if(buf > axis_t_unit) buf = axis_t_unit;		    //Prevent over flow

    //Join shooting and turning commands
    r_cmd		+= buf;

    return r_cmd;
}

//Function who makes moving command
unsigned char makeMovCmd(ros_robo15::Gamepad_cmd p_cmd){

    unsigned char r_cmd = 0;
    unsigned char buf	= 0;

    //////////////////////////////////////////
    //MEMO
    //moves(axis)
    //foward: -y
    //back  : +y
    //right : +x
    //left  : -x

    //moves(hat)
    //foward: +y
    //back  : -y
    //right : -x
    //left  : +x
    //////////////////////////////////////////

    //Reverse(hat)
    p_cmd.hat_x		*= -1;
    p_cmd.hat_y		*= -1;

    //Add bias values
    p_cmd.left_axis_x	+= AXIS_VAL_BIAS;
    p_cmd.left_axis_y	+= AXIS_VAL_BIAS;

    //Make y value
    r_cmd		=  p_cmd.left_axis_y / axis_y_reso;
    if(r_cmd > axis_y_unit) r_cmd = axis_y_unit;	    //Prevent over flow

    r_cmd		= r_cmd << 4;

    //Make x value
    buf			= p_cmd.left_axis_x / axis_x_reso;
    if(buf > axis_x_unit) buf = axis_x_unit;		    //Prevent over flow

    //Join x and y moving commands
    r_cmd		+= buf;
    r_cmd		|= 0x80;			    //Add distinction mark

    return r_cmd;
}

/*int main(void){

    unsigned char   fir_cmd = 0;	//Shoot rings command
    unsigned char   mov_cmd = 0;	//Command which moves robot.

    fir_cmd	= makeFirCmd(raw_cmd);	//Make shooting rings command
    mov_cmd	= makeMovCmd(raw_cmd);	//Make Moving robot command

    printf("%x %x\n",fir_cmd,mov_cmd);

    return 0;
}*/

