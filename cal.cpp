#include<iostream>
#include<sstream>
#include<cmath>
#define pi 3.14159265
#define deg(x) (x*pi)/180//allow easy conversion of number for deg
#define adeg(x) (x*180)/pi//allows easy conversion of result to arcsin for deg
//****************************************Lowercase**************************************************
void lowercase(std::string &word){
  
  for(int x=0;x<word.length();x++){
  if(word[x]>='A'&&word[x]<='Z')
  word[x]+=32;
  
  }
}
//****************************************convert_float && convert_str**************************************************
float convert_float(std::string &value){//converts string to float
float val;
std::stringstream convrt;
convrt<<value;
convrt>>val;
return val;
}
std::string convert_str(float &value){//converts float to string
std::string val;
std::stringstream convrt;
convrt<<value;
convrt>>val;
return val;
}
//****************************************check**************************************************
bool check(std::string equation){
  //std::cout<<"checking......"<<std::endl;
  int rep,close_b=0,open_b=0,point=0;
  char sign;
  std::string temp;
  for(int x=0;x<equation.length();x++){
    if(equation[x]>='0'&&equation[x]<='9'){//to prevent numbers from prompting errors
      if(equation[x]=='0'&&equation[x-1]=='-'&&x!=0)//if -0 is entered returns true for error
      return 1;
      
    }
    
    else if(equation[x]=='+'||equation[x]=='-'||equation[x]=='/'||equation[x]=='^'||equation[x]=='*'||equation[x]=='('||equation[x]==')'||equation[x]=='.'){
      sign=equation[x];
      if(sign=='.'&&point==0){//point ==0 makes sure if runs only once
        for(int rep=0;rep<equation.length();rep++){
          if(equation[rep]=='.'){
            if(point>=1)//if multiple points before a sign returns true foe error
            return 1;
          point++;
          }
          else if(equation[rep]<'0'||equation[rep]>'9')//once sign is seen resets the point
          point=0;
        }
      }
      else if(sign=='+'){
      for(rep=x;equation[rep]=='+';rep++);
      if(rep-x>2)//if sign repeats three times in a row returns true for error
      return 1;
      rep--;
      x=rep;
      
      }
      else if(sign=='-'){
      for(rep=x;equation[rep]=='-';rep++);
      if(rep-x>2)//if sign repeats three times in a row returns true for error
      return 1;
      rep--;
      x=rep;
      
      }
      else if(sign=='*'){
      for(rep=x;equation[rep]=='*';rep++);
      if(rep-x>1)//if sign repeats twice in a row returns true for error
      return 1;
      rep--;
      x=rep;
      }
      else if(sign=='/'){
      for(rep=x;equation[rep]=='/';rep++);
      if(rep-x>1)//if sign repeats twice in a row returns true for error
      return 1;
      rep--;
      x=rep;
      
      }
      else if(sign=='^'){
      for(rep=x;equation[rep]=='^';rep++);
      if(rep-x>1)//if sign repeats twice in a row returns true for error
      return 1;
      rep--;
      x=rep;
      
      }
      else if(open_b==0&&close_b==0&&(sign=='('||sign==')')){//open_b && close_b makes sure this if runs only once 
        for(rep=0;rep<equation.length();rep++){//loop to identify how many open and close bracket
        if(equation[rep]==')')
        open_b++;
        else if(equation[rep]=='('){
        close_b++;
        if(equation[rep+1]==')')//returns true for error if bracket is empty
        return 1;
        }
        }
        if(open_b!=close_b)//if they are not equal returns true for error
        return 1;
      }
      
    }
    
    else if(equation[x]=='a'||equation[x]=='c'||equation[x]=='s'||equation[x]=='t'){//checks for first character
    for(rep=x;equation[rep]!='('&&equation[rep]<'0'||equation[rep]>'9';rep++)//loop runs through all characters till a number is reached 
    //also to make sure nothing like sin+3 is inputed but allows sin(90)
      temp+=equation[rep];
      
      if(temp!="arcsin"&&temp!="arccos"&&temp!="arctan"&&temp!="sin"&&temp!="cos"&&temp!="tan")//if diesnt equal any returns true for error
      return 1;
      rep--;
      x=rep;//makes the main loop continue from the second to last character cause of iteration at end of main loop 
      temp="";//empties temp
    }
    else//if what is entered is non of the above return true for error
    {
      return 1;
    }
    
  }
  return 0;//if main loop reaches end then returns false foe error
}
//****************************************rev**************************************************
std::string rev(std::string &word){
  std::string rev_str;
  for(int count=word.length()-1;count>=0;count--)
  rev_str+=word[count];
  return rev_str;
}
//****************************************scientific**************************************************
std::string scientific(std::string special,std::string num,std::string angle){//passes e.g (sin,90,deg)
  float result;
  result=convert_float(num);
  if(special[0]=='a'){
    if(special=="arctan")
    result=atan(result);
    
    else if(special=="arcsin")
    result=asin(result);
    
    else if(special=="arccos")
    result=acos(result);

    if(angle=="deg")
    result=adeg(result);
  }
  else{
  if(angle=="deg")
  result=deg(result);
    if(special=="sin")
    result=sin(result);
    else if(special=="cos")
    result=cos(result);
    else if(special=="tan")
    result=atan(result);
  }
  special=convert_str(result);
    return special;
}

//************************************* solu function begins here*************************************
std::string solu(std::string equation){
  std::string temp;
  float result,temp_float;
  equation=" "+equation;
  /*
  adds a space to equation to allow
  when calculations are done to move loop backwards to re-read values so index will never
  be 0zoom_amd64.debmp;
float temp_float,result;
/*
################################################|logic of the solu function|###########################################
a sereies of loops starting from exponential(^) -> division(/) -> multiplication(*)-> addition(+) -> subtraction(-) 
in this order each sign will be solved then equation string is edited with answer then passed to the next loop till all 
loops have been completed
structur of loops from '^' to '+' are similar with slight expection of '-'

*/

//************************************* solving for exponential *************************************

//assuming equation is 3-2^+2-3 input can as well be -2^2 or -2^-2
for(int x=0;x<equation.length();x++){
  if(equation[x]>='0'&&equation[x]<='9'||equation[x]=='.'){//checks for numbers and (.) before sign
    if(equation[x-1]=='-'){//checks if sign before is negative 
    temp+=equation[x-1];//if so adds it to temp before any numbers
    //temp=-
  }
    temp+=equation[x];//adds all numbers to temp
    //temp=-2
  }

  else if(equation[x]=='^'){
  result=convert_float(temp);//converts number and sign to from string to float for calculation later
  int delete_val=x-1;
  while(equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.'){//deletes all numbers before sign
    equation.erase(equation.begin()+delete_val);
    delete_val--;
  }
  //equation=3-^+2-3

  if(equation[delete_val]=='-'){//if number before sign was negative deletes it as well

  equation.erase(equation.begin()+delete_val);//delete val position after while loop is at sign before '^' if the sign is '-' it will be deleted
}
  //equation=3^+2-3
  else
  delete_val++;//after while loop has deleted values position of delete_val will be at sign before so needs to be incremented by 1 if the sign was not deleted

  equation.erase(equation.begin()+delete_val);//deletes ^ sign
  //equation=3+2-3
  temp="";//temp is emptied
  if(equation[delete_val]=='+'||equation[delete_val]=='-'){
    temp+=equation[delete_val];//adds sign after '^' if sign is '+' || '-' to allow 4++2 1+-2 4*-3 and so on....
    equation.erase(equation.begin()+delete_val);//deletes sign
  }
  //equation=32-3
  for(delete_val;equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.';){
    temp+=equation[delete_val];//gets value of number after sign to temp
      //temp=2
      if(equation[delete_val+1]!='.'&&equation[delete_val+1]<'0'||equation[delete_val+1]>'9')
      //if the next character is not a number loop will break to allow for a position to use to insert result of calculation
      break;
        equation.erase(equation.begin()+delete_val);//deletes number after sign if the condition above is not met
    }
    //equation=32-3
    temp_float=convert_float(temp);//converts number after sign
    if(temp_float>=0)
    result=pow(result,temp_float);
    //result=pow(-2,2)
    else{
      temp_float*=-1;
    result=1/pow(result,temp_float);
  }
    temp=convert_str(result);//converts final result to string to be inserted
    //temp=4
    if(equation[delete_val-1]>='0'&&equation[delete_val]<='9'&&result>=0)
    //if character before the calculation is a number and result is positive add +infront of temp before replaceing value
    //to prevent combining to numbers 4-6/-2 -> 43 rather than 4+3
    //equation='3'2-3 this the character referred to in explanation
    temp='+'+temp;
    //temp=+4
    equation.replace(delete_val,1,temp);
   //equation=3+4-3
    x=delete_val-1;//moves main  loop to before calculation to read new values
    temp="";//empties temp incase next sign is also ^

  }
  else
  temp="";//empties temp if sign is not ^
}

//************************************* solving for division *************************************

for(int x=0;x<equation.length();x++){
  if(equation[x]>='0'&&equation[x]<='9'||equation[x]=='.'){
    if(equation[x-1]=='-'){
    temp+=equation[x-1];
  }
    temp+=equation[x];
  }
  else if(equation[x]=='/'){
  result=convert_float(temp);
  int delete_val=x-1;
  while(equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.'){
    equation.erase(equation.begin()+delete_val);
    delete_val--;
  }
  if(equation[delete_val]=='-')
  equation.erase(equation.begin()+delete_val);
  else
  delete_val++;
  equation.erase(equation.begin()+delete_val);
  temp="";
  if(equation[delete_val]=='+'||equation[delete_val]=='-'){
    temp+=equation[delete_val];
    equation.erase(equation.begin()+delete_val);
  }

  for(delete_val;equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.';delete_val+=0){
    temp+=equation[delete_val];

      if(equation[delete_val+1]!='.'&&equation[delete_val+1]<'0'||equation[delete_val+1]>'9')
      break;
        equation.erase(equation.begin()+delete_val);
    }
    temp_float=convert_float(temp);
    result/=temp_float;
    temp=convert_str(result);
     if(equation[delete_val-1]>='0'&&equation[delete_val]<='9'&&result>=0)
    temp='+'+temp;
    equation.replace(delete_val,1,temp);
    
    x=delete_val-1;
    temp="";

  }
  else
  temp="";
}

//************************************* solving for multiplication *************************************

for(int x=0;x<equation.length();x++){
if(equation[x]>='0'&&equation[x]<='9'||equation[x]=='.'){
  if(equation[x-1]=='-'){
  temp+=equation[x-1];
}
  temp+=equation[x];
}
  else if(equation[x]=='*'){
  result=convert_float(temp);

  int delete_val=x-1;
  while(equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.'){
    equation.erase(equation.begin()+delete_val);
    delete_val--;
  }
  if(equation[delete_val]=='-')
  equation.erase(equation.begin()+delete_val);
  else
  delete_val++;
  equation.erase(equation.begin()+delete_val);
  temp="";
  if(equation[delete_val]=='+'||equation[delete_val]=='-'){
    temp+=equation[delete_val];
    equation.erase(equation.begin()+delete_val);
  }

  for(delete_val;equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.';delete_val+=0){
    temp+=equation[delete_val];

      if(equation[delete_val+1]!='.'&&equation[delete_val+1]<'0'||equation[delete_val+1]>'9')
      break;
        equation.erase(equation.begin()+delete_val);
    }
    temp_float=convert_float(temp);
    result*=temp_float;

    temp=convert_str(result);
     if(equation[delete_val-1]>='0'&&equation[delete_val]<='9'&&result>=0)
    temp='+'+temp;
    equation.replace(delete_val,1,temp);
    
    x=delete_val-1;
    temp="";std::cout<<temp<<std::endl;

  }
  else
  temp="";
}

//************************************* solving for Addition *************************************

for(int x=0;x<equation.length();x++){
  if(equation[x]>='0'&&equation[x]<='9'||equation[x]=='.'){
    if(equation[x-1]=='-'){
    temp+=equation[x-1];
  }
    temp+=equation[x];
  }
  else if(equation[x]=='+'){
  result=convert_float(temp);
  int delete_val=x-1;
  while(equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.'){
    equation.erase(equation.begin()+delete_val);
    delete_val--;
  }
  if(equation[delete_val]=='-')
  equation.erase(equation.begin()+delete_val);
  else
  delete_val++;
  equation.erase(equation.begin()+delete_val);
  temp="";
  if(equation[delete_val]=='+'||equation[delete_val]=='-'){
    temp+=equation[delete_val];
    equation.erase(equation.begin()+delete_val);
  }

  for(delete_val;(equation[delete_val]>='0'&&equation[delete_val]<='9')||equation[delete_val]=='.';delete_val+=0){
    temp+=equation[delete_val];

      if(equation[delete_val+1]!='.'&&equation[delete_val+1]<'0'||equation[delete_val+1]>'9')
      break;
        equation.erase(equation.begin()+delete_val);
    }
    temp_float=convert_float(temp);
    result+=temp_float;
    temp=convert_str(result);
    equation.replace(delete_val,1,temp);
    x=delete_val-1;
    temp="";

  }
  else
  temp="";
}

//************************************* solving for subtraction *************************************

for(int x=0;x<equation.length();x++){
  if(equation[x]>='0'&&equation[x]<='9'||equation[x]=='.'){
    temp+=equation[x];
  }
  
  else if(equation[x]==' '&&equation[x+1]=='-'){//special check for equations like -3-2 ||-3
    temp="";
    temp+=equation[x+1];//passes '-' to temp
    int count=x+2;
    if(equation[count]=='-'){//handles equation like --3 might be erased in next check
      temp="";
      equation.erase(equation.begin()+1);//deletes first '-'
      equation.erase(equation.begin()+1);//deletes second '-'
  //--3-5
    }
    else{
    for(count;equation[count]>='0'&&equation[count]<='9'||equation[count]=='.';count++);//checks to see the position of numbers after '-'
    if(count!=equation.length())//position of numbers is not the end of the equation deletes '-'
    equation.erase(equation.begin()+(x+1));
  //main loop is not changed cause once '-' is deleted string resizes and position will be on numbers
else
    x+=1;//position will be manually incremented by 1 to prevent infinite looping

  }
  }
  else if(equation[x]=='-'){
    
  int delete_val=x-1;
  
    result=convert_float(temp);
   
  while(equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.'){
    equation.erase(equation.begin()+delete_val);
    delete_val--;
}
  temp="";
  delete_val++;
  equation.erase(equation.begin()+delete_val);

  if(equation[delete_val]=='+'||equation[delete_val]=='-'){
    temp+=equation[delete_val];
    equation.erase(equation.begin()+delete_val);
  }

  for(delete_val;equation[delete_val]>='0'&&equation[delete_val]<='9'||equation[delete_val]=='.';delete_val+=0){
    temp+=equation[delete_val];

      if(equation[delete_val+1]!='.'&&equation[delete_val+1]<'0'||equation[delete_val+1]>'9')
      break;
        equation.erase(equation.begin()+delete_val);
    }

    temp_float=convert_float(temp);
      
      if(temp_float>0){
    result-=temp_float;
  }
      else{
        temp_float*=-1;//if number after - is negative converts to positive
      result+=temp_float;

    }
    temp=convert_str(result);
    if(result==0&&delete_val+1!=equation.length()){
    equation.erase(equation.begin()+delete_val);//deletes 0 if not at end of equation
    x=delete_val-2;
    }
    else{
    equation.replace(delete_val,1,temp);
    std::cout<<equation<<std::endl;
    std::cout<<equation[delete_val]<<std::endl;
    if(result>=0)
    x=delete_val-1;//if positive moves main loop to scan the new number
    else
    x=delete_val-2;//moves back to begining to allow the scan the '-' and then delete in earlier else if statement
    }
  temp="";

  }
  else
  temp="";
}

equation.erase(equation.begin());

return equation;
}

//************************************* Main begins here *************************************
int main(){
std::string equation,temp,special,angle,inv;
bool error;
int x;
std::cout<<"Deg or Rad :";
std::cin>>angle;
lowercase(angle);

if(angle!="deg"&&angle!="rad"){
  std::cout<<"Input invalid by default you will be using deg"<<std::endl;
  angle="deg";
}
std::cout<<"Enter Equation :";
std::cin>>equation;
lowercase(equation);//converts uppercase to lower for the sin and remaining cos and so on......
error=check(equation);//sends equation to check function to find errors if error in input returns true
if(error){//error is fount prints error then exits
  std::cout<<"Invalid input try again";
  return 0;
}
for(int count=0;count<equation.length();count++){//loop meant to scan through characters in equation
if(equation[count]==')'){
  
  equation.erase(equation.begin()+count);//erases closing bracket
  count--;
  //int counter;
  for(count;equation[count]!='('&&count>=0;count--){
    temp+=equation[count];
  equation.erase(equation.begin()+count);
}
  temp=rev(temp);

temp=solu(temp);//passes values in bracket to be solved by solu function and returns the solution in string

if(equation[count-1]>='0'&&equation[count-1]<='9')
/*
checks to see if character before opening bracket is a number
if so adds * to allow multiplication
4(-2)->4*-2
*/
temp='*'+temp;
equation.replace(count,1,temp);//uses position of closing bracket and replaces it with value of calculated temp string
temp="";//empties temp variable
}

}

for(int counter=0;counter<equation.length();counter++){
  if(equation[counter]=='s'||equation[counter]=='c'||equation[counter]=='t'||equation[counter]=='a'){
    special+=equation[counter];
    int count;
    for(count=counter+1;equation[count]>='a'&&equation[count]<='z';count++)
    special+=equation[count];
    for(count;equation[count]=='.'||equation[count]>='0'&&equation[count]<='9';count++)
    temp+=equation[count];
    
    if(special=="sin"||special=="cos"||special=="tan"||special=="arcsin"||special=="arccos"||special=="arctan"){
       if(angle=="deg")
      temp=scientific(special,temp,"deg");
      else
      temp=scientific(special,temp,"rad");
      count--;
      for(count;count>counter;count--)
          equation.erase(equation.begin()+count);

     
      equation.replace(count,1,temp);
      temp="";
      special="";
      
    }
    counter++;
  }
  
  
}

equation=solu(equation);//solves the whole equation after all brackets have been solved

std::cout<<"= "<<equation<<std::endl;

//code by Tolulope Fakoya(Toluhunter)
}