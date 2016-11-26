#include "Date.h"
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <cctype>

DateFormat Date::format;

bool isLeapYear(int year){						//to check leap year
	return (year%4==0 && (year%100!=0 || year%400==0));
}

int getLeapYearsPassed(int month,int year){  //counts the number of leap Years passed from 00/00/0000
	if (month <= 2)
        year--;
    return  year / 4 - year / 100 + year / 400;
}

long long int getNumberDaysPassed(int date,int month,int year){   //counts the number of leap Years passed from 00/00/0000
	int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
	long long int n1 = (static_cast<long long int>(year))*365 + date;
    for (int i=0; i<month - 1; i++){
        n1 += monthDays[i];
    }
    n1 += getLeapYearsPassed(month,year);
 	return n1;
}
void addDays(int numDays,int &day,int & month,int &year){	//adds number of days from the starting of the year 
	int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
	bool flag=isLeapYear(year) && year!=0;
	for(int i=0;i<12;++i){
		int numMonthDay=monthDays[i];
		if(i==1&&flag) numMonthDay=29;
		if(numDays>numMonthDay){
			numDays-=numMonthDay;
		}else{
			month=i+1;
			day=numDays;
			return;
		}
	}
}
void getInverseDate(long long int numDays,int & day,int & month,int & year){		//generates date from number of days passed from 00/00/0000
	int tempYear=numDays/365;
	numDays%=365;
	int numLeapYears= getLeapYearsPassed(1,tempYear);
	numDays-=numLeapYears;
	while(numDays<0){
		while(numDays<=0){
			numDays+=365;
			if(isLeapYear(tempYear-1)&&tempYear!=1) numDays+=1;
			--tempYear;
		}
		// if(isLeapYear(tempYear)&&tempYear!=0&&numDays<=366){
		// 	year=tempYear;
		// 	addDays(numDays,day,month,year);
		// 	return;
		// }
		// while(numDays>=365){
		// 	numDays-=365;
		// 	if(isLeapYear(tempYear)&&tempYear!=0) numDays-=1;
		// 	++tempYear;
		// }
		// year=tempYear;
		// month=12;
		// day=31;
		// if(numDays==0){
		// 	year--;
		// 	return;
		// }
	} 
	year=tempYear;
	addDays(numDays,day,month,year);
}					

bool isInRange(int day,int month,int year){  //to check if a given date is in the range specified 1 jan 1950- 31 dec 2049
	const int maxYear=2049;
    const int maxMonth=12;
    const int  maxDay=31;
    const int minYear=1950;
    const int minMonth=1;
    const int minDay=1;
	
	if(year<minYear||year>maxYear){
		return false;
	}
	if(year==minYear){
		if(month<minMonth){
			return false;
		}
		if(month==minMonth){
			if(day<minDay){
				return false;
			}
		}
	}
	if(year==maxYear){
		if(month>maxMonth){
			return false;
		}
		if(month>maxMonth){
			if(day>maxDay){
				return false;
			}
		}
	}
	return true;
}

bool isDateValid(int day,int month,int year){   //to check if the given triplet day month year is valid as a triplet
	int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
	bool flag=isLeapYear(year) ;
	int numMonthDay=monthDays[month-1];
	if(flag && month==2) numMonthDay=29;
	if(day<1||day>numMonthDay){
		return false;
	}
	return true;
}

int getDay(const char * day,const char * dayFormat){
	if(strlen(day)==0){
		throw  invalid_argument("Invalid C-String");	
	}
	int num=0;
	if(strcmp(dayFormat,"d")==0){
		if(day[0]=='0'){
			throw invalid_argument("Wrong Day Input Format");
		}
		for(int i=0;day[i]!='\0';++i){
			if(isdigit(day[i])){
				num*=10;
				num+=day[i]-'0';
			}else{
				throw invalid_argument("Wrong Day Input Type");
			}
		}
	}else if(strcmp(dayFormat,"dd")==0){
		for(int i=0;day[i]!='\0';++i){
			if(isdigit(day[i])){
				num*=10;
				num+=day[i]-'0';
			}else{
				throw invalid_argument("Wrong Day Input Type");
			}
		}
	}
	if(num<=0||num>31){
		throw invalid_argument("Invalid Day Input");
	}
	return num;
}
int getMonth(const char * month, const char * monthFormat){  //to get the month from const char * according to the given format 
	if(strlen(month)==0){
		throw  invalid_argument("Invalid C-String");
	}
	int num=0;
	if(strcmp(monthFormat,"m")==0){
		if(month[0]=='0'){
			throw invalid_argument("Wrong Month Input Format");
		}
		for(int i=0;month[i]!='\0';++i){
			if(isdigit(month[i])){
				num*=10;
				num+=month[i]-'0';
			}else{
				throw invalid_argument("Wrong Month Input Type");
			}
		}
	}else if(strcmp(monthFormat,"mm")==0){
		for(int i=0;month[i]!='\0';++i){
			if(isdigit(month[i])){
				num*=10;
				num+=month[i]-'0';
			}else{
				throw invalid_argument("Wrong Month Input Type");
			}
		}
	}
	if(num<=0||num>12){
		throw invalid_argument("Invalid Month Input");
	}
	return num;
}
int getYear(const char * year,const char * yearFormat){  // to generate year from const char * according to the given year format 
	if(strlen(year)==0){
		throw  invalid_argument("Invalid C-String");
	}
	int num=0;
	if(strcmp(yearFormat,"yy")==0){
		for(int i=0;year[i]!='\0';++i){
			if(isdigit(year[i])){
				num*=10;
				num+=year[i]-'0';
			}else{
				throw invalid_argument("Wrong Year Input Type");
			}
		}
		if(num>=50&&num<=99){
			num+=1900;
		}else if(num>=0&&num<=49){
			num+=2000;
		}else{
			throw invalid_argument("Wrong Year Format Type");
		}

	}else if(strcmp(yearFormat,"yyyy")==0){
		for(int i=0;year[i]!='\0';++i){
			if(isdigit(year[i])){
				num*=10;
				num+=year[i]-'0';
			}else{
				throw invalid_argument("Wrong Year Input Type");
			}
		}
	}
	return num;
}

DateFormat::DateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat){  // Date format constructor takes in const chr * for date month and year constructor  

	if(dateFormat==NULL){
		this->dateFormat=NULL;
	}else{
		if(strcmp(dateFormat,"d")==0 || strcmp(dateFormat,"dd")==0){
			this->dateFormat=new char[strlen(dateFormat)+1];
			strcpy(this->dateFormat,dateFormat);	
		}else{
			throw invalid_argument("Invalid argument type");
		}
	}
	if(monthFormat==NULL){
		this->monthFormat=NULL;
	}else {
		if(strcmp(monthFormat,"m")==0 || strcmp(monthFormat,"mm")==0 || strcmp(monthFormat,"mmm")==0){
			this->monthFormat=new char[strlen(monthFormat)+1];
			strcpy(this->monthFormat,monthFormat);	
		}else{
			throw invalid_argument("Invalid argument type");
		}
	}
	if(yearFormat==NULL){
		this->yearFormat=NULL;
	}else{
		if(strcmp(yearFormat,"yy")==0 || strcmp(yearFormat,"yyyy")==0){
			this->yearFormat=new char[strlen(yearFormat)+1];
			strcpy(this->yearFormat,yearFormat);
		}else{
			throw invalid_argument("Invalid argument type");	
		}
	}
}
DateFormat::DateFormat(const char* format){  //Date Format Constructor that takes in const char * for the whole format as dd-mm-yyyy
	if(format==NULL){
		throw invalid_argument("Invalid argument type");	
	}
	int length=strlen(format);
	int dateLength=-1;
	int monthLength=-1;
	for(int i=0;format[i]!='\0';++i){
		if(format[i]=='-'){
			dateLength=i;
			break;
		}
		if(format[i]!='d'){
			throw invalid_argument("Invalid argument type");
		}
	}
	for(int i=dateLength+1;format[i]!='\0';++i){
		if(format[i]=='-'){
			monthLength=i;
			break;
		}
		if(format[i]!='m'){
			throw invalid_argument("Invalid argument type");
		}
	}
	for(int i=monthLength+1;format[i]!='\0';++i){
		if(format[i]!='y'){
			throw invalid_argument("Invalid argument type");	
		}
	}
	if( (dateLength!=0 && dateLength!=1 && dateLength!=2) || dateLength==-1 ){
		throw invalid_argument("Invalid argument type");	
	}
	if( ( (monthLength-dateLength-1)!=0 && (monthLength-dateLength-1)!=1 && (monthLength-dateLength-1)!=2 && (monthLength-dateLength-1)!=3 )|| monthLength==-1){
		throw invalid_argument("Invalid argument type");		
	}
	if( (length-monthLength-1)!=0 && (length-monthLength-1)!=2 && (length-monthLength-1)!=4){
		throw invalid_argument("Invalid argument type");	
	}
	if(dateLength==0){
		this->dateFormat=NULL;
	}else{
		this->dateFormat=new char[dateLength+1];
		for(int i=0;i<dateLength;++i){
			(this->dateFormat)[i]='d';
		}
		(this->dateFormat)[dateLength]='\0';
	}
	if(monthLength-dateLength-1==0){
		this->monthFormat=NULL;
	}else{
		this->monthFormat=new char[monthLength-dateLength];
		for(int i=0;i<monthLength-dateLength-1;++i){
			(this->monthFormat)[i]='m';
		}
		(this->monthFormat)[monthLength-dateLength-1]='\0';
	}
	if(length-monthLength-1==0){
		this->yearFormat=NULL;
	}else{
		this->yearFormat=new char[length-monthLength];
		for(int i=0;i<length-monthLength-1;++i){
			(this->yearFormat)[i]='y';
		}
		(this->yearFormat)[length-monthLength-1]='\0';
	}
}


DateFormat::DateFormat(){						//Date Format Default Constructor as dd-mmm-yy
	dateFormat=new char[strlen("dd")+1];
	strcpy(dateFormat,"dd");
	monthFormat=new char[strlen("mmm")+1];
	strcpy(monthFormat,"mmm");
	yearFormat=new char[strlen("yy")+1];
	strcpy(yearFormat,"yy");
}  

DateFormat& DateFormat::operator=(const DateFormat& newFormat){  //DateFormat copy assignment operator 
	if(this->dateFormat!=NULL) delete[] this->dateFormat;
	if(this->monthFormat!=NULL) delete[] this->monthFormat;
	if(this->yearFormat!=NULL) delete[] this->yearFormat;
	if(newFormat.dateFormat==NULL){
		this->dateFormat=NULL;
	}else{
		this->dateFormat=new char[strlen(newFormat.dateFormat)+1];
		strcpy(this->dateFormat,newFormat.dateFormat);
	}
	if(newFormat.monthFormat==NULL){
		this->monthFormat=NULL;
	}else{
		this->monthFormat=new char[strlen(newFormat.monthFormat)+1];
		strcpy(this->monthFormat,newFormat.monthFormat);
	}
	if(newFormat.yearFormat==NULL){
		this->yearFormat=NULL;
	}else{
		this->yearFormat=new char[strlen(newFormat.yearFormat)+1];
		strcpy(this->yearFormat,newFormat.yearFormat);
	}
	return (*this);
}
DateFormat::DateFormat(const DateFormat& newFormat){
	if(newFormat.dateFormat==NULL){
		this->dateFormat=NULL;
	}else{
		this->dateFormat=new char[strlen(newFormat.dateFormat)+1];
		strcpy(this->dateFormat,newFormat.dateFormat);
	}
	if(newFormat.monthFormat==NULL){
		this->monthFormat=NULL;
	}else{
		this->monthFormat=new char[strlen(newFormat.monthFormat)+1];
		strcpy(this->monthFormat,newFormat.monthFormat);
	}
	if(newFormat.yearFormat==NULL){
		this->yearFormat=NULL;
	}else{
		this->yearFormat=new char[strlen(newFormat.yearFormat)+1];
		strcpy(this->yearFormat,newFormat.yearFormat);
	}
}
DateFormat::~DateFormat(){   					//Date Format destructor
	if(dateFormat!=NULL) delete [] dateFormat;
	if(monthFormat!=NULL) delete [] monthFormat;
	if(yearFormat!=NULL) delete [] yearFormat;
}

Date::Date(Day d, Month m, Year y) throw(invalid_argument, domain_error, out_of_range){               // Construct a Date from (d, m, y)
	int day=d,month=m,year=y;

	if(!isDateValid(day,month,year)){
		string s="Not a Valid Date:";
		s=s+to_string(day)+"-"+to_string(month)+"-"+to_string(year)+"";
		throw domain_error(s);
	}
	if(!isInRange(d,m,y)){
		string s="Date Not in Range:";
		s=s+to_string(day)+"-"+to_string(month)+"-"+to_string(year)+"";
		throw out_of_range(s);
	}

	this->year=static_cast<Year>(year);
    this->month=static_cast<Month>(month);
    this->day=static_cast<Day>(day);
}              

Date::Date(const char* date)    throw(invalid_argument, domain_error, out_of_range){  // date in string format -- to be parsed as static format member
	if(date==NULL){
		throw invalid_argument("Invalid C-String");
	}
	if( (this->getDateFormat()) ==NULL || (this->getMonthFormat()) ==NULL || strcmp(this->getMonthFormat(),"mmm")==0 || (this->getYearFormat()) ==NULL){
		throw invalid_argument("Invalid Date Format For Input");
	}
	//cout<<date<<" "<<this->getDateFormat()<<" "<<this->getMonthFormat()<<" "<<getYearFormat()<<endl;
	int length=strlen(date);
    int dateLength=-1;
    int monthLength=-1;        
    for(int i=0;date[i]!='\0';++i){
    	if(date[i]=='-'){
    		dateLength=i;
    		break;
    	}
    }
   
    for(int i=dateLength+1;date[i]!='\0';++i){
    	if(date[i]=='-'){
    		monthLength=i;
    		break;
    	}
    }

    if(dateLength==-1  || monthLength==-1 ){
    	throw invalid_argument("Invalid C-String");	
    }

    char day[dateLength+1];
    for(int i=0;i<dateLength;++i){
    	day[i]=date[i];
    }
    day[dateLength]='\0';
    char month[monthLength-dateLength];
    for(int i=dateLength+1;i<monthLength;++i){
    	month[i-dateLength-1]=date[i];
    }
    month[monthLength-dateLength-1]='\0';
    char year[length-monthLength];
    for(int i=monthLength+1;i<length;++i){
    	year[i-monthLength-1]=date[i];
    }
    year[length-monthLength-1]='\0';
   // cout<<dateLength<<" "<<monthLength<<" "<<length<<" "<<day<<" "<<month<<" "<<year<<" "<<this->getDateFormat()<<" "<<this->getMonthFormat()<<" "<<this->getYearFormat()<<endl; //debuggin
   	Day d=static_cast<Day>(getDay(day,this->getDateFormat()));	
    Month m=static_cast<Month>(getMonth(month,this->getMonthFormat()));
    Year y=static_cast<Year>(getYear(year,this->getYearFormat()));
    if(!isDateValid(d,m,y)){
    	throw domain_error("Invalid Date No Such Date Exists");
    }
    if(!isInRange(d,m,y)){
    	throw out_of_range("Date not in Range");
    }
    this->day=d;
    this->month=m;
    this->year=y;
}

Date::Date() throw(domain_error, out_of_range){					//default constructor
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int day=now->tm_mday;
    int month=now->tm_mon + 1;
    int year=now->tm_year + 1900;
    if(!isInRange(day,month,year)){
    	throw out_of_range("Current Date Out Of Range");
    }
    this->year=static_cast<Year>(year);
    this->month=static_cast<Month>(month);
    this->day=static_cast<Day>(day);
}
void Date::setFormat(DateFormat& newFormat){     //To set date format
	format=newFormat;
}

const DateFormat& Date::getFormat(){			//to get the date format
	return format;		
}

Date::Date(const Date& otherDate):year(otherDate.year),month(otherDate.month),day(otherDate.day) {}  //copy constructor

Date::~Date(){}   //Date class destructor 

Date& Date::operator++(){   //returns the next day
	*this=(*this)+1;
	return (*this);
}

const Date Date::operator++(int){
	Date temp=*this;
	*this=(*this)+7;
	return temp;
}
Date& Date::operator--(){
	*this=(*this)+(-1);
	return (*this);
}
const Date Date::operator--(int){
	Date temp=*this;
	*this=(*this)+(-7);
	return temp;
}
Date& Date::operator=(const Date& otherDate){  //copy assignment for date class
	if( this!= &otherDate ){
		this->year=otherDate.year;
		this->month=otherDate.month;
		this->day=otherDate.day;
	}
	return (*this);
}
unsigned int Date::operator-(const Date& otherDate){   //gets number of days between two dates by calculating number of days passed since 00/00/0000
	long long int daysPassed_currDate=getNumberDaysPassed(this->day,this->month,this->year);
	long long int daysPassed_otherDate=getNumberDaysPassed(otherDate.day,otherDate.month,otherDate.year);
	long long int daysPassed=daysPassed_currDate-daysPassed_otherDate;
	if(daysPassed<0){
		daysPassed*=-1;
	}
	return (static_cast<unsigned int>(daysPassed));
}

Date Date::operator+(int noOfDays) throw(domain_error, out_of_range){  // adds number of days to the given date the number of days can be positive or negative 
	int thisYear=this->year, thisMonth=this->month, thisDay=this->day;
	long long int numDaysPassed=getNumberDaysPassed(thisDay,thisMonth,thisYear);
	
	numDaysPassed+=noOfDays;

	if(numDaysPassed<0){
		throw out_of_range("The Result is Out Of Range");
	}
	
	int day,month,year;
	getInverseDate(numDaysPassed,day,month,year);
	if(!isInRange(day,month,year)){
		throw out_of_range("The Result is Out Of Range");	
	}

	Year newYear=static_cast<Year>(year);
	Month newMonth=static_cast<Month>(month);
	Day newDay=static_cast<Day>(day);
	Date newDate(newDay,newMonth,newYear);
	return newDate;
}

Date::operator WeekNumber() const{  // casts the Date in WeekNumber accordign to ISO 8601 defination 
	Day d=D04;
	Month m=Jan;
	Year y=this->year;
	Date firstMonday(d,m,y);
	while(static_cast<int>(WeekDay(firstMonday))!=1){
		--firstMonday;
	}
	if(firstMonday>(*this)){
		Date temp(d,m,y-1);
		firstMonday=temp;
		while(static_cast<int>(WeekDay(firstMonday))!=1){
			--firstMonday;
		}
	}
	int days=firstMonday-(*this);
	days=days/7+1;
	return (static_cast<WeekNumber>(days));
}

Date::operator Month() const{  //casts to Month
	return (this->month) ;
} 

Date::operator WeekDay() const{     //casts the date into WeekDay
	int currYear=this->year;
	int currMonth=this->month;
	int currDay=this->day;

	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    currYear -= currMonth < 3;
    int  tempWeekDay =( currYear + currYear/4 - currYear/100 + currYear/400 + t[currMonth-1] + currDay) % 7;

	if(tempWeekDay==0) tempWeekDay=7;
	WeekDay currWeekDay=static_cast<WeekDay>(tempWeekDay);
	return currWeekDay;
}

bool Date::leapYear() const{     //returns if  Year is a leap year
	int thisYear=this->year;
	return isLeapYear(thisYear);
}

bool Date::operator==(const Date& otherDate){    //if current Date is equal to other date  ** main function rest are derived
	int thisYear=this->year, thisMonth=this->month, thisDay=this->day;
	int otherYear=otherDate.year, otherMonth=otherDate.month, otherDay=otherDate.day;
	return ( thisYear==otherYear && thisMonth==otherMonth && thisDay==otherDay);
}

bool Date::operator!=(const Date& otherDate){    //if current date is not equal than other date
	return ( !((*this)==otherDate) );	
}

bool Date::operator<(const Date& otherDate){	//if current date is less than other date  **main function rest are derived
	int thisYear=this->year, thisMonth=this->month, thisDay=this->day;
	int otherYear=otherDate.year, otherMonth=otherDate.month, otherDay=otherDate.day;
	if(thisYear < otherYear){
		return true;
	}		
	if(thisYear==otherYear){
		if(thisMonth<otherMonth){
			return true;
		}
		if(thisMonth==otherMonth){
			if(thisDay<otherDay){
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

bool Date::operator<=(const Date& otherDate){  //if current date is less than equal to other date
	return ( (*this)<otherDate || (*this)==otherDate );
}

bool Date::operator>(const Date& otherDate){	//if current date is greater than other date
	return ( !( (*this)<= otherDate ) );
}

bool Date::operator>=(const Date& otherDate){	//if current date is greater than equal to other date
	return ( (*this)>otherDate || (*this)==otherDate );
}

ostream& operator<<(ostream& os, const Date& currDate){  //ostream operator for Date class that outputs in the set Date Format 
	const char * dateFormat=currDate.getDateFormat();
	const char * monthFormat=currDate.getMonthFormat();
	const char * yearFormat=currDate.getYearFormat();
	string monthName[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	int currYear=currDate.year, currMonth=currDate.month, currDay=currDate.day;
	
	if(dateFormat!=NULL){
		if(strcmp(dateFormat,"d")==0){
			os<<currDay<<"-";
		}else if(strcmp(dateFormat,"dd")==0){
			if(currDay<10){
				os<<"0";
			}
			os<<currDay<<"-";
		}
	}
	if(monthFormat==NULL){
		os<<monthName[currMonth-1];
	}else{
		if(strcmp(monthFormat,"m")==0){
			os<<currMonth;
		}else if(strcmp(monthFormat,"mm")==0){
			if(currMonth<10){
				os<<"0";
			}
			os<<currMonth;
		}else if(strcmp(monthFormat,"mmm")==0){
			os<<monthName[currMonth-1][0]<<monthName[currMonth-1][1]<<monthName[currMonth-1][2];
		}
	}
	if(yearFormat!=NULL){
		os<<"-";
		if(strcmp(yearFormat,"yy")==0){
			if(currYear%100<10){
				os<<"0";
			}
			os<<currYear%100;
		}else if(strcmp(yearFormat,"yyyy")==0){
			if(currYear<1000){
				os<<"0";
			}
			if(currYear<100){
				os<<"0";
			}
			if(currYear<10){
				os<<"0";
			}
			os<<currYear;
		}
	}
	return os;
}
istream& operator>>(istream& is, Date& currDate){  //istream operator for Date class 
		string s;
		is>>s;
		Date temp(s.c_str());
		currDate=temp;
		return is;
}