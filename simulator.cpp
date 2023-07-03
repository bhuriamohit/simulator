#include <bits/stdc++.h>

using namespace std;
#include<bits/stdc++.h>
using namespace std;
int hitin=0;
int missin=0;
string repoli;
int hit=0;
int miss=0;
int peep=0;
int access=0;
int accessin=0;
int cold=0;
int coldin=0;
int capacity=0;
int capacityin=0;
class set_associative_cache {
public:
    int size, ass, curr, div,blocksize,cachesize,as,data=0;
    string repoli;
    unordered_map<int,int> usage;
    unordered_map<int,int> queue;
    unordered_map<int,vector<int>> array;

public:
    set_associative_cache(int size, int ass) {
        this->size = size;
        this->ass = ass;
        this->curr = 0;
        this->div = this->size / this->ass;
        for(int i=0; i<this->div; i++) {
            this->array[i] = {};
        }
    }
public :
     set_associative_cache() {
        int blocksize;
       int cachesize;
       int as;
       string repoli;
       if(peep==0)
       {cout<<"for intruction caches:"<<endl;
        cout<<" NOTE:(>32)"<<endl;
       peep++;}
       else {
        cout<<"for data caches:"<<endl;
       this->data=1;
       }

       cout<<"enter cachesize:";

       cin>>cachesize;
      cout<<"enter block size:"<<endl;
      cin>>blocksize;
      
      cout<<"Enter associativity:";
      cin>>as;
      cout<<"Enter replacement policy:"<<endl;
     
     cin>>repoli;
       this->cachesize=cachesize;
      this->repoli=repoli;
      if(peep==0){
        blocksize=blocksize/8;
      }
      this->blocksize=blocksize;
        this->size = this->cachesize/this->blocksize;
        this->ass = as;
        this->curr = 0;
        this->div = this->size / this->ass;
        for(int i=0; i<this->div; i++) {
            this->array[i] = {};
        }
    }

    void print() {
        for(int i=0; i<this->div; i++) {
            cout<<"div"<<i+1<<"ass"<<this->array[i].size()<<endl;
            for(int j=0; j<this->array[i].size(); j++) {
                
                cout << this->array[i][j] << " ";
                for(int k=1;k<blocksize/4;k++){
                    cout<<this->array[i][j]+(4*k)<<" ";
                }
                cout<<endl;
            }
            cout << endl;
        }
    }

    string readcache(int addr) {
        if(this->find(addr)=="present") {
            if(this->usage.find(addr)==this->usage.end()) {
                this->usage[addr-(addr%blocksize)]=1;
            }
            else {
                this->usage[addr-(addr%blocksize)]++;
            }
            return "hit";
        }
        else {
            return "miss";
        }
    }

    string find(int addr) {
        int pos = (addr-(addr%blocksize)) % this->div;
        for(int i=0; i<this->array[pos].size(); i++) {
            if(this->array[pos][i]==addr-(addr%blocksize)) {
                return "present";
            }
        }
        return "not present";
    }

    void insert(int addr) {

        if(this->find(addr-(addr%blocksize))=="not present") {
            int pos = (addr/blocksize) % (this->div);
            //cout<<"pos"<<pos<<endl;
            if(this->array[pos].size() < this->ass) {
                if(this->data==0){
                    coldin++;
                }
                else{
                    cold++;
                }
                this->array[pos].push_back(addr-(addr%blocksize));
                this->usage[addr-(addr%blocksize)]=0;
               // cout << (addr-(addr%blocksize)) << " is added" << endl;
            }
            else {
                int ind=this->remove(repoli,addr-(addr%blocksize));
if(data==0){
    capacityin++;
}
else {
    capacity++;
}
               // cout << this->array[pos][ind] << " is removed" << endl;
                this->array[pos][ind]=addr-(addr%blocksize);
                this->usage[addr-(addr%blocksize)]=0;
               // cout <<(addr-(addr%blocksize)) << " is added" << endl;
            }
        }
        else {
          //  cout << "already present" << endl;
        }
    }

    int remove(string policy, int addr) {
        int pos=(addr/blocksize)%(this->div);
        if(policy=="random") {
            int rn=rand()%this->ass;
            return rn;
        }
        if(policy=="LFU") {
            int ind=0;
            int rem=0;
            for(int i=0; i<this->ass; i++) {
                if(this->usage[this->array[pos][i]]<=this->usage[this->array[pos][ind]]) {
                    ind=rem;
                    rem=i;
                }
            }
            return rem;
        }
        if(policy=="FIFO") {
            int rem=this->queue[pos];
            this->queue[pos]++;
            return rem%this->ass;
        }
        return -1;
    }
};
// class set_associative_cache {
// public:
//     int size, ass, curr, div,blocksize,cachesize,as;
//     string repoli;
//     unordered_map<int,int> usage;
//     unordered_map<int,int> queue;
//     unordered_map<int,vector<int>> array;

// public:
//     set_associative_cache(int size, int ass) {
//         this->size = size;
//         this->ass = ass;
//         this->curr = 0;
//         this->div = this->size / this->ass;
//         for(int i=0; i<this->div; i++) {
//             this->array[i] = {};
//         }
//     }
// public :
//      set_associative_cache() {
//         int blocksize;
//        int cachesize;
//        int as;
//        string repoli;
//        if(peep==0)
//        {cout<<"for intruction caches"<<endl;
//         cout<<" NOTE:(>32)"<<endl;
//        peep++;}
//        else {
//         cout<<"for data caches"<<endl;
       
//        }

//        cout<<"enter cachesize";

//        cin>>cachesize;
//       cout<<"enter block size"<<endl;
//       cin>>blocksize;
      
//       cout<<"Enter associativity";
//       cin>>as;
//       cout<<"Enter replacement policy"<<endl;
     
//      cin>>repoli;
//        this->cachesize=cachesize;
//       this->repoli=repoli;
//       if(peep==0){
//         blocksize=blocksize/8;
//       }
//       this->blocksize=blocksize;
//         this->size = this->cachesize/this->blocksize;
//         this->ass = as;
//         this->curr = 0;
//         this->div = this->size / this->ass;
//         for(int i=0; i<this->div; i++) {
//             this->array[i] = {};
//         }
//     }

//     void print() {
//         for(int i=0; i<this->div; i++) {
//             cout<<"div"<<i+1<<"ass"<<this->array[i].size()<<endl;
//             for(int j=0; j<this->array[i].size(); j++) {
                
//                 cout << this->array[i][j] << " ";
//                 for(int k=1;k<blocksize/4;k++){
//                     cout<<this->array[i][j]+(4*k)<<" ";
//                 }
//                 cout<<endl;
//             }
//             cout << endl;
//         }
//     }

//     string readcache(int addr) {
//         if(this->find(addr)=="present") {
//             if(this->usage.find(addr)==this->usage.end()) {
//                 this->usage[addr-(addr%blocksize)]=1;
//             }
//             else {
//                 this->usage[addr-(addr%blocksize)]++;
//             }
//             return "hit";
//         }
//         else {
//             return "miss";
//         }
//     }

//     string find(int addr) {
//         int pos = (addr-(addr%blocksize)) % this->div;
//         for(int i=0; i<this->array[pos].size(); i++) {
//             if(this->array[pos][i]==addr-(addr%blocksize)) {
//                 return "present";
//             }
//         }
//         return "not present";
//     }

//     void insert(int addr) {

//         if(this->find(addr-(addr%blocksize))=="not present") {
//             int pos = (addr/blocksize) % (this->div);
//             cout<<"pos"<<pos<<endl;
//             if(this->array[pos].size() < this->ass) {
//                 this->array[pos].push_back(addr-(addr%blocksize));
//                 this->usage[addr-(addr%blocksize)]=0;
//                 cout << (addr-(addr%blocksize)) << " is added" << endl;
//             }
//             else {
//                 int ind=this->remove(repoli,addr-(addr%blocksize));
//                 cout << this->array[pos][ind] << " is removed" << endl;
//                 this->array[pos][ind]=addr-(addr%blocksize);
//                 this->usage[addr-(addr%blocksize)]=0;
//                 cout <<(addr-(addr%blocksize)) << " is added" << endl;
//             }
//         }
//         else {
//             cout << "already present" << endl;
//         }
//     }

//     int remove(string policy, int addr) {
//         int pos=(addr/blocksize)%(this->div);
//         if(policy=="random") {
//             int rn=rand()%this->ass;
//             return rn;
//         }
//         if(policy=="LFU") {
//             int ind=0;
//             int rem=0;
//             for(int i=0; i<this->ass; i++) {
//                 if(this->usage[this->array[pos][i]]<=this->usage[this->array[pos][ind]]) {
//                     ind=rem;
//                     rem=i;
//                 }
//             }
//             return rem;
//         }
//         if(policy=="FIFO") {
//             int rem=this->queue[pos];
//             this->queue[pos]++;
//             return rem%this->ass;
//         }
//         return -1;
//     }
// };
 set_associative_cache I$;
 set_associative_cache D$;


int tempx = 0;
int cycles;
int instructionsexecuted;
float CPI;
int datatrans = 0;
int aluinstr = 0;
int ctrlinstr = 0;
int nofstalls = 0;
int datahazards = 0;
int ctrlhazard = 0;
int branchmis = 0;
int stalldata = 0;
int stallctrl = 0;
struct instr
{
    string opcode;
    string op;
    int rs1;
    int rs2;
    int rd = -1;
    int imm;
    string func3;
    string func7;
};
vector<string> MachineCode;
vector<instr> instru;
map<string, int> memory;
vector<instr> tex;
int sz;
int pc = 0;
int memoutput;
string convertHexa(int);
int execute(struct instr);

int reg[32];
string dectostr(int n)
{
    int k = n;
    string s = "";
    if (n == 0)
    {
        s = "0";
        return s;
    }
    if (n < 0)
    {
        // s="-";
        n = -n;
    }
    while (n > 0)
    {
        char c = n % 10 + '0';
        s = s + c;
        n /= 10;
    }
    if (k < 0)
    {
        s = s + "-";
    }
    reverse(s.begin(), s.end());
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
        integer = (1 << 31) + integer;
        // integer += pow(2, length - 1);
        // string temp = bitset<32>(integer).to_string();
        // int le = temp.length();
        // string binary = "1" + string(length - 1 - le, '0') + temp[1];
        string binary = bitset<32>(integer).to_string();
        binary[0] = '1';
        return binary;
    }
}

int savefun(int val, int n)
{
    string s = dectobin(val, 32);
    int ans = 0;
    int m = 1;
    for (int i = 0; i <= n; i++)
    {
        if (s[31 - i] == '1')
        {
            ans += m;
        }
        m *= 2;
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

        //  cout << h << endl;

        MachineCode.push_back(h);
    }
    for (int i = 0; i < MachineCode.size(); i++)
    {
        cout << MachineCode[i] << endl;
    }
}

struct ALU
{
    int mem;
    int wb;
    int ins;
};
void print(struct instr in)
{
    cout << "op : " << in.op << endl;
    cout << "rd : " << in.rd << endl;
    cout << "rs1 : " << in.rs1 << endl;
    cout << "rs2 : " << in.rs2 << endl;
    cout << "imm: " << in.imm << endl;
    cout << "alu: " << execute(in) << endl;
}
string tobin(char a)
{
    string s = "";
    if (a == '0')
    {
        a = 0;
    }
    if (a == '1')
    {
        a = 1;
    }
    if (a == '2')
    {
        a = 2;
    }
    if (a == '3')
    {
        a = 3;
    }
    if (a == '4')
    {
        a = 4;
    }
    if (a == '5')
    {
        a = 5;
    }
    if (a == '6')
    {
        a = 6;
    }
    if (a == '7')
    {
        a = 7;
    }
    if (a == '8')
    {
        a = 8;
    }
    if (a == '9')
    {
        a = 9;
    }
    if (a == 'A')
    {
        a = 10;
    }
    if (a == 'B')
    {
        a = 11;
    }
    if (a == 'C')
    {
        a = 12;
    }
    if (a == 'D')
    {
        a = 13;
    }
    if (a == 'E')
    {
        a = 14;
    }
    if (a == 'F')
    {
        a = 15;
    }

    for (int i = 0; i < 4; i++)
    {
        int x = a % 2;
        // x.toString();
        string temp;
        if (x == 1)
        {
            temp = "1";
        }
        else
        {
            temp = "0";
        }
        s.append(temp);
        a = a / 2;
    }
    // reverse(s);
    string s2 = "";
    int l = s.size();
    for (int i = 0; i < l; i++)
    {
        s2 = s[i] + s2;
    }
    // reverse(s2.begin(),s2.end());
    return s2;
}

int negative(string a)
{

    int m = 1;
    int ans = 0;
    for (int i = a.size() - 1; i > 0; i--)
    {
        if (a[i] == '1')
        {
            ans += m;
        }
        m *= 2;
    }
    ans -= m;
    return ans;
}

int toint(string a)
{
    int l = a.size();
    int ans = 0;
    int m = 1;
    for (int i = l - 1; i >= 0; i--)
    {
        if (a[i] == '1')
        {
            ans = ans + m;
        }
        m = m * 2;
    }

    return ans;
}

struct instr convert(string a)
{
    string s = "";
    struct instr ret;
    ret.op = "error";
    ret.rs1 = -1;
    ret.rs2 = -1;
    ret.rd = -1;
    int l = a.size();
    for (int i = 0; i < l; i++)
    {
        string s1 = tobin(a[i]);
        s = s + s1;
    }
    string opcode = "";
    for (int i = 25; i < 32; i++)
    {
        opcode = opcode + s[i];
    }
    ret.opcode = opcode;
    if (opcode == "0110011")
    {
        // let ret = { op: "", rd: 0, rs1: 0, rs2: 0,imm: 0 }
        string r = "";
        for (int i = 20; i < 25; i++)
        {
            r = r + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        string r1 = "";
        for (int i = 12; i < 17; i++)
        {
            r1 = r1 + s[i];
        }
        string r2 = "";
        for (int i = 7; i < 12; i++)
        {
            r2 = r2 + s[i];
        }

        string fun7 = "";
        for (int i = 0; i < 7; i++)
        {
            fun7 = fun7 + s[i];
        }
        ret.rs1 = toint(r1);
        ret.rs2 = toint(r2);
        ret.rd = toint(r);
        ret.func3 = fun3;
        ret.func7 = fun7;
        if (fun3 == "000" && fun7 == "0000000")
        {
            ret.op = "add";
        }
        else if (fun3 == "000" && fun7 == "0100000")
        {
            ret.op = "sub";
        }
        else if (fun3 == "100" && fun7 == "0000000")
        {
            ret.op = "xor";
        }
        else if (fun3 == "110" && fun7 == "0000000")
        {
            ret.op = "or";
        }
        else if (fun3 == "111" && fun7 == "0000000")
        {
            ret.op = "and";
        }
        else if (fun3 == "001" && fun7 == "0000000")
        {
            ret.op = "sll";
        }
        else if (fun3 == "101" && fun7 == "0000000")
        {
            ret.op = "srl";
        }
        else if (fun3 == "101" && fun7 == "0100000")
        {
            ret.op = "sra";
        }
        else if (fun3 == "010" && fun7 == "0000000")
        {
            ret.op = "slt";
        }
        else if (fun3 == "011" && fun7 == "0000000")
        {
            ret.op = "sltu";
        }

        return ret;
    }

    else if (opcode == "0010011")
    {
        // int ret = { op: 0, rd: 0, rs1: 0, imm:0,rs2:0 }
        string r = "";
        for (int i = 20; i < 25; i++)
        {
            r = r + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        string r1 = "";
        for (int i = 12; i < 17; i++)
        {
            r1 = r1 + s[i];
        }

        string imm = "";
        for (int i = 0; i < 12; i++)
        {
            imm = imm + s[i];
        }

        string fun7 = "";
        for (int i = 0; i < 7; i++)
        {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (fun3 == "000")
        {
            ret.op = "add";
        }
        else if (fun3 == "100")
        {
            ret.op = "xor";
        }
        else if (fun3 == "110")
        {
            ret.op = "or";
        }
        else if (fun3 == "111")
        {
            ret.op = "and";
        }
        else if (fun3 == "001" && fun7 == "0000000")
        {
            ret.op = "sll";
        }
        else if (fun3 == "101" && fun7 == "0000000")
        {
            ret.op = "srl";
        }
        else if (fun3 == "101" && fun7 == "0100000")
        {
            ret.op = "sra";
        }
        else if (fun3 == "010")
        {
            ret.op = "slt";
        }
        else if (fun3 == "011")
        {
            ret.op = "sltu";
        }
        ret.op = ret.op + 'i';

        return ret;
    }
    else if (opcode == "0000011")
    {
        // let ret = { op: "", rd: 0, rs1: 0, imm: 0,rs2:0}
        string r = "";

        for (int i = 20; i < 25; i++)
        {
            r = r + s[i];
        }
        // ("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        // ("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++)
        {
            r1 = r1 + s[i];
        }
        // ("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++)
        {
            imm = imm + s[i];
        }

        // ("imm : "+toint(imm))
        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1')
        {

            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (fun3 == "000")
        {
            ret.op = "lb";
        }
        else if (fun3 == "001")
        {
            ret.op = "lh";
        }
        else if (fun3 == "010")
        {
            ret.op = "lw";
        }
        else if (fun3 == "100")
        {
            ret.op = "lbu";
        }
        else if (fun3 == "101")
        {
            ret.op = "lhu";
        }
        return ret;
    }
    else if (opcode == "0100011")
    {
        // let ret = { op: "", rs1: 0, rs2: 0, imm: 0,rd:0 }

        string imm = "";

        for (int i = 0; i < 7; i++)
        {
            imm = imm + s[i];
        }
        for (int i = 20; i < 25; i++)
        {
            imm = imm + s[i];
        }
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        // ("fun3 : " + fun3)

        string rs1 = "";
        for (int i = 12; i < 17; i++)
        {
            rs1 = rs1 + s[i];
        }
        // ("rs1 : "+toint(rs1))

        string rs2 = "";
        for (int i = 7; i < 12; i++)
        {
            rs2 = rs2 + s[i];
        }

        // ("rs2 : "+toint(rs2))

        // ("fun7 : "+fun7)
        // ("imm : " + toint(imm))

        ret.rs1 = toint(rs1);
        ret.rs2 = toint(rs2);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (fun3 == "000")
        {
            ret.op = "sb";
        }
        else if (fun3 == "001")
        {
            ret.op = "sh";
        }
        else if (fun3 == "010")
        {
            ret.op = "sw";
        }

        return ret;
    }

    else if (opcode == "1100011")
    {
        // int ret = { op: "", rs1:0, rs2: 0, imm: 0,rd:0 }
        string imm = "";
        imm = imm + s[0];
        imm = imm + s[24];

        for (int i = 1; i < 7; i++)
        {
            imm = imm + s[i];
        }
        for (int i = 20; i < 24; i++)
        {
            imm = imm + s[i];
        }
        imm = imm + "0";
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        // ("fun3 : " + fun3)

        string rs1 = "";
        for (int i = 12; i < 17; i++)
        {
            rs1 = rs1 + s[i];
        }
        // ("rs1 : "+toint(rs1))

        string rs2 = "";
        for (int i = 7; i < 12; i++)
        {
            rs2 = rs2 + s[i];
        }

        // ("rs2 : "+toint(rs2))
        // ("imm : " + toint(imm))
        ret.rs1 = toint(rs1);
        ret.rs2 = toint(rs2);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (fun3 == "000")
        {
            ret.op = "beq";
        }
        else if (fun3 == "001")
        {
            ret.op = "bne";
        }
        else if (fun3 == "100")
        {
            ret.op = "blt";
        }
        else if (fun3 == "101")
        {
            ret.op = "bge";
        }
        else if (fun3 == "110")
        {
            ret.op = "bltu";
        }
        else if (fun3 == "111")
        {
            ret.op = "bgeu";
        }

        return ret;

        // ("fun7 : "+fun7)
    }
    else if (opcode == "0110111" || opcode == "0010111")
    {
        // let ret = { op: 0, rd: 0, imm: 0,rs1:0,rs2:0 }
        string rd = "";
        for (int i = 20; i < 25; i++)
        {
            rd = rd + s[i];
        }
        // ("rd : " + toint(rd))

        string imm = "";
        for (int i = 0; i < 20; i++)
        {
            imm = imm + s[i];
        }

        // ("imm : "+toint(imm))

        ret.rd = toint(rd);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (opcode == "0010111")
        {
            ret.op = "auipc";
        }
        else
        {
            ret.op = "lui";
        }

        return ret;
    }
    else if (opcode == "1101111")
    {
        // let ret = { op: "", rd: 0, imm: 0,rs1:0,rs2:0}
        string rd = "";
        for (int i = 20; i < 25; i++)
        {
            rd = rd + s[i];
        }
        // ("rd : " + toint(rd))

        string imm = "";
        imm = imm + s[0];
        for (int i = 12; i < 20; i++)
        {
            imm = imm + s[i];
        }
        imm = imm + s[11];
        for (int i = 1; i < 11; i++)
        {
            imm = imm + s[i];
        }
        imm += '0';

        // ("imm : "+toint(imm))

        ret.rd = toint(rd);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }
        ret.op = "jal";

        return ret;
    }
    else if (opcode == "1100111")
    {
        // let ret = { op: "", rd: 0, rs1: 0, imm: 0,rd:0 }
        string r = "";
        for (int i = 20; i < 25; i++)
        {
            r = r + s[i];
        }
        // ("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        // ("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++)
        {
            r1 = r1 + s[i];
        }
        // ("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++)
        {
            imm = imm + s[i];
        }

        // ("imm : "+toint(imm))
        string fun7 = "";
        for (int i = 0; i < 7; i++)
        {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }

        if (fun3 == "000")
        {
            ret.op = "jalr";
        }

        return ret;
    }
    else if (opcode == "1110011")
    {
        // let ret = { op: "", rd: 0, rs1: 0, imm:0 ,rs2: 0 }
        string r = "";
        for (int i = 20; i < 25; i++)
        {
            r = r + s[i];
        }
        // ("rd : " + toint(r))
        string fun3 = "";

        for (int i = 17; i < 20; i++)
        {
            fun3 = fun3 + s[i];
        }

        // ("fun3 : " + fun3)

        string r1 = "";
        for (int i = 12; i < 17; i++)
        {
            r1 = r1 + s[i];
        }
        // ("rs1 : "+toint(r1))

        string imm = "";
        for (int i = 0; i < 12; i++)
        {
            imm = imm + s[i];
        }

        // ("imm : "+toint(imm))
        string fun7 = "";
        for (int i = 0; i < 7; i++)
        {
            fun7 += imm[i];
        }

        ret.rs1 = toint(r1);
        ret.rd = toint(r);
        if (imm[0] == '1')
        {
            ret.imm = negative(imm);
        }
        else
        {
            ret.imm = toint(imm);
        }
        int imm1 = toint(imm);
        if (fun3 == "000")
        {
            if (imm1 == 0)
            {
                ret.op = "ecall";
            }
            else if (imm1 == 1)
            {
                ret.op = "ebreak";
            }
        }

        return ret;
    }
}

int execute(struct instr ins)
{
    string op = ins.op;
    int rs1 = ins.rs1;
    int rs2 = ins.rs2;
    int rd = ins.rd;
    int imm = ins.imm;
    int alu = 0;

    if (op == "add")
    {
        alu = reg[rs1] + reg[rs2];
    }
    if (op == "sub")
    {
        alu = reg[rs1] - reg[rs2];
    }
    if (op == "xor")
    {
        alu = reg[rs1] ^ reg[rs2];
    }
    if (op == "or")
    {
        alu = reg[rs1] | reg[rs2];
    }
    if (op == "and")
    {
        alu = reg[rs1] & reg[rs2];
    }
    if (op == "sll")
    {
        alu = reg[rs1] << reg[rs2];
    }
    if (op == "srl")
    {
        alu = reg[rs1] >> reg[rs2];
    }
    if (op == "sra")
    {
        alu = reg[rs1] >> reg[rs2];
    }
    if (op == "slt")
    {
        alu = reg[rs1] < reg[rs2] ? 1 : 0;
    }
    if (op == "sltu")
    {
        alu = reg[rs1] < reg[rs2] ? 1 : 0;
    }

    if (op == "addi")
    {
        alu = reg[rs1] + imm;
    }
    if (op == "xori")
    {
        alu = reg[rs1] ^ imm;
    }
    if (op == "ori")
    {
        alu = reg[rs1] | imm;
    }
    if (op == "andi")
    {
        alu = reg[rs1] & imm;
    }
    if (op == "slli")
    {
        alu = reg[rs1] << imm;
    }
    if (op == "srli")
    {
        alu = reg[rs1] >> imm;
    }
    if (op == "srai")
    {
        alu = reg[rs1] >> imm;
    }
    if (op == "slti")
    {
        alu = (reg[rs1] < imm) ? 1 : 0;
    }
    if (op == "sltiu")
    {
        alu = (reg[rs1] < imm) ? 1 : 0;
    }

    if (op == "lb")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 7);
    }
    if (op == "lw")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 31);
    }
    if (op == "lh")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 31);
    }
    if (op == "lbu")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 7);
    }
    if (op == "lhu")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 15);
    }

    int rs11 = reg[rs1];
    int rs12 = reg[rs2];

    if (op == "beq")
    {
        if (rs11 == rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }
    if (op == "bne")
    {
        if (rs11 != rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }
    if (op == "blt")
    {
        if (rs11 < rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }
    if (op == "bge")
    {
        if (rs11 >= rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }
    if (op == "bltu")
    {
        if (rs11 < rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }
    if (op == "bgeu")
    {
        if (rs11 >= rs12)
        {
            alu = imm;
        }
        else
        {
            alu = 4;
        }
    }

    if (op == "sb")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 7);
    }
    if (op == "sh")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 15);
    }
    if (op == "sw")
    {
        alu = reg[rs1] + imm;
        alu = savefun(alu, 31);
    }

    if (op == "jalr")
    {
        alu = imm;
        alu = savefun(alu, 15);
    }
    if (op == "jal")
    {
        alu = imm;
        alu = savefun(alu, 31);
    }

    if (op == "lui")
    {
        alu = imm << 12;
    }
    if (op == "auipc")
    {
        alu = imm << 12;
    }
    return alu;
}

void memoryfun(struct instr ins)
{

    string op = ins.op;
    if (op == "sb" || op == "sh" || op == "sw")
    {
        int alu = execute(ins);
        string save = dectostr(alu);
        memory[save] = reg[ins.rs2];
        // string s=save+ "  : " +dectostr(reg[ins.rs1]);
    }

    if (op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu")
    {
        int alu = execute(ins);

        string save = dectostr(alu);
        memoutput = memory[save];
    }
}

void writeback(struct instr ins)
{
    string op = ins.op;
    int alu = execute(ins);
    if (op == "sb" || op == "sh" || op == "sw")
    {
        return;
    }
    else if (op == "bge" || op == "blt" || op == "bne" || op == "beq" || op == "bltu" || op == "bgeu" || op == "jal" || op == "jalr")
    {
        return;
    }
    else if (op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu")
    {
        int rd = ins.rd;
        int alu = execute(ins);
        // cout<<"write back alu ;"<<alu<<endl;
        string s = dectostr(alu);
        // cout<<"write back ka "<<rd<<endl;
        reg[rd] = memory[s];
        // cout<<"memory : "<<reg[rd]<<endl;
    }
    else if (op == "lui")
    {
        int rd = ins.rd;
        reg[rd] = alu;
    }
    else if (op == "auipc")
    {
        int rd = ins.rd;
        reg[rd] = alu + pc;
    }
    else
    {
        reg[ins.rd] = alu;
    }
}

int address(struct instr ins)
{
    int add_pc = 4;
    string op = ins.op;

    if (op == "bge" || op == "blt" || op == "bne" || op == "beq" || op == "bltu" || op == "bgeu" || op == "jal" || op == "jalr")
    {
        int alu = execute(ins);
        add_pc = alu;
        if (alu == 0)
        {
            add_pc = 4;
        }
    }

    return add_pc;
}
string convertHexa(int number)
{
    string hexa;
    // loop till number>0
    while (number)
    {
        int rem = number % 16;
        // when rem is less than 10 then store 0-9
        // else store A - F
        if (rem < 10)
            hexa.push_back(rem + '0');
        else
            hexa.push_back(rem - 10 + 'A');

        number = number / 16;
    }
    reverse(hexa.begin(), hexa.end());
    return hexa;
}
string create_ins(struct instr instruction)
{
    string op = instruction.op;
    int rd = instruction.rd;
    int rs1 = instruction.rs1;
    int rs2 = instruction.rs2;
    int imm = instruction.imm;
    string s = "";
    if (op == "bge" || op == "blt" || op == "bne" || op == "beq" || op == "bltu" || op == "bgeu" || op == "jal" || op == "jalr")
    {
        s = op + " x" + dectostr(rs1) + " x" + dectostr(rs2) + " " + dectostr(imm);
    }
    if (op == "add" || op == "sub" || op == "xor" || op == "or" || op == "and" || op == "sll" || op == "srl" || op == "sra" || op == "slt" || op == "sltu")
    {
        s = op + " x" + dectostr(rd) + " x" + dectostr(rs1) + " x" + dectostr(rs2);
    }
    if (op == "addi" || op == "xori" || op == "ori" || op == "andi" || op == "slli" || op == "srli" || op == "srai" || op == "slti" || op == "sltiu")
    {
        s = op + " x" + dectostr(rd) + " x" + dectostr(rs1) + " " + dectostr(imm);
    }
    if (op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu")
    {
        s = op + " x" + dectostr(rd) + " " + dectostr(imm) + "(x" + dectostr(rs1) + ")";
    }
    if (op == "sb" || op == "sh" || op == "sw")
    {
        s = op + " x" + dectostr(rs2) + " " + dectostr(imm) + "(x" + dectostr(rs1) + ")";
    }
    if (op == "jal" || op == "jalr")
    {
        s = op + " x" + dectostr(rd) + " " + dectostr(imm);
    }
    if (op == "lui" || op == "auipc")
    {
        string s = op + " x" + dectostr(rd) + " " + dectostr(imm);
        return s;
    }
    if (op == "ecall" || op == "ebreak")
    {
        s = op;
    }

    return s;
}
void create_mem()
{
    ofstream memfile("./Memory.txt");
    memfile << "Addresses    :     value stored \n";
    for (auto i : memory)
    {
        string x = i.first;
        string s = convertHexa(stoi(x)) + "  :  " + dectostr(i.second) + "\n";
        memfile << s;
    }
}

int cycle = 4;
struct IF
{

    int pc = -4;
    string instruction = "";
};

struct ID
{
    string op = "";
    int pc = -4;
    int rs1 = -1;
    int rs2 = -1;
    int imm;
    int rd = -1;
    string opcode;
    string func3;
    string func7;
};

struct EX
{
    string op = "";
    int pc = -4;
    int rs1 = -1;
    int rs2 = -1;
    int imm;
    int rd = -1;
    string opcode = "";
    string funct3;
    string funct7;
    int alu_result;
};

struct MEM
{
    int pc = -4;
    int rs1 = -1;
    int rs2 = -1;
    int imm;
    int rd = -1;
    string opcode = "";
    string funct3 = "";
    string funct7 = "";
    int alu_result;
    string mem_address = "";
    int mem_data;
    string op = "";
};

struct WB
{
    int pc = -4;
    int rs1=-1;
    int rs2=-1;
    int imm;
    int rd=-1;
    string opcode="";
    string funct3="";
    string funct7="";
    int alu_result;
    int mem_data;
};

// Define the pipeline registers
IF if_id_reg;
ID id_ex_reg;
EX ex_mem_reg;
MEM mem_wb_reg;
vector<int> stalls;

IF pfetch(int PC)
{
    IF pinstr;
    // cout<<"sz"<<sz<<endl;
    // cout<<" [fetch m pc]"<<PC<<endl;
    if (PC > 4 * sz)
    {
        pinstr.instruction = "";
        pinstr.pc = PC - 4;
    }
    else
    {
       string kell= I$.readcache(pc);
       accessin++;
       if(kell=="hit"){
        hitin++;
       }
       else{
        missin++;
        I$.insert(pc);
       }
        string hex_code = MachineCode[PC / 4];
        struct instr instruction = convert(hex_code);
        // cout<<"pfetch m hex code"<<hex_code<<endl;
        pinstr.instruction = hex_code;
        pinstr.pc = PC;
    }
    return pinstr;
}
ID pdecode(IF reg)
{ // cout<<"decode mai pc"<<reg.instruction<<endl;
    ID ins;
    if (reg.pc == -4)
    {
        return ins;
    }
    else if (reg.instruction != "")
    {
        string hexcode = reg.instruction;
        struct instr instruction = convert(hexcode);
        ins.pc = reg.pc;
        ins.rs1 = instruction.rs1;
        ins.rs2 = instruction.rs2;
        ins.imm = instruction.imm;
        ins.rd = instruction.rd;
        ins.opcode = instruction.opcode;
        ins.func3 = instruction.func3;
        ins.func7 = instruction.func7;
        ins.op = instruction.op;

        return ins;
    }

    else
    {

        cout << " all fetched";
        ins.pc = reg.pc;
        return ins;
    }
}
EX pexecute(ID reg)
{ // cout<<" exct m pc"<<reg.op<<endl;
    EX exe;

    // if (reg.pc == 4 * sz && reg.op == "")
    // {
    //     cout << "all executed" << endl;
    //     exe.op = "";
    //     exe.pc = reg.pc;
    // }

    if (reg.pc == -4)
    {
        exe.op = "";
        exe.pc = reg.pc;
    }
    else
    {
        instr ins;
        exe.pc = reg.pc;
        exe.rs1 = reg.rs1;
        exe.rs2 = reg.rs2;
        exe.imm = reg.imm;
        exe.rd = reg.rd;
        exe.opcode = reg.func3;
        exe.funct3 = reg.func3;
        exe.funct7 = reg.func7;
        exe.op = reg.op;
        ins.op = reg.op;
        ins.rd = reg.rd;
        ins.rs1 = reg.rs1;

        ins.rs2 = reg.rs2;
        ins.imm = reg.imm;
        exe.alu_result = execute(ins);
        //      cout<<" ex m pc"<<exe.pc<<endl;
        // cout<<" exct m ins"<<exe.op<<endl;
    }
    return exe;
}
MEM pmem(EX regg)
{
    MEM mem;
    if (regg.pc == -4)
    {
        cout << "if" << endl;
        mem.op = " ";
        mem.pc = -4;
    }
    else
    {
        mem.pc = regg.pc;
        mem.rs1 = regg.rs1;
        mem.rs2 = regg.rs2;
        mem.imm = regg.imm;
        mem.rd = regg.rd;
        mem.opcode = regg.opcode;
        mem.funct3 = regg.funct3;
        mem.funct7 = regg.funct7;
        mem.alu_result = regg.alu_result;
        mem.op = regg.op;

        int rs2 = mem.rs2;
        int pmemout;
        string paddress;
        string op = regg.op;
        if (op == "sb" || op == "sh" || op == "sw")
        {
            int alu = mem.alu_result;
            string save = dectostr(alu);
          // cout<<save<<endl;
           string res= D$.readcache(alu);
           access++;
           if(res=="hit"){
hit++;
           }
           else {
            miss++;
            D$.insert(alu);
           }

            memory[save] = reg[rs2];
            datatrans++;
            // string s=save+ "  : " +dectostr(reg[ins.rs1]);
        }

        if (op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu")
        {
            datatrans++;
            // int alu = execute(ins);
            int alu = regg.alu_result;
            string save = dectostr(alu);
             string res= D$.readcache(alu);
             access++;
           if(res=="hit"){
hit++;
           }
           else {
            miss++;
            D$.insert(alu);
           }

            pmemout = memoutput = memory[save];
        }
        mem.mem_address = paddress;
        mem.mem_data = pmemout;
    }
    // cout<<"pmem m pc "<<mem.op<<endl;
    return mem;
}
WB pwriteback(MEM regis)
{

    WB wrtn;

    if (regis.pc == -4)
    {
        cout << "-4" << endl;
        wrtn.pc = -4;
    }
    else
    {
        wrtn.pc = regis.pc;
        wrtn.rs1 = regis.rs1;
        wrtn.rs2 = regis.rs2;
        wrtn.imm = regis.imm;
        wrtn.rd = regis.rd;
        wrtn.opcode = regis.opcode;
        wrtn.funct3 = regis.funct3;
        wrtn.funct7 = regis.funct7;
        wrtn.alu_result = regis.alu_result;
        wrtn.mem_data = regis.mem_data;

        int rd = regis.rd;
        string op = regis.op;
        int alu = regis.alu_result;
        if (op == "sb" || op == "sh" || op == "sw")
        {
        }
        else if (op == "bge" || op == "blt" || op == "bne" || op == "beq" || op == "bltu" || op == "bgeu" || op == "jal" || op == "jalr")
        {
        }
        else if (op == "lb" || op == "lh" || op == "lw" || op == "lbu" || op == "lhu")
        {
            int rd = regis.rd;
            // int alu=execute(ins);
            //  cout<<"write back alu ;"<<alu<<endl;
            string s = dectostr(alu);
            // cout<<"write back ka "<<rd<<endl;
            reg[rd] = memory[s];
            // cout<<"memory : "<<reg[rd]<<endl;
        }
        else if (op == "lui")
        {
            //  int rd = ins.rd;
            reg[rd] = alu;
        }
        else if (op == "auipc")
        {
            // int rd = ins.rd;
            reg[rd] = alu + pc;
        }
        else
        {
            reg[rd] = alu;
            // cout<<"wb dn";
        }
    }
    // cout<<" pwb me pc"<<wrtn.rd<<endl;
    return wrtn;
}

// Function to calculate stalls for a vector of instructions
struct cycleval{
    IF if_id_reg;
ID id_ex_reg;
EX ex_mem_reg;
MEM mem_wb_reg;
};
vector<cycleval> cyclereg;

int nostall(vector<instr> vex)
{
    int sum = 0;
    // vector<int> v;

    for (int i = 1; i < vex.size(); i++)
    {
        instr inst1 = vex[i];
        instr inst2;
        instr inst3;
        instr inst4;
        if (i > 0)
        {
            inst2 = vex[i - 1];
        }
        if (i > 1)
        {
            inst3 = vex[i - 2];
        }
        if (i > 2)
        {
            inst4 = vex[i - 3];
        }
        if ((inst1.rs1 == inst2.rd || inst2.rd == inst1.rs2) && inst2.rd != -1 && i > 0)
        {
            datahazards++;
            sum = sum + 3;
            //stalls.push_back(3);
        }
        else if ((inst3.rd == inst1.rs1 || inst1.rs2 == inst3.rd) && inst3.rd != -1 && i > 1)
        {
            datahazards++;
            sum = sum + 2;
           // stalls.push_back(2);
        }
        else if ((inst1.rs2 == inst4.rd || inst1.rs1 == inst4.rd) && inst4.rd != -1 && i > 2)
        {
            datahazards++;
            sum = sum + 1;
           // stalls.push_back(1);
        }
        else
        {
           // stalls.push_back(0);
        }
        stalls.push_back(sum);
    }
    // tempx = sum;
    return sum;
}
int datafor(vector<instr> vex)
{

    // vector<int> v;
    int sum = 0;
    for (int i = 1; i < vex.size(); i++)
    {
        // 1  cout<<"opcode"<<vex[i-1].opcode<<endl;
        if ((vex[i].rs1 == vex[i - 1].rd || vex[i].rs2 == vex[i - 1].rd) && vex[i - 1].opcode == "0000011")
        {
            sum++;
            datahazards++;
            //stalls.push_back(1);
        }
      else  {
           // stalls.push_back(0);
        }
         stalls.push_back(sum);
    }

    return sum;
}
map<int, int> pred;
int chaz = 0;
int choice;
int pipeline;
int cicle = 0;

int main()
{

    readFile();
    reg[3] = 0;
    stalls.push_back(0);
    sz = MachineCode.size();
    cout << "pipeline on/off(1/0)?";
    cin >> pipeline;
 cout<<" enter cache size"<<endl;
      
    cout<<choice<<endl;
   
    ofstream ins_file("./instruction_file.txt");
    // cout << "sizze" << sz << endl;
    pc = 0;
    
    while (pc < 4 * sz)
    {

     

        string hex_code = MachineCode[pc / 4];

        struct instr instruction = convert(hex_code);
        if (instruction.opcode == "0110011")
        {
            aluinstr++;
        }
        if (instruction.opcode == "1101111" || instruction.opcode == "1100111" || instruction.opcode == "1100011")
        {
            ctrlinstr++;
        }

        tex.push_back(instruction);
        // cout << pc << endl;
        if_id_reg = pfetch(pc);
        // cout << "if_id pc" << if_id_reg.pc << endl;
        id_ex_reg = pdecode(if_id_reg);
        // cout << "id_ex" << id_ex_reg.pc << endl;
        ex_mem_reg = pexecute(id_ex_reg);

        mem_wb_reg = pmem(ex_mem_reg);
        WB wbad = pwriteback(mem_wb_reg);
        instru.push_back(instruction);
        string s = create_ins(instruction) + "\n";
        ins_file << s;
       

        if (pred[pc] == 0 && (instruction.opcode == "1100011" || instruction.opcode == "1101111"))
        {
            ctrlhazard++;
            if (address(instruction) != 4)
            {
                pred[pc] = 1;
                chaz++;
            }
            else
            {
            }
        }
        if (pred[pc] == 1 && (instruction.opcode == "1100011" || instruction.opcode == "1101111"))
        {
            ctrlhazard++;
            if (address(instruction) == 4)
            {
                chaz++;
                pred[pc] = 0;
            }
        }
        pc += address(instruction);

        cout << endl;
    }

    branchmis = chaz;
    stallctrl = 2 * chaz;

    int x;

    if (pipeline == 0)
    {
        for (int i = 0; i < tex.size(); i++)
        {
            print(tex[i]);
        }
        cout<<"For I$:"<<endl;
        int memorystallsin=hitin+(20*missin);
        int memorystalls=hit+(20*miss);
        float CPI = static_cast<float>(5*tex.size()+memorystallsin+memorystallsin) / tex.size();
        // cout << "total number of cycles " << (5 * tex.size()) << endl;
        // cout << "total instruction executed " << tex.size() << endl;
        // cout << "CPI :" << endl;
        // cout << "No. of data transfer "
        //      << "0" << endl;
        // cout << "No. of ALU instruction " << aluinstr << endl;
        // cout << "No. of control instruction executed " << ctrlinstr << endl;
        // cout << "there were no stalls and no hazards" << endl;
        cout<<"No. of access:"<<accessin<<endl;
        cout<<"No. of hits:"<<hitin<<endl;
        cout<<"No. of misses"<<missin<<endl;
        cout<<"No. of cold misses"<<coldin<<endl;
        cout<<"No. of capacity misses"<<capacityin<<endl;
        cout<<"No. of memory stalls"<<memorystallsin<<endl;
        cout<<"CPI:"<<CPI<<endl;
          cout<<"***************************"<<endl;
          cout<<"D$"<<endl;
          cout<<"No. of access:"<<access<<endl;
        cout<<"No. of hits:"<<hit<<endl;
        cout<<"No. of misses"<<miss<<endl;
        cout<<"No. of cold misses"<<cold<<endl;
        cout<<"No. of capacity misses"<<capacity<<endl;
        cout<<"No. of memory stalls"<<memorystalls<<endl;
        cout<<"CPI:"<<CPI<<endl;
    }
    else if (pipeline == 1)
    {
        cout << "data forwarding on/off(1/0)?";
        cin >> choice;
        if (choice == 1)
        {
            x = datafor(tex);
        }
        if (choice == 0)
        {
            x = nostall(tex);
        }
        
        cycles = cycle + 2 * chaz + x + tex.size();
        nofstalls = chaz * 2 + x;
        CPI = cycles / tex.size();
        
        int memorystallsin=hitin+(20*missin);
        int memorystalls=hit+(20*miss);
        CPI = static_cast<float>(cycles+memorystalls+memorystallsin) / tex.size();
        // cout << "total number of cycles " << cycles << endl;
        // cout << "total instruction executed " << tex.size() << endl;
        // cout << "CPI " << CPI << endl;
        // cout << "No. of data transfer " << datatrans << endl;
        // cout << "No. of ALU instruction " << aluinstr << endl;
        // cout << "No. of control instruction executed " << ctrlinstr << endl;
        // cout << "No. of stall/bubbles in pipeline " << nofstalls << endl;
        // cout << "No. of data hazards " << datahazards << endl;
        // cout << "NO. of control hazards " << ctrlhazard << endl;
        // cout << "No. of branch mispredictions " << chaz << endl;
        // cout << "No. of stalls due to data hazards " << x << endl;
        // cout << "No. of stalls due to control hazards " << 2 * chaz << endl;
        for (int i = 0; i < tex.size(); i++)
        {
            print(tex[i]);
        }
        cout<<"I$"<<endl;
         cout<<"No. of access:"<<accessin<<endl;
        cout<<"No. of hits:"<<hitin<<endl;
        cout<<"No. of misses"<<missin<<endl;
        cout<<"No. of cold misses"<<coldin<<endl;
        cout<<"No. of capacity misses"<<capacityin<<endl;
        cout<<"No. of memory stalls"<<memorystallsin<<endl;
        cout<<"CPI:"<<CPI<<endl;
          cout<<"***************************"<<endl;
          cout<<"D$:"<<endl;
          cout<<"No. of access:"<<access<<endl;
        cout<<"No. of hits:"<<hit<<endl;
        cout<<"No. of misses"<<miss<<endl;
        cout<<"No. of cold misses"<<cold<<endl;
        cout<<"No. of capacity misses"<<capacity<<endl;
        cout<<"No. of memory stalls"<<memorystalls<<endl;
        cout<<"CPI:"<<CPI<<endl;
    }
// cout<<"hit"<<hit<<endl;
// cout<<"miss"<<miss<<endl;
// cout<<"hitin"<<hitin<<endl;
// cout<<"missin"<<missin<<endl;
// cout<<"capacityin"<<accessin<<endl;
// cout<<"capacity"<<access<<endl;
    ofstream regis("./register_file.txt");

    for (int i = 0; i < 32; i++)
    {
        string s = "x" + dectostr(i) + "  :  " + dectostr(reg[i]) + "\n";
        regis << s;
    }
    create_mem();

    return 0;
}
