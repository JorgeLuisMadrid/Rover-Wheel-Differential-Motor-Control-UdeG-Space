//Jorge Luis Madrid Gómez 09/07/22
//UdeG Space
#include <ros.h>
#include <Arduino.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

//Pins
#define EN_M1  6;
#define in1_M1 9;
#define in2_M1 4;
#define EN_M2 5;
#define in1_M2 8;
#define in2_M2 7;

//Parameters
const float Radius = 0.127;  //Radius
const float Length = 0.945;  //Length

//Speed variables
float left_speed = 0;
float right_speed = 0;
int = left_pwm = 0;
int = right_pwm = 0;

//Motor class
class DCmotor
{
private:
	//Variables
	byte In1;	//Direction Pin
	byte In2;	//Direction Pin
	byte En;	//Enable Pin
public:
	//Constructor
	DCmotor(byte en, byte in1, byte in2){
		this->En = en;
		this->In1 = in1;
		this->In2 = in2;
		Init();
	}
	//Methods
	void Init(){				//Motor Initialization
		pinMode(En,OUTPUT);
		pinMode(In1,OUTPUT);
		pinMode(In2,OUTPUT);
		Stop();
	}
	void Stop(){				//Motor Stop
		analogWrite(En,0);
		digitalWrite(In1,LOW);
		digitalWrite(In2,LO2);
	}
	void Forward(int pwm){		//Forward movement
		analogWrite(En,pwm);
		digitalWrite(In1,LOW);
		digitalWrite(In2,HIGH);
	}
	void Backward(int pwm){		//Backward movement
		analogWrite(En,pwm);
		digitalWrite(IN1,HIGH);
		digitalWrite(IN2,LOW);
	}
};

//Motor instances
DCmotor LeftWheel(EN_M1,in1_M1,in2_M1);		//Left Motor
DCmotor RightWheel(EN_M2,in1_M2,in2_M2);	//Right Motor

//Callback function
void wheelControls( const geometry_msgs::Twist& msg){
	//Kinematics calculus
	left_speed = (2*msg.linear.x - Length*msg.angular.z)/(2*Radius);
	right_speed = (2*msg.linear.x + Length*msg.angular.z)/(2*Radius);

	//PWM converter
	left_pwm = int(255*left_speed/7.1);
	right_pwm = int(255*right_speed/7.1);
	
	//Motor control
	if (left_speed < 0){
		LeftWheel.Backward(-left_pwm);
	}
	else if (left_speed > 0){
		LeftWheel.Forward(left_pwm);
	}
	else{
		LeftWheel.Stop();
	}

	if (right_speed < 0){
		RightWheel.Backward(-right_pwm);
	}
	else if (right_speed > 0){
		RightWheel.Forward(right_pwm);
	}
	else{
		RightWheel.Stop();
	}
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &wheelControls );

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
}