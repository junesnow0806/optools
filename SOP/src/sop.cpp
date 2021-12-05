#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
class SOPText {
public:
    SOPText() {}
    void set_probtype(std::string);
    void set_objective(std::string);
    void add_subjeccive(std::string);
    void add_bounds(std::string);
    void add_general(std::string);
    void add_binary(std::string);
    ~SOPText() {}
private:
    std::string probtype;
    std::string objective;
    std::vector<std::string> subjectives;
    std::vector<std::string> bounds;
    std::vector<std::string> general;
    std::vector<std::string> binary;
};
*/

void pipHandler(std::ifstream &infile, std::ofstream &outfile) {
    outfile << "Probtype pip" << std::endl << std::endl;

    std::string next_line;

    // handle Objective
    outfile << "Objective:" << std::endl;
    outfile << "    ";
    std::string obj_type;
    getline(infile, obj_type);
    if (obj_type == "Maximize") {
        outfile << "max z = ";
        getline(infile, next_line);
        next_line = next_line.substr(next_line.find(':')+1);    // 不需要"obj:"
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << "    " << next_line << std::endl;
    } else if (obj_type == "Minimize") {
        outfile << "min z = ";
        getline(infile, next_line);
        next_line = next_line.substr(next_line.find(':')+1);  // 不需要"obj:"
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << "    " << next_line << std::endl;
    } else {
        std::cerr << "invalid objective type " << obj_type << std::endl;
        exit(-1);
    }
    outfile << std::endl;

    // handle Subjectives
    getline(infile, next_line);  // 该行是"Subject to"
    outfile << "Subject to:" << std::endl;
    getline(infile, next_line);
    while (next_line != std::string("Bounds")) {
        next_line = next_line.substr(next_line.find(':')+1);  // 不需要"ci:"
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << "    " << next_line << std::endl;
        getline(infile, next_line);
    }
    outfile << std::endl;

    // handle Bounds
    outfile << "Bounds:" << std::endl;
    getline(infile, next_line);
    while (next_line != std::string("Binary") && next_line != std::string("General") && next_line != std::string("End")) {
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        outfile << "    " << next_line << std::endl;
        getline(infile, next_line);
    }
    outfile << std::endl;

    // handle General
    if (next_line == std::string("General")) {
            while (next_line != std::string("Binary") && next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
            outfile << "    " << next_line << std::endl;
            getline(infile, next_line);
        }
        outfile << std::endl;
    }

    // handle Binary
    if (next_line == std::string("Bianry")) {
            while (next_line != std::string("End")) {
            //next_line = next_line.substr(next_line.find(':')+1);
            next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
            outfile << "    " << next_line << std::endl;
            getline(infile, next_line);
        }
        outfile << std::endl;
    }

    outfile << "End";
    std::cout << "Successfully converted pip to sop." << std::endl;
}

void wboHandler(std::ifstream &infile, std::ofstream &outfile) {
    outfile << "Probtype pip" << std::endl << std::endl;

    // there is no objective function

    // handle Subjectives
    std::string next_line;
    getline(infile, next_line);     // 第一行的信息不需要
    outfile << "Subject to:" << std::endl;
    while (getline(infile, next_line) && next_line != std::string("Bounds")) {
        next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
        next_line.erase(next_line.find_last_of(';'));   // 删除行尾的';'
        outfile << "    " << next_line << std::endl;
    }
    outfile << std::endl;

    // handle Bounds
    if (next_line == std::string("Bounds")) {
        outfile << "Bounds:" << std::endl;
        getline(infile, next_line);
        while (next_line != std::string("Binary") && next_line != std::string("General") && next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
            outfile << "    " << next_line << std::endl;
            getline(infile, next_line);
        }
        outfile << std::endl;
    }

    // handle General
    if (next_line == std::string("General")) {
            while (next_line != std::string("Binary") && next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
            outfile << "    " << next_line << std::endl;
            getline(infile, next_line);
        }
        outfile << std::endl;
    }

    // handle Binary
    if (next_line == std::string("Bianry")) {
            while (next_line != std::string("End")) {
            next_line.erase(0, next_line.find_first_not_of(' '));   // 删除行首空格
            outfile << "    " << next_line << std::endl;
            getline(infile, next_line);
        }
        outfile << std::endl;
    }    

    outfile << "End";
    std::cout << "Successfully converted wbo to sop." << std::endl;
}

void mpsHandler(std::ifstream &infile, std::ofstream &outfile) {

}

int main() {
    std::cout << "Input file to open: ";
    std::string file_name;
    std::cin >> file_name;
    std::string file_type = file_name.substr(file_name.find_last_of('.') + 1);
    std::string prefix = file_name.substr(0, file_name.find_last_of('.'));
    
    std::string outpath("../output/");
    std::string suffix(".sop");
    std::ofstream outfile(outpath + prefix + suffix);

    std::ifstream infile(file_name);
    if (file_type == "lp") {

    } else if (file_type == "cnf") {

    } else if (file_type == "opb") {

    } else if (file_type == "pip") {
        pipHandler(infile, outfile);
    } else if (file_type == "wbo") {
        wboHandler(infile, outfile);
    } else if (file_type == "mps") {
        mpsHandler(infile, outfile);
    } else {
        std::cerr << "invalid file type " << file_type << std::endl;
        exit(-1);
    }

    infile.close();
    outfile.close();
    return 0;
}