#include <bits/stdc++.h>

using namespace std;
vector<string> MachineCode;
map<string,int> memory;
int pc=0;
int memoutput;

int reg[32];
string dectostr(int n)
{
    string s="";
    if(n==0)
    {
        s="0";
        return s;
    }
    while(n>0)
    {
        char c=n%10+'0';
        s=s+c;
        n/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
string hexToBin(string s)
{
    string ans = "";
    for (int i = 0; i < s.length(); i++)
    {
        string a = "";
        int x;
        if (s[i] <= '9')
        {
            x = s[i] - '0';
        }
        else
        {
            x = s[i] - 'A' + 10;
        }
        for (int i = 0; i < 4; i++)
        {
            if (x % 2 == 0)
            {
                a = a + '0';
            }
            else
            {
                a = a + '1';
            }
            x /= 2;
        }
        reverse(a.begin(), a.end());
        ans = ans + a;
    }

    return ans;
}
string dectobin(int integer, int length)
{
    if (integer >= 0)
    {
        string temp = bitset<32>(integer).to_string();
        int le = temp.length();
        string binary = string(length - le, '0') + temp;
        return binary;
    }
    else
    {
        integer += pow(2, length - 1);
        string temp = bitset<32>(integer).to_string();
        int le = temp.length();
        string binary = "1" + string(length - 1 - le, '0') + temp.substr(1);
        return binary;
    }
}

int savefun(int val,int n)
{
    string s=dectobin(val,32);
    int ans=0;
    int m=1;
    for(int i=0;i<=n;i++)
    {
        if(s[31-i]=='1')
        {
            ans+=m;
        }
        m*=2;
    }

    return ans;
}
void readFile()

{

    ifstream mfile("./input.mc");
    string s;
    while (getline(mfile, s))
    {
        string h = s.substr(s.length() - 8, 8);

        cout<<h<<endl;

        MachineCode.push_back(h);
    }
    for (int i = 0; i < MachineCode.size(); i++)
    {
        cout << MachineCode[i] << endl;
    }
}
struct instr
{
    string op;
    int rs1;
    int rs2;
    int rd;
    int imm;    
};
struct ALU
{
    int mem;
    int wb;
    int ins;
};
void print(struct instr in)
{
    cout<<"op : "<<in.op<<endl;
    cout<<"rd : "<<in.rd<<endl;
    cout<<"rs1 : "<<in.rs1<<endl;
    cout<<"rs2 : "<<in.rs2<<endl;
    cout<<"imm: "<<in.imm<<endl;
}
string tobin(char a) {
    string s = "";
    if (a == '0') {
        a = 0;
    }
    if (a == '1') {
        a = 1;
    }
    if (a == '2') {
        a = 2;
    }
    if (a == '3') {
        a = 3;
    }
    if (a == '4') {
        a = 4;
    }
    if (a == '5') {
        a = 5;
    }
    if (a == '6') {
        a = 6;
    }
    if (a == '7') {
        a = 7;
    }
    if (a == '8') {
        a = 8;
    }
    if (a == '9') {
        a = 9;
    }
    if (a == 'A') {
        a = 10;
    }
    if (a == 'B') {
        a = 11;
    }
    if (a == 'C') {
        a = 12;
    }
    if (a == 'D') {
        a = 13;
    }
    if (a == 'E') {
        a = 14;
    }
    if (a == 'F') {
        a = 15;
    }

    for (int i = 0; i < 4; i++) {
        int x = a % 2;
        // x.toString();
        string temp;
        if(x==1)
        {
            temp="1";
        }
        else
        {
            temp="0";
        }
        s.append(temp);
        a = a/2;
    }
    // reverse(s);
    string s2 = "";
    int l = s.size();
    for (int i = 0; i < l; i++) {
        s2 = s[i] + s2;
    }
    // reverse(s2.begin(),s2.end());
    return s2;

}

int negative(string a) {

    int m = 1;
    int ans = 0;
    for (int i = a.size() - 1; i > 0; i--) {
        if (a[i] == '1') {
            ans += m;
        }
        m *= 2;
    }
    ans -= m;
    return ans;
}

int toint(string a) {
    int l = a.size();
    int ans = 0;
    int m = 1;
    for (int i = l - 1; i >= 0; i--) {
        if (a[i] == '1') {
            ans = ans + m;
        }
        m = m * 2;
    }

    return ans;
}

struct instr convert(string a) {
    string s = "";
    struct instr ret;
    ret.op="error";
    ret.rs1=-1;
    ret.rs2=-1;
    ret.rd=-1;
    int l = a.size();
    for (int i = 0; i < l; i++) {
        string s1 = tobin(a[i]);
        s = s + s1;
    }
    string opcode = "";
    for (int i = 25; i < 32; i++) {
        opcode = opcode + s[i];
    }

    if (opcode == "0110011") {
        // let ret = { op: "", rd: 0, rs1: 0, rs2: 0,imm: 0 }
        string r = "";
        for (int i = 20; i < 25; i++) {
            r = r + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        string r1 = "";
        for (int i = 12; i < 17; i++) {
            r1 = r1 + s[i];
        }
        string r2 = "";
        for (int i = 7; i < 12; i++) {
            r2 = r2 + s[i];
        }

        string fun7 = "";
        for (int i = 0; i < 7; i++) {
            fun7 = fun7 + s[i];
        }
        ret.rs1 = toint(r1);
        ret.rs2 = toint(r2);
        ret.rd = toint(r);
        if (fun3 == "000" && fun7 == "0000000") {
            ret.op = "add";

        }
        else if (fun3 == "000" && fun7 == "0100000") {
            ret.op = "sub";
        }
        else if (fun3 == "100" && fun7 == "0000000") {
            ret.op = "xor";
        }
        else if (fun3 == "110" && fun7 == "0000000") {
            ret.op = "or";
        }
        else if (fun3 == "111" && fun7 == "0000000") {
            ret.op = "and";
        }
        else if (fun3 == "001" && fun7 == "0000000") {
            ret.op = "sll";
        }
        else if (fun3 == "101" && fun7 == "0000000") {
            ret.op = "srl";
        }
        else if (fun3 == "101" && fun7 == "0100000") {
            ret.op = "sra";
        }
        else if (fun3 == "010" && fun7 == "0000000") {
            ret.op = "slt";
        }
        else if (fun3 == "011" && fun7 == "0000000") {
            ret.op = "sltu";
        }

        return ret;
    }

    else if (opcode == "0010011") {
        // int ret = { op: 0, rd: 0, rs1: 0, imm:0,rs2:0 }
        string r = "";
        for (int i = 20; i < 25; i++) {
            r = r + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }


        string r1 = "";
        for (int i = 12; i < 17; i++) {
            r1 = r1 + s[i];
        }

        string imm = "";
        for (int i = 0; i < 12; i++) {
            imm = imm + s[i];
        }

        string fun7 = "";
        for (int i = 0; i < 7; i++) {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1') {
            ret.imm = negative(imm);
        }
        else {
            ret.imm = toint(imm);

        }

        if (fun3 == "000") {
            ret.op = "add";

        }
        else if (fun3 == "100") {
            ret.op = "xor";
        }
        else if (fun3 == "110") {
            ret.op = "or";
        }
        else if (fun3 == "111") {
            ret.op = "and";
        }
        else if (fun3 == "001" && fun7 == "0000000") {
            ret.op = "sll";
        }
        else if (fun3 == "101" && fun7 == "0000000") {
            ret.op = "srl";
        }
        else if (fun3 == "101" && fun7 == "0100000") {
            ret.op = "sra";
        }
        else if (fun3 == "010") {
            ret.op = "slt";
        }
        else if (fun3 == "011") {
            ret.op = "sltu";
        }
        ret.op = ret.op + 'i';

        return ret;

    }
    else if (opcode == "0000011") {
        // let ret = { op: "", rd: 0, rs1: 0, imm: 0,rs2:0}
        string r = "";
        
        for (int i = 20; i < 25; i++) {
            r = r + s[i];
        }
        // console.log("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        // console.log("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++) {
            r1 = r1 + s[i];
        }
        // console.log("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++) {
            imm = imm + s[i];
        }

        // console.log("imm : "+toint(imm))
        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1') {

            ret.imm =negative(imm);
        }
        else {
            ret.imm = toint(imm);
        }

        if (fun3 == "000") {
            ret.op = "lb";
        }
        else if (fun3 == "001") {
            ret.op = "lh";
        }
        else if (fun3 == "010") {
            ret.op = "lw";
        }
        else if (fun3 == "100") {
            ret.op = "lbu";
        }
        else if (fun3 == "101") {
            ret.op = "lhu";
        }
        return ret;

    }
    else if (opcode == "0100011")
    {
        // let ret = { op: "", rs1: 0, rs2: 0, imm: 0,rd:0 }
        
        string imm = "";
        
        for (int i = 0; i < 7; i++) {
            imm = imm + s[i];
        }
        for (int i = 20; i < 25; i++) {
            imm = imm + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        // console.log("fun3 : " + fun3)

        string rs1 = "";
        for (int i = 12; i < 17; i++) {
            rs1 = rs1 + s[i];
        }
        // console.log("rs1 : "+toint(rs1))

        string rs2 = "";
        for (int i = 7; i < 12; i++) {
            rs2 = rs2 + s[i];
        }

        // console.log("rs2 : "+toint(rs2))



        // console.log("fun7 : "+fun7)
        // console.log("imm : " + toint(imm))

        ret.rs1 = toint(rs1);
        ret.rs2 = toint(rs2);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }

        if (fun3 == "000") {
            ret.op = "sb";
        }
        else if (fun3 == "001") {
            ret.op = "sh";
        }
        else if (fun3 == "010") {
            ret.op = "sw";
        }

        return ret;

    }

    else if (opcode == "1100011") {
        // int ret = { op: "", rs1:0, rs2: 0, imm: 0,rd:0 }
        string imm = "";
        imm = imm + s[0];
        imm = imm + s[24];

        for (int i = 1; i < 7; i++) {
            imm = imm + s[i];
        }
        for (int i = 20; i < 24; i++) {
            imm = imm + s[i];
        }
        imm=imm+"0";
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        // console.log("fun3 : " + fun3)

        string rs1 = "";
        for (int i = 12; i < 17; i++) {
            rs1 = rs1 + s[i];
        }
        // console.log("rs1 : "+toint(rs1))

        string rs2 = "";
        for (int i = 7; i < 12; i++) {
            rs2 = rs2 + s[i];
        }

        // console.log("rs2 : "+toint(rs2))
        // console.log("imm : " + toint(imm))
        ret.rs1 = toint(rs1);
        ret.rs2 = toint(rs2);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }

        if (fun3 == "000") {
            ret.op = "beq";
        }
        else if (fun3 == "001") {
            ret.op = "bne";
        }
        else if (fun3 == "100") {
            ret.op = "blt";
        }
        else if (fun3 == "101") {
            ret.op = "bge";
        }
        else if (fun3 == "110") {
            ret.op = "bltu";
        }
        else if (fun3 == "111") {
            ret.op = "bgeu";
        }


        return ret;

        // console.log("fun7 : "+fun7)



    }
    else if (opcode == "0110111" || opcode == "0010111") {
        // let ret = { op: 0, rd: 0, imm: 0,rs1:0,rs2:0 }
        string rd = "";
        for (int i = 20; i < 25; i++) {
            rd = rd + s[i];
        }
        // console.log("rd : " + toint(rd))

        string imm = "";
        for (int i = 0; i < 20; i++) {
            imm = imm + s[i];
        }

        // console.log("imm : "+toint(imm))

        ret.rd = toint(rd);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }

        if (opcode == "0010111") {
            ret.op = "auipc";
        }
        else {
            ret.op = "lui";
        }

        return ret;

    }
    else if (opcode == "1101111") {
        // let ret = { op: "", rd: 0, imm: 0,rs1:0,rs2:0}
        string rd = "";
        for (int i = 20; i < 25; i++) {
            rd = rd + s[i];
        }
        // console.log("rd : " + toint(rd))

        string imm = "";
        imm = imm + s[0];
        for (int i = 12; i < 20; i++) {
            imm = imm + s[i];
        }
        imm = imm + s[11];
        for (int i = 1; i < 11; i++) {
            imm = imm + s[i];
        }
        imm += '0';

        // console.log("imm : "+toint(imm))

        ret.rd = toint(rd);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }
        ret.op = "jal";

        return ret;

    }
    else if (opcode == "1100111") {
        // let ret = { op: "", rd: 0, rs1: 0, imm: 0,rd:0 }
        string r = "";
        for (int i = 20; i < 25; i++) {
            r = r + s[i];
        }
        // console.log("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        // console.log("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++) {
            r1 = r1 + s[i];
        }
        // console.log("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++) {
            imm = imm + s[i];
        }

        // console.log("imm : "+toint(imm))
        string fun7 = "";
        for (int i = 0; i < 7; i++) {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }

        if (fun3 == "000") {
            ret.op = "jalr";
        }

        return ret;
    }
    else if (opcode == "1110011") {
        // let ret = { op: "", rd: 0, rs1: 0, imm:0 ,rs2: 0 }
        string r = "";
        for (int i = 20; i < 25; i++) {
            r = r + s[i];
        }
        // console.log("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++) {
            fun3 = fun3 + s[i];
        }

        // console.log("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++) {
            r1 = r1 + s[i];
        }
        // console.log("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++) {
            imm = imm + s[i];
        }

        // console.log("imm : "+toint(imm))
        string fun7 = "";
        for (int i = 0; i < 7; i++) {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1') {
            ret.imm = negative(imm);

        }
        else {
            ret.imm = toint(imm);

        }
        int imm1 = toint(imm);
        if (fun3 == "000") {
            if (imm1 == 0) {
                ret.op = "ecall";
            }
            else if (imm1 == 1) {
                ret.op = "ebreak";
            }
        }

        return ret;
    }




}

int execute(struct instr ins)
{
    string op=ins.op;
    int rs1=ins.rs1;
    int rs2=ins.rs2;
    int rd=ins.rd;
    int imm=ins.imm;
    int alu=0;

    if(op=="add")
    {
        alu=reg[rs1]+reg[rs2];
    }
    if(op=="sub")
    {
        alu=reg[rs1]-reg[rs2];

    }
    if(op=="xor")
    {
        alu=reg[rs1]^reg[rs2];

    }
    if(op=="or")
    {
        alu=reg[rs1]|reg[rs2];
    }
    if(op=="and")
    {
        alu=reg[rs1]&reg[rs2];
        
    }
    if(op=="sll")
    {
        alu=reg[rs1]<<reg[rs2];
    }
    if(op=="srl")
    {
        alu=reg[rs1]>>reg[rs2];

    }
    if(op=="sra")
    {
        alu=reg[rs1]>>reg[rs2];

    }
    if(op=="slt")
    {
        alu=reg[rs1]<reg[rs2]?1:0;

    }
    if(op=="sltu")
    {
        alu=reg[rs1]<reg[rs2]?1:0;

    }







    if(op=="addi")
    {
        alu=reg[rs1]+imm;
    }
    if(op=="xori")
    {
        alu=reg[rs1]^imm;
    }
    if(op=="ori")
    {
        alu=reg[rs1]|imm;
    }
    if(op=="andi")
    {
        alu=reg[rs1]&imm;
    }
    if(op=="slli")
    {
        alu=reg[rs1]<<imm;
    }
    if(op=="srli")
    {
        alu=reg[rs1]>>imm;
    }
    if(op=="srai")
    {
        alu=reg[rs1]>>imm;
    }
    if(op=="slti")
    {
        alu=(reg[rs1]<imm)?1:0;
    }
    if(op=="sltiu")
    {
        alu=(reg[rs1]<imm)?1:0;
        
    }




    if(op=="lb")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,7);
    }
    if(op=="lw")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,15);
    }
    if(op=="lh")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,31);
    }
    if(op=="lbu")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,7);
    }
    if(op=="lhu")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,15);
    }

    int rs11=reg[rs1];
    int rs12=reg[rs2];



    if(op=="beq")
    {
        if(rs11==rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
        
    }
    if(op=="bne")
    {
        if(rs11!=rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
    }
    if(op=="blt")
    {
        if(rs11<rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
    }
    if(op=="bge")
    {
        if(rs11>=rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
    }
    if(op=="bltu")
    {
        if(rs11<rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
    }
    if(op=="bgeu")
    {
        if(rs11>=rs12)
        {
            alu=imm;
        }
        else
        {
            alu=4;
        }
    }
        


    if(op=="sb")
    {
        alu=reg[rs1]+imm;
        alu=savefun(alu,7);
    }


    if(op=="jalr")
    {
        alu=imm;
        alu=savefun(alu,15);
    }
    if(op=="jal")
    {
        alu=imm;
        alu=savefun(alu,31);
    }
    return alu;



}

void memoryfun(struct instr ins)
{
    string op=ins.op;
    if(op=="sb" || op=="sh" || op=="sw")
    {
        int alu=execute(ins);
        string save=dectostr(alu);
        memory[save]=ins.rs1;
    }

    if(op=="lb" || op=="lh" || op=="lw" || op=="lbu" || op=="lhu")
    {
        int alu=execute(ins);
        string save=dectostr(alu);
        memoutput=memory[save];
    }
}

void writeback(struct instr ins)
{
    string op=ins.op;
    int alu=execute(ins);
    if(op=="sb" || op=="sh" || op=="sw")
    {
        return;
    }
    if(op=="bge" || op=="blt" || op=="bne" || op=="beq" || op=="bltu" || op=="bgeu" || op=="jal" || op=="jalr")
    {
        return;
    }
    if(op=="lb" || op=="lh" || op=="lw" || op=="lbu" || op=="lhu")
    {
        int rd=ins.rd;
        reg[rd]=memoutput;
    }
    else 
    {
        reg[ins.rd]=alu;
    }
}

int address(struct instr ins)
{
    int add_pc=4;
    string op=ins.op;

    if(op=="bge" || op=="blt" || op=="bne" || op=="beq" || op=="bltu" || op=="bgeu" || op=="jal" || op=="jalr")
    {
        int alu=execute(ins);
        add_pc=alu;
        if(alu==0)
        {
            add_pc=4;
        }
    }

    return add_pc;

}
int main()
{
    readFile();
    reg[3]=15;
   
   int sz=MachineCode.size();
   while(pc<4*sz)
   {
        string hex_code=MachineCode[pc/4];

        struct instr instruction=convert(hex_code);

        cout<<(instruction.op)<<(instruction.rs1);
        print(instruction);
        int alu=execute(instruction);
        memoryfun(instruction);
        writeback(instruction);
        pc+=address(instruction);

   cout<<endl;
        
   }

   for(int i=0;i<32;i++)
   {
        cout<<"x"<<i<<" "<<reg[i]<<endl;
   }



   return 0;

}