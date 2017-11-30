#pragma config(Sensor, in1,    rotate_angle_sensor_1, sensorAnalog)
#pragma config(Sensor, in2,    updown_angle_sensor_2, sensorPotentiometer)
#pragma config(Sensor, in3,    salver_potentiometer, sensorPotentiometer)
#pragma config(Sensor, in7,    GYRO,           sensorGyro)
#pragma config(Sensor, dgtl1,  run_right_encoder_sensor_1, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  run_left_encoder_sensor_3, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  updown_bump_sensor_5, sensorTouch)
#pragma config(Sensor, dgtl6,  cp6,            sensorDigitalIn)
#pragma config(Sensor, dgtl7,  cp7,            sensorDigitalIn)
#pragma config(Sensor, dgtl8,  cp8,            sensorDigitalIn)
#pragma config(Sensor, dgtl9,  cp9,            sensorDigitalIn)
#pragma config(Motor,  port1,           run_left_motor_1, tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           run_left_motor_2, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           updown_motor_3, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           updown_motor_4, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           intake_motor_5, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           salver_motor_6, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           salver_motor_7, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           rotate_right_8, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           run_right_motor_9, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          run_right_motor_10, tmotorVex393HighSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//V1.0	I increased the static speed of the clip from 19 to 25
//			by liu wenbin 20171125 night
#define ANGLE_KP 26
#define ANGLE_KD 100


int run_left_encoder_value;
int run_right_encoder_value;
int updown_bump_value;
int updown_angle_value;
int rotate_angle_value;
int bump_flag=0;

int cp6_value;
int cp7_value;
int cp8_value;
int cp9_value;

///////////////////////////////////////////////////////////////////////////////////////////
void run(int left_speed,int right_speed)
{
	motor[run_left_motor_1] = left_speed;
	motor[run_left_motor_2] = left_speed;
	motor[run_right_motor_9] = right_speed;
	motor[run_right_motor_10] = right_speed;
}

void updown(int updpwn_speed)
{
	motor[updown_motor_3] = updpwn_speed;
	motor[updown_motor_4] = updpwn_speed;
}

void intake(int intake_speed)     //Zheng  Xi
{
	motor[intake_motor_5] = intake_speed;
}

void salver(int salver_speed)
{
	motor[salver_motor_6] = salver_speed;
	motor[salver_motor_7] = salver_speed;
}

void rotate(int rotate_speed)
{
	motor[rotate_right_8] = rotate_speed;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void manual_run()//Di_Pan
{
  int leftspd=0;
  int rightspd=0;
  leftspd = vexRT[Ch3]+vexRT[Ch4];
  rightspd = vexRT[Ch3]-vexRT[Ch4];

  if(leftspd>127) leftspd=127;
  else if(leftspd<-127) leftspd=-127;
  if(rightspd>=127) rightspd=127;
  else if(rightspd<=-127) rightspd=-127;

  if((abs(vexRT[Ch3])>20)||(abs(vexRT[Ch4])>20))	run(leftspd,rightspd);
  else	run(0,0);
}

void manual_updown()//Tai_Sheng
{

	if(vexRT[Ch2]>20)  updown(vexRT[Ch2]);
	else if(vexRT[Ch2]<-20)  updown(0.9*vexRT[Ch2]);
	else updown(0);
}

void manual_rotate()//Xuan_Zhuan
{
	if((vexRT[Btn5U]==1))	rotate(120);
	else if(vexRT[Btn5D]==1)	rotate(-120);
	else rotate(13);
}

void manual_salver()//Tuo_Pan
{
	if(vexRT[Btn7L]==1) salver(-127);
	else if(vexRT[Btn7U]==1) salver(127);
	else if((vexRT[Btn7L]==0) && (vexRT[Btn7U]==0)) salver(0);
}

void manual_intake()//Jia_Qu
{
	if(vexRT[Btn6U]==1)	intake(-127);
	else if(vexRT[Btn6D]==1) intake(127);
	else intake(25);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////  dp //////////////////////////
void Run_Control(int left_add,int right_add,int mood)   //mood=0 zhi     mood=1 guai
{
	int left_encoder_target_value;
	int right_encoder_target_value;
	int left_encoder_error;
	int right_encoder_error;
	int left_speed=0;
	int right_speed=0;

	run_right_encoder_value = SensorValue[run_right_encoder_sensor_1];
	run_left_encoder_value = SensorValue[run_left_encoder_sensor_3];
  left_encoder_target_value = run_left_encoder_value+left_add;
  right_encoder_target_value = run_right_encoder_value+right_add;

	while(1)
	{
		run_right_encoder_value = SensorValue[run_right_encoder_sensor_1];
    run_left_encoder_value = SensorValue[run_left_encoder_sensor_3];

		left_encoder_error = left_encoder_target_value - run_left_encoder_value;
		right_encoder_error = right_encoder_target_value - run_right_encoder_value;

		if(mood==0 && left_encoder_error<50 && left_encoder_error>0 && right_encoder_error<50 && right_encoder_error>0 ) {  run(-50,-50);wait1Msec(100);run(0,0);  break;}
		else if(mood==0 && left_encoder_error<0 && left_encoder_error>-50 && right_encoder_error<0 && right_encoder_error>-50 ) {  run(50,50);wait1Msec(100);run(0,0);  break;}
		else if(mood==1 && abs(right_encoder_error)<50  && abs(left_encoder_error)<50 ) { run(0,0);wait1Msec(100);run(0,0);  break;}

		if(mood == 0)  // zhi
		{
			if(abs(left_encoder_error)<200)  ///////////// zuo
			{
				if(left_encoder_error>0) left_speed=80;
				else if(left_encoder_error<0) left_speed = -80;
			}
			else
			{
				if(left_encoder_error>0) left_speed=127;
				else if(left_encoder_error<-0) left_speed = -127;
			}

			if(abs(right_encoder_error)<200)  /////////////// you
			{
				if(right_encoder_error>0) right_speed=80;
				else if(right_encoder_error<-0) right_speed = -80;
			}
			else
			{
				if(right_encoder_error>0) right_speed=127;
				else if(right_encoder_error<0) right_speed = -127;
			}
		}
		else if(mood == 1)  // guai
		{
			if(right_encoder_error>50) right_speed=127;
			else if(right_encoder_error<-50) right_speed = -127;
			else right_speed = 0;
			if(left_encoder_error>50) left_speed=127;
			else if(left_encoder_error<-50) left_speed = -127;
			else left_speed = 0;
		}
		run(left_speed,right_speed);
	}
}

////////////////////  updown //////////////////////////

void Updown_Control(int updown_target_value)
{
	int updown_angle_error;
	int updown_speed;
	int up_down=2;
	clearTimer(T2);

	while(1)
	{
		if(time1(T2)>1500) break;

		updown_angle_value = SensorValue[updown_angle_sensor_2];
		updown_angle_error = updown_target_value - updown_angle_value;

		if(up_down==2)
		{
			if(updown_angle_error > 0) up_down=1;   //up
			else up_down=0; //down
		}

		if(abs(updown_angle_error)<150)
		{
			if(updown_angle_error>0) updown_speed=30;
			else if(updown_angle_error<0) updown_speed = -30;
		}
		else
		{
			if(updown_angle_error>0) updown_speed=127;
			else if(updown_angle_error<0) updown_speed = -127;
		}
		if(updown_angle_error<50 && updown_angle_error>-50)
			{
				if(up_down == 1) { updown(-40);wait1Msec(150);updown(0);}
				else if(up_down == 0) { updown(40);wait1Msec(150);updown(0);}
				break;
			}
		updown(updown_speed);
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////
void salverup()
{
	while(SensorValue[salver_potentiometer]>820)
	{
		motor[salver_motor_6] = 127;
		motor[salver_motor_7] = 127;
	}
		motor[salver_motor_6] = 0;
		motor[salver_motor_7] = 0;
}
void salverdown()
{
	while(SensorValue[salver_potentiometer]<3300)
	{
		motor[salver_motor_6] = -127;
		motor[salver_motor_7] = -127;
	}
		motor[salver_motor_6] = 0;
		motor[salver_motor_7] = 0;
}
//The parameter is from 0 to 4
void updownauto(int updown_angle_int)
{
	int updown_angle_value;
	int updown_angle;
	updown_angle=2250-362*updown_angle_int;
	updown_angle_value=SensorValue[updown_angle_sensor_2];
	if(updown_angle>updown_angle_value)
		while(SensorValue[updown_angle_sensor_2]<updown_angle)
			updown(-30);
	else if(updown_angle<updown_angle_value)
		while(SensorValue[updown_angle_sensor_2]>updown_angle)
			updown(127);

		updown(20);

}
void turn(int angle)
{
	int delta=2;
	int deltaOld=0;
	int output;
	int enterTime=nSysTime;
	while(delta>=1) //&& nSysTime-enterTime<2000 )
	{
		delta=angle-SensorValue[GYRO];
		datalogAddValue(1,delta);
		output=delta/ANGLE_KP+(delta-deltaOld)/ANGLE_KD;
		run(-output,output);
		writeDebugStream("%d\n",delta);
		deltaOld=delta;
	}
}
void run1()
{
	int target=1250;
	int right_encoder,left_encoder;
	int oldvalue,now;
	int value;
	SensorValue[run_left_encoder_sensor_3]=0;
	SensorValue[run_right_encoder_sensor_1]=0;
	while(abs(SensorValue[run_left_encoder_sensor_3])<target&&abs(SensorValue[run_right_encoder_sensor_1])<target)
		{
		right_encoder=SensorValue[run_right_encoder_sensor_1];
		left_encoder=SensorValue[run_left_encoder_sensor_3];
		now=target-right_encoder;
		value=now/2;
		run(value,value);
	}
	run(0,0);
}

task run_t()
{
	run1();
}
task salverdown_t()
{
	salverdown();
}
task salverup_t()
{
	salverup();
}
task updownAuto1_t()
{
	updownauto(1);
}
task updownAuto0_t()
{
	updownauto(0);
}
void runSalverdown()
{
	startTask(run_t,255)	;
	startTask(salverdown_t,255);
	startTask(salverup_t,254);

}

task putYellow()
{
	updownauto(0);
	//rotate(127);
	//delay(1000);
	intake(-120);
	wait1Msec(500);
}

void auto_1()
{
		updownauto(1);
		startTask(run_t,255)	;
		startTask(salverdown_t,255);
		startTask(salverup_t,254);
		startTask(putYellow,253);

}

void auto_2()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{

	SensorType[GYRO]=sensorNone;
	delay(100);
	SensorType[GYRO]=sensorGyro;
	delay(200);

	SensorValue[run_left_encoder_sensor_3]=0;
	SensorValue[run_right_encoder_sensor_1]=0;
//automatic code////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
  while (true)
  {
  	rotate_angle_value = SensorValue[rotate_angle_sensor_1];
    updown_angle_value = SensorValue[updown_angle_sensor_2];
    run_left_encoder_value = SensorValue[run_left_encoder_sensor_3];
    run_right_encoder_value = SensorValue[run_right_encoder_sensor_1];
		updown_bump_value = SensorValue[updown_bump_sensor_5];


	 /* if(updown_angle_value<1300)
	  	{
	  		if(vexRT[Ch2]<30) {	bump_flag=1;updown(20);}
	  		else bump_flag=0;
	  	}
	  else if(updown_angle_value>1300)
	  	{
	  		if(vexRT[Ch2]>-30) {	bump_flag=1;updown(-20);}
	  		else bump_flag=0;
	  	}
	  else bump_flag=0;*/

		clearLCDLine(0);
    clearLCDLine(1);
    displayLCDNumber(0,0,run_left_encoder_value);
    displayLCDNumber(0,6,run_right_encoder_value);
    displayLCDNumber(0,12,updown_angle_value);
    displayLCDString(1,0,"zuo");
    displayLCDString(1,6,"you");
    displayLCDString(1,12,"updown");

 /*   if(vexRT(Btn7D) == 1) Updown_Control(1400);
    if(vexRT(Btn7R) == 1) Updown_Control(1700);
    if(vexRT(Btn7R) == 1)
  	{
  		SensorValue[run_left_encoder_sensor_3]=0;
			SensorValue[run_right_encoder_sensor_1]=0;

  		Run_Control(1000,1000,0);
  	}
*/
//automatic code area




	//manual code area
	  manual_run();
   /* if(bump_flag == 0)*/ manual_updown();
    manual_intake();
    manual_rotate();
    manual_salver();


    	////////////////automatic code//////////////////////
 // if(vexRT[Btn8U]==1)
//  	auto_1();



  //////////////////////////////////////////////




  }
}
