#coding=utf-8
from myserial import my_serial
import threading
import binascii
import time
import msvcrt


def str_hex(val): #string 转换成 hex 数据
	temp = list()
	for v in val:
		temp.append( binascii.b2a_hex(v) ) 
		temp.append(" ")
	return (''.join(temp)).upper()


class main(threading.Thread):
	def __init__(self):
		super(main,self).__init__()
		self.__isopen__ = False # run flag
		self.__issend__ = False # data send flag
		self.revflag    = False
		self.__sendcount__	= 0
		self.__revcount__	= 0
		self.__time__		= time.strftime("%Y.%m.%H_%M_%S")
		self.__dir__		= "data\\"
		
		self.__mode__ = 0    # 0	hand operate
							 # 1	auto operate
		self.hand = my_serial()
		

	def begin(self):
		print 'begin....'
		self.onOpen()
		#while(1):
		#	self.onSendData()
	
	def onKeybordRev(self):
		if msvcrt.kbhit():
			ch = (msvcrt.getch()).lower()
			if ch == 's':  #stop
				print "STOP"
				return 1
			if ch == "p":  #pause
				print "PAUSE"
				return 2
			if ch == 'j':  # jog
				print "JOG"
				return 3
			if ch == 'a':  # auto
				print "AUTO"
				return 4
			if ch == 'c':  # continue
				print "CONTINUE"
				return 5
		return 0

	def onSendData(self, sendData):
		file_name =self.__dir__ + self.__time__ + "sendData.DB"
		f_hand = open(file_name, 'w')
		if self.__isopen__ == True:
			for line_data in sendData:
				#print ">>Out: "
				temp = 0
				f_hand.write("%s: " %(time.asctime() ) )
				for data in line_data:
					#print "0x%X" %(data),
					self.hand.serial_write( chr(data) )
					temp+=1
					f_hand.write("0x%X " %( data) )
					self.__sendcount__ += 1
					
				cmd = self.onKeybordRev()
				if cmd == 1:
					self.hand.serial_write(chr(0xff) )
					return
				if cmd == 2:
					self.hand.serial_write(chr(0xff) )
					while( self.onKeybordRev() == 0 ):
						continue
					self.hand.serial_write(chr(0x00) )
					
				f_hand.write("\n")
				time.sleep(0.01)

	def getSendDataCount(self):
		print 'on seld data number: ' + str(self.__sendcount__)
		print 'on rev  data number: ' + str(self.__revcount__ )

	def clearSendDataCount(self):
		self.__sendcount__ = 0
		self.__revcount__ = 0

#######################################################################
#		this method is a serial open method
#######################################################################
	def onOpen(self):
		print 'On opening serial...'
		if self.__isopen__ == False:
			if self.hand.serial_open() == True:
				self.__isopen__ = True
				self.hand.serial_clear_buffer()
				self.start()
				print 'Open serial sucess!!!'
			else:
				print "Open serial error, please check the param!!!"
				return False
		else:
			print 'The serial is already opened!!!'
		return True
#######################################################################
	
		
	def run(self):
		file_name = self.__dir__ + self.__time__ + "revData.DB"
		f_hand = open(file_name, 'w')

		while(self.__isopen__ == True ):
			#print 'geting data...'
			if self.hand.serial_iswaiting()> 0:
				self.revflag = True
				print '>>IN: ',
				print time.asctime(),': ',
				f_hand.write("%s: " %(time.asctime() ) )
				for ch in self.hand.serial_read():
					rev_data = ord(ch)
					self.__revcount__ += 1
					f_hand.write("0x%X " %(rev_data) )
					print "0x%X" % (rev_data),	
				print 
				f_hand.write("\n")
				self.revflag = True
				


class fileIO:
	def __init__(self):
		self.file_name		= str()
		self.file_size		= int()
		self.read_data		= list()
		self.read_hex_data	= list()
	
	def readFile(self,file_name):
		self.file_name	= file_name
		self.hand		= open(file_name, "r")
		self.read_data	= self.hand.readlines()
		self.file_size  = len(self.read_data)
	
	def getData(self):
		for ch_line in self.read_data:
			temp = list()
			for ch in ch_line.split():
				temp.append( int( ch,16 ) )
			self.read_hex_data.append(temp)
		return self.read_hex_data

	def getSize(self):
		return self.file_size

	def closeFile(self):
		self.hand.close()


if __name__ == "__main__":
	w = main()
	F = fileIO()
	F.readFile("test_1.DB")
	#print F.getData()
	w.begin()
	sendData = F.getData() 

	while(1):
		w.onSendData( sendData)
		w.getSendDataCount()
		w.clearSendDataCount()
		time.sleep(0)
		break
