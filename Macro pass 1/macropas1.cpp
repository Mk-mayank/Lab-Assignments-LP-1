#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    map<int, map<string, string>> MNT;
    map<int, string> MDT;
    map<int, map<string, string>> KPDTAB;
    vector<string> PNTAB;

    int MNT_counter = 1;
    int KPDTAB_counter = 0;
    int MDTP_counter = 1;
    bool got_header = false;

    void main(const vector<string>& input_file) {
        for (const auto& instruction : input_file) {
            if (instruction == "MACRO") {
                got_header = true;
            }
            else if (instruction == "MEND") {
                process_mend();
            }
            else if (got_header) {
                got_header = false;
                process_mnt(instruction);
            }
            else {
                process_body(instruction);
            }
        }
    }

    void process_mnt(const string& ins) {
        stringstream ss(ins);
        string name, params;
        ss >> name >> params;

        vector<string> parameters = split(params, ',');
        int current_kpdtp_index = KPDTAB_counter + 1;
        int keyword = 0;
        int positional = 0;

        for (const auto& param : parameters) {
            if (param.find('=') != string::npos) {
                keyword++;
                PNTAB.push_back(param);
                process_kpdtab(param);
            }
            else {
                positional++;
                PNTAB.push_back(param);
            }
        }

        string kpdtp = "-";
        if (keyword != 0) {
            kpdtp = to_string(current_kpdtp_index);
        }

        MNT[MNT_counter] = {
            {"Name", name},
            {"#PP", to_string(positional)},
            {"#KP", to_string(keyword)},
            {"MDTP", to_string(MDTP_counter)},
            {"KPDTP", kpdtp}
        };
        MNT_counter++;
    }

    void process_kpdtab(const string& parameter) {
        auto pos = parameter.find('=');
        string name = parameter.substr(0, pos);
        string value = (pos + 1 < parameter.size()) ? parameter.substr(pos + 1) : "No default value";

        KPDTAB[++KPDTAB_counter] = {
            {"Name", name},
            {"Value", value}
        };
    }

    void process_body(const string& word) {
        stringstream ss(word);
        string instruction, param_string;
        ss >> instruction >> param_string;

        vector<string> params = split(param_string, ',');
        string ins_line = instruction + " ";
        vector<string> param_references;

        for (const string& param : params) {
            auto it = find(PNTAB.begin(), PNTAB.end(), param);
            int index = (it != PNTAB.end()) ? distance(PNTAB.begin(), it) + 1 : -1;
            if (index > 3) {
                index -= 3;
            }
            param_references.push_back("(P," + to_string(index) + ")");
        }

        ins_line += join(param_references, " ");
        MDT[MDTP_counter++] = ins_line;
    }

    void process_mend() {
        MDT[MDTP_counter++] = "MEND";
    }

    void show_Result() const {
        cout << "Sr.No\tName\t#PP\t#KP\tMDTP\tKPDTP\n";
        for (const auto& [sr_no, entry] : MNT) {
            cout << sr_no << "\t" << entry.at("Name") << "\t" << entry.at("#PP") << "\t"
                 << entry.at("#KP") << "\t" << entry.at("MDTP") << "\t" << entry.at("KPDTP") << "\n";
        }

        cout << "\nMDT\nSr.No\tInstruction\n";
        for (const auto& [sr_no, instruction] : MDT) {
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

int main() {
    ifstream file("input.txt");
    string line;
    vector<string> input_file;
    while (getline(file, line)) {
        input_file.push_back(line);
    }
    file.close();

    Process obj;
    obj.main(input_file);
    obj.show_Result();

    return 0;
}
