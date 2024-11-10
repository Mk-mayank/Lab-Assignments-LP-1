#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Process{
    public:
        map<int,map<string,string>>MNT_Table;
        map<int,string>MDT_table;
        map<int,map<string,string>>KPDTAB;
        vector<string>PNTAB;

        int mnt_counter = 1; 
        int mdt_counter = 1; 
        int kpd_counter = 0;
        bool headerFound = false;

        void mainfunc(vector<string>&input_line){
            for(auto instructions : input_line){
                if(instructions == "MACRO"){
                    headerFound = true;
                }
                else if( instructions == "MEND"){
                    process_mend();
                }
                else if( headerFound ){
                    headerFound = false;
                    process_mnt(instructions);
                }
                else{
                    process_body(instructions);
                }
            }
        }

        void process_mnt(string ins){
            string name , parameters ;
            stringstream ss(ins);
            ss >> name >> parameters;
            vector<string>ParametersPresent = split(parameters,',');
            int kpdtab_index = kpd_counter + 1 ;
            int positional_argu = 0 ;
            int keyword_arg = 0 ;

            for( auto p : ParametersPresent){
                if(p.find('=') != string::npos){
                    //keyword wala present
                    process_kpdtab(p);
                    PNTAB.push_back(p);
                    keyword_arg++;
                }
                else{
                    PNTAB.push_back(p);
                    positional_argu++;
                }
            }
            string kpdtp = "-";
                    if(keyword_arg != 0){
                        kpdtp = to_string(kpdtab_index);
                    }

                    MNT_Table[mnt_counter]={
                        {"Name", name},
                        {"#PP" , to_string(positional_argu)},
                        {"#KP" , to_string(keyword_arg)},
                        {"MDTP",to_string(mdt_counter)},
                        {"KPTABP" , kpdtp}
                    };
                    mnt_counter++;
        }

        void process_kpdtab(string parameter){
            auto position = parameter.find('=');
            string name = parameter.substr(0,position);
            string Value ;
            if(position+1 < parameter.size()){
                Value = parameter.substr(position+1);
            }
            else{
                Value = "No default M/c";
            }
            KPDTAB[++kpd_counter]={
                {"Name" , name},
                {"Value",Value}
            };
        }

        void process_body(string ins){
            string name , parameters ;
            stringstream ss(ins);
            ss >> name >> parameters;
            vector<string>allparameters = split(parameters,',');
            vector<string>v ; //imp
            string ans = name + " ";

            for(auto p : allparameters){
                auto it = find(PNTAB.begin(),PNTAB.end(),p);
                int index = (it != PNTAB.end()) ? distance(PNTAB.begin(), it) + 1 : -1;
                if (index > 3) {
                index -= 3;
                }
                v.push_back("(P," + to_string(index) + ")");
            }
            ans += join(v, " ");
            MDT_table[mdt_counter++] = ans;
        };

        void process_mend(){
            MDT_table[mdt_counter++] = "MEND";
        };
            void show_Result() const {
        cout << "Sr.No\tName\t#PP\t#KP\tMDTP\tKPDTP\n";
        for (const auto& [sr_no, entry] : MNT_Table) {
            cout << sr_no << "\t" << entry.at("Name") << "\t" << entry.at("#PP") << "\t"
                 << entry.at("#KP") << "\t" << entry.at("MDTP") << "\t" << entry.at("KPTABP") << "\n";
        }

        cout << "\nMDT\nSr.No\tInstruction\n";
        for (const auto& [sr_no, instruction] : MDT_table) {
            cout << sr_no << "\t" << instruction << "\n";
        }

        cout << "\nKPDTAB\nSr.No\tName\tValue\n";
        for (const auto& [sr_no, entry] : KPDTAB) {
            cout << sr_no << "\t" << entry.at("Name") << "\t" << entry.at("Value") << "\n";
        }
    }

private:
    static vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static string join(const vector<string>& vec, const string& delimiter) {
        ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i != 0) {
                oss << delimiter;
            }
            oss << vec[i];
        }
        return oss.str();
    }
};


int main(){
    ifstream file("input.txt");
    string line;
    vector<string>input_lines;
    while(getline(file,line)){
        input_lines.push_back(line);
    }

    file.close();
    
    Process obj;
    obj.mainfunc(input_lines);
    obj.show_Result();

    return 0;
}