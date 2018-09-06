#NXP MPC5604芯片智能车程序
#built by 安徽工程大学机器人协会 Zamir
#build date 2017.6

主要文件说明：

	1，deal
		本文件是核心函数所在位置，包括了整个路径的识别与处理。
		函数说明：
		1)，AD_zhi()
			读取电感读得的AD值并进行处理，供后续程序处理。注意实际电感排序与程序里各个通道的对应关系。
		2)，DirectionControl()
			方向控制函数，利用差比合计算车身与赛道的偏角，采用pid反馈调节实时控制舵机的打角实现方向的控制。并对特殊赛道进行识别处理。其中pid的参数值计算位于Interrupt文件中。
			
	2，Interrupt
		本文件配置了系统的中断，使系统可以循环执行方向控制函数实现控制。
		1)，PIT1inter()
			定时器1中断处理函数，其中包含了Encoder_count()函数(用以读取编码器获得数度值计算feedback实现闭环控制)，DirectionControl()函数(用以控制车)。其中，K1,K2分别为两个拨码开关的状态，使车有多个基速度档，以便适应实际情况。K3,K4为测试时的速度档，不稳定。kp，kd为pid的p值与d值，由FeedBck计算而来，需要测试其表达式中的参数以获得最佳的pd参数值实现好的闭环控制。
		2)，Tingche()
			停车中断函数，由外部中断控制，在引脚被触发时进入中断，实现检测停车线后停车的处理。

	3，main
		本文件是main()函数的所在，系统由此处开始运行。其中：
		1)，System_init()
			系统初始化函数，其中包含了各个模块的初始化函数，将在后面介绍。
		2)，Visual_Data()
			将DATA数组中的数据通过蓝牙发送至上位机，用以读取传感器的值来分析。
			由于一次只能发送四个int字符，故在需要读取超过四个的数据时，需要切换拨码开关K1,K2来切换发送不同的数据。

	4，SYSTEM
		本文件包含了System_init()函数，其中包括了各个模块的初始化：
		void System_init()
		{
	  		SWT_DisableWatchDog(); 		//看门狗初始化
	  		SYSTEM_Init(); 				//锁相环配置，配置系统主频
	  		LED_Init();  				//LED灯相关引脚初始化
			PWM_Init();					//PWM模块初始化，用以电机以及舵机的控制
	   		EX_Interrupt();				//配置并初始化硬件中断
	  		initIrqVectors();			//配置并初始化中断向量表
	  		initINTC();  				//配置并初始化软件中断
	  		enableIrq();				//使能中断
	   		initPIT();					//初始化定时器中断
	  		ADC_Init();					//ADC模块初始化
	  		Encoder_Init();				//编码器初始化
	  		LINFlex0_init();			//UART串口初始化
	  		init_I2C();					//I2C模块初始化
		}
