import numpy as np


def getSpeed(current_time):
	
	speed_1_data = list()
	speed_2_data = list()

	cT = 10.

	eps_speed = 0.001
	##################Calc speed 1 data###########################
	#####                                                     ####
	##############################################################

	direction_1 = 0
	#speed_1 = np.float64( 200*np.sin(2*np.pi/cT * current_time))
	#speed_1 = 10
	#speed_1 = -( 5*np.cos(2*np.pi/cT * current_time )-5  )
	speed_1 = 5*np.cos(2*np.pi/cT * current_time) 
	if speed_1 >= 0:
		direction_1 = 0
	else:
		direction_1 = 1
		speed_1 = -speed_1

	if speed_1 < eps_speed:
		speed_1_data = [direction_1,0]
	else:
		speed_1_data = [direction_1, speed_1]
	##################Calc speed 2 data###########################
	#####                                                     ####
	##############################################################	
	direction_2 = 0
	#speed_1 = np.float64( 200*np.sin(2*np.pi/cT * current_time))
	#speed_1 = 10
	#speed_2 = -( 5*np.cos(2*np.pi/cT * current_time )-5  )
	speed_2 = 5*np.sin(2*np.pi/cT * current_time) 
	if speed_2 >= 0:
		direction_2 = 0
	else:
		direction_2 = 1
		speed_2 = -speed_2

	if speed_2 < eps_speed:
		speed_2_data = [direction_2,0]
	else:
		speed_2_data = [direction_2, speed_2]
	
	return [speed_1_data, speed_2_data]


class translateCode:
	def __init__(self):
		self.delta_time		= 0.01
		self.current_time	= 0
		self.deltaX			= 1/32768.
		self.freq			= 27*10**6
		self.T				= 1./self.freq*12/2
		
		self.direction_1	= 0
		self.direction_2	= 0
		self.runflag_1		= False
		self.runflag_2		= False

		self.controlCodeList = list()


	def calcCounter_1(self,speed): #rpm
		controlCode = list()
		if speed[1] == 0:
			controlCode.append(0xff)
			self.runflag_1 = False
			return controlCode
		else:
			deltaT = self.deltaX*60./speed[1]*1./2.
			delta_counter = np.int( deltaT/self.T )
			if delta_counter > 65536:
				delta_counter = 65536
			counter = 65536 - delta_counter + 10
			control_data = [0x01, counter/0x100, counter%0x100]
			return control_data
	
	def calcCounter_2(self,speed): #rpm
		controlCode = list()
		if speed[1] == 0:
			controlCode.append(0x04)
			self.runflag_2 = False
			return controlCode
		else:
			deltaT = self.deltaX*60./speed[1]*1./2.
			delta_counter = np.int( deltaT/self.T )
			if delta_counter > 65536:
				delta_counter = 65536
			counter = 65536 - delta_counter + 10
			control_data = [0x05, counter/0x100, counter%0x100]
			return control_data
	
	
	def process(self):
		self.initMotorAll()
		self.controlCodeList.append([0x00])
		for time in np.arange(0,10, self.delta_time):
			self.current_time = time
			speedAll = getSpeed(self.current_time)
			##########################################################
			if self.direction_1 != speedAll[0][0]:
				self.controlCodeList.append( [0x02, speedAll[0][0]] )
				self.direction_1 = speedAll[0][0]

			if self.direction_2 != speedAll[1][0]:
				self.controlCodeList.append( [0x06, speedAll[1][0]] )
				self.direction_2 = speedAll[1][0]


			control_data_1 = self.calcCounter_1(speedAll[0])
			control_data_2 = self.calcCounter_2(speedAll[1])

			self.controlCodeList.append( control_data_1 )
			self.controlCodeList.append( control_data_2 )

			if control_data_1[0] == 0x01 and self.runflag_1 == False:
				self.controlCodeList.append([0x00])
				self.runflag_1 = True

			if control_data_2[0] == 0x05 and self.runflag_2 == False:
				self.controlCodeList.append([0x03])
				self.runflag_2 = True

			###########################################################
		self.controlCodeList.append([0xFF])
		self.controlCodeList.append([0x04])
	
	def initMotorAll(self):
		self.controlCodeList.append([0x02, 0x00])
		self.controlCodeList.append([0x06, 0x00])
	
	
	def writeCodeList(self):
		file_name = "test_1.DB"
		f_hand = open(file_name, "w")
		for line_data in self.controlCodeList:
			for data in line_data:
				temp = "%x " %(data)
				#raw_input()
				f_hand.write(temp)
			f_hand.write('\n')
			
	


if __name__ == "__main__":
	h = translateCode()
	h.process()
	h.writeCodeList()
