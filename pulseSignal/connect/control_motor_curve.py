import numpy as np
import matplotlib.pyplot as pt


x_list = []
y_list = []


delta_t = 6/27. *10**-6
delta_x = 1/32768.
for calc_count in np.arange(20,200):
	time = calc_count*delta_t
	
	x_list.append( time )
	rpm = delta_x / time *60
	#speed = rpm * 5 /60.
	y_list.append( rpm*50 )


pt.plot(x_list, y_list,'r.')
pt.xlabel("time")
pt.ylabel("rotation per minit")
pt.show()

