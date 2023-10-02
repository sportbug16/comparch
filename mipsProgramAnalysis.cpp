/*########################################################
Note: Please don’t upload the assignments, template file/solution and lab. manual on GitHub or others public repository.
Kindly remove them, if you have uploaded the previous assignments. 
It violates the BITS’s Intellectual Property Rights (IPR).
********************************************************/   
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
int flag=0;
string Instructions[1000];                  //Only instructions are paresed in this array. No comments!!
string DependentInstructionSet[2000][2];    //Dependeny Instructions 2D array
string code[1000];                     //instruction + Labels
string BW_Labels[1000];
string FW_Labels[1000];

int windex=0;
int FwdJump=0, BackJump=0;
int Labels[1000];                           //Label flag bit 0 means its an instruction 1 means it is a label                  
int insCount=0; 
int VALIDINSTR=0;
int dCount=0; // total number of dependencies found
string instructionset[86]={
    "add","addi","addiu","addu","clo","clz","la","li","lui","move","negu","seb","seh","sub","subu", //0-14 arithematic operation 
    "rotr","rotrv","sll","sllv","sra","srav","srl","srlv",                                          //15-22 shift and rotate operations
    "and","andi","ext","ins","nop","nor","not","or","ori","wsbh","xor","xori",                      //23-34 logical and bitwise
    "movn","movz","stl","stli","stliu","stlu",                                                      //35-40 conditional
    "div","divu","madd","maddu","msub","msubu","mul","mult","multu",
    "mfhi","mflo","mthi","mtlo",
    "b","bal","beq","beqz","bgez","bgezal","bgtz","blez","bltz","bltzal","bne","bnez","j","jal","jalr","jr",
    "lb","lbu","lh","lhu","lw","lwl","lwr","sb","sh","sw","swl","swr","ulw","usw",
    "ll","sc" };   
    //41-49 mul/divide
    //50-53 accumulator access op
    //54-69 jump and branch
    //70-83 load and store
    //84-85 atomic read modify write
int TYPE[9]={0};
int TYPERJI[1000];
  string instructionsetRJI[48]={
    "sll","sllv","sra","srav","srl","srlv","jalr","jr",
    "mfhi","mflo","mthi","mtlo","mult","multu",
    "div","divu", "add","addu","sub","subu","and","or",
    "xor","nor","stlu","slt",      // R Type Instruction 0-25
    
    "j","jal",                     // J Type Instruction 26-27
    
    "beq","bne","blez","bgtz","addi","addiu","slti","sltiu",
    "andi","ori","xori","lui","lb","lh","lw","lbu","lhu","sb",
    "sh","sw"                      // I Type Instruction 28-47
    
     };   


string registerSet[32]={
    "zero","at","v0","v1","a0","a1",   //registers set of the architecture
    "a2","a3","t0","t1","t2","t3","t4",
    "t5","t6","t7","t8","t9","s0","s1","s2",
    "s3","s4","s5","s6","s7","k0","k1",
    "gp","sp","fp","ra"};

int countOfReg[32]={0};

void countRegister(); // to count number of register
void printNoReg();    // to print numner of register

int checkTypeRJI(int i);        //return int and checks the type of instruction


string printType(int i); 
void printInstrType();           // function prints all valid instruction

void verifyInstr_setType(string str);      
int checkLine(string line, string *validLine);

void checkDependency();

void printCode();
void countLabels(int , string);
void printJumpLabels();
void printDependentInstr();

int main(int arg,char * str[])
{   

    int tnoi=0;     //total number of instructions
    int typeoi=0;   //types of instructions

    int nloops=0;   //number of loops
    int typeofloop;

    ifstream fin;          //for input file
    ofstream fout;         //output file stream
    cout<<"File Name: \t\t"<<str[1]<<endl;
    fin.open(str[1]);
    string line, validLine;
    int count=0;

    while(fin)              //execute a loop until EOF
    {  
        getline(fin,line);
        if(checkLine(line, &validLine)!=0) //instr in validline
        { 
            code[windex] = validLine;           //code is an array of all valid instr and labels string
            Labels[windex] = 1;               //default as label
             
            verifyInstr_setType(validLine);   //WRITE YOUR CODE for this function
            windex++;
            
            count++;
        }
    }

    printInstrType();
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"Total Lines w/o Comments   =  "<< count<<endl;
    cout<<"Total Valid Instructions   =  "<< insCount<<endl;    
    cout<<"Backward Loops/JUMP        =  "<< BackJump<<endl;
    cout<<"Forward LOOPS/JUMP         =  "<< FwdJump<<endl;

    cout<<"---------------------------------------------------------------"<<endl;
    printJumpLabels();
    countRegister(); //WRITE YOUR CODE FOR this function
    printNoReg();
    checkDependency(); //WRITE YOUR CODE this function
    if(dCount==0) {
        cout<<" No Dependent Instruction !!"<<endl;
    } 
    else{
        printDependentInstr();  //prints the dependent instructions
    } 
    
    return 0;
}


int checkLine(string line, string *validLine)
{
    string opcode, f1,f2,f3;
    string instr;
    int i,start=0;
    bool first= true;
    //Remove the comment
    for(i =0; i< line.length();)
    {   if((line[i]==' '|| line[i]=='\t' ) && first == true)
        {
            start++;
            i++;
        }
        else 
        {  first=false; 
            if(line[i]=='#')
            {    
                 break; //comment
            }
            i++;     
        }
     }
    //comments removed
    *validLine = line.substr(start,i-1);
    return validLine->length();
    
}

void verifyInstr_setType(string instr) //whole line
{   
    //Count the jump labels from here and use the function countLabel()
    //WRITE YOUR CODE HERE
    //instr is valid line
    char *instruc;
    string opcode;
   
}

void printJumpLabels()
{
    int total;
    int bw_index=0;
    int fw_index=0;
    total = max(BackJump,FwdJump);
    cout<<"\n---------------------------------------------------------------"<<endl;
    cout<<"BACKWARD LABEL\t\t\tFORWARD LABEL"<<endl;

    for(int i=0;i<total;i++)
    {
        if(BackJump>i)
        {
            cout<<BW_Labels[bw_index]<<"  \t\t\t\t";
            bw_index++;
        }else{
            cout<<"-------\t\t\t\t";
        }
        if(FwdJump>i)
        {
            cout<<FW_Labels[fw_index]<<endl;
            fw_index++;
        }else{
            cout<<"-------\n";
        }

    }
    cout<<"---------------------------------------------------------------";


}
void printInstrType()
{ 
    cout<<"-----------------TOTAL INSTRUCTIONS----------------------------"<<endl;
    for(int i=0;i<insCount;i++)
     {
        cout<<Instructions[i]<< printType(i) <<endl;
     }
}

string printType(int i)
{

    if(TYPERJI[i]==0)
    {
    return "\t\t    ------ R Type ";
    }
    if(TYPERJI[i]==1)
    {
    return "\t\t    ------ J Type ";
    }
    if(TYPERJI[i]==2)
    {
    return "\t\t    ------ I Type ";
    }
    return "\t\t    ------ Others ";
}


int checkTypeRJI(int i)
{

    if(i<=25)
    {
        return 0;               //type R
    }
    else if(i== 26 || i==27)
    {
        return 1;               //type J
    }
    else if( i<48 && i>=28)
    {
        return 2;               //type immediate
    }
    else
        return -1;           
}


void printCode()
{

    for(int i=0;i<windex;i++)
    {

        cout<<code[i];
        if(Labels[i]==1)
        {
            cout<<"\t\t\t\t-- Label";
        }
        cout<<endl;
    }

}


void countLabels(int i, string str)                  //i is index of instruction and string is label
{
    //WRITE YOUR CODE HERE
    if (str.find(':') != string::npos)
    {
        Labels[i] = 0; // label=0 (it's an instruction)
    }
}
void printDependentInstr()
{
    int total_dependencies;
    total_dependencies= dCount;
    
    cout<<"\n--------------------DEPENDENT INSTRUCTIONS---------------------"<<endl;
    for(int i=0;i<total_dependencies;i++)
    {
        cout<<DependentInstructionSet[i][0]<<"\t ---> "<<DependentInstructionSet[i][1]<<endl;
    }
    cout<<"---------------------------------------------------------------"<<endl;
 
}


void countRegister()
{   
    //WRITE YOUR CODE HERE
    for (int i = 0; i < windex; i++)
    {
        string instr = code[i];
        for (int j = 0; j < 32; j++)
        {
            string reg = registerSet[j];
            if (instr.find(reg) != string::npos)
            {
                countOfReg[j]++;
            }
        }
    }
}

void printNoReg()
{   int count=0;
  cout<<"\n\n---------------------------------------------------------------"<<endl;
  cout<<"Names of Register used     =  ";
     for(int i=0;i<32;i++) 
    {
        if(countOfReg[i]>0)
        {    count++;
             cout<<registerSet[i]<<" ";
        }
    }
    cout<<"\nTotal number of registers  =  "<< count <<endl;
    cout<<"---------------------------------------------------------------"<<endl;
}

void checkDependency()
{
    /*NOTE Dependency for others-type instructions have not been evaluated*/
    // WRITE YOUR CODE HERE
    
 
    cout << "\n\n---------------------------------------------------------------" << endl;
    cout << "Total RAW Dependency       =  " << dCount << endl;
    cout << "---------------------------------------------------------------" << endl;
}