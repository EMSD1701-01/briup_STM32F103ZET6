#include <stdlib.h>
#include "briupMPU6050.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
										  0,-1, 0,
										  0, 0, 1};

#define q30  1073741824.0f
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
char num[50];
float Pitch,Roll,Yaw;
unsigned long sensor_timestamp;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];

void briupMPU6050Init(void)
{
	int result;
	
	i2cInit();
	
	result = mpu_init();//检测初始化返回值，初始化成功返回值为0;

	if(!result)//检测初始化是否每一步都成功
	{

		printf("mpu initialization complete......\r\n ");	 	  //mpu_set_sensor
		if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
			printf("mpu_set_sensor complete ......\r\n");
		else
			printf("mpu_set_sensor come across error ......\r\n");
		
		if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))	   	  //mpu_configure_fifo
			printf("mpu_configure_fifo complete ......\r\n");
		else
			printf("mpu_configure_fifo come across error ......\r\n");
		
		if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))	   	  //mpu_set_sample_rate
			printf("mpu_set_sample_rate complete ......\r\n");
		else
			printf("mpu_set_sample_rate error ......\r\n");
		
		if(!dmp_load_motion_driver_firmware())   	  //dmp_load_motion_driver_firmvare
			printf("dmp_load_motion_driver_firmware complete ......\r\n");
		else
			printf("dmp_load_motion_driver_firmware come across error ......\r\n");
		
		if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) 	  //dmp_set_orientation
			printf("dmp_set_orientation complete ......\r\n");
		else
			printf("dmp_set_orientation come across error ......\r\n");
		
		if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
		DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
		DMP_FEATURE_GYRO_CAL))		   	  //dmp_enable_feature
			printf("dmp_enable_feature complete ......\r\n");
		else
			printf("dmp_enable_feature come across error ......\r\n");
		
		if(!dmp_set_fifo_rate(DEFAULT_MPU_HZ))   	  //dmp_set_fifo_rate
			printf("dmp_set_fifo_rate complete ......\r\n");
		else
			printf("dmp_set_fifo_rate come across error ......\r\n");
		
		run_self_test();	//运行自检程序
		
		if(!mpu_set_dmp_state(1))
			printf("mpu_set_dmp_state complete ......\r\n");
		else
			printf("mpu_set_dmp_state come across error ......\r\n");
	}
}

void getMPU6050Data(short * x, short * y)
{
	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);	//从FIFO获取数据包 timestamp为采集数据速度，此时为0.全速模式
	if (sensors & INV_WXYZ_QUAT )
	{
		q0=quat[0] / q30;
		q1=quat[1] / q30;
		q2=quat[2] / q30;
		q3=quat[3] / q30;
		Pitch  = asin(2 * q1 * q3 - 2 * q0* q2)* 57.3; // pitch
		Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
		Yaw = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
		*y = (s16)Pitch;
		*x = (s16)Roll;
	}
}
