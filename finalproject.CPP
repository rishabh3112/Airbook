/*******************************************************************
	Airlines Ticketing System
	-------------------------
	+ Objective: To manage ticketing process across all airlines

	Made by : Rishabh chawla and Siddharth tripathi
*******************************************************************/

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>

struct flight
{
	char type[20],timings[20];
	int ftno;
};

class airline
{
	protected:

		long int regcode;
		char aname[20];
		flight f[10];
		int fno;
		void assignregcode()
		{
			randomize();
			regcode = (random(9)+1)*1000 + (random(9)+1)*100 + (random(9)+1)*10 + (random(9)+1);
		}

	public:
		airline()
		{
		    fno=0;
		}

		void aget()
		{
			// To get details of airline

			cout<<"\n-------------\n";
			cout<<"\nName of airlines:\t";

			gets(aname);

			assignregcode();
		}

		void ashow()
		{
			// To show details of airline

			cout<<"\n-------------\n";
			cout<<"Registration code of airlines:\t";
			cout<<regcode;
			cout<<"\nName of airlines:\t";
			puts(aname);
			cout<<"\n Flights available: \n";
			for(int i=0;i<fno;i++)
			{
				cout<<" "<<i+1<<". Type:\t"<<f[i].type<<endl;
				cout<<"    Timings:\t"<<f[i].timings<<endl;
				cout<<"    Flight number:\t"<<f[i].ftno<<endl<<endl;
			}
			cout<<"\n";
		}

		int fget()
		{
			if(fno==10)
				return 0;

			cout<<"\n Enter Flight Type [Domestic/International]: ";
			gets(f[fno].type);
			cout<<" Flight Number: ";
			cin>>f[fno].ftno;
			cout<<" Timings [eg. 14:00]: ";
			gets(f[fno].timings);
			fno++;
			return 1;

		}

		flight rf(int nf)
		{
		   for(int i=0;i<fno;i++)
		   {
			if(nf==f[i].ftno)
				return f[i];
		   }

		}

		int rfno()
		{
			return fno;
		}

		int rrc()
		{
		      // to return value of regcode
		      return regcode;
		}

		char* raname()
		{
			return aname;
		}

};

class ticket:public airline
{
	long int tno;            //ticket no
	char dest[20];          //destination
	char bordstn[20];       //boarding station
	int pno;            //no of passengers
	int ftda;           //date of departure


	void ticket_no_generator()
	{
	    randomize();
	    long int a = (random(9)+1)*1000 + (random(9)+1)*100 + (random(9)+1)*10 + (random(9)+1);
	    tno = a;
	}

	void assign_airline_name()
	{
		airline b;
		ifstream airdata("airlines.dat",ios::binary);
		while(!airdata.eof())
		{
			airdata.read((char*)&b,sizeof(b));

			if(b.rrc()==regcode)
			{
				strcpy(aname,b.raname());

				for(int i=0; i<b.rfno(); i++)
				{
					f[0]=b.rf(fno);
				}
				break;
			}
		}
		airdata.close();
	}

	public:
		void tget()
		{
			cout<<"\n-------------\n";
			cout<<"Enter boarding terminal:\t";
			gets(bordstn);
			cout<<"\nEnter destination :\t";
			gets(dest);
			cout<<"\nEnter no of passengers: \t";
			cin>>pno;
			cout<<"\nEnter date of departure: \t";
			cin>>ftda;
			cout<<"\nRegistration code of airline: \t";
			cin>>regcode;
			cout<<"\nFlight number: \t";
			cin>>fno;
			assign_airline_name();
			ticket_no_generator();
			cout<<"\n-----------------\n";
			cout<<"Your ticket number is "<<tno<<endl;
		}

		void tshow()
		{
			cout<<"\n-------------\n";
			cout<<" General Details\n\n";
			cout<<"Boarding terminal:\t";
			cout<<bordstn;
			cout<<"\nDestination :\t";
			cout<<dest;
			cout<<"\nNo of passengers: \t";
			cout<<pno;
			cout<<"\nDate of departure: \t";
			cout<<ftda;
			cout<<"\nTicket number: \t";
			cout<<tno;
			cout<<"\n\n Flight Details\n\n";
			cout<<"\nAirlines: \t";
			cout<<aname;
			cout<<"\nFlight number: \t"<<f[0].ftno;
			cout<<"\nFlight timings: \t"<<f[0].timings;
			cout<<"\nFlight type: \t"<<f[0].type;


		}

		int rtno()
		{
			return tno;
		}


};

int regairline(airline a)
{
   airline b;
   a.aget();
   ifstream airdata("airlines.dat",ios::binary);
   ofstream airwritr("airlines.dat",ios::binary|ios::app);
   while(airdata)
   {
	airdata.read((char*)&b , sizeof(b));
	if(!strcmpi(b.raname(),a.raname()))
	{
		return 0;
	}
   }

   airwritr.write((char*)&a,sizeof(a));
   return 1;

}

void showairlines()
{
	airline b;
	ifstream airdata("airlines.dat",ios::binary);
	while(airdata)
	{
	   airdata.read((char*)&b , sizeof(b));
	   b.ashow();
	}
}

void showflights()
{
	airline b;
	int f;
	cout<<"\n Enter airline no: ";
	cin>>f;
	ifstream airdata("airlines.dat",ios::binary);
	while(airdata)
	{
	   airdata.read((char*)&b , sizeof(b));
	   if(f==b.rrc())
	   {
		b.ashow();
		f= -1;
		break;
	   }
	}
	if(f!=-1)
		cout<<"\n airline not found";
}

int modifyairlines()
{
   long int s;
   int i;
   airline b;
   fstream airdata;
   airdata.open("airlines.dat",ios::binary|ios::in|ios::out);
   cout<<" Enter registration no of air line to be modified\n";
   cin>>s;
   int pos;
   while(airdata)
   {
	pos=airdata.tellg();
	airdata.read((char*)&b,sizeof(b));
	if(b.rrc()==s)
	{
		airdata.seekp(pos);
		i=1;
		break;
	}
   }


       if(i==1)
       {
	b.aget();
	airdata.write((char*)&b,sizeof(b));
	airdata.close();
	return(1);

       }
       else
       {
	airdata.close();
	return(0);
	}



}

int flight_register()
{
   long int s;
   int i;
   airline b;
   fstream airdata;
   airdata.open("airlines.dat",ios::binary|ios::in|ios::out);
   cout<<" Enter registration no of airline\n";
   cin>>s;
   int pos;
   while(airdata)
   {
	pos=airdata.tellg();
	airdata.read((char*)&b,sizeof(b));
	if(b.rrc()==s)
	{
		airdata.seekp(pos);
		i=1;
		break;
	}
   }


       if(i==1)
       {
	if(b.fget())
	{
		airdata.write((char*)&b,sizeof(b));
		airdata.close();
		return(1);
	}
	airdata.close();
	return(0);

       }
       else
       {
	airdata.close();
	return(0);
       }



}

int authorise()
{
	int i,j,ch;
	char pass[5],ans;
	clrscr();
	for(i=0;i<3;i++)
	{
		clrscr();
		cout<<"\n\n \t\tAdmin Login\n \t\t-----------------------\n\n";
		cout<<" \t\tEnter password:\n \t\t";

		for(j=0;j<5;j++)
		{
			pass[j]=getch();
			cout<<"*";
		}

		pass[j]='\0';

		if(strcmp(pass,"airrs")==0)
		{
			cout<<"\n\n \t\tLogin Succesful\n \t\tOpening Admin Panel ....";
			delay(2000);

			return(1);
		}
		else
		{
			cout<<"\n\n \t\tIncorrect password\n \t\t";
			cout<<3-i-1;
			cout<<" Tries left\n";
			cout<<" \t\tPress any key to continue";
			getch();
			continue;
		}

	}

	return(0);

}

int regticket(ticket a)
{
     cout<<"Available Airlines:\n";
     airline b;
     ifstream airdata("airlines.dat", ios::binary);
     while(!airdata.eof())
     {
	airdata.read((char*)&b,sizeof(b));
	b.ashow();
     }
     airdata.close();
     ofstream ticketwritr("tickets.dat",ios::binary);
     a.tget();

     ticketwritr.write((char*)&a,sizeof(a));
     ticketwritr.close();
     return 1;
}

int ticket_printer(int tno)
{
	int f=0;
	ticket s;
	ifstream ticketdata("tickets.dat",ios::binary);
	while(ticketdata)
	{
		ticketdata.read((char*)&s,sizeof(s));
		if(s.rtno()==tno)
		{
			s.tshow();
			f=1;
			break;
		}
	}
	ticketdata.close();

	if(f==1)
		return 1;

	return 0;
}

int showtickets(int rno)
{
	int f=0;
	ticket s;
	ifstream ticketdata("tickets.dat",ios::binary);
	while(ticketdata)
	{
		ticketdata.read((char*)&s,sizeof(s));
		if(s.rrc() == rno)
		{
			s.tshow();
			f=1;
		}
	}
	ticketdata.close();

	if(f==1)
		return 1;

	return 0;
}

int ticket_unbook(int tno)
{
	ticket s;
	int f=0;
	ifstream ticketdata("tickets.dat",ios::binary);
	ofstream temp("temp.dat",ios::binary);
	while(ticketdata)
	{
		ticketdata.read((char*)&s,sizeof(s));
		if(s.rtno()==tno)
		{
			f=1;
			continue;
		}
		temp.write((char*)&s,sizeof(s));

	}
	ticketdata.close();
	temp.close();
	remove("tickets.dat");
	rename("temp.dat","tickets.dat");

	return f;
}


int modifyticket()
{
   long int s;
   int i;
   ticket b;
   fstream t;
   t.open("tickets.dat",ios::binary|ios::in|ios::out);
   cout<<"Enter ticket no of ticket to be modified\n";
   cin>>s;
   int pos;
   while(t)
   {
	pos=t.tellg();
	t.read((char*)&b,sizeof(b));
	if(b.rtno()==s)
	{
		t.seekp(pos);
		i=1;
		break;
	}
   }


       if(i==1)
       {
	b.tget();
	t.write((char*)&b,sizeof(b));
	t.close();
	return(1);

       }
       else
       {
	t.close();
	return(0);
	}



}


void graphs()
{
	cout<<"\nNo of Airlines registered:\nAirlines:\t";
	ifstream airdata("airlines.dat",ios::binary);
	airline a;
	int count=0;
	int t =200;
	while(airdata)
	{
		airdata.read((char*)&a,sizeof(a));
		count++;
		cout<<"+";
		delay(t);
		t+=t/5;
	}
	cout<<" | "<<count;
	airdata.close();

	cout<<"\nNo of Tickets registered:\nTickets:\t";
	ifstream air("tickets.dat",ios::binary);
	ticket b;
	count=0;
	t =200;
	while(air)
	{
		air.read((char*)&b,sizeof(b));
		count++;
		cout<<"+";
		delay(t);
		t+=t/5;
	}
	cout<<" | "<<count;
	air.close();
}

void main()
{
       start:
       clrscr();
       cout<<"\n\n\t\t\tAirbook\n\t\t\t-------\n\t\t\tAn airticket booking system\n";
       cout<<"\n\n Choose your required option:\n";
       cout<<" 1. Book ticket\n 2. Print ticket\n 3. Modify ticket\n 4. Unbook Ticket\n 5. Admin login\n 6. About us and other info\n 7. Exit\n";
       cout<<"\n Enter choice: ";
       int choice;
       cin>>choice;
       switch(choice)
       {
	case 1:
		clrscr();
		ticket a;
		if(regticket(a))
		{
		     cout<<"\n Please use your ticket number to print ticket";
		     cout<<"\n Opening menu.....";
		     getch();
		     goto start;
		}

		else
		     exit(0);

		break;
	case 2:
		clrscr();
		cout<<" Airbook > Print ticket\n ------------------------\n";
		cout<<"\n Enter Your Ticket Number:\t";
		int tno;
		cin>>tno;
		cout<<"\n";
		if(!ticket_printer(tno))
		{
			cout<<"\nTicket not found";
		}
		getch();
		goto start;
		break;

	case 3:
		clrscr();
		cout<<" Airbook > Modify Ticket\n -----------------------\n";
		if(modifyticket())
		{
			cout<<"\n Ticket Modified. Print Ticket with new ticket number";
			getch();
		}
		else
		{
			cout<<"\n Ticket not found. Please recheck number entered";
			getch();
		}
		goto start;
		break;

	case 4:
	       clrscr();
	       cout<<" Airbook > Unbook Ticket\n -----------------------\n";
	       cout<<"\n Enter ticket number of ticket:\t";
	       int t;
	       cin>>t;
	       if(ticket_unbook(t))
	       {
		cout<<"\n Ticket Unbooked.\n Come back soon to Airbook.";
		getch();
	       }
	       else
	       {
		cout<<"\n Ticket not found";
		getch();
	       }
	 case 5:
		clrscr();
		if(authorise())
		{
		  admin:
		  clrscr();
		  cout<<"\n\n\t\t\tAirbook > Admin Panel\n\t\t\t------------------\n\t\t\tAn airticket booking system\n";
		  cout<<"\n\n Choose your required option:\n";
		  cout<<" 1. Register Airline\n 2. Show airlines\n 3. Modify Airlines\n 4. Register Flight\n 5. Show flights\n 6. Show tickets\n 7. Log out\n";
		  cout<<"\n Enter choice: ";
		  int choice;
		  cin>>choice;
		  switch(choice)
		  {
			case 1:
				clrscr();
				cout<<" Airbook > Admin panel > Register Airline\n";
				airline b;
				if(regairline(b))
				{
					cout<<"\n Airline registered.";
					getch();
				}
				goto admin;
				break;

			case 2:
				clrscr();
				cout<<" Airbook > Admin Panel > Show Airlines\n";
				showairlines();
				getch();
				goto admin;

			case 3:
				clrscr();
				cout<<" Airbook > Admin Panel > Modify Airline\n";
				if(modifyairlines())
				{
					cout<<"\n Airline Modified";
					getch();
				}
				else
				{
					cout<<"\n Airline not found.\n Please recheak number entered.\n";
					getch();
				}
				goto admin;
			case 4:
				clrscr();
				cout<<" Airbook > Admin Panel > Register Flight\n\n";
				flight_register();
				getch();
				goto admin;
			case 5:
				clrscr();
				cout<<" Airbook > Admin Panel > Show Flights\n\n";
				showflights();
				getch();
				goto admin;
			case 6:
				clrscr();
				cout<<" Airbook > Admin Panel > Show tickets\n ------------------------\n";
				cout<<"\n Enter Airline Number:\t";
				int rno;
				cin>>rno;
				cout<<"\n";
				if(!showtickets(rno))
				{
					cout<<"\n Airline not found";
				}
				getch();
				goto admin;
				break;
			case 7:
				clrscr();
				cout<<"\n\n \t\tLogout Succesful\n \t\tOpening Main Menu.....";
				delay(2000);
				goto start;

			default:
				cout<<" Enter valid Choice\n";
				goto admin;

		  }
		}
		else
		{
			goto start;
		}
	 case 6:
		clrscr();
		cout<<"Airbook > About us";
		cout<<"\n\n ";
		cout<<"Airbook is a unique airbooking and airline management system.\n";
		cout<<" It makes a users experience simplified as he or she can book ticket witout paying money and pay at cheakout.\n";
		cout<<" Many airlines and tickets have already registered and booked on the platform.\n";
		cout<<"\n\n";
		graphs();
		cout<<"\n\n ------------------------------------ \n";
		cout<<" Made by Rishabh Chawla and Siddarth Tripathi";
		getch();
		goto start;

	 case 7:
		clrscr();
		cout<<"\n\n \t\tHave a Great Day!\n\n \t\tCome Soon to Airbook!!";
		delay(2000);
		exit(0);

       }

       getch();
}