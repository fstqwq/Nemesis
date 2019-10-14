int gregorian(int year,int month,int day){
  if(month<=2)month+=12,year--;
  return (day+13*(month+1)/5+
          year+year/4-year/100+year/400+6)%7; }
int julian(int year, int month, int day) {
  if(month<=2)month+=12,year--;
  return (day+13*(month+1)/5+year+year/4+4)%7; }
