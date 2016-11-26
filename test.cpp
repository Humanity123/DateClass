#include <iostream>
#include "Date.cxx"
#include <string>
#include <stdexcept>
#include <sstream>

void testDateFormatConstructor(){
	cout<<"==============================================================================="<<endl;
	cout<<"Testing Date Format First Constructor true statements will be printed"<<endl<<endl;
	const char*  day[]={NULL,"d","dd","abd","de"};
	const char*  month[]={NULL,"m","mm","mmm","ad","amm"};
	const char* year[]={NULL,"yy","yyyy","as","ayyy"};
	for(int i=0;i<5;++i){
		for(int j=0;j<6;++j){
			for(int k=0;k<5;++k){
				try{
					DateFormat f(day[i],month[j],year[k]);
					cout<<"DateFormat type constructed with type\t\t\t\t\t\t"<<((day[i]!=NULL)?day[i]:"NULL")<<"\t"<<((month[j]!=NULL)?month[j]:"NULL")<<"\t"<<((year[k]!=NULL)?year[k]:"NULL")<<endl;
				}
				catch(invalid_argument e){
					cout<<"***ERROR  invalid_argument- "<<e.what()<<" with type "<<((day[i]!=NULL)?day[i]:"NULL")<<"\t"<<((month[j]!=NULL)?month[j]:"NULL")<<"\t"<<((year[k]!=NULL)?year[k]:"NULL")<<endl;
				}
				catch(domain_error e){
					cout<<"***ERROR  domain_error-     "<<e.what()<<" with type "<<((day[i]!=NULL)?day[i]:"NULL")<<"\t"<<((month[j]!=NULL)?month[j]:"NULL")<<"\t"<<((year[k]!=NULL)?year[k]:"NULL")<<endl;
				}
				catch(out_of_range e){
					cout<<"***ERROR  out_of_range-     "<<e.what()<<" with type "<<((day[i]!=NULL)?day[i]:"NULL")<<"\t"<<((month[j]!=NULL)?month[j]:"NULL")<<"\t"<<((year[k]!=NULL)?year[k]:"NULL")<<endl;
				}
			}
		}
	}
	cout<<endl;
	cout<<"========================================================================"<<endl;
	cout<<"Testing Date Format Second Constructor true statements will be printed"<<endl<<endl;
	string  days[]={"-","d-","dd-","d","abd-","de"};
	string  months[]={"-","m-","mm-","mmm-","ad-","--"};
	string years[]={"","yy","yyyy","as","ayyy"};

	for(int i=0;i<6;++i){
		for(int j=0;j<6;++j){
			for(int k=0;k<5;++k){
				try{
					DateFormat f((days[i]+months[j]+years[k]).c_str());
					cout<<"DateFormat type constructed with type\t\t\t\t\t\t\t"<<(days[i]+months[j]+years[k])<<endl;
				}
				catch(invalid_argument e){
					cout<<"***ERROR   invalid_argument- "<<e.what()<<"\twith type\t"<<(days[i]+months[j]+years[k])<<endl;
				}
				catch(domain_error e){
					cout<<"***ERROR   domain_error-     "<<e.what()<<"\twith type\t"<<(days[i]+months[j]+years[k])<<endl;
				}
				catch(out_of_range e){
					cout<<"***ERROR   out_of_range-     "<<e.what()<<"\twith type\t"<<(days[i]+months[j]+years[k])<<endl;
				}
			}
		}
	}

	cout<<endl;
	cout<<"========================================================================"<<endl;
	cout<<"Testing Date Format Default Constructor true statements will be printed"<<endl<<endl;
	DateFormat f;
	Date::setFormat(f);
	Date d;
	cout<<d<<endl;
	cout<<"DateFormat default constructed"<<endl;
	cout<<endl;
}
void testDateConstructor(){
	cout<<"==============================================================================="<<endl;
	cout<<"Testing Date  First Constructor(Day,Month,Year) true statements will be printed"<<endl<<endl;
	
	Day day[]={D01,D15,D28,D29,D30,D31};
	Month month[]={Jan,Feb,Jul,Aug,Nov};
	Year year[]={1949,1950,2000,2049,2050};

	for(int i=0;i<6;++i){
		for(int j=0;j<5;++j){
			for(int k=0;k<5;++k){
				try{
					Date d(day[i],month[j],year[k]);
					cout<<"Date type constructed"<<" with \t\t\t\t\t\t\t\t\t\tday- "<<day[i]<<"\tmonth- "<<month[j]<<"\tyear- "<<year[k]<<endl;
				}
				catch(invalid_argument e){
					cout<<"***ERROR invalid_argument- "<<e.what()<<" with \t\tday- "<<day[i]<<"\tmonth- "<<month[j]<<"\tyear- "<<year[k]<<endl;
				}
				catch(domain_error e){
					cout<<"***ERROR domain_error-     "<<e.what()<<" with \t\tday- "<<day[i]<<"\tmonth- "<<month[j]<<"\tyear- "<<year[k]<<endl;
				}
				catch(out_of_range e){
					cout<<"***ERROR out_of_range-     "<<e.what()<<" with \t\tday- "<<day[i]<<"\tmonth- "<<month[j]<<"\tyear- "<<year[k]<<endl;
				}
			}	
		}
	}

	cout<<endl;
	cout<<"==============================================================================="<<endl;
	cout<<"Testing Format not meant for input true statements will be printed"<<endl<<endl;	
	DateFormat formats[]={DateFormat(NULL,"mm","yy"),DateFormat("dd",NULL,"yy"),DateFormat("dd","mmm","yy"),DateFormat("dd","mm",NULL)};
	for(int i=0;i<4;++i){
		Date::setFormat(formats[i]);
		try{			
			
			Date d("12-03-99");
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error-     "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range-     "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
		try{				
			Date d("12-Jan-99");
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error-     "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range-     "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
	}
	

	cout<<endl;

	DateFormat f("d-mm-yyyy");
	Date::setFormat(f);
	cout<<"==========================================================================================================="<<endl;
	cout<<"Testing Date  Second Constructor(const char *) with input format dd-mm-yyyy true statements will be printed"<<endl<<endl;	
	string days[]={"1-","1","28-","29-","30-","31-","32-"};
	string months[]={"1-","2","01-","12-","13-"};
	string years[]={"1949","99","1950","a016","2049","2050"};
	for(int i=0;i<7;++i){
		for(int j=0;j<5;++j){
			for(int k=0;k<6;++k){
				try{	
					Date d((days[i]+months[j]+years[k]).c_str());
					cout<<"Date Constructed with type d-mm-yyyy\t\t\t\tdate value-"<<(days[i]+months[j]+years[k])<<endl;
				} 
				catch(invalid_argument e){
					cout<<"***ERROR invalid_argument -"<<e.what()<<" \t\tdate value-\t"<<(days[i]+months[j]+years[k])<<endl;

				}
				catch(domain_error e){
					cout<<"***ERROR domain_error     -"<<e.what()<<"   \t\tdate value-\t"<<(days[i]+months[j]+years[k])<<endl;
				}
				catch(out_of_range e){
					cout<<"***ERROR out_of_range     -"<<e.what()<<"   \t\tdate value-\t"<<(days[i]+months[j]+years[k])<<endl;
				}
				catch(exception e){
					cout<<"***ERROR Unknow Exception"<<endl;
				}
			}
		}
	}
	cout<<endl;

	cout<<"============================================================================================"<<endl;
	cout<<"Testing Date Copy Constructor with output format dd-mm-yyyy true statements will be printed"<<endl<<endl;	
	{
		DateFormat f("dd-mm-yyyy");
		Date::setFormat(f);
		cout<<"Using a date 29-02-1996 for copy"<<endl;
		Date d2("29-02-1996");
		Date d=d2;
		cout<<"The test date is "<<d2<<" the copy constructed date is "<<d<<endl;
	}
	cout<<endl;

	cout<<"=============================================================================================="<<endl;
	cout<<"Testing Date  Default Constructor with output format dd-mm-yyyy true statements will be printed"<<endl<<endl;	
	{
		DateFormat f("dd-mm-yyyy");
		Date::setFormat(f);
		Date d;
		cout<<"Todays Date is (in format dd-mm-yyyy) "<<d<<endl;
	}
	cout<<endl;


}
void testCopyAssignment(Date & d1, Date & d2){
	Date temp=d1;
	cout<<"========================================================"<<endl;
	cout<<"Testing Copy Assignment true statements will be printed"<<endl<<endl;
	cout<<d1<<" after being assigned  "<<d2<<" is "<<(d1=d2)<<endl;
	d1=temp;
	cout<<endl;
}
void testUnaryArithmeticOperators(Date & d1){
	cout<<"==================================================================="<<endl;
	cout<<"Testing Unary Arithmetic Operators true statements will be printed"<<endl<<endl;
	try{
			cout<<"++"<<d1<<" is "<<(++d1)<<endl;
			--d1;
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error- "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range- "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
	try{
			cout<<"--"<<d1<<" is "<<(--d1)<<endl;
			++d1;
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error- "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range- "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
	try{
			cout<<d1<<"++"<<" is "<<(d1++)<<endl;
			d1--;
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error- "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range- "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
	try{
			cout<<d1<<"--"<<" is "<<(d1--)<<endl;
			d1++;
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error- "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range- "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknow Exception"<<endl;
		}
	cout<<endl;
}
void testAddNumberOfDays(Date & d1, int days){
	cout<<"==============================================================="<<endl;
	cout<<"Testing Adding Number Of Days true statements will be printed"<<endl<<endl;
	try{
		cout<<d1<<" + "<<days<<" is "<<(d1+days)<<endl;
	}
	catch(invalid_argument e){
			cout<<endl<<"***ERROR\tinvalid_argument- "<<e.what()<<endl;

	}
	catch(domain_error e){
			cout<<endl<<"***ERROR\tdomain_error- "<<e.what()<<endl;
	}
	catch(out_of_range e){
			cout<<endl<<"***ERROR\tout_of_range- "<<e.what()<<endl;
	}
	catch(exception e){
			cout<<endl<<"***ERROR\tUnknow Exception"<<endl;
	}
	cout<<endl;
}
void testDifferenceOperator(Date & d1,Date & d2){
	cout<<"============================================================="<<endl;
	cout<<"Testing Difference in days true statements will be printed"<<endl<<endl;
	cout<<d1<<" - "<<d2<<" is "<<(d1-d2)<<endl;
	cout<<d2<<" - "<<d1<<" is "<<(d2-d1)<<endl;
	cout<<endl;
}
void testLeapYear(Date & d1){
	cout<<"============================================================"<<endl;
	cout<<"Testing LeapYear Function true statements will be printed"<<endl<<endl;
	if(d1.leapYear()){
		cout<<d1<<" is a leap year"<<endl;
	}else{
		cout<<d1<<" is not a leap year"<<endl;
	}
	cout<<endl;
}
void testCastOperators(Date & d1){
	cout<<"=========================================================="<<endl;
	cout<<"Testing Cast Operators true statements will be printed"<<endl<<endl;
	cout<<d1<<" as   WeekNumber  is "<<static_cast<WeekNumber>(d1)<<endl;
	cout<<d1<<" as   Month       is "<<static_cast<Month>(d1)<<endl;
	cout<<d1<<" as   WeekDay     is "<<static_cast<WeekDay>(d1)<<endl;
	cout<<endl;
}
void testRelationalOperators(Date & d1 , Date & d2){
	cout<<"======================================================================="<<endl;
	cout<<"Checking Relational Operators All The True Statements will be printed"<<endl<<endl;
	if(d1==d2){
		cout<<d1<<" is == to "<<d2<<endl;
	}
	if(d1!=d2){
		cout<<d1<<" is != to "<<d2<<endl;	
	}
	if(d1<d2){
		cout<<d1<<" is < than "<<d2<<endl;
	}
	if(d1<=d2){
		cout<<d1<<" is <= than "<<d2<<endl;
	}
	if(d1>d2){
		cout<<d1<<" is > than "<<d2<<endl;
	}
	if(d1>=d2){
		cout<<d1<<" is >= than "<<d2<<endl;
	}
	cout<<endl;
}
void testSetAndGetFormat(){
	cout<<"======================================================================="<<endl;
	cout<<"Checking Set And Get Format All The True Statements will be printed"<<endl<<endl;
	DateFormat f;
	Date::setFormat(f);
	Date d;

	cout<<"Initially the default format dd-mmm-yy is set  using setFormat"<<endl;
	cout<<"The output in this format is "<<d<<endl;
	f=DateFormat("dd-mm-yyyy");
	Date::setFormat(f);
	DateFormat f2=Date::getFormat();
	Date::setFormat(f2);
	cout<<"Set the format in dd-mm-yyyy . Using getFormat to get the format and set the format received by it "<<endl;
	cout<<"The output in this format is "<<d<<endl;
	cout<<"Set and Get Format Are Working Correctly"<<endl<<endl;

}
void testOStream(){
	cout<<"================================================================"<<endl;
	cout<<"Checking  Ostream Function Printing in all available formats"<<endl<<endl;
	DateFormat f("dd-mm-yyyy");
	Date::setFormat(f);
	Date d("27-07-2016");
	const char*  day[]={NULL,"d","dd"};
	const char*  month[]={NULL,"m","mm","mmm"};
	const char* year[]={NULL,"yy","yyyy"};
	for(int i=0;i<3;++i){
		for(int j=0;j<4;++j){
			for(int k=0;k<3;++k){
				DateFormat f1(day[i],month[j],year[k]);
				Date::setFormat(f1);
				cout<<"27-07-2016 in format \t"<<((day[i]!=NULL)?day[i]:"NULL")<<"\t"<<((month[j]!=NULL)?month[j]:"NULL")<<"\t"<<((year[k]!=NULL)?year[k]:"NULL")<<"    \t\tis\t    \t"<<d<<endl;
			}
		}
	}
	cout<<endl;
}
void testIstream(){
	cout<<"===================================================================================="<<endl;
	cout<<"Istream calls Date constructor so it is already tested so checking for only 1 input"<<endl;
	cout<<"Checking  Istream Function with input format dd-mm-yyyy"<<endl<<endl;
	stringstream s;
	s<<"27-03-2016"<<endl;
	DateFormat format("dd-mm-yyyy");
	Date::setFormat(format);
	Date d;
	cout<<"Originally date is "<<d<<endl;
	s>>d;
	cout<<"After taking in 27-03-2016 through stringstream date is "<<d<<endl;
	cout<<"===================================================================================="<<endl;
}
void testDate(int &flag){
	switch(flag){
		case 1:{
			testDateFormatConstructor();
			break;
		}
		case 2:{
			testDateConstructor();
			break;
		}
		case 3:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("27-07-2016");
			Date d2("26-02-1955");
			testCopyAssignment(d1,d2);
			break;
		}
		case 4:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("01-01-1950");
			Date d2("31-12-2049");
			Date d3("27-03-2016");
			testUnaryArithmeticOperators(d1);
			testUnaryArithmeticOperators(d2);
			break;
		}
		case 5:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("03-01-1950");
			Date d2("27-07-2016");
			Date d3("29-12-2049");
			testAddNumberOfDays(d1,5);
			testAddNumberOfDays(d1,-5);
			testAddNumberOfDays(d2,5);
			testAddNumberOfDays(d2,-5);
			testAddNumberOfDays(d3,5);
			testAddNumberOfDays(d3,-5);
			break;
		}
		case 6:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("06-08-1995");
			Date d2("27-07-2016");
			testDifferenceOperator(d1,d2);
			break;
		}
		
		case 7:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("03-01-2013");
			Date d2("27-07-2012");
			testLeapYear(d1);
			testLeapYear(d2);
			break;
		}
		case 8:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("27-07-2016");
			testCastOperators(d1);
			break;
		}
		case 9:{
			DateFormat f("dd-mm-yyyy");
			Date::setFormat(f);
			Date d1("03-01-2013");
			Date d2("27-07-2012");
			Date d3("26-05-2012");
			Date d4("27-07-2012");
			testRelationalOperators(d2,d1);
			testRelationalOperators(d2,d3);
			testRelationalOperators(d2,d4);
			break;
		}
		case 10:{
			testSetAndGetFormat();
			break;
		}
		case 11:{
			testOStream();
			break;
		}
		case 12:{
			testIstream();
			break;	
		}
	}
}
int main(){
	int flag=0;
	while(flag!=13){
		try{
			++flag;
			testDate(flag);
		} 
		catch(invalid_argument e){
			cout<<"***ERROR invalid_argument- "<<e.what()<<endl;

		}
		catch(domain_error e){
			cout<<"***ERROR domain_error- "<<e.what()<<endl;
		}
		catch(out_of_range e){
			cout<<"***ERROR out_of_range- "<<e.what()<<endl;
		}
		catch(exception e){
			cout<<"***ERROR Unknown Exception"<<endl;
		}
	}
	return 0;
}