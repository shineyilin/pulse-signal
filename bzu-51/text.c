	  #include<AT89X51.H>
	   sbit bell=P1^0;

	  void main()
	  {
	  	int i;
		for(i=1000;i>0;i--)
		{
		bell=1;
		bell=0;
		}

	  
	  }


	    #include<AT89X51.H>
  sbit l1=P0^0;
  sbit k1=P3^5;
  sbit bell=P1^0;

  void delay2s()
  {
  	int i,j,k;
	for(i=20;i>0;i--)
	for(j=20;j>0;j--)
	for(k=248;k>0;k--)
;
  }

  void bells()
  
  {int i,j;
  for(i=100;i>0;i--)
  for(j=400;j>0;j--)
  {
 	bell=0;
	bell=1;
  }
  }

 void main()
 {
 int i;
 while(1)
 {
if(k1==0)
	{
	for(i=8;i>0;i--)
     {
		l1=0;
		bells();
		delay2s();

		l1=1;
		bells();
		delay2s();	

		}
	}
else
l1=1;
 }
 }